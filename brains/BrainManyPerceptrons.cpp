/*
 * BrainManyPerceptrons.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainManyPerceptrons.h"

BrainManyPerceptrons::BrainManyPerceptrons() : BaseBrain() {
	srand (time(NULL));
	perceptronsCount = 5;
	perceptrons = new Perceptron*[perceptronsCount];
	initPerceptrons();
}

BrainManyPerceptrons::~BrainManyPerceptrons() {
	for(int i = 0; i < perceptronsCount; i++){
		delete perceptrons[i];
	}
	delete[] perceptrons;
}

int ** BrainManyPerceptrons::stimulate(int b1, int b2, int a1, int a2, int a3){
	int ** result = new int*[perceptronsCount];

	int i = 0;
	result[i] = stimulateSinglePerceptron(i, b1, a1, b2); i++; //b1
	result[i] = stimulateSinglePerceptron(i, b1, a1, b2); i++; //a1
	result[i] = stimulateSinglePerceptron(i, a1, a2, a3); i++; //a2
	result[i] = stimulateSinglePerceptron(i, b1, a3, b2); i++; //a3
	result[i] = stimulateSinglePerceptron(i, b1, a3, b2);      //b2

	return result;
}

int * BrainManyPerceptrons::stimulateSinglePerceptron(int perceptron, int x, int y, int z){
	int* result;
	int* inputs = new int[3];
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	result = perceptrons[perceptron]->stimulate(inputs);
	delete[] inputs;
	return result;
}

void BrainManyPerceptrons::initPerceptrons(){
	int layersAmount = 3;
	int * neuronsAmount = new int[layersAmount];

	neuronsAmount[0] = 3;
	neuronsAmount[1] = 5;
	neuronsAmount[2] = 2;

	int* givenRanges = new int[neuronsAmount[0]];
	int* givenBuckets = new int[neuronsAmount[0]];
	for (int i = 0; i < neuronsAmount[0]; i++){
		givenRanges[i] = 80;
		givenBuckets[i] = 20;
	}

	for(int i=0; i < perceptronsCount; i++){
		perceptrons[i] = new Perceptron(layersAmount, neuronsAmount, givenRanges, givenBuckets);
	}

	delete[] neuronsAmount;
	delete[] givenRanges;
	delete[] givenBuckets;
}


Genotype* BrainManyPerceptrons::getGenotype(){
	return new Genotype(perceptrons, perceptronsCount);
}


void BrainManyPerceptrons::setGenotype(Genotype* g){


}



void BrainManyPerceptrons::saveToFile(string name){
	ofstream file;

	file.open(name.c_str());

	file << "2" << endl ;
	file << getInitPoint()->x << " " << getInitPoint()->y << endl;
	file << getEndPoint()->x << " " << getEndPoint()->y << endl;

	int chromosomesCount;
	for(int i=0; i < perceptronsCount; i++){
		Chromosom ** ch1 = perceptrons[i]->getChromosomes();
		chromosomesCount = perceptrons[i]->getTotalAmountOfNeurons();

		for(int j=0; j < chromosomesCount; j++){
			file << ch1[j]->toString() << endl ;
		}
		file << "L" << endl;

		for(int j=0; j < chromosomesCount; j++){
			delete ch1[j];
		}
		delete[] ch1;
	}

	file.close();
}

void BrainManyPerceptrons::loadFromFile(string name){
	ifstream file;
	string line;

	file.open(name.c_str());

	//sprawdzamy typ:
	getline(file, line);
	if(line[0] != '2')
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

	int perceptron = 0;
	int neuron = 0;
	int index = 0;
	int chromosomesCount = perceptrons[0]->getTotalAmountOfNeurons();
	Chromosom ** ch = perceptrons[0]->getChromosomes();
	while(perceptron != perceptronsCount && getline(file, line)){
		if(line[0] == 'L'){
			//nastepny perceptron
			neuron = 0;
			perceptrons[perceptron++]->setChromosomes(ch);

			if(perceptron == perceptronsCount){
				break;
			}

			for(int i = 0; i < chromosomesCount; i++){
				delete ch[i];
			}
			delete[] ch;

			chromosomesCount = perceptrons[perceptron]->getTotalAmountOfNeurons();
			ch = perceptrons[perceptron]->getChromosomes();
		} else if(line.length() == 0){
			//nastepny neuron/chromosom
			neuron++;
			index = 0;
		} else {
			istringstream iss(line);
			vector<string> tokens;
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
			if(index < ch[neuron]->pairsCount){
				//para
				ch[neuron]->pairs[index].t = ::atof(tokens[0].c_str());
				ch[neuron]->pairs[index].w = ::atof(tokens[1].c_str());
				//cout << ch[neuron]->pairs[index].t << " " << ch[neuron]->pairs[index].w << endl;
			} else {
				//float
				ch[neuron]->floats[index - ch[neuron]->pairsCount] = ::atof(tokens[0].c_str());
				//cout << ch[neuron]->floats[index - ch[neuron]->pairsCount] << endl;
			}
			index++;
			//cout << index++ << " - " << tokens.size() << endl;
		}


	}

	file.close();
}
