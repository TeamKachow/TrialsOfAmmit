#pragma once
#include <irrKlang.h>

using namespace irrklang;

class AudioSystem
{

private:
	ISoundEngine* engine;
    ISound* currentSound;
    float volume;

public:
    AudioSystem();
    ~AudioSystem();
    void playSound(const char* filePath, bool loop = false);
    void pauseSound();
    void resumeSound();
    void stopSound();
    void setVolume(float newVolume);
    float getVolume();
    ISound* getCurrentSound();
};


