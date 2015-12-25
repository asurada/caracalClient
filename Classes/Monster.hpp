//
//  Monster.hpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
USING_NS_CC;


class Monster :public cocos2d::Sprite{
private:
    typedef Sprite super;
public:
    virtual void init(const char *pName) =0;
    static Monster* create(const std::string& name);
    
};
#endif /* Monster_hpp */
