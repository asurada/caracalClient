//
//  OperationLayer.cpp
//  caracalClient
//
//  Created by 厳 巍 on 2015/12/23.
//
//

#include "OperationLayer.h"
#include "Stone.hpp"
#include "Monster.hpp"


OperationLayer::OperationLayer()
{
//    magicSprites = CCArray::create();
//    magicSprites->retain();
//    magicMarks->retain();
//    brush = Sprite::create("largeBrush.png");
//    brush->retain();
}

OperationLayer::~OperationLayer(){
    
}


bool OperationLayer::init()
{
    bool bRet = false;
    Director * pDirector = Director::getInstance();
    marklayer = Layer::create();
    marklayer->setContentSize(Size(pDirector->getWinSize().width,pDirector->getWinSize().height/2));
    marklayer->setAnchorPoint(Point(0.5,0.5));
    marklayer->setPosition(Point(0,0));
    if(!LayerColor::initWithColor(Color4B(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height/2))
    {
        return false;
    }
    
    this->setTouchEnabled(true);

    bRet = true;
    this->addChild(marklayer,1);
    Vect array;

    return bRet;
}



bool OperationLayer::onTouchBegan(Touch *touch, Event *pEvent)
{

    CCLOG("onTouchBegan");
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    return true;
}

void OperationLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
    Vec2 p = touch->getLocation();
   CCLOG("onTouchMoved x:%f,y:%f",p.x,p.y);

  
//    Touch* touch = (Touch*)(*it);
//    if(!touch)
//        break;
//    Point location = touch->getLocationInView();
//    location = Director::sharedDirector()->convertToGL(location);
    
}

void OperationLayer::onTouchEnded(Touch *touch, Event *pEvent)
{
    CCLOG("onTouchEnded");
//    for( it = pTouches->begin(); it != pTouches->end(); it++)
//    {
//        touch = (CCTouch*)(*it);
//        
//        if(!touch)
//            break;
//        
//    }
}

void OperationLayer::onTouchCancelled(Touch* touch, Event* event){
     CCLOG("onTouchCancelled");
}

Scene* OperationLayer::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OperationLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


OperationLayer* OperationLayer::create()
{
    OperationLayer* pSprite = new OperationLayer();
    
    if (pSprite->init())
    {
        pSprite->autorelease();
        pSprite->initOptions();
        pSprite->addEvents();
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void OperationLayer::initOptions()
{
//    Sprite *spriteObject = Sprite::create("monster.png");
//    spriteObject->setPosition(Point(300,300));
//    this->addChild(spriteObject);
    Stone * stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,400));
    this->addChild(stoneObject);
    
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(226,148));
    this->addChild(stoneObject);
    
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,300));
    this->addChild(stoneObject);
    
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,300));
    this->addChild(stoneObject);
    
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,300));
    this->addChild(stoneObject);
    
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,300));
    this->addChild(stoneObject);
    
    
    
    Monster * monsterObject  = Monster::create("monster.png");
    monsterObject->setPosition(Point(300,300));
    this->addChild(monsterObject);
    
    // do things here like setTag(), setPosition(), any custom logic.
}



void OperationLayer::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p))
        {
            OperationLayer::onTouchBegan(touch,event);
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event){
         OperationLayer::onTouchMoved(touch,event);
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Vec2 p = touch->getLocation();
        OperationLayer::onTouchEnded(touch,event);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

