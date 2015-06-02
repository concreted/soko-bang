#ifndef MAIN_C
#define MAIN_C

#include <SDL/SDL.h>
#include "engine.h"

int screenW = levelSize * 40;
int screenH = levelSize * 40;

SDL_Rect camera; //= {0, 0, screenW, screenH};


const int fps = 60;

cTextureManager g_TextureManager;
cTextureManager g_TextureManager2;
cRenderManager g_RenderManager;
cLevelManager g_LevelManager("LevelManager");
//cLevelManager g_DemoLevelManager("DemoLevelManager");
cSoundManager g_SoundManager;
cInputManager g_InputManager;
cSpriteManager g_SpriteManager;

SDL_Surface* screen = SDL_SetVideoMode(screenW,screenH,16,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_Surface* display = SDL_CreateRGBSurface(SDL_SWSURFACE, 1000, 1000, 32, 0, 0, 0, 0);
//SDL_Rect camera(0,0,200,200);


int tick = SDL_GetTicks();
int gLastTick = 0;

bool fastMovement = true;

bool won = false;

int startScreen()
{
    initDemoLevelManager();
    clearHUD();
    SDL_Surface* title = g_TextureManager2.getSurface(0);

    SDL_Rect destRct;
    destRct.x = 0;
    destRct.y = 0;
    destRct.w = 250;
    destRct.h = 250;

    g_SoundManager.startStream(3);

    cMenu mainMenu("menu.bmp",3,18,150);
    mainMenu.enableColorKey();
    mainMenu.m_XPos = screenW - mainMenu.width() - mainMenu.m_Size;
    mainMenu.m_YPos = 5;

    //loadLevel(g_DemoLevelManager, 0);
    loadLevel(g_LevelManager, 0);

    bool done = false;
    int moveStartTime = SDL_GetTicks();

    while(!done)
    {
        int startTime = SDL_GetTicks();

        if(mainMenu.selected())
        {
            switch(mainMenu.selection())
            {
                case 0:
                    g_SoundManager.stop();
                    g_LevelManager.autoPlayOff();


                    done = true;
                    break;
                case 1:
                    g_SoundManager.stop();
                    g_LevelManager.autoPlayOn();


                    done = true;
                    break;
                default:
                    done = true;
                    break;
            }
            return mainMenu.selection();
        }

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            //check for messages
            switch(event.type)
            {
                case SDL_QUIT:
                    done = true;
                    //return done;
                    break;
                //check for keypresses
                case SDL_KEYDOWN:
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    else
                        mainMenu.updateKey(event.key.keysym.sym);
                    break;
                }
            } //end switch
        } //end of message processing

        //do game update

        //autoplay routine (if level autoplay enabled)
        if(g_LevelManager.activeLevel()->autoPlay())
        {
            if(g_LevelManager.activePlayer()->moveNumber() < g_LevelManager.activePlayer()->movesSize())
            {
                int moveCheckTime = SDL_GetTicks();
                if(moveCheckTime - moveStartTime >= 300)
                {
                    g_InputManager.update();
                    moveStartTime = moveCheckTime;
                }
            }
        }

        g_InputManager.autoUpdate();

        /*****update graphics*****/

            //clear screen
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,0,0));

        //draw image

        g_RenderManager.update();
        SDL_BlitSurface(title,0,screen,&destRct);
        mainMenu.update(screen);

        //end frame

        int endTime = SDL_GetTicks();

        if(endTime - startTime < 1000/fps) SDL_Delay(1000/fps - (endTime - startTime));

        SDL_Flip(screen);

        g_LevelManager.checkWin();

        //if(g_DemoLevelManager.activeLevel()->won())
            //return 3;

        //update input
    }
    return -1;
    //do exit
}

int showScreen(int i, int j)
{
    SDL_Surface* title = g_TextureManager2.getSurface(i);

    SDL_Rect destRct;
    destRct.x = 0;
    destRct.y = 0;
    destRct.w = 640;
    destRct.h = 640;

    g_SoundManager.startStream(j);

    bool done = false;
    while(!done)
    {
        int startTime = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            //check for messages
            switch(event.type)
            {
                case SDL_QUIT:
                case SDLK_ESCAPE:
                    g_SoundManager.stopStream(j);
                    done = true;
                    return cLevel::EXIT;
                    break;
                //check for keypresses
                case SDL_KEYDOWN:
                {
                    //handle keypresses
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_r:
                        {
                            g_SoundManager.stopStream(j);
                            done = true;
                            return cLevel::RESTART;
                        }
                            break;
                        case SDLK_RETURN:
                        {
                            g_SoundManager.stopStream(j);
                            done = true;
                            return cLevel::END;
                        }
                            break;
                        case SDLK_ESCAPE:
                            g_SoundManager.stopStream(j);
                            done = true;
                            return cLevel::EXIT;
                            break;
                        default:
                            break;
                    }
                    break;
                }
            } //end switch
        } //end of message processing

        //do game update

        /*****update graphics*****/

        //clear screen
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,0,0));

        //draw image
        SDL_BlitSurface(title,0,screen,&destRct);

        //end frame

        int endTime = SDL_GetTicks();

        if(endTime - startTime < 1000/fps) SDL_Delay(1000/fps - (endTime - startTime));

        SDL_Flip(screen);
        //update input
    }

    //do exit
}

