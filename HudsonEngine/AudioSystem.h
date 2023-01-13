#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>

using namespace irrklang;

class AudioSystem 
{
public:
    AudioSystem();
    ~AudioSystem();
    void playSound(const std::string& file, bool playLooped = false, float volume = 1.0f, float pitch = 1.0f, float pan = 0.0f);
    void stopSound(const std::string& file);
    void stopAllSounds();
    void setListenerPosition(float x, float y);

    void loadSoundFile(const std::string& file);
    void unloadSoundFile(const std::string& file);

    void setMasterVolume(float volume);
    void setSoundVolume(const std::string& file, float volume);
    void setSoundPitch(const std::string& file, float pitch);
    void setSoundPan(const std::string& file, float pan);
    bool isSoundPlaying(const std::string& file);
    
    bool addAudioStreamLoader(irrklang::IAudioStreamLoader* loader);

private:
   
    irrklang::ISoundEngine* engine;
    irrklang::ISoundEffectControl* fx;
    std::vector<irrklang::ISound*> sounds;
    std::vector<irrklang::IAudioStreamLoader*> audioStreamLoaders;
    std::unordered_map<std::string, irrklang::IAudioStream*> decoders;
   
};


