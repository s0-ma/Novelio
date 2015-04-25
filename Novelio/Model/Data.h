//
//  Data.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/11.
//
//

#ifndef __Novelio__Data__
#define __Novelio__Data__

#include "Novelio.h"

class NvData : public Ref {
public:
    NvData();
    ~NvData();
    
    static NvData* create(string filename);
    bool initWithFilename(string filename);

private:
    ValueMap valueMap;

protected:
    string filename;

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

    void saveToPList();
};

#endif /* defined(__Novelio__Data__) */
