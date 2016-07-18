//
//  GameTextLabel.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

#include "GameTextLabel.h"
#include "string.h"

USING_NS_CC;

GameTextLabel::GameTextLabel(FontAtlas *atlas /* = nullptr */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                   TextVAlignment vAlignment /* = TextVAlignment::TOP */,bool useDistanceField /* = false */,bool useA8Shader /* = false */)
:presentLabelLength(0)
,fullLabelText()
{
    
}

GameTextLabel::~GameTextLabel()
{
}

GameTextLabel* GameTextLabel::createWithTTF(const TTFConfig& ttfConfig, int maxLineWidth, TextHAlignment alignment /* = TextHAlignment::CENTER */)
{
    
    auto ret = new GameTextLabel(nullptr,alignment);
    
    if (ret && FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) && ret->setTTFConfig(ttfConfig))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString("");
        ret->autorelease();
        ret->isRunningFlag = false;
        
        ret->setString("");
        
        ret->offsetLabelLength = 0;
        ret->presentLabelLength = 1;
        ret->n_presentLine = 0;
        ret->eachTextLengths.clear();
        ret->fullLabelText = "";
        ret->fullLabelLength = 0;

        
        return ret;
    }
    
    delete ret;
    return nullptr;
}

void GameTextLabel::setInterval(float interval){
    this->interval = interval;
}

void GameTextLabel::setText(const std::string &text){
    offsetLabelLength = 0;
    presentLabelLength = 1;
    n_presentLine = 0;
    this->eachTextLengths.clear();
    
    this->fullLabelText = text;
    this->fullLabelLength = text.length();
    this->eachTextLengths.push_back(text.length());
    
}

void GameTextLabel::setTexts(std::vector<std::string> texts){
    offsetLabelLength = 0;
    presentLabelLength = 1;
    n_presentLine = 0;
    
    this->fullLabelText = "";
    this->fullLabelLength = 0;
    this->eachTextLengths.clear();

    for(int i=0;i<texts.size();i++){
        this->fullLabelText += texts[i];
        this->fullLabelLength += texts[i].length();
        this->eachTextLengths.push_back(texts[i].length());
    }
}

void GameTextLabel::addText(std::string text){
    this->fullLabelText += text;
    this->fullLabelLength += text.length();
    this->eachTextLengths.push_back(text.length());
}

void GameTextLabel::setLineHeight(float lineHeight){
    this->lineHeight = lineHeight;
}

void GameTextLabel::setOriginalPosition(cocos2d::Point originalPoint){
    this->originalPoint = originalPoint;
    this->setPosition(this->originalPoint);
}

void GameTextLabel::showNoText(){
    this->setString("");
    
    offsetLabelLength = 0;
    presentLabelLength = 1;
    n_presentLine = 0;
    this->eachTextLengths.clear();
    this->fullLabelText = "";
    this->fullLabelLength = 0;
}

void GameTextLabel::run()
{
    this->isRunningFlag = true;

    if (_currentLabelType == LabelType::TTF) {
        
        Director::getInstance()->getScheduler()->schedule([this](float time) {
            if(this->delaySchedulingCounter > 0){
                this->delaySchedulingCounter --;
                return;
            }
            
            // 全部表示したら停止
            if(presentLabelLength >= this->fullLabelLength) {
                Director::getInstance()->getScheduler()->unschedule("textTimer", this);
//                this->callback();
                this->isRunningFlag = false;
                
                this->callback_para();
                this->callback();
                
            //一行表示したら停止
            }else if(presentLabelLength - offsetLabelLength >= this->eachTextLengths[n_presentLine]) {
                this->n_presentLine++;
                this->offsetLabelLength = this->presentLabelLength;
                
                Director::getInstance()->getScheduler()->unschedule("textTimer", this);
//                this->callback();
                this->isRunningFlag = false;
                
                this->callback_line();
                this->callback();
            
            }else{
                // マルチバイト対応
                unsigned char lead = this->fullLabelText[presentLabelLength];
                int charSize;
                if (lead < 0x80) {
                    charSize = 1;
                } else if (lead < 0xE0) {
                    charSize = 2;
                } else if (lead < 0xF0) {
                    charSize = 3;
                } else {
                    charSize = 4;
                }
                
                //句読点の遅延処理
                if (presentLabelLength == this->fullLabelLength - charSize){
                    //最後の文字は、ちょっと長く表示。
                    this->delaySchedulingCounter = 5;
                }else if(presentLabelLength - offsetLabelLength == this->eachTextLengths[n_presentLine] - charSize){
                    this->delaySchedulingCounter = 5;
                    
                }else if (fullLabelText.substr(presentLabelLength, charSize) == "、"){
                    this->delaySchedulingCounter = 3;
                }else if (fullLabelText.substr(presentLabelLength, charSize) == "。"){
                    this->delaySchedulingCounter = 5;
                }else if (fullLabelText.substr(presentLabelLength, charSize) == "？"){
                    this->delaySchedulingCounter = 5;
                }else if (fullLabelText.substr(presentLabelLength, charSize) == "！"){
                    this->delaySchedulingCounter = 5;
                }
                
                presentLabelLength += charSize;
                
                std::string s(this->fullLabelText, 0, presentLabelLength);
                this->setString(s);
                Label::setLineHeight(lineHeight);
                this->setPosition(Point(originalPoint.x + this->getSystemFontSize() / 2 + this->getContentSize().width / 2, originalPoint.y - this->getContentSize().height/2  - this->getSystemFontSize() ));
                
            }
        }, this, interval, -1, 0, false, "textTimer");
    }
}

void GameTextLabel::showAll()
{
    Director::getInstance()->getScheduler()->unschedule("textTimer", this);
    this->setString(fullLabelText);
    this->setPosition(Point(originalPoint.x + this->getSystemFontSize() / 2 + this->getContentSize().width / 2, originalPoint.y - this->getContentSize().height/2  - this->getSystemFontSize() ));
    
    this->callback_para();
    this->callback();
    
    this->isRunningFlag = false;
}

bool GameTextLabel::isRunning(void){
    return this->isRunningFlag;
}

void GameTextLabel::setOnEndsCallback(std::function<void(void)> callback){
    this->callback = callback;
}

void GameTextLabel::setOnLineEndsCallback(std::function<void(void)> callback){
    this->callback_line = callback;
}

void GameTextLabel::setOnParagraphEndsCallback(std::function<void(void)> callback){
    this->callback_para = callback;
}

std::string GameTextLabel::getFullLabelText(){
    return this->fullLabelText;
}
