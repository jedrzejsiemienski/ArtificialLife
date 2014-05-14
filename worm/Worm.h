/*
 * Worm.h
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#ifndef WORM_H_
#define WORM_H_

#include "../brains/BaseBrain.h"
#include "../brains/BrainDummy.h"
#include "../brains/BrainRandom.h"
#include "../brains/BrainManyPerceptrons.h"
#include "../utils/Point.h"
#include "Skeleton.h"
#include "SDL.h"

using namespace std;

class Worm {
public:
	Worm(int, int, int, int, int);
	virtual ~Worm();
	void move();
	void draw(SDL_Surface*);

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();

	float getCurrentDistanceToTarget();

private:
	Point * endPoint;
	BaseBrain* brain;
	Skeleton* skeleton;
};

#endif /* WORM_H_ */
