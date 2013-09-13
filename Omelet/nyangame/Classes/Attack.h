//
//  Attack.h
//  nyangame
//
//  Created by Sacchy on 2013/09/05.
//
//

#ifndef __nyangame__Attack__
#define __nyangame__Attack__

#define PNG_ATTACK_ONE "atk1.png"
#define PNG_ATTACK_TWO "atk2.png"
#define PNG_ATTACK_THREE "atk3.png"

#define PNG_SKILL_DEF "smog0.png"
#define PNG_DEF "shield.png"

#define PNG_SKILL_STAR_ONE "star0.png"
#define PNG_SKILL_ICESPEAR_ONE "iceSpear0.png"
#define PNG_SKILL_THUNDER_ONE "thunder0.png"

#define PNG_EFFECT_HOSI "hosi0.png"
#define PNG_EFFECT_POWER "power0.png"

#include "cocos2d.h"

class Attack : public cocos2d::CCLayer
{
public:
/*    Attack();
    virtual ~Attack();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Attack);
    
    void showInitialAttack(int index, float x, float y);
    static Attack* createWithNothing();*/
    static cocos2d::CCAnimation* createWithAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithDefAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithStarAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithIceSpearAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithThunderAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithHosiAnimation(int index, float x, float y);
    static cocos2d::CCAnimation* createWithPowerAnimation(int index, float x, float y);
};

#endif /* defined(__nyangame__Attack__) */
