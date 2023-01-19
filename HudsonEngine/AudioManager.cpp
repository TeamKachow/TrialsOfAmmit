#include <iostream>
#include "AudioManager.h"


AudioManager::AudioManager()
{
   
    try {
        // Initialize the sound engine
        engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_DEFAULT_OPTIONS);
        if (engine == NULL)
        {
            printf("Failed to create the engine!\n");
            return;
        }
    }
    catch (std::exception& e) {
        std::cout << "An exception occurred while initializing the sound engine: " << e.what() << std::endl;
    }

}

AudioManager::~AudioManager() 
{
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();
}
    

irrklang::ISound* AudioManager::playSound(const std::string& filePath, bool playLooped, bool pitch, bool pan) 
{
    // Play a sound file
    irrklang::ISound* sound = engine->play2D(filePath.c_str(), playLooped);
    if (sound)
    {
        sounds[filePath] = sound;
        sound->setPlaybackSpeed(pitch);
        sound->setPan(pan);   
    }
    return sound;
}

irrklang::ISound* AudioManager::pauseSound(const std::string& filePath)
{
    engine->play2D(filePath.c_str());
    // pause the sound currently playing  
    irrklang::ISound* sound = sounds[filePath];
      if (sound)
      {
         sound->setIsPaused(true);
      }
    
    return sounds[filePath];
}


irrklang::ISound* AudioManager::resumeSound(const std::string& filePath)
{
    
    // resumes the sound file if the sound isn't paused
    if (sounds.count(filePath) > 0)
    {
        sounds[filePath]->setIsPaused(false);
    }
    return sounds[filePath];
}


void AudioManager::stopSound(const std::string& filePath)
{
   
    // Stop a sound file
    if (sounds.count(filePath) > 0)
    {
        try 
        {
            sounds[filePath]->stop();
            sounds.erase(filePath);
        }
        catch (...)
        {
            std::cout << "Sound not found" << std::endl;
        }
    }
    
}

void AudioManager::stopAllSounds()
{
    for (std::map<std::string,std::vector <irrklang::ISound*>>::iterator it = sounds.begin(); it != sounds.end(); ++it)
    {
        it->second->stop();
    }
    /*sounds.clear();*/
}

void AudioManager::loadSoundFile(const std::string& filePath)
{
    // Load the sound file into the engine
    engine->addSoundSourceFromFile("../audio/RoomEnter.wav");
}

void AudioManager::unloadSoundFile(const std::string& filePath)
{
   // Unloads the sound file fromn the engine
    engine->removeSoundSource(filePath.c_str());
    
}

void AudioManager::setListenerPosition(float x, float y) 
{
    // Set the position of the listener
    engine->setListenerPosition(irrklang::vec3df(x, y, 0), irrklang::vec3df(0, 0, 1));
}


void AudioManager::setSoundVolume(const std::string& filePath, float sVolume)
{
    // Set the volume of a sound file
    if (sounds.count(filePath) > 0)
    {
        sounds[filePath]->setVolume(sVolume);
    }
}

void AudioManager::setSoundPitch(const std::string& filePath, float pitch) 
{
    // Set the pitch of a sound file
    if (sounds.count(filePath) > 0)
    {
        sounds[filePath]->setPlaybackSpeed(pitch);
    }
}

void AudioManager::setSoundPan(const std::string& filePath, float pan) 
{
    // Set the pan of a sound file
    if (sounds.count(filePath) > 0)
    {
        sounds[filePath]->setPan(pan);
    }
}

bool AudioManager::isSoundPlaying(const std::string& filePath) 
{
    // Check if a sound file is currently playing
    if (sounds.count(filePath) > 0)
    {
        return !sounds[filePath]->isFinished();
    }
    return false;
        
}


bool AudioManager::addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numOfLoaders) 
{
    for (auto it = audioStreamLoaders.begin(); it != audioStreamLoaders.end(); ++it) 
    {
        if (*it == loader) 
        {
            return false;
        }
    }
    engine->registerAudioStreamLoader(loader);
    audioStreamLoaders.push_back(loader);
    numOfLoaders++;
    return true;
}

void AudioManager::setSoundEffect(const std::string& filePath, SoundEffectType effectType, bool enable)
{
    
    if (sounds.count(filePath) > 0)
    {
        irrklang::ISoundEffectControl* fx = sounds[filePath]->getSoundEffectControl();
        switch (effectType)
        {
        case SOUND_EFFECT_TYPE_CHORUS:
             fx->enableChorusSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_COMPRESSOR:
             fx->enableCompressorSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_DISTORTION:
             fx->enableDistortionSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_ECHO:
             fx->enableEchoSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_FLANGER:
             fx->enableFlangerSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_GARGLE:
             fx->enableGargleSoundEffect(enable);
             break;
        case SOUND_EFFECT_TYPE_DISABLE:
             fx->disableAllEffects();
             break;
        default:
             break;
            }
           
    }
    
}



