#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "PsyzkTileManager.h"


class PsyzkBaseEngine :
	public BaseEngine
{
	bool isPaused;
public:
	PsyzkBaseEngine();
	~PsyzkBaseEngine();
	void SetupBackgroundBuffer(void);
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
	void DrawTextToScreen();
	void DrawTextToForegroundScreen();
	PsyzkTileManager & returnTileManager();
	bool getPauseValue();
	int InitialiseObjects();
	

private:PsyzkTileManager m_oTiles;
};

