//
//  ViewFunctions.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/10/06.
//
//

#include "ViewFunctions.h"

#include "../Model/GameModel.h"
#include "../GameManager.h"
#include "../Controller/NovelController.h"

NS_NV_BEGIN

void ViewFunctions::load(int n_slot){
    
}
void ViewFunctions::save(int n_slot){
    
}

void ViewFunctions::hideText(){
    //テキストレイヤとUIレイヤを非表示に設定
    GameManager::getInstance()->getUILayer()->setVisible(false);
    GameManager::getInstance()->getTextLayer()->setVisible(false);
}
void ViewFunctions::unsetHideText(){
    //テキストレイヤとUIレイヤを表示
    GameManager::getInstance()->getUILayer()->setVisible(true);
    GameManager::getInstance()->getTextLayer()->setVisible(true);
}
void ViewFunctions::setAutoMode(){
    GameModel::getInstance()->setScenarioMode(GameModel::AUTO);
    NovelController::getInstance()->_execNextLine();
//    GameModel::getInstance()->save();
}
void ViewFunctions::setNormalMode(){
        GameModel::getInstance()->setScenarioMode(GameModel::NORMAL);
        //Autoボタンの表示を元に戻す
        GameManager::getInstance()->getUILayer()->unsetAutoMode();
}
void ViewFunctions::setAutoModeSpeed(double t_sec){
    GameManager::getInstance()->getTextLayer()->setTextWaitTime(t_sec);
}
void ViewFunctions::setSkipMode(){

    if(!(GameManager::getInstance()->getUILayer()->isWaitingClick())){
        if(GameModel::getInstance()->getScenarioMode() != GameModel::NORMAL){
            //Auto,SkipならNormalに
            ViewFunctions::setNormalMode();
        }else{
            //Normalの場合、Skipに
            GameModel::getInstance()->setScenarioMode(GameModel::SKIP);
            NovelController::getInstance()->_execNextLine();
        }
    }
}
void ViewFunctions::setBGMVol(int vol){
    
}
void ViewFunctions::setSEVol(int vol){
    
}
static std::vector<std::string> getLogText(){
    
}

NS_NV_END