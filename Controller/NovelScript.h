//
//  NovelScript.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/09.
//
//

#ifndef __Novelium__NovelScript__
#define __Novelium__NovelScript__

#include <vector>
#include <map>
#include "cocos2d.h"
#include "../View/View.h"
#include "Novelio.h"

NS_NV_BEGIN

class NovelioScriptLine : public cocos2d::Ref{
public:
    /**
     @enum 行のタイプ
     */
    enum LineType{
        /**
         *  初期化用ダミー
         */
        NONE,
        /**
         *  コメント行
         */
        COMMENT,
        /**
         *  クリックで実行されるLUAコマンド
         */
        LUA_CLICK,
        /**
         *  直前行と同時タイミングで実行
         */
        LUA_SYNC,
        /**
         *  直前が終わったタイミングで自動実行
         */
        LUA_NEXT,
        /**
         *  (空白文字+)改行文字のみ
         */
        BREAK,
        /**
         *  平文
         */
        TEXT,
        /**
         *  ジャンプ用タグ
         */
        TAG,
        /**
         *  ファイル終端. EOFはマクロ登録されていて使えなかった。
         */
        END
    };
    
public:
    static NovelioScriptLine* create(int n, string str);
    static NovelioScriptLine* createEOF(int n);
    void setNextLineType(LineType nextType);
    bool init(int n, string str);
    bool initEOF(int n);
    
private:
    /**
     *  スクリプトファイルの行番号
     */
    int num;
    /**
     *  この行のタイプ
     */
    LineType type;
    /**
     *  次の行のタイプ。
     */
    LineType nextLineType;
    /**
     *  内容
     */
    string val;
    
    std::vector<std::string> lines;
    std::string getLine(int i);
    std::vector<std::string> getSentences();
public:
    int getNum();
    LineType getLineType();
    LineType getNextLineType();
    string getVal();
};


class NovelScript : public cocos2d::Node
{
public:
    enum ScriptType{NOVELIO, UNKNOWN} scriptType;
    
    static NovelScript* create(std::string filename, ScriptType type);
    static NovelScript* createNovelio(std::string filename);
    bool initWithNovelioFile(string filename);
    
    std::string filename;
    
    void setTag(string tag, int nPara);
    
    std::map<std::string, int> tags;

    cocos2d::Vector<NovelioScriptLine*> lines;

};

NS_NV_END

#endif /* defined(__Novelium__NovelScript__) */
