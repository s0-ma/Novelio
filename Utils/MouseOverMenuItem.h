//  MouseOverMenuItem.h
//  MouseOver
//
//  Created by Baris Atamer on 3/15/15.
//  Modified by reah_at
#ifndef __MouseOver__MouseOverMenuItem__
#define __MouseOver__MouseOverMenuItem__

#include "cocos2d.h"

USING_NS_CC;

class MouseOverMenuItem : public MenuItemImage
{
public:
    
    ~MouseOverMenuItem();
    
    static MouseOverMenuItem * create(const std::string &normalImage, const std::string &pressedImage, const std::string &focusImage);
    void setCursorInCallback(const std::function<void(Ref*)> &callback);
    void setButtonPressedCallback(const std::function<void(Ref*)> &callback);
    void setButtonReleasedCallback(const std::function<void(Ref*)> &callback);
    
protected:
    EventListenerMouse* mouseListener;
    
private:
    void onMouseMove(Event *event);
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
    void setMouseListener();
    bool isMousePressing = false;
    // カーソルがボタンに乗った際のコールバック
    std::function<void(Ref*)> cursor_in_callback = nullptr;
    // カーソルがボタンに乗ったとき、初回のみコールバックを動作させる
    bool isCursorInCallbackEnable = true;
    // ボタンを押したとき（離した時ではない）のコールバック
    std::function<void(Ref*)> button_pressed_callback = nullptr;
    // ボタンを離した時のコールバック
    std::function<void(Ref*)> button_released_callback = nullptr;
};

#endif /* defined(__MouseOver__MouseOverMenuItem__) */
