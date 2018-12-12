//
//  MathLib.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/10.
//

#ifndef MathLib_hpp
#define MathLib_hpp

#include "cocos2d.h"

class MathLib
{
private:
    MathLib(){}
public:
    static const float RAD_TO_DEG;
    static const float DEG_TO_RAD;
    
    static cocos2d::Vec2 radianToVec(const float &rad) {
        return cocos2d::Vec2(cosf(rad), sinf(rad));
    }
    
    static cocos2d::Vec2 getPointOnCircumference(const cocos2d::Vec2 &centerPos, const float &r, const float &angle) {
        return cocos2d::Vec2(centerPos.x + r * cosf(angle), centerPos.y + r * sinf(angle));
    }
};

#endif /* MathLib_hpp */
