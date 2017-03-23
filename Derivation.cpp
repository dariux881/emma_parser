/*
 * Derivation.cpp
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#include "Derivation.h"
#include <sstream>

Derivation::Derivation() {
}

Derivation::~Derivation() {
}

string Derivation::toString() {
	stringstream ss;

	ss << "<derivation>" << endl;
	ss << childrenToString();
	ss << "</derivation>" << endl;

	return ss.str();
}

string Derivation::childrenToString() {
	stringstream ss;
	vector<Container*>::iterator contIt;
	vector<Interpretation*>::iterator intIt;

	if( !interprets.empty() ) {
		for( intIt=interprets.begin(); intIt!=interprets.end(); intIt++) {
			ss << (*intIt)->toString();
		}
	}

	if( !conts.empty() ) {
		for( contIt=conts.begin(); contIt!=conts.end(); contIt++) {
			ss << (*contIt)->toString();
		}
	}

	return ss.str();
}
