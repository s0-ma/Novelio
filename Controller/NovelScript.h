//
//  NovelScript.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/09.
//
//

/*!
  @file      NovelScript.h
  @ingroup   Controller
  @brief
  @date      2014/10/09
  @author    Tatsuya Soma
  */

#ifndef __Novelium__NovelScript__
#define __Novelium__NovelScript__

#include <vector>
#include <map>
#include "cocos2d.h"
#include "../Macros.h"

NS_NV_BEGIN

//! スクリプト一行に相当
class NovelioScriptLine : public cocos2d::Ref{

    public:
        enum LineType{
            NONE,       //!< 初期化用ダミー
            COMMENT,    //!< コメント行
            LUA_CLICK,  //!< クリックで実行されるLUAコマンド
            LUA_SYNC,   //!<  直前行と同時タイミングで実行
            LUA_NEXT,   //!<  直前が終わったタイミングで自動実行
            BREAK,      //!< (空白文字+)改行文字のみ
            TEXT,       //!< 平文
            TAG,        //!< ジャンプ用タグ
            END         //!< ファイル終端. EOFはマクロ登録されていて使えなかった。
        };

    public:
        static NovelioScriptLine* create(int n, string str);
        static NovelioScriptLine* createEOF(int n);
        void setNextLineType(LineType nextType);
        bool init(int n, string str);
        bool initEOF(int n);

    private:
        int num;                //!< スクリプトファイルの行番号
        LineType type;          //!< この行のタイプ
        LineType nextLineType;  //!< 次の行のタイプ
        string val;             //!< 内容

    public:
        /* --------------------------------------------------------------------------*/
        /**
         * @brief ファイル中の行番号(0オリジン)を返す
         */
        /* ----------------------------------------------------------------------------*/
        int getNum();
        /* --------------------------------------------------------------------------*/
        /**
         * @brief ラインタイプを返す
         */
        /* ----------------------------------------------------------------------------*/
        LineType getLineType();
        /* --------------------------------------------------------------------------*/
        /**
         * @brief 次の行のラインタイプを返す
         */
        /* ----------------------------------------------------------------------------*/
        LineType getNextLineType();
        /* --------------------------------------------------------------------------*/
        /**
         * @brief 行の文字列(コマンドの場合は識別用の行頭文字を覗く)を返す。
         */
        /* ----------------------------------------------------------------------------*/
        string getVal();
};

//! スクリプトファイル１つに相当
class NovelScript : public cocos2d::Node
{
    public:
        /* --------------------------------------------------------------------------*/
        /**
         * @brief スクリプトタイプ。現在はNovelioの記法のみに対応。
         */
        /* ----------------------------------------------------------------------------*/
        enum ScriptType{NOVELIO, UNKNOWN} scriptType;

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @param filename 読み込むファイル名
         * @param type スクリプトタイプ(Novelioにのみ現在は対応)
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        static NovelScript* create(std::string filename, ScriptType type);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief Novelioタイプでcreateするだけ
         *
         * @param filename
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        static NovelScript* createNovelio(std::string filename);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief Novelioファイルの読み込み処理
         *
         * @param filename
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        bool initWithNovelioFile(string filename);

        std::string filename;
        cocos2d::Vector<NovelioScriptLine*> lines;
        std::map<std::string, int> tags;

        void setTag(string tag, int nPara);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 引数として指定したタグから、次のタグまでに存在するコメント分を返す。
         *
         * @param tag
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        vector<string> getCommentsByTag(string tag);

};

NS_NV_END

#endif /* defined(__Novelium__NovelScript__) */
