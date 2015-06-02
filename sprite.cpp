#include "engine.h"
#include "sprite.h"

cSprite::cSprite(std::string Name, int FrameCount, int FPS, int Size) : cRenderObject(Name)
{
    m_FrameCount = FrameCount;
    m_FPS = FPS;
    m_Size = Size;
    m_Height = Size;
    m_Width = Size;
    m_CurrentFrame = 0;
    m_StartTime = 0;
    m_CurrentTime = 0;
    m_FrameNumber = 0;
    m_SpriteSurface = loadSprite(Name,true,0);
    m_XPos = 0;
    m_YPos = 0;
    m_destX = 0;
    m_destY = 0;
    m_displayX = 0;
    m_displayY = 0;
    m_pushDir = cSprite::NONE;
    m_nextMove = cSprite::NONE;
}

cSprite::cSprite(std::string Name, int FrameCount, int FPS, int Height, int Width) : cRenderObject(Name)
{
    m_FrameCount = FrameCount;
    m_FPS = FPS;
    if(Height > Width)
        m_Size = Width;
    else
        m_Size = Height;
    m_Height = Height;
    m_Width = Width;
    m_CurrentFrame = 0;
    m_StartTime = 0;
    m_CurrentTime = 0;
    m_FrameNumber = 0;
    m_SpriteSurface = loadSprite(Name,true,0);
    m_XPos = 0;
    m_YPos = 0;
    m_destX = 0;
    m_destY = 0;
    m_displayX = 0;
    m_displayY = 0;
    m_pushDir = cSprite::NONE;
    m_nextMove = cSprite::NONE;
}

cSprite::~cSprite()
{
}

SDL_Surface* cSprite::loadSprite(std::string Filename, bool enableColourKey, int colourKey)
{
    // load texture from texture manager

    m_SpriteSurface = g_TextureManager.loadSurface(Filename.c_str());

    return m_SpriteSurface;
}

void cSprite::update(SDL_Surface* Screen)
{
    if((Screen) && (m_SpriteSurface))
    {
        updateAnim();

        SDL_Rect sourceRct;
        sourceRct.x = m_CurrentFrame*m_Size;
        sourceRct.y = 0;
        sourceRct.w = m_Size;
        sourceRct.h = m_Size;

        SDL_Rect destRct;
        destRct.x = m_XPos;
        destRct.y = m_YPos;
        destRct.w = m_Size;
        destRct.h = m_Size;

        SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
    }
}

