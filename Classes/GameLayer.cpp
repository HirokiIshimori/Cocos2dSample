//
//  GameLayer.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//  ゲーム部分のレイヤー.

#include "GameLayer.hpp"
#include "Player.hpp"
#include "Objects.hpp"
#include "Enemy.hpp"

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
    this->addChild(label, -1);
    
    mCollisionGroup = CollisionGroup::create();
    mCollisionGroup->retain();
    mCollisionGroup->setLayer(this);
    
    mPlayer = Player::create(Vec2(winSize.width * 0.5, winSize.height * 0.25), this);
    mPlayer->retain();
    mCollisionGroup->setPlayer(mPlayer);
    
    mEnemy = Enemy::create(Vec2(winSize.width * 0.5, winSize.height * 0.5), this);
    mEnemy->retain();
    mCollisionGroup->setEnemy(mEnemy);
        
    // 更新処理を行うようにする.
    this->scheduleUpdate();

    return true;
}

/**
 ゲームの更新処理.

 @param delta 前のフレームからの経過時間.
 */
void GameLayer::update(float delta) {
    Objects::update(delta);
    mPlayer->update(delta);
    mEnemy->update(delta);
    mCollisionGroup->update(delta);
}

void GameLayer::addCollision(Collision* collision, const CollisionGroupType &type) {
    mCollisionGroup->addCollision(collision, type);
}

void GameLayer::removeCollision(const unsigned int &num, const CollisionGroupType &type) {
    mCollisionGroup->remove(num, type);
}

void GameLayer::addCollisionView(CollisionView* collisionView, const CollisionGroupType &type) {
    mCollisionGroup->addCollisionView(collisionView, type);
}

void GameLayer::removeCollisionView(const unsigned int &num, const CollisionGroupType &type) {
    mCollisionGroup->removeView(num, type);
}

GameLayer::~GameLayer() {
    CC_SAFE_RELEASE_NULL(mPlayer);
    CC_SAFE_RELEASE_NULL(mEnemy);
    CC_SAFE_RELEASE_NULL(mCollisionGroup);
    Objects::reset();
}
