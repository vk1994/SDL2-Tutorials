#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture{
    public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = NULL, double angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gArrowTexture;

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

bool LTexture::loadFromFile(std::string path){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == NULL){
            printf("Unable to create texture from %s! Error: %s", path.c_str(), SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL not initialized! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Window not created! Error %s\n", SDL_GetError());
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL){
                printf("Renderer not created! Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image not initialized! Error:%s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    if(!gArrowTexture.loadFromFile("../img/arrow.png")){
        printf("Failed to load animation texture!\n");
        success = false;
    }
    return success;
}

void close(){
    gArrowTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]){
    if(!init()){
        printf("Failed to init()\n");
    } else {
        if(!loadMedia()){
            printf("Failed to loadMedia()\n");
        } else {
            bool quit = false;
            SDL_Event e;
            double degree = 0;

            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit= true;
                    } else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_a:
                            degree -= 60;
                            break;

                            case SDLK_d:
                            degree += 60;
                            break;

                            case SDLK_q:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;

                            case SDLK_w:
                            flipType = SDL_FLIP_NONE;
                            break;

                            case SDLK_e:
                            flipType = SDL_FLIP_VERTICAL;
                            break;
                        }
                    }
                } 


                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                gArrowTexture.render((SCREEN_WIDTH-gArrowTexture.getWidth())/2, (SCREEN_HEIGHT-gArrowTexture.getHeight())/2, NULL, degree, NULL, flipType);
                
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}