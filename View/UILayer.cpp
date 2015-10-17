//
//  UILayer.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#include "UILayer.h"
#include "../Controller/NovelController.h"
#include "GameModel.h"
#include "GameManager.h"
#include "CCLuaEngine.h"
#include "ViewFunctions.h"


NS_NV_BEGIN

bool UILayer::init(){
    if(!LayerColor::initWithColor(Color4B(0,0,0,255))){
        return false;
    }
    GameManager::getInstance()->setUILayer(this);

    
    this->setOpacity(0);
    
    //タッチイベントのリスナー
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//trueなので、タッチイベントは貫通せずここで止まる。
    listener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(UILayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    //ボタン
    //LOG
    auto logBtn = MenuItemImage::create("nvRes/system/button_back.png",
                                        "nvRes/system/button_back_on.png",
                                        [](Ref* sender){
                                            auto scene = Director::getInstance()->getRunningScene();
                                            scene->addChild(LogLayer::create(), Z_SCENARIO_LOG);
                                            GameManager::getInstance()->getUILayer()->setVisible(false);
                                        });
    logBtn->setPosition(Vec2(250,-250));
    
    //SKIP
    auto skipBtn = MenuItemImage::create("nvRes/system/button_skip.png",
                                        "nvRes/system/button_skip_on.png",
                                        [](Ref* sender){
                                            ViewFunctions::setSkipMode();
                                        });
    skipBtn->setPosition(Vec2(320,-250));

    //AUTO
    auto autoBtn = MenuItemImage::create("nvRes/system/button_auto.png",
                                         "nvRes/system/button_auto_on.png",
                                         [](Ref* sender){
                                             ViewFunctions::setAutoMode();  
                                         });
    autoBtn->setPosition(Vec2(390,-250));
    
    auto menu = Menu::create(logBtn, skipBtn, autoBtn, NULL);
    addChild(menu);
    
    return true;
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    return true;
}

void UILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    NovelController::getInstance()->onDisplayTouched();    
}

NS_NV_END