/*
 * Model.h
 *
 *  Created on: 21 ott 2015
 *      Author: dariux881
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <string>

using namespace std;

class Model {
public:
	Model();
	virtual ~Model();

	string getId() { return id; }
	string getUri() { return uri; }

	void setId(string id) { this->id = id; }
	void setUri(string uri) { this->uri = uri; }

private:
	string id, uri;
};

#endif /* MODEL_H_ */
