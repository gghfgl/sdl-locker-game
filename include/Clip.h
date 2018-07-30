#ifndef CLIP_H
#define CLIP_H

#include "Globals.h"

enum CLIP_LOCK_POS
{
	LOCK_POS_UP = 0,
	LOCK_POS_MID = 1,
	LOCK_POS_DOWN = 3
};

struct Clip
{
	Clip(int x, int y, int w, int h);

	//void updateLockPosition();
	void setSelected();
	void clearSelected();
	bool isSelected();

	SDL_Rect clip;

	private:
		CLIP_LOCK_POS mCurrentLockPos;
		bool mSelected;
};

Clip::Clip(int x, int y, int w, int h)
{
	clip.x = x;
	clip.y = y;
	clip.w = w;
	clip.h = h;

	//Just UP pos for test
	mCurrentLockPos = LOCK_POS_UP;
	mSelected = false;
}

void Clip::setSelected()
{
	if(!mSelected)
	{
		mSelected = true;
	}
}

void Clip::clearSelected()
{
	if(mSelected)
	{
		mSelected = false;
	}
}


bool Clip::isSelected()
{
	return mSelected;
}

#endif
