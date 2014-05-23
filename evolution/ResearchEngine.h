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

	static Point * start;
	static Point * end;
	static int type;
	static int startPopulationSize;
	static vector<float> f;
	static vector<float> cr;
	static int movementSteps;
	static int epochs;

	static void doSingleResearch(Point*, Point*, int, int, float, float, int, bool showResult = false);
	static void saveResultsToFile(string, vector<float>);
	static string createFileName(string, string, float, float);

};

int _researchThread(void *data);
int _progressThread(void *data);

#endif /* RESEARCH_ENGINE_H_ */


