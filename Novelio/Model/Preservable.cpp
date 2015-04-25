//
//  Preservable.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/22.
//
//

#include "Preservable.h"

NS_NV_BEGIN

PreservableValueManager* PreservableValueManager::instance = 0;

PreservableValueManager::PreservableValueManager(){
    
}

PreservableValueManager* PreservableValueManager::getInstance() {
    if(instance == 0){
        instance = new PreservableValueManager();
    }
    return instance;
};

bool PreservableValueManager::initWithFilename(string filename){
    
    this->filename = filename;
    auto path = FileUtils::getInstance()->getWritablePath();
    this->valueMap = FileUtils::getInstance()->getValueMapFromFile(path + SAVEDIR + "/"+ this->filename + ".save");
    
    return true;
}

void PreservableValueManager::saveToPList(){
//    for (auto a:valueMap){
//        CCLOG("%s",static_cast<string>(a).c_str);
//    }
    
    /*
    vector<cocos2d::Value> v;
    string hufa = "hogehoge";
    v.push_back(Value("hoge"));
    v.push_back(Value("aaaaaaaaaaa"));
    valueMap["test"] = v;
    */
     
    auto rootPath = FileUtils::getInstance()->getWritablePath();
    
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    FileUtils::getInstance()->writeToFile(this->valueMap, rootPath + SAVEDIR + "/"+ this->filename + ".save");
    
    auto filePath = rootPath + SAVEDIR + "/"+ this->filename + ".save";
    CCLOG("%s", filePath.c_str());
}

bool PreservableValueManager::setData(string key, bool value){
    this->valueMap[key] = value;
    return true;
};
bool PreservableValueManager::setData(string key, string value){
    this->valueMap[key] = value;
    return true;
};
bool PreservableValueManager::setData(string key, int value){
    this->valueMap[key] = value;
    return true;
};
bool PreservableValueManager::setData(string key, double value){
    this->valueMap[key] = value;
    return true;
};

bool PreservableValueManager::getBoolData(string key){
    return this->valueMap[key].asBool();
};
int PreservableValueManager::getIntData(string key){
    return this->valueMap[key].asInt();
};
double PreservableValueManager::getDoubleData(string key){
    return this->valueMap[key].asDouble();
};
string PreservableValueManager::getStringData(string key){
    return this->valueMap[key].asString();
};


//**************************************************************************

Preservable::Preservable(string baseKey){
    this->baseKey = baseKey;
    this->absKey = baseKey;
};
Preservable::~Preservable(){
    
};


void Preservable::addDataNode(Preservable* pChild){
    pChild->absKey = this->absKey + "__" + pChild->baseKey;
    this->childrenData[pChild->baseKey] = pChild;
};
void Preservable::save(){
    PreservableValueManager::getInstance()->saveToPList();
};

void Preservable::load(){
    
};
void Preservable::_load(){
    
};

//**************************************************************************

#define SAVEFILE "savedata"

//ValueMap ModelData::rootValueMap = ValueMap();


ModelData::ModelData(string name)
:values(val)
{
    this->initModelName(name);
    values = ValueMap();
}

//void ModelData::setRoot(bool root){
//    if(root == true){
//        values = &rootValueMap;
//    }
//}

bool ModelData::setData(string key, bool v){
    values[key] = v;
    return true;
};
bool ModelData::setData(string key, string v){
    values[key] = v;
    return true;
};
bool ModelData::setData(string key, int v){
    values[key] = v;
    return true;
};
bool ModelData::setData(string key, double v){
    values[key] = v;
    return true;
};

bool ModelData::getBoolData(string key){
    return values[key].asBool();
};
int ModelData::getIntData(string key){
    return values[key].asInt();
};
double ModelData::getDoubleData(string key){
    return values[key].asDouble();
};
string ModelData::getStringData(string key){
    return values[key].asString();
};


void ModelData::initModelName(string name){
    this->modelName = name;
}

void ModelData::loadFromPlist(){
    auto path = FileUtils::getInstance()->getWritablePath();
    values = FileUtils::getInstance()->getValueMapFromFile(path + SAVEDIR + "/"+ SAVEFILE + ".save");
}

void ModelData::saveToPList(){
    auto rootPath = FileUtils::getInstance()->getWritablePath();

    
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    FileUtils::getInstance()->writeToFile(values, rootPath + SAVEDIR + "/"+ SAVEFILE + ".save");
    
    auto filePath = rootPath + SAVEDIR + "/"+ SAVEFILE + ".save";
    CCLOG("%s", filePath.c_str());
}

void ModelData::addChildModel(nv::ModelData* model){
//    values[model->modelName] = ;
//    model->values = &(*values)[model->modelName].asValueMap();
}

NS_NV_END