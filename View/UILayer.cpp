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
    logBtn->setPosition(Vec2(150,-250));
    
    //SKIP
    auto skipBtn = MenuItemImage::create("nvRes/system/button_skip.png",
                                        "nvRes/system/button_skip_on.png",
                                        [](Ref* sender){
                                            ViewFunctions::setSkipMode();
                                        });
    skipBtn->setPosition(Vec2(220,-250));

    //AUTO
    std::vector<string> autoBtnMenuSpeedxPath = {
        "nvRes/system/button_auto_speedx1.png",
        "nvRes/system/button_auto_speedx2.png",
        "nvRes/system/button_auto_speedx4.png",
        "nvRes/system/button_auto_speedx8.png",
        "nvRes/system/button_auto_speedx16.png"};

    cocos2d::Vector<MenuItem*> autoBtnSpeedx;
    auto autoBtnCallback = [this](Ref* sender){
        std::vector<string> autoBtnSpeedxPath = {
            "nvRes/system/button_speedx1.png",
            "nvRes/system/button_speedx2.png",
            "nvRes/system/button_speedx4.png",
            "nvRes/system/button_speedx8.png",
            "nvRes/system/button_speedx16.png"};
        MenuItem* item = (MenuItem*)sender;
        int tag = item->getTag();
        ViewFunctions::setAutoModeSpeed(tag);
        ViewFunctions::setAutoMode();
        this->autoBtnPopup->setVisible(false);
        this->autoBtn->setNormalImage(Sprite::create(autoBtnSpeedxPath[tag]));
        this->autoBtn->setScale(1.5);
    };
    for(int i = 0; i < 5; i++){
        auto s = Sprite::create(autoBtnMenuSpeedxPath[i]);
        auto nsf = SpriteFrame::createWithTexture(s->getTexture(), Rect(0, 0, 45, 30));
        auto ssf = SpriteFrame::createWithTexture(s->getTexture(), Rect(45, 0, 45, 30));
        auto mii = MenuItemImage::create();
        mii->setNormalSpriteFrame(nsf);
        mii->setSelectedSpriteFrame(ssf);
        mii->setTag(i);
        mii->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        mii->setCallback(autoBtnCallback);
        mii->setPosition(Vec2(0 ,-25*i));
        autoBtnSpeedx.pushBack(mii);
    }
    
    auto autoBtnPopupMenu = Menu::createWithArray(autoBtnSpeedx);
    autoBtnPopupMenu->ignoreAnchorPointForPosition(false);
    autoBtnPopup = Layer::create();
    autoBtnPopup->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    
    auto autoBtnPopupBack = Sprite::create("nvRes/system/box_auto.png");
    autoBtnPopupBack->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    
    autoBtnPopup->setPosition(Vec2(800, 200));
    addChild(autoBtnPopup);
    autoBtnPopup->addChild(autoBtnPopupBack);
    autoBtnPopup->addChild(autoBtnPopupMenu);
    autoBtnPopup->setVisible(false);//非表示
    
    autoBtn = MenuItemImage::create("nvRes/system/button_auto.png",
                                         "nvRes/system/button_auto_on.png",
                                         [this](Ref* sender){
                                             this->autoBtnPopup->setVisible(true);
                                         });
    autoBtn->setPosition(Vec2(290,-250));
    
    //System
    auto systemBtn = MenuItemImage::create("nvRes/system/button_system.png",
                                         "nvRes/system/button_system_on.png",
                                         [](Ref* sender){
                                             ViewFunctions::setAutoMode();
                                         });
    systemBtn->setPosition(Vec2(360,-250));
    
    //Hide Text
    auto hideTextBtn = MenuItemImage::create("nvRes/system/button_hidetext.png",
                                         "nvRes/system/button_hidetext_on.png",
                                         [](Ref* sender){
                                             ViewFunctions::hideText();
                                         });
    hideTextBtn->setPosition(Vec2(430,-250));
    
    auto menu = Menu::create(logBtn, skipBtn, autoBtn, systemBtn, hideTextBtn, NULL);
    addChild(menu);
    
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
    if(this->autoBtnPopup->isVisible()){
        res = true;
    }
    if(!(this->isVisible())){
        res = true;
    }
    return res;
}

void UILayer::unWait(){
    ViewFunctions::unsetHideText();
    this->autoBtnPopup->setVisible(false);
}

void UILayer::unsetAutoMode(){
    this->autoBtn->setScale(1.0);
    this->autoBtn->setNormalImage(Sprite::create("nvRes/system/button_auto.png"));
}

NS_NV_END