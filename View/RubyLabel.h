//
//  RubyLabel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/18.
//
//

#ifndef __Novelio__RubyLabel__
#define __Novelio__RubyLabel__

#include <vector>

#include "cocos2d.h"

USING_NS_CC;


class RubyLabel : public cocos2d::Node, public cocos2d::LabelProtocol{
public:
    RubyLabel();
    ~RubyLabel();
    static RubyLabel * createWithTTF(const std::string& text, const std::string& fontFile,
                                     float fontSize, float rubyfontSize = 0,
                                     const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                     TextVAlignment vAlignment = TextVAlignment::TOP);
protected:
    struct RubyIndex{
        int parentStart;
        int parentEnd;
        int rubyStart;
        int rubyEnd;
    };
    std::string fullText;
    std::string parentText;
    Label* parentLetters;
    std::string rubyText;
    Label* rubyLetters;
    std::vector<RubyIndex> rubyIndex;
    
public:
    void setString(const std::string& text);
    const std::string& getString() const override { return fullText; };
    void setColor(const Color3B &color);

void setLineHeight(float lineHeight);
void setMaxLineWidth(unsigned int maxLineWidth);
void adjustRubyPosition();
Size getContentSize();


protected:
int countByte(unsigned char);
int countString(const std::string text);

};

#endif /* defined(__Novelio__RubyLabel__) */
