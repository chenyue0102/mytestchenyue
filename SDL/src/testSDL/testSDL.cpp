// testSDL.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "testSDL.h"
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

void getCurrentPath(char *path, int len)
{
	char szTmp[MAX_PATH] = { 0 };
	GetModuleFileNameA(nullptr, szTmp, _countof(szTmp));
	char *sep = strrchr(szTmp, '\\');
	if (nullptr != sep)
	{
		*sep = '\0';
	}
	strcpy(path, szTmp);
}

SDL_Texture* createTextTexture(SDL_Renderer *ren, const char *text, const char *fontFile, SDL_Color color, int pointSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile, pointSize);
	SDL_Surface *surf = TTF_RenderText_Blended(font, text, color);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return tex;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_Window *win = SDL_CreateWindow("hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	char szPath[MAX_PATH] = { 0 }, szImage[MAX_PATH] = {};
	getCurrentPath(szPath, MAX_PATH);
	strcpy(szImage, szPath);
	strcat(szImage, "/img12.jpg");
	//SDL_Surface *bmp = SDL_LoadBMP(szFile);
	//SDL_Surface *bmp = IMG_Load(szFile);
	SDL_Texture *tex = IMG_LoadTexture(ren, szImage);

	//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);

	//SDL_FreeSurface(bmp);
	//bmp = nullptr;
	char szFont[MAX_PATH] = { 0 };
	strcpy(szFont, szPath);
	strcat(szFont, "/NotoSansHans-Regular.otf");
	SDL_Color color = { 255, 0, 0 };
	SDL_Texture *tex2 = createTextTexture(ren, "hello world", szFont, color, 20);
	

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (0 != SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				quit = true;
				break;
			}
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONDOWN:
			{
				quit = true;
				break;
			}
			default:
			{
				break;
			}
			}
		}
		SDL_RenderClear(ren);
		int w = 0, h = 0;
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		SDL_Rect pos = { 0 };
		pos.w = w;
		pos.h = h;

		SDL_RenderCopy(ren, tex, nullptr, &pos);
		pos.x = 20;
		pos.y = 20;
		pos.w = 640;
		pos.h = 480;
		SDL_RenderCopy(ren, tex, nullptr, &pos);

		SDL_QueryTexture(tex2, NULL, NULL, &w, &h);
		pos.w = w;
		pos.h = h;
		SDL_RenderCopy(ren, tex2, nullptr, &pos);
		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();
	return 0;
}


