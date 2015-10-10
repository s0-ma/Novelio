//
//  ViewFunctions.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/10/06.
//
//

#include "ViewFunctions.h"

#include "Model/GameModel.h"
#include "Controller/NovelController.h"

NS_NV_BEGIN

void ViewFunctions::load(int n_slot){
    
}
void ViewFunctions::save(int n_slot){
    
}

void ViewFunctions::HideText(){
    
}
void ViewFunctions::setAutoMode(){
    GameModel::getInstance()->setScenarioMode(GameModel::AUTO);
    NovelControler::getInstance()->_execNextLine();
//    GameModel::getInstance()->save();
}
void ViewFunctions::setAutoModeSpeed(int speed){
    
}
void ViewFunctions::setSkipMode(){
    GameModel::getInstance()->setScenarioMode(GameModel::SKIP);
    NovelControler::getInstance()->_execNextLine();
}
void ViewFunctions::setBGMVol(int vol){
    
}
void ViewFunctions::setSEVol(int vol){
    
}
void ViewFunctions::setTextSpeed(int speed){
    
}
static std::vector<std::string> getLogText(){
    
}

NS_NV_END