void cPlayer::update(SDL_Surface *Screen)
{
    if((Screen) && (m_SpriteSurface))
    {
        if(m_Size%10 != 0) std::runtime_error("cSprite::update: m_Size%10 != 0");        //bad error checking

        if(m_XPos != m_displayX)
        {
            //SDL_Delay(10);

            if(m_displayX < m_XPos)
                m_displayX+=(m_Size/4);
            else if(m_displayX > m_XPos )
                m_displayX-=(m_Size/4);
        }

        if(m_YPos != m_displayY)
        {
            //SDL_Delay(10);
            if(m_displayY < m_YPos)
                m_displayY+=(m_Size/4);
            else if(m_displayY > m_YPos )
                m_displayY-=(m_Size/4);
        }

        updateAnim();


        if(!fastMovement)
        {
            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = p_state * m_Height;
            sourceRct.w = m_Size;
            sourceRct.h = m_Height;

            SDL_Rect destRct;
            destRct.x = m_displayX;
            destRct.y = m_displayY-5;
            destRct.w = m_Size;
            destRct.h = m_Height;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
        else if(fastMovement)
        {
            updateAnim();

            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = p_state * m_Height;
            sourceRct.w = m_Size;
            sourceRct.h = m_Height;

            SDL_Rect destRct;
            destRct.x = m_XPos;
            destRct.y = m_YPos - 5;
            destRct.w = m_Size;
            destRct.h = m_Height;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
    }
}

void cPiece::update(SDL_Surface *Screen)
{
    if((Screen) && (m_SpriteSurface))
    {
        if(m_Size%10 != 0) std::runtime_error("cSprite::update: m_Size%10 != 0");        //bad error checking

        if(m_XPos != m_displayX)
        {
            //SDL_Delay(10);

            if(m_displayX < m_XPos)
                m_displayX+=(m_Size/4);
            else if(m_displayX > m_XPos )
                m_displayX-=(m_Size/4);
        }

        if(m_YPos != m_displayY)
        {
            //SDL_Delay(10);
            if(m_displayY < m_YPos)
                m_displayY+=(m_Size/4);
            else if(m_displayY > m_YPos )
                m_displayY-=(m_Size/4);
        }

        updateAnim();


        if(!fastMovement)
        {
            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = p_state * m_Size;
            sourceRct.w = m_Size;
            sourceRct.h = m_Size;

            SDL_Rect destRct;
            destRct.x = m_displayX;
            destRct.y = m_displayY;
            destRct.w = m_Size;
            destRct.h = m_Size;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
        else if(fastMovement)
        {
            updateAnim();

            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = p_state * m_Size;
            sourceRct.w = m_Size;
            sourceRct.h = m_Size;

            SDL_Rect destRct;
            destRct.x = m_XPos;
            destRct.y = m_YPos;
            destRct.w = m_Size;
            destRct.h = m_Size;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
    }
}

void cBlock::update(SDL_Surface* Screen)
{
    if((Screen) && (m_SpriteSurface))
    {

        if(m_Size%10 != 0) std::runtime_error("cSprite::update: m_Size%10 != 0");        //bad error checking

        if(m_XPos != m_displayX)
        {
            //SDL_Delay(10);

            if(m_displayX < m_XPos)
                m_displayX+=(m_Size/4);
            else if(m_displayX > m_XPos )
                m_displayX-=(m_Size/4);
        }

        if(m_YPos != m_displayY)
        {
            //SDL_Delay(10);
            if(m_displayY < m_YPos)
                m_displayY+=(m_Size/4);
            else if(m_displayY > m_YPos )
                m_displayY-=(m_Size/4);
        }

        updateAnim();


        if(!fastMovement)
        {
            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = 0;
            sourceRct.w = m_Size;
            sourceRct.h = m_Size;

            SDL_Rect destRct;
            destRct.x = m_displayX;
            destRct.y = m_displayY;
            destRct.w = m_Size;
            destRct.h = m_Size;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
        else if(fastMovement)
        {
            updateAnim();

            SDL_Rect sourceRct;
            sourceRct.x = m_CurrentFrame*m_Size;
            sourceRct.y = 0;
            sourceRct.w = m_Size;
            sourceRct.h = m_Size;

            SDL_Rect destRct;
            destRct.x = m_XPos;
            destRct.y = m_YPos;
            destRct.w = m_Size;
            destRct.h = m_Size;

            SDL_BlitSurface(m_SpriteSurface,&sourceRct,Screen,&destRct);
        }
    }
}

bool cSprite::updateMove()
{
    //return doAutoMove();
}

bool cSprite::updateKey(SDLKey Key)
{

}

bool cPlayer::updateKey(SDLKey Key)
{
    //m_lastXPos = m_XPos;
    //m_lastYPos = m_YPos;

    if(state()!=ACTIVE) return false;

    bool valid = false;
    switch(Key)
    {
        case SDLK_DOWN:
            valid = Move(cSprite::DOWN);
            break;
        case SDLK_UP:
            valid = Move(cSprite::UP);
            break;
        case SDLK_RIGHT:
            valid = Move(cSprite::RIGHT);
            break;
        case SDLK_LEFT:
            valid = Move(cSprite::LEFT);
            break;
        case SDLK_SPACE:
            valid = Move(cSprite::PASS);
            break;
        default:
            valid = false;
            break;
    }


    /*
    bool valid = ruleSokobanPlayerBox(this, Key);
    */
    if(valid)
    {
        g_LevelManager.countDown();
        for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
        {
            g_LevelManager.activeLevel()->getAllObjects(i)->countdown();
        }
    }
    return valid;

}

bool cPlayer::updateMove()
{
    if(p_moveDirs.size() > 0)
    {
        bool valid = Move(p_moveDirs[p_moveNumber]);
        if(p_moveNumber < p_moveDirs.size()) ++p_moveNumber;
        if(valid)
        {
            g_LevelManager.countDown();
            for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
            {
                g_LevelManager.activeLevel()->getAllObjects(i)->countdown();
            }
        }
        return valid;
    }
}

void cSprite::updateAnim()
{
    m_CurrentTime = SDL_GetTicks() - m_StartTime;

    if(m_CurrentTime >= 1000)
    {
        m_StartTime = SDL_GetTicks();
        m_CurrentTime = 0;
        return;
    }

    float Scalar = (float) (m_CurrentTime / 1000.0f);
    float Frame = (float) (Scalar * m_FPS);

    if(m_FrameNumber != int(Frame))
    {
        m_FrameNumber = int(Frame);

        m_CurrentFrame++;

        if(m_CurrentFrame>=m_FrameCount)
            m_CurrentFrame = 0;
    }
}

bool cSprite::autoMove()
{
    //m_lastXPos = m_XPos;
    //m_lastYPos = m_YPos;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    switch(m_nextMove)
    {
        case cSprite::UP:
        {
            m_destX = indexX;
            m_destY = indexY-1;
        }
            break;
        case cSprite::DOWN:
        {
            m_destX = indexX;
            m_destY = indexY+1;
        }
            break;
        case cSprite::RIGHT:
        {
            m_destX = indexX+1;
            m_destY = indexY;
        }
            break;
        case cSprite::LEFT:
        {
            m_destX = indexX-1;
            m_destY = indexY;
        }
            break;
        default:
        {
            m_destX = indexX;
            m_destY = indexY;
        }
            break;
    }


    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(this == g_LevelManager.activeLevel()->getAllObjects(i)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(m_destX*m_Size, m_destY*m_Size))
        {
            return false;
        }

    }

    if(g_LevelManager.activePlayer()->m_XPos == m_destX * m_Size && g_LevelManager.activePlayer()->m_YPos == m_destY* m_Size)      //check if box matches player position
        return false;

    m_XPos = m_destX*m_Size;
    m_YPos = m_destY*m_Size;
    m_nextMove = cSprite::NONE;
    if(m_lastXPos == m_XPos && m_lastYPos == m_YPos) return false;
    return true;
}

bool cPiece::ArrowMove()
{
    bool auto_move = false;

    //m_lastXPos = m_XPos;
    //m_lastYPos = m_YPos;

    int currentSquare = g_LevelManager.activeLevel()->getIndex(m_XPos/m_Size, m_YPos/m_Size);
    do
    {
        switch(currentSquare)
        {
            case cLevel::GROUND:
            case cLevel::DEST:
            {
                m_nextMove = cSprite::NONE;
                return false;
            }
                break;
            case cLevel::ARROW_UP:
            {
                m_nextMove = cSprite::UP;
            }
                break;
            case cLevel::ARROW_DOWN:
            {
                m_nextMove = cSprite::DOWN;
            }
                break;
            case cLevel::ARROW_RIGHT:
            {
                m_nextMove = cSprite::RIGHT;
            }
                break;
            case cLevel::ARROW_LEFT:
            {
                m_nextMove = cSprite::LEFT;
            }
                break;

            default:
                m_nextMove = cSprite::NONE;
                break;
        }

            auto_move = Step(m_nextMove);
            currentSquare = g_LevelManager.activeLevel()->getIndex(m_XPos/m_Size, m_YPos/m_Size);
    }
    while(auto_move == true);

    if(m_XPos == m_lastXPos && m_YPos == m_lastYPos) return false;
    return true;
}

bool cBlock::Whack(cSprite::DIRECTION dir)
{
    return ruleWhack(this, dir);
}

bool cBlock::ArrowMove()
{
    bool auto_move = false;

    int counter = 0;

    //m_lastXPos = m_XPos;
    //m_lastYPos = m_YPos;

    int currentSquare = g_LevelManager.activeLevel()->getIndex(m_XPos/m_Size, m_YPos/m_Size);
    do
    {
        switch(currentSquare)
        {
            case cLevel::GROUND:
            case cLevel::DEST:
            {
                m_nextMove = cSprite::NONE;
                return false;
            }
                break;
            case cLevel::ARROW_UP:
            {
                m_nextMove = cSprite::UP;
            }
                break;
            case cLevel::ARROW_DOWN:
            {
                m_nextMove = cSprite::DOWN;
            }
                break;
            case cLevel::ARROW_RIGHT:
            {
                m_nextMove = cSprite::RIGHT;
            }
                break;
            case cLevel::ARROW_LEFT:
            {
                m_nextMove = cSprite::LEFT;
            }
                break;

            default:
                m_nextMove = cSprite::NONE;
                break;
        }
            //no whacking
                //auto_move = Step(m_nextMove);
            //whacking

            if(counter == 0)
                auto_move = Step(m_nextMove);
            else
                auto_move = Whack(m_nextMove);

            currentSquare = g_LevelManager.activeLevel()->getIndex(m_XPos/m_Size, m_YPos/m_Size);
            ++counter;
    }
    while(auto_move == true);

    if(m_XPos == m_lastXPos && m_YPos == m_lastYPos) return false;
    return true;
}

bool cPusher::Step(cSprite::DIRECTION dir)
{
    if(state() == ACTIVE)
        return rulePushBox(this, dir);
    else return false;
}

bool cMover::Step(cSprite::DIRECTION dir)
{
    if(state() == ACTIVE)
        return ruleMove(this, dir);
    else return false;
}

bool cPiece::Move(cSprite::DIRECTION dir)
{
    m_lastXPos = m_XPos;
    m_lastYPos = m_YPos;

    bool valid = false;
    valid = Step(dir);

    ArrowMove();

    return valid;
}

bool cBlock::Step(cSprite::DIRECTION dir)
{
    return ruleBlockMove(this, dir);
}

bool cBlock::pushMove()
{
    //m_lastXPos = m_XPos;
    //m_lastYPos = m_YPos;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    switch (m_pushDir)
    {
        case cSprite::UP:
        {
            m_destX = indexX;
            m_destY = indexY-1;
        }
        break;
        case cSprite::DOWN:
        {
            m_destX = indexX;
            m_destY = indexY+1;
        }
        break;
        case cSprite::LEFT:
        {
            m_destX = indexX-1;
            m_destY = indexY;
        }
        break;
        case cSprite::RIGHT:
        {
            m_destX = indexX+1;
            m_destY = indexY;
        }
        break;
        default:
        {
            m_destX = indexX;
            m_destY = indexY;
        }
            break;
    }


    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(this == g_LevelManager.activeLevel()->getAllObjects(i)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(m_destX*m_Size, m_destY*m_Size))
        {
            return false;
        }

    }

    m_XPos = m_destX*m_Size;
    m_YPos = m_destY*m_Size;
    m_pushDir = cSprite::NONE;
    if(m_lastXPos == m_XPos && m_lastYPos == m_YPos) return false;
    return true;
}

bool cBlock::updateMove()
{
    //return doAutoMove();
}

bool cEnemyPawn::updateMove()
{
    bool valid;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    int xDist = (m_XPos - g_LevelManager.activePlayer()->m_XPos)/g_LevelManager.activePlayer()->m_Size;
    int yDist = (m_YPos - g_LevelManager.activePlayer()->m_YPos)/g_LevelManager.activePlayer()->m_Size;

    Point lastPlayer(g_LevelManager.activePlayer()->m_lastXPos/g_LevelManager.activePlayer()->m_Size, g_LevelManager.activePlayer()->m_lastYPos/g_LevelManager.activePlayer()->m_Size);
    Point currentPlayer(g_LevelManager.activePlayer()->m_XPos/g_LevelManager.activePlayer()->m_Size, g_LevelManager.activePlayer()->m_YPos/g_LevelManager.activePlayer()->m_Size);

    int lastX = lastPlayer.x;
    int lastY = lastPlayer.y;

    int distLastX = indexX - lastPlayer.x;
    int distLastY = indexY - lastPlayer.y;


    if(abs(xDist)==abs(yDist))
    {
        if(lastY == indexY)
        {
            if(lastX == indexX - 1)
                return Move(cSprite::LEFT);
            if(lastX == indexX + 1)
                return Move(cSprite::RIGHT);
        }
        if(lastX == indexX)
        {
            if(lastY == indexY - 1)
                return Move(cSprite::UP);
            if(lastY == indexY + 1)
                return Move(cSprite::DOWN);
        }
        if(abs(distLastX) > abs(distLastY))
        {
            if(distLastY > 0)
                return Move(cSprite::UP);
            if(distLastY < 0)
                return Move(cSprite::DOWN);
        }
        if(abs(distLastX) < abs(distLastY))
        {
            if(distLastX > 0)
                return Move(cSprite::LEFT);
            if(distLastY < 0)
                return Move(cSprite::RIGHT);
        }
        //rule for determining which way the player entered proximity of enemy

        //enemy goes to spot player was last in - should only run if player's last point was directly up, down, left, or right of enemy, otherwise enemy will teleport
        //return Move(lastPlayer.x, lastPlayer.y);
        if(yDist<0)
            return Move(cSprite::DOWN);
        else if(yDist>0)
            return Move(cSprite::UP);
    }



    if(abs(xDist)<abs(yDist))
    {
        if(yDist<0)
            return Move(cSprite::DOWN);
        else if(yDist>0)
            return Move(cSprite::UP);
    }
    else if(abs(yDist)<abs(xDist))
    {
        if(xDist<0)
            return Move(cSprite::RIGHT);
        else if(xDist>0)
            return Move(cSprite::LEFT);
    }
    return false;
}


bool cEnemyBishop::updateMove()
{
    bool moved = false;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    Point target(g_LevelManager.activePlayer()->m_XPos, g_LevelManager.activePlayer()->m_YPos);

    if(target.x == m_XPos)      //player on same vertical axis
    {
        if(target.y > m_YPos)       //player below
        {
            moved = ruleMove(this, cSprite::DOWNRIGHT);
            if(!moved)
                moved = ruleMove(this, cSprite::DOWNLEFT);
        }
        else if(target.y < m_YPos)      //player above
        {
            moved = ruleMove(this, cSprite::UPLEFT);
            if(!moved)
                moved = ruleMove(this, cSprite::UPRIGHT);
        }
    }
    else if(target.y == m_YPos)     //player on same horizontal axis
    {
        if(target.x > m_XPos)       //player to right
        {
            moved = ruleMove(this, cSprite::UPRIGHT);
            if(!moved)
                moved = ruleMove(this, cSprite::DOWNRIGHT);
        }
        else if(target.x < m_XPos)      //player to left
        {
            moved = ruleMove(this, cSprite::DOWNLEFT);
            if(!moved)
                moved = ruleMove(this, cSprite::UPLEFT);
        }
    }
    else if(target.y < m_YPos && target.x < m_XPos)      //player to upper left
    {
        moved = ruleMove(this, cSprite::UPLEFT);
        if(!moved)
            moved = ruleMove(this, cSprite::UPRIGHT);
    }
    else if(target.x > m_XPos && target.y < m_YPos) // player to upper right
    {
        moved = ruleMove(this, cSprite::UPRIGHT);
        if(!moved)
            moved = ruleMove(this, cSprite::UPLEFT);
    }
    else if(target.x > m_XPos && target.y > m_YPos) // player to lower right
    {
        moved = ruleMove(this, cSprite::DOWNRIGHT);
        if(!moved)
            moved = ruleMove(this, cSprite::DOWNLEFT);
    }
    else if(target.y > m_YPos && target.x < m_XPos)    //player to lower left
    {
        moved = ruleMove(this, cSprite::DOWNLEFT);
        if(!moved)
            moved = ruleMove(this, cSprite::DOWNRIGHT);
    }

    return moved;
}

bool cEnemyBishop2::updateMove()
{
    bool moved = false;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    Point target(g_LevelManager.activePlayer()->m_XPos, g_LevelManager.activePlayer()->m_YPos);

    if(target.x == m_XPos)      //player on same vertical axis
    {
        if(target.y > m_YPos)       //player below
        {
            moved = ruleMove(this, cSprite::DOWNLEFT);
            if(!moved)
                moved = ruleMove(this, cSprite::DOWNRIGHT);
        }
        else if(target.y < m_YPos)      //player above
        {
            moved = ruleMove(this, cSprite::UPRIGHT);
            if(!moved)
                moved = ruleMove(this, cSprite::UPLEFT);
        }
    }
    else if(target.y == m_YPos)     //player on same horizontal axis
    {
        if(target.x > m_XPos)       //player to right
        {
            moved = ruleMove(this, cSprite::DOWNRIGHT);
            if(!moved)
                moved = ruleMove(this, cSprite::UPRIGHT);
        }
        else if(target.x < m_XPos)      //player to left
        {
            moved = ruleMove(this, cSprite::UPLEFT);
            if(!moved)
                moved = ruleMove(this, cSprite::DOWNLEFT);
        }
    }
    else if(target.y < m_YPos && target.x < m_XPos)      //player to upper left
    {
        moved = ruleMove(this, cSprite::UPLEFT);
        if(!moved)
            moved = ruleMove(this, cSprite::DOWNLEFT);
    }
    else if(target.x > m_XPos && target.y < m_YPos) // player to upper right
    {
        moved = ruleMove(this, cSprite::UPRIGHT);
        if(!moved)
            moved = ruleMove(this, cSprite::DOWNRIGHT);
    }
    else if(target.x > m_XPos && target.y > m_YPos) // player to lower right
    {
        moved = ruleMove(this, cSprite::DOWNRIGHT);
        if(!moved)
            moved = ruleMove(this, cSprite::UPRIGHT);
    }
    else if(target.y > m_YPos && target.x < m_XPos)    //player to lower left
    {
        moved = ruleMove(this, cSprite::DOWNLEFT);
        if(!moved)
            moved = ruleMove(this, cSprite::UPLEFT);
    }

    return moved;
}

bool cEnemyKnight::updateMove()
{
    bool completed = false;

    Point originalPos(m_XPos, m_YPos);

    Point target(g_LevelManager.activePlayer()->m_XPos, g_LevelManager.activePlayer()->m_YPos);

    Point dist = distToObject(g_LevelManager.activePlayer());

    //completed = completed = ruleMoveKnight(this, cSprite::RIGHTDOWN);


        if(target.y == m_YPos)
        {
            if(target.x > m_XPos)
                completed = ruleMoveKnight(this, cSprite::RIGHT);
            else if(m_XPos > target.x)
                completed = ruleMoveKnight(this, cSprite::LEFT);
        }
        else if(target.x == m_XPos)
        {
            if(target.y > m_YPos)
                completed = ruleMoveKnight(this, cSprite::DOWN);
            else if(m_YPos > target.y)
                completed = ruleMoveKnight(this, cSprite::UP);
        }
        else if(target.x > m_XPos)
        {
            if(target.y > m_YPos)
            {
                //below line is different in knight2 (no equals)
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::RIGHTDOWN);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
                   //completed = ruleMoveKnight(this, cSprite::RIGHT);
                else
                {
                    completed = ruleMoveKnight(this, cSprite::DOWNRIGHT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
            }
            else if(target.y < m_YPos)
            {
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::RIGHTUP);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::UPRIGHT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
            }
        }
        else if(target.x < m_XPos)
        {
            if(target.y >= m_YPos)
            {
                //below line is different in knight2 (no equals)
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::LEFTDOWN);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::DOWNLEFT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
            }

            else if(target.y < m_YPos)
            {
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::LEFTUP);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::UPLEFT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }

            }

        }

    return completed;
}

