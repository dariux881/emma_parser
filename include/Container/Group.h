/*
 * Group.h
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#ifndef CONTAINER_GROUP_H_
#define CONTAINER_GROUP_H_

#include "../../config.h"
#include "Container.h"
#include "../Interpretation.h"

class Group : public Container {
public:
	EMMAPARSER_API Group();
	EMMAPARSER_API virtual ~Group();

	EMMAPARSER_API void addInterpretation(Interpretation* newInt) {
		this->addInterpretation_impl(newInt);
	}
	EMMAPARSER_API void addNestedContainer(Container* newCont) {
		this->addNestedContainer_impl(newCont);
	}
	EMMAPARSER_API vector<Interpretation*> getInterpretations() {
		return this->getInterpretations_impl();
	}
	EMMAPARSER_API string toString() {
		return this->toString_impl();
	}

protected:
	void addInterpretation_impl(Interpretation* newInt);
	void addNestedContainer_impl(Container* newCont);
	vector<Interpretation*> getInterpretations_impl();
	string toString_impl();
};

#endif /* CONTAINER_GROUP_H_ */
