#include "SDL.h"
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL not initialized. Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Window not created. Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    gHelloWorld = SDL_LoadBMP("../preview.bmp");
    if(gHelloWorld == NULL) {
        printf("Unable to load image %s .Error: %s\n", "preview.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close(){
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

int main(int argc, char* argv[]){
    bool quit = false;
    SDL_Event event;

    if(!init()){
        printf("Failed to initialize!\n");
    } else {
        if(!loadMedia()){
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            while(!quit){
                SDL_WaitEvent(&event);

                switch(event.type){
                    case SDL_QUIT:
                    quit = true;
                    break;
                }
            }
        }
    }
    close();
    return 0;
}