//
//  TextLayer.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#include "cocos2d.h"
#include "TextLayer.h"
#include "../Controller/NovelControler.h"
#include "GameModel.h"
#include "GameManager.h"

#define SKIP_SPEED 0.1

NS_NV_BEGIN

bool TextLayer::init(){
    if(!Layer::init()){
        return false;
    }
    GameManager::getInstance()->setTextLayer(this);

    this->setCascadeOpacityEnabled(true);
    
    
    initializeLayer();
    
    //表示状態
    this->state = COMPLETED;
    
    return true;
}

void TextLayer::initializeLayer(){
    //nameLabel
    nameFontPath = "nvRes/fonts/ipamp.ttf";
    nameFontSize = 25;
    
    textFontPath = "nvRes/fonts/ipamp.ttf";
    textFontSize = 30;
    
    name="";
    
    TTFConfig nameConf = TTFConfig(nameFontPath.c_str(), nameFontSize, GlyphCollection::DYNAMIC);
    nameLabel = Label::createWithTTF(nameConf,name);
    setNameColor(Color3B::BLACK);
    this->addChild(nameLabel,20);
    
    //textLabel
    text = "";
    
    TTFConfig textConf = TTFConfig(textFontPath.c_str(), textFontSize, GlyphCollection::DYNAMIC);
    textLabel = GameTextLabel::createWithTTF(textConf,600);
    textLabel->setOnEndsCallback([this](){this->onTextEnds();});
    textLabel->setOnLineEndsCallback([this](){this->onLineEnds();});
    textLabel->setOnParagraphEndsCallback([this](){this->onParaEnds();});
    setTextColor(Color3B::BLACK);
    textLabel->setVerticalAlignment(cocos2d::TextVAlignment::TOP);
    textLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    setTextSpeed(20);
    setLineHeight(textFontSize);
    this->addChild(textLabel,20);
    
    //textBox
    setTextboxImage("nvRes/system/box_text.png");
    setNameLabelPosition(nv::PointFromCenter(-420, -120));
    
    setTextPosition(nv::PointFromCenter(-450, -150));
    setTextWidth(900);


}

void TextLayer::setNameLabelPosition(cocos2d::Point position){
    namePosition = position;
    nameLabel->setPosition(position);
};
void TextLayer::setNameLabelFont(std::string path){
    nameFontPath = path;
    TTFConfig nameConf = TTFConfig(nameFontPath.c_str(), nameFontSize, GlyphCollection::DYNAMIC);
    nameLabel->setTTFConfig(nameConf);
};
void TextLayer::setNameColor(const cocos2d::Color3B& color){
    nameLabel->setColor(color);
};
void TextLayer::setNameFontSize(int size){
    nameFontSize = size;
    TTFConfig nameConf = TTFConfig(nameFontPath.c_str(), nameFontSize, GlyphCollection::DYNAMIC);
    nameLabel->setTTFConfig(nameConf);
}

void TextLayer::setName(std::string name){
    this->name = name;
    nameLabel->setString(name);
};


void TextLayer::setTextboxImage(std::string path){
    textBox = Sprite::create(path);
    textBox->setAnchorPoint(cocos2d::Point(0.5,0.5));
    textBox->setPosition(nv::PointFromCenter(0,0));
    this->addChild(textBox,0);
};


void TextLayer::setTextPosition(cocos2d::Point position){
    textPosition = position;
    textLabel->setOriginalPosition(textPosition);
};
void TextLayer::setTextWidth(int width){
    textLabel->setMaxLineWidth(width);
}
void TextLayer::setTextFont(std::string path){
    textFontPath = path;
    TTFConfig textConf = TTFConfig(textFontPath.c_str(), textFontSize, GlyphCollection::DYNAMIC);
    textLabel->setTTFConfig(textConf);
};
void TextLayer::setTextFontSize(int size){
    textFontSize = size;
    TTFConfig textConf = TTFConfig(textFontPath.c_str(), textFontSize, GlyphCollection::DYNAMIC);
    textLabel->setTTFConfig(textConf);
};
void TextLayer::setTextColor(const cocos2d::Color3B &color){
    textLabel->setColor(color);
};

void TextLayer::setText(){
    std::string text = GameModel::getInstance()->textLayerModel->getText();
    this->text = text;
    textLabel->setText(text);
};
void TextLayer::setTexts(){
    std::vector<std::string> texts = GameModel::getInstance()->textLayerModel->getTexts();
    this->text = "";
    for(int i=0; i<text.size(); i++){
        this->text += texts[i];
    }
    textLabel->setTexts(texts);
};
void TextLayer::addText(){
    std::vector<std::string> texts = GameModel::getInstance()->textLayerModel->getTexts();
    this->text += texts[texts.size()-1];
    textLabel->addText(texts[texts.size()-1]);
};

void TextLayer::setTextSpeed(double speed){
    textSpeed = speed;
};

void TextLayer::setLineHeight(float lineHeight){
    textLabel->setLineHeight(lineHeight);
};

void TextLayer::showNoText(){
    textLabel->showNoText();
}

void TextLayer::startText(){
    if(GameModel::getInstance()->getScenarioMode() != GameModel::SKIP){
        this->state = SHOWING;
        textLabel->setInterval(1./textSpeed);
        textLabel->run();
    }else{
        textLabel->showAll();
        //            auto nc = NovelControler::getInstance();
        //            nc->onDisplayTouched();
    }
};
void TextLayer::pauseText(){
    CCLOG("TextLayer::pauseText is not coded yet.");
};
void TextLayer::showAllText(){
    textLabel->showAll();
};

void TextLayer::onTextEnds(){
    auto gm = GameModel::getInstance();
    if(gm->getScenarioMode() == GameModel::AUTO){
        auto nc = NovelControler::getInstance();
        nc->_execNextLine();
    }else if(gm->getScenarioMode() == GameModel::SKIP){
        this->runAction(Sequence::create(DelayTime::create(SKIP_SPEED),CallFunc::create([this](){
            auto nc = NovelControler::getInstance();
            nc->_execNextLine();
        }), NULL));
    }
};
void TextLayer::onLineEnds(){
    this->state = STOP;
    //        CCLOG("onLineEnds");
};
void TextLayer::onParaEnds(){
    this->state = COMPLETED;
    //        CCLOG("onParaEnds");
};

Sprite* TextLayer::getTextBox(){
    return textBox;
}

NS_NV_END