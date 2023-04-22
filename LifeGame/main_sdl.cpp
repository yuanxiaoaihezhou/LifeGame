/*
#include <SDL.h>

int main1(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("LifeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		// Ê§°Ü´¦Àí
		SDL_Log("SDLÔØÈëÊ§°Ü£º%s", SDL_GetError);
	}
    bool quit = false;
    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
*/