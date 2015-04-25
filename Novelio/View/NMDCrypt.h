//
//  NMDCrypt.h
//  nmd
//
//  Created by Tatsuya Soma on 2014/12/31.
//
//

#ifndef __nmd__NMDCrypt__
#define __nmd__NMDCrypt__

#include "cocos2d.h"

using namespace std;

class NMDCrypt{
public:
    static cocos2d::Sprite* getSprite(string zipPath, string imgPath, string password);
    static void setSpriteFrameCache(string zipPath, string imgPath, string password, string plistPath);
    static cocos2d::SpriteBatchNode* getSpriteBatchNode(string zipPath, string imgPath, string password);
    static cocos2d::Texture2D* getTexture(string zipPath, string imgPath, string password);

private:
    static cocos2d::Image* getImage(string zipPath, string imgPath, string password);
    
};

#endif /* defined(__nmd__NMDCrypt__) */
