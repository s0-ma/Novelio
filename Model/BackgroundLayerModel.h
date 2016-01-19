//
//  BackgroundLayerModel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#ifndef __Novelio__BackgroundLayerModel__
#define __Novelio__BackgroundLayerModel__

//#include "Preservable.h"
#include "../Macros.h"

NS_NV_BEGIN


class BackgroundLayerModel{
public:
    BackgroundLayerModel();
    ~BackgroundLayerModel();

//    DEFINE_STRING_DATA(BackgroundImagePath);
//    DEFINE_STRING_DATA(BGMPath);
//    DEFINE_STRING_DATA(SEPath);
    
    string bgImagePath;
    void setBackgroundImagePath(string p){
        this->bgImagePath = p;
    };
    string getBackgroundImagePath(){
        return this->bgImagePath;
    };
    string bgmPath;
    void setBGMPath(string p){
        this->bgmPath = p;
    };
    string getBGMPath(){
        return this->bgmPath;
    }
    string sePath;
    void setSEPath(string p){
        this->sePath = p;
    };
    string getSEPath(){
        return this->sePath;
    };
    
};
NS_NV_END

#endif /* defined(__Novelio__BackgroundLayerModel__) */
