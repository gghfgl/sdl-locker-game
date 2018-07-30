#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDl2/SDL.h>
#include <SDL2_Image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

//DEBUG
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int TOTAL_DATA = 10;

#endif
