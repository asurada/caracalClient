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
#include "MonsterParam.hpp"
#include "MonsterLogic.hpp"

USING_NS_CC;

class Monster : public cocos2d::Sprite
{
private:
    typedef Sprite super;
    Magic* currentMagic;
   //Monster* enemy;
    
    MonsterParam* param;
    MonsterLogic* logic;
    std::vector<Stone*>  stones;
    MonsterDelegate* monsterDelegate;
    
public:
    Monster();
    ~Monster();
    static Monster* create(const std::string& name);
    void initOpition();
    
    
    
    void addStone(Stone* _stones);
    void invokeMagic();
    void attack();
    void defend();
    
    MonsterParam* getParam();
    
    void setDelegate(MonsterDelegate*  delegate);
    Magic* judgeMagic(std::vector<int> magics);

    std::vector<Stone*> getStones();
 
};

#endif /* Monster_hpp */
