/*
 * OneOf.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_ONEOF_H_
#define CONTAINER_ONEOF_H_

#include "../config.h"
#include "Container.h"
#include "../Interpretation.h"

enum DISJUNCTION_TYPE {UNSET, RECOGNITION, UNDERSTANDING, MULTI_DEVICE, MULTI_PROCESS};

using namespace std;

class OneOf : public Container {
public:
	EMMAPARSER_API OneOf();
	EMMAPARSER_API virtual ~OneOf();

	EMMAPARSER_API void setMedium(string med);
	EMMAPARSER_API void setMode(string mode);
	EMMAPARSER_API void setDisjunctionType(DISJUNCTION_TYPE disjunctionType) { this->disjunction_type = disjunctionType; }

	EMMAPARSER_API vector<Interpretation*> getInterpretations() { return this->getInterpretations_impl(); }
	EMMAPARSER_API string 					toString() { return this->toString_impl(); }
	EMMAPARSER_API DISJUNCTION_TYPE 		getDisjunctionType() { return this->disjunction_type; }

	EMMAPARSER_API void addInterpretation(Interpretation* newInt) {
		this->addInterpretation_impl(newInt);
	}
	EMMAPARSER_API void addNestedContainer(Container* newCont) {
		this->addNestedContainer_impl(newCont);
	}
	EMMAPARSER_API string attributesToString() {
		return attributesToString_impl();
	}

protected:
	DISJUNCTION_TYPE disjunction_type;

	void addInterpretation_impl(Interpretation* newInt);
	void addNestedContainer_impl(Container* newCont);
	vector<Interpretation*> getInterpretations_impl();
	string toString_impl();
	string attributesToString_impl();
};

#endif /* CONTAINER_ONEOF_H_ */
