#include <irrKlang.h>
#pragma comment(lib, "irrklang.lib")
#include "AudioSystem.h"

using namespace irrklang;

AudioSystem::AudioSystem() 
{
    // Initialize the sound engine
    engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_MULTI_THREADED | irrklang::ESEO_LOAD_PLUGINS | irrklang::ESEO_USE_3D_BUFFERS);
    
    if (engine == NULL)
    {
        printf("Failed to create the engine!\n");
        return;
    }
    
}

AudioSystem::~AudioSystem() 
{
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();
}

void AudioSystem::playSound(const std::string& file, bool playLooped, float volume, float pitch, float pan) 
{
    // Play a sound file
    irrklang::ISound* sound = engine->play2D(file.c_str(), playLooped, false, true);
    if (sound) 
    {
        sounds.push_back(sound);
        sound->setVolume(volume);
        sound->setPlaybackSpeed(pitch);
        sound->setPan(pan);
    }
}

void AudioSystem::pauseSound(const std::string& file)
{
    // Pause a sound file
    for (auto& sound : sounds)
    {
        if (sound->getSoundSource()->getName() == file) {
            sound->setIsPaused(true);
            break;
        }
    }
}


void AudioSystem::resumeSound(const std::string& file)
{
    // resumes the sound file if the sound isn't paused
    for (auto& sound : sounds)
    {
        if (sound->getSoundSource()->getName() == file)
        {
            sound->setIsPaused(false);
            break;
        }
    }
}


void AudioSystem::stopSound(const std::string& file) 
{
    // Stop a sound file
    for (auto it = sounds.begin(); it != sounds.end(); ++it) 
    {
        irrklang::ISound* sound = *it;
        if (sound->getSoundSource()->getName() == file) {
            sound->stop();
            sounds.erase(it);
            break;
        }
    }
}

void AudioSystem::stopAllSounds() 
{
    // Stop all sound files
    for (auto& sound : sounds) 
    {
        sound->stop();
    }
    sounds.clear();
}

void AudioSystem::loadSoundFile(const std::string& file)
{
    engine->addSoundSourceFromFile(file.c_str());
}

void AudioSystem::unloadSoundFile(const std::string& file)
{
    engine->removeSoundSource(file.c_str());
}

void AudioSystem::setListenerPosition(float x, float y) 
{
    // Set the position of the listener
    engine->setListenerPosition(irrklang::vec3df(x, y, 0), irrklang::vec3df(0, 0, 1));
}

void AudioSystem::setMasterVolume(const std::string& file, float mVolume)
{
    for (auto& sound : sounds)
    {
        engine->setSoundVolume(mVolume);
    }
   
}

void AudioSystem::setSoundVolume(const std::string& file, float volume) 
{
    // Set the volume of a sound file
    for (auto& sound : sounds) 
    {
        if (sound-> getSoundSource()->getName() == file) 
        {
            sound->setVolume(volume);
            break;
        }
    }
}

void AudioSystem::setSoundPitch(const std::string& file, float pitch) 
{
    // Set the pitch of a sound file
    for (auto& sound : sounds) 
    {
        if (sound->getSoundSource()->getName() == file) {
            sound->setPlaybackSpeed(pitch);
            break;
        }
    }
}

void AudioSystem::setSoundPan(const std::string& file, float pan) 
{
    // Set the pan of a sound file
    for (auto& sound : sounds) 
    {
        if (sound->getSoundSource()->getName() == file) {
            sound->setPan(pan);
            break;
        }
    }
}

bool AudioSystem::isSoundPlaying(const std::string& file) 
{
    // Check if a sound file is currently playing
    for (auto& sound : sounds) 
    {
        if (sound->getSoundSource()->getName() == file) 
        {
            return !sound->isFinished();
        }
    }
    return false;
}


bool AudioSystem::addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numLoaders) 
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
    numLoaders++;
    return true;
        
}

void AudioSystem::setSoundEffect(const std::string& file, SoundEffectType effectType, bool enable)
{
    for (auto& sound : sounds)
    {
        if (sound->getSoundSource()->getName() == file)
        {
            irrklang::ISoundEffectControl* fx = sound->getSoundEffectControl();
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
            default:
                break;
            }
            break;
        }
    }
}



