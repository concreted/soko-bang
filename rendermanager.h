#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "engine.h"

class cRenderManager
{
    public:
        // list of objects to draw on screen
        std::vector<cRenderObject*> m_Objects;
        std::vector<cRenderObject*> m_HUDElements;

        // draws child objects, called each frame
        void update();

        void addRenderObject(cRenderObject* Object)
        {
            m_Objects.push_back(Object);
        }

        void addHUDElement(cRenderObject* Object)
        {
            m_HUDElements.push_back(Object);
        }

        void clear()
        {
            m_Objects.clear();
            m_HUDElements.clear();
        }
};


#endif
