//
//  BackgroundLayerModel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#ifndef __Novelio__BackgroundLayerModel__
#define __Novelio__BackgroundLayerModel__

#include "Preservable.h"

class BackgroundLayerModel : public nv::Preservable{
public:
    BackgroundLayerModel();
    ~BackgroundLayerModel();

    DEFINE_STRING_DATA(BackgroundImagePath);
    DEFINE_STRING_DATA(BGMPath);
    DEFINE_STRING_DATA(SEPath);
    
};

#endif /* defined(__Novelio__BackgroundLayerModel__) */
