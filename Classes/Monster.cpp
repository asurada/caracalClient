//
//  Monster.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#include "Monster.hpp"

Monster* Monster::create(const std::string& name){
    return (Monster*)super::create(name);
}