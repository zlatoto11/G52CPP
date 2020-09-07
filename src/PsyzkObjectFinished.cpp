
#include "header.h"
#include "templates.h"

#include "PsyzkObjectFinished.h"
#include "PsyzkBaseEngine.h"
#include "JPGImage.h"




PsyzkObjectFinished::PsyzkObjectFinished(BaseEngine* pEngine, int iX, int iY, bool axis) : DisplayableObject(pEngine), axis(axis)
{
	pacman1.LoadImage("resources/pacman1.png");
	pacman2.LoadImage("resources/pacman2.png");
	pacman3.LoadImage("resources/pacman3.png");
	pacman4.LoadImage("resources/pacman4.png");
	pac1.LoadImage("resources/pacman1l.png");
	pac2.LoadImage("resources/pacmanleftface.png");
	pac3.LoadImage("resources/pacman3l.png");
	pac4.LoadImage("resources/pacman4l.png");
	pacmanup.LoadImage("resources/pacmanup.png");
	pacmanup2.LoadImage("resources/pacman2up.png");
	pacmanup3.LoadImage("resources/pacman3up.png");
	pacmanup4.LoadImage("resources/pacman4up.png");
	bEngine = dynamic_cast<PsyzkBaseEngine*>(pEngine);
	// Current and previous coordinates for the object - set them the same
	//initially
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 40;
	m_iDrawHeight = 40;
	// And make it visible
	//m_iColour = GetEngine()->GetColour(rand() % 41);
	
	SetVisible(true);
}


PsyzkObjectFinished::~PsyzkObjectFinished()
{
}

void PsyzkObjectFinished::Draw()
{	
	/*PsyzkBaseEngine pBE;
	ImageData im, im2;
	im.LoadImage("resources/test2.png");
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
	/*GetEngine()->DrawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_iColour);*/
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	int time = bEngine->GetTime(); // 1 per 20ms

	int iTick = time / 200;
	//iTick += tickOffset;
	int iFrame = iTick % 4;

	
	

	if (iFrame == 0)
		if (direction == 1)
		pacman1.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
		else if (direction == 0) {
			if (!axis)
			pac1.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			else if (axis) {
				pacmanup.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			}
		}
	 if (iFrame == 1)
		 if (direction == 1)
			 pacman2.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
		 else if (direction == 0) {
			 if (!axis)
				 pac2.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 else if (axis) {
				 pacmanup2.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 }
		 }
	 if (iFrame == 2)
		 if (direction == 1)
			 pacman3.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
		 else if (direction == 0) {
			 if (!axis)
				 pac3.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 else if (axis) {
				 pacmanup3.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 }
		 }
	 if (iFrame == 3)
		 if (direction == 1)
			 pacman4.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
		 else if (direction == 0) {
			 if (!axis)
				 pac4.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 else if (axis) {
				 pacmanup4.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
			 }
		 }

	StoreLastScreenPositionForUndraw();
}

void PsyzkObjectFinished::DoUpdate(int iCurrentTIme)
{
	PsyzkTileManager& tM = dynamic_cast<PsyzkBaseEngine*>(GetEngine())->returnTileManager();
	bool isGamePaused = bEngine->getPauseValue();
	if (isGamePaused == true) {
		return;
	}

	if (direction == 0) {
		if (!axis) m_iCurrentScreenX -= 5;
		else m_iCurrentScreenY -= 5;
	}
	else if (direction == 1) {
		if(!axis)	m_iCurrentScreenX += 5;
		else m_iCurrentScreenY += 5;
	}	

	/*int random = rand() % 4;
	switch (random)
	{
	case 0:
		m_iCurrentScreenY -= 6;
		break;

	case 1:
		m_iCurrentScreenY += 6;
		break;

	case 2:
		m_iCurrentScreenX -= 6;
		break;

	case 3:
		m_iCurrentScreenX += 6;
		break;
	}*/

	if (m_iCurrentScreenX < 0) {
		m_iCurrentScreenX = 0;
		direction = 1;
	}
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth) {
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
		direction = 0;
	}
	
	if (m_iCurrentScreenY < 0) {
		m_iCurrentScreenY = 0;
		direction = 1;
	}
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


	if (tM.GetValue(iTileX1, iTileY1) == 103 || tM.GetValue(iTileX1, iTileY1) == 106) { //top collision
		//printf("\n\ncollision mofucker\n\n");
		m_iCurrentScreenY += 5;
		direction = 1;
	}
	if (tM.GetValue(iTileX2, iTileY2) == 103 || tM.GetValue(iTileX2, iTileY2) == 106) { // right collision
		m_iCurrentScreenX -= 5;
		direction = 0;
	}
	if (tM.GetValue(iTileX3, iTileY3) == 103 || tM.GetValue(iTileX3, iTileY3) == 106) { // bottom collision
		m_iCurrentScreenY -= 5;
		direction = 0;
	}
	if (tM.GetValue(iTileX4, iTileY4) == 103 || tM.GetValue(iTileX4, iTileY4) == 106) { // left collision
		m_iCurrentScreenX += 5;
		direction = 1;
	}
		
	if (m_iCurrentScreenY >= GetEngine()->GetWindowHeight() - m_iDrawHeight) {
		m_iCurrentScreenY = GetEngine()->GetWindowHeight() - m_iDrawHeight;
		direction = 1;
	}
		
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}