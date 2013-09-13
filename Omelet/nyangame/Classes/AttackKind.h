//
//  AttackKind.h
//  nyangame
//
//  Created by Sacchy on 2013/09/06.
//
//

#ifndef __nyangame__AttackKind__
#define __nyangame__AttackKind__


#include "cocos2d.h"

class AttackKind : public cocos2d::CCLayer
{
public:
    static cocos2d::CCSprite* createWithSprite(int kind, int index);
};

#endif /* defined(__nyangame__AttackKind__) */
