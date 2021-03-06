#include "SDL.h"
#include <stdio.h>
#include <string>

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! Error: %s\n", path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}

bool init() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL not intialized!. Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window not created!. Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("../img/press.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface("../img/up.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL ){
        printf("Failed to load up inage!\n");
        success = false;
    }
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface("../img/down.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL ) {
        printf("failed to load down image!\n");
        success = false;
    }
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface("../img/left.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL ) {
        printf("Failed to load left image!\n");
        success = false;
    }
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface("../img/right.bmp");
    if(gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL ) {
        printf("Failed to load right image!\n");
        success = false;
    }
    return success;
}

void close(){
    SDL_FreeSurface(gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ]);
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = NULL;

    SDL_FreeSurface(gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ]);
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = NULL;

    SDL_FreeSurface(gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ]);
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = NULL;

    SDL_FreeSurface(gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ]);
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = NULL;

    SDL_FreeSurface(gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ]);
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = NULL;

    gCurrentSurface = NULL;
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    bool quit = false;
    SDL_Event e;

    if(!init()){
        printf("Failed to intialize!\n");
    } else {
        if(!loadMedia()){
            printf("Failed to load media!\n");
        } else {
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    } else if(e.type == SDL_KEYDOWN) {
                        switch(e.key.keysym.sym) {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;
                        }
                    }
                }
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();

    return 0;
}