#include "engine.h"
#include "renderobject.h"

bool match(cRenderObject* a, cRenderObject* b)
{
    if(a->m_XPos == b->m_XPos && a->m_YPos == b->m_YPos)
        return true;
    return false;
}

void cRenderObject::addMove(int a)
{
        m_moves.push_back(a);
         switch(a)
        {

            case cSprite::RIGHT:
                //m_displayX = m_XPos + 40;
                m_XPos += m_Size;
            break;
            case cSprite::LEFT:
                //m_displayX = m_XPos - 40;
                m_XPos -= m_Size;
            break;
            case cSprite::UP:
                //m_displayY = m_YPos - 40;
                m_YPos -= m_Size;
            break;
            case cSprite::DOWN:
                //m_displayY = m_YPos + 40;
                m_YPos += m_Size;
            break;

            //cases for upright, downright, etc.

            case cSprite::NONE:
            default:
                break;
        }
}


