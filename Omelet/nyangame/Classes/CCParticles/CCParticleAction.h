//
//  CCParticleAction.h
//  particleAction
//
//  Created by 上松 友規 on 2013/06/20.
//
//  MIT License
//

#ifndef __particleAction__CCParticleAction__
#define __particleAction__CCParticleAction__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;


//パーティクルの放出を止めるアクションです
class CC_DLL CCParticleStop : public CCActionInterval
{
public:
    static CCParticleStop* create();
    bool initWithDuration();
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
};

//パーティクルをリセットして、放出を再開するアクションです
class CC_DLL CCParticleReset : public CCActionInterval
{
public:
    static CCParticleReset* create();
    bool initWithDuration();
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
};

//パーティクルを移動させるアクションです
class CC_DLL CCParticleSrcPosTo : public CCActionInterval
{
public:
    static CCParticleSrcPosTo* create( float duration, const CCPoint& position );
    bool initWithDuration( float duration, const CCPoint& position );
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
protected:  
    CCPoint m_endPosition;
    CCPoint m_startPosition;
    CCPoint m_delta;
};

#endif