#include "engine.h"
#include "rules.h"

bool ruleMoveCheck(Point& index, cSprite::DIRECTION dir)		//DON'T REMOVE THE &!! IT BREAKS THE KNIGHT!! //don't use this except within another function with a newly defined index Point
{

    Point oldIndex(index.x, index.y);
    Point newIndex(0,0);

    int indx = 0;

    switch (dir)
    {
        case cSprite::UP:
        {
            newIndex.set(oldIndex.x, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWN:
        {
            newIndex.set(oldIndex.x, oldIndex.y + 1);
        }
        break;
        case cSprite::RIGHT:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y);
        }
        break;
        case cSprite::LEFT:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y);
        }
        break;
        case cSprite::UPRIGHT:
        case cSprite::RIGHTUP:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y - 1);
        }
        break;
        case cSprite::UPLEFT:
        case cSprite::LEFTUP:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWNRIGHT:
        case cSprite::RIGHTDOWN:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y + 1);
        }
        break;
        case cSprite::DOWNLEFT:
        case cSprite::LEFTDOWN:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y + 1);
        }
        break;
        default:
            return false;
        break;
    }

    index.x = newIndex.x;
    index.y = newIndex.y;

    indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(newIndex);

    if(indx == 1) {return false;}



    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(g_LevelManager.activePlayer()->matchPos(newIndex.x * 40, newIndex.y * 40)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(newIndex.x * 40, newIndex.y * 40) && g_LevelManager.activeLevel()->getAllObjects(i)->state() != cPiece::DEAD)
        {
            return false;
        }
    }



    return true;
}

/*
bool ruleMoveCheckBool(cRenderObject* o, cSprite::DIRECTION dir)
{
    Point index(o->m_XPos/o->m_Size, o->m_YPos/o->m_Size);

    return(ruleMoveCheck(index, dir));
}
*/

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1)
{
    Point index(o->m_XPos/o->m_Size, o->m_YPos/o->m_Size);

    int possibleMoves = 1;
    int validMoves = 0;

    if(ruleMoveCheck(index, dir1)) ++validMoves;

    return validMoves;
}

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2)
{
    Point index(o->m_XPos/o->m_Size, o->m_YPos/o->m_Size);

    int possibleMoves = 2;
    int validMoves = 0;

    bool valid;

    if(ruleMoveCheck(index, dir1) > 0) ++validMoves;
    if(ruleMoveCheck(index, dir2) > 0) ++validMoves;

    return validMoves;
}

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2, cSprite::DIRECTION dir3)
{
    Point index(o->m_XPos/o->m_Size, o->m_YPos/o->m_Size);

    int possibleMoves = 3;
    int validMoves = 0;

    if(ruleMoveCheck(index, dir1)) ++validMoves;
    if(ruleMoveCheck(index, dir2)) ++validMoves;
    if(ruleMoveCheck(index, dir3)) ++validMoves;

    return validMoves;
}

bool ruleBlockMove(cRenderObject* o, cSprite::DIRECTION dir)
{
    Point oldPosition(o->m_XPos, o->m_YPos);
    Point oldIndex(oldPosition.x/o->m_Size, oldPosition.y/o->m_Size);
    Point newIndex(0,0);

    int indx = 0;

    switch (dir)
    {
        case cSprite::UP:
        {
            newIndex.set(oldIndex.x, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWN:
        {
            newIndex.set(oldIndex.x, oldIndex.y + 1);
        }
        break;
        case cSprite::RIGHT:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y);
        }
        break;
        case cSprite::LEFT:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y);
        }
        break;
        case cSprite::UPRIGHT:
        case cSprite::RIGHTUP:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y - 1);
        }
        break;
        case cSprite::UPLEFT:
        case cSprite::LEFTUP:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWNRIGHT:
        case cSprite::RIGHTDOWN:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y + 1);
        }
        break;
        case cSprite::DOWNLEFT:
        case cSprite::LEFTDOWN:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y + 1);
        }
        break;
        default:
            return false;
        break;
    }

    indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(newIndex);

    if(indx == 1) {return false;}

    cPiece* target = NULL;

    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(o == g_LevelManager.activeLevel()->getAllObjects(i)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(newIndex.x * o->m_Size, newIndex.y * o->m_Size))
        {

            target = g_LevelManager.activeLevel()->getAllObjects(i);
            switch(target->state())
            {
                case cPiece::ACTIVE:
                    return false;
                    break;
                case cPiece::STUN:
                    target->setStateDead();
                    break;
                case cPiece::DEAD:
                default:
                    break;
            }

        }
    }

    if(g_LevelManager.activePlayer()->matchPos(newIndex.x * o->m_Size, newIndex.y * o->m_Size))
    {
        return false;
    }

    o->m_XPos = newIndex.x * o->m_Size;
    o->m_YPos = newIndex.y * o->m_Size;

    //o->addMove(dir);

    if(oldPosition.x == o->m_XPos && oldPosition.y == o->m_YPos) return false;
    return true;
}

