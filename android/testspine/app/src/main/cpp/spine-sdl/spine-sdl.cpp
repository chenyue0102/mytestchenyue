/*
 * By GeorgeChong 2018
*/
#define SPINE_SHORT_NAMES
#include <assert.h>
#include "spine-sdl.h"
#include "SDL.h"
#include "../SDL2_image/SDL_image.h"
#include "SDL_opengles.h"
#include "SDL_render.h"


static SDL_Renderer *g_SDL_Renderer = NULL;

char* _Util_readFile(const char* path, int* length) {

	char *data;
	SDL_RWops *file = SDL_RWFromFile(path, "rb");
	if (!file) return 0;

	SDL_RWseek(file, 0, SEEK_END);
	*length = (int)SDL_RWtell(file);
	SDL_RWseek(file, 0, SEEK_SET);

	data = MALLOC(char, *length);
	SDL_RWread(file, data, 1, *length);
	SDL_RWclose(file);

	return data;

}

/**/
namespace spine {
	//////////////////////////////////////////////////////
    

	SDLTexture::SDLTexture(const char *path)
		: mTexture(nullptr)
		, mWidth(0)
		, mHeight(0)
	{
		SDL_Surface* img = IMG_Load(path);
		if (img) {
			/* Replace your own SDL_Renderer here! */
			mTexture = SDL_CreateTextureFromSurface(g_SDL_Renderer, img);
			mWidth = img->w;
			mHeight = img->h;
			SDL_FreeSurface(img);
		}
		else {
			assert(false);
		}
	}

	SDLTexture::~SDLTexture() {
		if (nullptr != mTexture) {
			SDL_DestroyTexture(mTexture);
			mTexture = nullptr;
		}
	}

	int SDLTexture::width()const {
		return mWidth;
	}

	int SDLTexture::height()const {
		return mHeight;
	}

    RenderStates::RenderStates(SDL_Window* awd,SDL_Renderer* ard):window(awd),renderer(ard)
    {
        
    }
    RenderStates::~RenderStates()
    {
        
    }

	void RenderStates::setTextureBlendMode(TextureBase *texture, BlendMode mode) {
		SDLTexture *sdltexture = (SDLTexture*)texture;
		SDL_BlendMode blend;
		if (mode & BLENDMODE_PMA) {
			switch (mode & BLENDMODE_MASK) {
			case BLENDMODE_NORMAL:
				blend = SkeletonDrawable::sdl_blend_normalPma;
				break;
			case BLENDMODE_ADDITIVE:
				blend = SkeletonDrawable::sdl_blend_additivePma;
				break;
			case BLENDMODE_MULTIPLY:
				blend = SkeletonDrawable::sdl_blend_multiplyPma;
				break;
			case BLENDMODE_SCREEN:
				blend = SkeletonDrawable::sdl_blend_screenPma;
				break;
			default:
				blend = SkeletonDrawable::sdl_blend_normalPma;
				break;
			}
		}
		else {
			switch (mode & BLENDMODE_MASK) {
			case BLENDMODE_NORMAL:
				blend = SkeletonDrawable::sdl_blend_normal;
				break;
			case BLENDMODE_ADDITIVE:
				blend = SkeletonDrawable::sdl_blend_additive;
				break;
			case BLENDMODE_MULTIPLY:
				blend = SkeletonDrawable::sdl_blend_multiply;
				break;
			case BLENDMODE_SCREEN:
				blend = SkeletonDrawable::sdl_blend_screen;
				break;
			default:
				blend = SkeletonDrawable::sdl_blend_normal;
				break;
			}
		}
		SDL_SetTextureBlendMode(sdltexture->mTexture, blend);
	}

	void RenderStates::draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray) {
		unsigned int firstVertex = 0;
		std::size_t vertexCount = vertexArray->size();
		if (vertexCount == 0)
			return;//Nothing to draw

		//set BLEND MODE
		if (texture)
		{
			setTextureBlendMode(texture, blendMode);
		}

		const char* src_data = reinterpret_cast<const char*>(vertexArray->data());

		SDL_RenderCopySpine(renderer, ((SDLTexture*)texture)->mTexture, type, sizeof(Vertex), firstVertex, (unsigned int)vertexCount, src_data);
	}

	SDL_BlendMode SkeletonDrawable::sdl_blend_normal = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_SRC_ALPHA,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_SRC_ALPHA,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD);

	SDL_BlendMode SkeletonDrawable::sdl_blend_additive = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_SRC_ALPHA,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_SRC_ALPHA,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDOPERATION_ADD);

	SDL_BlendMode SkeletonDrawable::sdl_blend_multiply = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_DST_COLOR,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_DST_COLOR,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD);

	SDL_BlendMode SkeletonDrawable::sdl_blend_screen = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
		SDL_BLENDOPERATION_ADD);

	SDL_BlendMode SkeletonDrawable::sdl_blend_normalPma = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD);
	SDL_BlendMode SkeletonDrawable::sdl_blend_additivePma = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDOPERATION_ADD);
	SDL_BlendMode SkeletonDrawable::sdl_blend_multiplyPma = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_DST_COLOR,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDOPERATION_ADD);

	SDL_BlendMode SkeletonDrawable::sdl_blend_screenPma = SDL_ComposeCustomBlendMode(
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
		SDL_BLENDOPERATION_ADD,
		SDL_BLENDFACTOR_ONE,
		SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
		SDL_BLENDOPERATION_ADD);




	void SkeletonDrawable::onListenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
		switch (type)
		{
		case SP_ANIMATION_START:
		{

		}
		break;
		case SP_ANIMATION_COMPLETE:
		{

		}
		break;
		default:

			break;
		}
	}

	TextureBase* SkeletonDrawable::createTexture(const char *path) {
		SDLTexture *texture = new SDLTexture(path);

		if (0 == texture->width() || 0 == texture->height()) {
			delete texture;
			return nullptr;
		}
		else {
			return texture;
		}
	}
    
	void setRender(SDL_Renderer * render)
	{
		g_SDL_Renderer = render;
	}

} /* namespace spine */
