/*
 * Perceptron.cpp
 *
 *  Created on: 19 gru 2013
 *      Author: jedrek
 */

#include "Perceptron.h"

#include <typeinfo>

using namespace std;

/*
 * Na wejscie podajemy:
 * - ilosc wejsc (neuronow w warstwie wejsciowej)
 * - wektor z zakresami dla poszczegolnych wejsc            - kodowanie
 * - wektor z ilosciami kubelkow dla poszczegolnych wejsce  - kodowanie
 * - ilosc neuronow w warstwie ukrytej
 * - ilosc wyjsc (neurony w warstwie wyjsciowej)
 */
Perceptron::Perceptron(int givenLayersAmount, int* neuronsAmounts, int* givenRanges, int* givenBuckets, int initVal) {
	buckets = new int[neuronsAmounts[0]];
	for (int i = 0; i < neuronsAmounts[0]; i++){
		buckets[i] = givenBuckets[i];
	}

	ranges = new int[neuronsAmounts[0]];
	for (int i = 0; i < neuronsAmounts[0]; i++){
		ranges[i] = givenRanges[i];
	}

	layersAmount = givenLayersAmount;

	for (int i = 0; i < neuronsAmounts[0]; i++){
		converters.push_back(new KonwerterDanych(buckets[i], ranges[i]));
	}

	float timeBase = 0.01;

	totalAmountOfNeurons = 0;

	int inputsAmounts;
	WarstwaNeuronow* layer;
	for(int i = 0; i < layersAmount; i++) {
		layer = new WarstwaNeuronow();
		totalAmountOfNeurons += neuronsAmounts[i];
		for (int j = 0; j != neuronsAmounts[i]; j++){
 			if(i > 0){
				inputsAmounts = neuronsAmounts[i-1];
			} else {
				inputsAmounts = buckets[j];
			}
			layer->push_back(new NeuronImpulsowy(inputsAmounts, timeBase, initVal));
		}
		layers.push_back(layer);
	}
}

Perceptron::Perceptron(const Perceptron & p){
	int firstLayerSize = (*p.layers.begin())->size();
	buckets = new int[firstLayerSize];
	for (int i = 0; i < firstLayerSize; i++){
		buckets[i] = p.buckets[i];
	}

	ranges = new int[firstLayerSize];
	for (int i = 0; i < firstLayerSize; i++){
		ranges[i] = p.buckets[i];
	}

	layersAmount = p.layersAmount;

	for (int i = 0; i < firstLayerSize; i++){
		converters.push_back(new KonwerterDanych(buckets[i], ranges[i]));
	}

	totalAmountOfNeurons = 0;

	WarstwaNeuronow* layer;
	Warstwy::const_iterator pLayersIter;
	WarstwaNeuronow::const_iterator pSingleLayerIter;
	for(pLayersIter = p.layers.begin(); pLayersIter != p.layers.end(); ++pLayersIter){
		layer = new WarstwaNeuronow();
		totalAmountOfNeurons += (*pLayersIter)->size();
		for(pSingleLayerIter = (*pLayersIter)->begin(); pSingleLayerIter != (*pLayersIter)->end(); ++pSingleLayerIter){
			layer->push_back(new NeuronImpulsowy(**pSingleLayerIter));
		}
		layers.push_back(layer);
	}
}

Perceptron::~Perceptron() {
	WarstwaKonwerterow::iterator iterator;
	for(iterator = converters.begin(); iterator != converters.end(); ++iterator){
		delete *iterator;
	}

	for(int i = 0; i < layersAmount; i++) {
		for (WarstwaNeuronow::iterator neuron = layers[i]->begin(); neuron != layers[i]->end(); neuron++) {
			delete *neuron;
		}
		delete layers[i];
	}


	delete[] ranges;
	delete[] buckets;
}

void Perceptron::reset(){
	for(int i = 0; i < layersAmount; i++) {
		for (WarstwaNeuronow::iterator neuron = layers[i]->begin(); neuron != layers[i]->end(); neuron++) {
			(*neuron)->reset();
		}
	}
}

int Perceptron::getTotalAmountOfNeurons(){
	return totalAmountOfNeurons;
}

Chromosom ** Perceptron::getChromosomes(){
	Chromosom ** chromosomes = new Chromosom*[totalAmountOfNeurons];

	int index = 0;
	for(int i = 0; i < layersAmount; i++) {
		for (WarstwaNeuronow::iterator neuron = layers[i]->begin(); neuron != layers[i]->end(); neuron++) {
			chromosomes[index++] = (*neuron)->getChromosome();
		}
	}

	return chromosomes;
}

void Perceptron::setChromosomes(Chromosom ** chromosomes){
	int index = 0;
	for(int i = 0; i < layersAmount; i++) {
		for (WarstwaNeuronow::iterator neuron = layers[i]->begin(); neuron != layers[i]->end(); neuron++) {
			(*neuron)->setChromosome(chromosomes[index++]);
		}
	}
}


//na wejscie podajemy wektor wejsc - liczby po prostu
//na wyjsciu mamy wektor z impulsami - wyjsciami neurownow z ostatniej warstwy
int * Perceptron::stimulate(int* inputs) {

	int inputsCount = layers.front()->size();
	int** xIn = new int*[inputsCount];

	//konwersja
	for (int i = 0; i < inputsCount; i++){
		xIn[i] = converters[i]->convert(inputs[i]);
		//cout << "liczba: " << inputs[i] << endl;
		//printList(xIn[i], buckets[i]);
	}

	//wejscie na pierwsze warstwy
	int index = 0;
	int * layerOut = new int[inputsCount];
	for (WarstwaNeuronow::iterator neuron = layers[0]->begin(); neuron != layers[0]->end(); neuron++) {
		layerOut[index] = (*neuron)->compute(xIn[index]);
		index++;
	}

	for (int i = 0; i < inputsCount; i++){
		delete[] xIn[i];
	}
	delete[] xIn;

	//printNueronsOutput(layerOut, inputsCount);




	//propagacja kolejnych wyjsc dalej
	int currentNeuronsCount = inputsCount;
	for(int i = 1; i < layersAmount; i++) {
		//copy output to input for next layer
		int * layerInput = new int[currentNeuronsCount];
		for(int j = 0; j < currentNeuronsCount; j++){
			layerInput[j] = layerOut[j];
		}

		delete[] layerOut;

		currentNeuronsCount = layers[i]->size();
		layerOut = new int[currentNeuronsCount];

		index = 0;
		for (WarstwaNeuronow::iterator neuron = layers[i]->begin(); neuron != layers[i]->end(); neuron++) {
			layerOut[index++] = (*neuron)->compute(layerInput);
		}

		delete[] layerInput;
		//printNueronsOutput(layerOut, currentNeuronsCount);
	}
	return layerOut;

}

void Perceptron::printNueronsOutput(int* list, int length){
	for (int i = 0; i < length; i++){
		cout << "Neuron " << i << ": " << list[i] << endl;
	}
}

void Perceptron::printList(int* list, int length){
	for (int i = 0; i < length; i++){
		cout << list[i] << " ";
	}
	cout << endl;
}

void Perceptron::print(){
	cout << "Jestem perceptronem pod adresem " << this << endl;
	cout << "Mam " << layersAmount << " warstw" << endl;

	for(int i = 0; i < layersAmount; i++) {
		cout << "Warstwa nr " << i << " ma " << layers[i]->size() << " neuronow."<< endl;
		for (WarstwaNeuronow::iterator j = layers[i]->begin(); j != layers[i]->end(); j++) {
			cout << "\t";
			(*j)->print();
			cout << endl;
		}
	}

}
