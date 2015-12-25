//
//  Stone.hpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#ifndef Stone_hpp
#define Stone_hpp

#include <stdio.h>

USING_NS_CC;


class Stone :public cocos2d::Sprite{
private:
    typedef Sprite super;
public:
    virtual void init(const char *pName) =0;
    static Stone* create(const std::string& name);
    
    
};



#endif /* Stone_hpp */
