/*
 * OneOf.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_ONEOF_H_
#define CONTAINER_ONEOF_H_

#include "Container.h"
#include "../Interpretation.h"

enum DISJUNCTION_TYPE {UNSET, RECOGNITION, UNDERSTANDING, MULTI_DEVICE, MULTI_PROCESS};

class OneOf : public Container {
public:
	OneOf();
	virtual ~OneOf();

	void setMedium(string med);
	void setMode(string mode);
	void setDisjunctionType(DISJUNCTION_TYPE disjunctionType) { disjunction_type = disjunctionType; }

	vector<Interpretation*> getInterpretations() { return getInterpretations_impl(); }
	string 					toString() { return toString_impl(); }
	DISJUNCTION_TYPE 		getDisjunctionType() { return disjunction_type; }

	void addInterpretation(Interpretation* newInt) {
		addInterpretation_impl(newInt);
	}
	void addNestedContainer(Container* newCont) {
		addNestedContainer_impl(newCont);
	}
	string attributesToString();

protected:
	void addInterpretation_impl(Interpretation* newInt);
	void addNestedContainer_impl(Container* newCont);
	vector<Interpretation*> getInterpretations_impl();
	string toString_impl();

	DISJUNCTION_TYPE disjunction_type;
};

#endif /* CONTAINER_ONEOF_H_ */
