//
//  GameTextLabel.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

#ifndef __Novelium__GameTextLabel__
#define __Novelium__GameTextLabel__

#include "cocos2d.h"

class GameTextLabel : public cocos2d::Label
{
public:
    GameTextLabel(cocos2d::FontAtlas *atlas = nullptr, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
             cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);
    virtual ~GameTextLabel();
    
    static GameTextLabel* createWithTTF(const cocos2d::TTFConfig& ttfConfig, int maxLineWidth, cocos2d::TextHAlignment alignment = cocos2d::TextHAlignment::LEFT);
    
    void setInterval(float interval);
    void setText(const std::string &text);
    void setTexts(std::vector<std::string> texts);
    void addText(std::string text);
    
    void setLineHeight(float lineHeight);
    
    void setOriginalPosition(cocos2d::Point originalPoint);
    
    void showNoText();
    void run();
    void showAll();
    
    bool isRunning(void);

    void setOnEndsCallback(std::function<void(void)> callback);
    
    void setOnLineEndsCallback(std::function<void(void)> callback);
    void setOnParagraphEndsCallback(std::function<void(void)> callback);
    
    
private:
    float interval = 0.01;
    int delaySchedulingCounter = 0;
    
    float lineHeight;
    
    int presentLabelLength;
    int offsetLabelLength;
    
    std::string fullLabelText;
    int fullLabelLength;
    std::vector<int> eachTextLengths;
    int n_presentLine;
    
    cocos2d::Point originalPoint;
    bool isRunningFlag;
    
    std::function<void(void)> callback = [](){};
    std::function<void(void)> callback_line = [](){};
    std::function<void(void)> callback_para = [](){};
};

#endif /* defined(__Novelium__GameTextLabel__) */
