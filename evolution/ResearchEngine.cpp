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

	startPopulationSize = 50;

	f.push_back(0.4f);
	f.push_back(0.5f);
	f.push_back(0.7f);
	f.push_back(0.9f);
	cr.push_back(0.1f);
	cr.push_back(0.5f);
	cr.push_back(0.9f);

	movementSteps = 300;

	epochs = 10;

	screenWidth = 1000;
	screenHeight = 100;
}

ResearchEngine::~ResearchEngine() {
	delete start;
	delete end;
}

bool ResearchEngine::running;
int ResearchEngine::epochNumber;
int ResearchEngine::researchNumber;
int ResearchEngine::researchesCount;
SDL_Surface* ResearchEngine::screen;
int ResearchEngine::screenWidth;
int ResearchEngine::screenHeight;

Point * ResearchEngine::start;
Point * ResearchEngine::end;
int ResearchEngine::type;
int ResearchEngine::startPopulationSize;
vector<float> ResearchEngine::f;
vector<float> ResearchEngine::cr;
int ResearchEngine::movementSteps;
int ResearchEngine::epochs;

void ResearchEngine::doPlannedResearches(bool showResults){
	SDL_Thread *researchThread = SDL_CreateThread( _researchThread, NULL );
	SDL_Thread *progressThread = SDL_CreateThread( _progressThread, NULL );

	//SDL_WaitThread(researchThread, NULL);
	SDL_WaitThread(progressThread, NULL);
}

int _researchThread(void *data){
	vector<float>::iterator F;
	vector<float>::iterator CR;
	ResearchEngine::running = true;
	ResearchEngine::type = 1;
	ResearchEngine::researchNumber = 0;
	ResearchEngine::researchesCount = ResearchEngine::f.size() * ResearchEngine::cr.size() * 2;
	ResearchEngine::epochNumber = 0;
	for(F = ResearchEngine::f.begin(); F != ResearchEngine::f.end(); ++F){
		for(CR = ResearchEngine::cr.begin(); CR != ResearchEngine::cr.end(); ++CR){
			ResearchEngine::doSingleResearch(
				ResearchEngine::start,
				ResearchEngine::end,
				ResearchEngine::type,
				ResearchEngine::startPopulationSize,
				*F, *CR,
				ResearchEngine::movementSteps,
				false
			);
			ResearchEngine::researchNumber++;
		}
	}

	ResearchEngine::type = 2;
	for(F = ResearchEngine::f.begin(); F != ResearchEngine::f.end(); ++F){
		for(CR = ResearchEngine::cr.begin(); CR != ResearchEngine::cr.end(); ++CR){
			ResearchEngine::doSingleResearch(
				ResearchEngine::start,
				ResearchEngine::end,
				ResearchEngine::type,
				ResearchEngine::startPopulationSize,
				*F, *CR,
				ResearchEngine::movementSteps,
				false
			);
			ResearchEngine::researchNumber++;
		}
	}
	ResearchEngine::running = false;
}

int _progressThread( void *data )
{
	int screenWidth = 1000;
	int screenHeight = 100;
	int r = ResearchEngine::researchNumber;
	int e = ResearchEngine::epochNumber;

	SDL_Init( SDL_INIT_VIDEO );
	SDL_Surface* screen = SDL_SetVideoMode( screenWidth, screenHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Reasearch progress", 0 );
	SDL_Event event;

	bool quit = false;
    while( ResearchEngine::running && !quit)
    {
    	if(r != ResearchEngine::researchNumber || e != ResearchEngine::epochNumber){
    		r = ResearchEngine::researchNumber;
    		e = ResearchEngine::epochNumber;

    		int barHeight = 30;
    		int offset1 = 5;
    		int offset2 = 50;
    		int start = 5;
    		float barWidth = (float)screenWidth - 5.0f;
    		float progressA = barWidth * ((float)r / (float)ResearchEngine::researchesCount);
    		float progressB = barWidth * ((float)e / (float)ResearchEngine::epochs);

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

	/*
	ResearchEngine::initScreen();
	int currentNumber = 0;
    while( ResearchEngine::running == false )
    {
    	if(currentNumber != ResearchEngine::researchNumber){
    		currentNumber = ResearchEngine::researchNumber;
    		ResearchEngine::showProgressBar((float)currentNumber / (float)ResearchEngine::researchesCount, 1);
    	}
    }
    */
    return 0;
}



void ResearchEngine::doSingleResearch(Point *start, Point *end, int type, int populationSize, float f, float cr, int movementSteps, bool showResult){
	Environment env(*start, *end, type, startPopulationSize, f, cr, movementSteps);
	env.epochs(epochs);
	Worm * worm = env.getBestWorm();
	worm->saveToFile(createFileName("", "_worm.txt", f, cr));
	saveResultsToFile(createFileName("", "_results.txt", f, cr), env.getResults());

	if(showResult){
		SDLInterface inteface;
		inteface.displayWorm(worm);
	}

	env.clear();
}

void ResearchEngine::saveResultsToFile(string name, vector<float> results){
	ofstream file;

	file.open(name.c_str());
/*
	file << type << endl ;
	file << start->x << " " << start->y << endl ;
	file << end->x << " " << end->y << endl ;
	file << f << endl ;
	file << cr << endl ;
	file << startPopulationSize << endl ;
	file << movementSteps << endl ;
	file << epochs << endl ;
	file << endl ;
*/
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

void ResearchEngine::initScreen(){
	SDL_Init( SDL_INIT_VIDEO );

	screen = SDL_SetVideoMode( screenWidth, screenHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Reasearch progress", 0 );
}

void ResearchEngine::killScreen(){
	SDL_Quit();
}

void ResearchEngine::showProgressBar(float a, float b){
	int barHeight = 30;
	int offset1 = 5;
	int offset2 = 50;
	int start = 5;
	float barWidth = (float)screenWidth - 5.0f;
	float progressA = barWidth*a;
	float progressB = barWidth*b;

	boxRGBA(screen, 0, 0, screenWidth, screenHeight, 255, 255, 255, 255);
	rectangleRGBA(screen, start, offset1, barWidth, barHeight + offset1, 0, 0, 255, 255);
	boxRGBA(screen, start, offset1, progressA, barHeight + offset1, 0, 0, 255, 255);
	rectangleRGBA(screen, start, offset2, barWidth, barHeight + offset2, 0, 0, 255, 255);
	boxRGBA(screen, start, offset2, progressB, barHeight + offset2, 0, 0, 255, 255);
	SDL_Flip(screen);
}
