/*
 * DerivedFrom.cpp
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#include "DerivedFrom.h"
#include <iostream>
#include <sstream>

DerivedFrom::DerivedFrom() {
	resource = NULL;
	composite = false;
}

DerivedFrom::~DerivedFrom() {
}

void DerivedFrom::setResourceId(string interRefId) {
	this->resourceId = interRefId;

	if( resourceId.find('#', 0)!=string::npos ) {
		resourceId.erase(0,1);
	}
}

string DerivedFrom::toString() {
	stringstream ss;
	string	resId, comp;

	if( resource )
		resId = resource->getId();

	comp = composite? "true" : "false";

	ss << "<derived-from "
			<< "resource=\"#" << resId << "\" "
			<< "composite=\"" << comp << "\" "
			<< "/>" << endl;

	return ss.str();
}
