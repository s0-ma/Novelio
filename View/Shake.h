//
//  Shake.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/10/09.
//
//

#ifndef __Novelio__Shake__
#define __Novelio__Shake__

#include "../Macros.h"

class Shake : public ActionInterval
{
    // Code by Francois Guibert
    // Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax
public:
    Shake();
    
    // Create the action with a time and a strength (same in x and y)
    static Shake* actionWithDuration(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static Shake* actionWithDuration(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
protected:
    // Initial position of the shaked node
    float _initial_x, _initial_y;
    // Strength of the action
    float _strength_x, _strength_y;
};

#endif /* defined(__Novelio__Shake__) */
