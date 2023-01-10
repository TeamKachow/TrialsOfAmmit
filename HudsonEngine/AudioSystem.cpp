#include <iostream>
#include <irrKlang.h>
#include "AudioSystem.h"

using namespace irrklang;


AudioSystem::AudioSystem() 
{
    engine = createIrrKlangDevice();
    volume = 1.0f;
    currentSound = nullptr;
}

AudioSystem::~AudioSystem() {
    engine->drop();
}

void AudioSystem::playSound(const char* filePath, bool loop) 
{
    if (currentSound)
    {
        currentSound->stop();
        currentSound = nullptr;
    }
    currentSound = engine->play2D(filePath, loop);
}

void AudioSystem::pauseSound() 
{
    if (currentSound)
        currentSound->setIsPaused(true);
}

void AudioSystem::resumeSound() 
{
    if (currentSound)
        currentSound->setIsPaused(false);
}

void AudioSystem::stopSound() 
{
    if (currentSound)
        currentSound->stop();
}

void AudioSystem::setVolume(float newVolume)
{
    volume = newVolume;
    engine->setSoundVolume(volume);

}

float AudioSystem::getVolume()
{
    return volume;
}

ISound* AudioSystem::getCurrentSound()
{
    return currentSound;
}

