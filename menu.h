#ifndef MENU_H
#define MENU_H

#include "engine.h"

class cMenu : public cRenderObject
{
    private:
        SDL_Surface* m_menuSurface;
        unsigned int m_selection;
        unsigned int m_items;       //number of menu items
        unsigned int m_width;
        unsigned int m_height;
        bool m_selected;

    public:
        cMenu(std::string name, unsigned int items, unsigned int size, unsigned int width) : cRenderObject(name), m_items(items), m_width(width)
        {
            m_Size = size;
            m_menuSurface = loadSurface(name);
            m_selection = 0;
            m_XPos = 0;
            m_YPos = 0;
            m_height = m_items * m_Size;
            m_selected = false;
        }

        void enableColorKey()
        {
            SDL_SetColorKey(m_menuSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);
        };

        unsigned int width() {return m_width;};

        unsigned int height() {return m_height;};

        bool selected() {return m_selected;};

        unsigned int selection() {return m_selection;};

        SDL_Surface* loadSurface(std::string filename)
        {
            SDL_Surface* tmp = SDL_LoadBMP(filename.c_str());
            SDL_Surface* bmp = NULL;

            if(tmp)
            {
                bmp = SDL_DisplayFormat(tmp);
                SDL_FreeSurface(tmp);
                return bmp;
            }
        }

        void update(SDL_Surface *Screen)
        {
            if((Screen) && (m_menuSurface))
            {
                for(int i=1;i<=m_items; ++i)
                {
                    SDL_Rect sourceRct;
                    sourceRct.x = 0;
                    sourceRct.y = i*m_Size;
                    sourceRct.w = m_width;
                    sourceRct.h = m_Size;

                    SDL_Rect destRct;
                    destRct.x = m_XPos + m_Size;
                    destRct.y = (i-1) * m_Size + m_YPos;
                    destRct.w = m_width;
                    destRct.h = m_Size;

                    SDL_BlitSurface(m_menuSurface,&sourceRct,Screen,&destRct);
                }

                SDL_Rect sourceRct;
                sourceRct.x = 0;
                sourceRct.y = 0;
                sourceRct.w = m_Size;
                sourceRct.h = m_Size;

                SDL_Rect destRct;
                destRct.x = m_XPos;
                destRct.y = m_selection * m_Size + m_YPos;
                destRct.w = m_Size;
                destRct.h = m_Size;

                SDL_BlitSurface(m_menuSurface,&sourceRct,Screen,&destRct);
            }
        }

        bool updateKey(SDLKey Key)
        {
            if(!m_selected)
            {
                switch(Key)
                {
                    case SDLK_UP:
                    {
                        if(m_selection == 0)
                            m_selection = m_items-1;
                        else
                            --m_selection;
                        return true;
                    }
                        break;
                    case SDLK_DOWN:
                    {
                        if(m_selection == m_items - 1)
                            m_selection = 0;
                        else
                            ++m_selection;
                        return true;
                    }
                        break;
                    case SDLK_RETURN:
                    {
                        m_selected = true;
                        return true;
                    }
                        break;
                    default:
                        return false;
                }
            }
            else if(m_selected)
                return true;

            return false;
        }
};

#endif
