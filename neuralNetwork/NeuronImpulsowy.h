/*
 * NeuronImpulsowy.h
 *
 *  Created on: 2 lis 2013
 *      Author: jedrek
 */

#ifndef NEURONIMPULSOWY_H_
#define NEURONIMPULSOWY_H_

#include "../evolutionAlgorithms/Chromosom.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

class NeuronImpulsowy {
public:
	//NeuronImpulsowy(float);
	NeuronImpulsowy(int, float);
	virtual ~NeuronImpulsowy();
	int compute(int*);

	//funkcje potrzebne do krzyzowania - pobieranie/ustawianie genotypu neuronu
	Chromosom * getChromosome();
	int setChromosome(Chromosom*);

	void print();

	void reset();

private:
	float randomNumber(); //generates random number form 0..1
	float randomNumberFromRange(float, float); //generates random number form 0..1

	float T;	 //intewal czasowy
	float eta;   //wsp�czynnik zamulenia
	float theta; //pr�g wyj�cia
	int   g;     //ilosc neurownow wejsciowych = gamma.length

	float* w;	 //tablica wag wejsc neuronu
	float* talInput; //tablica z wspolczynnikami mowiacymi o tym przez jaki czas dany neuron wplywa na na stan naszego
	float  talOutput; //wspolczynnik mowiacy o tym jak mocno nas zmula w czasie
	float* uf;	 //tablica czastkowych zmian stanu zwiazaynch z wejsciami
	float  ut;	 //czastkowa zmiana stanu zwiazana z zamula

	int y; //wyjscie neuronu

};

#endif /* NEURONIMPULSOWY_H_ */
