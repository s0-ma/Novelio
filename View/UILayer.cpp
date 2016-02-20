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
                                             this->systemBtnPopup->setVisible(false);
                                         });
    autoBtn->setPosition(Vec2(290,-250));
    
    //System
    std::vector<string> systemBtnMenuPath = {
        "nvRes/system/button_system_save.png",
        "nvRes/system/button_system_load.png",
        "nvRes/system/button_system_backtitle.png",
        "nvRes/system/button_system_config.png"};
    
    cocos2d::Vector<MenuItem*> systemBtnItem;
    auto systemBtnCallback = [this](Ref* sender){
        MenuItem* item = (MenuItem*)sender;
        int tag = item->getTag();
        switch(tag){
                
            case 0 ://save
                break;
            case 1 ://load
                break;
            case 2 :{//back to title
                auto nextScene = TitleScene::create();
                auto trans = TransitionFade::create(1.0f,nextScene);
                Director::getInstance()->replaceScene(trans);
                break;}
            case 3 ://config
                break;
            default:
                break;
        }
        this->systemBtnPopup->setVisible(false);
    };
    for(int i = 0; i < 4; i++){
        auto s = Sprite::create(systemBtnMenuPath[i]);
        auto nsf = SpriteFrame::createWithTexture(s->getTexture(), Rect(0, 0, 125, 50));
        auto ssf = SpriteFrame::createWithTexture(s->getTexture(), Rect(125, 0, 125, 50));
        auto mii = MenuItemImage::create();
        mii->setNormalSpriteFrame(nsf);
        mii->setSelectedSpriteFrame(ssf);
        mii->setTag(i);
        mii->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        mii->setCallback(systemBtnCallback);
        mii->setPosition(Vec2(0 ,-38*i));
        systemBtnItem.pushBack(mii);
    }
    
    auto systemBtnPopupMenu = Menu::createWithArray(systemBtnItem);
    systemBtnPopupMenu->ignoreAnchorPointForPosition(false);
    systemBtnPopup = Layer::create();
    systemBtnPopup->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    
    auto systemBtnPopupBack = Sprite::create("nvRes/system/box_system.png");
    systemBtnPopupBack->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    
    systemBtnPopup->setPosition(Vec2(820, 230));
    addChild(systemBtnPopup);
    systemBtnPopup->addChild(systemBtnPopupBack);
    systemBtnPopup->addChild(systemBtnPopupMenu);
    systemBtnPopup->setVisible(false);//非表示
    systemBtn = MenuItemImage::create("nvRes/system/button_system.png",
                                         "nvRes/system/button_system_on.png",
                                         [this](Ref* sender){
                                             this->systemBtnPopup->setVisible(true);
                                             this->autoBtnPopup->setVisible(false);
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
    
    
    //For DEBUG
    auto pLabel = Label::createWithSystemFont("1", "Arial", 50);
    auto debugButton = MenuItemLabel::create(pLabel,
                                         [](Ref* sender){
                                            CareTaker::getInstance()->storeMemento(1);
                                         });
    debugButton->setPosition(Vec2(330,+250));
    menu->addChild(debugButton);
    auto pLabel2 = Label::createWithSystemFont("2", "Arial", 50);
    auto debugButton2 = MenuItemLabel::create(pLabel2,
                                         [](Ref* sender){
                                            CareTaker::getInstance()->loadMemento(1);
                                         });
    debugButton2->setPosition(Vec2(430,+250));
    menu->addChild(debugButton2);
    
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
    if(this->systemBtnPopup->isVisible()){
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
    this->systemBtnPopup->setVisible(false);
}

void UILayer::unsetAutoMode(){
    this->autoBtn->setScale(1.0);
    this->autoBtn->setNormalImage(Sprite::create("nvRes/system/button_auto.png"));
}

NS_NV_END