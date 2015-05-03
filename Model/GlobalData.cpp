//
//  GlobalData.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#include "GlobalData.h"

GlobalData::GlobalData(){
    //使用できるキーを制限(最終的には外部ファイルに移したい。)
    boolKeyList = {
    };
    intKeyList = {
        "textMode"
    };
    doubleKeyList = {
        "textSpeed",
        "BGMVolume",
        "SEVolume"
    };
    stringKeyList = {
    };
}
GlobalData::~GlobalData(){
}

GlobalData* GlobalData::create(string filename){
    auto pRet = new (std::nothrow) GlobalData();
    if( pRet && pRet->initWithFilename(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