bool ruleMove(cRenderObject* o, cSprite::DIRECTION dir)
{
    Point oldPosition(o->m_XPos, o->m_YPos);
    Point oldIndex(oldPosition.x/o->m_Size, oldPosition.y/o->m_Size);
    Point newIndex(0,0);

    int indx = 0;

    switch (dir)
    {
        case cSprite::UP:
        {
            newIndex.set(oldIndex.x, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWN:
        {
            newIndex.set(oldIndex.x, oldIndex.y + 1);
        }
        break;
        case cSprite::RIGHT:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y);
        }
        break;
        case cSprite::LEFT:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y);
        }
        break;
        case cSprite::UPRIGHT:
        case cSprite::RIGHTUP:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y - 1);
        }
        break;
        case cSprite::UPLEFT:
        case cSprite::LEFTUP:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y - 1);
        }
        break;
        case cSprite::DOWNRIGHT:
        case cSprite::RIGHTDOWN:
        {
            newIndex.set(oldIndex.x + 1, oldIndex.y + 1);
        }
        break;
        case cSprite::DOWNLEFT:
        case cSprite::LEFTDOWN:
        {
            newIndex.set(oldIndex.x - 1, oldIndex.y + 1);
        }
        break;
        default:
            return false;
        break;
    }

    indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(newIndex);

    if(indx == 1) {return false;}



    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(o == g_LevelManager.activeLevel()->getAllObjects(i) || g_LevelManager.activePlayer()->matchPos(newIndex.x * o->m_Size, newIndex.y * o->m_Size)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(newIndex.x * o->m_Size, newIndex.y * o->m_Size) && g_LevelManager.activeLevel()->getAllObjects(i)->state() != cPiece::DEAD)
        {
            return false;
        }
    }



    o->m_XPos = newIndex.x * o->m_Size;
    o->m_YPos = newIndex.y * o->m_Size;

    //o->addMove(dir);

    if(oldPosition.x == o->m_XPos && oldPosition.y == o->m_YPos) return false;
    return true;
}

bool ruleMove(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2, cSprite::DIRECTION dir3)
{
    bool completed = ruleMove(o, dir1);
        if(completed)
        {
            completed = ruleMove(o, dir2);
            if(completed)
                completed = ruleMove(o, dir3);
            return completed;
        }
}

/*
bool ruleMove(cRenderObject* o, unsigned int indexX, unsigned int indexY)
{
    Point oldPosition(o->m_XPos, o->m_YPos);

    int indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(indexX, indexY);

    if(indx == 1) {return false;}

    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(o == g_LevelManager.activeLevel()->getAllObjects(i)) {}
        else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(indexX * o->m_Size, indexY * o->m_Size))
        {
            return false;
        }
    }

    o->m_XPos = indexX * o->m_Size;
    o->m_YPos = indexY * o->m_Size;
}
*/

