/*
 * main.cpp
 *
 *  Created on: 15 ott 2015
 *      Author: dariux881
 */

#include "Emma.h"
#include "EmmaParser.h"
#include <iostream>

int main() {
	Emma *node, *node2;
	EmmaParser ep;
	string result;

	node = ep.parseDocument("/Users/dariux881/test2.xml");

	if( !node ) {
		cout << "error parsing emma node"<< endl;
		return -1;
	}

	cout << "print!" << endl;
	result = node->toString();
	cout << "primo parser" << endl;
	cout << result << endl;

	node2 = ep.parseNode(result);

	cout << endl << "secondo parser" << endl;
	cout << node2->toString() << endl;
}


