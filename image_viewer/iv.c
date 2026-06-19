#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
int main(){
    SDL_setenv("SDL_VIDEODRIVER", "x11", 1);
    //initialized the window pointer
    const int width = 900;
    const int height = 600;
    SDL_Window* window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    Uint8 r,g,b;
    r = 0xFF;
    g = b = 0;
    Uint32 color = SDL_MapRGB(surface-> format,r,g,b);
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    for(int x =0;x<width;x++){
        for (int y =0;y<height;y++){
            pixel.x = x;
            pixel.y = y;
             SDL_FillRect(surface,&pixel,color);
            
        }
    }
       SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    return 0;
}