bool ruleMoveKnight(cRenderObject* o, cSprite::DIRECTION dir)
{
    bool completed = false;

    switch(dir)
    {
        //MAKE OTHER CASES

        case cSprite::UPRIGHT:
        {
            int ruu = ruleMoveCheck(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            int uur = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);
            int rru = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            int urr = ruleMoveCheck(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);

            if(ruu == 3) return(ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP));
            else if(uur == 3) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT));
            else if(rru == 3) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP));
            else if(urr == 3) return(ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT));

            if(ruu == 2) return(ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP));
            else if(uur == 2) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT));
            else if(rru == 2) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP));
            else if(urr == 2) return(ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT));

            if(ruu == 1) return(ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP));
            else if(uur == 1) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT));
            else if(rru == 1) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP));
            else if(urr == 1) return(ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT));

            return false;
        }
            break;

        case cSprite::DOWNRIGHT:
        {
            int rdd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            int ddr = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);
            int rrd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            int drr = ruleMoveCheck(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);

            if(rdd == 3) return(ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN));
            else if(ddr == 3) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT));
            else if(rrd == 3) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN));
            else if(drr == 3) return(ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT));

            if(rdd == 2) return(ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN));
            else if(ddr == 2) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT));
            else if(rrd == 2) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN));
            else if(drr == 2) return(ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT));

            if(rdd == 1) return(ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN));
            else if(ddr == 1) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT));
            else if(rrd == 1) return(ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN));
            else if(drr == 1) return(ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT));

            return false;
        }
            break;

        case cSprite::UPLEFT:
        {
            int luu = ruleMoveCheck(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            int uul = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::LEFT);
            int llu = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            int ull = ruleMoveCheck(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);

            if(luu == 3) return(ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP));
            else if(uul == 3) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT));
            else if(llu == 3) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP));
            else if(ull == 3) return(ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT));

            if(luu == 2) return(ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP));
            else if(uul == 2) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT));
            else if(llu == 2) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP));
            else if(ull == 2) return(ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT));

            if(luu == 1) return(ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP));
            else if(uul == 1) return(ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT));
            else if(llu == 1) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP));
            else if(ull == 1) return(ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT));

            return false;
        }
            break;

        case cSprite::DOWNLEFT:
        {
            int ldd = ruleMoveCheck(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            int ddl = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);
            int lld = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            int dll = ruleMoveCheck(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);

            if(ldd == 3) return(ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN));
            else if(ddl == 3) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT));
            else if(lld == 3) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN));
            else if(dll == 3) return(ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT));

            if(ldd == 2) return(ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN));
            else if(ddl == 2) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT));
            else if(lld == 2) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN));
            else if(dll == 2) return(ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT));

            if(ldd == 1) return(ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN));
            else if(ddl == 1) return(ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT));
            else if(lld == 1) return(ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN));
            else if(dll == 1) return(ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT));

            return false;
        }
            break;

        case cSprite::RIGHTUP:
        {
            int rru = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            int urr = ruleMoveCheck(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            int ruu = ruleMoveCheck(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            int uur = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);

            if(rru == 3) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            else if(urr == 3) return ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            else if(ruu == 3) return ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            else if(uur == 3) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);

            if(rru == 2) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            else if(urr == 2) return ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            else if(ruu == 2) return ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            else if(uur == 2) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);

            if(rru == 1) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            else if(urr == 1) return ruleMove(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            else if(ruu == 1) return ruleMove(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            else if(uur == 1) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);

            return false;
        }
            break;

        case cSprite::RIGHTDOWN:
        {


            int rrd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            int drr = ruleMoveCheck(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            int rdd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            int ddr = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);

            if(rrd == 3) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            else if(drr == 3) return ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            else if(rdd == 3) return ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            else if(ddr == 3) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);

            if(rrd == 2) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            else if(drr == 2) return ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            else if(rdd == 2) return ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            else if(ddr == 2) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);

            if(rrd == 1) return ruleMove(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            else if(drr == 1) return ruleMove(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            else if(rdd == 1) return ruleMove(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            else if(ddr == 1) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);


            return false;
        }
            break;

        case cSprite::LEFTUP:
        {
            int llu = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            int ull = ruleMoveCheck(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            int luu = ruleMoveCheck(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            int uul = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::LEFT);

            if(llu == 3) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            else if(ull == 3) return ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            else if(luu == 3) return ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            else if(uul == 3) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT);

            if(llu == 2) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            else if(ull == 2) return ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            else if(luu == 2) return ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            else if(uul == 2) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT);

            if(llu == 1) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            else if(ull == 1) return ruleMove(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            else if(luu == 1) return ruleMove(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            else if(uul == 1) return ruleMove(o, cSprite::UP, cSprite::UP, cSprite::LEFT);

            return false;
        }
            break;

        case cSprite::LEFTDOWN:
        {

            int lld = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            int dll = ruleMoveCheck(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            int ldd = ruleMoveCheck(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            int ddl = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);

            if(lld == 3) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            else if(dll == 3) return ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            else if(ldd == 3) return ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            else if(ddl == 3) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);

            if(lld == 2) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            else if(dll == 2) return ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            else if(ldd == 2) return ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            else if(ddl == 2) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);

            if(lld == 1) return ruleMove(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            else if(dll == 1) return ruleMove(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            else if(ldd == 1) return ruleMove(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            else if(ddl == 1) return ruleMove(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);

            return false;
        }
            break;

        case cSprite::RIGHT:
        {
            int rru = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            int urr = ruleMoveCheck(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            int rrd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            int drr = ruleMoveCheck(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            int ruu = ruleMoveCheck(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            int uur = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);
            int rdd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            int ddr = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);

            if(rru >= urr && rru >= rrd && rru >= drr && rru >= ruu && rru >= uur && rru >= rdd && rru >= ddr)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(urr >= rru && urr >= rrd && urr >= drr && urr >= ruu && urr >= uur && urr >= rdd && urr >= ddr)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(rrd >= rru && rrd >= urr && rrd >= drr && rrd >= ruu && rrd >= uur && rrd >= rdd && rrd >= ddr)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }

            }
            else if(drr >= rru && drr >= urr && drr >= rrd && drr >= ruu && drr >= uur && drr >= rdd && drr >= ddr)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(ruu >= rru && ruu >= urr && ruu >= rrd && ruu >= drr && ruu >= uur && ruu >= rdd && ruu >= ddr)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(uur >= rru && uur >= urr && uur >= rrd && uur >= drr && uur >= ruu && uur >= rdd && uur >= ddr)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(rdd >= rru && rdd >= urr && rdd >= uur && rdd >= drr && rdd >= ruu && rdd >= rdd && rdd >= ddr)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }
            }
            else if(ddr >= rru && ddr >= urr && ddr >= uur && ddr >= drr && ddr >= ruu && ddr >= rdd && ddr >= ddr)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
        }
            break;
        case cSprite::LEFT:
        {
            int llu = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);
            int ull = ruleMoveCheck(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            int lld = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);
            int dll = ruleMoveCheck(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            int luu = ruleMoveCheck(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            int uul = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::LEFT);
            int ldd = ruleMoveCheck(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            int ddl = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);


            if(llu >= ull && llu >= lld && llu >= dll && llu >= luu && llu >= uul && llu >= ldd && llu >= ddl)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(ull >= llu && ull >= lld && ull >= dll && ull >= luu && ull >= uul && ull >= ldd && ull >= ddl)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(lld >= llu && lld >= ull && lld >= dll && lld >= luu && lld >= uul && lld >= ldd && lld >= ddl)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }

            }
            else if(dll >= llu && dll >= ull && dll >= lld && dll >= luu && dll >= uul && dll >= ldd && dll >= ddl)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(luu >= llu && luu >= ull && luu >= lld && luu >= dll && luu >= uul && luu >= ldd && luu >= ddl)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(uul >= llu && uul >= ull && uul >= lld && uul >= dll && uul >= luu && uul >= ldd && uul >= ddl)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(ldd >= llu && ldd >= ull && ldd >= uul && ldd >= dll && ldd >= luu && ldd >= ldd && ldd >= ddl)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }
            }
            else if(ddl >= llu && ddl >= ull && ddl >= uul && ddl >= dll && ddl >= luu && ddl >= ldd && ddl >= ddl)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
        }
            break;
        case cSprite::UP:
        {
            int uur = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::RIGHT);
            int ruu = ruleMoveCheck(o, cSprite::RIGHT, cSprite::UP, cSprite::UP);
            int uul = ruleMoveCheck(o, cSprite::UP, cSprite::UP, cSprite::LEFT);
            int luu = ruleMoveCheck(o, cSprite::LEFT, cSprite::UP, cSprite::UP);
            int urr = ruleMoveCheck(o, cSprite::UP, cSprite::RIGHT, cSprite::RIGHT);
            int rru = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::UP);
            int ull = ruleMoveCheck(o, cSprite::UP, cSprite::LEFT, cSprite::LEFT);
            int llu = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::UP);

            if(uur >= ruu && uur >= uul && uur >= luu && uur >= urr && uur >= rru && uur >= ull && uur >= llu)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(ruu >= uur && ruu >= uul && ruu >= luu && ruu >= urr && ruu >= rru && ruu >= ull && ruu >= llu)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(uul >= uur && uul >= ruu && uul >= luu && uul >= urr && uul >= rru && uul >= ull && uul >= llu)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }

            }
            else if(luu >= uur && luu >= ruu && luu >= uul && luu >= urr && luu >= rru && luu >= ull && luu >= llu)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::UP);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
            else if(urr >= uur && urr >= ruu && urr >= uul && urr >= luu && urr >= rru && urr >= ull && urr >= llu)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(rru >= uur && rru >= ruu && rru >= uul && rru >= luu && rru >= urr && rru >= ull && rru >= llu)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(ull >= uur && ull >= ruu && ull >= uul && ull >= luu && ull >= urr && ull >= rru && ull >= llu)
            {
                completed = ruleMove(o, cSprite::UP);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(llu >= uur && llu >= ruu && llu >= uul && llu >= luu && llu >= urr && llu >= rru && llu >= ull)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::UP);
                    return completed;
                }
            }
        }
            break;
        case cSprite::DOWN:
        {
            int ddr = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::RIGHT);
            int rdd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::DOWN, cSprite::DOWN);
            int ddl = ruleMoveCheck(o, cSprite::DOWN, cSprite::DOWN, cSprite::LEFT);
            int ldd = ruleMoveCheck(o, cSprite::LEFT, cSprite::DOWN, cSprite::DOWN);
            int drr = ruleMoveCheck(o, cSprite::DOWN, cSprite::RIGHT, cSprite::RIGHT);
            int rrd = ruleMoveCheck(o, cSprite::RIGHT, cSprite::RIGHT, cSprite::DOWN);
            int dll = ruleMoveCheck(o, cSprite::DOWN, cSprite::LEFT, cSprite::LEFT);
            int lld = ruleMoveCheck(o, cSprite::LEFT, cSprite::LEFT, cSprite::DOWN);

            if(ddr >= rdd && ddr >= ddl && ddr >= ldd && ddr >= drr && ddr >= rrd && ddr >= dll && ddr >= lld)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(rdd >= ddr && rdd >= ddl && rdd >= ldd && rdd >= drr && rdd >= rrd && rdd >= dll && rdd >= lld)
            {
                completed = ruleMove(o, cSprite::RIGHT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }
            }
            else if(ddl >= ddr && ddl >= rdd && ddl >= ldd && ddl >= drr && ddl >= rrd && ddl >= dll && ddl >= lld)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }

            }
            else if(ldd >= ddr && ldd >= rdd && ldd >= ddl && ldd >= drr && ldd >= rrd && ldd >= dll && ldd >= lld)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }
            }
            else if(drr >= ddr && drr >= rdd && drr >= ddl && drr >= ldd && drr >= rrd && drr >= dll && drr >= lld)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::RIGHT);
                    if(completed)
                        completed = ruleMove(o, cSprite::RIGHT);
                    return completed;
                }
            }
            else if(rrd >= ddr && rrd >= rdd && rrd >= ddl && rrd >= ldd && rrd >= drr && rrd >= dll && rrd >= lld)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::DOWN);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(dll >= ddr && dll >= rdd && dll >= ddl && dll >= ldd && dll >= drr && dll >= rrd && dll >= lld)
            {
                completed = ruleMove(o, cSprite::DOWN);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::LEFT);
                    return completed;
                }
            }
            else if(lld >= ddr && lld >= rdd && lld >= ddl && lld >= ldd && lld >= drr && lld >= rrd && lld >= dll)
            {
                completed = ruleMove(o, cSprite::LEFT);
                if(completed)
                {
                    completed = ruleMove(o, cSprite::LEFT);
                    if(completed)
                        completed = ruleMove(o, cSprite::DOWN);
                    return completed;
                }
            }
        }
            break;
        default:
            break;
    }
    return false;
}

