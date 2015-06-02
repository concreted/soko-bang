#include "engine.h"

void initSoundManager()
{
    g_SoundManager.addStream("sokoban.wav");
    g_SoundManager.addStream("sokoban_2.wav");
    g_SoundManager.addStream("sokoban_fail.wav");
    g_SoundManager.addClip("sokoban_intro.wav");
    g_SoundManager.addClip("sokoban_win.wav");
}

void loadMusic(std::string music_filename)
{
    HSTREAM musicStream = BASS_StreamCreateFile(FALSE,music_filename.c_str(),0,0,BASS_SAMPLE_LOOP);
    //BASS_ChannelPlay(musicStream,true);
};

void cSoundManager::playStream(int i)
{
    if(i == -1)
    {
        //stopAllStreams();
    }
    else if(!streamPlaying())
    {
        startStream(i);
    }
    else if(i != loadedStream())
    {
        stopAllStreams();
        startStream(i);
    }
    return;
}
