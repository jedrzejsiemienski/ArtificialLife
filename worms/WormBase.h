/*
 * WormBase.h
 *
 *  Created on: 5 maj 2014
 *      Author: jedrek
 */

#ifndef WORMBASE_H_
#define WORMBASE_H_


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

class WormBase {
public:
	WormBase(Point*, Point*);
	virtual ~WormBase();

	void draw(SDL_Surface*);
	float getDistanceToTarget(); //funkcja do oceny

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();
	float getDistanceAfterNMoves(int, Point *, bool verbose = false);
	float getCurrentDistance(Point *);
	void move();

	virtual void reset() = 0;
	virtual void mutate(float, float, float) = 0;
	virtual WormBase* cross(WormBase *) = 0;
	virtual void loadFromFile(string) = 0;
	virtual void saveToFile(string) = 0;

	int perceptronsCount;
	Perceptron** perceptrons;
	Point * initPoint;
	Point * endPoint;

protected:

	float distance;
	int lastLinkMoved;
	int jointsCount;
	Joint** joints;

	bool tossACoin();
	int normalizeAlpha(float, bool);
	int normalizeBeta(float);
	void moveCenterJoint(int);
	void moveLeftJoint();
	void moveRightJoint();

	virtual int * stimulatePerceptron(int, int, int, int) = 0;
};


#endif /* WORMBASE_H_ */
