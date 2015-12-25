//
//  OperationLayer.hpp
//  caracalClient
//
//  Created by 厳 巍 on 2015/12/23.
//
//

#ifndef OperationLayer_hpp
#define OperationLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class OperationLayer : public cocos2d::LayerColor
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
    Layer * marklayer;
    
   
    void addEvents();
    void initOptions();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
};

#endif /* OperationLayer_hpp */
