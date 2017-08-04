/*
 * DerivedFrom.h
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#ifndef DERIVEDFROM_H_
#define DERIVEDFROM_H_

#include "config.h"
#include <string>
#include "Interpretation.h"

using namespace std;

class Interpretation;

class DerivedFrom {
public:
	DerivedFrom();
	virtual ~DerivedFrom();

	EMMAPARSER_API void setComposite(bool composite) { this->composite = composite; }
	EMMAPARSER_API void setResource(Interpretation* interRef) { this->resource = interRef; }
	EMMAPARSER_API void setResourceId(string interRefId);

	EMMAPARSER_API bool isComposite() { return this->composite; }
	EMMAPARSER_API Interpretation* getResource() { return this->resource; }
	EMMAPARSER_API string getResourceId() { return this->resourceId; }

	EMMAPARSER_API string	toString();

private:
	string 			resourceId;
	Interpretation* resource;
	bool			composite;
};

#endif /* DERIVEDFROM_H_ */
