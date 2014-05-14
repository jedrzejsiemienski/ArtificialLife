/*
 * BrainManyPerceptrons.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainManyPerceptrons.h"

BrainManyPerceptrons::BrainManyPerceptrons() {
	srand (time(NULL));
	dataCount = 5;
	perceptronsCount = 5;
	perceptrons = new Perceptron*[perceptronsCount];
	initPerceptrons();
}

BrainManyPerceptrons::~BrainManyPerceptrons() {
	for(int i = 0; i < perceptronsCount; i++){
		delete perceptrons[i];
	}
	delete[] perceptrons;
}

int ** BrainManyPerceptrons::stimulate(int b1, int b2, int a1, int a2, int a3){
	int ** result = new int*[perceptronsCount];

	int i = 0;
	result[i] = stimulateSinglePerceptron(i, b1, b2, a1); i++;
	result[i] = stimulateSinglePerceptron(i, b1, b2, a1); i++;
	result[i] = stimulateSinglePerceptron(i, b1, b2, a1); i++;
	result[i] = stimulateSinglePerceptron(i, b1, b2, a1); i++;
	result[i] = stimulateSinglePerceptron(i, b1, b2, a1);

	return result;
}

int * BrainManyPerceptrons::stimulateSinglePerceptron(int perceptron, int x, int y, int z){
	int* result;
	int* inputs = new int[3];
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	result = perceptrons[perceptron]->stimulate(inputs);
	delete[] inputs;
	return result;
}

void BrainManyPerceptrons::initPerceptrons(){
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 3;
	neuronsAmount[1] = 5;
	neuronsAmount[2] = 2;

	int* givenRanges = new int[neuronsAmount[0]];
	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 80;
		givenBuckets[i] = 20;
	}

	for(int i=0; i < perceptronsCount; i++){
		perceptrons[i] = new Perceptron(layersAmount, neuronsAmount, givenRanges, givenBuckets);
	}

	delete[] neuronsAmount;
	delete[] givenRanges;
	delete[] givenBuckets;
}
