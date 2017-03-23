/*
 * Utils.h
 *
 *  Created on: 19 ott 2015
 *      Author: dariux881
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <stdlib.h>
#include <string>

using namespace std;

class Utils {
public:
	Utils();
	virtual ~Utils();

	template<typename T>
	static inline T stringToNumber(string);
};

#include "Utils_inline.inl"

#endif /* UTILS_UTILS_H_ */
