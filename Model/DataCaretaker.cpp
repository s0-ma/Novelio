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

void CareTaker::storeMemento(int key){
    auto mem = GameModel::getInstance()->createMemento();
    SqliteDAO::getInstance()->writeMemento(key, mem);
};

void CareTaker::loadMemento(int key){
    Memento* memento = SqliteDAO::getInstance()->createMemento(key);
    GameModel::getInstance()->setMemento(memento);
};

NS_NV_END