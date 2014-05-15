/*
 * Genotype.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef GENOTYPE_H_
#define GENOTYPE_H_

#include "../neuralNetwork/Perceptron.h"

class Genotype {
public:
	Genotype(Perceptron **, int);
	Genotype(const Genotype &);
	virtual ~Genotype();

	Genotype* crossWith(float, Genotype*); //pobiera mutanta v, mutuje go ze soba i zwraca u - osobnika probnego
	Genotype* mutateWith(float, Genotype*, Genotype*); //mutates current with 2 given

	Perceptron ** perceptrons;
	int perceptronsCount;

private:
	Genotype* substract(Genotype*);  //substract given genotype from current genotype
	Genotype* add(Genotype*);  //add given genotype to current genotype
	Genotype* multiply(float); //mutliplies everything from genotype by given number

	bool assertEqualStructure(Genotype*);

};

#endif /* GENOTYPE_H_ */
