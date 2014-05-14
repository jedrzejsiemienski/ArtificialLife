/*
 * BrainManyPerceptrons.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainManyPerceptrons.h"

BrainManyPerceptrons::BrainManyPerceptrons() : BaseBrain() {
	srand (time(NULL));
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
	result[i] = stimulateSinglePerceptron(i, b1, a1, b2); i++; //b1
	result[i] = stimulateSinglePerceptron(i, b1, a1, b2); i++; //a1
	result[i] = stimulateSinglePerceptron(i, a1, a2, a3); i++; //a2
	result[i] = stimulateSinglePerceptron(i, b1, a3, b2); i++; //a3
	result[i] = stimulateSinglePerceptron(i, b1, a3, b2);      //b2

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

void BrainManyPerceptrons::saveToFile(string name){

}

void BrainManyPerceptrons::loadFromFile(string name){

}
