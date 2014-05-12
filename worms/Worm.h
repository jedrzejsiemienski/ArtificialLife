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
	WormBase* cross(WormBase *);
	void loadFromFile(string);
	void saveToFile(string);

private:
	void initPerceptrons();
	int * stimulatePerceptron(int, int, int, int);
};

#endif /* WORM_H_ */