bool ruleWhack(cRenderObject* o, cSprite::DIRECTION pd)
{
    unsigned int indexX = o->m_XPos/o->m_Size;
    unsigned int indexY = o->m_YPos/o->m_Size;
    unsigned int boxX = o->m_XPos/o->m_Size;
    unsigned int boxY = o->m_YPos/o->m_Size;

    switch(pd)
    {
        case cSprite::LEFT:
        {
            indexX = indexX-1;
            boxX = indexX-1;
        }
            break;
        case cSprite::RIGHT:
        {
            indexX = indexX+1;
            boxX = indexX+1;
        }
            break;
        case cSprite::UP:
        {
            indexY = indexY-1;
            boxY = indexY-1;
        }
            break;
        case cSprite::DOWN:
        {
            indexY = indexY+1;
            boxY = indexY+1;
        }
            break;
        case cSprite::PASS:
            return true;
            break;
        default:
            break;
    }
    Point oldPosition(o->m_XPos, o->m_YPos);
    bool whacked = false;
    //int pushedBox = 0;
    cPiece* whackedPiece;

    // find whacked object, get pointer to it
    for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
    {
        if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(indexX * o->m_Size, indexY * o->m_Size))
        {
            whacked = true;
            whackedPiece = g_LevelManager.activeLevel()->getAllObjects(i);
        }
    }

    if(g_LevelManager.activePlayer()->matchPos(indexX * o->m_Size, indexY * o->m_Size))
    {
        whacked = true;
        whackedPiece = g_LevelManager.activePlayer();
    }

    int indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(indexX, indexY);
    int boxIndx;

    if(indx >= 0)
    {
        if(indx == cLevel::GROUND || indx == cLevel::DEST || indx == cLevel::ARROW_LEFT|| indx == cLevel::ARROW_RIGHT || indx == cLevel::ARROW_UP || indx == cLevel::ARROW_DOWN)
        {
            //setPos(indexX * m_Size, indexY * m_Size);

            if(whacked)
            {
                boxIndx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(boxX, boxY);

                bool boxObstruct = false;

                for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
                {
                    if(whackedPiece == g_LevelManager.activeLevel()->getAllObjects(i)) {}
                    else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(boxX * o->m_Size, boxY * o->m_Size) || g_LevelManager.activePlayer()->matchPos(boxX * o->m_Size, boxY * o->m_Size))
                    {
                        boxObstruct = true;
                    }
                }

                if(boxIndx != cLevel::WALL && boxObstruct == false)
                {
					//REWRITE THIS TO NOT CALL UPDATE MOVE MULTIPLE TIMES PER TURN
                    //getCurrentLevelBlock(whackedPiece)->setPos(boxX*getCurrentLevelBlock(whackedPiece)->m_Size, boxY*getCurrentLevelBlock(0)->m_Size);
                    //whackedPiece->m_pushDir = pd;
                    if(whackedPiece->Move(pd))
                    {
                        //whackedPiece->Stun();       //stun the whacked piece
                        o->setPos(indexX * o->m_Size, indexY * o->m_Size);      //update block position
                    }
                    else
                    {
                        /*
                        //if whacked but not moved, set state to dead
                        whackedPiece->Kill();
                        //update block position
                        if(whackedPiece->state() == cPiece::DEAD)
                            o->setPos(indexX * o->m_Size, indexY * o->m_Size);
                            */

                    }
                }
                else if (boxIndx == cLevel::WALL || boxObstruct == true)
                {
                    /*
                    //if whacked but not moved, set state to dead
                    whackedPiece->Kill();
                    //update block position
                    if(whackedPiece->state() == cPiece::DEAD)
                        o->setPos(indexX * o->m_Size, indexY * o->m_Size);
                    */
                }
            }
            else
                o->setPos(indexX * o->m_Size, indexY * o->m_Size);      //update block position
        }
        if(indx == cLevel::WALL)
            o->setPos(o->m_XPos,o->m_YPos);
    }
    Point newPosition(o->m_XPos, o->m_YPos);
    if(newPosition == oldPosition) return false;

    /*
    cSprite* s;
    s = dynamic_cast<cSprite*>(o);
    s->setLastMove(pd);
    */
    return true;
}

