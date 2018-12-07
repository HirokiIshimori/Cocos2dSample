//
//  TouchLayer.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//

#include "TouchLayer.hpp"

using namespace cocos2d;

bool TouchLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    reset();
    touchON();
    return true;
}

/**
 Touch 登録処理.
 */
void TouchLayer::touchON()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    mTouchEvent = EventListenerTouchOneByOne::create();
    
    mTouchEvent->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
    mTouchEvent->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
    mTouchEvent->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
    mTouchEvent->onTouchCancelled = CC_CALLBACK_2(TouchLayer::onTouchCancelled, this);
    dispatcher->addEventListenerWithSceneGraphPriority(mTouchEvent, this);
}

/**
 Touch 登録削除.
 */
void TouchLayer::touchOff() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(mTouchEvent);
}

/**
 Touch 開始.

 @param touch タップ情報
 @param event イベント
 @return true で onTouchMoved, onTouchEnded へ処理を流す．
 */
bool TouchLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Began");
    if (mTouchId >= 0) {
        return false;
    }
    mStartPoint = touch->getLocation();   // タッチ座標を取得できる.
    mTouchId = touch->getID();
    return true;
}

/**
 Touch 移動.

 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Moved");
    if (mTouchId == touch->getID()) {
        mMovePoint = touch->getLocation();
    }
}

/**
 Touch 終了.
 
 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Ended");
    if (mTouchId == touch->getID()) {
        reset();
    }
}

/**
 Touch キャンセル.
 
 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Canceled");
    if (mTouchId == touch->getID()) {
        reset();
    }
}

Vec2 TouchLayer::getStartPoint() const {
    return mStartPoint;
}

Vec2 TouchLayer::getMovePoint() const {
    return mMovePoint;
}

void TouchLayer::reset() {
    mStartPoint = Vec2(-1, -1);
    mMovePoint = Vec2(-1, -1);
    mTouchId = -1;
}
