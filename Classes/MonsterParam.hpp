//
//  MonsterParam.hpp
//  caracalClient
//
//  Created by Yan Wei on 2016/03/16.
//
//

#ifndef MonsterParam_hpp
#define MonsterParam_hpp

#include <stdio.h>

class MonsterParam{
    
private:
    
    int hp;
    int magic;      //magicSkill
    int strength;   //physicsSkill
    int defense;    //defense
    int revolution; //revolution
    int speed;

public:
    int getHp();
    int getMagic();
    int getStrength();
    int getDefense();
    int getRevolution();
    int getSpeed();
    
    void setHp(int _hp);
    void setMagic(int _magic);
    void setStreng(int _strength);
    void setDefense(int _defense);
    void setRevolution(int _revolution);
    void setSpeed(int _speed);
    
    MonsterParam();
    ~MonsterParam();

};
#endif /* MonsterParam_hpp */
