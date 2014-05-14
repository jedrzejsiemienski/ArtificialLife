/*
 * BrainDummy.h
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#ifndef BRAINDUMMY_H_
#define BRAINDUMMY_H_

#include "BaseBrain.h"

class BrainDummy : public BaseBrain {
public:
	BrainDummy();
	virtual ~BrainDummy();
	int ** stimulate(int b1, int b2, int a1, int a2, int a3);
};

#endif /* BRAINDUMMY_H_ */
