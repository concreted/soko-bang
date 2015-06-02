#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "engine.h"

class Song
{
    private:
        HSTREAM* songStream;
        std::string songName;
};

class cSoundManager
{
    private:
        std::vector <HSTREAM> musicStreams;
        std::vector <HSTREAM> musicClips;
        int s_ls;
        bool s_sp;
    public:
        cSoundManager()
        {
            s_ls = 0;
            s_sp = false;
        }
        void addClip(std::string filename)
        {
            HSTREAM ms = BASS_StreamCreateFile(FALSE,filename.c_str(),0,0,0);
            musicStreams.push_back(ms);
        }
        void addStream(std::string filename)
        {
            HSTREAM ms = BASS_StreamCreateFile(FALSE,filename.c_str(),0,0,BASS_SAMPLE_LOOP);
            musicStreams.push_back(ms);
        };
        int loadedStream(){return s_ls;};
        void loadStream(int i){s_ls = i;};
        bool streamPlaying(){return s_sp;};

        HSTREAM* getStream(int i) {return &musicStreams[i];};
        HSTREAM* getClip(int i) {return &musicClips[i];};
        void startStream(int i)
        {
            s_ls = i;
            BASS_ChannelPlay(*getStream(i),true);
            s_sp = true;
        };
        void stopStream(int i)
        {
            BASS_ChannelStop(*getStream(i));
            s_sp = false;
        };
        void stopAllStreams()
        {
            for(int i=0;i<musicStreams.size();++i)
            {
                stopStream(i);
            }
        }
        void stopAllClips()
        {
            for(int i=0;i<musicClips.size();++i)
            {
                BASS_ChannelStop(musicClips[i]);
            }
        }
        void stop()
        {
            stopAllStreams();
            stopAllClips();
        }
        void startClip(int i) {BASS_ChannelPlay(*getClip(i),true);};
        void stopClip(int i) {BASS_ChannelStop(*getClip(i));};

        void playStream(int i);
};

void initSoundManager();

void loadMusic(std::string music_filename);

#endif
