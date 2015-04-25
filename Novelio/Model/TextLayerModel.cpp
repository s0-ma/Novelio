//
//  TextLayerModel.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#include "TextLayerModel.h"

void TextLayerModel::setName(string name){
    this->name = name;
};

string TextLayerModel::getName(){
    return name;
}
void TextLayerModel::setText(string text){
    this->text = text;
};
string TextLayerModel::getText(){
    return text;
}
void TextLayerModel::setTexts(std::vector<std::string> texts){
    this->texts = texts;
};
vector<string> TextLayerModel::getTexts(){
    return texts;
}
void TextLayerModel::addText(std::string text){
    this->texts.push_back(text);
};
