//
//  Monster.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#include "Monster.hpp"

Monster* Monster::create(const std::string& name){
    return (Monster*)super::create(name);
}


void Monster::setDelegate(MonsterDelegate*  delegate){
    monsterDelegate = delegate;
}

int Monster::updateHp(int value){
    hpValue = hpValue + value;
    return hpValue;
}

void Monster::attack(){
    
}

void Monster::defend(){
    
}


void Monster::invokeMagic(){
    
}

Magic* Monster::judgeMagic(Vector<String*> magics){
    return NULL;
}


void StoneDelegate::stoneAttck(){
    
}