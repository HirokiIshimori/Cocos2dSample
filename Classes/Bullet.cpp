//
//  Bullet.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/07.
//

#include "Bullet.hpp"
#include "MultiLayerScene.hpp"
#include "GameLayer.hpp"
#include "MathLib.hpp"
#include "Objects.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

using namespace cocos2d;
using namespace std;

class Player;
class Enemy;

ParticleBatchNode* Bullet::mEffectNode = nullptr;
unsigned int Bullet::mIndex = 0;

Bullet* Bullet::create(const Vec2 &pos, const Vec2 &moveVec, const string& fileName, const ZIndex& z, const BulletType &type) {
    Bullet *pBullet = new Bullet();
    
    if (pBullet && pBullet->init(pos, moveVec, fileName, z, type)) {
        pBullet->autorelease();
        return pBullet;
    } else {
        delete pBullet;
        pBullet = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool Bullet::init(const Vec2 &pos, const Vec2 &moveVec, const string& fileName, const ZIndex& z, const BulletType &type) {
    mParticle = ParticleSystemQuad::create(fileName);
    if (mParticle == nullptr) {
        return false;
    }
    
    auto gameLayer = MultiLayerScene::sharedLayer()->gameLayer();
    
    if (Bullet::mEffectNode == nullptr) {
        Bullet::mEffectNode = ParticleBatchNode::create("bullet1.png");
        gameLayer->addChild(mEffectNode, ZWeapon);
    }
    
    mParticle->retain();
    mParticle->resetSystem();
    mParticle->setPositionType(ParticleSystem::PositionType::GROUPED);
    mParticle->setPosition(pos);
    mParticle->setAutoRemoveOnFinish(true);
    Bullet::mEffectNode->addChild(mParticle, z);
    mType = type;
    mIsDie = false;
    
    auto order = [this](float delta){
        this->orderCollision(delta);
    };
    
    auto hitHandler = [this](Mover* mover){
        this->hitHandler(mover);
    };

    auto collision = Collision::create(Bullet::mIndex++, true, pos, 1, order, hitHandler);
    collision->retain();
    
    auto collisionGroupType = mType == BulletPlayer ? CollisionPlayerBullets : CollisionEnemyBullets;
    gameLayer->addCollision(collision, collisionGroupType);
    return this->Mover::init(moveVec, collision, collisionGroupType, gameLayer);
}

bool Bullet::update(const float& delta) {
    if (mIsDie) {
        return false;
    }
    
    auto newPos = mParticle->getPosition() + mMoveVec;
    auto winSize = Director::getInstance()->getWinSize();
    
    if (newPos.x < 0 || newPos.x > winSize.width) {
        return false;
    }
    
    if (newPos.y < 0 || newPos.y > winSize.height) {
        return false;
    }
    
    mParticle->setPosition(newPos);
    return true;
}

void Bullet::shootDirectionalBullet(const Vec2 &position, const float &speed, const float &angle, const BulletType& type) {
    string fileName;
    ZIndex z;
    
    switch (type) {
        case BulletPlayer:
            fileName = "bullet1.plist";
            z = ZWeapon;
            break;
        case BulletEnemy:
            fileName = "bullet2.plist";
            z = ZBullet;
        break;
    }
    auto bullet = Bullet::create(position, MathLib::radianToVec(angle) * speed, fileName, z, type);
    bullet->retain();
    Objects::addBullet(bullet);
}

void Bullet::shootDirectionalNWayBullets(const cocos2d::Vec2 &position, const float &speed, const float &angle, const float &angleRange, const int &count, BulletType type) {
    for (int i = 0; i < count; i++) {
        shootDirectionalBullet(position, speed, angle-angleRange/2+angleRange*i/(count-1), type);
    }
}

void Bullet::clearBatchNode() {
    if (Bullet::mEffectNode != nullptr) {
        Bullet::mEffectNode->removeFromParentAndCleanup(true);
        Bullet::mEffectNode = nullptr;
    }
}

void Bullet::orderCollision(float delta) {
    mCollision->setPoint(mParticle->getPosition());
}

void Bullet::hitHandler(Mover* mover) {
    if ( (dynamic_cast<Player*>(mover) != nullptr && mType == BulletEnemy) || (dynamic_cast<Enemy*>(mover) != nullptr && mType == BulletPlayer) ) {
        mIsDie = true;
    }
}

BulletType Bullet::getType() const {
    return mType;
}

Bullet::~Bullet() {
    mParticle->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(mParticle);
}
