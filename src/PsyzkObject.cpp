#include "header.h"
#include "templates.h"

#include "PsyzkObject.h"
#include "PsyzkBaseEngine.h"
#include "JPGImage.h"
#include "PsyzkTileManager.h"
#include "DisplayableObject.h"

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

#include "PsyzkObject.h"
#include "PsyzkObjectFinished.h"
#include "PsyzkObjectDiff.h"

#include "TileManager.h"


PsyzkObject::PsyzkObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{

	bEngine = dynamic_cast<PsyzkBaseEngine*>(pEngine);
	// Current and previous coordinates for the object - set them the same
	//initially
	m_iCurrentScreenX = m_iPreviousScreenX = 50;
	m_iCurrentScreenY = m_iPreviousScreenY = 450;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 40;
	m_iDrawHeight = 40;

	m_iColour = GetEngine()->GetColour(rand() % 41);

	health = 100;

	// And make it visible
	SetVisible(true);
}

void PsyzkObject::changeColour() {
	m_iColour = GetEngine()->GetColour(rand() % 41);
}

PsyzkObject::~PsyzkObject()
{
}

void PsyzkObject::Draw(void)
{
	ImageData left, right, up, down;
		//load image based on direction
	/*ImageData im, im2;
	im2.LoadImage("resources/Pokeball.png");
	im.ShrinkFrom(&im2, 1);
	
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);*/
	int iSize = 25;
	GetEngine()->CopyBackgroundPixels(m_iCurrentScreenX-30, m_iCurrentScreenY - 20, GetEngine()->GetWindowWidth(), 30);
	GetEngine()->DrawForegroundOval(
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_iColour);

	char draw[128];
	sprintf(draw, "Health: %d", health);
	GetEngine()->DrawForegroundString(m_iCurrentScreenX-30, m_iCurrentScreenY - 20, draw, 0xFFFFFF);
	StoreLastScreenPositionForUndraw();
	

}

void PsyzkObject::objectCollision() {
	PsyzkTileManager& tM = dynamic_cast<PsyzkBaseEngine*>(GetEngine())->returnTileManager();

	int circleCenterX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth / 2;
	int circleCenterY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight / 2;
	int circleRadius = m_iDrawWidth / 2;

	
	int iTileX = tM.GetTileXForPositionOnScreen(m_iCurrentScreenX);
	int iTileY = tM.GetTileYForPositionOnScreen(m_iCurrentScreenY);
	int currentTile = tM.GetValue(iTileX, iTileY);
	int topRight = tM.GetTileXForPositionOnScreen(m_iCurrentScreenX+50);
	int bottomleft = tM.GetTileYForPositionOnScreen(m_iCurrentScreenY + 50);
	
}

