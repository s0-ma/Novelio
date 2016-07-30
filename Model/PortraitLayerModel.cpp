//
//  PortraitLayerModel.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#include "PortraitLayerModel.h"

void PortraitLayerModel::reset(){
    map<string, PortraitModel>::iterator it = portraits.begin();
    while(it != portraits.end()){
        portraits.erase(it++);
    }
    
}

void PortraitLayerModel::addPortrait(string id, string path){
    portraits[id] = PortraitModel();
    portraits[id].basePath = path;
};
void PortraitLayerModel::addPortraitFace(string id, string faceId, string path){
    portraits[id].facePool[faceId] = path;
};

void PortraitLayerModel::removePortrait(string id){
    portraits.erase(id);
};
void PortraitLayerModel::setBasePath(string id, string path){
    portraits[id].basePath = path;
};
void PortraitLayerModel::setFacePath(string id, string path){
    portraits[id].facePath = path;
};
void PortraitLayerModel::setScreenName(string id, string name){
    portraits[id].screenName = name;
};
void PortraitLayerModel::setX(string id, int x){
    portraits[id].x = x;
};
void PortraitLayerModel::setY(string id, int y){
    portraits[id].y = y;
};
void PortraitLayerModel::setScale(string id, double scale){
    portraits[id].scale = scale;
};
void PortraitLayerModel::setGrayout(string id, bool isGray){
    portraits[id].grayout = isGray;
};

