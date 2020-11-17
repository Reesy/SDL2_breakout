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
SDL_Texture *circle = NULL;
SDL_Rect textureRect;
SDL_Rect positionRect;

bool quit = false;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
		std::cout << "Could not load texture" << std::endl;
	}
	return texture;
}

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

	circle = loadTexture("resources/circles.png", renderer);
	
	//This rectangle represents where from the circles.png we should grab the texture. 
	//X, Y, W, H means that we grab 100 x 100 pixels from the top left of the target image (when we use SDL_RenderCopy)
	textureRect = {0, 0, 100, 100};
	
	//This represents where on the screen we will put the circle texture and it's size, 
	//this will initialise it at the top left and the image will be squished to 15 x 15
	positionRect = {0, 0, 15, 15};
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
	//clears previous frame.
	SDL_RenderClear(renderer);
	
	//Set up the circle on the next render frame.
	SDL_RenderCopy(renderer, circle, &textureRect, &positionRect);

	//Renders current frame.
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


	//When creating a native app (.exe on windows or sh on OSX/Linux this will directly call mainLoop. when running in browser emscripten deals with calls to the main method)
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
};