//============================================================================
// Name        : SztuczneZycie.cpp// Author      : Jedrek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "neuralNetwork/NeuronImpulsowy.h"
#include "neuralNetwork/KonwerterDanych.h"
#include "neuralNetwork/Perceptron.h"
#include "interfaces/SDLInterface.h"
#include "evolutionAlgorithms/Chromosom.h"
#include "evolutionAlgorithms/ChromosomesCrosser.h"
#include "evolutionAlgorithms/Environment.h"
#include "worms/Joint.h"
#include "worms/WormBase.h"
#include "worms/Worm.h"
#include <iostream>
#include <memory>

using namespace std;

//typedef boost::shared_ptr<gate> gate_ptr;

/*
void testDestruktory(){

	list<WormBase*> population;
	list<WormBase*>::iterator currentWorm;

	int index1 = 0, index2 = 0;
	for(int j = 1; j < 10000; j++){
		index1++;
		for(int i = 0; i < 1000; i++){
			Point * a = new Point(10,10);
			WormBase * w1 = new Worm(a, a);
			WormBase * w2 = new Worm(a, a);
			//Worm * w3 = new Worm(a);
			delete a;
			WormBase* w3 = w1->cross(w2);
			population.push_back(w1);
			population.push_back(w2);
			population.push_back(w3);
		}

		while(!population.empty()){
			index2++;
			cout << index1 << " " << index2 << endl;

			WormBase * toErase;
			currentWorm = population.begin();
		    toErase = *currentWorm;
		    toErase->mutate(0.5, 0.5, 0.5);
		    for(int k = 0; k < 100; k++){
		    	toErase->move();
		    }
		    delete toErase;
		    population.erase(currentWorm);
		}
	}
*/
/*
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 3;
	neuronsAmount[1] = 3;
	neuronsAmount[2] = 2;

	int* givenRanges = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 360;
	}

	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenBuckets[i] = 10;
	}

	list<Perceptron*> population;
	list<Perceptron*>::iterator currentWorm;

	int index1 = 0, index2 = 0;
	for(int j = 1; j < 10000; j++){
		index1++;
		for(int i = 0; i < 1000; i++){
			population.push_back(new Perceptron(layersAmount, neuronsAmount, givenRanges, givenBuckets));
		}

		while(!population.empty()){
			index2++;
			cout << index1 << " " << index2 << endl;

			Perceptron * toErase;
			currentWorm = population.begin();
		    toErase = *currentWorm;
		    population.erase(currentWorm);
		    delete toErase;
		}
	}
*/

	/*
	float timeBase = 0.1;
	list<NeuronImpulsowy*> population;
	list<NeuronImpulsowy*>::iterator currentWorm;

	int index1 = 0, index2 = 0;
	for(int j = 1; j < 10000; j++){
		index1++;
		for(int i = 0; i < 1000; i++){
			population.push_back(new NeuronImpulsowy(10, timeBase));
		}

		while(!population.empty()){
			index2++;
			cout << index1 << " " << index2 << endl;

			NeuronImpulsowy * toErase;
			currentWorm = population.begin();
		    toErase = *currentWorm;
		    population.erase(currentWorm);
		    delete toErase;
		}
	}
*/

	/*
	float timeBase = 0.1;
	NeuronImpulsowy n1(10, timeBase);
	NeuronImpulsowy n2(10, timeBase);

	list<Chromosom*> population;
	list<Chromosom*>::iterator currentWorm;

	int index1 = 0, index2 = 0;
	for(int j = 1; j < 10000; j++){
		index1++;
		for(int i = 0; i < 1000; i++){
			Chromosom * c1 = n1.getChromosome();
			Chromosom * c2 = n2.getChromosome();
			Chromosom * c3 = ChromosomesCrosser::cross(c1, c2, crossingTypes(MULTI_POINT), 1);
			ChromosomesCrosser::mutate(c3, 0.3, 0.3);

			population.push_back(c3);

			delete c1;
			delete c2;
			//population.push_back(new Chromosom());
		}

		while(!population.empty()){
			index2++;
			cout << index1 << " " << index2 << endl;

			Chromosom * toErase;
			currentWorm = population.begin();
		    toErase = *currentWorm;
		    population.erase(currentWorm);
		    delete toErase;
		}
	}
	*/
