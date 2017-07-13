/*
 * Derivation.h
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#ifndef DERIVATION_H_
#define DERIVATION_H_

#include "../config.h"
#include <vector>
#include "Container/Container.h"

using namespace std;

class Derivation {
public:
	EMMAPARSER_API Derivation();
	EMMAPARSER_API virtual ~Derivation();

	EMMAPARSER_API void addContainer( Container* newCont ) {
		if( newCont )
			this->conts.push_back(newCont);
	}

	EMMAPARSER_API void addInterpretation( Interpretation* inter) {
		if( inter )
			this->interprets.push_back(inter);
	}

	EMMAPARSER_API string 	toString();
	EMMAPARSER_API string	childrenToString();

private:
	vector<Container*> 		conts;
	vector<Interpretation*> interprets;
};

#endif /* DERIVATION_H_ */
