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
//    static OperationLayer* create();
//    std::vector<cocos2d::Point> tempMagicPoints;
//    Array *magicMarks;
//    Array *magicSprites;
//    Sprite* brushSprite;
//    Sprite* makeBrushImage();
//    void fadeout(Sprite* sprite,float time);
//    void draw(Point point);
//    void removeAllMagicSquare();
    
private:
    OperationLayer();
    ~OperationLayer();
    Sprite *brush;
    Layer * marklayer;
//    Sprite* isHit(cocos2d::Point point);
//    Sprite* addMark(Point point);
//    Sprite* adjustMark(Sprite* brush,Point start,Point end);
//    void animate(Sprite *spirit);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);

//  void touchBegin_TouchTrail(Point point);
//  void touchMove_TouchTrail(Point point);
//  void touchEnd_TouchTrail(Point point);
    void onPop(Point point);
    void onPopLast(Point point);
    void onPopStop();
    
};

#endif /* OperationLayer_hpp */
