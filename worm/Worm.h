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
#include "../brains/BrainOnePerceptron.h"
#include "../utils/Point.h"
#include "Skeleton.h"
#include "SDL.h"

using namespace std;

class Worm {
public:
	Worm(int, int, int, int, int);
	Worm(int, string); //load from file
	virtual ~Worm();
	void move();
	void reset();
	void draw(SDL_Surface*);

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();

	float getCurrentDistanceToTarget();
	float getDistanceAfterNMoves(int);

	void setBrain(BaseBrain*);
	BaseBrain* getBrain();

	void saveToFile(string);

private:
	void loadFromFile(string);
	void setBrainByType(int);

	Point * initPoint;
	Point * endPoint;
	BaseBrain* brain;
	Skeleton* skeleton;
};

#endif /* WORM_H_ */
