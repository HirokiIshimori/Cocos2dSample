//
//  Bullet.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/07.
//

#include "Bullet.hpp"
#include "MultiLayerScene.hpp"
#include "GameLayer.hpp"

using namespace cocos2d;
using namespace std;

Bullet* Bullet::create(const Vec2 &pos, const Vec2 &moveVec, const string& fileName, const ZIndex& z) {
    Bullet *pBullet = new Bullet();
    
    if (pBullet && pBullet->init(pos, moveVec, fileName, z)) {
        pBullet->autorelease();
        return pBullet;
    } else {
        delete pBullet;
        pBullet = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool Bullet::init(const Vec2 &pos, const Vec2 &moveVec, const string& fileName, const ZIndex& z) {
    mParticle = ParticleSystemQuad::create(fileName);
    if (mParticle == nullptr) {
        return false;
    }
    mParticle->retain();
    mParticle->resetSystem();
    mParticle->setPositionType(ParticleSystem::PositionType::GROUPED);
    mParticle->setPosition(pos);
    mParticle->setAutoRemoveOnFinish(true);
    MultiLayerScene::sharedLayer()->gameLayer()->addChild(mParticle, z);
    return this->Mover::init(moveVec);
}

bool Bullet::update(const float& delta) {
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

void Bullet::shootDirectionalWeapon(const Vec2 &position, const float &speed, const float &angle) {
    
}

Bullet::~Bullet() {
    CC_SAFE_RELEASE_NULL(mParticle);
}
