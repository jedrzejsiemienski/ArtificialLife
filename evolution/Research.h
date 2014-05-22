/*
 * Research.h
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#ifndef RESEARCH_H_
#define RESEARCH_H_

#include <fstream>
#include <iterator>
#include <string>

using namespace std;

class Research {
public:
	Research();
	virtual ~Research();

private:
	void saveToFile(string);
};

#endif /* RESEARCH_H_ */
