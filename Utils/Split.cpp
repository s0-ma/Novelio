//
//  Split.cpp
//  MyGame
//
//  Created by soma on 2014/05/15.
//
//

#include "Split.h"

vector<string> split(const string &str, char delim){
    vector<string> res;
    size_t current = 0, found;
    while((found = str.find_first_of(delim, current)) != string::npos){
        res.push_back(string(str, current, found - current));
        current = found + 1;
    }
    res.push_back(string(str, current, str.size() - current));
    //TODO
    //頭とおしりの"スペース","タブ"も消去しときたいところ。
    return res;
}
