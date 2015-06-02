#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include <BASS.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>

// create window and set video mode
extern int screenW;
extern int screenH;
extern SDL_Surface* screen;
extern SDL_Surface* display;
extern SDL_Rect camera;
//extern HSTREAM* musicStream;

#include "soundmanager.h"
extern cSoundManager g_SoundManager;


#include "texturemanager.h"
extern cTextureManager g_TextureManager;

// placeholder until figure out how to remove cSprite dependency on g_TextureManager
extern cTextureManager g_TextureManager2;

#include "renderobject.h"
#include "rendermanager.h"

#include "sprite.h"

#include "inputmanager.h"
extern cInputManager g_InputManager;

#include "levelmanager.h"
#include "rules.h"
extern cSpriteManager g_SpriteManager;
extern cInputManager g_InputManager;
extern cRenderManager g_RenderManager;
extern cLevelManager g_LevelManager;
//extern cLevelManager g_DemoLevelManager;

#include "menu.h"


#endif
