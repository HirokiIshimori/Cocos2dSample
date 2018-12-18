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
#include "CollisionView.hpp"

using namespace cocos2d;
using namespace std;

bool Mover::init(const Vec2 &moveVec, Collision* collision, const CollisionGroupType& collisionGroupType, GameLayer* layer) {
    mMoveVec = moveVec;
    mCollision = collision;
    mCollisionView = CollisionView::create(collision->getNumber(), collision->getPoint(), collision->getRange(), layer);
    mCollisionView->retain();
    layer->addCollisionView(mCollisionView, collisionGroupType);
    mCollisionGroupType = collisionGroupType;
    return true;
}

Collision* Mover::getCollision() const {
    return mCollision;
}

Mover::~Mover() {
    auto gameLayer = MultiLayerScene::sharedLayer()->gameLayer();
    gameLayer->removeCollision(mCollision->getNumber(), mCollisionGroupType);
    gameLayer->removeCollisionView(mCollision->getNumber(), mCollisionGroupType);
    CC_SAFE_RELEASE_NULL(mCollisionView);
    CC_SAFE_RELEASE_NULL(mCollision);
}
