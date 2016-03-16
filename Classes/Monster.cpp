//
//  Monster.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#include "Monster.hpp"

Monster* Monster::create(const std::string& name){
    Monster* sprite = new Monster();
    if(sprite->initWithFile(name)){
        sprite->initOpition();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;


}

void Monster::initOpition(){
    param = new MonsterParam();
    logic = new MonsterLogic();
}

void Monster::setDelegate(MonsterDelegate*  delegate){
    monsterDelegate = delegate;
}


void Monster::attack(){
    
}

void Monster::defend(){
    
}


void Monster::invokeMagic(){
    
}

std::vector<Stone*>  Monster::getStones(){
    return stones;
}

Magic* Monster::judgeMagic(std::vector<int> magics){
    std::string strSeq = "";
    for (int seq:magics) {
          strSeq = StringUtils::format("%s\n%d",strSeq.c_str(),seq);
    }
    CCLOG("%s",strSeq.c_str());
    int result = logic->getMagicType(strSeq);
    CCLOG("magic :%d",result);
    return NULL;
}


void StoneDelegate::stoneAttck(){
    
}

void Monster::addStone(Stone* _stone){
    stones.push_back(_stone);
}



Monster::Monster(){}

Monster::~Monster(){}