bool gameLoop()
{
    initLevelManager();
    loadLevel(g_LevelManager, 0);
    initHUD();
    bool done = false;
    int moveStartTime = SDL_GetTicks();

    while(!done)
    {
        int startTime = SDL_GetTicks();
        // handle game lose situation (timer has run out, eaten by monster)
        // now handled in cLevelManager::update()


        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            //check for messages
            switch(event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                //check for keypresses
                case SDL_KEYDOWN:
                {
                    //handle keypresses
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            g_LevelManager.stop();
                            done = true;
                            return true;
                            break;
                        case SDLK_m:
                            g_LevelManager.stop();
                            done = true;
                            return false;
                            break;
                        case SDLK_r:
                            g_LevelManager.endLevel();
                            moveStartTime = SDL_GetTicks();
                            loadLevel(g_LevelManager, g_LevelManager.getCurrentLevel());
                            break;
                        case SDLK_n:
                            nextLevel();
                            moveStartTime = SDL_GetTicks();
                            break;
                        case SDLK_p:
                            prevLevel();
                            moveStartTime = SDL_GetTicks();
                            break;
                        default:
                            g_InputManager.updateKey(event.key.keysym.sym);
                            break;
                    }
                }
            } //end switch
        } //end of message processing


        //autoplay routine (if level autoplay enabled)
        if(g_LevelManager.activeLevel()->autoPlay())
        {
            if(g_LevelManager.activePlayer()->moveNumber() < g_LevelManager.activePlayer()->movesSize())
            {
                int moveCheckTime = SDL_GetTicks();
                if(moveCheckTime - moveStartTime >= 300)
                {
                    g_InputManager.update();
                    moveStartTime = moveCheckTime;
                }
            }
        }

        g_InputManager.autoUpdate();
        //do game update

        /*****update graphics*****/

        //clear screen
        SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,0,0));
        //SDL_FillRect(display,0,SDL_MapRGB(display->format,0,0,0));

        //draw image
        g_RenderManager.update();

        int endTime = SDL_GetTicks();
        if(endTime - startTime < 1000/fps) SDL_Delay(1000/fps - (endTime - startTime));

        //end frame

        SDL_Flip(screen);

        //level win now handled in cLevelManager::update()

        if(g_LevelManager.checkWin())
        {
            done = true;
            return false;
        }

        /*
        if(levelWon())
        {
            nextLevel();
        }
        */
    }
    return done;
    //do exit
}

SDL_Surface* importBMP()
{
    std::string filename = "test.bmp";
    SDL_Surface *Tmp = SDL_LoadBMP(filename.c_str());
    SDL_Surface *bmp = NULL;

    if(Tmp)
    {
        bmp = SDL_DisplayFormat(Tmp);
        SDL_FreeSurface(Tmp);
    }

    return bmp;
}

int main ( int argc, char** argv )
{
    camera.x = 0;
    camera.y = 0;
    camera.h = screenW;
    camera.w = screenH;
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        //printf( "Unable to init SDL: %s\n", SDL_GetError() );
        std::cout<<"Unable to init SDL: " <<SDL_GetError() <<std::endl;
        return 1;
    }

    /*
    if(!screen)
    {
        std::cout<<"Unable to set screen: " <<SDL_GetError() <<std::endl;
        return 1;
    }
    */

    std::string windowTitle = "soco-*";
    SDL_WM_SetCaption(windowTitle.c_str(), windowTitle.c_str());

    /***** MUSIC *****/

    // initialize BASS

    if(!BASS_Init(-1,44100,0,NULL,NULL))
    {
        BASS_Init(0,44100,0,NULL,NULL);
    }

    /***** GAME *****/
    // specify game loop
    initSpriteManager();
    initTextureManager();
    initSoundManager();

    bool done = false;
    while(!done)
    {
        int menuValue = startScreen();
        switch(menuValue)
        {
            case 0:
            case 1:
                done = gameLoop();
                break;
            case 2:
            case 3:
            default:
                return 0;
                break;
        }
    }
    return 0;
}

#endif
