#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "LTexture.h"
#include "LButton.h"
#include "LTimer.h"
#include "Dot.h"
#include "Grid.h"

struct Game
{
	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;

	//Globally used font
	TTF_Font *gFont;

	//Scene textures
	LTexture gFPSTextTexture;

	Game();

	bool init();
	bool loadMedia();
	void close();

	void run();
};

Game::Game()
{
	gRenderer = NULL;
	gWindow = NULL;

	//Globally used font
	gFont = NULL;
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("la famillia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("asset/Roboto-Light.ttf", 20);
	if(gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	// ============================================================================
	
	return success;
}

void Game::close()
{
	//Free loaded image
	gFPSTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy renderer / window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;
	gWindow = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::run()
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = {0, 0, 0, 255};

			//The application timer
			LTimer fpsTimer;

			//The frames per second timer
			LTimer capTimer;

			//In memory text stream
			std::stringstream timeText;

			int countedFrames = 0;
			fpsTimer.start();

			//Init clip grid
			Grid grid;

			//While application is running
			while( !quit )
			{
				//Start cap timer
				capTimer.start();

				bool goNextClip = false;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_LEFT:
								goNextClip = true;
								break;
						}
					}
				}

				/*******************
				 * FPS CALCULATING.*
				 *******************/
				
				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if(avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				//Set text to be rendered
				timeText.str("");
				timeText << "FPS: " << avgFPS;

				//Render text
				if(!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gFont, gRenderer))
				{
					printf("Unable to render FPS texture!\n");
				}

				/***********************
				 * UPDATE SELECTED CLIP*
				 ***********************/
				if(goNextClip)
				{
					grid.next();
				}

				/**********
				 * RENDER.*
				 **********/

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				
				//Render fps textures
				gFPSTextTexture.render((SCREEN_WIDTH - gFPSTextTexture.getWidth()), 0, gRenderer);

				//TODO:
				//Render grid with clips
				grid.render(gRenderer);
				
				//Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if(frameTicks < SCREEN_TICK_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
				}
			}
		}
	}

	//Free resources and close SDL
	close();
}

#endif
