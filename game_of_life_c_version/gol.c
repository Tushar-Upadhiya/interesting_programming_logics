#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdint.h>
#include<stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LINE_WIDTH 2
#define COLOR_GRAY 0x2f2f2f2f
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define CELL_WIDTH 30

int draw_cell(SDL_Surface* surface , int cell_x , int cell_y,int cell_value){
	int pixel_x = cell_x*CELL_WIDTH;
	int pixel_y = cell_y*CELL_WIDTH;
	uint32_t color = cell_value== 0?COLOR_BLACK:COLOR_WHITE;
	SDL_Rect cell_rect = (SDL_Rect) {pixel_x, pixel_y, CELL_WIDTH,CELL_WIDTH};
	SDL_FillRect(surface , &cell_rect,color);
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

void initialize_game_matrix(int rows , int columns,int* game_matrix ){
	for (int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			*(game_matrix + i*rows + j) = rand()%2;
		}
	}
}

void draw_game_matrix(SDL_Surface* surface,int rows , int columns, int* game_matrix){
	for(int i =0;i<rows;i++){
		for(int j =0;j<columns;j++){
			int cell_value = *(game_matrix + i*rows + j);
			draw_cell(surface,i,j,cell_value);
		}
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
	int row_count = SCREEN_HEIGHT/CELL_WIDTH;
	int column_count = SCREEN_WIDTH / CELL_WIDTH;
	int game_matrix[row_count][column_count];
	initialize_game_matrix(row_count,column_count,game_matrix[0]);
	draw_game_matrix(surface,row_count, column_count, game_matrix[0]);
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
