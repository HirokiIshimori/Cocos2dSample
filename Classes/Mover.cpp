//
//  Mover.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#include "Mover.hpp"

using namespace cocos2d;
using namespace std;

bool Mover::init(const Vec2 &moveVec) {
    mMoveVec = moveVec;
    return true;
}
