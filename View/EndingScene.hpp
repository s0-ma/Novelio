//
//  EndingScene.hpp
//  Novelio
//
//  Created by yokonami
//
//

#ifndef EndingScene_hpp
#define EndingScene_hpp

#include "Novelio.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_NV;

class EndingScene : public Scene{
    
public:
    static EndingScene* create(string filename);
    Sprite* gif;
    
private:
    bool init(string filename);
    void onEnterTransitionDidFinish();
};



#endif /* EndingScene_hpp */
