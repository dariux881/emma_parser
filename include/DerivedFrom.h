/*
 * DerivedFrom.h
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#ifndef DERIVEDFROM_H_
#define DERIVEDFROM_H_

#include <string>
#include "Interpretation.h"

using namespace std;

class Interpretation;

class DerivedFrom {
public:
	DerivedFrom();
	virtual ~DerivedFrom();

	void setComposite(bool composite) { this->composite = composite; }
	void setResource(Interpretation* interRef) { this->resource = interRef; }
	void setResourceId(string interRefId);

	bool isComposite() { return composite; }
	Interpretation* getResource() { return resource; }
	string getResourceId() { return resourceId; }

	string	toString();

private:
	string 			resourceId;
	Interpretation* resource;
	bool			composite;
};

#endif /* DERIVEDFROM_H_ */
