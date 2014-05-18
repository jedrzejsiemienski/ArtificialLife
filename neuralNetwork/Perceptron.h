/*
 * Perceptron.h
 *
 *  Created on: 19 gru 2013
 *      Author: jedrek
 */

#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_

#include "KonwerterDanych.h"
#include "NeuronImpulsowy.h"
#include <iostream>
#include <vector>

typedef std::vector<NeuronImpulsowy*> WarstwaNeuronow;
typedef std::vector<WarstwaNeuronow*> Warstwy;
typedef std::vector<KonwerterDanych*> WarstwaKonwerterow;

class Perceptron {
public:
	Perceptron(int, int*, int*, int*, int initVal = NeuronImpulsowy::USE_RANDOM_VALUE);
	Perceptron(const Perceptron &);
	~Perceptron();
	int * stimulate(int*);

	int getTotalAmountOfNeurons();
	Chromosom ** getChromosomes();
	void setChromosomes(Chromosom **);

	void print();
	void reset();

private:
	//neurons
	int totalAmountOfNeurons;
	int layersAmount;
	Warstwy layers;

	//data converters
	WarstwaKonwerterow converters;
	int* ranges;
	int* buckets;

	//helpers functions
	void printList(int*, int);
	void printNueronsOutput(int* list, int length);
};

#endif /* PERCEPTRON_H_ */
