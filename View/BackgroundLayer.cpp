﻿//
//  BackgroundLayer.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#include "BackgroundLayer.h"
#include "../Model/BackgroundLayerModel.h"
#include "SimpleAudioEngine.h"
#include "../GameManager.h"
#include "NMDAudioEngine.h"
#include "../Model/GameModel.h"

NS_NV_BEGIN

bool BackgroundLayer::init()
{
    
    if(!Layer::init()){
        return false;
    }
    GameManager::getInstance()->setBackgroundLayer(this);
    
    frontSprite = Sprite::create();
    frontSprite->setAnchorPoint(cocos2d::Point(0.5,0.5));
    frontSprite->setPosition(nv::PointFromCenter(0,0));
    
    this->addChild(frontSprite);
    
    this->setCascadeOpacityEnabled(true);
    
    this->flg_disableOnEnterTentatively = false;
    
    return true;
}

void BackgroundLayer::onEnter(){
    
    Layer::onEnter();
    
    if(flg_disableOnEnterTentatively){
        flg_disableOnEnterTentatively = false;
        return;
    }
    
    auto gm = GameManager::getInstance();
    gm->getBackgroundLayer()->setBackgroundImage();
    
    // @memo eventCGONからの戻りで、直前に再生したSEが再生されるバグがあったためコメントアウト
    auto bgm_path = GameModel::getInstance()->backgroundLayerModel->getBGMPath();
    NMDAudioEngine::getInstance()->playBackgroundMusic(bgm_path.c_str());
    //auto se_path = GameModel::getInstance()->backgroundLayerModel->getSEPath();
    //NMDAudioEngine::getInstance()->playEffect(se_path.c_str());
}

void BackgroundLayer::disableOnEnterTentatively(){
    this->flg_disableOnEnterTentatively = true;
}

void BackgroundLayer::setBackgroundImage(){
    string path = static_cast<BackgroundLayerModel*>(GameModel::getInstance()->backgroundLayerModel)->getBackgroundImagePath();
    frontSprite->setTexture(path);
};

//void BackgroundLayer::playBGM(bool loop){
//    string path = GameModel::getInstance()->backgroundLayerModel->getBGMPath();
////    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str(),true);
//    NMDAudioEngine::getInstance()->playBackgroundMusic(path.c_str(), loop);
//};
//
//void BackgroundLayer::stopBGM(){
//    NMDAudioEngine::getInstance()->stopBackgroundMusic();
//}
//
//void BackgroundLayer::playSE(bool loop){
//    string path = GameModel::getInstance()->backgroundLayerModel->getSEPath();
////    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());
//    NMDAudioEngine::getInstance()->playEffect(path.c_str(), loop);
//};

NS_NV_END