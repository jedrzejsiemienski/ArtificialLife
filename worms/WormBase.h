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

	virtual void move();
	virtual void reset();
	virtual void mutate(float, float, float);
	virtual void saveToFile(string);
	virtual static Worm * loadFromFile(string);

	Worm static * cross(Worm*, Worm*); //TOFIX KONIECZNIE BO TO NIE MOZE BYC STATYCZNE!!!!!

protected:
	Point * initPoint;
	Point * endPoint;

	float distance;
	int lastLinkMoved;
	int jointsCount;
	Joint** joints;

	virtual int * stimulatePerceptron(int, int, int, int);
	bool tossACoin();
	int normalizeAlpha(float, bool);
	int normalizeBeta(float);
	void moveCenterJoint(int);
	void moveLeftJoint();
	void moveRightJoint();
};


#endif /* WORMBASE_H_ */
