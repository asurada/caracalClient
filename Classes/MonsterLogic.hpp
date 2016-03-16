//
//  MonsterLogic.hpp
//  caracalClient
//
//  Created by Yan Wei on 2016/03/16.
//
//

#ifndef MonsterLogic_hpp
#define MonsterLogic_hpp

#include <stdio.h>

enum magic_type
{
    C0 = 0,
    C1 = 1,
    C2 = 2,
    C3 = 3,
    C4 = 4,
    C5 = 5,
    C6 = 6,
    C7 = 7,
    C8 = 8,
    C9 = 9,
    C10,
    C11,
    C12,
    C13,
    C14,
};


class MonsterLogic{
    
private:
    
public:
    magic_type getMagicType(std::string magic);
    MonsterLogic();
    ~MonsterLogic();
    
};

#endif /* MonsterLogic_hpp */
