#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine.h"

enum GAME_TYPE_OBJECT {OBJECT_WALL = 0, OBJECT_EMPTY = 1, OBJECT_DEST = 2, OBJECT_PLAYER = 3, OBJECT_BOX = 4};

const int levelSize = 20;

class cLevel
{
    public:

        cLevel()
        {
            for(int i=0;i<levelSize;++i)
            {
                for(int j=0;i<levelSize;++j)
                {
                    m_Level[i][j] = OBJECT_EMPTY;
                    m_CrateArray[i][j] = OBJECT_EMPTY;
                }
            }
            m_LevelName = "";
            m_LevelNumber = 0;
            m_PlayerStartPosX = m_PlayerStartPosY = 0;
        }

        GAME_TYPE_OBJECT m_Level[levelSize][levelSize];
        GAME_TYPE_OBJECT m_CrateArray[levelSize][levelSize];
        int m_PlayerStartPosX;
        int m_PlayerStartPosY;
        int m_LevelNumber;
        std::string m_LevelName;
};

class cLevelManager : public cRenderObject
{
    protected:
        SDL_Surface *m_LevelTiles;
        SDL_Surface *m_CrateTile;

        cSprite *m_Player;
        int m_PlayerPosX;
        int m_PlayerPosY;

        int m_TileSize;

        void createLevels();
    public:
        std::vector<cLevel*> m_Levels;
        cLevel m_CurrentLevel;

        cLevelManager(std::string Name, int TileSize);
        void update(SDL_Surface *screen);
        bool updateKey(SDLKey Key);
        bool setPlayerPos(int x, int y);
        bool doMove(SDLKey Key);
        void selectLevel(unsigned int Level);
        bool checkForWin();
};

#endif
