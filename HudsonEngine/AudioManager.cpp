#include <iostream>
#include <map>
#include "AudioManager.h"
#include "imgui/imgui.h"


AudioManager::AudioManager()
{
   
    try 
    {
        // Initialize the sound engine
        engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_DEFAULT_OPTIONS);

        if (engine == NULL)
        {
            printf("Failed to create the engine!\n");
            return;
        }
    }
    catch (std::exception& e) 
    {
        std::cout << "An exception occurred while initializing the sound engine: " << e.what() << std::endl;
    }

}

AudioManager::~AudioManager() 
{
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();
}
    

irrklang::ISound* AudioManager::playSound(const std::string& filePath, bool playLooped, float pitch, float pan) 
{
    // Play a sound file
    irrklang::ISound* sound = engine->play2D(filePath.c_str(), playLooped, pitch, pan);
    if (sound)
    {
        
        sounds[filePath].push_back(sound);
     
        sound->setPlaybackSpeed(pitch);
        sound->setPan(pan);   
    }
    return sound;
}

bool AudioManager::toggleSound(const std::string& filePath)
{
    //toggles the sound if the user wants to pause or resume a sound file
    
        bool isPlaying = isSoundPlaying(filePath);
        if (isPlaying)
        {
            pauseSound(filePath);
        }
        else
        {
            resumeSound(filePath);
        }
        return !isPlaying;
    
  
}


void AudioManager::stopSound(const std::string& filePath)
{
    // Stop a sound file
    for (auto& sound : sounds[filePath]) 
    {
        if (sound) 
        {
            sound->stop();
            engine->removeSoundSource(filePath.c_str());
        }
    }
    
}

void AudioManager::stopAllSounds()
{
    // stop all sound files
    for (auto& element : sounds) 
    {
        std::string filePath = element.first;
        std::vector<irrklang::ISound*> vec = element.second;
        for (auto& s : vec) 
        {
            s->stop();
        }
        vec.clear();
    }
    sounds.clear();
    engine->removeAllSoundSources();
   
}

void AudioManager::loadSoundFile(const std::string& filePath)
{
    // Load the sound file into the engine
    engine->addSoundSourceFromFile(filePath.c_str());
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
        for (auto& s : sounds[filePath]) 
        {
            s->setVolume(1.0f);
        }
    }
}

//void AudioManager::setSoundPitch(const std::string& filePath, float pitch) 
//{
//    // Set the pitch of a sound file
//    if (sounds.count(filePath) > 0)
//    {
//        for (auto& s : sounds[filePath]) 
//        {
//            s->setPlaybackSpeed(-1.0f);
//        }
//    }
//}
//
//void AudioManager::setSoundPan(const std::string& filePath, float pan) 
//{
//    // Set the pan of a sound file
//    if (sounds.count(filePath) > 0)
//    {
//        for (auto& s : sounds[filePath]) 
//        {
//            s->setPan(pan);
//        }
//    }
//}

bool AudioManager::isSoundPlaying(const std::string& filePath) 
{
    // Check if a sound file is currently playing
    if (sounds.count(filePath) > 0)
    {
        for (auto& s : sounds[filePath]) 
        {
            if (!s->isFinished()) 
            {
                return true;
            }
        }
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

void AudioManager::setSoundEffect(const std::string &filePath, SoundEffectType effectType, bool enable)
{
    for (auto& sound : sounds[filePath])
    {
        if (sound)
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
                break;
            default:
                break;
            }

        }
    }
    
}
bool AudioManager::pauseSound(const std::string& filePath)
{
    for (auto& s : sounds[filePath])
    {
        s->setIsPaused(true);
        return s;
    }
    
}

bool AudioManager::resumeSound(const std::string& filePath)
{
    for (auto& s : sounds[filePath])
    {
        s->setIsPaused(false);
        return s;
    }

}

void AudioManager::soundButtonUI(const std::string& filePath)
{
    //Play sound button
    if (ImGui::Button("PlaySound"))
    {
        std::cout << ">\n";
        loadSoundFile(filePath);
        playSound(filePath, true, 1.5f, -0.5f);
    }
    // Play/pause toggle button
    if (ImGui::Button("Pause"))
    {
        std::cout << "||\n";
        toggleSound(filePath);
    }

    if (ImGui::Button("Resume"))
    {
        std::cout << ">>\n";
        resumeSound(filePath);
    }
    
    //Stop sound button
    if (ImGui::Button("Stop"))
    {
        std::cout << "stop\n";
        stopSound(filePath);
        unloadSoundFile(filePath);

    }
}