void PsyzkObject::DoUpdate(int iCurrentTime)  //update currentscreen X + Y variables, and change where objects are drawn
{
	
	bool isGamePaused = bEngine->getPauseValue();

	if (isGamePaused == true) {
		return;
	}
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 4;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 4;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 4;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 4;

	PsyzkTileManager& tM = dynamic_cast<PsyzkBaseEngine*>(GetEngine())->returnTileManager();

	//PsyzkTileManager *tM = GetEngine()->returnTileManager();
	int circleCenterX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth / 2;
	int circleCenterY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight / 2;
	int circleRadius = m_iDrawWidth / 2;

	int collisionX1 = circleCenterX;
	int collisionY1 = circleCenterY - circleRadius;
	int collisionX2 = circleCenterX + circleRadius;
	int collisionY2 = circleCenterY;
	int collisionX3 = circleCenterX;
	int collisionY3 = circleCenterY + circleRadius;
	int collisionX4 = circleCenterX - circleRadius;
	int collisionY4 = circleCenterY;



	int iTileX1 = tM.GetTileXForPositionOnScreen(collisionX1);
	int iTileY1 = tM.GetTileYForPositionOnScreen(collisionY1);
	int iTileX2 = tM.GetTileXForPositionOnScreen(collisionX2);
	int iTileY2 = tM.GetTileYForPositionOnScreen(collisionY2);
	int iTileX3 = tM.GetTileXForPositionOnScreen(collisionX3);
	int iTileY3 = tM.GetTileYForPositionOnScreen(collisionY3);
	int iTileX4 = tM.GetTileXForPositionOnScreen(collisionX4);
	int iTileY4 = tM.GetTileYForPositionOnScreen(collisionY4);


	if (tM.GetValue(iTileX1, iTileY1) == 103 || tM.GetValue(iTileX1, iTileY1) == 106) {
		//printf("\n\n collision works \n\n");
		m_iCurrentScreenY += 4;
	}
	else if (tM.GetValue(iTileX2, iTileY2) == 103 || tM.GetValue(iTileX2, iTileY2) == 106) {
		m_iCurrentScreenX -= 4;
	}
	else if (tM.GetValue(iTileX3, iTileY3) == 103 || tM.GetValue(iTileX3, iTileY3) == 106) {
		m_iCurrentScreenY -= 4;
	}
	else if (tM.GetValue(iTileX4, iTileY4) == 103 || tM.GetValue(iTileX4, iTileY4) == 106) {
		m_iCurrentScreenX += 4;
	}
	if (tM.GetValue(iTileX1, iTileY1) == 120) {
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
		tM.SetSize(16, 12);
		// Set up the tiles
		for (int x = 0; x < 16; x++)
			for (int y = 0; y < 12; y++)
				tM.SetValue(x, y, data[y][x]);

		for (int y = 0; y < 12; y++)		//Prints out Tile Value
		{
			for (int x = 0; x < 16; x++)
				printf("%d ", tM.GetValue(x, y));
			printf("\n");
		}

		tM.SetBaseTilesPositionOnScreen(0, 0);	//Set start position to draw
		tM.DrawAllTiles(GetEngine(), GetEngine()->GetBackground(), 0, 0, 15, 11);

		//GetEngine()->DrawTextToScreen();
		//GetEngine()->DrawTextToForegroundScreen();
		GetEngine()->Redraw(true);

		GetEngine()->DrawableObjectsChanged();
		GetEngine()->DestroyOldObjects();
		GetEngine()->CreateObjectArray(1);
		GetEngine()->StoreObjectInArray(0, new PsyzkObject(bEngine));
		GetEngine()->StoreObjectInArray(1, NULL);
	}

	if (tM.GetValue(iTileX1, iTileY1) == 117) {
		std::vector<std::string> data;
		std::ifstream readfile;
		const char* filetoload;

		filetoload = "leveldata3.txt";
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
		tM.SetSize(16, 12);
		// Set up the tiles
		for (int x = 0; x < 16; x++)
			for (int y = 0; y < 12; y++)
				tM.SetValue(x, y, data[y][x]);

		for (int y = 0; y < 12; y++)		//Prints out Tile Value
		{
			for (int x = 0; x < 16; x++)
				printf("%d ", tM.GetValue(x, y));
			printf("\n");
		}

		tM.SetBaseTilesPositionOnScreen(0, 0);	//Set start position to draw
		tM.DrawAllTiles(GetEngine(), GetEngine()->GetBackground(), 0, 0, 15, 11);

		//GetEngine()->DrawTextToScreen();
		//GetEngine()->DrawTextToForegroundScreen();
		GetEngine()->Redraw(true);

		GetEngine()->DrawableObjectsChanged();
		GetEngine()->DestroyOldObjects();
		GetEngine()->CreateObjectArray(26);
		GetEngine()->StoreObjectInArray(0, new PsyzkObject(bEngine));
		GetEngine()->StoreObjectInArray(1, new PsyzkObjectFinished(bEngine, 150, 50, false));
		GetEngine()->StoreObjectInArray(2, new PsyzkObjectFinished(bEngine, 50, 100, false));
		GetEngine()->StoreObjectInArray(3, new PsyzkObjectFinished(bEngine, 100, 300, false));
		GetEngine()->StoreObjectInArray(4, new PsyzkObjectFinished(bEngine, 50, 200, false));
		GetEngine()->StoreObjectInArray(5, new PsyzkObjectFinished(bEngine, 300, 250, false));
		GetEngine()->StoreObjectInArray(6, new PsyzkObjectFinished(bEngine, 400, 150, false));
		GetEngine()->StoreObjectInArray(7, new PsyzkObjectFinished(bEngine, 600, 500, false));
		GetEngine()->StoreObjectInArray(8, new PsyzkObjectFinished(bEngine, 275, 400, false));
		GetEngine()->StoreObjectInArray(9, new PsyzkObjectFinished(bEngine, 200, 350, false));
		GetEngine()->StoreObjectInArray(10, new PsyzkObjectFinished(bEngine, 200, 450, false));
		GetEngine()->StoreObjectInArray(11, new PsyzkObjectFinished(bEngine, 50, 50, true));
		GetEngine()->StoreObjectInArray(12, new PsyzkObjectFinished(bEngine, 100, 250, true));
		GetEngine()->StoreObjectInArray(13, new PsyzkObjectFinished(bEngine, 150, 200, true));
		GetEngine()->StoreObjectInArray(14, new PsyzkObjectFinished(bEngine, 200, 450, true));
		GetEngine()->StoreObjectInArray(15, new PsyzkObjectFinished(bEngine, 250, 400, true));
		GetEngine()->StoreObjectInArray(16, new PsyzkObjectFinished(bEngine, 300, 350, true));
		GetEngine()->StoreObjectInArray(17, new PsyzkObjectFinished(bEngine, 350, 150, true));
		GetEngine()->StoreObjectInArray(18, new PsyzkObjectFinished(bEngine, 400, 100, true));
		GetEngine()->StoreObjectInArray(19, new PsyzkObjectFinished(bEngine, 450, 500, true));
		GetEngine()->StoreObjectInArray(20, new PsyzkObjectFinished(bEngine, 500, 300, true));
		GetEngine()->StoreObjectInArray(21, new PsyzkObjectFinished(bEngine, 550, 250, true));
		GetEngine()->StoreObjectInArray(22, new PsyzkObjectFinished(bEngine, 600, 50, true));
		GetEngine()->StoreObjectInArray(23, new PsyzkObjectFinished(bEngine, 650, 300, true));
		GetEngine()->StoreObjectInArray(24, new PsyzkObjectFinished(bEngine, 700, 500, true));
		GetEngine()->StoreObjectInArray(25, new PsyzkObjectFinished(bEngine, 750, 200, true));
		GetEngine()->StoreObjectInArray(26, NULL);
	}

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= GetEngine()->GetWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetWindowHeight() - m_iDrawHeight;

	DisplayableObject* enemyObject;
	for (int objectID = 0;(enemyObject = bEngine->GetDisplayableObject(objectID)) != NULL; objectID++) {
		if (enemyObject == this) {
			continue;
		}
		int enemyX = enemyObject->GetXCentre();
		int enemyXLeft = enemyObject->GetXCentre() - 20;
		int enemyXRight = enemyObject->GetXCentre() + 20;
		int enemyY = enemyObject->GetYCentre();
		int centerY = this->GetYCentre();
		int lBox = m_iCurrentScreenX;
		int rBox = m_iCurrentScreenX + (m_iDrawWidth / 2);

		if (centerY >= enemyY && centerY <= enemyY + 20) {

			if (lBox <= enemyXLeft && enemyXLeft <= rBox) {
				health -= 2;
			}
			else if (rBox <= enemyXRight && enemyXRight <= lBox) {

				health -= 2;

			}
			else if (enemyXLeft <= lBox && lBox <= enemyXRight) {

				health -= 2;

			}
			else if (enemyXLeft <= rBox && rBox <= enemyXRight) {

				health -= 2;

			}

		}

	}
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();

	if (health <= 0) {
		m_iCurrentScreenX = m_iPreviousScreenX = 50;
		m_iCurrentScreenY = m_iPreviousScreenY = 450;
		health = 100;
		GetEngine()->Redraw(true);
	}

	
}

int PsyzkObject::getHealth() {
	return health;
}
