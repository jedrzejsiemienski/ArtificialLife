/*
 * BrainOnePerceptron.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainOnePerceptron.h"


BrainOnePerceptron::BrainOnePerceptron() {
	srand (time(NULL));
	dataCount = 5;
	initPerceptron();
}

BrainOnePerceptron::~BrainOnePerceptron() {
	delete perceptron;
}

int ** BrainOnePerceptron::stimulate(int b1, int b2, int a1, int a2, int a3){
	int* rawResult;
	int* inputs = new int[dataCount];
	int i = 0;
	inputs[i] = b1; i++;
	inputs[i] = b2; i++;
	inputs[i] = a1; i++;
	inputs[i] = a2; i++;
	inputs[i] = a3;
	rawResult = perceptron->stimulate(inputs);
	delete[] inputs;

	int ** result = new int*[dataCount];
	int j = 0;
	for(i = 0; i < dataCount; i++){
		result[i] = new int[2];
		result[i][0] = rawResult[j++];
		result[i][1] = rawResult[j++];
	}
	return result;
}


void BrainOnePerceptron::initPerceptron(){
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 5;
	neuronsAmount[1] = 10; //to w sumie dyskusyjne
	neuronsAmount[2] = 10;

	int* givenRanges = new int[neuronsAmount[0]];
	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 80;
		givenBuckets[i] = 20;
	}

	perceptron = new Perceptron(layersAmount, neuronsAmount, givenRanges, givenBuckets);

	delete[] neuronsAmount;
	delete[] givenRanges;
	delete[] givenBuckets;
}
