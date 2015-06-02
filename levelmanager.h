#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine.h"

extern cRenderManager g_RenderManager;

const int levelSize = 16;

int getNumberSize(int x);
std::string numberToString(int x);
int getNumber(std::string s, int i);
int getNumber(int x, int i);

class cHUDElement
{
    private:
        std::vector<cRenderObject*> HUDObjects;
        SDL_Surface* HUDTexture;
        std::vector<int> HUDObjectSizes;

    public:
        void setHUDTexture(SDL_Surface* s) {HUDTexture = s;};
        SDL_Surface* getHUDTexture() {return HUDTexture;};
        void enableColorKey() {SDL_SetColorKey(HUDTexture, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);}

        virtual void set() {};

        virtual void update(SDL_Surface *Screen)
        {
        };
};

class cHUDCounter : public cHUDElement
{
    private:
        //int counter;
        //std::string privatecounterString;
    public:
        int counter;
        void set(int a)
        {
            counter = a;
        }
        void update(SDL_Surface *Screen);
};

class cLevel : public cRenderObject
{
    private:
        std::vector<cPlayer*> players;
        std::vector<cPiece*> enemies;
        std::vector<cBlock*> blocks;
        std::vector<cPiece*> allObjects;
        std::vector<cSprite::DIRECTION> solutionMoves;
        int l_musicTrack;
        std::string levelMusic;
        SDL_Surface* levelTiles;
        int lSize;
        bool l_lost;
        bool l_autoPlay;

    public:
        enum TILE_TYPE {GROUND, WALL, DEST, BLANK, ARROW_UP, ARROW_DOWN, ARROW_RIGHT, ARROW_LEFT};
        enum END_TYPE {EXIT, END, RESTART};
        std::vector< std::vector<int> > staticIndex;
        std::vector<Point> startPts;
        std::vector<Point> destPts;
        std::vector<Point> exitPts;
        std::vector<Point> enemyPts;
        HSTREAM ms;
        Point playerStartPt;
        int cameraX;
        int cameraY;
        int dests;

        cLevel(std::string Name) : cRenderObject(Name), playerStartPt(Point(0,0))
        {
            lSize = levelSize;
            l_lost = false;
            l_autoPlay = false;
            l_musicTrack = -1;
            cameraX = 0;
            cameraY = 0;
            dests = 0;
        };

        void addMove(cSprite::DIRECTION move) {solutionMoves.push_back(move);};

        int solutionMovesSize() {return solutionMoves.size();};

        cSprite::DIRECTION getSolutionMove(int i) {return solutionMoves[i];};

        bool won();

        void autoPlayOn() {l_autoPlay = true;};

        void autoPlayOff() {l_autoPlay = false;};

        bool autoPlay(){return l_autoPlay;};

        void setMusicTrack(int i) {l_musicTrack = i;};

        void setLevelTiles(SDL_Surface* s){levelTiles = s;};

        SDL_Surface* getLevelTiles() {return levelTiles;}

        bool levelLost() {return l_lost;};

        void addBlock(cBlock* o)
        {
            blocks.push_back(o);
            allObjects.push_back(o);
        }

        void addPlayer(cPlayer* o)
        {
            players.push_back(o);
            //allObjects.push_back(o);
        }

        void addEnemy(cPiece* o)
        {
            enemies.push_back(o);
            allObjects.push_back(o);
        }

        cBlock* getBlock(int i) {return blocks[i];};
        cPlayer* getPlayer(int i) {return players[i];};
        cPiece* getEnemy(int i) {return enemies[i];};
        cPiece* getAllObjects(int i) {return allObjects[i];};

        int blocksSize() {return blocks.size();};
        int playersSize() {return players.size();};
        int enemiesSize() {return enemies.size();};
        int allObjectsSize() {return allObjects.size();};

        //void setMusic(std::string filename) {levelMusic = filename;};
        int musicTrack() {return l_musicTrack;};
        //std::string music() {return levelMusic;};

        bool playerEnemyOverlap()
        {
            for(int i=0;i<players.size();++i)
            {
                for(int j=0;j<enemies.size();++j)
                {
                    if(match(players[i], enemies[j]) && enemies[j]->state() == cPiece::ACTIVE) return true;
                }
            }
            return false;
        }

