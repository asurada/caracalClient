//
//  Magic.hpp
//  caracalClient
//
//  Created by Yan Wei on 2016/01/19.
//
//

#ifndef Magic_hpp
#define Magic_hpp

#include <stdio.h>


class Magic{
private:
    int _effectId;
    int _force;
    int _defend;
    int _magic;
    int _magic_type;//3,4,5,6,7
    
public:
    void magicInvoke();
    Magic();
    ~Magic();
 
    void set_force(int force);
    void set_effectId(int effectid);
    void set_defend(int defend);
    void set_magic(int magic);
    void set_magic_type(int type);
    
    int get_force();
    int get_effectId();
    int get_defend();
    int get_magic();
    
};


#endif /* Magic_hpp */
