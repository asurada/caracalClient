//
//  GameScene.h
//  legend
//
//  Created by 厳 巍 on 2014/05/17.
//
//

#ifndef __legend__GameScene__
#define __legend__GameScene__

#include "OperationCallback.h"
#include "OperationLayer.h"
#include "BaseFighter.h"
#include "FighterCallback.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Char_01.h"
#include "Enm_01.h"


class GameScene : public cocos2d::CCLayer,OperationCallback,b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    GameScene();
    ~GameScene();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    void startFireAnm(cocos2d::Point &pos,const char * image,const char * plist,const char * imgSplit,int count);
    void cleanupSprite(cocos2d::Sprite* inSprite);
    void addRectangleBetweenPointsToBody(b2Body *body, Point start, Point end);
    
   // void fire(const char *pszFileName);
    void monsterAttack();
    void update(float dt);
    void backgroundRun();
    void onDraw();
    
    virtual void onTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
	virtual void onTouchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
	virtual void onTouchesBegan(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void onTouchesCancelled(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void beginFire(AnalysisShape shape);
    virtual void endFire(AnalysisShape shape);
    void onFire(bulletType _type);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
    
private:
    b2World* world;
	b2Body* currentPlatformBody;
    cocos2d::Point center;
    cocos2d::Point monster;
    cocos2d::Sprite* bullet;
    cocos2d::Sprite* pSprite_round;
    Enm_01* pSprite_monster;
    Char_01* pSprite_char;
    cocos2d::Sprite* pSprite_bg_1;
    cocos2d::Sprite* pSprite_bg_2;
    cocos2d::Sprite* emptyNode;
    cocos2d::Array *touchBallArray;
    std::vector<cocos2d::Point> autoPoints;
    OperationLayer *operationlayer;

    void initPhysics();
    cocos2d::Sprite* animationSprite;
    Bullet *bullets;
};
#endif /* defined(__legend__GameScene__) */
