/*
 * Joint.h
 *
 *  Created on: 29 gru 2013
 *      Author: jedrek
 */

#ifndef JOINT_H_
#define JOINT_H_

#include "../utils/Point.h"
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

class Joint {
public:
	Joint(int, int, bool);
	virtual ~Joint();

	void increaseAlpha();
	void increaseBetaLeft();
	void increaseBetaRight();

	void decreaseAlpha();
	void decreaseBetaLeft();
	void decreaseBetaRight();

	void setAB(Point, Point, bool resetAngles = false);
	void setCB(Point, Point);

	void setLeft(Joint*);
	void setRight(Joint*);

	void draw(SDL_Surface*);
	void print();

	void reset(bool);
	void setStartPoint(int, int);

	Point a;
	Point b;
	Point c;

	float alpha;
	float beta;
	bool positive;

	void resetAngles();

private:
	Joint* leftJoint;
	Joint* rightJoint;

	void propagateLeft();
	void propagateRight(bool resetAngles = false);
	void propagate();
	bool canIncreaseAlpha();
	bool canDecreaseAlpha();
	bool canIncreaseBeta();
	bool canDecreaseBeta();

	Point test1;
	Point test2;
	float lineA;
	float lineB;
	float d;

	float AA;
	float BB;
	float AAA;
	float BBB;
	float CCC;

	float min;
	float h;

	int startX;
	int startY;

	void recalculate(bool);
	void recalculateBeta(bool);
};


#endif /* JOINT_H_ */
