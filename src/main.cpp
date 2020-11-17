#include <stdio.h>
#include <string> 
#include <iostream>

#if __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#else
	#include <SDL.h>
	#include <SDL_image.h>
#endif

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event *event = NULL;

bool quit = false;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

void init()
{
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw("SDL failed to initialise");
	}


	window = SDL_CreateWindow("Breakout!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		SDL_Quit();
		throw("Failed to create window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == nullptr)
	{
		window = NULL;
		SDL_Quit();
		throw("Failed to create renderer");
	}
	event = new SDL_Event();
}

void input()
{
	if (event->type == SDL_QUIT)
	{
		quit = true;
	}

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_KP_A:
				
				break;
			case SDLK_KP_D:
				
				break;
			default:
				break;
		}
	}
}

void render()
{
	//Rendering
	SDL_RenderClear(renderer);
	//Draw the image
	//renderTexture(image, renderer, x, y, &clips[useClip]);
	//Update the screen
	SDL_RenderPresent(renderer);
}
void mainLoop()
{

	//Event Polling
	while (SDL_PollEvent(event))
	{

		input();
		render();
	}


	
}

int main(int, char**)
{
	init();

	#if __EMSCRIPTEN__
		emscripten_set_main_loop(mainLoop, -1, 1);
	#else
		while (quit != true)
		{
			mainLoop();
		}
	#endif

	SDL_DestroyRenderer(renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
