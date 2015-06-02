#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "engine.h"

class cTextureManager
{
    public:
    // list of textures
        std::vector<SDL_Surface*> m_Surfaces;

        ~cTextureManager()
        {
            // clear the list
            for(unsigned int indx=0; indx < m_Surfaces.size(); indx++)
                SDL_FreeSurface(m_Surfaces[indx]);
        }

        SDL_Surface* getSurface(int x)
        {
            return m_Surfaces[x];
        }

        SDL_Surface* loadSurface(std::string Filename)
        {
            SDL_Surface* Tmp = SDL_LoadBMP(Filename.c_str());
            SDL_Surface* bmp = NULL;

            if(Tmp)
            {
                bmp = SDL_DisplayFormat(Tmp);
                SDL_FreeSurface(Tmp);

                // add to list
                if(bmp)
                {
                    m_Surfaces.push_back(bmp);
                }
                return bmp;
            }
        }
};

void initTextureManager();

#endif
