/*
 * Research.cpp
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#include "Research.h"


Research::Research() {
	// TODO Auto-generated constructor stub

}

Research::~Research() {
	// TODO Auto-generated destructor stub
}



void Research::saveToFile(string name){
	ofstream file;

	file.open(name.c_str());

	file << "1" << endl ;

	file.close();
}
