//
//  HUDLayer.hpp
//  caracalClient
//
//  Created by Yan Wei on 2016/01/07.
//
//

#ifndef HUDLayer_hpp
#define HUDLayer_hpp

#include <stdio.h>
USING_NS_CC;

class HUDLayer : public cocos2d::LayerColor{
    public:
        virtual bool init();
        void DrawHUD();
        void OnMenu(cocos2d::Ref* pSender);
        CREATE_FUNC(HUDLayer);

};

#endif /* HUDLayer_hpp */
