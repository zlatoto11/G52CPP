#include "header.h"
#include "templates.h"
#include "string"

#include "stdlib.h"
#include "string.h"
#include <ctime>
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <fstream>

#include "PsyzkBaseEngine.h"
#include "PsyzkObject.h"
#include "PsyzkObjectFinished.h"
#include "PsyzkObjectDiff.h"

#include "TileManager.h"


PsyzkBaseEngine::PsyzkBaseEngine()
{
	isPaused = false;
}


PsyzkBaseEngine::~PsyzkBaseEngine()
{
}

void PsyzkBaseEngine::SetupBackgroundBuffer(void)
{
	std::vector<std::string> data;
	std::ifstream readfile;
	const char* filetoload;

	filetoload = "leveldata.txt";
	readfile.open(filetoload);

	if (!readfile.is_open())
	{
		std::cout << "File unable to open";	//If unable to open file , display error and reject after 2.5 sec
	}

	std::string word;
	while (!readfile.eof())	//If succesfull launch
	{												//cout << word << endl;	//Print out the wrold and a new line
		readfile >> word;	// Continue
		data.push_back(word);	//Load word into vector array 
	}
	std::cout << filetoload << "\n\n"; //Debug purposes , quote which file to read from
									   //this_thread::sleep_for(chrono::milliseconds(2500));

	/*const char* data[] = {
		"gggggggggggggggg",
		"gbbbbbbbbbbbbbbg",
		"gbbbbbbbbbgggggg",
		"gbbbgggggbbbbbbg",
		"gbbbbbbbbbbbbbbg",
		"ggbbbbbbbbbbbbbg",
		"gbbggggggggggggg",
		"ggbbbbbbbbbbbbbg",
		"gbbgbbbbgbbbbbbg",
		"gggbggggbggggbbg",
		"gbbbbbbbbbbbbbbg",
		"gggggggggggggggg" };*/

	m_oTiles.SetSize(16, 12);
	// Set up the tiles
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 12; y++)
			m_oTiles.SetValue(x, y, data[y][x]);

	
	for (int y = 0; y < 12; y++)		//Prints out Tile Value
	{
		for (int x = 0; x < 16; x++)
			printf("%d ", m_oTiles.GetValue(x, y));
		printf("\n");
	}

	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);	//Set start position to draw
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);

	DrawTextToScreen(); 
	DrawTextToForegroundScreen();
}

void PsyzkBaseEngine::MouseDown(int iButton, int iX, int iY)
{
	printf("%d %d\n", iX, iY); //Prints out location of rectangle drawn
	if (iButton == SDL_BUTTON_LEFT) { // SDL_BUTTON_LEFT refers to left mouse click
		DrawTextToForegroundScreen();
		(dynamic_cast<PsyzkObject*>(GetDisplayableObject(0)))->changeColour();
	}
	else if (iButton == SDL_BUTTON_RIGHT)
	{
		DrawTextToForegroundScreen();
		(dynamic_cast<PsyzkObject*>(GetDisplayableObject(0)))->changeColour();
	}
	else if (iButton == SDL_BUTTON_MIDDLE) {

		std::vector<std::string> data;
		std::ifstream readfile;
		const char* filetoload;

		filetoload = "leveldata2.txt";
		readfile.open(filetoload);

		if (!readfile.is_open())
		{
			std::cout << "File unable to open";	//If unable to open file , display error and reject after 2.5 sec
		}

		std::string word;
		while (!readfile.eof())	//If succesfull launch
		{												//cout << word << endl;	//Print out the wrold and a new line
			readfile >> word;	// Continue
			data.push_back(word);	//Load word into vector array 
		}
		std::cout << filetoload << "\n\n"; //Debug purposes , quote which file to read from
		m_oTiles.SetSize(16, 12);
		// Set up the tiles
		for (int x = 0; x < 16; x++)
			for (int y = 0; y < 12; y++)
				m_oTiles.SetValue(x, y, data[y][x]);

		for (int y = 0; y < 12; y++)		//Prints out Tile Value
		{
			for (int x = 0; x < 16; x++)
				printf("%d ", m_oTiles.GetValue(x, y));
			printf("\n");
		}

		m_oTiles.SetBaseTilesPositionOnScreen(0, 0);	//Set start position to draw
		m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);

		DrawTextToScreen();
		DrawTextToForegroundScreen();
		Redraw(true);
	} // Mouse level force
}

void PsyzkBaseEngine::KeyDown(int iKeyCode) // Basically redraws background when you press spacebar
{
	switch (iKeyCode) // Keycode is key press
	{
	case SDLK_SPACE: // Refers to space bar
		SetupBackgroundBuffer(); //Calls the background function . Redraws entire screen.
		//Redraw(true);
		DrawTextToForegroundScreen();
		break;

	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode(0);
		break;
	case SDLK_BACKSPACE:
		isPaused = !isPaused;
	}
	
}

int PsyzkBaseEngine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(7);
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
	//order to work out where the end of the array is.
	StoreObjectInArray(0, new PsyzkObject(this));
	StoreObjectInArray(1, new PsyzkObjectFinished(this, 250, 500, false));
	StoreObjectInArray(2, new PsyzkObjectFinished(this, 500, 450, false));
	StoreObjectInArray(3, new PsyzkObjectFinished(this, 250, 250, true));
	StoreObjectInArray(4, new PsyzkObjectFinished(this, 425, 250, false));
	StoreObjectInArray(5, new PsyzkObjectFinished(this, 700, 350, false));
	StoreObjectInArray(6, new PsyzkObjectDiff(this, 600, 500));
	StoreObjectInArray(7, NULL);
	return 0;
}

void PsyzkBaseEngine::DrawTextToScreen()
{
	//CopyBackgroundPixels(200/*X*/, 500/*Y*/, GetWindowWidth(), 30/*Height*/); 
	DrawBackgroundString(200, 500, "Survive the Maze!", 0xFFFFFF, NULL);

}
	
void PsyzkBaseEngine::DrawTextToForegroundScreen()
{	
		std::string stringToAddTo = "Time Since Launch:";
		stringToAddTo.append(std::to_string(SDL_GetTicks()));	// Add Time to end of string
		const char *cstr = stringToAddTo.c_str();	//Set cstr to the string
		CopyBackgroundPixels(200/*X*/, 565/*Y*/, GetWindowWidth(), 30/*Height*/);
		DrawForegroundString(200, 565, cstr, 0xFFFFFF, NULL);

		if (isPaused == true) {
			//char draw[128];
			
			//sprintf(draw, "Game is paused! Current HP = %d", dynamic_cast<GetDisplayableObject(0)>->;
			DrawForegroundString(400, 300, "The game has been paused", 0x000000,NULL);
		}
}

PsyzkTileManager& PsyzkBaseEngine::returnTileManager() {
	return m_oTiles;
}

bool PsyzkBaseEngine::getPauseValue() {
	return isPaused;
}