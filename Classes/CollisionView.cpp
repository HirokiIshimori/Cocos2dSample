//
//  CollisionView.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/18.
//

#include "CollisionView.hpp"
#include "ZIndex.hpp"

using namespace cocos2d;
using namespace std;

CollisionView* CollisionView::create(const int &num, const Vec2 &point, const float &r, cocos2d::Layer* layer) {
    CollisionView *pCollisionView = new CollisionView();
    
    if (pCollisionView && pCollisionView->init(num, point, r, layer)) {
        pCollisionView->autorelease();
        return pCollisionView;
    } else {
        delete pCollisionView;
        pCollisionView = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool CollisionView::init(const int &num, const Vec2 &point, const float &r, cocos2d::Layer* layer) {
    mNum = num;
    mPoint = point;
    mIsHit = false;
    mEnable = true;
    mRange = r;
    mDrawNode = DrawNode::create();
    mDrawNode->retain();
    layer->addChild(mDrawNode, ZCollision, ZCollision);
    return true;
}

void CollisionView::order(const Vec2 &point, const bool &isHit, const bool &enable) {
    mPoint = point;
    mIsHit = isHit;
    mEnable = enable;
}

void CollisionView::draw() {
    mDrawNode->clear();
    
    if (!mEnable) {
        return;
    }
    mDrawNode->drawCircle(mPoint, mRange, 0, 8, false, 1, 1, mIsHit ? Color4F::RED : Color4F::GREEN);
}

CollisionView::~CollisionView() {
    mDrawNode->clear();
    CC_SAFE_RELEASE_NULL(mDrawNode);
}
