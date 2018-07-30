#ifndef DOT_H
#define DOT_H

#include "Globals.h"
#include "LTexture.h"
#include "Physics.h"

struct Dot
{
	// Dimensions.
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	// Velocity.
	static const int DOT_VEL = 5;

	Dot();

	void handleEvent(SDL_Event& e);
	//void move(SDL_Rect& wall);
	void move();
	void render(int camX, int camY, LTexture& gDotTexture, SDL_Renderer* gRenderer);

	// Position accessors.
	int getPosX();
	int getPosY();

	private:
		// X and Y offsets of the dot.
		int mPosX, mPosY;
		// Velocity of the dot.
		int mVelX, mVelY;
		// Dot's collision boxe
		SDL_Rect mCollider;
};

Dot::Dot()
{
	// Init the offsets
	mPosX = 0;
	mPosY = 0;

	// Set collision boxe dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

	// Init the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
	// if a key was pressed.
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// adjust velocity.
		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
				mVelY -= DOT_VEL;
				break;
			case SDLK_DOWN:
				mVelY += DOT_VEL;
				break;
			case SDLK_LEFT:
				mVelX -= DOT_VEL;
				break;
			case SDLK_RIGHT:
				mVelX += DOT_VEL;
				break;
		}
	}
	// if a key was released.
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
				mVelY += DOT_VEL;
				break;
			case SDLK_DOWN:
				mVelY -= DOT_VEL;
				break;
			case SDLK_LEFT:
				mVelX += DOT_VEL;
				break;
			case SDLK_RIGHT:
				mVelX -= DOT_VEL;
				break;
		}
	}
}

//void Dot::move(SDL_Rect& wall)
void Dot::move()
{
	// Move the dot left or right.
	mPosX += mVelX;
	//mCollider.x = mPosX;

	// If the dot went too far to the left or right.
	//if((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || Physics::checkCollision(mCollider, wall))
	if((mPosX < 0) || (mPosX + DOT_WIDTH > LEVEL_WIDTH))
	{
		// Move back.
		mPosX -= mVelX;
		//mCollider.x = mPosX;

		//std::cout << "x=" << mPosX << std::endl;
	}

	// Move up or down.
	mPosY += mVelY;
	//mCollider.y = mPosY;

	// If the dot went too far up or down.
	//if((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || Physics::checkCollision(mCollider, wall))
	if((mPosY < 0) || (mPosY + DOT_HEIGHT > LEVEL_HEIGHT))
	{
		// Move back
		mPosY -= mVelY;
		//mCollider.y = mPosY;

		//std::cout << "y=" << mPosY << std::endl;
	}
}

void Dot::render(int camX, int camY, LTexture& gDotTexture, SDL_Renderer* gRenderer)
{
	gDotTexture.render(mPosX - camX, mPosY - camY, gRenderer);
}

int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
}

#endif
