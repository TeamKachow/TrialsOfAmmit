#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>
#include <vector>

using namespace irrklang;

enum SoundEffectType {
  
    SOUND_EFFECT_TYPE_CHORUS,
    SOUND_EFFECT_TYPE_COMPRESSOR,
    SOUND_EFFECT_TYPE_DISTORTION,
    SOUND_EFFECT_TYPE_ECHO,
    SOUND_EFFECT_TYPE_FLANGER,
    SOUND_EFFECT_TYPE_GARGLE,
    SOUND_EFFECT_TYPE_REVERB,
    SOUND_EFFECT_TYPE_DISABLE
};


class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    void playSound(const std::string& file, bool playLooped = true);
    void pauseSound(const std::string& file);
    void resumeSound(const std::string& file);
    void stopSound(const std::string& file);
    void stopAllSounds();
    void setListenerPosition(float x, float y);

    void loadSoundFile(const std::string& file);
    void unloadSoundFile(const std::string& file);

    void setMasterVolume(const std::string& file,float mVolume);
    void setSoundVolume(const std::string& file, float volume = 1.0f);
    void setSoundPitch(const std::string& file, float pitch = 1.0f);
    void setSoundPan(const std::string& file, float pan = 0.0f);
    bool isSoundPlaying(const std::string& file);
    
    bool addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numLoaders = 0);  
    void setSoundEffect(const std::string& file, SoundEffectType effectType, bool enable);

private:
   
    irrklang::ISoundEngine* engine;
    std::vector<irrklang::ISoundEffectControl*> fx;
    std::vector<irrklang::ISound*> sounds;
    std::vector<irrklang::IAudioStreamLoader*> audioStreamLoaders;
    std::unordered_map<std::string, irrklang::IAudioStream*> decoders;
   
   
};