bool rulePushBox(cRenderObject* o, cSprite::DIRECTION pd)
{
    unsigned int indexX = o->m_XPos/o->m_Size;
    unsigned int indexY = o->m_YPos/o->m_Size;
    unsigned int boxX = o->m_XPos/o->m_Size;
    unsigned int boxY = o->m_YPos/o->m_Size;

    switch(pd)
    {
        case cSprite::LEFT:
        {
            indexX = indexX-1;
            boxX = indexX-1;
        }
            break;
        case cSprite::RIGHT:
        {
            indexX = indexX+1;
            boxX = indexX+1;
        }
            break;
        case cSprite::UP:
        {
            indexY = indexY-1;
            boxY = indexY-1;
        }
            break;
        case cSprite::DOWN:
        {
            indexY = indexY+1;
            boxY = indexY+1;
        }
            break;
        case cSprite::PASS:
            return true;
            break;
        default:
            break;
    }
    Point oldPosition(o->m_XPos, o->m_YPos);
    bool pushed = false;
    //int pushedBox = 0;
    cBlock* pushedBox;


    for(int i=0;i<g_LevelManager.activeLevel()->enemiesSize();++i)
    {
        if(o == g_LevelManager.activeLevel()->getEnemy(i)) {}
        else if(g_LevelManager.activeLevel()->getEnemy(i)->matchPos(indexX * o->m_Size, indexY * o->m_Size) && g_LevelManager.activeLevel()->getEnemy(i)->state() != cPiece::DEAD)
        {
            return false;
        }
    }

    // find pushed block, get pointer to it
    for(int i=0;i<getCurrentLevelObjectSize();++i)
    {
        if(getCurrentLevelBlock(i)->matchPos(indexX * o->m_Size, indexY * o->m_Size))
        {
            pushed = true;
            pushedBox = getCurrentLevelBlock(i);
        }
    }

    int indx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(indexX, indexY);
    int boxIndx;

    if(indx >= 0)
    {
        if(indx == cLevel::GROUND || indx == cLevel::DEST || indx == cLevel::ARROW_LEFT|| indx == cLevel::ARROW_RIGHT || indx == cLevel::ARROW_UP || indx == cLevel::ARROW_DOWN)
        {
            //setPos(indexX * m_Size, indexY * m_Size);

            if(pushed)
            {
                boxIndx = g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getIndex(boxX, boxY);

                bool boxObstruct = false;

                /*
                for(int i=0;i<g_LevelManager.activeLevel()->allObjectsSize();++i)
                {
                    if(pushedBox == g_LevelManager.activeLevel()->getAllObjects(i)) {}
                    else if(g_LevelManager.activeLevel()->getAllObjects(i)->matchPos(boxX * o->m_Size, boxY * o->m_Size) || g_LevelManager.activePlayer()->matchPos(boxX * o->m_Size, boxY * o->m_Size))
                    {
                        boxObstruct = true;
                    }
                }
                */

                switch(pd)
                {
                    case cSprite::RIGHT:
                    {
                        if(boxIndx == cLevel::ARROW_LEFT)
                            boxObstruct = true;
                    }
                        break;
                    case cSprite::LEFT:
                    {
                        if(boxIndx == cLevel::ARROW_RIGHT)
                            boxObstruct = true;
                    }
                        break;
                    case cSprite::UP:
                    {
                        if(boxIndx == cLevel::ARROW_DOWN)
                            boxObstruct = true;
                    }
                        break;
                    case cSprite::DOWN:
                    {
                        if(boxIndx == cLevel::ARROW_UP)
                            boxObstruct = true;
                    }
                        break;
                }

                if(boxIndx != cLevel::WALL && boxObstruct == false)
                {
                    if (boxIndx != cLevel::GROUND && boxIndx != cLevel::DEST && boxIndx != cLevel::ARROW_LEFT && boxIndx != cLevel::ARROW_RIGHT && boxIndx != cLevel::ARROW_UP && boxIndx != cLevel::ARROW_DOWN)
                        return false;
                    pushedBox->m_pushDir = pd;
                    if(pushedBox->Move(pd))
                    {
                        o->setPos(indexX * o->m_Size, indexY * o->m_Size);

                        //o->addMove(pd);
                        return true;
                    }

                    else //o->setFinalPos(o->m_XPos,o->m_YPos);
                    {
                        //o->m_moves.push_back(cSprite::NONE);
                        return false;
                    }

                }
                else if (boxIndx == cLevel::WALL || boxObstruct == true)
                {
                    //o->setFinalPos(o->m_XPos,o->m_YPos);
                    //o->m_moves.push_back(cSprite::NONE);
                    return false;
                }

            }
            else
            {
                o->setPos(indexX * o->m_Size, indexY * o->m_Size);

                //o->addMove(pd);
                return true;
            }

        }
        if(indx == cLevel::WALL)
        {
            //o->setFinalPos(o->m_XPos,o->m_YPos);
            //o->m_moves.push_back(cSprite::NONE);
            return false;
        }

    }
    //Point newPosition(o->m_XPos, o->m_YPos);
    //if(newPosition == oldPosition) return false;

    /*
    cSprite* s;
    s = dynamic_cast<cSprite*>(o);
    s->setLastMove(pd);
    */
    return false;
}

