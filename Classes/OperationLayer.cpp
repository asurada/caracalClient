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
#include "ui/CocosGUI.h"
#include "HUDLayer.hpp"

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
    monsterObject->stones.clear();
    delete monsterObject;
}


bool OperationLayer::init()
{
    bool bRet = false;
    Director * pDirector = Director::getInstance();
    marklayer = Layer::create();
    marklayer->setContentSize(Size(pDirector->getWinSize().width,pDirector->getWinSize().height/2));
    marklayer->setAnchorPoint(Point(0.5,0.5));
    marklayer->setPosition(Point(0,0));
    _touchTrailLayer = TouchTrailLayer::create();
    _touchTrailLayer->setDelegate(this);
    if(!LayerColor::initWithColor(Color4B(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height))
    {
        return false;
    }
    
    this->setTouchEnabled(true);

    bRet = true;
    this->addChild(_touchTrailLayer,2);
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
    std::string strOrder = "";

    for (int str:order) {
        strOrder = StringUtils::format("%s\n%d",strOrder.c_str(),str);
    }
    Magic* magic = monsterObject->judgeMagic(order);
    
    order.clear();
    myLabel->setString(strOrder.c_str());
    

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
    
    myLabel = Label::createWithBMFont("myFont.fnt", "Your Text");
    myLabel->setPosition(Point(180,208));
    this->addChild(myLabel);
    
    auto button = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
    button->setTitleText("clear");
    
    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
//                for (Sprite*  brush : brushes) {
//                    brush->removeFromParentAndCleanup(true);
//                }
//                brushes.clear();
               //HUDLayer *layer2 = HUDLayer::create();
               // CC_BREAK_IF(! layer2);
               // add the layers as a child to scene
               this->addChild(HUDLayer::create(), 5);
               break;
            default:
               break;
        }
    });
    button->setPosition(Point(230,278));
    this->addChild(button);

    monsterObject  = Monster::create("monster.png");

    Stone * stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(300,94));
    this->addChild(stoneObject);
    stoneObject->setTag(3);
    monsterObject->addStone(stoneObject);
    
    stoneObject  = Stone::create("bll_02.png");
    stoneObject->setPosition(Point(230,148));
    this->addChild(stoneObject);
    stoneObject->setTag(4);
    monsterObject->addStone(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(230,40));
    this->addChild(stoneObject);
    stoneObject->setTag(2);
    monsterObject->addStone(stoneObject);
    
    stoneObject  =  Stone::create("bll_02.png");
    stoneObject->setPosition(Point(170,94));
    this->addChild(stoneObject);
    stoneObject->setTag(1);
    monsterObject->addStone(stoneObject);
    
//    stoneObject  =  Stone::create("bll_02.png");
//    stoneObject->setPosition(Point(309,94));
//    this->addChild(stoneObject);
//    stoneObject->setTag(5);
//    stones.pushBack(stoneObject);
//    
//    stoneObject  =  Stone::create("bll_02.png");
//    stoneObject->setPosition(Point(290,100));
//    this->addChild(stoneObject);
//    stoneObject->setTag(6);
//    stones.pushBack(stoneObject);
    
    //monsterObject->setStone(stones);
    
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
            _touchTrailLayer->onTouchBegan(touch, event);
            for (auto stone : monsterObject->stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    preStone = stone;
                    CCLOG("start :%d",stone->getTag());
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
            _touchTrailLayer->onTouchMoved(touch, event);
             for (auto stone : monsterObject->stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    if(brush == NULL)return;
                    if(preStone == stone)return;
                    brush->setTag(1);
                    //order.push_back(StringUtils::format("(%d,%d)",preStone->getTag(),stone->getTag()));
                    order.push_back(stone->getTag());
                    CCLOG("stone(%d,%d)",preStone->getTag(),stone->getTag());
                    brush = adjustBrush(brush,stone->getPosition());
                    brushes.pushBack(brush);
                    preStone = stone;
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
            _touchTrailLayer->onTouchEnded(touch, event);
            for (auto stone : monsterObject->stones){
                cocos2d::Rect rect = stone->getBoundingBox();
                if(rect.containsPoint(p)){
                    brush = adjustBrush(brush,stone->getPosition());
                    stone->onTouchEnded(touch, event);
                }
            }
        }
        

    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    
    
//    auto listen2 = cocos2d::EventListenerTouchAllAtOnce::create();
//    listen2->onTouchesBegan = CC_CALLBACK_2(TouchTrailLayer::onTouchesBegan,_touchTrailLayer);
//    listen2->onTouchesMoved = CC_CALLBACK_2(TouchTrailLayer::onTouchesMoved,_touchTrailLayer);
//    listen2->onTouchesEnded = CC_CALLBACK_2(TouchTrailLayer::onTouchesEnded,_touchTrailLayer);
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen2, _touchTrailLayer);
}


Brush* OperationLayer::addBrush(Point point){
    Brush *brush = Brush::create("brush.png");
    brush->setAnchorPoint(Vec2(0,0.5));//image height/2
    brush->setPosition(point);
    brush->setOpacity(225);
    brush->setScaleX(1/320);
    brush->setTag(0);
    this->addChild(brush);
    return brush;
}





Brush* OperationLayer::adjustBrush(Brush* brush,const Vec2& end){
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


void OperationLayer::touchBegin_TouchTrail(Point point){
   CCLOG("touchBegin_TouchTrail");
   if(_touchTrailLayer->insert(point)){
      
       //魔法石毎アニメ
        //animate(spirit);
    }

}

void OperationLayer::touchMove_TouchTrail(Point point){
    CCLOG("touchMove_TouchTrail");
    if(_touchTrailLayer->insert(point)){
       
    }

}


void OperationLayer::touchEnd_TouchTrail(Point point){
    CCLOG("touchEnd_TouchTrail");
     _touchTrailLayer->autoDrawAfterFinger();
}

void OperationLayer::onPop(Point point){
}

void OperationLayer::onPopLast(Point point){
}

void OperationLayer::onPopStop(){
    
}




