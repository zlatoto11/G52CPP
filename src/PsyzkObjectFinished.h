#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class PsyzkBaseEngine;

class PsyzkObjectFinished :
	public DisplayableObject
{
	PsyzkBaseEngine* bEngine;
public:
	PsyzkObjectFinished();
	PsyzkObjectFinished(BaseEngine * pEngine, int iX, int iY, bool axis);
	~PsyzkObjectFinished();
	void Draw();
	void DoUpdate(int iCurrentTIme);
	ImageData pacman1, pacman2, pacman3, pacman4, pac1, pac2, pac3, pac4, pacmanup, pacmanup2, pacmanup3, pacmanup4;
private:
	int m_iColour;
	int direction = 0;
	bool axis;
	
};

