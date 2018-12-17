//
//  Mover.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#include "Mover.hpp"
#include "Collision.hpp"
#include "MultiLayerScene.hpp"
#include "GameLayer.hpp"

using namespace cocos2d;
using namespace std;

bool Mover::init(const Vec2 &moveVec, Collision* collision, const CollisionGroupType& collisionGroupType) {
    mMoveVec = moveVec;
    mCollision = collision;
    mCollisionGroupType = collisionGroupType;
    return true;
}

Collision* Mover::getCollision() const {
    return mCollision;
}

Mover::~Mover() {
    MultiLayerScene::sharedLayer()->gameLayer()->removeCollision(mCollision->getNumber(), mCollisionGroupType);
    CC_SAFE_RELEASE_NULL(mCollision);
}
