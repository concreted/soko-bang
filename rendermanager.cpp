#include "engine.h"
#include "rendermanager.h"

void cRenderManager::update()
{
    SDL_FillRect(display, 0, 0);
    // loop through objects
    for (unsigned int indx = 0; indx < m_Objects.size(); indx++)
    {
        if(m_Objects[indx]->m_Visible)
            m_Objects[indx]->update(display);
    }

    //camera should be handled by level manager/level

    SDL_BlitSurface(display, &camera, screen, 0);

    for (unsigned int indx = 0; indx < m_HUDElements.size(); indx++)
    {
        m_HUDElements[indx]->update(screen);
    }

}
