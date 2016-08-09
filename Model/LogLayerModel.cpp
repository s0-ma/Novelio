//
//  LogLayerModel.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#include "LogLayerModel.h"

LogLayerModel::LogLayerModel(){
    
}

vector<string> LogLayerModel::getLog(){
    CCLOG("ret");
    return log;
}

void LogLayerModel::appendLog(std::string text){
    this->log.push_back(text);
};

void LogLayerModel::clearLog(void){
    this->log.clear();
};

void LogLayerModel::setLog(vector<string> logs){
    this->log = logs;
};

