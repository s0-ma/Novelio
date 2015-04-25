//
//  LogLayer.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#include "LogLayer.h"
#include "GameManager.h"

#include "GameModel.h"

#include "RubyLabel.h"

#include "ModalLayerDecorator.h"

NS_NV_BEGIN

bool LogLayer::init(){
    if(! Layer::init()){
        return false;
    }
    
    //
    GameManager::getInstance()->setLogLayer(this);
    ModalLayerDecorator::makeModal(this);
    
    //背面
    setBackground("nvRes/system/box_backlog.png");
    
    

//    scroll view
    auto size = Director::getInstance()->getVisibleSize();
    auto scrollView = cocos2d::extension::ScrollView::create(size);
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
//    scrollView->setAnchorPoint(Vec2(0.,0.));
//    scrollView->setPosition(0,0);
    addChild(scrollView);
    
//    auto base = Layer::create();
    
    //log text
    vector<string> log_data = GameModel::getInstance()->logLayerModel->getLog();
    string log = "";
    for (int i=0; i<log_data.size(); i++){
        log += log_data[i] + "\n";
    }
    
    Label* label = Label::createWithTTF("", "res/fonts/ipamp.ttf", 25);
    label->setString(log);
    label->setColor(Color3B(255, 0, 127));

//    auto hoge= Sprite::create("nvRes/character/ame/ame.png");
//    label->setPosition(PointFromCenter(0, 0));
    
//    base->addChild(hoge);
//    base->addChild(label);
//    scrollView->setPosition(Vec2(0,0));
//    addChild(base);
    scrollView->setContainer(label);
    scrollView->setContentSize(label->getContentSize());
    CCLOG("%f",label->getContentSize().height);
//    CCLOG("%f",Sprite::create("nvRes/character/ame/ame.png")->getContentSize().height);
//    scrollView->setBounceable(true);
    

    //前面
    auto backBtn = MenuItemImage::create("nvRes/system/button_log_back.png",
                                         "nvRes/system/button_log_back_on.png",
                                         [=](Ref* sender){
                                             GameManager::getInstance()->getUILayer()->setVisible(true);
                                             this->removeFromParent();
                                             
                                         });
    backBtn->setPosition(Vec2(400,-250));
    
    auto menu = Menu::create(backBtn, NULL);
    addChild(menu);

    
    return true;
    
}

void LogLayer::setBackground(string path){
    auto background = Sprite::create(path);
    background->setAnchorPoint(Vec2(0.5,0.5));
    background->setPosition(PointFromCenter(0,0));
    addChild(background);
}
NS_NV_END