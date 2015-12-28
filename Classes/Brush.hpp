//
//  Brush.hpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/28.
//
//

#ifndef Brush_hpp
#define Brush_hpp

#include <stdio.h>
USING_NS_CC;



class Brush :public cocos2d::Sprite{
private:
    typedef Sprite super;
public:
    virtual void init(const char *pName) =0;
    static Brush* create(const std::string& name);
    
};

#endif /* Brush_hpp */
