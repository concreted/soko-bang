#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "engine.h"

class Point
{
    public:
        Point(int a, int b) : x(a), y(b) {};
        bool operator==(const Point& p)
        {
            if(x == p.x && y == p.y) return true;
            return false;
        }

        int x;
        int y;

        void set(int a, int b)
        {
            x = a;
            y = b;
        }
};
class cRenderObject
{
    public:
        std::string m_Name;
        int m_ZOrder;
        int m_XPos;
        int m_YPos;
        int m_Size;
        int m_Height;
        int m_Width;
        bool m_Visible;
        int m_pushDir;
        int m_lastXPos;
        int m_lastYPos;
        //int m_nextMove;
        int m_destX;
        int m_destY;

        int m_displayX;
        int m_displayY;

        std::vector<int> m_moves; //should be a cPiece member holding cSprite::DIRECTIONs
        void addMove(int a);

        cRenderObject(std::string Name)
        {
            m_Name = Name;
            m_ZOrder = 0;
            m_Visible = true;
        }

        // class virtual destructor
        virtual ~cRenderObject(){};

        // method to draw
        virtual void update(SDL_Surface *Screen) = 0;

        //method for input
        virtual bool updateKey(SDLKey Key) = 0;

        virtual bool updateMove() {};

        virtual bool pushMove() {};

        virtual bool autoMove() {};

        virtual bool doAutoMove() {};

        void setPos(int x, int y)
        {
            m_XPos = x;
            m_YPos = y;
        };

        void setDisplayPos(int x, int y)
        {
            m_displayX = x;
            m_displayY = y;
        };

        bool matchPos(cRenderObject* Object)
        {
            if(m_XPos == Object->m_XPos && m_YPos == Object->m_YPos)
                return true;
            return false;
        }

        bool matchPos(int x, int y)
        {
            if(m_XPos == x && m_YPos == y)
                return true;
            return false;
        }

        Point distToObject(cRenderObject* o)
        {
            int x = (m_XPos - o->m_XPos);
            int y = (m_YPos - o->m_YPos);
            return Point(x,y);
        }
};

class cPicture : public cRenderObject
{
    cPicture(std::string Name) : cRenderObject(Name) {};

};

bool match(cRenderObject* a, cRenderObject* b);

#endif
