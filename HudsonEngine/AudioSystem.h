#pragma once
#include <irrKlang.h>
#include <unordered_map>

using namespace irrklang;

class AudioSystem 
{
public:
    AudioSystem();
    ~AudioSystem();
    void playSound(const char* file, bool playLooped = false, float volume = 1.0f, float pitch = 1.0f, float pan = 0.0f, bool enableEffect);
    void stopSound(const char* file);
    void stopAllSounds();
    void setListenerPosition(float x, float y);
    void setSoundVolume(const char* file, float volume);
    void setSoundPitch(const char* file, float pitch);
    void setSoundPan(const char* file, float pan);
    bool isSoundPlaying(const char* file);
    bool setSoundEffect(const char* file, int enableEffect);
    void fxDisplayUI();
    void update();

private:
   
    irrklang::ISoundEngine* engine;
    irrklang::ISound* music;
    irrklang::ISoundEffectControl* fx;

    std::vector<irrklang::ISound*> sounds;
   
};


