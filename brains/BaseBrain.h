/*
 * BaseBrain.h
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#ifndef BASEBRAIN_H_
#define BASEBRAIN_H_

class BaseBrain {
public:
	virtual int ** stimulate(int b1, int b2, int a1, int a2, int a3) = 0;
};

#endif /* BASEBRAIN_H_ */
