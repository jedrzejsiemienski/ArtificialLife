/*
 * BrainOnePerceptron.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef BRAINONEPERCEPTRON_H_
#define BRAINONEPERCEPTRON_H_

#include "BaseBrain.h"
#include "../neuralNetwork/Perceptron.h"

using namespace std;

class BrainOnePerceptron : public BaseBrain{
public:
	BrainOnePerceptron();
	virtual ~BrainOnePerceptron();
	int ** stimulate(int b1, int b2, int a1, int a2, int a3);

	Genotype* getGenotype();
	void setGenotype(Genotype*);

	void saveToFile(string name);
	void loadFromFile(string name);

private:
	Perceptron* perceptron;
	void initPerceptron();
};

#endif /* BRAINONEPERCEPTRON_H_ */
