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
#include "TitleScene.h"
#include "DataCaretaker.h"

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

    return true;
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    return true;
}

void UILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    NovelController::getInstance()->onDisplayTouched();    
}

bool UILayer::isWaitingClick(){
    bool res = false;
    
    res = func_isWaitingClick();

    if(!(this->isVisible())){
        res = true;
    }
    return res;
}

void UILayer::unWait(){
    ViewFunctions::unsetHideText();
    func_unWait();
}

void UILayer::unsetAutoMode(){
    func_unsetAutoMode();
}

NS_NV_END