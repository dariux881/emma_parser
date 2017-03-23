/*
 * Derivation.h
 *
 *  Created on: 22 ott 2015
 *      Author: dariux881
 */

#ifndef DERIVATION_H_
#define DERIVATION_H_

#include <vector>
#include "Container/Container.h"

using namespace std;

class Derivation {
public:
	Derivation();
	virtual ~Derivation();

	void addContainer( Container* newCont ) {
		if( newCont )
			conts.push_back(newCont);
	}

	void addInterpretation( Interpretation* inter) {
		if( inter )
			interprets.push_back(inter);
	}

	string 	toString();
	string	childrenToString();

private:
	vector<Container*> 		conts;
	vector<Interpretation*> interprets;
};

#endif /* DERIVATION_H_ */