        void update(SDL_Surface *Screen)
        {
            for(int i=0;i<lSize;++i)
            {
                for(int j=0;j<lSize;++j)
                {
                    int Index = staticIndex[i][j];
                    SDL_Rect SourceRct;
                    SourceRct.x = Index * 40;
                    SourceRct.y = 0;
                    SourceRct.h = 40;
                    SourceRct.w = 40;

                    SDL_Rect DestRct;
                    DestRct.x = j * 40;
                    DestRct.y = i * 40;
                    DestRct.h = 40;
                    DestRct.w = 40;

                    SDL_BlitSurface(getLevelTiles(), &SourceRct, Screen, &DestRct);
                }
            }
            // check for collision between player and enemies
            if(playerEnemyOverlap()) l_lost = true;
        };

        void setLost(bool a) {l_lost = a;};
        void resetLost() {l_lost = false;};

        bool updateKey(SDLKey Key) {};

        void addDestPt(int x, int y)
        {
            Point a(x,y);
            destPts.push_back(a);
            ++dests;
        };

        void addDest()
        {
            ++dests;
        }

        void addExitPt(int x, int y)
        {
            Point a(x,y);
            exitPts.push_back(a);
        };

        void addEnemyPt(const Point& p){enemyPts.push_back(p);};

        void addEnemyPt(int x, int y)
        {
            Point a(x,y);
            enemyPts.push_back(a);
        };
        Point getEnemyPt(int i) {return enemyPts[i];};
        int getEnemyPtsSize() {return enemyPts.size();};

        int getIndex(const Point& p)
        {
            if(p.x < 0 || p.y < 0 || p.x >= levelSize || p.y >= levelSize) return -1;
            return staticIndex[p.y][p.x];
        };
        int getIndex(int x, int y) {return staticIndex[y][x];};     // x and y need to be reversed because of vector ordering
        int getLevelSize() {return lSize;};
        void setLevelSize(int i) {lSize = i;};
};

class cLevelManager : public cRenderObject
{
    private:
        std::vector<cLevel*> levels;
        cPicture* header;
        int currentLevel;
        bool mplay;
        int gameCounter;
        bool l_autoPlay;
        int wintimer;
        int losetimer;

    public:
        cHUDCounter HUDCounter;
        cLevelManager(std::string Name) : cRenderObject(Name)
        {
            wintimer = -1;
            losetimer = -1;
            gameCounter = -1;
        };
        void addLevel(cLevel* l) {levels.push_back(l);}
        cLevel* getLevel(int i) {return levels[i];};
        void setCounter(int i)
        {
            gameCounter = i;
            HUDCounter.counter = gameCounter;
        };
        void countDown()
        {
            --gameCounter;
            HUDCounter.counter = gameCounter;
        };

        int getCounter() {return gameCounter;};
        int numberOfLevels() {return levels.size();};
        void setCurrentLevel(int i) {currentLevel = i;};
        int getCurrentLevel() {return currentLevel;};
        cLevel* activeLevel() {return levels[currentLevel];};
        cPlayer* activePlayer() {return levels[currentLevel]->getPlayer(0);};
        void update(SDL_Surface* Screen);
        bool updateKey(SDLKey Key) {};
        void setMusicPlaying(bool a) {mplay = a;};
        bool musicPlaying() {return mplay;};
        bool autoPlay() {return l_autoPlay;};
        void autoPlayOn()
        {
            l_autoPlay = true;
            for(int i=0;i<levels.size();++i)
            {
                levels[i]->autoPlayOn();
            }
        }
        void autoPlayOff()
        {
            l_autoPlay = false;
            for(int i=0;i<levels.size();++i)
            {
                levels[i]->autoPlayOff();
            }
        }

        void endLevel()
        {
            g_RenderManager.clear();
            g_InputManager.clearInputObjects();
            wintimer = -1;
            losetimer = -1;
        };

        void stop()
        {
            g_RenderManager.clear();
            g_InputManager.clearInputObjects();
            for(int i=0;i<levels.size();++i)
            {
                levels[i]->resetLost();
            }
            g_SoundManager.stop();
        }

        void clear()
        {
            endLevel();
            stop();
            levels.clear();
        }

        bool checkWin();
};

extern cLevelManager g_LevelManager;

// create levels
void initLevel(std::string name, cLevelManager& lm);
void initLevel1();
void initLevel2();
void initLevel3();

void loadLevel(int i);
void loadLevel(cLevelManager& lm, int x);

cBlock* getCurrentLevelBlock(int x);

int getCurrentLevelObjectSize();

cLevel* getCurrentLevel();

void nextLevel();
void prevLevel();

void initLevelManager();
void initDemoLevelManager();
void initHUD();
void clearHUD();

#endif
