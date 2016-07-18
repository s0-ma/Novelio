//
//  LogLayer.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#include "LogLayer.h"



#include "../GameManager.h"
#include "../Model/GameModel.h"
#include "RubyLabel.h"
#include "ModalLayerDecorator.h"

NS_NV_BEGIN

int LogLayer::maxLogLine = 1000;

bool LogLayer::init(){
    if(! Layer::init()){
        return false;
    }
    
    //
    GameManager::getInstance()->setLogLayer(this);
    ModalLayerDecorator::makeModal(this);
    
    //背面
    setBackground("nvRes/system/box_backlog.png");
    

    //scroll view
    auto size = Director::getInstance()->getVisibleSize();
    scrollView = cocos2d::extension::ScrollView::create(size);
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    addChild(scrollView, 20);
    
    auto base = Layer::create();
    
    //log text
    vector<string> log_data = GameModel::getInstance()->logLayerModel->getLog();
    string log = "";
    for (int i=log_data.size() - maxLogLine ; i<log_data.size(); i++){
        log += log_data[i] + "\n";
    }
    
    //label
    label = Label::createWithTTF("", "res/fonts/ipamp.ttf", 25);
    label->setString(log);
    label->setLineHeight(35.0);//行間の設定
    label->setWidth(size.width * 0.9);//左右に5%のマージンをつける
    label->setColor(Color3B::BLACK);


    base->addChild(label);

    scrollView->setContainer(base);
    
    this->setContentSize();

    //前面
    auto backBtn = MenuItemImage::create("nvRes/system/button_log_back.png",
                                         "nvRes/system/button_log_back_on.png",
                                         [=](Ref* sender){
                                             GameManager::getInstance()->getUILayer()->setVisible(true);
                                             this->removeFromParent();
                                             
                                         });
    backBtn->setPosition(Vec2(400,-250));
    
    auto menu = Menu::create(backBtn, NULL);
    addChild(menu, 30);

    
    return true;
    
}

void LogLayer::setBackground(string path){
    auto background = Sprite::create(path);
    background->setAnchorPoint(Vec2(0.5,0.5));
    background->setPosition(PointFromCenter(0,0));
    addChild(background);
}

void LogLayer::setContentSize(){
    auto size = Director::getInstance()->getVisibleSize();
    //画面端のマージンを、画面全体の5%に設定
    auto startx = size.width * 0.05;
    auto starty = size.height * 0.05;
    //ラベルが画面サイズより大きい場合
    if(label->getContentSize().height > size.height){
        label->setPosition(PointFromBottomLeft(startx, starty));
        label->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        scrollView->setContentSize(label->getContentSize());
    //ラベルが画面サイズより小さい場合
    }else{
        label->setPosition(PointFromTopLeft(startx, -starty));
        label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        scrollView->setContentSize(size);
    }
}

void LogLayer::showLog(){
    
}

NS_NV_END