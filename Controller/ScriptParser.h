//
//  ScriptParser.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

/*!
 @file      ScriptParser.h
 @ingroup   Controller
 @brief
 @date      2014/10/12
 @author    Tatsuya Soma
 */

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
    std::string lastLetter = "";
    bool inScript = false;
    bool isspace(string);
    bool isNewline(string);
    
public:
    ScriptParser();
    std::string Novelio(std::string string);
    void mainLoop(string filename);
    std::string getNextLetter();
    std::string getNextToken();
    std::string getNextTextToken();
    std::string getNextScriptToken();
};




NS_NV_END

#endif /* defined(__Novelium__ScriptParser__) */