//}

/*
void testKonwertera(){
	int ilosc = 3;
	KonwerterDanych ** konwertery = new KonwerterDanych*[ilosc];
	for(int i = 0; i < ilosc; i++){
		konwertery[i] = new KonwerterDanych(10, 360);
	}

	int* result;
	for(int i = 0; i < ilosc; i++){
		result = konwertery[i]->convert(36);
		cout << "Wynik " << i << endl;
		for(int j = 0; j < konwertery[i]->getBucketsNumber(); j++){
			cout << result[j] << " ";
		}
		cout << endl;
	}
}

void testNeuronuImpulsowego(){
	int g = 3;
	float T = 0.01;

	NeuronImpulsowy ip(g, T);

	int* x = new int[g];

	cout << "------- krok 1 -------" << endl;
	x[0] = 0;
	x[1] = 1;
	x[2] = 1;
	ip.compute(x);

	cout << "------- krok 2 -------" << endl;
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	ip.compute(x);

	cout << "------- krok 3 -------" << endl;
	x[0] = 0;
	x[1] = 1;
	x[2] = 0;
	ip.compute(x);
}

void testPerceptron() {
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 3;
	neuronsAmount[1] = 3;
	neuronsAmount[2] = 2;

	int* givenRanges = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 360;
	}

	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenBuckets[i] = 10;
	}

	//Perceptron(int givenLayersAmount, int* neuronsAmounts, int* givenRanges, int* givenBuckets)
	Perceptron p(layersAmount, neuronsAmount, givenRanges, givenBuckets);

	p.print();

	int* inputs = new int[neuronsAmount[0]];
	inputs[0] = 45;
	inputs[1] = 135;
	inputs[2] = 225;

	for (int i = 0; i < 10; i++){
		cout << "Petla " << i << endl;
		p.stimulate(inputs);
		cout << endl;

		inputs[0]+=2;
		inputs[1]+=3;
		inputs[2]+=4;
	}
}

/*
void testChromosome(){
	float timeBase = 0.1;
	NeuronImpulsowy n1(10, timeBase);
	NeuronImpulsowy n2(10, timeBase);
	n1.print();
	n2.print();

	Chromosom * c3;
	Chromosom * c1 = n1.getChromosome();
	Chromosom * c2 = n2.getChromosome();
	c3 = ChromosomesCrosser::cross(c1, c2, crossingTypes(MULTI_POINT), 1);

	NeuronImpulsowy n3(timeBase);
	n3.setChromosome(c3);

	n3.print();
}
*/


void testJoint() {
	SDLInterface inteface;
	inteface.manuallyWorm();
}

