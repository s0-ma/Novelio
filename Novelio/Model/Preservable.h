//
//  Preservable.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/22.
//
//

#ifndef __Novelio__Preservable__
#define __Novelio__Preservable__

#include "cocos2d.h"
#include "Novelio.h"

NS_NV_BEGIN

class PreservableValueManager{
private:
    //唯一のinstance
    static PreservableValueManager* instance;
    // 生成やコピーを禁止する
    PreservableValueManager();
    PreservableValueManager(const PreservableValueManager& rhs);
    PreservableValueManager& operator=(const PreservableValueManager& rhs);

public:
    //唯一のアクセス手段
    static PreservableValueManager* getInstance();


private:
    string filename;
    cocos2d::ValueMap valueMap;
    bool initWithFilename(string filename);

public:
    bool setData(string, bool);
    bool setData(string, int);
    bool setData(string, double);
    bool setData(string, string);
    
    bool getBoolData(string);
    int getIntData(string);
    double getDoubleData(string);
    string getStringData(string);
    
    void saveToPList();
};

class Preservable{
protected:
    Preservable(string baseKey);
    ~Preservable();
    
public:
    map<string, Preservable*> childrenData;
    string absKey;
    string baseKey;
    
    void addDataNode(Preservable*);
    void save();
    void load();
    void _load();
    
    friend PreservableValueManager;
    
};

#define DEFINE_STRING_DATA(NAME) \
public:\
    void set##NAME(string NAME){\
        nv::PreservableValueManager::getInstance()->setData(absKey + "__" + #NAME, NAME);\
    };\
    string get##NAME(){\
        return nv::PreservableValueManager::getInstance()->getStringData(absKey + "__" + #NAME);\
    };

#define DEFINE_INT_DATA(NAME) \
public:\
    void set##NAME(int NAME){\
        nv::PreservableValueManager::getInstance()->setData(absKey + "__" + #NAME, NAME);\
    };\
    int get##NAME(){\
        return nv::PreservableValueManager::getInstance()->getIntData(absKey + "__" + #NAME);\
    };

#define DEFINE_BOOL_DATA(NAME) \
public:\
    void set##NAME(bool NAME){\
        nv::PreservableValueManager::getInstance()->setData(absKey + "__" + #NAME, NAME);\
    };\
    bool get##NAME(){\
        return nv::PreservableValueManager::getInstance()->getBoolData(absKey + "__" + #NAME);\
    };

#define DEFINE_DOUBLE_DATA(NAME) \
public:\
    void set##NAME(double NAME){\
        nv::PreservableValueManager::getInstance()->setData(absKey + "__" + #NAME, NAME);\
    };\
    double get##NAME(){\
        return nv::PreservableValueManager::getInstance()->getDoubleData(absKey + "__" + #NAME);\
    };

class ModelData{

public:
    ValueMap val;
//    static Val/ueMap rootValueMap;
    ValueMap& values;
    string modelName;
    
//    bool isRoot;
    
    bool setData(string, bool);
    bool setData(string, int);
    bool setData(string, double);
    bool setData(string, string);
    
    bool getBoolData(string);
    int getIntData(string);
    double getDoubleData(string);
    string getStringData(string);

    
    
public:
    ModelData(string name);
//    void setRoot(bool root = true);
    void initModelName(string name);

    void saveToPList();
    void loadFromPlist();
    
    void addChildModel(ModelData* model);
};

NS_NV_END

#endif /* defined(__Novelio__Preservable__) */
