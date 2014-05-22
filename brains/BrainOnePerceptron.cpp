/*
 * BrainOnePerceptron.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainOnePerceptron.h"


BrainOnePerceptron::BrainOnePerceptron(int initVal) : BaseBrain() {
	initPerceptron(initVal);
}

BrainOnePerceptron::~BrainOnePerceptron() {
	delete perceptron;
}

int ** BrainOnePerceptron::stimulate(int b1, int b2, int a1, int a2, int a3){
	int* rawResult;
	int* inputs = new int[dataCount];
	int i = 0;
	inputs[i] = b1; i++;
	inputs[i] = b2; i++;
	inputs[i] = a1; i++;
	inputs[i] = a2; i++;
	inputs[i] = a3;
	rawResult = perceptron->stimulate(inputs);
	delete[] inputs;

	int ** result = new int*[dataCount];
	int j = 0;
	for(i = 0; i < dataCount; i++){
		result[i] = new int[2];
		result[i][0] = rawResult[j++];
		result[i][1] = rawResult[j++];
	}
	delete rawResult;
	return result;
}


void BrainOnePerceptron::initPerceptron(int initVal){
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 5;
	neuronsAmount[1] = 10; //to w sumie dyskusyjne
	neuronsAmount[2] = 10;

	int* givenRanges = new int[neuronsAmount[0]];
	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 80;
		givenBuckets[i] = 20;
	}

	perceptron = new Perceptron(layersAmount, neuronsAmount, givenRanges, givenBuckets, initVal);

	delete[] neuronsAmount;
	delete[] givenRanges;
	delete[] givenBuckets;
}


Genotype* BrainOnePerceptron::getGenotype(){
	return new Genotype(perceptron);
}


void BrainOnePerceptron::setGenotype(Genotype* g){
	Chromosom **ch = g->perceptrons[0]->getChromosomes();
	perceptron->setChromosomes(ch);
	for(int j = 0; j < perceptron->getTotalAmountOfNeurons(); j++){
		delete ch[j];
	}
	delete[] ch;
	delete g;
}



void BrainOnePerceptron::saveToFile(string name){
	ofstream file;

	file.open(name.c_str());

	file << "1" << endl ;
	file << getInitPoint()->x << " " << getInitPoint()->y << endl;
	file << getEndPoint()->x << " " << getEndPoint()->y << endl;

	int chromosomesCount;
	Chromosom ** ch1 = perceptron->getChromosomes();
	chromosomesCount = perceptron->getTotalAmountOfNeurons();

	for(int j=0; j < chromosomesCount; j++){
		file << ch1[j]->toString() << endl ;
	}
	file << "L" << endl;

	for(int j=0; j < chromosomesCount; j++){
		delete ch1[j];
	}
	delete[] ch1;

	file.close();
}

void BrainOnePerceptron::loadFromFile(string name){
	ifstream file;
	string line;

	file.open(name.c_str());

	//sprawdzamy typ:
	getline(file, line);
	if(line[0] != '1')
		return;

	//to to jest punkt startowy
	getline(file, line);
	istringstream iss(line);
	vector<string> point;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(point));
	double x1 = ::atof(point[0].c_str());
	double y1 = ::atof(point[1].c_str());
	initPoint->x = x1;
	initPoint->y = y1;

	getline(file, line);
	istringstream iss2(line);
	vector<string> point2;
	copy(istream_iterator<string>(iss2), istream_iterator<string>(), back_inserter<vector<string> >(point2));
	double x2 = ::atof(point2[0].c_str());
	double y2 = ::atof(point2[1].c_str());
	endPoint->x = x2;
	endPoint->y = y2;

	int neuron = 0;
	int index = 0;
	int chromosomesCount = perceptron->getTotalAmountOfNeurons();
	Chromosom ** ch = perceptron->getChromosomes();
	while(getline(file, line)){
		if(line[0] == 'L'){
			perceptron->setChromosomes(ch);
			for(int i = 0; i < chromosomesCount; i++){
				delete ch[i];
			}
			delete[] ch;
			break;
		} else if(line.length() == 0){
			neuron++;
			index = 0;
		} else {
			istringstream iss(line);
			vector<string> tokens;
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
			if(index < ch[neuron]->pairsCount){
				ch[neuron]->pairs[index].t = ::atof(tokens[0].c_str());
				ch[neuron]->pairs[index].w = ::atof(tokens[1].c_str());
			} else {
				ch[neuron]->floats[index - ch[neuron]->pairsCount] = ::atof(tokens[0].c_str());
			}
			index++;
		}
	}
	file.close();
}

