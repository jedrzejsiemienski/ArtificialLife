/*
 * BrainRandom.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef BRAINRANDOM_H_
#define BRAINRANDOM_H_

#include "BaseBrain.h"
#include <stdlib.h>
#include <time.h>

class BrainRandom : public BaseBrain {
public:
	BrainRandom();
	virtual ~BrainRandom();
	int ** stimulate(int b1, int b2, int a1, int a2, int a3);
};

#endif /* BRAINRANDOM_H_ */
