/*
 * SDLInterface.h
 *
 *  Created on: 9 gru 2013
 *      Author: jedrek
 */

#ifndef SDLINTERFACE_H_
#define SDLINTERFACE_H_

#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_gfxPrimitives.h"

#include "../worm/Skeleton.h"
#include "../worm/Worm.h"
#include <iostream>

//#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <stdlib.h>

class SDLInterface {
	public:
		SDLInterface();
		virtual ~SDLInterface();

		int manuallySkeleton();
		int manuallyJoints();
		int displayWorm(Worm * worm, int, Point*, int interval = 100);
		void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
		void clrScr();

	private:
		void printMesh(int, int, SDL_Surface*);

		SDL_Surface* screen;
		const int WINDOW_WIDTH = 1000;
		const int WINDOW_HEIGHT = 650;
		const char* WINDOW_TITLE = "SDL Start";

		bool start;

		void timerAction();
		void drawScene();
		int handleKeyPress(SDLKey);

		int moveJoint(SDLKey);
		int moveSkeleton(SDLKey);

		Point * target;

		Joint * j1;
		Joint * j2;
		Joint * j3;

		Skeleton * skeleton;
		Worm * worm;
};

#endif /* SDLINTERFACE_H_ */
