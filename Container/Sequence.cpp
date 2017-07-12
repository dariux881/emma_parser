/*
 * Sequence.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Sequence.h"
#include <sstream>

Sequence::Sequence() {
	containerType = SEQUENCE_CONTAINER;
}

Sequence::~Sequence() {
}

void Sequence::addInterpretation_impl(Interpretation* newInt) {
	if( !newInt )
		return;

	interprets.push_back(newInt);
	finalizeCreation();
}

void Sequence::addNestedContainer_impl(Container* newCont) {
	if( !newCont )
		return;

	nested.push_back(newCont);
	finalizeCreation();
}

vector<Interpretation*> Sequence::getInterpretations_impl() {
	vector<Interpretation*> result, tmp;
	vector<Container*>::iterator it;

	result = interprets;
	for( it=nested.begin(); it!=nested.end(); it++) {
		tmp = (*it)->getInterpretations();
		result.insert(result.end(), tmp.begin(), tmp.end());
	}

	return result;
}

string Sequence::toString_impl() {
	stringstream ss;

	ss << "<sequence " << attributesToString() << ">" << endl;
	ss << childrenToString();
	ss <<"</sequence>" << endl;

	return ss.str();
}
