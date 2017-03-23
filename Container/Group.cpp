/*
 * Group.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Group.h"
#include <sstream>

Group::Group() {
	containerType = GROUP;
	start = 0;
	end = 0;
}

Group::~Group() {
}

void Group::addInterpretation_impl(Interpretation* newInt) {
	if( !newInt )
		return;

	interprets.push_back(newInt);
	finalizeCreation();
}

void Group::addNestedContainer_impl(Container* newCont) {
	if( !newCont )
		return;

	nested.push_back(newCont);
	finalizeCreation();
}

vector<Interpretation*> Group::getInterpretations_impl() {
	vector<Interpretation*> result, tmp;
	vector<Container*>::iterator it;

	result = interprets;
	for( it=nested.begin(); it!=nested.end(); it++) {
		tmp = (*it)->getInterpretations();
		result.insert(result.end(), tmp.begin(), tmp.end());
	}

	return result;
}

string Group::toString_impl() {
	stringstream ss;

	ss << "<group " << attributesToString() << ">" << endl;
	ss << childrenToString();
	ss <<"</group>" << endl;

	return ss.str();
}
