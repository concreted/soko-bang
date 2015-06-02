#ifndef SPRITE_H
#define SPRITE_H

#include "engine.h"

extern bool fastMovement;

class cSprite : public cRenderObject
{
    private:


    protected:
        SDL_Surface *m_SpriteSurface;
        int m_FrameCount;
        bool m_Playing;
        Uint32 m_StartTime;
        Uint32 m_CurrentTime;

    public:
        enum DIRECTION {NONE, UP, RIGHT, DOWN, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, RIGHTUP, RIGHTDOWN, LEFTUP, LEFTDOWN, PASS};
        int m_FPS;
        int m_CurrentFrame;
        int m_FrameNumber;

        cSprite::DIRECTION m_lastMove;
        cSprite::DIRECTION m_nextMove;

        //int m_pushDir;

        cSprite(std::string Name, int FrameCount, int FPS, int Size);
        cSprite(std::string Name, int FrameCount, int FPS, int Height, int Width);
        ~cSprite();

        // overloaded virtual draw function
        void update(SDL_Surface *Screen);
        void updateAnim();
        bool updateKey(SDLKey Key);
        bool updateMove();
        bool pushMove() {};
        bool autoMove();
        bool doAutoMove() {};
        void setLastMove(const cSprite::DIRECTION& dir) {m_lastMove = dir;};

        cSprite::DIRECTION lastMove() {return m_lastMove;};
        SDL_Surface* loadSprite(std::string Filename, bool enableColourKey = false, int colourKey = 0);
        void enableColorKey()
        {
            SDL_SetColorKey(m_SpriteSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);
        };
};

class cPiece : public cSprite
{
    protected:
        int p_timeout;
        int p_timer;
        int p_state;
    public:
        enum STATE {ACTIVE, STUN, DEAD};
        cPiece(std::string Name, int FrameCount, int FPS, int Size) : cSprite(Name, FrameCount, FPS, Size)
        {
            p_timeout = 0;
            p_timer = 0;
            p_state = 0;
        };
        cPiece(std::string Name, int FrameCount, int FPS, int Height, int Width) : cSprite(Name, FrameCount, FPS, Height, Width)
        {
            p_timeout = 0;
            p_timer = 0;
            p_state = 0;
        };

        void update(SDL_Surface *Screen);

        virtual bool Step(cSprite::DIRECTION dir) = 0;      //should NOT call arrowMove(), should NOT track lastPos;
        bool Move(cSprite::DIRECTION dir);      //should call arroMove(), should track lastPos;
        bool fullMove(cSprite::DIRECTION dir)       //for more complex movers - contains full move rule (i.e. cKnight move). not necessary?
        {
            return Move(dir);
        };
        virtual bool ArrowMove();               //should call Move() to perform automoves
        void reset()
        {
            setState(cPiece::ACTIVE);
            reset_timer();
        }
        void set_timer() {p_timer = p_timeout;};
        void set_timeout(int i) {p_timeout = i;};
        int timer() {return p_timer;};
        void countdown()
        {
            if(p_state == DEAD)
                return;
            if(p_timer > 0)
                --p_timer;
            if(p_timer == 0)
                setState(ACTIVE);
        }
        void reset_timer() {p_timer = 0;};
        void setState(int x) {p_state = x;};
        virtual void Stun()
        {
            setStateStun();
        }
        virtual void Kill()
        {
            setStateDead();
        }
        void setStateStun()
        {
            p_state = cPiece::STUN;
            p_timer = p_timeout;
        }
        void setStateDead()
        {
            p_state = cPiece::DEAD;
            p_timer = -1;
        }

        int state() {return p_state;};
};

class cPusher : public cPiece
{
    private:

    public:
        cPusher(std::string Name, int FrameCount, int FPS, int Size) : cPiece(Name, FrameCount, FPS, Size) {};
        cPusher(std::string Name, int FrameCount, int FPS, int Height, int Width) : cPiece(Name, FrameCount, FPS, Height, Width) {};
        bool Step(cSprite::DIRECTION dir);
};

class cMover : public cPiece
{
    private:

    public:
        cMover(std::string Name, int FrameCount, int FPS, int Size) : cPiece(Name, FrameCount, FPS, Size) {};
        bool Step(cSprite::DIRECTION dir);
};

class cPlayer : public cPusher
{
    private:
        int p_moveNumber;
        std::vector<cSprite::DIRECTION> p_moveDirs;

    public:
        cPlayer(std::string Name, int FrameCount, int FPS, int Size) : cPusher(Name, FrameCount, FPS, Size)
        {
            p_moveNumber = 0;
            set_timeout(3);
        };
        cPlayer(std::string Name, int FrameCount, int FPS, int Height, int Width) : cPusher(Name, FrameCount, FPS, Height, Width)
        {
            p_moveNumber = 0;
            set_timeout(3);
        };

        int moveNumber() {return p_moveNumber;};

        bool updateMove();

        void update(SDL_Surface *Screen);

        void addMove(cSprite::DIRECTION move) {p_moveDirs.push_back(move);};

        int movesSize() {return p_moveDirs.size();};

        void clearMoves() {p_moveDirs.clear();};

        void reset()
        {
            p_moveNumber = 0;
            setState(cPiece::ACTIVE);
            reset_timer();
        };

