/*
 * Worm.cpp
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#include "Worm.h"

using namespace std;

Worm::Worm(Point * initPoint, Point * endPoint) : WormBase(initPoint, endPoint) {
	perceptronsCount = 3;
	perceptrons = new Perceptron*[perceptronsCount];
	initPerceptrons();
}

Worm::~Worm() {
	for(int i = 0; i < perceptronsCount; i++){
		delete perceptrons[i];
	}
	delete[] perceptrons;
}

void Worm::reset(){
	joints[0]->reset(false);
	for(int i=0; i < perceptronsCount; i++){
		perceptrons[i]->reset();
	}
}

void Worm::mutate(float p, float f, float ft){
	int chromosomesCount;
	for(int i=0; i < perceptronsCount; i++){
		Chromosom ** chromosomes = perceptrons[i]->getChromosomes();
		chromosomesCount = perceptrons[i]->getTotalAmountOfNeurons();

		for(int j=0; j < chromosomesCount; j++){
			if(rand() % 100 > p*100){
				ChromosomesCrosser::mutate(chromosomes[j], f, ft);
			}
		}

		for(int j=0; j < chromosomesCount; j++){
				delete chromosomes[j];
		}
		delete[] chromosomes;
	}
}

void Worm::saveToFile(string name){
	ofstream file;

	file.open(name.c_str());

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

void Worm::loadFromFile(string name){
	ifstream file;
	string line;

	file.open(name.c_str());

	//to to jest punkt startowy
	getline(file, line);
	istringstream iss(line);
	vector<string> point;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(point));
	double x1 = ::atof(point[0].c_str());
	double y1 = ::atof(point[1].c_str());

	getline(file, line);
	istringstream iss2(line);
	vector<string> point2;
	copy(istream_iterator<string>(iss2), istream_iterator<string>(), back_inserter<vector<string> >(point2));
	double x2 = ::atof(point2[0].c_str());
	double y2 = ::atof(point2[1].c_str());

	Worm * worm = this;
	worm->initPoint = new Point(x1, y1);
	worm->endPoint = new Point(x2, y2);

	int perceptron = 0;
	int neuron = 0;
	int index = 0;
	int chromosomesCount = worm->perceptrons[0]->getTotalAmountOfNeurons();
	Chromosom ** ch = worm->perceptrons[0]->getChromosomes();
	while(perceptron != worm->perceptronsCount && getline(file, line)){
		if(line[0] == 'L'){
			//nastepny perceptron
			neuron = 0;
			worm->perceptrons[perceptron++]->setChromosomes(ch);

			if(perceptron == worm->perceptronsCount){
				break;
			}

			for(int i = 0; i < chromosomesCount; i++){
				delete ch[i];
			}
			delete[] ch;

			chromosomesCount = worm->perceptrons[perceptron]->getTotalAmountOfNeurons();
			ch = worm->perceptrons[perceptron]->getChromosomes();
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
	//return worm;
}

WormBase * Worm::cross(WormBase* w2){
	int chromosomesCount;

	Worm * w1 = this;

	Worm * worm = new Worm(w1->getInitPoint(), w1->getEndPoint());

	for(int i=0; i < w1->perceptronsCount; i++){

		Chromosom ** ch1 = w1->perceptrons[i]->getChromosomes();
		Chromosom ** ch2 = w2->perceptrons[i]->getChromosomes();
		chromosomesCount = w1->perceptrons[i]->getTotalAmountOfNeurons();

		Chromosom ** ch3 = new Chromosom*[chromosomesCount];

		for(int j=0; j < chromosomesCount; j++){
			ch3[j] = ChromosomesCrosser::cross(ch1[j], ch2[j], crossingTypes(MULTI_POINT), 0.4);
		}
		worm->perceptrons[i]->setChromosomes(ch3);


		for(int j=0; j < chromosomesCount; j++){
			delete ch1[j];
			delete ch2[j];
			delete ch3[j];
		}
		delete[] ch1;
		delete[] ch2;
		delete[] ch3;
	}
	return worm;
}

void Worm::initPerceptrons(){
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
		//perceptrons[i]->print();
	}

	delete[] neuronsAmount;
	delete[] givenRanges;
	delete[] givenBuckets;
}

int * Worm::stimulatePerceptron(int i, int x, int y, int z){
	int* inputs = new int[3];
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	int * output = perceptrons[i]->stimulate(inputs);
	delete[] inputs;
	return output;
}
