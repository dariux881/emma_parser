/*
 * Emma.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef EMMA_H_
#define EMMA_H_

#include "Container/Container.h"
#include "Derivation.h"

class Emma {
public:
	Emma();
	virtual ~Emma();

	void setContainer(Container* newCont) { container = newCont; }
	void setDerivation(Derivation* derivation) { this->derivation = derivation; }

	Container* getContainer() { return container; }
	Derivation* getDerivation() { return derivation; }

	vector<Interpretation*> getAllData();

	string toString();

private:
	Derivation*	derivation;
	Container* 	container;
};

#endif /* EMMA_H_ */