        bool updateKey(SDLKey Key);
};

class cBlock : public cMover
{
    public:
        cBlock(std::string Name, int FrameCount, int FPS, int Size) : cMover(Name, FrameCount, FPS, Size)
        {
            set_timeout(10);
        };

        bool Step(cSprite::DIRECTION dir);

        bool updateMove();

        void update(SDL_Surface *Screen);

        bool ArrowMove();

        bool Whack(cSprite::DIRECTION dir);

        bool pushMove();

        void Stun() {};

        void Kill() {};
};

/*
class cEnemy : public cPiece
{
    public:
        cEnemy(std::string Name, int FrameCount, int FPS, int Size) : cSprite(Name, FrameCount, FPS, Size) {};

        bool updateMove() {};
};
*/

class cEnemyPawn : public cMover
{
    public:
        cEnemyPawn(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size)
        {
            set_timeout(3);
        };

        bool updateMove();
};

class cEnemyBishop : public cMover     //moves diagonally in clockwise rotation
{
    public:
        cEnemyBishop(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size)
        {
            set_timeout(3);
        };

        bool updateMove();
};

class cEnemyBishop2 : public cMover     //moves diagonally in counter-clockwise rotation
{
    public:
        cEnemyBishop2(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cEnemyKnight : public cMover      //blocks player's right/left movement
{
    public:
        cEnemyKnight(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cEnemyKnight2 : public cMover     //blocks player's up/down movement
{
    public:
        cEnemyKnight2(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cEnemyRook : public cMover
{
    public:
        cEnemyRook(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cEnemyRook2 : public cMover
{
    public:
        cEnemyRook2(std::string Name, int frameCount, int FPS, int Size) : cMover(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cEnemyKing : public cPusher
{
    public:
        cEnemyKing(std::string Name, int frameCount, int FPS, int Size) : cPusher(Name, frameCount, FPS, Size) {};

        bool updateMove();
};

class cSpriteManager
{
    private:
        std::vector<cSprite*> sprites;

        //sokoban
        std::vector<cPlayer*> players;
        std::vector<cBlock*> blocks;
        std::vector<cEnemyPawn*> enemyPawns;
        std::vector<cEnemyRook*> enemyRooks;
        std::vector<cEnemyRook2*> enemyRook2s;
        std::vector<cEnemyBishop*> enemyBishops;
        std::vector<cEnemyBishop2*> enemyBishop2s;
        std::vector<cEnemyKnight*> enemyKnights;
        std::vector<cEnemyKnight2*> enemyKnight2s;
        std::vector<cEnemyKing*> enemyKings;

    public:
        void addSprite(cSprite* s) {sprites.push_back(s);};
        cSprite* getSprite(int x) {return sprites[x];};
        int spritesSize() {return sprites.size();};

        //sokoban
        void addPlayer(cPlayer* s) {players.push_back(s);};
        cPlayer* getPlayer(int x) {return players[x];};
        int playersSize() {return players.size();};

        void addBlock(cBlock* s) {blocks.push_back(s);};
        cBlock* getBlock(int x) {return blocks[x];};
        int blocksSize() {return blocks.size();};

        void addPawn(cEnemyPawn* s) {enemyPawns.push_back(s);};
        cPiece* getPawn(int x) {return enemyPawns[x];};
        int pawnsSize() {return enemyPawns.size();};

        void addRook(cEnemyRook* s) {enemyRooks.push_back(s);};
        cPiece* getRook(int x) {return enemyRooks[x];};
        int rooksSize() {return enemyRooks.size();};

        void addRook2(cEnemyRook2* s) {enemyRook2s.push_back(s);};
        cPiece* getRook2(int x) {return enemyRook2s[x];};
        int rook2sSize() {return enemyRook2s.size();};

        void addBishop(cEnemyBishop* s) {enemyBishops.push_back(s);};
        cPiece* getBishop(int x) {return enemyBishops[x];};
        int bishopsSize() {return enemyBishops.size();};

        void addBishop2(cEnemyBishop2* s) {enemyBishop2s.push_back(s);};
        cPiece* getBishop2(int x) {return enemyBishop2s[x];};
        int bishop2sSize() {return enemyBishop2s.size();};

        void addKnight(cEnemyKnight* s) {enemyKnights.push_back(s);};
        cPiece* getKnight(int x) {return enemyKnights[x];};
        int knightsSize() {return enemyKnights.size();};

        void addKnight2(cEnemyKnight2* s) {enemyKnight2s.push_back(s);};
        cPiece* getKnight2(int x) {return enemyKnight2s[x];};
        int knight2sSize() {return enemyKnight2s.size();};

        void addKing(cEnemyKing* s) {enemyKings.push_back(s);};
        cPiece* getKing(int x) {return enemyKings[x];};
        int kingssSize() {return enemyKings.size();};
};

extern cSpriteManager g_SpriteManager;

void initSpriteManager();

bool ruleSokobanPlayerBox(cRenderObject* o, SDLKey Key);

void addPlayer();
void addBlock();
void addPawn();
void addRook();
void addRook2();
void addBishop();
void addBishop2();
void addKnight();
void addKnight2();
void addKing();

#endif
