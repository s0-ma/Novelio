//
//  LogLayer.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#ifndef __Novelio__LogLayer__
#define __Novelio__LogLayer__

#include "../Macros.h"
#include "../extensions/cocos-ext.h"
NS_NV_BEGIN

class LogLayer : public cocos2d::Layer, create_func<LogLayer>
{
public:
    bool init();
    using create_func::create;
    void setBackground(string path);
    Label* label;
    Label* nameLabel;
    void showLog();

private:
    static int maxLogLine;//画面表示するログ行数の最大値
    cocos2d::extension::ScrollView* scrollView;
    void setContentSize();
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    
    
    string shapeLog(vector<string> log_orig, int start, int end);
    string shapeLogName(vector<string> log_orig, int start, int end);
};

NS_NV_END


#endif /* defined(__Novelio__LogLayer__) */
