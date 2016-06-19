//
//  TextLayerModel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#ifndef __Novelio__TextLayerModel__
#define __Novelio__TextLayerModel__

#include "../Macros.h"

class TextLayerModel {
    
private:
    std::string name;
    std::string text;
    std::vector<string> texts;

public:
    void setName(string name);
    string getName();
    void setText(string text);
    string getText();
    void setTexts(std::vector<std::string> texts);
    vector<string> getTexts();
    void addText(std::string text);

};

#endif /* defined(__Novelio__TextLayerModel__) */
