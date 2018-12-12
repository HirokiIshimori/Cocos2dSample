//
//  Enemy.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#include "Enemy.hpp"
#include "MultiLayerScene.hpp"
#include "Bullet.hpp"
#include "MathLib.hpp"

using namespace cocos2d;
using namespace std;

Enemy* Enemy::create(const Vec2 &pos, Layer* layer) {
    Enemy *pEnemy = new Enemy();
    
    if (pEnemy && pEnemy->init(pos, layer)) {
        pEnemy->autorelease();
        return pEnemy;
    } else {
        delete pEnemy;
        pEnemy = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool Enemy::init(const Vec2 &pos, Layer* layer) {
    return this->Character::init(pos, Vec2::ZERO, ZEnemy, layer, "enemy.png");
}

bool Enemy::update(const float &delta) {
    auto winSize = Director::getInstance()->getWinSize();
    
    auto newPos = MathLib::getPointOnCircumference(Vec2(winSize.width * 0.5, winSize.height * 0.7), 60, mAnimFrame * 3 * MathLib::DEG_TO_RAD);
    
    if (newPos.x < 0 || newPos.x > winSize.width) {
        return false;
    }
    
    if (newPos.y < 0 || newPos.y > winSize.height) {
        return false;
    }
    
    mSprite->setPosition(newPos);

    if (mAnimFrame % 20 == 0) {
        auto pos = mSprite->getPosition();
        Bullet::shootDirectionalNWayBullets(Vec2(pos.x, pos.y - 10), 4, -90 * MathLib::DEG_TO_RAD, 10 * MathLib::DEG_TO_RAD, 3, BulletEnemy);
    }
    
    ++mAnimFrame;
    
    return true;
}

Enemy::~Enemy() {
    
}
