#pragma once
#include "TileManager.h"
class PsyzkTileManager :
	public TileManager
{
public:
	PsyzkTileManager();
	~PsyzkTileManager();
	void DrawTileAt(BaseEngine * pEngine, SDL_Surface * pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const;
	void DrawTileAt(BaseEngine * pEngine, SDL_Surface * pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY);
};

