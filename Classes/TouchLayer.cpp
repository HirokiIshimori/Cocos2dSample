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
    
    this->touchON();
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
    auto id = touch->getID();               // タッチ ID を取得できる.
    auto touchPos = touch->getLocation();   // タッチ座標を取得できる.
    return true;
}

/**
 Touch 移動.

 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Moved");
    Point touchPos = touch->getLocation();
}

/**
 Touch 終了.
 
 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Ended");
}

/**
 Touch キャンセル.
 
 @param touch タップ情報
 @param event イベント
 */
void TouchLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("touch Canceled");
}
