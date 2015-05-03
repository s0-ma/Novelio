//
//  NovelControler.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/06.
//
//

#ifndef __Novelium__NovelControler__
#define __Novelium__NovelControler__

#include "NovelScript.h"
#include "CommandExecutor.h"

NS_NV_BEGIN

class NovelControler
{
private:
    //唯一のinstance
    static NovelControler* instance;
    // 生成やコピーを禁止する
    NovelControler();
    NovelControler(const NovelControler& rhs);
    NovelControler& operator=(const NovelControler& rhs);
    
    NovelScript* script;
    void onParagraphEnds();
    
public:
    ~NovelControler();
    //唯一のアクセス手段
    static NovelControler* getInstance();
    
    /**
     *  基本的に一行一行読み込んで実行しているが、テキスト表示の場合だけ例外的に連続した行を読み込んでから実行している。
     *
     *  @return 意味なし
     */
    bool onDisplayTouched(void);
    
    NovelScript* getScript();
    
    void loadScript(NovelScript* script);
    void immediateExecute(NovelScript*);
    void _execNextLine();
    
protected:
    bool _stopRunningCommand();
    string _preProcessText(string);
    
};

NS_NV_END
#endif /* defined(__Novelium__NovelControler__) */
