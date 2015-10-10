//
//  PortraitLayerModel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#ifndef __Novelio__PortraitLayerModel__
#define __Novelio__PortraitLayerModel__

#include "../Macros.h"

struct PortraitModel{
    string id;
    string basePath;
    string faceId;
    string facePath;
    string screenName;
    map<string, string> facePool;
    int x;
    int y;
    int emo_x;
    int emo_y;
    string emoticon_path;
    double scale;
    bool grayout;
};

class PortraitLayerModel {
private:

public:
    std::map<std::string, PortraitModel> portraits;
    
    void addPortrait(string id, string path);
    void addPortraitFace(string id, string faceId, string path);
    void removePortrait(string id);
    void setBasePath(string id, string path);
    void setFacePath(string id, string path);
    void setScreenName(string id, string name);
    void setX(string id, int x);
    void setY(string id, int y);
    void setScale(string id, double scale);
    void setGrayout(string id, bool isGray);
};

#endif /* defined(__Novelio__PortraitLayerModel__) */
