#pragma once
#include "header.h"
#include "DisplayableObject.h"

#include "templates.h"

#include "PsyzkObjectFinished.h"
#include "PsyzkBaseEngine.h"
#include "JPGImage.h"

class PsyzkBaseEngine;

class PsyzkObjectDiff :
	public DisplayableObject
{
	PsyzkBaseEngine* bEngine;
public:
	~PsyzkObjectDiff(void);
	PsyzkObjectDiff(BaseEngine * pEngine, int iX, int iY);
	void Draw();
	void DoUpdate(int iCurrentTime);
private:
	ImageData im, im2;
};

