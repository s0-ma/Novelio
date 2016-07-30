//
//  DataCaretaker.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//
#include <locale>
#include <codecvt>
#include <string>

#include "DataCaretaker.h"
#include "GameManager.h"
#include "GameModel.h"
#include "DataAccessObject.h"

NS_NV_BEGIN
CareTaker* CareTaker::instance = 0;

CareTaker* CareTaker::getInstance() {
    if(instance == 0){
        instance = new CareTaker();
    }
    return instance;
};

CareTaker::CareTaker(){
    //ディレクトリがなければ作る
    auto rootPath = FileUtils::getInstance()->getWritablePath();
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    
}
CareTaker::~CareTaker(){
    
}

vector<SqliteDAO::LoadInformation> CareTaker::getLoadInformation(){
    auto dao = SqliteDAO::getInstance()->getLoadInformation();
    return dao;
}

map<string, int> CareTaker::getGlobalData(){
    auto g = SqliteDAO::getInstance()->getGlobalData();
    return g;
}

void CareTaker::saveGlobalData(){
    auto dao = SqliteDAO::getInstance();
    auto m = GameModel::getInstance();
    dao->writeGlobalData(m->getBgmVolume(), m->getSeVolume(), m->getTextSpeed(), m->getRecentSaveNo());
};

void CareTaker::loadGlobalData(){
    auto d = SqliteDAO::getInstance()->getGlobalData();
    auto m = GameModel::getInstance();
    m->setBgmVolume(d["bgm_vol"]);
    m->setSeVolume(d["se_vol"]);
    m->setTextSpeed(d["text_speed"]);
    m->setRecentSaveNo(d["recent_save"]);
};

void CareTaker::storeMemento(int key){
    auto model = GameModel::getInstance();
    auto dao = SqliteDAO::getInstance();
    dao->writeMemento(key, model->createMemento());
    
    string p = "save"+to_string(key);
    model->saveThumbnail(p);
    string text = GameManager::getInstance()->getTextLayer()->getGameTextLabelText();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring wtext = converter.from_bytes(text);
    wstring wComment = L"";
    
    int maxCommentLength = 30;
    if(wtext.size() > maxCommentLength){
        wComment = wtext.substr(0, maxCommentLength);
    }else{
        wComment = wtext;
    }
    string comment = converter.to_bytes(wComment);
    dao->writeLoadIndex(key, p , comment);
};

bool CareTaker::loadMemento(int key){
    Memento* memento = SqliteDAO::getInstance()->createMemento(key);
    if(memento->getFilename() != ""){
        GameModel::getInstance()->setMemento(memento);
        return true;
    }else{
        return false;
    }
};

void CareTaker::saveAlbumImage(string filepath){
    auto dao = SqliteDAO::getInstance();
    dao->writeAlbumImage(filepath);
}

vector<string> CareTaker::getAlbumImages(){
    auto dao = SqliteDAO::getInstance();
    return dao->getAlbumImages();
}
NS_NV_END