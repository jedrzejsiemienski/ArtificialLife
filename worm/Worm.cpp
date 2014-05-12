/*
 * Worm.cpp
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#include "Worm.h"

using namespace std;

Worm::Worm(Point * initPoint, Point * endPoint) {
	this->initPoint = new Point(initPoint->x, initPoint->y);
	this->endPoint = new Point(endPoint->x, endPoint->y);

	distance = -1;
	lastLinkMoved = 0;
	jointsCount = 3;
	perceptronsCount = jointsCount + 2;
	joints = new Joint*[jointsCount];
	perceptrons = new Perceptron*[perceptronsCount];

	bool positive;
	for(int i=0; i < jointsCount; i++){
		positive = i%2 == 0;
		joints[i] = new Joint(initPoint->x, initPoint->y, positive);
		if(i > 0){
			joints[i-1]->setRight(joints[i]);
			joints[i]->setLeft(joints[i-1]);
		}
	}

	initPerceptrons();
}

Worm::~Worm() {
	for(int i = 0; i < perceptronsCount; i++){
		delete perceptrons[i];
	}
	delete[] perceptrons;

	for(int i = 0; i < jointsCount; i++){
		delete joints[i];
	}
	delete[] joints;
	delete initPoint;
}

Point * Worm::getEndPoint(){
	return endPoint;
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

Worm * Worm::cross(Worm* w1, Worm* w2){
	int chromosomesCount;

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

Point * Worm::getInitPoint(){
	return initPoint;
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

Point * Worm::getPosition(){
	Point * c = new Point();
	//c->x = (b->x - a->x)/2 + a->x;
	//c->y = (b->y - a->y)/2 + a->y;
	//c->x = (joints[jointsCount - 1]->c.x - joints[0]->a.x)/2 + joints[0]->a.x;
	//c->y = (joints[jointsCount - 1]->c.y - joints[0]->a.y)/2 + joints[0]->a.y;
	c->x = joints[0]->a.x;
	c->y = joints[0]->a.y;
	return c;
}

void Worm::reset(){
	joints[0]->reset(false);
	for(int i=0; i < perceptronsCount; i++){
		perceptrons[i]->reset();
	}
}

void Worm::draw(SDL_Surface* screen){
	for(int i=0; i < jointsCount; i++){
		joints[i]->draw(screen);
	}
}

void Worm::moveCenterJoint(int i){
	int x, y, z;
	x = 0;
	y = normalizeAlpha(joints[i]->alpha, joints[i]->positive);
	z = 0;

	if(i > 0){
		x = normalizeAlpha(joints[i-1]->alpha, joints[i-1]->positive);
		z = normalizeAlpha(joints[i-1]->alpha, joints[i-1]->positive);
	}

	if(i < jointsCount - 1){
		z = normalizeAlpha(joints[i+1]->alpha, joints[i+1]->positive);
		x = normalizeAlpha(joints[i+1]->alpha, joints[i+1]->positive);
	}

	if(i == 0 || i == jointsCount - 1){
		x = normalizeBeta(joints[0]->beta);
		z = normalizeBeta(joints[jointsCount-1]->beta);
	}


	int * result = stimulatePerceptron(i, x, y, z);
	if(result[0] == 1){
		if(result[1] == 1){
			joints[i]->increaseAlpha();
		} else {
			joints[i]->decreaseAlpha();
		}
	}

	delete[] result;

	/*
	if(result[0] == 1 && result[1] == 0){
		joints[i]->increaseAlpha();
	} else if(result[0] == 0 && result[1] == 1){
		joints[i]->decreaseAlpha();
	}
	*/
}

void Worm::moveLeftJoint(){
	int x, y, z;
	x = normalizeBeta(joints[0]->beta);
	y = normalizeAlpha(joints[0]->alpha, joints[0]->positive);
	z = normalizeBeta(joints[jointsCount-1]->beta);
	int * result = stimulatePerceptron(jointsCount, x, y, z);
	//cout << "x - " << x << ", y - " << y << ", z - " << z << endl;
	if(result[0] == 1){
		if(result[1] == 1){
			joints[0]->increaseBetaLeft();
		} else {
			joints[0]->decreaseBetaLeft();
		}
	}
	delete[] result;
}

void Worm::moveRightJoint(){
	int x, y, z;
	x = normalizeBeta(joints[jointsCount-1]->beta);
	y = normalizeAlpha(joints[jointsCount-1]->alpha, joints[jointsCount-1]->positive);
	z = normalizeBeta(joints[0]->beta);
	int * result = stimulatePerceptron(jointsCount + 1, x, y, z);
	//cout << "x - " << x << ", y - " << y << ", z - " << z << endl;
	if(result[0] == 1){
		if(result[1] == 1){
			joints[jointsCount-1]->increaseBetaRight();
		} else {
			joints[jointsCount-1]->decreaseBetaRight();
		}
	}
	delete[] result;
}

float Worm::getDistance(){
	return distance;
}

float Worm::getDistanceAfterNMoves(int movesCount, Point * target, bool verbose){
	if(distance == -1.0){
		for(int i = 0; i < movesCount; i++){
			move();
			if(verbose){
				cout << getCurrentDistance(target) << endl;
			}
		}
		distance = getCurrentDistance(target);
		reset();
	}
	return distance;
}

float Worm::getCurrentDistance(Point * target){
	Point * p1 = getPosition();
	float currenDtistance = sqrt(pow((p1->x - target->x),2) + pow((p1->y - target->y),2));
	//cout << p1->x << " " << p1->y << " - " << target->x << " " << target->y << " : " << currenDtistance << endl;
	delete p1;
	return currenDtistance;
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

Worm * Worm::loadFromFile(string name){
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

	//cout << x << " " << y << endl;
	Worm * worm = new Worm(new Point(x1, y1), new Point(x2, y2));

	//int chromosomesCount = worm->perceptrons[i]->getTotalAmountOfNeurons();

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

	return worm;
}

void Worm::move(){
	//cout << "move" << endl;

	if(lastLinkMoved < jointsCount){
		moveCenterJoint(lastLinkMoved);
	}

	if(lastLinkMoved == jointsCount){
		moveLeftJoint();
	}

	if(lastLinkMoved == jointsCount + 1){
		moveRightJoint();
	}

	lastLinkMoved++;
	if(lastLinkMoved == jointsCount + 2){
		lastLinkMoved = 0;
	}

	//cout << getPosition().x << " - " << getPosition().y << endl;
}

int Worm::normalizeAlpha(float a, bool positive){
	float b;
	if(a > 180){
		b = a - 180;
	} else {
		b = a;
	}

	if(!positive){
		b = b - 60;
	}
	b = b - 20;

	//cout << "alfa " << b << endl;
	return b;
}

int Worm::normalizeBeta(float a){
	return a + 90;
}


bool Worm::tossACoin(){
	if(rand() % 2 == 0){
		return true;
	} else {
		return false;
	}
}
