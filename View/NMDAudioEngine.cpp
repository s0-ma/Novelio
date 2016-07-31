//
//  NMDAudioEngine.cpp
//  nmd
//
//  Created by Kainoki Kaede on 2014/10/06.
//
//

#include "NMDAudioEngine.h"
#include "Novelio.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;
#endif

// To make NMDAudioEngine as a singleton{
NMDAudioEngine* NMDAudioEngine::instance = 0;

NMDAudioEngine* NMDAudioEngine::getInstance() {
    if(instance == 0){
        instance = new NMDAudioEngine();
    }
    return instance;
}
// }

void NMDAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
    if (pszFilePath == this->currentBackgroundMusicFilePath) {
        return;
        // Note: in this implementation, if you try to play the same song with different loop option, the new loop option will be ignored. But what can I do? Remember the loop option and set it if it changes? This is possible, but it replays the music, and this was what we wanted to avoid (in other words, one of the purposes of creating this class), wasn't it? As a matter of fact, there is no way to reset the loop option without replaying the music.
    }
	this->previousBackgroundMusicFilePath = this->currentBackgroundMusicFilePath;
	this->currentBackgroundMusicFilePath = pszFilePath;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (bgm_playing){
		AudioEngine::stop(bgm_id);
	}
	float vol = nv::GameModel::getInstance()->getBgmVolume()/256.0;
	bgm_id = AudioEngine::play2d(pszFilePath, true, vol);
	bgm_playing = true;
	CCLOG("%s, volume = %f", pszFilePath, vol);
#else
    if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        stopBackgroundMusic(true);
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, bLoop);
#endif
    //CCLOG("%s", this->currentBackgroundMusicFilePath);
    //CCLOG("%s", this->previousBackgroundMusicFilePath);
    //CCLOG("%s", pszFilePath);
}

void NMDAudioEngine::stopBackgroundMusic(bool bReleaseData) {
    this->previousBackgroundMusicFilePath = this->currentBackgroundMusicFilePath;
    this->currentBackgroundMusicFilePath = nullptr;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (bgm_playing){
		AudioEngine::stop(bgm_id);
	}
	bgm_playing = false;
	bgm_id = -1;
#else
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(bReleaseData);
#endif
//    CCLOG("Music Stopped");
}

void NMDAudioEngine::pauseBackgroundMusic() {
    this->previousBackgroundMusicFilePath = this->currentBackgroundMusicFilePath;
    this->currentBackgroundMusicFilePath = nullptr;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (bgm_playing){
		AudioEngine::pause(bgm_id);
	}
#else
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
#endif
}

void NMDAudioEngine::resumeBackgroundMusic() {
    this->currentBackgroundMusicFilePath = this->previousBackgroundMusicFilePath;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (bgm_playing){
		AudioEngine::resume(bgm_id);
	}
#else
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
#endif
    // Note: in this implementation, the song before the paused song will not be remembered.
    //       To remember it, you can do something like: assume that song is playing while paused, and do not change prev/current file pathes. I'll code so if necessary.
}

void NMDAudioEngine::fadeBackgroundMusic(float fadeSeconds, float targetVolume) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    auto fadeMusicNode = cocos2d::Node::create();
    fadeMusicNode->runAction(cocos2d::Sequence::create(MusicFade::create(fadeSeconds, targetVolume, false),
                                                       cocos2d::RemoveSelf::create(),  // Kill this node after fade.
                                                       NULL));
    auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
    runningScene->addChild(fadeMusicNode);
#endif
}

void NMDAudioEngine::fadeBackgroundMusic(cocos2d::Node* node, float fadeSeconds, float targetVolume) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    if (!node) {
        this->fadeBackgroundMusic(fadeSeconds, targetVolume);
    }
    else {
        node->runAction(MusicFade::create(fadeSeconds, targetVolume, false));
    }
#endif
}

void NMDAudioEngine::fadeInBackgroundMusic(const char* pszFilePath, bool bLoop, float fadeInSeconds, float targetVolume) {
    this->fadeInBackgroundMusic(nullptr, pszFilePath, bLoop, fadeInSeconds, targetVolume);
}

void NMDAudioEngine::fadeInBackgroundMusic(cocos2d::Node* node, const char* pszFilePath, bool bLoop, float fadeInSeconds, float targetVolume) {
    if (pszFilePath == this->currentBackgroundMusicFilePath) {
        // Avoid fading the same music in.
        return;
    }
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	this->playBackgroundMusic(pszFilePath, bLoop);
#else
    this->setBackgroundMusicVolume(0.0);
    this->playBackgroundMusic(pszFilePath, bLoop);
    this->fadeBackgroundMusic(node, fadeInSeconds, targetVolume);
#endif
}

void NMDAudioEngine::fadeOutBackgroundMusic(bool bReleaseData, float fadeOutSeconds) {
    this->fadeOutBackgroundMusic(nullptr, bReleaseData, fadeOutSeconds);
}

void NMDAudioEngine::fadeOutBackgroundMusic(cocos2d::Node* node, bool bReleaseData, float fadeOutSeconds) {
    this->fadeBackgroundMusic(node, fadeOutSeconds, 0.0);
    if (!node) {
        node = cocos2d::Director::getInstance()->getRunningScene();
    }
    node->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(fadeOutSeconds),
                                    cocos2d::CallFunc::create([this](){this->pauseBackgroundMusic();}),
                                     NULL));
}

unsigned int NMDAudioEngine::playEffectWithDimmedBGM(const char* pszFilePath, bool bLoop) {
    // TODO: Implement the function.
    // Get length of the effect, dim the BGM for the length (save the default volume), and put volume up again.
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, bLoop);
}

unsigned int NMDAudioEngine::playEffectWithDimmedBGM(const char* pszFilePath) {
    return this->playEffectWithDimmedBGM(pszFilePath, false);
}

void NMDAudioEngine::memorizeBackgroundMusicVolume() {
    this->backgroundMusicVolumeMemory = this->getBackgroundMusicVolume();
}

void NMDAudioEngine::recallBackgroundMusicVolume() {
    this->setBackgroundMusicVolume(this->backgroundMusicVolumeMemory);
}
