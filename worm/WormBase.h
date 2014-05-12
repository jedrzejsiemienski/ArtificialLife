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
#include "../evolution/ChromosomesCrosser.h"
#include "../evolution/Chromosom.h"
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
/*
	void draw(SDL_Surface*);
	float getDistanceToTarget(); //funkcja do oceny

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();
	float getDistanceAfterNMoves(int, Point *, bool verbose = false);
	float getCurrentDistance(Point *);
	void move();

	virtual void reset();
	virtual void mutate(float, float, float);
	virtual WormBase* cross(WormBase *);
	virtual void loadFromFile(string);
	virtual void saveToFile(string);

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

	void initPerceptrons();
	virtual int * stimulatePerceptron(int, int, int, int);
*/
};


#endif /* WORMBASE_H_ */
