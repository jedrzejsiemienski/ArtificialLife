/*
 * Genotype.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "Genotype.h"

Genotype::Genotype(Perceptron ** perceptrons, int perceptronsCount) {
	this->perceptronsCount = perceptronsCount;
	this->perceptrons = new Perceptron*[perceptronsCount];
	for(int i = 0; i < perceptronsCount; i++){
		this->perceptrons[i] = new Perceptron(*perceptrons[i]);
	}
}

Genotype::Genotype(Perceptron * perceptron) {
	perceptronsCount = 1;
	perceptrons = new Perceptron*[perceptronsCount];
	perceptrons[0] = new Perceptron(*perceptron);
}

Genotype::~Genotype() {
	for(int i = 0; i < perceptronsCount; i++){
		delete perceptrons[i];
	}
	delete[] perceptrons;
	perceptronsCount = 0;
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
		result->perceptrons[i]->setChromosomes(resultChr);

		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			delete resultChr[j];
			delete baseChr[j];
		}
		delete[] resultChr;
		delete[] baseChr;

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
		result->perceptrons[i]->setChromosomes(resultChr);

		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			delete resultChr[j];
			delete baseChr[j];
		}
		delete[] resultChr;
		delete[] baseChr;
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
		result->perceptrons[i]->setChromosomes(resultChr);

		for(int j = 0; j < result->perceptrons[i]->getTotalAmountOfNeurons(); j++){
			delete resultChr[j];
		}
		delete[] resultChr;
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
			delete resultChr[j];
			delete baseChr[j];
			delete crossedChr[j];
		}
		delete[] resultChr;
		delete[] baseChr;
		delete[] crossedChr;
	}
	return result;
}

//mutates current with 2 given
Genotype* Genotype::mutateWith(float f, Genotype* x1, Genotype* x2){
	Genotype *substract = x1->substract(x2);
	Genotype *mutlipiled = substract->multiply(f);
	Genotype *result = this->add(mutlipiled);
	delete substract;
	delete mutlipiled;
	return result;
}

//mutates current with 3 given
Genotype* Genotype::mutateCurrentToBest(float f, Genotype* xBest, Genotype* x1, Genotype* x2){
	Genotype *substract1 = xBest->substract(this);
	Genotype *mutlipiled1 = substract1->multiply(f);

	Genotype *substract2 = x1->substract(x2);
	Genotype *mutlipiled2 = substract2->multiply(f);

	Genotype *partial = mutlipiled2->add(mutlipiled1);

	Genotype *result = this->add(partial);
	delete substract1;
	delete mutlipiled1;
	delete substract2;
	delete mutlipiled2;
	delete partial;
	return result;
}

bool assertEqualStructure(Genotype* g){
	return true;
}
