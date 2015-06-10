//
//  TextLayer.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#ifndef __Novelium__TextLayer__
#define __Novelium__TextLayer__

#include "cocos2d.h"
#include "../Novelio.h"
#include "GameTextLabel.h"

NS_NV_BEGIN

struct TextLayerConfig{
    string nameFontPath;
    int nameFontSize;
    const Color3B& nameColor;

    string textFontPath;
    int textFontSize;
    const Color3B& textColor;

    TextLayerConfig(string nameFontPath = "", int nameFontSize = 25, const Color3B& nameColor = Color3B::BLACK,
                    string textFontPath = "", int textFontSize = 30, const Color3B& textColor = Color3B::BLACK)
    :nameFontPath(nameFontPath)
    ,nameFontSize(nameFontSize)
    ,nameColor(nameColor)
    ,textFontPath(textFontPath)
    ,textFontSize(textFontSize)
    ,textColor(textColor){
    
    }
};

class TextLayer : public cocos2d::Layer, create_func<TextLayer>
{
public:
    bool init();
    using create_func::create;
    
    enum TextLayerState{INIT, SHOWING, STOP, COMPLETED} state;
    
    void initializeLayer();
    
    void setTextboxImage(std::string path);
    
    void setNameLabelPosition(cocos2d::Point position);
    void setNameLabelFont(std::string path);
    void setNameColor(const Color3B& color);
    void setNameFontSize(int size);
    
    void setTextPosition(cocos2d::Point position);
    void setTextWidth(int width);
    void setTextFont(std::string path);
    void setTextFontSize(int size);
    void setTextColor(const Color3B& color);
    void setTextSpeed(double speed);
    
    void setText();
    void setTexts();
    void addText();
    void setName(std::string name);
    void showName();
    
    void showNoText();
    void startText();
    void pauseText();
    void showAllText();
    
    Sprite* getTextBox();
    
private:
    Sprite* textBox;
    
    Label* nameLabel;
    std::string name;
    std::string nameFontPath;
    int nameFontSize;
    cocos2d::Point namePosition;
    
    GameTextLabel* textLabel;
    std::string text;
    std::string textFontPath;
    int textFontSize;
    cocos2d::Point textPosition;
    double textSpeed;
    
    void onTextEnds();
    void onLineEnds();
    void onParaEnds();
    
};

NS_NV_END

#endif /* defined(__Novelium__TextLayer__) */
