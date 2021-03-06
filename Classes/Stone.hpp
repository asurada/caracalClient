//
//  Stone.hpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#ifndef Stone_hpp
#define Stone_hpp

#include <stdio.h>
#include "StoneDelegate.hpp"


USING_NS_CC;


class Stone :public cocos2d::Sprite{
private:
    typedef Sprite super;
    void addEvents();
    int magicValue;
    
    StoneDelegate* stoneDelegate;
    //return initWithTexture(nullptr, Rect::ZERO );
    
public:
    
    static Stone* create(const std::string& name);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    void initOptions();
    
    void invokeMagic();
    void setStoneDelegate(StoneDelegate* stoneDelegate);

    Stone();
    ~Stone();

};



#endif /* Stone_hpp */
