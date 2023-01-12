#include <iostream>
#include <irrKlang.h>
#include "AudioSystem.h"


using namespace irrklang;

irrklang::ISoundEngine* AudioSystem::engine;
irrklang::ISound* AudioSystem::music;


void AudioSystem::init() 
{
    engine = createIrrKlangDevice();
    volume = 1.0f;
    pitch = 1.0f;
    currentSound = nullptr;
    fx = nullptr;
    loader = nullptr;

    if (!engine)
    {
        std::cout << "Engine couldn't be loaded." << std::endl;
        return; // error starting the audio engine
    }
    music = play2D("audio/breakout.mp3", AudioType::music);

    AudioSystem::setVolume();
}

void AudioSystem::deinit() 
{
    music->drop();
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

void AudioSystem::stopSound() //stops audio immediately during playback
{
    if (currentSound)
        currentSound->stop();
}

void AudioSystem::removeAllSounds()  // Removes all sound sources
{
    if (currentSound)
        engine->removeAllSoundSources();
}

void AudioSystem::soundPitch(float newPitch)
{
    pitch = newPitch;

    if (currentSound)
        currentSound->setPlaybackSpeed();
}

void AudioSystem::soundPanning()
{

}
void AudioSystem::setVolume()
{
    AudioSystem::engine->setSoundVolume();
    music->setVolume();
   

}

float AudioSystem::getVolume()
{
    return volume;
}

ISound* AudioSystem::getCurrentSound()
{
    return currentSound;
}

ISoundEffectControl* AudioSystem::soundEffect()
{
    currentSound = engine->play2D("sound.wav", true, false, true, ESM_AUTO_DETECT, true);

    if (currentSound)
    {
        fx = currentSound->getSoundEffectControl();
        if (fx)
        {
            fx->enableEchoSoundEffect();
        }
    }
    currentSound->drop();
}

ISound* AudioSystem::play2D(std::string musicFile, AudioType audiotype, bool playLooped)
{
    ISound* currentSound = engine->play2D(musicFile.c_str(), playLooped, false, true);
    if (!currentSound)
    {
        std::cout << "Sound cannot be played" + musicFile << std::endl;
        return nullptr;
    }

    switch (audiotype)
    {
        case AudioType::soundeffect:
        {
        currentSound->setVolume();
        break;
        }
        case AudioType::ambient:
        {
        currentSound->setVolume();
        break;
        }
        case AudioType::music:
        {
        currentSound->setVolume();
        break;
        }
    }
    return currentSound;
}

IAudioStreamLoader* AudioSystem::audioStream()
{
    
}

