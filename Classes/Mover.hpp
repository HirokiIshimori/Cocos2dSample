//
//  Mover.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#ifndef Mover_hpp
#define Mover_hpp

#include "cocos2d.h"
#include "ZIndex.hpp"

class Mover : public cocos2d::Ref
{
public:
    bool init(const cocos2d::Vec2 &moveVec);
    virtual ~Mover(){}
    virtual bool update(const float &delta) = 0;
protected:
    explicit Mover() {}
    cocos2d::Vec2 mMoveVec;
private:
    Mover(const Mover& rhs);
    Mover& operator=(const Mover& rhs);
};

#endif /* Mover_hpp */
