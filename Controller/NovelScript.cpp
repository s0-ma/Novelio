//
//  NovelScript.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/09.
//
//
#include <fstream>
#include "NovelScript.h"

NS_NV_BEGIN

NovelioScriptLine* NovelioScriptLine::create(int n, string str){
    NovelioScriptLine* pRet = new NovelioScriptLine();
    if (pRet && pRet->init(n, str))
    {
        pRet->autorelease();
        pRet->retain();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool NovelioScriptLine::init(int n, string str){
    this->num = n;
    
    auto key = str.substr(0,1);
    
    if(key == "#"){
        this->type = COMMENT;
        this->val = str.substr(1);
    }else if(key == "."){
        this->type = LUA_CLICK;
        this->val = str.substr(1);
    }else if(key == "+"){
        this->type = LUA_SYNC;
        this->val = str.substr(1);
    }else if(key == "-"){
        this->type = LUA_NEXT;
        this->val = str.substr(1);
    }else if(key == ""){
        this->type = BREAK;
        this->val = "";
    }else if(key == ":"){
        this->type = TAG;
        this->val = str.substr(1);
    }else{
        this->type = TEXT;
        this->val = str;
    }
    
    return true;
}
void NovelioScriptLine::setNextLineType(nv::NovelioScriptLine::LineType nextType){
    this->nextLineType = nextType;
}
NovelioScriptLine* NovelioScriptLine::createEOF(int n){
    NovelioScriptLine* pRet = new NovelioScriptLine();
    if (pRet && pRet->initEOF(n))
    {
        pRet->autorelease();
        pRet->retain();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
    
}
bool NovelioScriptLine::initEOF(int n){
    this->num = n;
    this->nextLineType = END;
    this->type = END;
    this->val = "";
    
    return true;
}

NovelioScriptLine::LineType NovelioScriptLine::getLineType(){
    return type;
}
NovelioScriptLine::LineType NovelioScriptLine::getNextLineType(){
    return nextLineType;
}
string NovelioScriptLine::getVal(){
    return val;
}


NovelScript* NovelScript::createNovelio(std::string filename){
    
    NovelScript* pNovelScript = new NovelScript();
    if (pNovelScript && pNovelScript->initWithNovelioFile(filename))
    {
        pNovelScript->autorelease();
        pNovelScript->retain();
        return pNovelScript;
    }
    
    CC_SAFE_DELETE(pNovelScript);
    return NULL;
}


bool NovelScript::initWithNovelioFile(string filename){
    this->filename = filename;
    
    string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
    ifstream ifs(filePath.c_str());
    
    std::string str;
    if (ifs.fail()){
        CCLOG("Fail to open script file: %s", filename.c_str());
        return nullptr;
    }
    
    int n = 0;
    
    //複数行処理のため
    string str_stack = "";
    
    //行ごとに格納
    while (getline(ifs, str))
    {
        //複数行つながる場合は連結
        if(str.length() >0 && str.substr(str.length()-1) == "\\"){
            str_stack += str.substr(0,str.length()-1);
            //ダミーの行を追加(コメント)
            lines.pushBack(NovelioScriptLine::create(n, "#__DUMMY__"));
            continue;
        }else{
            
            lines.pushBack(NovelioScriptLine::create(n/*-n_diff*/, str_stack + str));
            
            //タグの登録
            if(lines.at(n)->getLineType() == NovelioScriptLine::TAG){
                this->setTag(lines.at(n)->getVal(), n);
            }
            
            str_stack = "";
        }
        n++;
    }
    lines.pushBack(NovelioScriptLine::createEOF(n));
    
    //次行の実行タイプを各linse[i]に登録
    for(int i = lines.size()-1 -1; i >= 0 ; i--){
        NovelioScriptLine::LineType next = lines.at(i+1)->getLineType();
        lines.at(i)->setNextLineType(next);
    }
    
//    for(int i = 0; i <lines.size() ; i++){
//        CCLOG("%s",lines.at(i)->getVal().c_str());
//    }
    
//    map<string, int>::iterator it;
//    for(it = tags.begin(); it != tags.end(); it++){
//        CCLOG("%s, %d", it->first.c_str(), it->second);
//    }
    
    return true;
}


NovelScript* NovelScript::create(std::string filename, ScriptType type){
    
    if(type == ScriptType::NOVELIO){
        return createNovelio(filename);
    }else{
        CCLOG("unknown script type");
        return nullptr;
    }
    
}

void NovelScript::setTag(string tag, int para){
    this->tags[tag] = para;
}

//void NovelScript::addParagraph(Paragraph *para){
//    this->paragraphs.push_back(para);
//}

NS_NV_END