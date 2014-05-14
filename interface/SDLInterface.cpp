/*
 * SDLInterface.cpp
 *
 *  Created on: 9 gru 2013
 *      Author: jedrek
 */

#include "SDLInterface.h"

using namespace std;

SDLInterface::SDLInterface() {
	screen = 0;
}

SDLInterface::~SDLInterface() {}

int SDLInterface::manuallySkeleton() {

	skeleton = new Skeleton(400, 400);

	SDL_Init( SDL_INIT_VIDEO );

	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	SDL_Event event;
	bool gameRunning = true;

	clrScr();
	skeleton->draw(screen);

	while (gameRunning)	{
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			if (event.type == SDL_KEYDOWN) {
				if(moveSkeleton(event.key.keysym.sym) == 1) {
					gameRunning = false;
				}
	        }
		}
	}

	SDL_Quit();
    return 0;
}

int SDLInterface::moveSkeleton(SDLKey keyPressed) {
    switch (keyPressed)
    {
       case SDLK_ESCAPE:
          return 1;
       //=============================================== 1
       case SDLK_UP:
       	  for(int i = 0; i < 5; i++){
       		  skeleton->moveFirstJoint(true);
     	  }
    	  break;
       case SDLK_DOWN:
       	  for(int i = 0; i < 5; i++){
       		  skeleton->moveFirstJoint(false);
      	  }
    	  break;
       case SDLK_LEFT:
       	  for(int i = 0; i < 20; i++){
       		skeleton->moveLeftJoint(true);
       	  }
    	  break;
       case SDLK_RIGHT:
       	  for(int i = 0; i < 20; i++){
       		  skeleton->moveLeftJoint(false);
       	  }
    	   break;
       //=============================================== 2
       case SDLK_q:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveSecondJoint(true);
    	   }
    	   break;
       case SDLK_e:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveSecondJoint(false);
    	   }
    	  break;
       //=============================================== 3
       case SDLK_w:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveThirdJoint(true);
    	   }
     	  break;
       case SDLK_s:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveThirdJoint(false);
    	   }
    	  break;
       case SDLK_a:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveRightJoint(true);
    	   }
    	  break;
       case SDLK_d:
    	   for(int i = 0; i < 5; i++){
    		   skeleton->moveRightJoint(false);
    	   }
    	  break;
    }

	clrScr();
	skeleton->draw(screen);

    return 0;
}





int SDLInterface::manuallyJoints() {
	j1 = new Joint(400,400,true);
	j2 = new Joint(400,400,false);
	j3 = new Joint(400,400,true);

	j1->setRight(j2);
	j2->setLeft(j1);

	j2->setRight(j3);
	j3->setLeft(j2);

	SDL_Init( SDL_INIT_VIDEO );

	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	SDL_Event event;
	bool gameRunning = true;

	clrScr();
	j1->draw(screen);
	j2->draw(screen);
	j3->draw(screen);

	while (gameRunning)	{
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			if (event.type == SDL_KEYDOWN) {
				if(moveJoint(event.key.keysym.sym) == 1) {
					gameRunning = false;
				}
	        }
		}
	}

	SDL_Quit();
    return 0;
}

