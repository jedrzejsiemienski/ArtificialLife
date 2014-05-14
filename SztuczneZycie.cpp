//============================================================================
// Name        : SztuczneZycie.cpp// Author      : Jedrek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "interface/SDLInterface.h"
#include "worm/Worm.h"

using namespace std;

/*
1 - BrainOnePerceptron();
2 - BrainManyPerceptrons();
3 - BrainDummy();
4 - BrainRandom();
*/

void testJoints() {
	SDLInterface inteface;
	inteface.manuallyJoints();
}

void testSkeleton() {
	SDLInterface inteface;
	inteface.manuallySkeleton();
}

void testWorm() {
	Point target(0, 0);
	Worm * worm = new Worm(4, 400, 400, target.x, target.y);

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, &target, 100);
}

void testSavingToFile(){
	Worm * worm = new Worm(1, 400, 400, 20, 20);
	worm->saveToFile("test.txt");
}

void testLoadingFromFile(){
	Worm * worm = new Worm(1, "test.txt");

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, worm->getEndPoint(), 50);
}

int main(int argc, char *argv[]) {
	//testJoints();
	//testSkeleton();
	//testWorm();
	//testSavingToFile();
	testLoadingFromFile();

	return 0;
}

