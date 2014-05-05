/*
 * Worm.h
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#ifndef WORM_H_
#define WORM_H_

#include "Joint.h"
#include "../utils/Point.h"
#include "../neuralNetwork/Perceptron.h"
#include "../evolutionAlgorithms/ChromosomesCrosser.h"
#include "../evolutionAlgorithms/Chromosom.h"
#include "SDL.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

class Worm {
public:
	Worm(Point*, Point*);
	virtual ~Worm();

	void draw(SDL_Surface*);
	void move();
	void reset();

	float getDistance();

	//funkcje do mutacji itd
	Point * getPosition();
	Point * getInitPoint();
	void mutate(float, float, float);
	Worm static * cross(Worm*, Worm*);

	int perceptronsCount;
	Perceptron** perceptrons;

	float getDistanceAfterNMoves(int, Point *, bool verbose = false);
	float getCurrentDistance(Point *);

	void saveToFile(string);
	static Worm *  loadFromFile(string);

	Point * getEndPoint();

private:
	Point * initPoint;
	Point * endPoint;

	float distance;
	int lastLinkMoved;
	int jointsCount;
	Joint** joints;

	void initPerceptrons();
	int * stimulatePerceptron(int, int, int, int);
	bool tossACoin();
	int normalizeAlpha(float, bool);
	int normalizeBeta(float);

	void moveCenterJoint(int);
	void moveLeftJoint();
	void moveRightJoint();
};

#endif /* WORM_H_ */
