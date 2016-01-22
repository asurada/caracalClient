//
//  Monster.hpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>

#include "Stone.hpp"
#include "Magic.hpp"
#include "MonsterDelegate.hpp"

USING_NS_CC;

class Monster :public cocos2d::Sprite,StoneDelegate{
private:
    typedef Sprite super;
    Vector<Stone *> stones;
    Vector<Magic *>  magics;
    Magic* currentMagic;
    Monster* enemy;
    
    int hpValue;
    int magicValue;      //magicSkill
    int strengthValue;   //physiceSkill
    int defenseValue;    //defense
    int revolutionValue; //revolution
    MonsterDelegate* monsterDelegate;
    
public:
    //virtual void init(const char *pName) =0;
    static Monster* create(const std::string& name);
    void invokeMagic();
    void revolve();
    void attack();
    void defend();
    void setDelegate(MonsterDelegate*  delegate);
    int updateHp(int value);
    
    Magic* judgeMagic(Vector<String*> magics);
    
};
#endif /* Monster_hpp */
