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

class Monster :public cocos2d::Sprite,StoneDelegate{
private:
    typedef Sprite super;

    Magic* currentMagic;
    Monster* enemy;
    
    int hpValue;
    int magicValue;      //magicSkill
    int strengthValue;   //physiceSkill
    int defenseValue;    //defense
    int revolutionValue; //revolution
    MonsterDelegate* monsterDelegate;
    magic_type getMagicType(std::string magic);
    
public:
    //virtual void init(const char *pName) =0;
    static Monster* create(const std::string& name);
    void invokeMagic();
    void revolve();
    void attack();
    void defend();
    void addStone(Stone* _stones);
    void setDelegate(MonsterDelegate*  delegate);
    int updateHp(int value);
    void setStone(Vector<Stone*> _stones);
    Magic* judgeMagic(std::vector<int> magics);
//    Vector<Stone*> stones;
//    Vector<Magic*> magics;
    
    std::shared_ptr<Vector<Stone*>>  stones;/// = std::make_shared<Vector<Sprite*>>();  //default constructor
    //std::shared_ptr<Vector<Magic*>>  magics;
    
    Monster();
    ~Monster();
    
};
#endif /* Monster_hpp */
