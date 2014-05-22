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
#include "../evolution/Genotype.h"
#include "../neuralNetwork/NeuronImpulsowy.h"
#include "../utils/Point.h"
#include "Skeleton.h"
#include "SDL.h"

using namespace std;

class Worm {
public:
	Worm(int, int, int, int, int, int givenMovementSteps = 300, int initVal = NeuronImpulsowy::USE_RANDOM_VALUE);
	Worm(int, string); //load from file
	Worm(int, int, int, int, int, Genotype*, int givenMovementSteps = 300); //create from genotype
	virtual ~Worm();
	void move();
	void reset();
	void draw(SDL_Surface*);

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();

	float getCurrentDistanceToTarget();
	float getDistanceAfterNMoves(int);
	float getMovementSteps();

	void setBrain(BaseBrain*);
	BaseBrain* getBrain();

	void saveToFile(string);

private:
	void loadFromFile(string);
	void setBrainByType(int, int initVal = NeuronImpulsowy::USE_RANDOM_VALUE);

	Point * initPoint;
	Point * endPoint;
	BaseBrain* brain;
	Skeleton* skeleton;
	float movementSteps;
};

#endif /* WORM_H_ */
