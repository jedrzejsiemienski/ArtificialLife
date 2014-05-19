//============================================================================
// Name        : SztuczneZycie.cpp// Author      : Jedrek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "tests/Test.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(NULL));

	Test tests;
	tests.performTests();

	return 0;
}

