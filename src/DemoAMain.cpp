#include "header.h"
#include "templates.h"

#include "DemoAMain.h"
#include "DemoBObject.h"



DemoAMain::DemoAMain()
{
}


DemoAMain::~DemoAMain()
{
}


void DemoAMain::SetupBackgroundBuffer(void) // DRAW SOMETHING HERE FOR THE COURSEWORK BACKGROUND ( HOUSE MAYBE TREE W/E)
{
	FillBackground(0xff0000);

	for (int iX = 0; iX < GetWindowWidth(); iX++)
		for (int iY = 0; iY < this->GetWindowHeight(); iY++)
			switch (rand() % 100)
			{
			case 0: SetBackgroundPixel(iX, iY, 0xFF0000); break;	//Goes through each pixel horrizontally and verticaly and sets 
			case 1: SetBackgroundPixel(iX, iY, 0x00FF00); break;	//it to a color based on rand % 100
			case 2: SetBackgroundPixel(iX, iY, 0x0000FF); break;	//http://www.cs.nott.ac.uk/~pszja/cpp1718/coursework/CW3_LabA_v1.pdf
			case 3: SetBackgroundPixel(iX, iY, 0xFFFF00); break;
			case 4: SetBackgroundPixel(iX, iY, 0x00FFFF); break;
			case 5: SetBackgroundPixel(iX, iY, 0xFF00FF); break;
			}

}
/*
Basically, a
Redraw(true) will redraw the background (the original thing which we drew in the
SetupBackgroundBuffer function), and will overwrite everything that we draw onto the
foreground. This can be really useful, but can also be really confusing until you understand it.
*/

/*
1) If you are drawing a stationary/unchanging item them draw it to the background, otherwise
it will be eliminated when you redraw the screen.
2) If you are drawing a moving object then draw it to the foreground – you WANT it to be
removed when you redraw the screen, to remove it from the old position on the screen. 
*/
void DemoAMain::MouseDown(int iButton, int iX, int iY)
{
	printf("%d %d\n", iX, iY); //Prints out location of rectangle drawn
	if (iButton == SDL_BUTTON_LEFT) { // SDL_BUTTON_LEFT refers to left mouse click
		//DrawRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xffff00);	//Draw to foreground (will be removed on redraw)
		DrawBackgroundRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xffff00);//Drawn to background, not removed on redraw
		Redraw(true); 
		//Essentially have 2 copies of the screen ,background and foreground (background is constant)
	}
	else if (iButton == SDL_BUTTON_RIGHT)
	{
		//DrawOval(iX - 10, iY - 10, iX + 10, iY + 10, 0xff0000);
		DrawBackgroundOval(iX - 10, iY - 10, iX + 10, iY + 10, 0xffff00); //Drawn to background , not removed on redraw
		//Redraw(false);
		Redraw(true); //Redraw true will remove background and overwrite everything we have drawn to the foreground.
	}
}

void DemoAMain::KeyDown(int iKeyCode) // Basically redraws background when you press spacebar
{
	switch (iKeyCode) // Keycode is key press
	{
	case SDLK_SPACE: // Refers to space bar
		SetupBackgroundBuffer(); //Calls the background function
		Redraw(true);
		break;
	}
}

int DemoAMain::InitialiseObjects(void)
{
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
		DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(2);
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
		// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
		//order to work out where the end of the array is.
		StoreObjectInArray(0, new DemoBObject(this));
	StoreObjectInArray(1, NULL);
	return 0;
}