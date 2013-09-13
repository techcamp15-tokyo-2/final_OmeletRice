//
//  AttackKind.cpp
//  nyangame
//
//  Created by Sacchy on 2013/09/06.
//
//

#include "AttackKind.h"
#include "Config.h"

using namespace cocos2d;
using namespace std;

// エネミーと異なる画像を出すことも可能とした
CCSprite* AttackKind::createWithSprite(int kind, int index)
{
    CCSprite* sprite;
    if (kind == PLAYER)
    {
        switch (index)
        {
            case ATTACK:
                sprite = CCSprite::create(PNG_ATTACK_KIND);
                sprite->setScale(0);
                break;
            case DEFFENCE:
                sprite = CCSprite::create(PNG_DEFFENCE_KIND);
                sprite->setScale(0);
                break;
            case SKILL:
                sprite = CCSprite::create(PNG_SKILL_KIND);
                sprite->setScale(0);
                break;
            case MISS:
                sprite = CCSprite::create(PNG_MISS_KIND);
                sprite->setScale(0);
                break;
            default:
                break;
        }
    }
    else
    {
        switch (index)
        {
            case ATTACK:
                sprite = CCSprite::create(PNG_ATTACK_KIND);
                sprite->setScale(0);
                break;
            case DEFFENCE:
                sprite = CCSprite::create(PNG_DEFFENCE_KIND);
                sprite->setScale(0);
                break;
            case SKILL:
                sprite = CCSprite::create(PNG_SKILL_KIND);
                sprite->setScale(0);
                break;
            case MISS:
                sprite = CCSprite::create(PNG_MISS_KIND);
                sprite->setScale(0);
                break;
            default:
                break;
        }
    }
    return sprite;
}