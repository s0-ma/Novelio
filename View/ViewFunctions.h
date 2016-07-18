//
//  ViewFunctions.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/10/06.
//
//

#ifndef __Novelio__ViewFunctions__
#define __Novelio__ViewFunctions__

#include <vector>
#include <string>

#include "../Macros.h"

NS_NV_BEGIN

class ViewFunctions{
public:
    static void load(int n_slot);
    static void save(int n_slot);
    
    static void hideText();
    static void unsetHideText();
    static void setAutoMode();
    static void setAutoModeSpeed(double t_sec);
    static void setSkipMode();
    static void setNormalMode();
    static void setBGMVol(int vol);
    static void setSEVol(int vol);
    static std::vector<std::string> getLogText();
    
};
NS_NV_END
#endif /* defined(__Novelio__ViewFunctions__) */
