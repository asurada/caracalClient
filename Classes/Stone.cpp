//
//  Stone.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#include "Stone.hpp"




Stone::Stone()
{

}

Stone::~Stone(){
    CCLOG("release");
}



Stone* Stone::create(const std::string& name){
    Stone* pSprite = new Stone();
    if (pSprite->initWithFile(name))
    {
        pSprite->autorelease();
        pSprite->initOptions();
       // pSprite->addEvents();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}


void Stone::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p))
        {
            Stone::onTouchBegan(touch,event);
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event){
        Stone::onTouchMoved(touch,event);
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Vec2 p = touch->getLocation();
        Stone::onTouchEnded(touch,event);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Stone::initOptions()
{
    return ;
}


bool Stone::onTouchBegan(Touch *touch, Event *pEvent)
{
    
    CCLOG("onTouchBegan Stone");
    return true;
}

void Stone::onTouchMoved(Touch *touch, Event *pEvent)
{
    CCLOG("onTouchMoved Stone");
    Vec2 p = touch->getLocation();
    
}

void Stone::onTouchEnded(Touch *touch, Event *pEvent)
{
    CCLOG("onTouchEnded Stone");
}

void Stone::onTouchCancelled(Touch* touch, Event* event){
    CCLOG("onTouchCancelled");
}