/*
void testMutatingWorms(int interval){
	Point start(500,300);

	Worm * worm = new Worm(&start, &start);
	worm->mutate(0.8, 0.5, 0.5);

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, new Point(0,0), interval);
}

void testCrossingWorms(){
	Point start(500,300);
	Point target(700, 600);

	WormBase * worm1 = new Worm(&start, &target);
	WormBase * worm2 = new Worm(&start, &target);
	WormBase * worm3 = worm1->cross(worm2);

	SDLInterface inteface;
	inteface.displayWorm(worm3, 200, new Point(0,0));

}

void testGettingDistance(){
	//Point start(100, 500);
	//Point target(1000, 10);

	Point start(50, 50);
	Point target(700, 600);

	Worm * worm1 = new Worm(&start, &target);

	int steps = 300;
	cout << worm1->getDistanceAfterNMoves(steps, &target, true);

	SDLInterface inteface;
	inteface.displayWorm(worm1, steps, &target, 10);

}



void testShowingFromFile(string name){
	Point p1(0,0);
	Point p2(0,0);
	Worm * worm = new Worm(&p1, &p2);
	worm->loadFromFile(name);
	Point target(worm->getEndPoint()->x, worm->getEndPoint()->y);

	SDLInterface inteface;
	inteface.displayWorm(worm, 300, &target, 20);

	cout << worm->getCurrentDistance(&target) << endl;
}

void testEnvironment(char * cnfFile) {
	ifstream inFile;
	string line;

	inFile.open(cnfFile);

	getline(inFile, line);
	istringstream iss1(line);
	vector<string> point1;
	copy(istream_iterator<string>(iss1), istream_iterator<string>(), back_inserter<vector<string> >(point1));
	double x1 = ::atof(point1[0].c_str());
	double y1 = ::atof(point1[1].c_str());
	Point start(x1, y1);

	getline(inFile, line);
	istringstream iss2(line);
	vector<string> point2;
	copy(istream_iterator<string>(iss2), istream_iterator<string>(), back_inserter<vector<string> >(point2));
	double x2 = ::atof(point2[0].c_str());
	double y2 = ::atof(point2[1].c_str());
	Point target(x2, y2);

	getline(inFile, line);
	int movementSteps = ::atof(line.c_str());

	getline(inFile, line);
	float mutationP = ::atof(line.c_str());

	getline(inFile, line);
	float mutationF = ::atof(line.c_str());

	getline(inFile, line);
	float mutationFt = ::atof(line.c_str());

	getline(inFile, line);
	int populationSize = ::atof(line.c_str());

	getline(inFile, line);
	int cycles = ::atof(line.c_str());


	Environment env(start, target, populationSize, mutationP, mutationF, mutationFt, movementSteps);

	ostringstream ss1, ss2;
	ss1 << "out_"  << mutationP*10.0 << "_" << mutationF*10.0 << "_" << mutationFt*10.0 << "_" << populationSize << "_" << cycles << ".txt";
	ss2 << "worm_" << mutationP*10.0 << "_" << mutationF*10.0 << "_" << mutationFt*10.0 << "_" << populationSize << "_" << cycles << ".txt";

	ofstream file;
	file.open(ss1.str().c_str());
	float bestDistance;
	for(int i = 0; i < cycles; i++){
		bestDistance = env.evolutionCycle();
		file << i << ";" << bestDistance << endl;
	}
	file.close();

	WormBase * worm;
	worm = env.getBestWorm();

	worm->saveToFile(ss2.str());
}



void testSavingToFile(){
	WormBase * worm = new Worm(new Point(100,100), new Point(100,100));
	worm->saveToFile("worm1.txt");

	Point p1(0,0);
	Point p2(0,0);
	WormBase * worm2 = new Worm(&p1, &p2);
	worm2->loadFromFile("worm1.txt");
	worm2->saveToFile("worm2.txt");
}
*/

int main(int argc, char *argv[]) {
	srand (time(NULL));
	//testNeuronuImpulsowego();
	//testKonwertera();
	//testPerceptron();
	//testChromosome();

	testJoint();
	//testMutatingWorms(40);

	//testCrossingWorms();

	//testDestruktory();
	//testGettingDistance();
	//testSavingToFile();

	//testEnvironment(40);

	/*
	for (int n = 1; n < argc; n++){
		if(argv[n][1] == 'm'){
			testJoint();
			return 0;
		} else if(argv[n][1] == 'w'){
			testShowingFromFile(argv[n+1]);
			return 0;
		} else if(argv[n][1] == 'h'){
			testEnvironment(argv[n+1]);
			return 0;
		}
	}
	*/

	//testShowingFromFile("worm_8_2_3_70_70.txt");

	//testShowingFromFile("worm_8_2_3_100_50.txt");

	//testShowingFromFile("worm_8_7_7_100_50.txt");

	return 0;
}

