#include "header.h"
#include "templates.h"
#include "PsyzkObjectDiff.h"





PsyzkObjectDiff::PsyzkObjectDiff(BaseEngine* pEngine, int iX, int iY) :DisplayableObject(pEngine)
{
	bEngine = dynamic_cast<PsyzkBaseEngine*>(pEngine);
	im.LoadImage("resources/brick1.png");
	// Current and previous coordinates for the object - set them the same
	//initially
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);

}


PsyzkObjectDiff::~PsyzkObjectDiff()
{
}

void PsyzkObjectDiff::Draw() {
	PsyzkBaseEngine pBE;
	
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void PsyzkObjectDiff::DoUpdate(int iCurrentTime) {
	PsyzkTileManager& tM = dynamic_cast<PsyzkBaseEngine*>(GetEngine())->returnTileManager();
	bool isGamePaused = bEngine->getPauseValue();
	if (isGamePaused == true) {
		return;
	}

	int random = rand() % 4;
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
	}

	if (m_iCurrentScreenX < 0) {
		m_iCurrentScreenX = 0;
	}
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth) {
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
	}

	if (m_iCurrentScreenY < 0) {
		m_iCurrentScreenY = 0;
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
	}
	if (tM.GetValue(iTileX2, iTileY2) == 103 || tM.GetValue(iTileX2, iTileY2) == 106) { // right collision
		m_iCurrentScreenX -= 5;
	}
	if (tM.GetValue(iTileX3, iTileY3) == 103 || tM.GetValue(iTileX3, iTileY3) == 106) { // bottom collision
		m_iCurrentScreenY -= 5;
	}
	if (tM.GetValue(iTileX4, iTileY4) == 103 || tM.GetValue(iTileX4, iTileY4) == 106) { // left collision
		m_iCurrentScreenX += 5;
	}

	if (m_iCurrentScreenY >= GetEngine()->GetWindowHeight() - m_iDrawHeight) {
		m_iCurrentScreenY = GetEngine()->GetWindowHeight() - m_iDrawHeight;
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();

}