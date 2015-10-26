//
//  NovelController.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/06.
//
//

/*!
 @file      NovelController.h
 @ingroup   Controller
 @brief
 @date      2014/10/06
 @author    Tatsuya Soma
 */

#ifndef __Novelium__NovelControler__
#define __Novelium__NovelControler__

#include "NovelScript.h"
#include "CommandExecutor.h"

NS_NV_BEGIN

/*! @brief スクリプトファイルの実行を司る
*/
class NovelController
{
private:
    //唯一のinstance
    static NovelController* instance;
    // 生成やコピーを禁止する
    NovelController();
    NovelController(const NovelController& rhs);
    NovelController& operator=(const NovelController& rhs);
    
    NovelScript* script;
    void onParagraphEnds();
    
public:
    ~NovelController();
    //唯一のアクセス手段
    static NovelController* getInstance();
    
    /**
     *  基本的に一行一行読み込んで実行しているが、テキスト表示の場合だけ例外的に連続した行を読み込んでから実行している。
     */
    bool onDisplayTouched(void);
    
    NovelScript* getScript();
    
    void loadScript(NovelScript* script);
    void immediateExecute(NovelScript*);
    void _execNextLine();
    
    void setNameToModel(string name);
    
protected:
    bool _stopRunningCommand();
    string _preProcessText(string);
    
};

NS_NV_END
#endif /* defined(__Novelium__NovelControler__) */
