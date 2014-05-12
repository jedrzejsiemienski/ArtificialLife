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

#include "../worms/WormBase.h"
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

		int manuallyWorm();
		int displayWorm(WormBase * worm, int, Point*, int interval = 100);
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
		int moveWorm(SDLKey);

		Point * target;

		Joint * j1;
		Joint * j2;
		Joint * j3;

		WormBase * worm;
};

#endif /* SDLINTERFACE_H_ */