bool cEnemyKnight2::updateMove()
{
    bool completed = false;

    Point originalPos(m_XPos, m_YPos);

    Point target(g_LevelManager.activePlayer()->m_XPos, g_LevelManager.activePlayer()->m_YPos);

    Point dist = distToObject(g_LevelManager.activePlayer());

        if(target.y == m_YPos)
        {
            if(target.x > m_XPos)
                completed = ruleMoveKnight(this, cSprite::RIGHT);
            else if(m_XPos > target.x)
                completed = ruleMoveKnight(this, cSprite::LEFT);
        }
        else if(target.x == m_XPos)
        {
            if(target.y > m_YPos)
                completed = ruleMoveKnight(this, cSprite::DOWN);
            else if(m_YPos > target.y)
                completed = ruleMoveKnight(this, cSprite::UP);
        }
        else if(target.x > m_XPos)
        {
            if(target.y > m_YPos)
            {
                //below line is different in knight2 (no equals)
                if(abs(dist.x) > abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::RIGHTDOWN);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
                   //completed = ruleMoveKnight(this, cSprite::RIGHT);
                else
                {
                    completed = ruleMoveKnight(this, cSprite::DOWNRIGHT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
            }
            else if(target.y < m_YPos)
            {
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::RIGHTUP);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::UPRIGHT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::RIGHT);
                }
            }
        }
        else if(target.x < m_XPos)
        {
            if(target.y >= m_YPos)
            {
                //below line is different in knight2 (no equals)
                if(abs(dist.x) > abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::LEFTDOWN);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::DOWNLEFT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
            }

            else if(target.y < m_YPos)
            {
                if(abs(dist.x) >= abs(dist.y))
                {
                    completed = ruleMoveKnight(this, cSprite::LEFTUP);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }
                else
                {
                    completed = ruleMoveKnight(this, cSprite::UPLEFT);
                    if(originalPos.x == m_XPos && originalPos.y == m_YPos)
                        completed = ruleMoveKnight(this, cSprite::LEFT);
                }

            }

        }
    return completed;
}

