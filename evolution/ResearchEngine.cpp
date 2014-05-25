/*
 * ResearchEngine.cpp
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#include "ResearchEngine.h"

ResearchEngine::ResearchEngine() {
	epochsVector.push_back(50);

	types.push_back(1);
	types.push_back(2);

	Route * route;
	route = new Route();
	route->start = new Point(100, 100);
	route->end = new Point(900, 600);
	routes.push_back(route);
/*
	route = new Route();
	route->start = new Point(900, 600);
	route->end = new Point(100, 100);
	routes.push_back(route);

	route = new Route();
	route->start = new Point(100, 600);
	route->end = new Point(900, 600);
	routes.push_back(route);
*/
	startPopulationSizes.push_back(200);

	f.push_back(0.4f);
//	f.push_back(0.5f);
//	f.push_back(0.6f);
//	f.push_back(0.7f);
//	f.push_back(0.8f);
//	f.push_back(0.9f);

	cr.push_back(0.1f);
//	cr.push_back(0.3f);
//	cr.push_back(0.5f);
//	cr.push_back(0.7f);
//	cr.push_back(0.9f);

	movementSteps = 300;
}

ResearchEngine::~ResearchEngine() {

}

void ResearchEngine::doPlannedResearches(bool showResults){
	SDL_Thread *progressThread = SDL_CreateThread( _progressThread, (void*)this);
	SDL_Thread *researchThread = SDL_CreateThread( _researchThread, (void*)this);

	//SDL_WaitThread(researchThread, NULL);
	SDL_WaitThread(progressThread, NULL);
}

int _researchThread(void *data){
	ResearchEngine* researchEngine = (ResearchEngine*) data;
	researchEngine->_doPlannedResearches(true);
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
	vector<Route*>::iterator route;
	vector<int>::iterator startPopulationSize;
	vector<int>::iterator type;
	vector<int>::iterator epochs;

	running = true;
	currentResearch = 0;
	researchesTotal = startPopulationSizes.size() * routes.size() * f.size() * cr.size() * types.size() * epochsVector.size();

	for(startPopulationSize = startPopulationSizes.begin(); startPopulationSize != startPopulationSizes.end(); ++startPopulationSize){
		for(epochs = epochsVector.begin(); epochs != epochsVector.end(); ++epochs){
			epochsTotal = *epochs;
			for(type = types.begin(); type != types.end(); ++type){
				for(route = routes.begin(); route != routes.end(); ++route){
					for(F = f.begin(); F != f.end(); ++F){
						for(CR = cr.begin(); CR != cr.end(); ++CR){
							doSingleResearch(
								(*route)->start,
								(*route)->end,
								*type,
								*startPopulationSize,
								*F, *CR,
								movementSteps,
								epochsTotal,
								showResults
							);
							currentResearch++;
						}
					}
				}
			}
		}
	}
	running = false;
}

void ResearchEngine::doSingleResearch(Point *start, Point *end, int type, int populationSize, float f, float cr, int movementSteps, int epochs, bool showResult){
	Environment env(*start, *end, type, populationSize, f, cr, movementSteps);

	vector<float> results;
	for(currentEpoch = 0; currentEpoch < epochs; currentEpoch++){
		results.push_back(env.evolutionCycle());
	}

	Worm * worm = env.getBestWorm();
	worm->saveToFile(createFileName("", "_worm.txt", start, end, type, populationSize, f, cr, movementSteps, epochs));
	saveResultsToFile(createFileName("", "_results.txt", start, end, type, populationSize, f, cr, movementSteps, epochs), results);

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

string ResearchEngine::createFileName(string prefix, string postfix, Point *start, Point *end, int type, int populationSize, float f, float cr, int movementSteps, int epochs){
	string results = "";
	results += prefix;

	stringstream ss;
	ss << type << "_";
	ss << start->x << "_" << start->y << "_";
	ss << end->x   << "_" << end->y   << "_";
	ss << f << "_";
	ss << cr << "_";
	ss << populationSize << "_";
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
	return epochsTotal;
}

int ResearchEngine::getCurrentResearch(){
	return currentResearch;
}

int ResearchEngine::getResearches(){
	return researchesTotal;
}
