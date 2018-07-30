#ifndef PHYSICS_H
#define PHYSICS_H

#include "Globals.h"

struct Physics
{
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
};

bool Physics::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The side of the rectangle
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of sides from A are outside of B
	if(bottomA <= topB)
	{
		//std::cout << "(bottomA)=" << bottomA << " <= (topB)->" << topB << std::endl;
		return false;
	}

	if(topA >= bottomB)
	{
		//std::cout << "(topA)=" << topA << " >= (bottomB)->" << bottomB << std::endl;
		return false;
	}

	if((rightA) <= leftB)
	{
		//std::cout << "(rightA)->" << rightA << " <= (leftB)->" << leftB << std::endl;
		return false;
	}

	if(leftA >= rightB)
	{
		//std::cout << "(leftA)->" << leftA << " >= (rightB)->" << rightB << std::endl;
		return false;
	}

	//std::cout << "[]collision[]" << std::endl;

	//If none of the sides from A are outside B
	return true;
}

#endif
