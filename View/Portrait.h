//
//  Portrait.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/20.
//
//

#ifndef __Novelio__Portrait__
#define __Novelio__Portrait__

#include "cocos2d.h"
#include "../Macros.h"

NS_NV_BEGIN

/**
 *  Portrait用の表情フェードインアクション
 */
class PortraitFaceFade : public ActionInterval{
    public:
        //    PortraitFaceFade();

        /* --------------------------------------------------------------------------*/
        /**
         * @brief create function.
         *
         * @param d time in sec
         * @param path path for face.
         * @param x x position
         * @param y y position
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        static PortraitFaceFade* create(float d, string path="", int x=0, int y=0);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @param d
         * @param path
         * @param x
         * @param y
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        bool initWithDuration(float d, string path, int x, int y);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        virtual PortraitFaceFade* clone() const override;  // pure virtual

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        virtual PortraitFaceFade* reverse() const override;  // pure virtual

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @param pTarget
         */
        /* ----------------------------------------------------------------------------*/
        virtual void startWithTarget(cocos2d::Node *pTarget);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         *
         * @param time
         */
        /* ----------------------------------------------------------------------------*/
        virtual void update(float time);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 
         */
        /* ----------------------------------------------------------------------------*/
        virtual void stop(void);

    protected:
        Sprite* _newFace;
        string _newFacePath;
        int _x, _y;
};

/**
 *  Portrait用の目パチアニメーション
 */
class PortraitBlink : public RepeatForever{
    //    FiniteTimeAction* makeBlinkAnimation(std::string face);
    public:
        PortraitBlink();

        static PortraitBlink* create(string path, float d);
        bool initWithDuration(string path, float d);

        virtual PortraitBlink* clone() const override;  // pure virtual
        virtual PortraitBlink* reverse() const override;  // pure virtual
        virtual void startWithTarget(cocos2d::Node *pTarget);
        virtual void update(float time);
        virtual void stop(void);

};

/**
 *  Portrait用のエモティコンアニメーション
 */
class PortraitEmotion : public ActionInterval{
    public:
        PortraitEmotion();

        static PortraitEmotion* create(string path, float d);
        bool initWithDuration(string path, float d);

        virtual PortraitEmotion* clone() const override;  // pure virtual
        virtual PortraitEmotion* reverse() const override;  // pure virtual
        virtual void startWithTarget(cocos2d::Node *pTarget);
        virtual void update(float time);
        virtual void stop(void);
};

class PortraitEmotionForever : public RepeatForever{
    public:
        PortraitEmotionForever();

        static PortraitEmotionForever* create(string path, float d);
        bool initWithDuration(string path, float d);

        virtual PortraitEmotionForever* clone() const override;  // pure virtual
        virtual PortraitEmotionForever* reverse() const override;  // pure virtual
        virtual void startWithTarget(cocos2d::Node *pTarget);
        virtual void update(float time);
        virtual void stop(void);
};

class Portrait : public Sprite
{
    public:
        Portrait();
        ~Portrait();

        static Portrait* create(std::string basePath, string facePath = "", int x = 0, int y = 0);

        bool init(string basePath, string pacePath, int x, int y);

        std::string basePath;
        std::string facePath;
        int faceX, faceY;

    public:
        /**
         *  表情を変える。フェードなどのアニメーションの場合はrunActionで。
         *
         *  @param facePath <#facePath description#>
         */
        void changeFace(std::string facePath);

        /**
         *  エモティコンを追加する。アニメーションの場合はrunActionで。
         *
         *  @param path <#path description#>
         *  @param x    <#x description#>
         *  @param y    <#y description#>
         */
        void addEmoticon(string path, int x, int y);

        /**
         *  表示中のエモティコン(runActionでも)を全て消す。
         */
        void removeEmoticon();
};

NS_NV_END

#endif /* defined(__Novelio__Portrait__) */

