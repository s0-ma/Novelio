//
//  LocalData.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#ifndef __Novelio__LocalData__
#define __Novelio__LocalData__

#include "../Macros.h"



NS_NV_BEGIN

class LocalData{
public:
    static void saveThumbnail(string filename);
    static Sprite* getThumbnail(string filename);
    
};

NS_NV_END



#endif /* defined(__Novelio__LocalData__) */
