#pragma once
#include <irrKlang.h>

using namespace irrklang;

class AudioSystem
{

private:
	ISoundEngine* engine;
    ISound* currentSound;
    float volume;

public:
    AudioSystem() {
        // Create the audio system
        engine = createIrrKlangDevice();
        volume = 2.0f;
    }

    ~AudioSystem() {
        // Clean up and shut down the engine
        engine->drop();
    }

    void playSound(const char* filePath) {
       
        currentSound = engine->play2D(filePath, false, false, true);
    }

    void pauseSound(const char* filePath) {
        engine->play2D(filePath, false);
    }

    void stopSound(const char* filePath) {
        engine->stopAllSounds();
    }

    void setVolume(float newVolume)
    {
        volume = newVolume;
        engine->setSoundVolume(volume);
    }

    float getVolume()
    {
        return volume;
    }
};


