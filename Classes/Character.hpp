//
//  Character.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/05.
//

#ifndef Character_hpp
#define Character_hpp

#include "Mover.hpp"

class Character : public Mover {
public:
    bool init(const cocos2d::Vec2 &pos, const cocos2d::Vec2 &moveVec, const ZIndex &zIndex, cocos2d::Layer* layer, const std::string& fileName);
    virtual ~Character();
protected:
    explicit Character(){}
    cocos2d::Sprite* mSprite;
private:
    Character(const Character& rhs);
    Character& operator=(const Character& rhs);
};

#endif /* Character_hpp */
