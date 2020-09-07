#include "header.h"

#include "PsyzkTileManager.h"
#include "PsyzkBaseEngine.h"

#include "JPGImage.h"



PsyzkTileManager::PsyzkTileManager():TileManager(50,50) // Determines Tile Size
{
}


PsyzkTileManager::~PsyzkTileManager()
{
}

// Draw a tile at a location on the screen determined by the tile
// position and the base X and Y co-ordinates
// OVERRIDE THIS TO DRAW YOUR TILE!!!
// Draw a tile
void PsyzkTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	ImageData im;
	switch (GetValue(iMapX, iMapY))
	{
	case 'a':
		im.LoadImage("resources/grasstopleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'b':
		im.LoadImage("resources/grasstopright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'c':
		/*pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			0x7EC0EE,
			pSurface);
		break;*/
		im.LoadImage("resources/grassleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'd':
		im.LoadImage("resources/grassright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'e':
		im.LoadImage("resources/grasstop.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'f':
		im.LoadImage("resources/grassbottom.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'g':
		im.LoadImage("resources/dungbackgrounddark.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'h':
		im.LoadImage("resources/grassbottomleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'i':
		im.LoadImage("resources/dungbackground.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'j':
		im.LoadImage("resources/dungbackgrounddark.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'k':
		im.LoadImage("resources/grasspathleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'l':
		im.LoadImage("resources/grasspathright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'm':
		im.LoadImage("resources/grasspathtop.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'n':
		im.LoadImage("resources/grasspathbottom.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'o':
		im.LoadImage("resources/waterbottomleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'p':
		im.LoadImage("resources/waterbottomright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'q':
		im.LoadImage("resources/watertopleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'r':
		im.LoadImage("resources/watertopright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 's':
		im.LoadImage("resources/waterleft.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 't':
		im.LoadImage("resources/waterright.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'u':
		im.LoadImage("resources/portal2.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'v':
		im.LoadImage("resources/waterbottom.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'w':
		im.LoadImage("resources/watercenter.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'x':
		im.LoadImage("resources/portal.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	case 'y':
		im.LoadImage("resources/test.png");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	}
}
