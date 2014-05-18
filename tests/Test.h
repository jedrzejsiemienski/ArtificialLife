/*
 * Test.h
 *
 *  Created on: 18 maj 2014
 *      Author: jedrek
 */

#ifndef TEST_H_
#define TEST_H_

#include "../interface/SDLInterface.h"
#include "../worm/Worm.h"

class Test {
public:
	Test(){};
	virtual ~Test(){};

	void performTests();

private:
	void testJoints();
	void testSkeleton();
	void testWorm();
	void testSavingToFile();
	void testLoadingFromFile();
};

#endif /* TEST_H_ */
