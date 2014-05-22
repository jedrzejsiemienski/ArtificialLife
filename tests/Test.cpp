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
	Worm * worm = new Worm(2, "result.txt");

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, worm->getEndPoint(), 50);
}

void Test::testGenotypeOperations(int type){
	//type 2;
	Worm * worm1 = new Worm(type, 400, 400, 20, 20, 2);
	worm1->saveToFile("base1Type2.txt");
	Genotype * g1 = worm1->getBrain()->getGenotype();

	Worm * worm2 = new Worm(type, 400, 400, 20, 20, 1);
	worm2->saveToFile("base2Type2.txt");
	Genotype * g2 = worm2->getBrain()->getGenotype();

	//Genotype* substract(Genotype*);
//	Worm * wormSub = new Worm(2, 400, 400, 20, 20, g1->substract(g2));
//	wormSub->saveToFile("subType2.txt");
	Worm * wormSub = new Worm(type, 400, 400, 20, 20);
	BaseBrain * brainSub = wormSub->getBrain();
	brainSub->setGenotype(g1->substract(g2));
	wormSub->saveToFile("subType2.txt");

	//Genotype* add(Genotype*);
	Worm * wormAdd = new Worm(type, 400, 400, 20, 20);
	BaseBrain * brainAdd = wormAdd->getBrain();
	brainAdd->setGenotype(g1->add(g2));
	wormAdd->saveToFile("addType2.txt");

	//Genotype* multiply(float); //mutliplies everything from genotype by given number
	Worm * wormMult = new Worm(type, 400, 400, 20, 20);
	BaseBrain * brainMult = wormMult->getBrain();
	brainMult->setGenotype(g1->multiply(2.0));
	wormMult->saveToFile("multType2.txt");

	//Genotype* crossWith(float cr, Genotype* x)
	Worm * wormCross = new Worm(type, 400, 400, 20, 20);
	BaseBrain * brainCross = wormCross->getBrain();
	brainCross->setGenotype(g1->crossWith(0.5f, g2));
	wormCross->saveToFile("crossType2.txt");

	//Genotype* mutateWith(float f, Genotype* x1, Genotype* x2);
	Worm * wormMutate = new Worm(type, 400, 400, 20, 20);
	BaseBrain * brainMutate = wormMutate->getBrain();
	Genotype* g3 = brainSub->getGenotype();
	brainMutate->setGenotype(g3->mutateWith(0.5f, g1, g2));
	wormMutate->saveToFile("mutateType2.txt");

	delete worm1;
	delete worm2;
	delete wormSub;
	delete wormAdd;
	delete wormMult;
	delete wormCross;
	delete wormMutate;
	delete g1;
	delete g2;
	delete g3;
}

void Test::testWormToAndFromGenotype(int type){
	Worm * worm1 = new Worm(type, 400, 400, 20, 20);
	worm1->saveToFile("g1.txt");

	Worm * worm2 = new Worm(type, 400, 400, 20, 20, worm1->getBrain()->getGenotype());
	worm2->saveToFile("g2.txt");

	Worm * worm3 = new Worm(type, 400, 400, 20, 20, worm2->getBrain()->getGenotype());
	worm3->saveToFile("g3.txt");

	delete worm1;
	delete worm2;
	delete worm3;
}

void Test::testMemoryLeaks(){
	for(float i = 0; i < 100000000.0f; i++){
		//skeleton
		Skeleton * skeleton = new Skeleton(1.0f, 1.0f);
		delete skeleton;

		//brain
		BaseBrain * brain = new BrainOnePerceptron();
		delete brain;
		BaseBrain * brain2 = new BrainManyPerceptrons();
		delete brain2;

		//worm
		Worm * worm1 = new Worm(1, 400, 400, 20, 20);
		Genotype * g1 = worm1->getBrain()->getGenotype();

		Worm * worm2 = new Worm(2, 400, 400, 20, 20);
		Genotype * g2 = worm2->getBrain()->getGenotype();

		delete g1;
		delete worm1;
		delete g2;
		delete worm2;

		testGenotypeOperations(1);
		testGenotypeOperations();

		testWormToAndFromGenotype(1);
		testWormToAndFromGenotype();
	}
}

void Test::testMovingWorm(){
	Point target(0, 0);
	Worm * worm = new Worm(1, 400, 400, target.x, target.y, 0.4);

	cout << worm->getCurrentDistanceToTarget() << endl;
	cout << worm->getDistanceAfterNMoves(1000) << endl;
	cout << worm->getCurrentDistanceToTarget() << endl;
	cout << worm->getDistanceAfterNMoves(1000) << endl;

	SDLInterface inteface;
	//inteface.displayWorm(worm, 300, &target, 100);
	inteface.displayWormStatic(worm);

	//delete worm;
}

void Test::testEvolutionaryAlgorithm(){
	int type = 2;
	Point start(100.0f, 300.0f);
	Point end(800.0f, 500.0f);
	Environment env(
		start,	//start
		end,	//target
		type,	//typ
		50,	//populacja startowa
		0.7,	//f
		0.5,	//cr
		100		//movement steps
	);

	env.epochs(10);
	Worm * worm = env.getBestWorm();
	worm->saveToFile("result.txt");

	SDLInterface inteface;
	inteface.displayWorm(worm, 100, &end, 50);

	env.clear();
}

void Test::testResearch(){
	ResearchEngine engine;
	engine.doPlannedResearches();
}

void Test::performTests(){
	//testJoints();
	//testSkeleton();
	//testWorm();
	//testSavingToFile();
	//testLoadingFromFile();
	//testGenotypeOperations(1);
	//testWormToAndFromGenotype();
	//testMemoryLeaks();
	//testMovingWorm();
	//testEvolutionaryAlgorithm();
	testResearch();
}
