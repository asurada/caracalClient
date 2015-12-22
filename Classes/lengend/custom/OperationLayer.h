//
//  OperationLayer.h
//  legend
//
//  Created by 厳 巍 on 2014/05/21.
//
//

#ifndef __legend__OperationLayer__
#define __legend__OperationLayer__
#include "cocos2d.h"
#include "ShapeConst.h"
#include "AnalysisHexagon.h"
#include "AnalysisTriangle.h"
#include "AnalysisRhombus.h"
#include "AnalysisRect.h"
#include "AnalysisPentagon.h"

#include "OperationCallback.h"
#include "AnalysisFactory.h"
#include "TouchTrailLayer.h"
#include "TouchTrailCallback.h"


USING_NS_CC;

class OperationLayer : public cocos2d::CCLayerColor,TouchTrailCallback
{
public:
    int _shape;
    virtual bool init();
    static OperationLayer* create();
    AnalysisLogic* createBall(int shape);
    TouchTrailLayer *_touchTrailLayer;
    CC_SYNTHESIZE(OperationCallback*, operationCallBack, Delegate);
    std::vector<cocos2d::Point> tempMagicPoints;
    Array *magicMarks;
    Array *magicSprites;
    cocos2d::Sprite* brushSprite;
    cocos2d::Sprite* makeBrushImage();
    void fadeout(Sprite* sprite,float time);
    void draw(cocos2d::Point point);
    void removeAllMagicSquare();
    
private:
    OperationLayer();
    ~OperationLayer();
    ResultData *resultData;
    AnalysisFactory* factory;
    AnalysisLogic* analysisLogic;
    
    cocos2d::Sprite *brush;
    Layer * marklayer;
    Sprite* isHit(cocos2d::Point point);
    cocos2d::Sprite* addMark(Point point);
    cocos2d::Sprite* adjustMark(Sprite* brush,Point start,Point end);
    void animate(Sprite *spirit);
    
    void onTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
    void onTouchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
    void onTouchesBegan(cocos2d::Set* touches, cocos2d::Event* event);
    void touchBegin_TouchTrail(cocos2d::Point point);
    void touchMove_TouchTrail(cocos2d::Point point);
    void touchEnd_TouchTrail(cocos2d::Point point);
    void onPop(cocos2d::Point point);
    void onPopLast(cocos2d::Point point);
    void onPopStop();
};

#endif