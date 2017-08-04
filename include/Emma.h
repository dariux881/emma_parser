/*
 * Emma.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef EMMA_H_
#define EMMA_H_

#include "config.h"
#include "Container/Container.h"
#include "Derivation.h"

class Emma {
public:
	EMMAPARSER_API Emma();
	EMMAPARSER_API ~Emma();

	EMMAPARSER_API void setContainer(Container* newCont) { this->container = newCont; }
	EMMAPARSER_API void setDerivation(Derivation* derivation) { this->derivation = derivation; }

	EMMAPARSER_API Container* getContainer() { return this->container; }
	EMMAPARSER_API Derivation* getDerivation() { return this->derivation; }

	EMMAPARSER_API vector<Interpretation*> getAllData();

	EMMAPARSER_API string toString();

private:
	Derivation*	derivation;
	Container* 	container;
};

#endif /* EMMA_H_ */
