#include <iostream>
#include <map>
#include "AudioManager.h"
#include "imgui/imgui.h"


// Firstly, the sound engine needs to be initialised, the engine value is creating the irrklang device with the auto detect
// and default options - which ables the complier to recognise a sound driver in order for sounds to be played.

// namespaces and includes of the irrklang high level api is in the audiomanager header, which ables the program
//to load in the library.

Audio::AudioManager::AudioManager()
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

Audio::AudioManager::~AudioManager() 
{
    // Stop all sounds and close the sound engine
    stopAllSounds();
    engine->drop();

}
 

// This is an important fuhnction which allows the sound to be played with settings, so you can adjust the pitch and pan of the sound
// The playlooped setting can be adjusted in the UI function which controls if a sound file repeats a sound infinitely or not.

irrklang::ISound* Audio::AudioManager::playSound(const std::string& filePath, bool playLooped, float pitch, float pan) 
{
    try
    {
        // Play a sound file
        irrklang::ISound* sound = engine->play2D(filePath.c_str(), playLooped);
        if (sound)
        {

            sounds[filePath.c_str()].push_back(sound);

        }
        return sound;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: Sound could not be played!" << e.what() << std::endl;
    }
    return NULL;
}



// optional button instead of two separate button for pausing and resuming a sound. This toggle is determined
//by the issoundplaying function
bool Audio::AudioManager::toggleSound(const std::string& filePath)
{
    //toggles the sound if the user wants to pause or resume a sound file
    for (auto& sound : sounds[filePath.c_str()])
    {
        bool isPlaying = isSoundPlaying(filePath.c_str());
        if (isPlaying)
        {
            pauseSound(filePath.c_str(), false, 0.0f, 0.0f);
        }
        else
        {
            resumeSound(filePath.c_str(), true, 1.0f, 0.0f);
        }
        return !isPlaying;
    }
    return NULL;
  
}

// function only stops a source source, not all sounds like the stopAllSounds function.
void Audio::AudioManager::stopSound(const std::string& filePathbool, bool playLooped, float pitch, float pan)
{
    // Stop a sound file
    for (auto& sound : sounds[filePath.c_str()])
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
void Audio::AudioManager::stopAllSounds()
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

//void Audio::AudioManager::loadSoundFile(const std::string& filePath)
//{
//    //// Load the sound file into the engine
//    engine->addSoundSourceFromFile(filePath.c_str(), ESM_AUTO_DETECT);
//
//}

void Audio::AudioManager::loadSoundFile(const std::string& filePath)
{
    // Check if the sound file has already been loaded
    if (sounds.count(filePath) == 0)
    {
        try
        {
            // Load the sound file
            engine->addSoundSourceFromFile(filePath.c_str());
            sounds[filePath] = std::vector<irrklang::ISound*>();
        }
        catch (std::exception& e)
        {
            std::cout << "Exception: Sound file could not be loaded! " << e.what() << std::endl;
        }
    }
}


// engine unloads file when no longer used  

void Audio::AudioManager::unloadSoundFile(const std::string& filePath)
{
   // Unloads the sound file fromn the engine
    engine->removeSoundSource(filePath.c_str());
   
    
}

bool Audio::AudioManager::isSoundFileLoaded(const std::string& filePath) const
{
    auto it = sounds.find(filePath.c_str());
    return it != sounds.end();
}

// Set the position of the sound file
void Audio::AudioManager::setListenerPosition(float x, float y) 
{
    // Set the position of the listener
    engine->setListenerPosition(irrklang::vec3df(x, y, 0), irrklang::vec3df(0, 0, 1));
}


// Sets the appropriate volume value for the sound file
void Audio::AudioManager::setSoundVolume(const std::string& filePath, float sVolume)
{
    // Set the volume of a sound file

    if (sounds.count(filePath.c_str()) > 0)
    {
        for (auto& s : sounds[filePath.c_str()])
        {
            s->setVolume(1.0f);
            engine->getSoundVolume();
        }
    }
}


// Function which checks current conditon of the sound file, it checks the sound file to see if the sound
//is finished playing or not.
bool Audio::AudioManager::isSoundPlaying(const std::string& filePath) 
{
    // Check if a sound file is currently playing
    if (sounds.count(filePath.c_str()) > 0)
    {
        for (auto& s : sounds[filePath.c_str()])
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

bool Audio::AudioManager::addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numOfLoaders) 
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

void Audio::AudioManager::setSoundEffect(const std::string &filePath, SoundEffectType effectType, bool enable)
{
    for (auto& sound : sounds[filePath.c_str()])
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
bool Audio::AudioManager::pauseSound(const std::string& filePathbool, bool playLooped, float pitch, float pan)
{
    for (auto& s : sounds[filePath.c_str()])
    {
        s->setIsPaused(true);
        return s;
    }
    return NULL;
}

// You can unpause the sound file with this function, goes through a loop of sound files and sets any paused files to resume.
bool Audio::AudioManager::resumeSound(const std::string& filePathbool, bool playLooped, float pitch, float pan)
{
    for (auto& s : sounds[filePath.c_str()])
    {
        s->setIsPaused(false);
        return s;
    }
    return NULL;
}

// This is the function which helps to display all the available sound prompt buttons for the engine, this includes playing, pause, resume
//and stop buttons to influence the way sound files work. Buttons are present in the ImGui window.

void Audio::AudioManager::soundButtonUI(const std::string& filePath)
{
    //Play sound button
    if (ImGui::Button("PlaySound"))
    {
        std::cout << ">\n";
        loadSoundFile(filePath.c_str());
        playSound(filePath.c_str(), true, 1.5f, -0.5f);
        setSoundEffect(filePath.c_str(), SOUND_EFFECT_TYPE_DISTORTION, true);
    }
    // Play/pause toggle button
    if (ImGui::Button("Pause"))
    {
        std::cout << "||\n";
        pauseSound(filePath.c_str(), false, 0.0f, 0.0f);
    }

    // Resume sound button
    if (ImGui::Button("Resume"))
    {
        std::cout << ">>\n";
        resumeSound(filePath.c_str(), true, 1.5f, -0.5f);
        
    }
    
    //Stop sound button
    if (ImGui::Button("Stop"))
    {
        std::cout << "stop\n";
        stopSound(filePath.c_str(), false, false, false);
        setSoundEffect(filePath.c_str(), SOUND_EFFECT_TYPE_DISABLE, true);
        unloadSoundFile(filePath.c_str());

    }
}



