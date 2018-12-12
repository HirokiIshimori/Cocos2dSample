//
//  Player.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#include "Player.hpp"
#include "MultiLayerScene.hpp"
#include "TouchLayer.hpp"
#include "Bullet.hpp"
#include "MathLib.hpp"

using namespace cocos2d;
using namespace std;

Player* Player::create(const Vec2 &pos, Layer* layer) {
    Player *pPlayer = new Player();
    
    if (pPlayer && pPlayer->init(pos, layer)) {
        pPlayer->autorelease();
        return pPlayer;
    } else {
        delete pPlayer;
        pPlayer = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool Player::init(const Vec2 &pos, Layer* layer) {
    mStartMovePoint = Vec2(-1, -1);
    return this->Character::init(pos, Vec2::ZERO, ZPlayer, layer, "myShip.png");
}

bool Player::update(const float &delta) {
    auto touchLayer = MultiLayerScene::sharedLayer()->touchLayer();
    auto startPoint = touchLayer->getStartPoint();
    auto winSize = Director::getInstance()->getWinSize();
    
    if (mAnimFrame % 4 == 0) {
        auto pos = mSprite->getPosition();
        Bullet::shootDirectionalBullet(Vec2(pos.x, pos.y + 10), 10, 90 * MathLib::DEG_TO_RAD, BulletMyChara);
    }
    
    ++mAnimFrame;
    
    if (startPoint.x < 0 && startPoint.y < 0) {
        mStartMovePoint = Vec2(-1, -1);
        return true;
    }
    
    if (mStartMovePoint.x < 0 && mStartMovePoint.y < 0) {
        mStartMovePoint = mSprite->getPosition();
        return true;
    }
    
    auto movePoint = touchLayer->getMovePoint();

    if (movePoint.x < 0 && movePoint.y < 0) {
        return true;
    }

    auto move = movePoint - startPoint;
    auto newPos = mStartMovePoint + move;
    
    mSprite->setPosition(newPos);
    
    return true;
}

Player::~Player() {
    
}
