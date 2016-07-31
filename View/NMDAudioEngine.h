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
#include "Novelio.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;
#endif

class NMDAudioEngine{
    
private:
    static NMDAudioEngine* instance;
    // To make NMDAudioEngine as a singleton{
    NMDAudioEngine(void) : bgm_playing(false), bgm_id(-1) {}
    NMDAudioEngine(const NMDAudioEngine& other){}
    NMDAudioEngine& operator=(const NMDAudioEngine& other);
    // }
	bool bgm_playing;
	int bgm_id;
	vector<int> se_id;
	void seFinishCallBack(int id, string){
		se_id.erase(remove(se_id.begin(), se_id.end(), id), se_id.end());
	};

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		if (bgm_id != -1 && bgm_playing){
			AudioEngine::setVolume(bgm_id, volume);
		}
#else
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
#endif
    }

    float getEffectsVolume() {
        return CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
    }

    void setEffectsVolume(float volume) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		for_each(se_id.begin(), se_id.end(), [=](int id){
			AudioEngine::setVolume(id, volume);
		});
#else
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
#endif
    }

    // for sound effects
    unsigned int playEffect(const char* pszFilePath, bool bLoop) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		float vol = nv::GameModel::getInstance()->getSeVolume() / 256.0;
		int id = AudioEngine::play2d(pszFilePath, bLoop, vol);
		se_id.push_back(id);
		AudioEngine::setFinishCallback(id, CC_CALLBACK_2(NMDAudioEngine::seFinishCallBack, this));
		return 0;
#else
        return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, bLoop);
#endif
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		for_each(se_id.begin(), se_id.end(), [](int id){
			AudioEngine::stop(id);
		});
		se_id.clear();
#else
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
#endif
    }
    
    void preloadEffect(const char* pszFilePath) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(pszFilePath);
    }
    
    void unloadEffect(const char* pszFilePath) {
        CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(pszFilePath);
    }

};

#endif /* defined(__nmd__NMDAudioEngine__) */
