//
//  ScriptParser.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

/*!
 @file      ScriptParser.cpp
 @ingroup   Controller
 @brief
 @date      2014/10/12
 @author    Tatsuya Soma
 */

#include <iostream>
#include <regex>
#include <string>
#include <locale>

#include "ScriptParser.h"
#include "Split.h"

#include "cocos2d.h"

#include "GameModel.h"
#include "GameManager.h"

#include <fstream>

NS_NV_BEGIN

ScriptParser::ScriptParser(){
    
};

std::string ScriptParser::Novelio(std::string string){
    
    this->mainLoop(string);
    
    std::string ret = string;
    return ret;
    
};


void ScriptParser::mainLoop(string string){
    
    //std::string filePath = FileUtils::getInstance()->fullPathForFilename(string);
    ifs.open(string.c_str());
    
    if (ifs.fail()){
        CCLOG("Fail to open script file: %s", string.c_str());
        return;
    }
    
    while(1){
        std::string str = getNextToken();
        if(!ifs.eof()){
            CCLOG("*%s", str.c_str());
        }else{
            break;
        }
    }
    
};

string ScriptParser::getNextLetter(){
    std::string str;
    str = ifs.get();
    
    unsigned char lead = str[0];
    if (lead >= 0xF0){
        str += ifs.get();
    }
    if (lead >= 0xE0) {
        str += ifs.get();
    }
    if (lead >= 0x80) {
        str += ifs.get();
    }
    
    return str;
    
}

bool ScriptParser::isspace(string str){
    if(str == " " || str == "\n" || str == "\t"){
        return true;
    }else{
        return false;
    }
    
}
bool ScriptParser::isNewline(string str){
    if(str == "\n"){
        return true;
    }else{
        return false;
    }
    
}

string ScriptParser::getNextToken(){
    if(inScript){
        return getNextScriptToken();
    }else{
        return getNextTextToken();
    }
    
}

string ScriptParser::getNextTextToken(){
    string idStr;
    
    if(isNewline(lastLetter)){
        lastLetter = getNextLetter();
    }
    
    idStr = lastLetter;
    while(1){
        lastLetter = getNextLetter();
        if(lastLetter[0] != EOF && lastLetter != "\n" && lastLetter != "\r"){
            if(lastLetter == "["){
                inScript = true;
                break;
            }
            idStr += lastLetter;
        }else{
            break;
        }
    }
    return idStr;
}

string ScriptParser::getNextScriptToken(){
    string idStr;
    //空白文字の無視
    while (isspace(lastLetter)){
        lastLetter = getNextLetter();
    }
    
    //アルファベット単語
    if(isalpha(lastLetter.c_str()[0])){
        idStr = lastLetter;
        while (isalnum((lastLetter = getNextLetter()).c_str()[0]) || lastLetter == "_" ){
            idStr += lastLetter;
        }
        
        if (idStr == "def"){
            return "***def***";
        }
        if (idStr == "else"){
            return "***else***";
        }
        if (idStr == "if"){
            return "***if***";
        }
        
        return idStr;
    }
    
    //ワイド文字単語(文章)
    if(lastLetter.length() != 1){
        idStr = lastLetter;
        while(1){
            lastLetter = getNextLetter();
            if(lastLetter[0] != EOF && lastLetter != "\n" && lastLetter != "\r" && lastLetter != " "){
                idStr += lastLetter;
            }else{
                break;
            }
        }
    
        if (lastLetter[0] != EOF){
            return idStr;
        }
        
        return idStr;
    }
    
    //数値
    if (isdigit(lastLetter[0]) || lastLetter[0] == '.') {   // Number: [0-9.]+
        do {
            idStr += lastLetter;
            lastLetter = getNextLetter();
        } while (isdigit(lastLetter[0]) || lastLetter[0] == '.');
        
        return idStr;
    }
    
    //コメントはひとまとまりに
    if (lastLetter == "#") {
        while (lastLetter[0] != EOF && lastLetter != "\n" && lastLetter != "\r"){
            idStr += lastLetter;
            lastLetter = getNextLetter();
        }
    
        if (lastLetter[0] != EOF){
            return idStr;
        }
    }
    
    //""で囲まれた文字列
    if (lastLetter == "\"") {
        lastLetter = getNextLetter();
        while (lastLetter[0] != EOF && lastLetter != "\n" && lastLetter != "\r" && lastLetter != "\""){
            idStr += lastLetter;
            lastLetter = getNextLetter();
        }
        lastLetter = getNextLetter();
    
        if (lastLetter[0] != EOF){
            return idStr;
        }
    }
    
    if(lastLetter == "]"){
        inScript = false;
    }
    
    //その他(アルファベット、数値以外のもの)
    string thisLetter = lastLetter;
    lastLetter = getNextLetter();
    return thisLetter;
};

NS_NV_END