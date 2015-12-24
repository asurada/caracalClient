//
//  OperationLayer.cpp
//  caracalClient
//
//  Created by 厳 巍 on 2015/12/23.
//
//

#include "OperationLayer.h"


OperationLayer::OperationLayer()
{
//    magicSprites = CCArray::create();
//    magicSprites->retain();
//    magicMarks->retain();
    brush = Sprite::create("largeBrush.png");
    brush->retain();
}

OperationLayer::~OperationLayer(){
    
}


bool OperationLayer::init()
{
    bool bRet = false;
    //CCSize s = CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCDirector * pDirector = cocos2d::CCDirector::sharedDirector();
    //CCLOG("width=%f,height=%f",s.width,s.height);
  //  _touchTrailLayer = TouchTrailLayer::create();
  //  _touchTrailLayer->setDelegate(this);
    marklayer = Layer::create();
    marklayer->setContentSize(Size(pDirector->getWinSize().width,pDirector->getWinSize().height/2));
    marklayer->setAnchorPoint(Point(0.5,0.5));
    marklayer->setPosition(Point(0,0));
    if(!LayerColor::initWithColor(Color4B(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height/2))
    {
        return false;
    }
    setTouchEnabled(true);
    bRet = true;
    this->addChild(_touchTrailLayer,2);
    this->addChild(marklayer,1);
    //#define TRIANGLE 3
    //#define RECT     4
    //#define RHOMBUS  5
    //#define PENTAGON 6
    //#define HEXAGON  7
    //analysisLogic = this->createBall(HEXAGON);
    CCArray* array = Array::create();
    array->addObject(StoneData::create("bll_01.png"));
    array->addObject(StoneData::create("bll_02.png"));
    array->addObject(StoneData::create("bll_03.png"));
    array->addObject(StoneData::create("bll_04.png"));
    array->addObject(StoneData::create("bll_05.png"));
    array->addObject(StoneData::create("bll_06.png"));
    analysisLogic->init(this,array);
    return bRet;
}



bool OperationLayer::onTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch;
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        if(magicSprites != NULL && this->magicSprites->count()>0){
            magicSprites->removeAllObjects();
        }
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
    return true;
}

void OperationLayer::onTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        CCTouch* touch = (CCTouch*)(*it);
        if(!touch)
            break;
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
}

void OperationLayer::onTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
    }
}

void OperationLayer::onTouchCancelled(Touch* touch, Event* event){
    
}
