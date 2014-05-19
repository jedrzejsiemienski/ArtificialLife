/*
 * NeuronImpulsowy.cpp
 *
 *  Created on: 2 lis 2013
 *      Author: jedrek
 */

#include "NeuronImpulsowy.h"

using namespace std;
/*
NeuronImpulsowy::NeuronImpulsowy(float givenTimeBase) {
	T = givenTimeBase;
	eta = 0;
	theta = 0;
	g = 0;
	w = 0;
	talInput = 0;
	talOutput = 0;
	uf = 0;
	ut = 0;
	y = 0;
}
*/


NeuronImpulsowy::NeuronImpulsowy(int givenG, float givenTimeBase, int initVal) {
	eta = returnNumber(initVal, randomNumberFromRange(4.0, 100000.0));//0.01;   //wsplczynnik zamulenia  ---- TO
	theta = returnNumber(initVal, randomNumberFromRange(20.0, 1000.0));//0.4; //prog wyjscia  ---- TO
	g = givenG;  //ilosc neurownow wejsciowych = gamma.length, tzn ilosc wejsc - givenG!!!
	T = givenTimeBase;

	w = new float [g];	 //tablica wag wejsc neuronu ---- TO
	for (int i = 0; i < g; i++){
		w[i] = returnNumber(initVal, randomNumber());//0.25;
	}

	talInput = new float [g]; //tablica z wspolczynnikami mowiacymi o tym przez jaki czas dany neuron wplywa na na stan naszego
	for (int i = 0; i < g; i++){  //---- TO
		talInput[i] = returnNumber(initVal, randomNumberFromRange(1.0, 10000.0));//0.01;
	}

	talOutput = returnNumber(initVal, randomNumber());//0.1; //wspolczynnik mowiacy o tym jak mocno nas zmula w czasie  ---- TO
	uf = new float [g];	 //tablica czastkowych zmian stanu zwiazaynch z wejsciami
	for (int i = 0; i < g; i++){
		uf[i] = 0;
	}

	ut = 0;	 //czastkowa zmiana stanu zwiazana z zamula
	y = 0; //wyjscie neuronu
}

NeuronImpulsowy::NeuronImpulsowy(const NeuronImpulsowy & n){
	eta = n.eta;
	theta = n.theta;
	g = n.g;
	T = n.T;

	w = new float [g];
	for (int i = 0; i < g; i++){
		w[i] = n.w[i];
	}

	talInput = new float [g];
	for (int i = 0; i < g; i++){
		talInput[i] = n.talInput[i];
	}

	talOutput = n.talOutput;
	uf = new float [g];
	for (int i = 0; i < g; i++){
		uf[i] = n.uf[i];
	}

	ut = 0;	 //czastkowa zmiana stanu zwiazana z zamula
	y = 0; //wyjscie neuronu
}

float NeuronImpulsowy::returnNumber(int given, float random){
	return given == USE_RANDOM_VALUE ? random : (float)given;
}

NeuronImpulsowy::~NeuronImpulsowy() {
	delete[] w;
	delete[] talInput;
	delete[] uf;
}

void NeuronImpulsowy::reset(){
	for (int i = 0; i < g; i++){
		uf[i] = 0;
	}
	ut = 0;
	y = 0;
}

int NeuronImpulsowy::compute(int* x) {

	//czynnik zwiazny z wejsciami
	float ufSum = 0;
	for (int i = 0; i < g; i++){
		uf[i] = w[i]*(float)x[i] + exp(T/(-talInput[i]))*uf[i];
		ufSum += uf[i];
	}

	//czynnik zwiazany z wypuszczeniem neuronu
	ut = -(eta * y + talOutput * ut + theta);
	float u = ufSum + ut;

	if(u >= 0){
		y = 1;
	} else {
		y = 0;
	}

	return y;
}

void NeuronImpulsowy::print(){
	cout << "Jestem neuronem pod adresem " << this << endl;
	cout << "Ilosc wejsc: " << g << endl;
	cout << "eta = " << eta << endl;
	cout << "theta = " << theta << endl;
	cout << "talOutput = " << talOutput << endl;

	cout << "Wagi wejsc i czasy wejsc:" << endl;
	for(int i = 0; i < g; i++){
		cout << "w[" << i << "] = " << w[i] << ", ti[" << i << "] = " << talInput[i] << endl;
	}
	cout << endl;
}


Chromosom * NeuronImpulsowy::getChromosome(){
	Chromosom * chromosom = new Chromosom;

	chromosom->pairsCount = g;
	chromosom->floatsCount = 3;
	chromosom->pairs = new Pair[chromosom->pairsCount];
	for(int i = 0; i < chromosom->pairsCount; i++){
		Pair pair;
		pair.w = w[i];
		pair.t = talInput[i];
		chromosom->pairs[i] = pair;
	}

	chromosom->floats = new float[chromosom->floatsCount];
	chromosom->floats[0] = eta;
	chromosom->floats[1] = theta;
	chromosom->floats[2] = talOutput;

	return chromosom;
}

float NeuronImpulsowy::randomNumber(){ //generates random number form 0..max
	float max = 1.0;
	float base = 1000.0;
	return randomNumberFromRange(max, base);
}

float NeuronImpulsowy::randomNumberFromRange(float max, float base){
	return ((float)(rand() % (int)base) / (base / max));
}

int NeuronImpulsowy::setChromosome(Chromosom * chromosom){
	eta = chromosom->floats[0];
	theta = chromosom->floats[1];
	talOutput = chromosom->floats[2];
	g = chromosom->pairsCount;

	for (int i = 0; i < g; i++){
		w[i] = chromosom->pairs[i].w;
		talInput[i] = chromosom->pairs[i].t;
	}

	//tablica czastkowych zmian stanu zwiazaynch z wejsciami
	for (int i = 0; i < g; i++){
		uf[i] = 0;
	}

	return 0;
}
