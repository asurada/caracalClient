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
    CCLOG("release");
}


bool OperationLayer::init()
{
    bool bRet = false;
    Director * pDirector = Director::getInstance();
    marklayer = Layer::create();
    marklayer->setContentSize(Size(pDirector->getWinSize().width,pDirector->getWinSize().height/2));
    marklayer->setAnchorPoint(Point(0.5,0.5));
    marklayer->setPosition(Point(0,0));
    if(!LayerColor::initWithColor(Color4B(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height))
    {
        return false;
    }
    
    this->setTouchEnabled(true);

    bRet = true;
    this->addChild(marklayer,1);
    return bRet;
}



bool OperationLayer::onTouchBegan(Touch *touch, Event *pEvent)
{

    CCLOG("onTouchBegan");
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    //brush = addBrush(location);
    return true;
}

void OperationLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
    Vec2 p = touch->getLocation();
    if(brush != NULL){
        brush = adjustBrush(brush,p);
    }
    CCLOG("onTouchMoved x:%f,y:%f",p.x,p.y);

    
}

void OperationLayer::onTouchEnded(Touch *touch, Event *pEvent)
{
    CCLOG("onTouchEnded");

    if(brush != NULL && brush->getTag() == 0){
        brush->removeFromParentAndCleanup(true);
        brush = NULL;
    }

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

    Stone * stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,400));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(230,148));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(230,40));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(170,94));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(309,94));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(290,100));
    this->addChild(stoneObject);
    stones.pushBack(stoneObject);
    
    
    Monster * monsterObject  = Monster::create("monster.png");
    monsterObject->setPosition(Point(230,94));
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
            for (auto stone : stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    brush = addBrush(stone->getPosition());
                    stone->onTouchBegan(touch, event);
                }
            }


            return true; // to indicate that we have consumed it.
        }
        
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event){
    
        Vec2 p = touch->getLocation();
        
        cocos2d::Rect rect = this->getBoundingBox();
        if(rect.containsPoint(p))
        {
            OperationLayer::onTouchMoved(touch,event);
             for (auto stone : stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    brush = adjustBrush(brush,stone->getPosition());
                    if(brush == NULL)return;
                    brush->setTag(1);
                    brush = addBrush(stone->getPosition());
                    stone->onTouchMoved(touch, event);
                }
            }
        }
        
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {

        Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        if(rect.containsPoint(p))
        {
            OperationLayer::onTouchEnded(touch,event);
            
            for (auto stone : stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    brush = adjustBrush(brush,stone->getPosition());
                    stone->onTouchEnded(touch, event);
                }
            }
        }
        

    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}


Sprite* OperationLayer::addBrush(Point point){
    Sprite *brush = Sprite::create("brush.png");
    brush->setAnchorPoint(Vec2(0,0.5));//image height/2
    brush->setPosition(point);
    brush->setOpacity(225);
    brush->setScaleX(1/320);
    brush->setTag(0);
    this->addChild(brush);
    return brush;
}


Sprite* OperationLayer::adjustBrush(Sprite* brush,Point end){
    if(brush == NULL) return brush;
    if(end.isZero())return brush;
    float dist = end.getDistance(brush->getPosition());
    Point diffPoint = Vec2(brush->getPosition(),end);
    float angleRadians = atan2f(diffPoint.y, diffPoint.x);
    angleRadians = -angleRadians;
    float cocosAngle = CC_RADIANS_TO_DEGREES(angleRadians);
    brush->setRotation(cocosAngle);
    brush->setScaleX(dist*4/320);
    return brush;
}

