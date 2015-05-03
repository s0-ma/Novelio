//
//  GlobalData.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#ifndef __Novelio__GlobalData__
#define __Novelio__GlobalData__

#include "ControlledData.h"

class GlobalData : public ControlledData{
public:
    GlobalData();
    ~GlobalData();
    
    static GlobalData* create(string filename);

};

#endif /* defined(__Novelio__GlobalData__) */
