/*
 * OneOf.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "OneOf.h"
#include <sstream>

OneOf::OneOf() {
	containerType = ONE_OF;
	disjunction_type = UNSET;
}

OneOf::~OneOf() {
}

/**
 * According to the Emma standard, a one-of container could maintain a medium for all
 * its interpretations
 */
void OneOf::setMedium(string med) {
	vector<Interpretation*>::iterator it;

	if( !med.compare("") )
		return;

	for( it=interprets.begin(); it!=interprets.end(); it++ ) {
		(*it)->setMedium(med);
	}
}

/**
 * According to the Emma standard, a one-of container could maintain a mode for all
 * its interpretations
 */
void OneOf::setMode(string mode) {
	vector<Interpretation*>::iterator it;

	if( !mode.compare("") )
		return;

	for( it=interprets.begin(); it!=interprets.end(); it++ ) {
		(*it)->setMode(mode);
	}
}

void OneOf::addInterpretation_impl(Interpretation* newInt) {
	vector<Interpretation*>::iterator it;

	if( !newInt )
		return;

	it = interprets.begin();
	while(it!=interprets.end() && (*it)->getConfidence() > newInt->getConfidence()) {
		it++;
	}

	if( it==interprets.end() )
		interprets.push_back(newInt);
	else
		interprets.insert(it, newInt);

	finalizeCreation();
}

/**
 * This method inserts a new container maintaining a confidence order.
 */
void OneOf::addNestedContainer_impl(Container* newCont) {
	vector<Container*>::iterator it;

	if( !newCont )
		return;

	it = nested.begin();
	if( it==nested.end() )
		nested.push_back(newCont);
	else {
		while( (*it)->getConfidence() >
				newCont->getConfidence() ) {
			it++;
		}

		nested.insert(it, newCont);
	}

	finalizeCreation();
}

/**
 * This method return a vector with just one interpretation.
 */
vector<Interpretation*> OneOf::getInterpretations_impl() {
	vector<Interpretation*> 			result, tmp;
	vector<Interpretation*>::iterator	it;
	vector<Container*>::iterator		conIt;
	Interpretation* 	best;
	float				bestConf;
	bool				bestFromNested;

	bestConf = 0;
	bestFromNested = true;

	// I search the best child from nested containers
	for( conIt=nested.begin(); conIt!=nested.end(); conIt++) {
		if( (*conIt)->getConfidence() <= bestConf )
			continue;

		bestConf = (*conIt)->getConfidence();
		tmp = (*conIt)->getInterpretations();
	}

	// I search the best interpretations among children
	for( it=interprets.begin(); it!=interprets.end(); it++) {
		if( (*it)->getConfidence() > bestConf ) {
			bestConf = (*it)->getConfidence();
			best = *it;
			bestFromNested = false;
		}
	}

	if( !bestFromNested ) {
		result.push_back(best);
	}
	else {
		result.insert(result.end(), tmp.begin(), tmp.end());
	}

	return result;
}

/**
 * translates a one-of object in a string
 */
string OneOf::toString_impl() {
	stringstream ss;

	ss << "<one-of " << attributesToString() << ">" << endl;
	ss << childrenToString();
	ss <<"</one-of>" << endl;

	return ss.str();
}

/**
 * reports as string all attributes specific to one-of node
 */
string OneOf::attributesToString() {
	stringstream ss;

	ss << Container::attributesToString();

	if( disjunction_type != UNSET )
		ss << "disjunction-type=\""<< disjunction_type <<"\" ";

	return ss.str();
}