bool cEnemyRook::updateMove()
{

    bool done = false;
    bool moved = false;
    while(!done)
    {
        int s = state();
        switch(s)
        {
            case 0:
            {
                if(!ruleMoveCheck(this, cSprite::UP))
                    setState(2);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::UP);
                }

            }
                break;
            case 2:
            {
                if(!ruleMoveCheck(this, cSprite::RIGHT))
                    setState(1);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::RIGHT);
                }

            }
                break;
            case 1:
            {
                if(!ruleMoveCheck(this, cSprite::DOWN))
                    setState(3);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::DOWN);
                }
            }
                break;
            case 3:
            {
                if(!ruleMoveCheck(this, cSprite::LEFT))
                    setState(0);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::LEFT);
                }

            }
                break;
            default:
            {
                done = true;
                setState(0);
            }

                break;
        }
        if(!ruleMoveCheck(this, cSprite::UP) && !ruleMoveCheck(this, cSprite::DOWN) && !ruleMoveCheck(this, cSprite::LEFT) && !ruleMoveCheck(this, cSprite::RIGHT))
            done = true;
    }
    return moved;
}

bool cEnemyRook2::updateMove()
{

    bool done = false;
    bool moved = false;
    while(!done)
    {
        int s = state();
        switch(s)
        {
            case 0:
            {
                if(!ruleMoveCheck(this, cSprite::UP))
                    setState(3);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::UP);
                }

            }
                break;
            case 3:
            {
                if(!ruleMoveCheck(this, cSprite::LEFT))
                    setState(1);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::LEFT);
                }

            }
                break;
            case 1:
            {
                if(!ruleMoveCheck(this, cSprite::DOWN))
                    setState(2);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::DOWN);
                }
            }
                break;
            case 2:
            {
                if(!ruleMoveCheck(this, cSprite::RIGHT))
                    setState(0);
                else
                {
                    done = true;
                    moved = ruleMove(this,cSprite::RIGHT);
                }

            }
                break;
            default:
            {
                done = true;
                setState(0);
            }

                break;
        }
        if(!ruleMoveCheck(this, cSprite::UP) && !ruleMoveCheck(this, cSprite::DOWN) && !ruleMoveCheck(this, cSprite::LEFT) && !ruleMoveCheck(this, cSprite::RIGHT))
            done = true;
    }
    return moved;
}


