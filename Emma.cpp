/*
 * Emma.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Emma.h"
#include <sstream>

Emma::Emma() {
	container 	= NULL;
	derivation 	= NULL;
}

Emma::~Emma() {

}

string Emma::toString() {
	stringstream ss;

	ss << "<emma>" << endl;

	if( this->derivation )
		ss << this->derivation->toString();
	if(this->container )
		ss << this->container->toString();

	ss << "</emma>";

	return ss.str();
}

vector<Interpretation*> Emma::getAllData() {
	vector<Interpretation*> result;
	vector<Container*>::iterator it;

	if(this->container )
		result = this->container->getInterpretations();

	return result;
}

