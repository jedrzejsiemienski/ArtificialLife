/*
 * ResearchEngine.h
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#ifndef RESEARCH_ENGINE_H_
#define RESEARCH_ENGINE_H_

#include <fstream>
#include <iterator>
#include <string>

#include "../evolution/Environment.h"
#include "../interface/SDLInterface.h"
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_gfxPrimitives.h"

using namespace std;

class ResearchEngine {
public:
	ResearchEngine();
	virtual ~ResearchEngine();
	void doPlannedResearches(bool showResults = true);

	static bool running;
	static int epochNumber;
	static int researchNumber;
	static int researchesCount;
	static SDL_Surface* screen;
	static int screenWidth;
	static int screenHeight;
	static void initScreen();
	static void showProgressBar(float, float);
	static void killScreen();


private:
	void doSingleResearch(Point*, Point*, int, int, float, float, int, bool showResult = false);

	void saveResultsToFile(string, vector<float>);

	string createFileName(string, string, float, float);

	Point * start;
	Point * end;
	int type;
	int startPopulationSize;
	vector<float> f;
	vector<float> cr;
	int movementSteps;
	int epochs;
};

int _progressThread( void *data );

#endif /* RESEARCH_ENGINE_H_ */

