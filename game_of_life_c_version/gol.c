#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[]){
	printf("Hello conway's game of life.\n");
	SDL_Window *window = NULL;

	//initializing SDL window
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL_Init failed: %s\n",SDL_GetError());

		return 1;
	}

		//create the window
	window = SDL_CreateWindow(
        "My Game",                        // title
        SDL_WINDOWPOS_CENTERED,           // x
        SDL_WINDOWPOS_CENTERED,           // y
        SCREEN_WIDTH,                     // width
        SCREEN_HEIGHT,                    // height
        0                  // flags
    );
	 if (!window) {
        printf("CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

	
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Rect rect = (SDL_Rect){30,40,50,60};
	uint32_t color = 0xffffffff;
	SDL_FillRect(surface, &rect , color);
	 SDL_UpdateWindowSurface(window);

	SDL_Event event;
    	int running = 1;
    	while (running) {
        	while (SDL_PollEvent(&event)) {
            		if (event.type == SDL_QUIT) running = 0;
        				}
        	SDL_Delay(10);
    	}

    	SDL_DestroyWindow(window);
   	 SDL_Quit();

	return 0;
}
