/*
 * Worm.h
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#ifndef WORM_H_
#define WORM_H_

#include "WormBase.h"

class Worm : public WormBase{
public:
	Worm(Point*, Point*);
	~Worm();

	void reset();
	void mutate(float, float, float);
	void saveToFile(string);
	static Worm * loadFromFile(string);
	static Worm * cross(Worm*, Worm*);

	int perceptronsCount;
	Perceptron** perceptrons;

private:
	Point * initPoint;
	Point * endPoint;

	float distance;
	int lastLinkMoved;
	int jointsCount;
	Joint** joints;

	void initPerceptrons();
	int * stimulatePerceptron(int, int, int, int);
};

#endif /* WORM_H_ */
