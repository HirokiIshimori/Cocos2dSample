//
//  Character.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/05.
//

#include "Character.hpp"

using namespace cocos2d;
using namespace std;

bool Character::init(const Vec2 &pos, const Vec2 &moveVec, const ZIndex &zIndex, Layer* layer, const string& fileName) {
    mSprite = Sprite::create(fileName);
    if (mSprite == nullptr) {
        return false;
    }
    mSprite->setPosition(pos);
    mSprite->retain();
    layer->addChild(mSprite, zIndex);
    return this->Mover::init(moveVec);
}

/**
 デストラクタ
 mSprite を解放
 @return
 */
Character::~Character() {
    CC_SAFE_RELEASE_NULL(mSprite);
}
