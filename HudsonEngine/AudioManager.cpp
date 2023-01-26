#include <iostream>
#include <map>
#include "AudioManager.h"
#include "imgui/imgui.h"


// Firstly, the sound engine needs to be initialised, the engine value is creating the irrklang device with the auto detect
// and default options - which ables the complier to recognise a sound driver in order for sounds to be played.

// namespaces and includes of the irrklang high level api is in the audiomanager header, which ables the program
//to load in the library.

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
        // error checking 
        std::cout << "An exception occurred while initializing the sound engine: " << e.what() << std::endl;
    }

}

// Deintialise the engine - delete the engine and all sound files entirely once theyre no longer in use

AudioManager::~AudioManager() 
{
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();
}
 

// This is an important fuhnction which allows the sound to be played with settings, so you can adjust the pitch and pan of the sound
// The playlooped setting can be adjusted in the UI function which controls if a sound file repeats a sound infinitely or not.

irrklang::ISound* AudioManager::playSound(const std::string& filePath, bool playLooped, float pitch, float pan) 
{
    try
    {
        // Play a sound file
        irrklang::ISound* sound = engine->play2D(filePath.c_str(), playLooped, pitch, pan);
        if (sound)
        {

            sounds[filePath].push_back(sound);

            /* sound->setPlaybackSpeed(pitch);
             sound->setPan(pan); */
        }
        return sound;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: Sound couldn't be played!" << e.what() << std::endl;
    }
}


// optional button instead of two separate button for pausing and resuming a sound. This toggle is determined
//by the issoundplaying function
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

// function only stops a source source, not all sounds like the stopAllSounds function.
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

// engine removes all sound sources - meaning all sound files. The elements are part of the std::map which finds
//the file path and number of sound files currently there and clears them.
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

// This function tells the engine to load the sound file into the engine runtime from the sound file folder

void AudioManager::loadSoundFile(const std::string& filePath)
{
    // Load the sound file into the engine
    engine->addSoundSourceFromFile(filePath.c_str());
}

// engine unloads file when no longer used

void AudioManager::unloadSoundFile(const std::string& filePath)
{
   // Unloads the sound file fromn the engine
    engine->removeSoundSource(filePath.c_str());
    
}

// Set the position of the sound file
void AudioManager::setListenerPosition(float x, float y) 
{
    // Set the position of the listener
    engine->setListenerPosition(irrklang::vec3df(x, y, 0), irrklang::vec3df(0, 0, 1));
}


// Sets the appropriate volume value for the sound file
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

// Function which checks current conditon of the sound file, it checks the sound file to see if the sound
//is finished playing or not.
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

// Additional feature which creates and adds a number of audio streams from a file. Essentially, reads and decodes
// data from the sound files.

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


// This function toggles through the APi's avaliable sound effects such as chorus and distortion. This would then be
//applied to a sound file which can be set inside of the UI button function. For example, a sound filepath, the effect
//you specifically want, then toggle true or false to apply that effect.

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

// Pauses sound files currently playing - looping through them to check if the files are playing.
bool AudioManager::pauseSound(const std::string& filePath)
{
    for (auto& s : sounds[filePath])
    {
        s->setIsPaused(true);
        return s;
    }
    return NULL;
}

// You can unpause the sound file with this function, goes through a loop of sound files and sets any paused files to resume.
bool AudioManager::resumeSound(const std::string& filePath)
{
    for (auto& s : sounds[filePath])
    {
        s->setIsPaused(false);
        return s;
    }
    return NULL;
}

// This is the function which helps to display all the available sound prompt buttons for the engine, this includes playing, pause, resume
//and stop buttons to influence the way sound files work. Buttons are present in the ImGui window.

void AudioManager::soundButtonUI(const std::string& filePath)
{
    //Play sound button
    if (ImGui::Button("PlaySound"))
    {
        std::cout << ">\n";
        loadSoundFile(filePath);
        playSound(filePath, true, 1.5f, -0.5f);
        setSoundEffect(filePath, SOUND_EFFECT_TYPE_DISTORTION, true);
    }
    // Play/pause toggle button
    if (ImGui::Button("Pause"))
    {
        std::cout << "||\n";
        toggleSound(filePath);
    }

    // Resume sound button
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
        setSoundEffect(filePath, SOUND_EFFECT_TYPE_DISABLE, true);
        unloadSoundFile(filePath);

    }
}



