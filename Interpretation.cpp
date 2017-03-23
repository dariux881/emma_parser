/*
 * Interpretation.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Interpretation.h"
#include <sstream>

Interpretation::Interpretation() {
	confidence = 1.0f;
	cost = 0.0f;
	start = end = offset_to_start = signal_size = 0;
	parent = NULL;
	no_input = uninterpreted = verbal = false;
	grammarRef = NULL;
	modelRef = NULL;
}

Interpretation::~Interpretation() {
}

void Interpretation::addDerivedFrom(DerivedFrom* derivedFrom) {
	if( derivedFrom )
		this->derivedFrom.push_back( derivedFrom );
}

/**
 * This method set the start for an interpretation
 */
void Interpretation::setStart(unsigned long long start) {
	this->start = start;

	if( parent ) { // valid parent
		if( parent->getStart()==0 ) // unset parent start
			parent->setStart(start);
		else // set parent start. I just update it
			parent->setStart( min(parent->getStart(), start) );
	}
}

/**
 * This method set the duration of an interpretation
 */
void Interpretation::setDuration(unsigned long long dur) {

	if( end==0 ) {
		end = start+dur;
	}
	else if( start==0 && ((long)end-(long)dur)>=0)
		start = end-dur;

	if( parent )
		parent->setDuration(dur);
}

/**
 * This method set the end for an interpretation
 */
void Interpretation::setEnd(unsigned long long end) {
	this->end = end;

	if( parent ) { // valid parent
		if( parent->getEnd()==0 ) // unset parent end
			parent->setEnd(end);
		else // set parent end. I just update it
			parent->setEnd( max(parent->getEnd(), end) );
	}
}

string Interpretation::toString() {
	stringstream ss;
	vector<DerivedFrom*>::iterator it;

	ss << "<interpretation "
			<< attributesToString()
			<< ">" << endl;

	for( it=derivedFrom.begin(); it!=derivedFrom.end(); it++) {
		ss << (*it)->toString();
	}

	ss <<"</interpretation>" << endl;

	return ss.str();
}

string Interpretation::attributesToString() {
	stringstream ss;
	string noInputStr, uninStr, verbalStr;

	noInputStr 	= no_input ? "true" : "false";
	uninStr 	= uninterpreted ? "true" : "false";
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

	ss << "no-input=\"" << noInputStr << "\" "
		<< "uninterpreted=\"" << uninStr << "\" "
		<< "verbal=\"" << verbalStr << "\" ";

	return ss.str();
}
