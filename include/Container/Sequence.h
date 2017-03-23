/*
 * Sequence.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_SEQUENCE_H_
#define CONTAINER_SEQUENCE_H_

#include "Container.h"
#include "../Interpretation.h"

class Sequence : public Container {
public:
	Sequence();
	virtual ~Sequence();

	void addInterpretation(Interpretation* newInt) {
		addInterpretation_impl(newInt);
	}
	void addNestedContainer(Container* newCont) {
		addNestedContainer_impl(newCont);
	}
	vector<Interpretation*> getInterpretations() {
		return getInterpretations_impl();
	}
	string toString() {
		return toString_impl();
	}


protected:
	void addInterpretation_impl(Interpretation* newInt);
	void addNestedContainer_impl(Container* newCont);
	vector<Interpretation*> getInterpretations_impl();
	string toString_impl();
};

#endif /* CONTAINER_SEQUENCE_H_ */