bool cEnemyKing::updateMove()
{

    bool v1 = false;
    bool v2 = false;
    bool v3 = false;
    bool v4 = false;

    int indexX = m_XPos/m_Size;
    int indexY = m_YPos/m_Size;

    // need to set conditions for if player is both left and above, etc...
    if(g_LevelManager.activePlayer()->m_XPos < m_XPos)
    {
        //v1 = rulePushBox(this, m_XPos/m_Size-1, m_YPos/m_Size, m_XPos/m_Size-2, m_YPos/m_Size, cSprite::LEFT);
        v1 = rulePushBox(this, cSprite::LEFT);
    }

    if(g_LevelManager.activePlayer()->m_XPos > m_XPos)
    {
        //v2 = rulePushBox(this, m_XPos/m_Size+1, m_YPos/m_Size, m_XPos/m_Size+2, m_YPos/m_Size, cSprite::RIGHT);
        v2 = rulePushBox(this, cSprite::RIGHT);
    }
    if(g_LevelManager.activePlayer()->m_YPos < m_YPos)
    {
        //v3 = rulePushBox(this, m_XPos/m_Size, m_YPos/m_Size-1, m_XPos/m_Size, m_YPos/m_Size-2, cSprite::UP);
        v3 = rulePushBox(this, cSprite::UP);
    }

    if(g_LevelManager.activePlayer()->m_YPos > m_YPos)
    {
        //v4 = rulePushBox(this, m_XPos/m_Size, m_YPos/m_Size+1, m_XPos/m_Size, m_YPos/m_Size+2, cSprite::DOWN);
        v4 = rulePushBox(this, cSprite::DOWN);
    }

    if(v1 || v2 || v3 || v4) return true;
    return false;
}

