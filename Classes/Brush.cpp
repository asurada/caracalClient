//
//  Brush.cpp
//  caracalClient
//
//  Created by Yan Wei on 2015/12/28.
//
//

#include "Brush.hpp"

Brush* Brush::create(const std::string& name){
    return (Brush*)super::create(name);
}