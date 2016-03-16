//
//  MonsterParam.cpp
//  caracalClient
//
//  Created by Yan Wei on 2016/03/16.
//
//

#include "MonsterParam.hpp"


int MonsterParam::getHp(){
    return hp;
}
int MonsterParam::getMagic(){
    return magic;
}
int MonsterParam::getStrength(){
    return strength;
}
int MonsterParam::getDefense(){
    return defense;
}
int MonsterParam::getRevolution(){
    return revolution;
}
int MonsterParam::getSpeed(){
    return speed;
}

void MonsterParam::setHp(int _hp){
    hp =_hp;
}
void MonsterParam::setMagic(int _magic){
    magic = _magic;
}
void MonsterParam::setStreng(int _strength){
    strength = _strength;
}
void MonsterParam::setDefense(int _defense){
    defense = _defense;
}
void MonsterParam::setRevolution(int _revolution){
    revolution = _revolution;
}
void MonsterParam::setSpeed(int _speed){
    speed = _speed;
}

MonsterParam::MonsterParam(){
    
}

MonsterParam::~MonsterParam(){
    
}