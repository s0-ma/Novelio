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
#include "Split.h"

NS_NV_BEGIN

int LogLayer::maxLogLine = 1000;

bool LogLayer::init(){
    if(! Layer::init()){
        return false;
    }
    
    
    //キーボードイベントのリスナー
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(LogLayer::onKeyPressed, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    
    //
    GameManager::getInstance()->setLogLayer(this);
    ModalLayerDecorator::makeModal(this);
    
    //背面
    setBackground("nvRes/system/box_backlog.png");
    

    //scroll view
    auto size = Director::getInstance()->getVisibleSize();
#ifdef TASOMACHI
    scrollView = cocos2d::extension::ScrollView::create(Size(1024, 576));
    scrollView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    scrollView->setPosition(PointFromCenter(-512, -288));
#else
    scrollView = cocos2d::extension::ScrollView::create(size);
#endif
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    addChild(scrollView, 20);
    
    auto base = Layer::create();
    
    //log text
    vector<string> log_data = GameModel::getInstance()->logLayerModel->getLog();
    int log_start_index = 0;
    if(log_data.size() > maxLogLine){
        log_start_index = log_data.size() - maxLogLine;
    }
    
    
    //label
    label = Label::createWithTTF("", "nvRes/fonts/ipamp.ttf", 25);
    string log = shapeLog(log_data, log_start_index, log_data.size());
    label->setString(log);
    label->setLineHeight(35.0);//行間の設定
    label->setWidth(size.width * 0.65);//左右に5%のマージンをつける
    label->setColor(Color3B::BLACK);

    label->setPosition(Vec2(0,0));
    base->addChild(label);

    //namelabel
    nameLabel = Label::createWithTTF("", "nvRes/fonts/ipamp.ttf", 25);
    string name = shapeLogName(log_data, log_start_index, log_data.size());
    nameLabel->setString(name);
    nameLabel->setHorizontalAlignment(TextHAlignment::RIGHT);
    nameLabel->setLineHeight(35.0);//行間の設定
    nameLabel->setWidth(size.width * 0.1);//左右に5%のマージンをつける
    nameLabel->setColor(Color3B::BLACK);

    label->setPosition(Vec2(0,0));
    base->addChild(nameLabel);
    
    
    scrollView->setContainer(base);
    
    this->setContentSize();

    //前面
    auto backBtn = MenuItemImage::create("nvRes/iPhone_UI_png/config_back.png",
                                         "nvRes/iPhone_UI_png/config_back.png",
                                         [=](Ref* sender){
                                             hideLogLayer();
                                             
                                         });
    backBtn->setPosition(Vec2(380,-230));
    
    auto menu = Menu::create(backBtn, NULL);
    addChild(menu, 30);

#ifdef TASOMACHI
    //COVER LAYER
    auto w =  Director::getInstance()->getWinSize().width;
    auto h =  Director::getInstance()->getWinSize().height;
    
    auto cover_down = Sprite::create();
    cover_down->setTextureRect(Rect(0,0,w,(h-576)/2) );
    cover_down->setColor(Color3B(128, 128, 128));
    cover_down->setOpacity(1);
    cover_down->setPosition(PointFromCenter(0,-h/2 + (h-576)/2/2));
    auto cover_up = Sprite::create();
    cover_up->setTextureRect(Rect(0,0,w,(h-576)/2) );
    cover_up->setColor(Color3B(128, 128, 128));
    cover_up->setOpacity(1);
    cover_up->setPosition(PointFromCenter(0,h/2 - (h-576)/2/2));
    
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ZERO;
    
    cover_down->setBlendFunc(blend);
    cover_up->setBlendFunc(blend);
    this->addChild(cover_down);
    this->addChild(cover_up);
#endif
    
    return true;
    
}

void LogLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    Vec2 offsetShiftPx = Vec2(0, 50);
    if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW||
       keyCode == EventKeyboard::KeyCode::KEY_KP_UP){
        auto offset = scrollView->getContentOffset();
        scrollView->setContentOffset(offset - offsetShiftPx);
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW||
       keyCode == EventKeyboard::KeyCode::KEY_KP_DOWN){
        auto offset = scrollView->getContentOffset();
        if(offset.y > 0){
            // 閉じる
            hideLogLayer();
        }else{
            scrollView->setContentOffset(offset + offsetShiftPx);
        }
    }
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
    auto startx = size.width * 0.20;
    auto starty = size.height * 0.00;
    
    auto name_startx = size.width * 0.05;
    
    //ラベルが画面サイズより大きい場合
    if(label->getContentSize().height > size.height){
        label->setPosition(PointFromBottomLeft(startx, starty));
        label->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        nameLabel->setPosition(PointFromBottomLeft(name_startx, starty));
        nameLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        scrollView->setContentSize(Size(size.width, nameLabel->getContentSize().height));
    //ラベルが画面サイズより小さい場合
    }else{
        label->setPosition(PointFromTopLeft(startx, -starty));
        label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        nameLabel->setPosition(PointFromTopLeft(name_startx, -starty));
        nameLabel->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        scrollView->setContentSize(size);
    }
}

void LogLayer::showLog(){
    
}

void LogLayer::hideLogLayer(){
    GameManager::getInstance()->getUILayer()->setVisible(true);
    GameManager::getInstance()->getTextLayer()->setVisible(true);
    GameManager::getInstance()->getUILayer()->addKeyEventListener();
    this->removeFromParent();
}
string LogLayer::shapeLog(vector<string> log_data, int start, int end){
    string ret = "";
    for (int i = start; i<end; i++){
        //ret += ":" + log_data[i];
        string tmp = "";
        if(log_data[i].find("%") == 0){
            tmp = split(log_data[i], ' ')[1];
        }else{
            tmp = log_data[i];
        }
        
        ret += tmp;
    }
    
    return ret;
}

string LogLayer::shapeLogName(vector<string> log_data, int start, int end){
    string currentSpeaker;
    bool isSpeaking = false;
    
    string ret = "";
    
    auto dummy = Label::createWithTTF("", "nvRes/fonts/ipamp.ttf", 25);
    auto size = Director::getInstance()->getVisibleSize();
    dummy->setWidth(size.width * 0.65);//左右に5%のマージンをつける
    dummy->setLineHeight(35.0);//行間の設定
    
    for (int i = start; i<end; i++){
        //発話中
        if(isSpeaking){
            if(log_data[i].find("%") == 0){
                currentSpeaker = "";
                dummy->setString(split(log_data[i], ' ')[1]);
            }else{
                currentSpeaker = "";
                dummy->setString(log_data[i]);
            }
        }else{
            if(log_data[i].find("%") == 0){
                isSpeaking = true;
                currentSpeaker = split(log_data[i].substr(1), ' ')[0];
                dummy->setString(split(log_data[i], ' ')[1]);
            }else{
                currentSpeaker = "";
                dummy->setString(log_data[i]);
            }
        }
        
        //発話終了
        if(log_data[i].find("」") != -1){
            isSpeaking = false;
        }
        
        
        
        ret += currentSpeaker;
        
        for(int j=0; j<dummy->getStringNumLines(); j++){
           ret += "\n";
        }
    }
    
    return ret;
}
NS_NV_END
