//
//  AnimationTool.h
//  legend
//
//  Created by Yan Wei on 2014/08/11.
//
//

#ifndef __legend__AnimationTool__
#define __legend__AnimationTool__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class AnimationTool{
    public:
    static Sprite* startFireAnm(Point &pos,const char * image,const char * plist,const char * imgSplit,int count,const char *format,Object* pSelectorTarget,SEL_CallFuncND selector);
    static void setBullet(Sprite * bullet,float radius, float density,float friction,float restitution, b2World* world);

    
};

#endif /* defined(__legend__AnimationTool__) */
