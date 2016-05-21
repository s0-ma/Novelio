//
//  DataCaretaker.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/01/13.
//
//

#include "DataCaretaker.h"

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
}
CareTaker::~CareTaker(){
    
}

vector<SqliteDAO::LoadInformation> CareTaker::getLoadInformation(){
    auto dao = SqliteDAO::getInstance()->getLoadInformation();
    return dao;
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
    dao->writeLoadIndex(key, p , "test.");
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

NS_NV_END