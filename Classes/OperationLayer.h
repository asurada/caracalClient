//
//  OperationLayer.hpp
//  caracalClient
//
//  Created by 厳 巍 on 2015/12/23.
//
//

#ifndef OperationLayer_hpp
#define OperationLayer_hpp
#include "Stone.hpp"
#include "TouchTrailLayer.h"
#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

class OperationLayer : public cocos2d::LayerColor,TouchTrailCallback
{
  
public:
//    int _shape;
    virtual bool init();
    static cocos2d::Scene* createScene();
    static OperationLayer* create();
    
private:
    OperationLayer();
    ~OperationLayer();
    Sprite *brush;
    Stone* preStone;
    Layer * marklayer;
    Label* myLabel;
   
    void addEvents();
    Sprite* addBrush(Point point);
    Vector<Stone*> stones;
    Vector<Sprite*> brushes;
    Vector<String*> order;
    TouchTrailLayer *_touchTrailLayer;
    Sprite* adjustBrush(Sprite* brush,const Vec2& end);
    void initOptions();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    

    
    void touchBegin_TouchTrail(Point point);
    void touchMove_TouchTrail(Point point);
    void touchEnd_TouchTrail(Point point);
    void onPop(Point point);
    void onPopLast(Point point);
    void onPopStop();
};

#endif /* OperationLayer_hpp */
