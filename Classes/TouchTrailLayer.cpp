/*
 * CCBlade
 *
 * Copyright (c) 2011 - Ngo Duc Hiep
 * Copyright (c) 2012 - YangLe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "TouchTrailLayer.h"
#include "CCBlade.h"
#define kFileStreak "Deco_shine_v1.png"
#define kBrushStreak "brush.png"

USING_NS_CC;

TouchTrailLayer::TouchTrailLayer()
{
    setTouchEnabled(true);
    _bladeSparkle = ParticleSystemQuad::create("blade_sparkle.plist");
    _bladeSparkle->stopSystem();
    this->addChild(_bladeSparkle);
    addEvents();
}

TouchTrailLayer* TouchTrailLayer::create()
{
    TouchTrailLayer *pRet = new TouchTrailLayer();
    pRet->autorelease();
    return pRet;
}

void TouchTrailLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& pTouches, Event *pEvent)
{
    _points.clear();
    for(auto& touch : pTouches){
        CCBlade *blade = CCBlade::create(kFileStreak, 24, 20);
        CCLOG("touch begin");
        _map[touch] = blade;
		addChild(blade);
        blade->setColor(Color3B(255,0,0));
        //blade->setOpacity(100);
        blade->setDrainInterval(1.0/40);
        point = convertTouchToNodeSpace(touch);
		if(touchTrailCallback != NULL){
            touchTrailCallback->touchBegin_TouchTrail(point);
        }
        blade->push(point);
        _bladeSparkle->setPosition(point);
        _bladeSparkle->resetSystem();
	}
}

void TouchTrailLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& pTouches, Event *pEvent)
{
    for(auto& touch : pTouches){
        CCLOG("touch move");
        if (_map.find(touch) == _map.end()) continue;
        CCBlade *blade = _map[touch];
        Point point = convertTouchToNodeSpace(touch);
        if(touchTrailCallback != NULL){
            touchTrailCallback->touchMove_TouchTrail(point);
        }
        point = point*0.5f + touch->getPreviousLocation()*0.5f;
        CCLOG("touch x:%f y:%f",point.x,point.y);
		blade->push(point);
         _bladeSparkle->setPosition(point);
    }
}

void TouchTrailLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& pTouches, Event *pEvent)
{
     for(auto& touch : pTouches){
        CCLOG("touch end");
        if (_map.find(touch) == _map.end()) continue;
        CCBlade *blade = _map[touch];
        blade->autoCleanup();
        Point point = convertTouchToNodeSpace(touch);
        if(touchTrailCallback != NULL){
            touchTrailCallback->touchEnd_TouchTrail(point);
        }
        _map.erase(touch);
        _bladeSparkle->stopSystem();
    }
    autoDrawAfterFinger();
}


bool TouchTrailLayer::onTouchBegan(Touch* touch, Event *pEvent)
{

    CCBlade *blade = CCBlade::create(kFileStreak, 24, 20);
    CCLOG("touch begin");
    _map[touch] = blade;
    addChild(blade);
    blade->setColor(Color3B(255,0,0));
    //blade->setOpacity(100);
    blade->setDrainInterval(1.0/40);
    point = convertTouchToNodeSpace(touch);
    if(touchTrailCallback != NULL){
        touchTrailCallback->touchBegin_TouchTrail(point);
    }
    blade->push(point);
    _bladeSparkle->setPosition(point);
    _bladeSparkle->resetSystem();
    return true;

}

void TouchTrailLayer::onTouchMoved(Touch* touch, Event *pEvent)
{

        CCLOG("touch move");
        if (_map.find(touch) == _map.end()) return;
        CCBlade *blade = _map[touch];
        Point point = convertTouchToNodeSpace(touch);
        if(touchTrailCallback != NULL){
            touchTrailCallback->touchMove_TouchTrail(point);
        }
        point = point*0.5f + touch->getPreviousLocation()*0.5f;
        CCLOG("touch x:%f y:%f",point.x,point.y);
        blade->push(point);
        _bladeSparkle->setPosition(point);

}

void TouchTrailLayer::onTouchEnded(Touch* touch, Event *pEvent)
{

    CCLOG("touch end");
    if (_map.find(touch) == _map.end()) return;
    CCBlade *blade = _map[touch];
    blade->autoCleanup();
    Point point = convertTouchToNodeSpace(touch);
    if(touchTrailCallback != NULL){
        touchTrailCallback->touchEnd_TouchTrail(point);
    }
    _map.erase(touch);
    _bladeSparkle->stopSystem();
    
    autoDrawAfterFinger();
}


void TouchTrailLayer::addEvents()
{
    auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true);
    
    listener->onTouchesBegan = CC_CALLBACK_2(TouchTrailLayer::onTouchesBegan,this);
    
    listener->onTouchesMoved = CC_CALLBACK_2(TouchTrailLayer::onTouchesMoved,this);
    
    listener->onTouchesEnded = CC_CALLBACK_2(TouchTrailLayer::onTouchesEnded,this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}




float alphaX = 5;
float alphaY = 5;
void TouchTrailLayer::autoDraw(){
    Size winSize = Director::getInstance()->getWinSize();

    if(_x > winSize.width){
        alphaX = -( CCRANDOM_0_1()+ 10);
    }
    
    if(_x < 0){
        alphaX = CCRANDOM_0_1()+ 10;
    }
    
    if(_y >winSize.height){
        alphaY = -(CCRANDOM_0_1()+ 10);
    }
    
    if(_y < 0){
        alphaY = CCRANDOM_0_1()+ 10;
    }
    _x = _x + alphaX;
    _y = _y + alphaY;
    
    point = Vec2(_x, _y);
//    float root = 60 - pow(_y,2);
//    if(root > 0){
//        _x = sqrtf(root);
//    }else{
//        _x = -sqrtf(root);
//    }
    blade->push(point);
}


void TouchTrailLayer::drawRound(Point center){
    _y = _y + alphaY;
    if(_y > 650){
        alphaY = -5;
    }
    if(_y < 50){
        alphaY = 5;
    }
    float root = pow(300,2) - pow(_y-350,2);
    if(root > 350){
        _x = sqrtf(root);
    }else{
        _x = -sqrtf(-root);
    }
    point = Vec2(_x+350, _y);
    blade->push(point);
}

bool TouchTrailLayer::insert(Point point){
    if(_points.size() == 0){
        _points.insert(_points.begin(), point);
        return true;
    }else if(_points.size() > 0){
        Point beginPoint =  _points.at(0);
        if(beginPoint.getDistance(point)){
            _points.insert(_points.begin(), point);
            return true;
        }
    }
    return false;
}

bool TouchTrailLayer::isCloseShape(Point point){
    if(_points.size() < 3){
        return false;
    }
    for (int index =0; index<_points.size()-1; index++) {
        Point it = _points.at(index);
        if(it.equals(point)){
            return true;
        }
    }
    return false;
}



void TouchTrailLayer::autoDrawPoints(float frame){
    CCLOG("_point.size :%d",(int)_points.size());
    if(_points.size() > 1){
        Point point = _points.back();
        blade->push(point);
        touchTrailCallback->onPop(point);
        _points.pop_back();
    }else if(_points.size() == 1){
        Point point = _points.back();
        blade->push(point);
        touchTrailCallback->onPopLast(point);
        _points.pop_back();
    }else{
        touchTrailCallback->onPopStop();
        unschedule(schedule_selector(TouchTrailLayer::autoDrawPoints));
    }
}


void TouchTrailLayer::autoDrawAfterFinger(){
    CCLOG("autoDrawAfterFinger");
    blade = CCBlade::create(kFileStreak, 24, 30);
    addChild(blade);
    blade->setDrainInterval(1.5/40.0);
    schedule(schedule_selector(TouchTrailLayer::autoDrawPoints), 1.0/40.0f);
}

void TouchTrailLayer::bladeCleanup(){
    blade->setDrainInterval(1/40.0);
}


bool TouchTrailLayer::isCollide(cocos2d::Point object, cocos2d::Point target, float distance){
    float result = (object-target).getLength();
    if(result <= distance){
        return true;
    }
    return false;
}


