#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrklang.lib")
#include <unordered_map>

using namespace irrklang;

class AudioSystem 
{
public:
    AudioSystem();
    ~AudioSystem();
    void playSound(const char* file, bool loop = false, float volume = 1.0f, float pitch = 1.0f, float pan = 0.0f);
    void stopSound(const char* file);
    void stopAllSounds();
    void setListenerPosition(float x, float y);
    void setSoundVolume(const char* file, float volume);
    void setSoundPitch(const char* file, float pitch);
    void setSoundPan(const char* file, float pan);
    bool isSoundPlaying(const char* file);
    void fxDisplayUI();

private:
    irrklang::ISoundEngine* engine;

    std::vector<irrklang::ISound*> sounds;
   
};


