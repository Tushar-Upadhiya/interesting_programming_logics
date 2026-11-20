#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LINE_WIDTH 2
#define COLOR_GRAY 0x2f2f2f2f
#define COLOR_WHITE 0xffffffff
#define CELL_WIDTH 30

int draw_cell(SDL_Surface* surface , int cell_x , int cell_y){
	int pixel_x = cell_x*CELL_WIDTH;
	int pixel_y = cell_y*CELL_WIDTH;
	SDL_Rect cell_rect = (SDL_Rect) {pixel_x, pixel_y, CELL_WIDTH,CELL_WIDTH};
	SDL_FillRect(surface , &cell_rect,COLOR_WHITE);
}

int draw_grid(SDL_Surface* surface,int cell_width, int rows, int columns){
	for(int i =0;i<rows;i++){
		SDL_Rect line = (SDL_Rect){0,i*cell_width,SCREEN_WIDTH,LINE_WIDTH};
		SDL_FillRect(surface,&line,COLOR_GRAY);
	}
		for(int i =0;i<rows;i++){
		SDL_Rect line = (SDL_Rect){i*cell_width,0,LINE_WIDTH,SCREEN_HEIGHT};
		SDL_FillRect(surface,&line,COLOR_GRAY);
	}

}

int main(int argc, char* argv[]){
	printf("Hello conway's game of life.\n");
	int column = SCREEN_WIDTH/10;
	int rows = SCREEN_HEIGHT/10;
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
	int cell_x = 10;
	int cell_y = 6;
	draw_cell(surface , cell_x , cell_y);
	draw_grid(surface,30,rows,column);

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
