//============================================================================
// Name        : SztuczneZycie.cpp// Author      : Jedrek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "interface/SDLInterface.h"
#include "worm/Worm.h"

using namespace std;


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
	Worm * worm = new Worm(1, 400, 400, target.x, target.y);

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, &target, 100);
}


int main(int argc, char *argv[]) {
	//testJoints();
	//testSkeleton();
	testWorm();

	return 0;
}

