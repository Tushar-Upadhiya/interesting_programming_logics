#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
int main(){
    SDL_setenv("SDL_VIDEODRIVER", "x11", 1);
    //initialized the window pointer
    FILE* in = stdin;
    char* throwaway = calloc(1000,sizeof(char));
    //Read first line (specifier P3 or P6 - ignore here)
    fgets(throwaway,1000,in);
    //Read second line (comment)
      fgets(throwaway,1000,in);
      
    
    //Read third line(dimensions: width/height)
        
    char* dimensions = calloc(1000,sizeof(char));
    fgets(dimensions,1000,in);

    //Read fourth line(max color value - ignore it)
       fgets(throwaway,1000,in);
     free(throwaway);
    int width=-1 ;
    int height=-1 ;
    sscanf(dimensions,"%d %d\n",&width,&height);
    printf("width: %d  height: %d",width,height );
    free(dimensions);
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

