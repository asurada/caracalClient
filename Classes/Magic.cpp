//
//  Magic.cpp
//  caracalClient
//
//  Created by Yan Wei on 2016/01/19.
//
//

#include "Magic.hpp"

Magic::Magic()
{
    
}

Magic::~Magic(){
    CCLOG("release");
}



void Magic::set_force(int force){
    _force = force;
}

void Magic::set_effectId(int effectid){
    _effectId = effectid;
}

void Magic::set_defend(int defend){
    _defend = defend;
}

void Magic::set_magic(int magic){
    _magic = magic;
}

void Magic::set_magic_type(int type){
    _magic_type = type;
}

int Magic::get_force(){
    return _force;
}

int Magic::get_effectId(){
    return _effectId;
}

int Magic::get_defend(){
    return _defend;
}

int Magic::get_magic(){
    return _magic;
}
