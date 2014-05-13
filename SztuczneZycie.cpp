//============================================================================
// Name        : SztuczneZycie.cpp// Author      : Jedrek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "interface/SDLInterface.h"

using namespace std;


void testJoints() {
	SDLInterface inteface;
	inteface.manuallyJoints();
}

void testSkeleton() {
	SDLInterface inteface;
	inteface.manuallySkeleton();
}


int main(int argc, char *argv[]) {
	//testJoints();
	testSkeleton();

	return 0;
}

