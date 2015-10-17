//
//  PortraitLayer.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#include "PortraitLayer.h"
#include "Portrait.h"

#include "../Utils/Split.h"

#include "GameModel.h"
#include "GameManager.h"

NS_NV_BEGIN

bool PortraitLayer::init(){
    if(!Layer::init()){
        return false;
    }
    GameManager::getInstance()->setPortraitLayer(this);

    
    this->setCascadeOpacityEnabled(true);

    return true;
}

Portrait* PortraitLayer::getPortrait(string id){
    if(portraits.count(id) == 0){
        return nullptr;
    }else{
        return portraits[id];
    }
    };


void PortraitLayer::addPortrait(string id){
    auto basePath = GameModel::getInstance()->portraitLayerModel->portraits[id].basePath;
//    CCLOG("%s", basePath.c_str());
    portraits[id] = Portrait::create(basePath);
    addChild(portraits[id]);
};

void PortraitLayer::setPortraitPosition(std::string id){
    auto x = GameModel::getInstance()->portraitLayerModel->portraits[id].x;
    auto y = GameModel::getInstance()->portraitLayerModel->portraits[id].y;
    portraits[id]->setPosition(x, y);
};

void PortraitLayer::movePortrait(std::string id, int t_sec){
    auto x = GameModel::getInstance()->portraitLayerModel->portraits[id].x;
    auto y = GameModel::getInstance()->portraitLayerModel->portraits[id].y;
    portraits[id]->runAction(MoveTo::create(t_sec, Vec2(x, y)));
};

void PortraitLayer::cutinPortrait(std::string id){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    if(portraits.count(id) != 0){
        portraits[id]->setOpacity(255);
    }else{
        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
                        GameModel::getInstance()->getLine(), id.c_str());
    }
};

void PortraitLayer::fadeinPortrait(std::string id, int t_sec){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    portraits[id]->runAction(FadeIn::create(t_sec));
}

void PortraitLayer::cutoutPortrait(std::string id){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    if(portraits.count(id) != 0){
        portraits[id]->setOpacity(0);
        portraits[id]->removeEmoticon();
    }else{
        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
                        GameModel::getInstance()->getLine(), id.c_str());
    }
};

void PortraitLayer::fadeoutPortrait(std::string id, int t_sec){
    portraits[id]->runAction(Spawn::create(FadeOut::create(t_sec),
                                           CallFunc::create([this, id](){
                                                portraits[id]->removeEmoticon();
                                           }),
                                           NULL));
};

void PortraitLayer::cutinFace(std::string id, string faceId){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    auto facePath = GameModel::getInstance()->portraitLayerModel->portraits[id].facePool[faceId];
    auto FaceKey = facePath;
    if (faceId != "" && facePath == ""){
        CCLOG("l:%d, face not found. %s : %s",GameModel::getInstance()->getLine(),id.c_str(), faceId.c_str() );
        return;
    }
    
    if(portraits.count(id) != 0){
        portraits[id]->setOpacity(255);
        portraits[id]->changeFace(facePath);
    }else{
        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
                        GameModel::getInstance()->getLine(), id.c_str());
    }
};

void PortraitLayer::fadeinFace(std::string id, string faceId){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    
};

void PortraitLayer::removePortrait(std::string id){
    auto basePath = GameModel::getInstance()->portraitLayerModel->portraits[id].basePath;
    portraits[id] = Portrait::create(basePath);
    removeChild(portraits[id]);
};

void PortraitLayer::clear(){
    
};

NS_NV_END