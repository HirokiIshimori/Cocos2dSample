//
//  Enemy.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"

class GameLayer;

class Enemy : public Character {
public:
    static Enemy* create(const cocos2d::Vec2 &pos, GameLayer* layer);
    bool init(const cocos2d::Vec2 &pos, GameLayer* layer);
    virtual bool update(const float &delta) override;
    virtual ~Enemy();
protected:
    virtual void hitHandler(Mover* mover) override;    
private:
    explicit Enemy(): mAnimFrame(0){}
    Enemy(const Enemy& rhs);
    Enemy& operator=(const Enemy& rhs);
    int mAnimFrame;
};

#endif /* Enemy_hpp */
