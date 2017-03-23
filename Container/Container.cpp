/*
 * Container.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Container.h"
#include <sstream>
#include <climits>

Container::Container() {
	start = end = signal_size = 0;
	confidence = 1.0f;
	cost = 0.0f;
	containerType = ONE_OF;
	parentContainer = NULL;
	grammarRef = NULL;
	modelRef = NULL;
	offset_to_start = 0;
	verbal = false;
}

Container::~Container() {
}

/**
 * This method set the start for an interpretation
 */
void Container::setStart(unsigned long long start) {
	this->start = start;
}

/**
 * This method set the duration of an interpretation
 */
void Container::setDuration(unsigned long long dur) {
	if( end==0 ) {
		end = start+dur;
	}
	else if (start==0 ) {
		if (((long)end-(long)dur)>=0 ) {
			start = end-dur;
		}
	}
	else {
		end = max(end, start+dur);
	}
}

/**
 * This method set the end for an interpretation
 */
void Container::setEnd(unsigned long long end) {
	this->end = end;
}

void Container::addDerivedFrom(DerivedFrom* derivedFrom) {
	if( derivedFrom )
		this->derivedFrom.push_back( derivedFrom );
}

/**
 * This method updates local start and end considering
 * autonomous intervals for children
 */
void Container::finalizeCreation() {
	unsigned long 	tmpStart, tmpEnd;
	float			maxConfidence;
	vector<Interpretation*>::iterator intIt;
	vector<Container*>::iterator conIt;

	tmpStart = ULONG_MAX;
	tmpEnd = 0;
	maxConfidence = 0;

	for( intIt=interprets.begin(); intIt!=interprets.end(); intIt++ ) {
		// Update start and finish from children interpretation
		if ((*intIt)->getStart() < tmpStart)
			tmpStart = (*intIt)->getStart();
		if ((*intIt)->getEnd() > tmpEnd)
			tmpEnd = (*intIt)->getEnd();

		// Update confidence from children interpretations
		if( (*intIt)->getConfidence() > maxConfidence )
			maxConfidence = (*intIt)->getConfidence();
	}

	for( conIt=nested.begin(); conIt!=nested.end(); conIt++ ) {
		// Update start and finish from children containers
		if ((*conIt)->getStart() < tmpStart)
			tmpStart = (*conIt)->getStart();
		if ((*conIt)->getEnd() > tmpEnd)
			tmpEnd = (*conIt)->getEnd();

		// Update confidence from children interpretations
		if( (*conIt)->getConfidence() > maxConfidence )
			maxConfidence = (*conIt)->getConfidence();
	}

	if( tmpStart == ULONG_MAX) // no children or no valid start for them
		tmpStart = 0;

	start = tmpStart;
	end = tmpEnd;
	confidence = maxConfidence;
}

string Container::attributesToString() {
	stringstream ss;
	string verbalStr;

	verbalStr 	= verbal ? "true" : "false";

	ss << "id=\"" << id << "\" ";
	ss << "start=\"" << start << "\" ";
	ss << "end=\"" << end << "\" ";
	ss << "confidence=\"" << confidence << "\" ";
	ss << "cost=\"" << cost << "\" ";

	if (tokens.compare(""))
		ss << "tokens=\"" << tokens << "\" ";

	if( medium.compare(""))
		ss << "medium=\"" << medium << "\" ";

	if( mode.compare(""))
		ss << "mode=\"" << mode << "\" ";

	if( process.compare(""))
		ss << "process=\"" << process << "\" ";

	if( lang.compare(""))
		ss << "lang=\"" << lang << "\" ";

	if( signal.compare(""))
		ss << "signal=\"" << signal << "\" ";

	if( source.compare(""))
		ss << "source=\"" << source << "\" ";

	if( function.compare(""))
		ss << "function=\"" << function << "\" ";

	if( dialog_turn.compare(""))
		ss << "dialog-turn=\"" << dialog_turn << "\" ";

	if( media_type.compare(""))
		ss << "media-type=\"" << media_type << "\" ";

	if( time_ref_uri.compare(""))
		ss << "time-ref-uri=\"" << time_ref_uri << "\" ";

	if( time_ref_anchor_point.compare(""))
		ss << "time-ref-anchor-point=\"" << time_ref_anchor_point << "\" ";

	if( signal_size!=0 )
		ss << "signal-size=\""<< signal_size <<"\" ";

	if( offset_to_start!=0 )
		ss << "offset-to-start=\""<< offset_to_start <<"\" ";

	if( grammarRef )
		ss << "grammar-ref=\""<< grammarRef->getId() <<"\" ";

	if( modelRef )
		ss << "model-ref=\""<< modelRef->getId() <<"\" ";

	ss << "verbal=\"" << verbalStr << "\" ";

	return ss.str();
}

string Container::childrenToString() {
	stringstream ss;
	vector<Container*>::iterator contIt;
	vector<Interpretation*>::iterator intIt;

	if( !interprets.empty() ) {
		for( intIt=interprets.begin(); intIt!=interprets.end(); intIt++) {
			ss << (*intIt)->toString();
		}
	}

	if( !nested.empty() ) {
		for( contIt=nested.begin(); contIt!=nested.end(); contIt++) {
			ss << (*contIt)->toString();
		}
	}

	return ss.str();
}
