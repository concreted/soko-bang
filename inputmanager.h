#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "engine.h"

class cInputManager
{
    public:
        std::vector<cPiece*> m_InputObjects;
        std::vector<cPiece*> m_ReactPieces;

        bool updateKey(SDLKey Key);

        void update();
        void autoUpdate();

        void addInputObject(cPiece *Object)
        {
            m_InputObjects.push_back(Object);
        }
        void addReactPiece(cPiece *Piece)
        {
            m_ReactPieces.push_back(Piece);
        }
        void clearInputObjects()
        {
            m_InputObjects.clear();
        }
        void clearObjects()
        {
            m_InputObjects.clear();
            m_ReactPieces.clear();
        }
};

#endif
