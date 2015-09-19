//
//  ScriptParser.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

#ifndef __Novelium__ScriptParser__
#define __Novelium__ScriptParser__

#include <string>
#include "../Macros.h"
#include <fstream>
using namespace std;

NS_NV_BEGIN

class ScriptParser{
private:
    ifstream ifs;
    std::string lastLetter = " ";
    bool isspace(string);
    
public:
    ScriptParser();
    std::string Novelio(std::string string);
    void mainLoop(string filename);
    std::string getNextLetter();
    std::string getNextToken();
};




NS_NV_END

#endif /* defined(__Novelium__ScriptParser__) */
