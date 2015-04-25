//
//  Data.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/11.
//
//

#include "Data.h"

NvData::NvData(){
}
NvData::~NvData(){
}

NvData* NvData::create(string filename){
    
    NvData * data = new (std::nothrow) NvData();
    if( data && data->initWithFilename(filename))
    {
        data->autorelease();
        return data;
    }
    CC_SAFE_DELETE(data);
    return nullptr;

}
bool NvData::initWithFilename(string filename){
    
    this->filename = filename;
    auto path = FileUtils::getInstance()->getWritablePath();
    this->valueMap = FileUtils::getInstance()->getValueMapFromFile(path + SAVEDIR + "/"+ this->filename + ".save");

    return true;
}

void NvData::saveToPList(){
    auto rootPath = FileUtils::getInstance()->getWritablePath();
    
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    FileUtils::getInstance()->writeToFile(this->valueMap, rootPath + SAVEDIR + "/"+ this->filename + ".save");
    
    auto filePath = rootPath + SAVEDIR + "/"+ this->filename + ".save";
    CCLOG("%s", filePath.c_str());
}

bool NvData::setData(string key, bool value){
    this->valueMap[key] = value;
    return true;
};
bool NvData::setData(string key, string value){
    this->valueMap[key] = value;
    return true;
};
bool NvData::setData(string key, int value){
    this->valueMap[key] = value;
    return true;
};
bool NvData::setData(string key, const char* value){
    setData(key, string(value));
    return true;
};
bool NvData::setData(string key, double value){
    this->valueMap[key] = value;
    return true;
};

bool NvData::getBoolData(string key){
    return this->valueMap[key].asBool();
};
int NvData::getIntData(string key){
    return this->valueMap[key].asInt();
};
double NvData::getDoubleData(string key){
    return this->valueMap[key].asDouble();
};
string NvData::getStringData(string key){
    return this->valueMap[key].asString();
};

