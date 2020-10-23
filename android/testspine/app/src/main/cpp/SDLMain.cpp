
#include <SDL.h>
#include <assert.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
//#define SPINE_SHORT_NAMES
#include "spine/spine.h"
#include "spine-sdl/spine-sdl.h"
#include "spine-sdl/SpineOpenGLES.h"


#if defined(EMSCRIPTEN)
#include <emscripten.h>
#endif

#ifdef WIN32
#include <direct.h>
#endif

static int done = 0;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static SDL_Texture* texture = NULL;

static spAtlas* g_spAtlas = NULL;
static spSkeletonData *g_spSkeletonData = NULL;
static spine::SkeletonDrawable *g_SkeletonDrawable = NULL;
static spine::RenderStates* g_RenderStates = NULL;

static spine::SkeletonDrawableOpenGLES *g_SkeletonDrawable2 = NULL;
static spine::RenderOpenGLES *g_RenderStates2 = NULL;
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
    int width = 800;
    int height = 600;
    Uint32 flags = 0;

#if defined(__ANDROID__)
    flags |= SDL_WINDOW_FULLSCREEN;
#elif WIN32
	flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
#endif


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");// easy to be extended to other drivers,Follow the "How to Extend" section below



    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        SDL_Log("Creating window failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }
#ifdef WIN32
	int index = 2;//使用OPENGL
#else
	int index = -1;
#endif
    renderer = SDL_CreateRenderer(window, index, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Creating renderer failed: %s", SDL_GetError());
        SDL_ClearError();
        return 0;
    }
#ifdef WIN32
	char szTmp[256] = { 0 };
	_getcwd(szTmp, 256);
	strcat(szTmp, "/../../assets/sdl.bmp");
    const char* fileName = szTmp;
#else
	const char* fileName = ASSET_PATH "sdl.bmp";
#endif
#if 0
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
#endif
#ifdef WIN32
	_getcwd(szTmp, 256);
	strcat(szTmp, "/../../assets/alien.atlas");
	const char *spineboy_atlas = szTmp;
	char szTmp2[256];
	_getcwd(szTmp2, 256);
	strcat(szTmp2, "/../../assets/alien.json");
	const char *spineboy_json = szTmp2;
#else
	const char *spineboy_atlas = "tuzi.atlas";
	const char *spineboy_json = "tuzi.json";
#endif
	spine::setRender(renderer);
    //g_spAtlas = Atlas_createFromFile(spineboy_atlas, 0);
    //g_spSkeletonData = spine::SkeletonDrawable::readSkeletonJsonData(spineboy_json, g_spAtlas, 0.6f);
    
	g_SkeletonDrawable = new spine::SkeletonDrawable();
	g_SkeletonDrawable->create(spineboy_atlas, spineboy_json);

	spSkeleton* skeleton = g_SkeletonDrawable->skeleton;
	skeleton->x = 500;
	skeleton->y = 500;
	spSkeleton_updateWorldTransform(skeleton);
	g_SkeletonDrawable->tryAnimation("death", true, true);

	//初始化 glew wglMakeCurrent
	GLenum status = glewInit();
	assert(GLEW_OK == status);

	g_SkeletonDrawable2 = new spine::SkeletonDrawableOpenGLES();
	g_SkeletonDrawable2->create(spineboy_atlas, spineboy_json);

	spSkeleton* skeleton2 = g_SkeletonDrawable2->skeleton;
	skeleton2->x = 500;
	skeleton2->y = 500;
	spSkeleton_updateWorldTransform(skeleton2);
	g_SkeletonDrawable2->tryAnimation("death", true, true);

    
    g_RenderStates = new spine::RenderStates(window, renderer);

	SDL_SetRenderDrawBlendMode(g_RenderStates->renderer, spine::SkeletonDrawable::sdl_blend_normal);

	g_RenderStates2 = new spine::RenderOpenGLES();
	g_RenderStates2->setViewWidth(800);
	g_RenderStates2->setViewHeight(600);
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
	SDL_RenderClear(renderer);
    {
        //SDL_SetRenderDrawColor(g_RenderStates->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(g_RenderStates->renderer,NULL);
        g_SkeletonDrawable->update(delta);
		g_SkeletonDrawable2->update(delta);
        //g_SkeletonDrawable->draw(g_RenderStates);
		g_SkeletonDrawable2->draw(g_RenderStates2);
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
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//glutCreateWindow("OpenGL 程序");
	auto v = glGetString(GL_VERSION);
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	printf("OpenGL Version=%s texturemaxsize=%d\n", v, max);

	/*GLuint tex = -1;
	glGenTextures(1, &tex);
	GLuint program = glCreateProgram();
	GLuint buf = -1;
	glGenBuffers(1, &buf);
	GLuint vertex = -1;
	glGenVertexArrays(1, &vertex);*/

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
