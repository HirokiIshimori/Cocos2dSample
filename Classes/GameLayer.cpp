//
//  GameLayer.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//  ゲーム部分のレイヤー.

#include "GameLayer.hpp"

using namespace cocos2d;
using namespace std;

/**
 ゲームの初期化処理.

 @return 初期化成功フラグ.
 */
bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto label = Label::createWithTTF("GameLayer", "fonts/Marker Felt.ttf", 24);
    auto winSize = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(label, 1);
    
    // 更新処理を行うようにする.
    this->scheduleUpdate();

    return true;
}

/**
 ゲームの更新処理.

 @param delta 前のフレームからの経過時間.
 */
void GameLayer::update(float delta) {
    
}

GameLayer::~GameLayer() {

}