bool ruleSokobanPlayerBox(cRenderObject* o, SDLKey Key)
{
    o->m_lastXPos = o->m_XPos;
    o->m_lastYPos = o->m_YPos;

    unsigned int indexX = o->m_XPos/o->m_Size;
    unsigned int indexY = o->m_YPos/o->m_Size;
    unsigned int boxX = indexX;
    unsigned int boxY = indexY;

    //dynamic_cast<cSprite*>(o)->setLastMove(cSprite::NONE);
    cSprite::DIRECTION pushedDirection = cSprite::NONE;

    switch(Key)
    {
        case SDLK_DOWN:
        {
            ++indexY;
            boxY = indexY + 1;
            pushedDirection = cSprite::DOWN;
        }
            break;
        case SDLK_RIGHT:
        {
            ++indexX;
            boxX = indexX + 1;
            pushedDirection = cSprite::RIGHT;
        }
            break;
        case SDLK_LEFT:
        {
            --indexX;
            boxX = indexX - 1;
            pushedDirection = cSprite::LEFT;
        }
            break;
        case SDLK_UP:
        {
            --indexY;
            boxY = indexY - 1;
            pushedDirection = cSprite::UP;
        }
            break;
        case SDLK_SPACE:
        {
            /*
            if(g_LevelManager.activeLevel()->getIndex(indexX, indexY) == cLevel::ARROW_RIGHT)
            {
                ++indexX;
                boxX = indexX + 1;
                pushedDirection = cSprite::RIGHT;
            }

            else
            */
            return true;
        }
        break;
        default:
        {
            return false;
        }
            break;
    }

    if(rulePushBox(o, pushedDirection)) return true;
    return false;
}
