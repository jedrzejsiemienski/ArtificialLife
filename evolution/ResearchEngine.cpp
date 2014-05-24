/*
 * ResearchEngine.cpp
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#include "ResearchEngine.h"

ResearchEngine::ResearchEngine() {
	start = new Point(100, 100);
	end = new Point(900, 600);

	startPopulationSize = 20;

	f.push_back(0.4f);
	f.push_back(0.5f);
	f.push_back(0.6f);
	f.push_back(0.7f);
	f.push_back(0.8f);
	f.push_back(0.9f);

	cr.push_back(0.1f);
	cr.push_back(0.3f);
	cr.push_back(0.5f);
	cr.push_back(0.7f);
	cr.push_back(0.9f);

	movementSteps = 300;

	epochs = 10;
}

ResearchEngine::~ResearchEngine() {
	delete start;
	delete end;
}

void ResearchEngine::doPlannedResearches(bool showResults){
	SDL_Thread *progressThread = SDL_CreateThread( _progressThread, (void*)this);
	SDL_CreateThread( _researchThread, (void*)this);

	//SDL_WaitThread(researchThread, NULL);
	SDL_WaitThread(progressThread, NULL);
}

int _researchThread(void *data){
	ResearchEngine* researchEngine = (ResearchEngine*) data;
	researchEngine->_doPlannedResearches(false);
	return 0;
}

int _progressThread( void *data )
{
	ResearchEngine* researchEngine = (ResearchEngine*) data;
	int screenWidth = 1000;
	int screenHeight = 100;
	int r = researchEngine->getCurrentResearch();
	int e = researchEngine->getCurrentEpoch();

	SDL_Init( SDL_INIT_VIDEO );
	SDL_Surface* screen = SDL_SetVideoMode( screenWidth, screenHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Reasearch progress", 0 );
	SDL_Event event;

	bool quit = false;
    while( researchEngine->isRunning() && !quit)
    {
    	if(r != researchEngine->getCurrentResearch() || e != researchEngine->getCurrentEpoch()){
    		r = researchEngine->getCurrentResearch();
    		e = researchEngine->getCurrentEpoch();

    		int barHeight = 30;
    		int offset1 = 5;
    		int offset2 = 50;
    		int start = 5;
    		float barWidth = (float)screenWidth - 5.0f;
    		float progressA = barWidth * ((float)r / (float)researchEngine->getResearches());
    		float progressB = barWidth * ((float)e / (float)researchEngine->getEpochs());

    		boxRGBA(screen, 0, 0, screenWidth, screenHeight, 255, 255, 255, 255);
    		rectangleRGBA(screen, start, offset1, barWidth, barHeight + offset1, 0, 0, 255, 255);
    		boxRGBA(screen, start, offset1, progressA + start, barHeight + offset1, 0, 0, 255, 255);
    		rectangleRGBA(screen, start, offset2, barWidth, barHeight + offset2, 0, 0, 255, 255);
    		boxRGBA(screen, start, offset2, progressB + start, barHeight + offset2, 0, 0, 255, 255);
    		SDL_Flip(screen);
    	}

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
    }

    SDL_Quit();

    return 0;
}

void ResearchEngine::_doPlannedResearches(bool showResults){
	vector<float>::iterator F;
	vector<float>::iterator CR;

	running = true;
	currentResearch = 0;
	researches = f.size() * cr.size() * 2;
	for(type = 1; type <= 2; type++){
		for(F = f.begin(); F != f.end(); ++F){
			for(CR = cr.begin(); CR != cr.end(); ++CR){
				doSingleResearch(
					start,
					end,
					type,
					startPopulationSize,
					*F, *CR,
					movementSteps,
					false
				);
				currentResearch++;
			}
		}
	}
	running = false;
}

void ResearchEngine::doSingleResearch(Point *start, Point *end, int type, int populationSize, float f, float cr, int movementSteps, bool showResult){
	Environment env(*start, *end, type, startPopulationSize, f, cr, movementSteps);

	vector<float> results;
	for(currentEpoch = 0; currentEpoch < epochs; currentEpoch++){
		results.push_back(env.evolutionCycle());
	}

	Worm * worm = env.getBestWorm();
	worm->saveToFile(createFileName("", "_worm.txt", f, cr));
	saveResultsToFile(createFileName("", "_results.txt", f, cr), results);

	if(showResult){
		SDLInterface inteface;
		inteface.displayWorm(worm);
	}

	env.clear();
}

void ResearchEngine::saveResultsToFile(string name, vector<float> results){
	ofstream file;

	file.open(name.c_str());

	vector<float>::iterator iter = results.begin();
	while(iter != results.end()){
		file << *iter << endl;
		iter++;
	}

	file.close();
}

string ResearchEngine::createFileName(string prefix, string postfix, float f, float cr){
	string results = "";
	results += prefix;

	stringstream ss;
	ss << type << "_";
	ss << start->x << "_" << start->y << "_";
	ss << end->x   << "_" << end->y   << "_";
	ss << f << "_";
	ss << cr << "_";
	ss << startPopulationSize << "_";
	ss << movementSteps << "_";
	ss << epochs << "_";

	results += ss.str();
	results += postfix;
	return results;
}

bool ResearchEngine::isRunning(){
	return running;
}

int ResearchEngine::getCurrentEpoch(){
	return currentEpoch;
}

int ResearchEngine::getEpochs(){
	return epochs;
}

int ResearchEngine::getCurrentResearch(){
	return currentResearch;
}

int ResearchEngine::getResearches(){
	return researches;
}
