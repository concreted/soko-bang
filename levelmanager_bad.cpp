#include "engine.h"

cLevelManager::cLevelManager(std::string Name, int TileSize) : cRenderObject(Name)
{
    m_LevelTiles = SDL_LoadBMP("char.bmp");
    m_TileSize = TileSize;

    createLevels();

    m_Player = new cSprite("player", 2, 3, 40);
    m_Player->loadSprite("char.bmp",true,SDL_MapRGB(screen->format,255,0,0));

    m_CrateTile = g_TextureManager.loadSurface("core.bmp");

    m_PlayerPosX = m_PlayerPosY = 0;

    selectLevel(0);
}

bool cLevelManager::setPlayerPos(int x, int y)
{
    m_PlayerPosX = x;
    m_PlayerPosY = y;

    m_Player->m_XPos = x * m_TileSize;
    m_Player->m_YPos = y * m_TileSize;

    return true;
}

void cLevelManager::selectLevel(unsigned int Level)
{
    if(Level<m_Levels.size())
    {
        m_CurrentLevel = *m_Levels[Level];
        setPlayerPos(m_CurrentLevel.m_PlayerStartPosX, m_CurrentLevel.m_PlayerStartPosY);
    }
}

bool cLevelManager::doMove(SDLKey Key)
{
    unsigned int indexX = m_PlayerPosX;
    unsigned int indexY = m_PlayerPosY;
    unsigned int boxspaceX = indexX;
    unsigned int boxspaceY = indexY;

    switch(Key)
    {
        case SDLK_UP:
        {
            indexX--;
            boxspaceX = indexX - 1;
        }
        break;

        case SDLK_DOWN:
        {
            indexX++;
            boxspaceX = indexX + 1;
        }
        break;

        case SDLK_LEFT:
        {
            indexY--;
            boxspaceY = indexY - 1;
        }
        break;

        case SDLK_RIGHT:
        {
            indexY++;
            boxspaceY = indexY + 1;
        }
        break;

        default:
            break;
    }

    if((m_CurrentLevel.m_Level[indexX][indexY] == OBJECT_EMPTY) || (m_CurrentLevel.m_Level[indexX][indexY] == OBJECT_DEST))
    {
        if(m_CurrentLevel.m_CrateArray[indexX][indexY] == OBJECT_BOX)
        {
            if(m_CurrentLevel.m_CrateArray[boxspaceX][boxspaceY] == OBJECT_BOX)
                return false;

            if(m_CurrentLevel.m_Level[boxspaceX][boxspaceY] == OBJECT_WALL)
                return false;

            m_CurrentLevel.m_CrateArray[indexX][indexY] = OBJECT_EMPTY;
            m_CurrentLevel.m_CrateArray[boxspaceX][boxspaceY] = OBJECT_BOX;
        }

        setPlayerPos(indexX,indexY);
    }

    return false;
}

void cLevelManager::update(SDL_Surface *Screen)
{
    if((Screen) && (m_LevelTiles))
    {
        for(int i=0;i<20;++i)
        {
            for(int j=0;j<20;++j)
            {
                GAME_TYPE_OBJECT Index = m_CurrentLevel.m_Level[i][j];

                SDL_Rect SourceRct;
                SourceRct.x = Index * m_TileSize;
                SourceRct.w = m_TileSize;
                SourceRct.y = 0;
                SourceRct.h = m_TileSize;

                SDL_Rect DestRct;
                DestRct.x = j * m_TileSize;
                DestRct.w = m_TileSize;
                DestRct.y = i * m_TileSize;
                DestRct.h = m_TileSize;

                SDL_BlitSurface(m_LevelTiles, &SourceRct, Screen, &DestRct);

                if(m_CurrentLevel.m_CrateArray[i][j] == OBJECT_BOX)
                {
                    DestRct.x = j * m_TileSize;
                    DestRct.w = m_TileSize;
                    DestRct.y = i * m_TileSize;
                    DestRct.h = m_TileSize;
                    SDL_BlitSurface(m_CrateTile, NULL, Screen, &DestRct);
                }

                m_Player->update(Screen);
            }
        }
    }
}

void cLevelManager::createLevels()
{
    cLevel* Level1 = new cLevel();

    Level1->m_LevelNumber = 0;

    for(int i=0;i<20;++i)
    {
        for(int j=0;j<20;++j)
        {
            Level1->m_Level[i][j] = OBJECT_EMPTY;
        }
    }

    Level1->m_PlayerStartPosX = 4;
    Level1->m_PlayerStartPosY = 4;

    m_Levels.push_back(Level1);
    return;
}

bool cLevelManager::checkForWin()
{
    //INCOMPLETE
    return false;
}

bool cLevelManager::updateKey(SDLKey Key)
{
    switch(Key)
    {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_RIGHT:
            doMove(Key);
            return true;
        break;

        case SDLK_r:
            selectLevel(m_CurrentLevel.m_LevelNumber);
            return true;
        break;

        default:
        break;
    }

    return true;
}
