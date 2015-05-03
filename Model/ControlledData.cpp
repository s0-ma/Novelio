//
//  ControlledData.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/18.
//
//

#include "ControlledData.h"

ControlledData::ControlledData(){
    
    //使用できるキーを制限(最終的には外部ファイルに移したい。)
    boolKeyList = {
    };
    intKeyList = {
    };
    doubleKeyList = {
    };
    stringKeyList = {
    };
}
ControlledData::~ControlledData(){
}



ControlledData* ControlledData::create(string filename){
    auto pRet = new (std::nothrow) ControlledData();
    if( pRet && pRet->initWithFilename(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool ControlledData::initWithFilename(string filename){
    if(!NvData::initWithFilename(filename)){
        return false;
    }
    
    return true;
}

bool ControlledData::setData(string key, bool val){
    if(!isContain(boolKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return false;
    }
    NvData::setData(key, val);
    return true;
}
bool ControlledData::setData(string key, int val){
    if(!isContain(intKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return false;
    }
    NvData::setData(key, val);
    return true;
}
bool ControlledData::setData(string key, double val){
    if(!isContain(doubleKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return false;
    }
    NvData::setData(key, val);
    return true;
}
bool ControlledData::setData(string key, const char* val){
    return setData(key, string(val));
}

bool ControlledData::setData(string key, string val){
    if(!isContain(stringKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return false;
    }
    NvData::setData(key, val);
    return true;
}

bool ControlledData::isContain(const vector<string> l, string key){
    auto iter = find(l.begin(), l.end(), key);
    if( iter != l.end() ){
        return true;
    }
    return false;
}

bool ControlledData::getBoolData(string key){
    if(!isContain(boolKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return nullptr;
    }
    return NvData::getBoolData(key);
};
int ControlledData::getIntData(string key){
    if(!isContain(intKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return NULL;
    }
    return NvData::getIntData(key);
};
double ControlledData::getDoubleData(string key){
    if(!isContain(doubleKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return NULL;
    }
    return NvData::getBoolData(key);
};
string ControlledData::getStringData(string key){
    if(!isContain(stringKeyList,key)){
        CCLOG("key %s not exist.", key.c_str());
        return nullptr;
    }
    return NvData::getStringData(key);
};

