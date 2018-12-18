//
//  Character.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/05.
//

#include "Character.hpp"
#include "GameLayer.hpp"
#include "Collision.hpp"

using namespace cocos2d;
using namespace std;

bool Character::init(const Vec2 &pos, const Vec2 &moveVec, const ZIndex &zIndex, GameLayer* layer, const string& fileName, Collision* collision, const CollisionGroupType& collisionGroupType) {
    mSprite = Sprite::create(fileName);
    if (mSprite == nullptr || collision == nullptr) {
        return false;
    }
    mSprite->setPosition(pos);
    mSprite->retain();
    layer->addChild(mSprite, zIndex);
    layer->addCollision(collision, collisionGroupType);
    return this->Mover::init(moveVec, collision, collisionGroupType, layer);
}

void Character::orderCollision(float delta) {
    mCollision->setPoint(mSprite->getPosition());
}

/**
 デストラクタ
 mSprite を解放
 @return
 */
Character::~Character() {
    mSprite->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE_NULL(mSprite);
}
