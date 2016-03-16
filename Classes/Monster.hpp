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

enum magic_type
{
    C0 = 0,
    C1 = 1,
    C2 = 2,
    C3 = 3,
    C4 = 4,
    C5 = 5,
    C6 = 6,
    C7 = 7,
    C8 = 8,
    C9 = 9,
    C10,
    C11,
    C12,
    C13,
    C14,
};

class Monster : public cocos2d::Sprite
{
private:
    typedef Sprite super;
    Magic* currentMagic;
    Monster* enemy;
    
    int hpValue;
    int magicValue;      //magicSkill
    int strengthValue;   //physicsSkill
    int defenseValue;    //defense
    int revolutionValue; //revolution
    std::vector<Stone*>  stones;
    MonsterDelegate* monsterDelegate;
    magic_type getMagicType(std::string magic);
    
public:
    Monster();
    ~Monster();
    static Monster* create(const std::string& name);
    void invokeMagic();
    void attack();
    void defend();
    void addStone(Stone* _stones);
    void setDelegate(MonsterDelegate*  delegate);
    int updateHp(int value);
    Magic* judgeMagic(std::vector<int> magics);

    std::vector<Stone*> getStones();
 
};

#endif /* Monster_hpp */
