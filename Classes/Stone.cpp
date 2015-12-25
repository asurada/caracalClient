//
//  Stone.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/25.
//
//

#include "Stone.hpp"


Stone* Stone::create(const std::string& name){
    return (Stone*)super::create(name);
}