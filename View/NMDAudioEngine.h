//
//  NMDAudioEngine.h
//  nmd
//
//  Created by Kainoki Kaede on 2014/10/06.
//
//

#ifndef __nmd__NMDAudioEngine__
#define __nmd__NMDAudioEngine__

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "MusicFade.h"

class NMDAudioEngine{
    
private:
    static NMDAudioEngine* instance;
    // To make NMDAudioEngine as a singleton{
    NMDAudioEngine(void){}
    NMDAudioEngine(const NMDAudioEngine& other){}
    NMDAudioEngine& operator=(const NMDAudioEngine& other);
    // }
    
public:
    // To make NMDAudioEngine as a singleton{
    ~NMDAudioEngine(){}
    static NMDAudioEngine* getInstance();
    // }
    
    const char* currentBackgroundMusicFilePath = nullptr;
    const char* previousBackgroundMusicFilePath = nullptr;
    
    // Overridden functions:
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    void stopBackgroundMusic(bool bReleaseData);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

    // Newly defined functions:
    void fadeBackgroundMusic(float fadeSeconds, float targetVolume);
    void fadeInBackgroundMusic(const char* pszFilePath, bool bLoop, float fadeInSeconds, float targetVolume = 0.9);
    void fadeOutBackgroundMusic(bool bReleaseData, float fadeOutSeconds);
    void fadeBackgroundMusic(cocos2d::Node* node, float fadeSeconds, float targetVolume);
    void fadeInBackgroundMusic(cocos2d::Node* node, const char* pszFilePath, bool bLoop, float fadeInSeconds, float targetVolume = 0.9);
    void fadeOutBackgroundMusic(cocos2d::Node* node, bool bReleaseData, float fadeOutSeconds);
    unsigned int playEffectWithDimmedBGM(const char* pszFilePath, bool bLoop);
    unsigned int playEffectWithDimmedBGM(const char* pszFilePath);
    void memorizeBackgroundMusicVolume();
    void recallBackgroundMusicVolume();
    float backgroundMusicVolumeMemory = 1.0;
    
    // Functions from SimpleAudioEngine
    void preloadBackgroundMusic(const char* pszFilePath) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(pszFilePath);
    }
    
    void playBackgroundMusic(const char* pszFilePath) {
        this->playBackgroundMusic(pszFilePath, false);
    }

    void stopBackgroundMusic() {
        this->stopBackgroundMusic(false);
    }

    void rewindBackgroundMusic() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
    }

    bool willPlayBackgroundMusic() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->willPlayBackgroundMusic();
    }

    bool isBackgroundMusicPlaying() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
    }

    // properties
    float getBackgroundMusicVolume() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    }

    void setBackgroundMusicVolume(float volume) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    }

    float getEffectsVolume() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
    }

    void setEffectsVolume(float volume) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
    }

    // for sound effects
    unsigned int playEffect(const char* pszFilePath, bool bLoop) {
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, bLoop);
    }

    unsigned int playEffect(const char* pszFilePath) {
        return this->playEffect(pszFilePath, false);
    }
    
    void pauseEffect(unsigned int nSoundId) {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(nSoundId);
    }
    
    void pauseAllEffects() {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    }

    void resumeEffect(unsigned int nSoundId) {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(nSoundId);
    }
    
    void resumeAllEffects() {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    }

    void stopEffect(unsigned int nSoundId) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(nSoundId);
    }

    void stopAllEffects() {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    }
    
    void preloadEffect(const char* pszFilePath) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(pszFilePath);
    }
    
    void unloadEffect(const char* pszFilePath) {
        CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(pszFilePath);
    }

};

#endif /* defined(__nmd__NMDAudioEngine__) */
