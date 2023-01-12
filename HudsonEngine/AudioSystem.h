#pragma once
#include <irrKlang.h>
#include <string>

using namespace irrklang;


static class AudioSystem
{
    enum AudioType
    {
        soundeffect,
        ambient,
        music,
    };

private:
	static irrklang::ISoundEngine* engine;
    static irrklang::ISoundEffectControl* fx;
    static irrklang::IAudioStreamLoader* loader;
    static irrklang::ISound* currentSound;
    static irrklang::ISound* music;
    static float volume;
    static float pitch;

public:
    static void init();
    static void deinit();

    static void playSound(const char* filePath, bool loop = false);
    static void pauseSound();

    static void resumeSound();
    static void stopSound();

    static void removeAllSounds();

    static void soundPitch(float newPitch);
    static void soundPanning();

    static void updateAudioListener();


    static void setVolume();
    static float getVolume();
    static irrklang::ISound* getCurrentSound();
    static irrklang::ISoundEffectControl* soundEffect();
    static irrklang::ISound* play2D(std::string musicFile, AudioType audiotupe = AudioType::soundeffect, bool playLooped = false);
    

};


