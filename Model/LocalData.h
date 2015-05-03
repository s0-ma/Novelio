//
//  LocalData.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#ifndef __Novelio__LocalData__
#define __Novelio__LocalData__

#include "cocos2d.h"

#include "ControlledData.h"

USING_NS_CC;

class LocalData : public ControlledData{
public:
    LocalData();
    ~LocalData();
    
    static LocalData* create(string filename);
    
    void saveThumbnail();
    Sprite* getThumbnail();
    
};



#endif /* defined(__Novelio__LocalData__) */
