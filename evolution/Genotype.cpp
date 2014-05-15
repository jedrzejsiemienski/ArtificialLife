/*
 * Genotype.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "Genotype.h"

Genotype::Genotype(Perceptron ** perceptrons, int perceptronsCount) {
	this->perceptrons = perceptrons;
	this->perceptronsCount = perceptronsCount;
}

Genotype::~Genotype() {
	this->perceptrons = NULL;
	this->perceptronsCount = 0;
}

Genotype::Genotype(const Genotype & g){
	perceptronsCount = g.perceptronsCount;
	perceptrons = new Perceptron*[perceptronsCount];

	for(int i = 0; i < perceptronsCount; i++){
		perceptrons[i] = new Perceptron(*g.perceptrons[i]);
	}
}

//substract given genotype from current genotype
Genotype* Genotype::substract(Genotype* x){
	Genotype * result = new Genotype(*this);
	for(int i = 0; i < result->perceptronsCount; i++){
		Chromosom** resultChr = result->perceptrons[i]->getChromosomes();
		Chromosom** baseChr = x->perceptrons[i]->getChromosomes();
		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			resultChr[j]->substract(baseChr[j]);
		}
	}
	return result;
}

//add given genotype to current genotype
Genotype* Genotype::add(Genotype* x){
	Genotype * result = new Genotype(*this);
	for(int i = 0; i < result->perceptronsCount; i++){
		Chromosom** resultChr = result->perceptrons[i]->getChromosomes();
		Chromosom** baseChr = x->perceptrons[i]->getChromosomes();
		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			resultChr[j]->add(baseChr[j]);
		}
	}
	return result;
}

//mutliplies everything from genotype by given number
Genotype* Genotype::multiply(float a){
	Genotype * result = new Genotype(*this);
	for(int i = 0; i < result->perceptronsCount; i++){
		Chromosom** resultChr = result->perceptrons[i]->getChromosomes();
		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			resultChr[j]->multiply(a);
		}
	}
	return result;
}

//pobiera mutanta v, mutuje go ze soba i zwraca u - osobnika probnego
Genotype* Genotype::crossWith(float cr, Genotype* x){
	Genotype * result = new Genotype(*this);
	for(int i = 0; i < result->perceptronsCount; i++){
		Chromosom** resultChr = result->perceptrons[i]->getChromosomes();
		Chromosom** baseChr = x->perceptrons[i]->getChromosomes();

		Chromosom** crossedChr = new Chromosom*[result->perceptrons[i]->getTotalAmountOfNeurons()];
		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			crossedChr[j] = ChromosomesCrosser::cross(resultChr[j], baseChr[j], crossingTypes(HOMOGENEOUS), cr);
		}
		result->perceptrons[i]->setChromosomes(crossedChr);

		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			delete crossedChr[j];
		}
		delete[] crossedChr;
	}
	return result;
}

//mutates current with 2 given
Genotype* Genotype::mutateWith(float f, Genotype* x1, Genotype* x2){
	return this->add((x1->substract(x2))->multiply(f));
}

bool assertEqualStructure(Genotype* g){
	return true;
}