void addPlayer()
{
    cPlayer* a = new cPlayer("char.bmp",4,8,50,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addPlayer(a);
}

void addBlock()
{
    cBlock* a = new cBlock("core.bmp",6,12,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addBlock(a);
}

void addPawn()
{
    cEnemyPawn* a = new cEnemyPawn("enemyPawn.bmp",9,10,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addPawn(a);
}

void addRook()
{
    cEnemyRook* a = new cEnemyRook("enemyRook.bmp",6,12,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addRook(a);
}

void addRook2()
{
    cEnemyRook2* a = new cEnemyRook2("enemyRook2.bmp",6,12,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addRook2(a);
}

void addBishop()
{
    cEnemyBishop* a = new cEnemyBishop("enemyBishop.bmp",4,8,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addBishop(a);
}

void addBishop2()
{
    cEnemyBishop2* a = new cEnemyBishop2("enemyBishop2.bmp",4,8,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addBishop2(a);
}

void addKnight()
{
    cEnemyKnight* a = new cEnemyKnight("enemyKnight.bmp",6,8,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addKnight(a);
}

void addKnight2()
{
    cEnemyKnight2* a = new cEnemyKnight2("enemyKnight2.bmp",6,8,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addKnight2(a);
}

void addKing()
{
    cEnemyKing* a = new cEnemyKing("enemyKing.bmp",11,10,40);
    g_SpriteManager.addSprite(a);
    g_SpriteManager.addKing(a);
}

void initSpriteManager()
{
    addPlayer();

    // add one sprite for each core - need to figure out how to add one sprite and make copies when needed
    for(int i=0; i<5; ++i)
    {
        addBlock();
    }


    for(int i=0; i<5; ++i)
    {
        addPawn();
        addRook();
        addRook2();
        addBishop();
        addBishop2();
        addKnight();
        addKnight2();
        addKing();
    }


    for(int i=0; i<g_SpriteManager.spritesSize(); ++i)
    {
        g_SpriteManager.getSprite(i)->enableColorKey();
    }
}
