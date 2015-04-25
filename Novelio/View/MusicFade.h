// This code is originally from http://www.fuguelike.com/music-fader-for-cocos2dx/
// but altered to make it work with Cocos2d-x 3.x

#ifndef __MusicFade__
#define __MusicFade__

#include "cocos2d.h"
//#include "nmd.h"

class MusicFade : public cocos2d::ActionInterval
{
public:
    MusicFade();
    
    static MusicFade* create(float d, float volume, bool pauseOnComplete = false );
    bool initWithDuration(float d, float volume, bool pauseOnComplete );
    
    virtual MusicFade* clone() const override;  // pure virtual
    virtual MusicFade* reverse() const override;  // pure virtual
    virtual void startWithTarget(cocos2d::Node *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
protected:
    float m_targetVal;
    float m_initialVal;
    bool m_bPauseOnComplete;
};

#endif /* defined(__MusicFade__) */
