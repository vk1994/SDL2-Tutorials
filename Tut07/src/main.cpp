#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(std::string path);
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init(){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL not initialized! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            printf("Warning: Linear texture filtering not enables!");
        }

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Window not created! Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL){
                printf("Renderer not created! Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image not initialized! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    gTexture = loadTexture("../img/texture.png");
    if(gTexture == NULL){
        printf("Failed to load texture image!\n");
        success = false;
    }
    return success;
}

void close(){
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL){
            printf("Unable to create texture from %s! SDL_image Error %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

int main(int argc, char* argv[]){
    if(!init()){
        printf("Failed to initialize!\n");
    } else {
        if(!loadMedia()){
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                }
                SDL_RenderClear(gRenderer);
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}