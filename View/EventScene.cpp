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

EventScene* EventScene::create(string filename, bool waitClick){
    EventScene* pRet = new (std::nothrow) EventScene();
    
    if(pRet && pRet->init(filename, waitClick)){
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool EventScene::init(string filename, bool waitClick){
    if(!Scene::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    gif = Sprite::create(filename);
    gif->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    gif->setOpacity(0);
    
    this->waitClick = waitClick;
    
    this->addChild(gif);



    return true;
}

void EventScene::onEnterTransitionDidFinish(){
    Scene::onEnterTransitionDidFinish();
    
    gif->runAction(Sequence::create(
                                    FadeIn::create(5),
                                    CallFunc::create([this](){
        if(!(waitClick)){
            Director::getInstance()->popScene();
        }else{
            // タッチで閉じるためのリスナーを作成
            auto listener = cocos2d::EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan = [this](cocos2d::Touch *touch,cocos2d::Event*event)->bool{
                Director::getInstance()->popScene();
                return true;
            };
            auto dip = this->getEventDispatcher();
            dip->addEventListenerWithSceneGraphPriority(listener, this);
            dip->setPriority(listener, -1);
        }
    }),
                                    NULL));
}