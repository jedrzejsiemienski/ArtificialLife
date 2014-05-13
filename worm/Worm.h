/*
 * Worm.h
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#ifndef WORM_H_
#define WORM_H_

#include "SDL.h"

class Worm {
public:
	Worm();
	virtual ~Worm();

	void move();
	void draw(SDL_Surface*);
};

#endif /* WORM_H_ */
