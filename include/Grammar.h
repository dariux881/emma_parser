/*
 * Grammar.h
 *
 *  Created on: 21 ott 2015
 *      Author: dariux881
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <string>

using namespace std;

class Grammar {
public:
	Grammar();
	virtual ~Grammar();

	string getId() { return id; }
	string getUri() { return uri; }

	void setId(string id) { this->id = id; }
	void setUri(string uri) { this->uri = uri; }

private:
	string id, uri;
};

#endif /* GRAMMAR_H_ */
