//  MouseOverMenuItem.cpp
//  MouseOver
//
//  Created by Baris Atamer on 3/15/15.
//  Modified by reah_at
#include "MouseOverMenuItem.h"

MouseOverMenuItem::~MouseOverMenuItem()
{
    _eventDispatcher->removeEventListener(mouseListener);
}

MouseOverMenuItem* MouseOverMenuItem::create(const std::string &normalImage, const std::string &pressedImage, const std::string &focusImage)
{
    MouseOverMenuItem *ret = new (std::nothrow) MouseOverMenuItem();
    
    if (ret && ret->initWithNormalImage(normalImage, pressedImage, focusImage, nullptr))
    {
        ret->setMouseListener();
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// マウスオーバー時処理
void MouseOverMenuItem::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
    
    Rect r = Rect(0, 0, getContentSize().width, getContentSize().height);
    
    // マウスオーバー時
    if (!isMousePressing){
        if (r.containsPoint(locationInNode)){
            selected();
            // マウスオーバー時のコールバックがセット済み、かつ一度も実行されていない場合
            if (cursor_in_callback && isCursorInCallbackEnable){
                cursor_in_callback(this);
                isCursorInCallbackEnable = false;
            }
        }
        else{
            unselected();
            isCursorInCallbackEnable = true;
        }
    }
}

// ボタン押下時処理（離した時ではない）
void MouseOverMenuItem::onMouseDown(Event* event){
    EventMouse* e = (EventMouse*)event;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
    
    Rect r = Rect(0, 0, getContentSize().width, getContentSize().height);
    
    if (r.containsPoint(locationInNode)){
        setEnabled(false);
        if (button_pressed_callback) button_pressed_callback(this);
        isMousePressing = true;
    }
    
}

// ボタンを離したとき
void MouseOverMenuItem::onMouseUp(Event* event){
    EventMouse* e = (EventMouse*)event;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
    
    Rect r = Rect(0, 0, getContentSize().width, getContentSize().height);
    
    if (r.containsPoint(locationInNode)){
        setEnabled(true);
        isMousePressing = false;
        if (button_released_callback) button_released_callback(this);
    }
}


void MouseOverMenuItem::setCursorInCallback(const std::function<void(Ref*)> &callback){
    cursor_in_callback = callback;
}
void MouseOverMenuItem::setButtonPressedCallback(const std::function<void(Ref*)> &callback){
    button_pressed_callback = callback;
}
void MouseOverMenuItem::setButtonReleasedCallback(const std::function<void(Ref*)> &callback){
    button_released_callback = callback;
}

void MouseOverMenuItem::setMouseListener()
{
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(MouseOverMenuItem::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(MouseOverMenuItem::onMouseDown, this);
    mouseListener->onMouseUp   = CC_CALLBACK_1(MouseOverMenuItem::onMouseUp, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
