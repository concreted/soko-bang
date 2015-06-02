#include "engine.h"
#include "levelmanager.h"

bool cInputManager::updateKey(SDLKey Key)
{
    bool inputValid = false;

    for(unsigned int indx = 0; indx<m_InputObjects.size(); ++indx)
    {
        if(m_InputObjects[indx]->m_Visible)
            inputValid = m_InputObjects[indx]->updateKey(Key);
    }

    if(inputValid)
    {
        update();
    }

    return inputValid;
}

void cInputManager::update()
{
    bool reactValid = false;
    //update intentional moves first
    for(int i=0;i<m_ReactPieces.size();++i)
    {

        if(m_ReactPieces[i]->m_Visible && m_ReactPieces[i]->state() == cPiece::ACTIVE)
        {
            reactValid = m_ReactPieces[i]->updateMove();
        }
    }

    //autoUpdate();
    //then update moves caused by automove blocks
}

void cInputManager::autoUpdate()
{
    for(int i=0;i<m_ReactPieces.size();++i)
    {

        if(m_ReactPieces[i]->m_Visible)
        {
            m_ReactPieces[i]->ArrowMove();
        }
    }
}