int SDLInterface::moveJoint(SDLKey keyPressed) {
    switch (keyPressed)
    {
       case SDLK_ESCAPE:
          return 1;
       //=============================================== 1
       case SDLK_UP:
    	  for(int i = 0; i < 5; i++){
    		  j1->increaseAlpha();
    		  //j2->increaseAlpha();
    	  }
    	  break;
       case SDLK_DOWN:
     	  for(int i = 0; i < 5; i++){
     		 j1->decreaseAlpha();
     		 //j2->decreaseAlpha();
    	  }
    	  break;
       case SDLK_LEFT:
      	  for(int i = 0; i < 40; i++){
      		  j1->increaseBetaLeft();
      		  //j2->increaseBetaLeft();
    	  }
    	  break;
       case SDLK_RIGHT:
    	  for(int i = 0; i < 40; i++){
    		  j1->decreaseBetaLeft();
    		  //j2->decreaseBetaLeft();
    	  }
    	  break;
       //=============================================== 2
       case SDLK_q:
      	  for(int i = 0; i < 5; i++){
      		  j2->increaseAlpha();
      		  //j2->increaseBetaLeft();
    	  }
    	  break;
       case SDLK_e:
    	  for(int i = 0; i < 5; i++){
    		  j2->decreaseAlpha();
    		  //j2->decreaseBetaLeft();
    	  }
    	  break;
       //=============================================== 3
       case SDLK_w:
    	  for(int i = 0; i < 5; i++){
    		  j3->increaseAlpha();
    		  //j2->increaseAlpha();
    	  }
    	  break;
       case SDLK_s:
     	  for(int i = 0; i < 5; i++){
     		 j3->decreaseAlpha();
     		 //j2->decreaseAlpha();
    	  }
    	  break;
       case SDLK_a:
      	  for(int i = 0; i < 40; i++){
      		  j3->increaseBetaRight();
      		  //j2->increaseBetaLeft();
    	  }
    	  break;
       case SDLK_d:
    	  for(int i = 0; i < 40; i++){
    		  j3->decreaseBetaRight();
    		  //j2->decreaseBetaLeft();
    	  }
    	  break;
    }

	clrScr();
	j1->draw(screen);
	j2->draw(screen);
	j3->draw(screen);

    return 0;
}






int SDLInterface::displayWorm(Worm * worm, int movementSteps, Point * target, int interval) {
	//worm = new Worm(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT/2 - 20);
	//worm = new Worm(50, 50);
	this->worm = worm;
	int currentStep = 0;
	this->target = target;

	start = true;

	SDL_Init( SDL_INIT_VIDEO );

	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );

	SDL_Event event;
	bool gameRunning = true;
//	Uint32 interval = 100;
	Uint32 lastActionTime;
	Uint32 currentTime;

	lastActionTime = SDL_GetTicks();
	while (gameRunning)	{
		currentTime = SDL_GetTicks();

		if(start && currentTime - lastActionTime > interval && currentStep != movementSteps) {
		//if(currentTime - lastActionTime > interval) {
			lastActionTime = currentTime;
			drawScene();
			timerAction();
			currentStep++;
		}

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			if (event.type == SDL_KEYDOWN) {
				if(handleKeyPress(event.key.keysym.sym) == 1) {
					gameRunning = false;
				}
	        }
		}
	}

	SDL_Quit();
    return 0;
}

void SDLInterface::printMesh(int stepX, int stepY, SDL_Surface* screen){
	for(int x = 0; x < WINDOW_WIDTH; x += stepX){
		lineRGBA(screen, x, 0, x, WINDOW_HEIGHT, 0, 0, 255, 255);
	}

	for(int y = 0; y < WINDOW_HEIGHT; y += stepY){
		lineRGBA(screen, 0, y, WINDOW_WIDTH, y, 0, 0, 255, 255);
	}

}

void SDLInterface::drawScene() {
	clrScr();
	filledCircleColor(screen, this->target->x, this->target->y, 10, 0x331188);
	printMesh(100,100,screen);
	worm->draw(screen);


	//filledCircleColor(screen, 100, 100, 10, 0x331188);
}

void SDLInterface::timerAction() {
	worm->move();
	//cout << "Sprawdzenie - " << worm->getCurrentDistance(&target);
	//Point * p = worm->getPosition();
	//cout << p.x << " " << p.y << endl;
}

int SDLInterface::handleKeyPress(SDLKey keyPressed) {
    switch (keyPressed)
    {
       case SDLK_ESCAPE:
          return 1;
       case SDLK_DOWN:
    	  start = true;
          break;

    }
    drawScene();
    return 0;
}

void SDLInterface::clrScr() {
	boxRGBA(screen, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 255, 255, 255, 255);
}

void SDLInterface::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b){
    lineRGBA(screen, x1, y1, x2, y2, r, g, b, 255);
    SDL_Flip(screen);
}
