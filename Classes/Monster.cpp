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
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;


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

std::vector<Stone*>  Monster::getStones(){
    return stones;
}

Magic* Monster::judgeMagic(std::vector<int> magics){
    std::string strSeq = "";
    for (int seq:magics) {
          strSeq = StringUtils::format("%s\n%d",strSeq.c_str(),seq);
    }
    CCLOG("%s",strSeq.c_str());
    int result = getMagicType(strSeq);
    CCLOG("magic :%d",result);
    return NULL;
}


void StoneDelegate::stoneAttck(){
    
}

void Monster::addStone(Stone* _stone){
  
    //stones = _stones;
    stones.push_back(_stone);

    // if(stones.size() >0){
    //     stones.clear();
    // }
    //stones.pushBack(_stone);
}



magic_type Monster::getMagicType(std::string magic){
    if (magic == "1231" ||
        magic == "2312" ||
        magic == "3123") {
        
        return C1;
        //時計順三角 C1
    }
    
    if (magic == "1321" ||
        magic == "3213" ||
        magic == "2132") {
        
        return C2;
        //逆時計順三角 C2
    }
    
    if (magic == "12341" ||
        magic == "23412" ||
        magic == "34123" ||
        magic == "41234" ){
        
        return C3;
        //時計順四角 C3
    }
    
    if (magic == "43214" ||
        magic == "32143" ||
        magic == "21432" ||
        magic == "14321" ){
        
        return C4;
        //時計順四角 C4
    }
    
    if (magic == "12431" ||
        magic == "24312" ||
        magic == "43124" ||
        magic == "31243" ||
        magic == "13421" ||
        magic == "34213" ||
        magic == "42134" ||
        magic == "21342" ){
        
        return C5;
        //对三角 C5
    }
    
    if (magic == "14231" ||
        magic == "42314" ||
        magic == "23142" ||
        magic == "31423" ||
        magic == "14231" ||
        magic == "42314" ||
        magic == "23142" ||
        magic == "31423" ){
        
        return C6;
        //逆对三角 C6
    }

    
    if (magic == "123451" ||
        magic == "234512" ||
        magic == "345123" ||
        magic == "451234" ||
        magic == "512345" ){
        
        return C7;
        //5角形状 C7
    }
    
    if (magic == "154321" ||
        magic == "543215" ||
        magic == "432154" ||
        magic == "321543" ||
        magic == "215432" ){
         return C8;
        //逆5角形状 C8
    }
    
    
    if (magic == "253142" ||
        magic == "531425" ||
        magic == "314253" ||
        magic == "142531" ||
        magic == "425314" ){
        
         return C9;
        //星形 C9
    }
    
    if (magic == "524135" ||
        magic == "135241" ||
        magic == "241352" ||
        magic == "352413" ||
        magic == "413524" ){
        
        return C10;
        //星形 C10
    }
    
    if (magic == "1251341" ||
        magic == "1251431" ||
        magic == "1521341" ||
        magic == "1521431" ||
        magic == "1341251" ||
        magic == "1341521" ||
        magic == "1431251" ||
        magic == "1431521" ){
        
        return C11;
        //重合双三角形 C11
    }
    
    if (magic == "1231451" ||
        magic == "1231541" ||
        magic == "1321541" ||
        magic == "1321451" ||
        magic == "1451321" ||
        magic == "1451231" ||
        magic == "1541231" ||
        magic == "1541321" ){
        
        return C12;
        //分离双三角形 C12
    }

    return C0;
    
}

Monster::Monster(){}

Monster::~Monster(){}