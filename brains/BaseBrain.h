/*
 * BaseBrain.h
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#ifndef BASEBRAIN_H_
#define BASEBRAIN_H_

#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>
#include <string>
#include "../utils/Point.h"
#include "../evolution/Genotype.h"
#include "../neuralNetwork/NeuronImpulsowy.h"

using namespace std;

class BaseBrain {
public:
	BaseBrain(){dataCount = 5; initPoint = new Point(0, 0); endPoint = new Point(0, 0);};
	virtual ~BaseBrain(){delete initPoint; delete endPoint;};

	virtual int ** stimulate(int b1, int b2, int a1, int a2, int a3) = 0;

	virtual void saveToFile(string name){};
	virtual void loadFromFile(string name){};

	virtual Genotype* getGenotype(){return 0;};
	virtual void setGenotype(Genotype*){};
	virtual void reset(){};

	void setInitPoint(int x, int y){initPoint->x = x; initPoint->y = y;};
	void setEndPoint(int x, int y){endPoint->x = x; endPoint->y = y;};
	Point* getInitPoint(){return initPoint;};
	Point* getEndPoint(){return endPoint;};

	int movementSteps;

protected:
	int dataCount;
	Point* initPoint;
	Point* endPoint;
};

#endif /* BASEBRAIN_H_ */
