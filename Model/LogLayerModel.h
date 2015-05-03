//
//  LogLayerModel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#ifndef __Novelio__LogLayerModel__
#define __Novelio__LogLayerModel__

#include "Novelio.h"

class LogLayerModel {
public:
    LogLayerModel();
    
    vector<string> getLog();
    void appendLog(std::string text);
    void clearLog(void);

private:
    vector<string> log;
    
};

#endif /* defined(__Novelio__LogLayerModel__) */
