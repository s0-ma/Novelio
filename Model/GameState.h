//
//  GameState.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/10/22.
//
//

#ifndef __Novelio__GameState__
#define __Novelio__GameState__

#include "../Macros.h"

class GameState{
public:
    GameState();
    ~GameState();
    
    string BackgroundImagePath;
    string BGMPath;
    string SEPath;
    vector<string> log;
    string name;
    string text;
    vector<string> texts;
    
};

#endif /* defined(__Novelio__GameState__) */
