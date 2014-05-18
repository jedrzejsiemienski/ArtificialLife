/*
 * Test.cpp
 *
 *  Created on: 18 maj 2014
 *      Author: jedrek
 */

#include "Test.h"

/*
1 - BrainOnePerceptron();
2 - BrainManyPerceptrons();
3 - BrainDummy();
4 - BrainRandom();
*/

void Test::testJoints() {
	SDLInterface inteface;
	inteface.manuallyJoints();
}

void Test::testSkeleton() {
	SDLInterface inteface;
	inteface.manuallySkeleton();
}

void Test::testWorm() {
	Point target(0, 0);
	Worm * worm = new Worm(4, 400, 400, target.x, target.y);

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, &target, 100);
}

void Test::testSavingToFile(){
	Worm * worm = new Worm(2, 400, 400, 20, 20, 1);
	worm->saveToFile("test3.txt");
}

void Test::testLoadingFromFile(){
	Worm * worm = new Worm(2, "test3.txt");

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, worm->getEndPoint(), 50);
}


void Test::performTests(){
	testJoints();
	//testSkeleton();
	//testWorm();
	//testSavingToFile();
	//testLoadingFromFile();
}
