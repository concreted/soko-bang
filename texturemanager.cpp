#include "engine.h"
#include "texturemanager.h"

extern cTextureManager g_TextureManager;

void initTextureManager()
{
    g_TextureManager2.loadSurface("title.bmp");
    g_TextureManager2.loadSurface("tiles.bmp");
    g_TextureManager2.loadSurface("numbers.bmp");
    g_TextureManager2.loadSurface("fail.bmp");

    SDL_SetColorKey(g_TextureManager2.getSurface(0), SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);
}
