/*
 * By GeorgeChong 2018
*/
#ifndef SPINE_SDL_H
#define SPINE_SDL_H
#define SPINE_SHORT_NAMES
#include "spine/spine.h"
#include "spine/extension.h"
#include "SDL.h"
#include "SpineBase.h"
#include <string>
#include <vector>

#ifdef __IPHONEOS__
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#elif WIN32

#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif



struct SDL_Renderer;
typedef SDL_Texture Texture;
typedef SDL_Color Color;

namespace spine {



	///////////////////////////////////////////////////////////////////
	class SDLTexture : public TextureBase {
	public:
		SDLTexture(const char *path);
		virtual ~SDLTexture();
	public:
		virtual int width()const;
		virtual int height()const;
	public:
		SDL_Texture *mTexture;
		int mWidth;
		int mHeight;
	};

	class RenderStates : public RenderBase
	{
	public:
		RenderStates(SDL_Window* awindow, SDL_Renderer* arenderer);
		~RenderStates();

	public:
		virtual void draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray);

	private:
		void setTextureBlendMode(TextureBase *texture, BlendMode mode);
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
	};

        
	class SkeletonDrawable : public SkeletonDrawableBase {
     
	public:
        static SDL_BlendMode sdl_blend_normal;
        static SDL_BlendMode sdl_blend_additive;
        static SDL_BlendMode sdl_blend_multiply;
        static SDL_BlendMode sdl_blend_screen;
     
        static SDL_BlendMode sdl_blend_normalPma;
        static SDL_BlendMode sdl_blend_additivePma;
        static SDL_BlendMode sdl_blend_multiplyPma;
        static SDL_BlendMode sdl_blend_screenPma;

     
        public:
			virtual TextureBase* createTexture(const char *path);

 protected:
	 virtual void onListenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event);
            
            //static SkeletonData* readSkeletonJsonData (const char* filename, Atlas* atlas, float scale) ;
     
            //static SkeletonData* readSkeletonBinaryData (const char* filename, Atlas* atlas, float scale);
        };
 void setRender(SDL_Renderer *render);
    } /* namespace spine */

#endif
