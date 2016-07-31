//
//  EndingScene.cpp
//  Novelio
//
//  Created by yokonami
//
//

#include "EndingScene.hpp"
#include <iostream>
#include <iomanip>

EndingScene* EndingScene::create(string filename){
    EndingScene* pRet = new (std::nothrow) EndingScene();
    
    if(pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool EndingScene::init(string filename){
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

void EndingScene::onEnterTransitionDidFinish(){
    Scene::onEnterTransitionDidFinish();
    
    gif->runAction(Sequence::create(
                                    FadeIn::create(5),
                                    CallFunc::create([this](){
            // タッチで閉じるためのリスナーを作成
            auto listener = cocos2d::EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan = [this](cocos2d::Touch *touch,cocos2d::Event* event)->bool{
                GameManager::getInstance()->onExitScript();
                return true;
            };
            auto dip = this->getEventDispatcher();
            dip->addEventListenerWithSceneGraphPriority(listener, this);
            dip->setPriority(listener, -1);
    }),
                                    NULL));
}