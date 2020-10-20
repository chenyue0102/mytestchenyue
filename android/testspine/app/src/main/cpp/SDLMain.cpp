
#define SPINE_SHORT_NAMES
#include <SDL.h>
#include "spine/spine.h"
#include "spine-sdl/spine-sdl.h"

#if defined(EMSCRIPTEN)
#include <emscripten.h>
#endif

static int done = 0;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static SDL_Texture* texture = NULL;

static spAtlas* g_spAtlas = NULL;
static spSkeletonData *g_spSkeletonData = NULL;
static spine::SkeletonDrawable *g_SkeletonDrawable = NULL;
static spine::RenderStates* g_RenderStates = NULL;
/*
On android (in SDL) relative paths point to the root of the assets dir
On desktop we are assuming that the working dir is the location of the
executable (bin/<buildtype>). So assests are in ../../assets/.
*/
#if defined(__ANDROID__) || defined(EMSCRIPTEN)
#define ASSET_PATH ""
#else
#define ASSET_PATH "../../assets/"
#endif

int init() {
    int width = 640;
    int height = 480;
    Uint32 flags = 0;

#if defined(__ANDROID__)
    flags |= SDL_WINDOW_FULLSCREEN;
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (!window) {
        SDL_Log("Creating window failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Creating renderer failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    const char* fileName = ASSET_PATH "sdl.bmp";
    SDL_Surface* bitmap = SDL_LoadBMP(fileName);
    if (!bitmap) {
        SDL_Log("Loading bitmap '%s' failed: %s", fileName, SDL_GetError());
        SDL_ClearError();
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    if (!texture) {
        SDL_Log("Creating texture failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    g_spAtlas = Atlas_createFromFile("tuzi.atlas", 0);
    g_spSkeletonData = spine::SkeletonDrawable::readSkeletonJsonData("tuzi.json", g_spAtlas, 1.0f);
    g_SkeletonDrawable = new spine::SkeletonDrawable(g_spSkeletonData);
    Skeleton* skeleton = g_SkeletonDrawable->skeleton;
    skeleton->x = 0;
    skeleton->y = 0;
    Skeleton_updateWorldTransform(skeleton);
    g_SkeletonDrawable->tryAnimation("tuzi",true,false);
    g_RenderStates = new spine::RenderStates(window, renderer);

    SDL_Log("Initialized.");
    return 1;
}

void release() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = 0;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = 0;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = 0;
    }

    SDL_Quit();
}
#if 0
void renderFrame() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}
#endif

void renderFrame(){
    float delta=0.01666666f;
    SDL_SetRenderDrawBlendMode(g_RenderStates->renderer, spine::SkeletonDrawable::sdl_blend_normal);
    {
        SDL_SetRenderDrawColor(g_RenderStates->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(g_RenderStates->renderer,NULL);
        g_SkeletonDrawable->update(delta);
        g_SkeletonDrawable->draw(g_RenderStates);
        SDL_RenderPresent(g_RenderStates->renderer);

    }
}

void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Log("Event: SDL_QUIT");
            done = 1;
        }
    }

    renderFrame();
    float delta=0.01666666f;
    SDL_Delay(delta*1000);
    //SDL_Delay(5);
}


int main(int argc, char* argv[]) {
    if (!init()) {
        SDL_Log("Initialization failed.");
        release();
        return 1;
    }

#if defined(EMSCRIPTEN)
    emscripten_set_main_loop(mainLoop, 0, 0);
    return 0;
#else
    while (!done) {
        mainLoop();
    }

    release();
    SDL_Log("All done.");
    return 0;
#endif
}
