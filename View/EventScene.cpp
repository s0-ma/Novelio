//
//  EventScene.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/07/18.
//
//

#include "EventScene.hpp"
#include <iostream>
#include <iomanip>

EventScene* EventScene::create(string filename){
    EventScene* pRet = new (std::nothrow) EventScene();
    
    if(pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool EventScene::init(string filename){
    if(!Scene::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    gif = Sprite::create(filename);
    gif->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    gif->setOpacity(0);
    
    this->addChild(gif);
    return true;
}

void EventScene::onEnterTransitionDidFinish(){
    Scene::onEnterTransitionDidFinish();
    
    gif->runAction(Sequence::create(
                                    FadeIn::create(5),
                                    CallFunc::create([](){
        Director::getInstance()->popScene();
    }),
                                    NULL));
}