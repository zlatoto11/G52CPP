#pragma once
#include "DisplayableObject.h"

class PsyzkBaseEngine;

class PsyzkObject :
	public DisplayableObject
{
	PsyzkBaseEngine* bEngine;
public:
	PsyzkObject(BaseEngine* pEngine);
	void changeColour();
	~PsyzkObject(void);
	void Draw(void);
	void WallCollision();
	void tileManagerColission();
	void objectCollision();
	void DoUpdate(int iCurrentTime);
	int getHealth();
	int InitialiseObjects(void);

private:
	int m_iColour;
	int health;
	PsyzkObject* m_pMainEngine;
	int direction = 0;
	
};

