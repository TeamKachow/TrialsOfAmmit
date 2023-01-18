#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>

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
    
    irrklang::ISound* playSound(const std::string& filePath, bool playLooped, bool pitch, bool pan);
    irrklang::ISound* pauseSound(const std::string& filePath);
    irrklang::ISound* resumeSound(const std::string& filePath);
    irrklang::ISound* stopSound(const std::string& filePath);
    irrklang::ISound* stopAllSounds();
    void setListenerPosition(float x, float y);

    void loadSoundFile(const std::string& filePath);
    void unloadSoundFile(const std::string& filePath);

    void setSoundVolume(const std::string& filePath, float sVolume = 1.0f);
    void setSoundPitch(const std::string& filePath, float pitch = 1.0f);
    void setSoundPan(const std::string& filePath, float pan = 0.0f);
    bool isSoundPlaying(const std::string& filePath);
    
    bool addAudioStreamLoader(irrklang::IAudioStreamLoader* loader, int numLoaders = 0);  
    void setSoundEffect(const std::string& filePath, SoundEffectType effectType, bool enable);

private:
   
    irrklang::ISoundEngine* engine;
    std::map<std::string, irrklang::ISound*> sounds;

    std::vector<irrklang::ISoundEffectControl*> fx;

    std::vector<irrklang::IAudioStreamLoader*> audioStreamLoaders;
    std::unordered_map<std::string, irrklang::IAudioStream*> decoders;
   
   
};


