/*
 * BrainManyPerceptrons.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef BRAINMANYPERCEPTRONS_H_
#define BRAINMANYPERCEPTRONS_H_

#include <stdlib.h>
#include <time.h>
#include "BaseBrain.h"
#include "../neuralNetwork/Perceptron.h"

class BrainManyPerceptrons : public BaseBrain {
public:
	BrainManyPerceptrons(int initVal = NeuronImpulsowy::USE_RANDOM_VALUE);
	virtual ~BrainManyPerceptrons();
	int ** stimulate(int b1, int b2, int a1, int a2, int a3);

	Genotype* getGenotype();
	void setGenotype(Genotype*);

	void saveToFile(string name);
	void loadFromFile(string name);

private:
	int perceptronsCount;
	Perceptron** perceptrons;

	void initPerceptrons(int);
	int * stimulateSinglePerceptron(int, int, int, int);
};

#endif /* BRAINMANYPERCEPTRONS_H_ */
