//
//  Collision.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#include "Collision.hpp"
#include "Character.hpp"

using namespace cocos2d;
using namespace std;

Collision* Collision::create(const unsigned int &num, const bool &enable, const Vec2 &point, const float &r, const function<void (float)> &order, const function<void(Mover*)> &hitHandler) {
    Collision *pCollision = new Collision();
    
    if (pCollision && pCollision->init(num, enable, point, r, order, hitHandler)) {
        pCollision->autorelease();
        return pCollision;
    } else {
        delete pCollision;
        pCollision = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool Collision::init(const unsigned int &num, const bool &enable, const Vec2 &point, const float &r, const function<void (float)> &order, const function<void(Mover*)> &hitHandler) {
    mNum = num;
    mEnable = enable;
    mPoint = point;
    mR = r;
    mOrder = order;
    mHitHandler = hitHandler;
    mIsHit = false;
    return true;
}

void Collision::update(const float &delta) {
    mIsHit = false;
    mOrder(delta);
}

unsigned Collision::getNumber() const {
    return mNum;
}

bool Collision::getEnable() const {
    return mEnable;
}

Vec2 Collision::getPoint() const {
    return mPoint;
}

float Collision::getRange() const {
    return mR;
}

void Collision::hit() {
    mIsHit = true;
}

void Collision::setPoint(const cocos2d::Vec2& point) {
    mPoint = point;
}

bool Collision::getIsHit() const {
    return mIsHit;
}

Collision::~Collision() {
    mHitHandler = nullptr;
    mOrder = nullptr;
}
