#ifndef GRID_H
#define GRID_H

#include "Globals.h"
#include "Clip.h"

struct Grid
{
	Grid();

	void handleEvent(SDL_Event& e);
	void next();
	void reset();
	void render(SDL_Renderer* gRenderer);

	std::vector<Clip> v;

	private:
		int mInterval;
		int mPosX;
		int mPosY;
};

Grid::Grid()
{
	//TODO:
	//Temp setting before reading from file
	static const int CLIP_WIDTH = 20;
	static const int CLIP_HEIGHT = 100;
	static const int NB_CLIPS = 10;
	static const int INTERVAL = 20;

	//TODO:
	//read from file?
	
	mPosX = (SCREEN_WIDTH - (NB_CLIPS * (CLIP_WIDTH + INTERVAL))) / 2;
	mPosY = (SCREEN_HEIGHT - CLIP_HEIGHT) / 2;
	mInterval = INTERVAL;

	for(int i = 0; i < NB_CLIPS; ++i)
	{
		if(i != 0)
		{
			Clip clip(mPosX + (i * (CLIP_WIDTH + INTERVAL)), mPosY, CLIP_WIDTH, CLIP_HEIGHT);

			if(i == NB_CLIPS - 1)
			{
				clip.setSelected();
			}

			v.push_back(clip);
		}
		else
		{
			Clip clip(mPosX, mPosY, CLIP_WIDTH, CLIP_HEIGHT);
			v.push_back(clip);
		}
	}
}

void Grid::handleEvent(SDL_Event& e)
{
	//TODO:
	//change lock POS
	//update current selected clip
}

void Grid::next()
{
	//TODO:
	//move to next (left only) clip
	//if first clip -> reset pos
	
	for(std::vector<int>::size_type i = 0; i < v.size(); i++)
	{
		if(v[i].isSelected())
		{
			if(i == 0)
			{
				v[i].clearSelected();
				v.back().setSelected();
			}
			else
			{
				v[i].clearSelected();
				v[i-1].setSelected();
			}
			break;
		}
	}
}

void Grid::reset()
{
	//TODO:
	//refactor next function for
	//reset pos at the end of clips vector?
}

void Grid::render(SDL_Renderer* gRenderer)
{
	for(auto & element : v)
	{
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &element.clip);

		if(element.isSelected())
		{
			SDL_Rect select;
			select.x = element.clip.x - 10;
			select.y = element.clip.y - 15;
			select.w = element.clip.w + 20;
			select.h = element.clip.h + 30;

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRect(gRenderer, &select);
		}
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	for(int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(gRenderer, SCREEN_HEIGHT / 2, i);
	}
}

#endif
