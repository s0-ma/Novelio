//
//  ControlledData.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/18.
//
//

#ifndef __Novelio__ControlledData__
#define __Novelio__ControlledData__

#include "Novelio.h"
#include "Data.h"

class ControlledData : public NvData {
public:
    ControlledData();
    ~ControlledData();
    
    static ControlledData* create(string filename);
    bool initWithFilename(string);
    
protected:
    //使用可能なキーを制限
    vector<string> boolKeyList;
    vector<string> intKeyList;
    vector<string> doubleKeyList;
    vector<string> stringKeyList;
    
private:
    static bool isContain(const vector<string>, string);
    
public:
    bool setData(string, bool);
    bool setData(string, int);
    bool setData(string, double);
    bool setData(string, const char*);
    bool setData(string, string);
    
    bool getBoolData(string);
    int getIntData(string);
    double getDoubleData(string);
    string getStringData(string);
};

#endif /* defined(__Novelio__ControlledData__) */
