//
//  CCParticleAction.cpp
//  particleAction
//
//  Created by 上松 友規 on 2013/06/20.
//
//

#include "CCParticleAction.h"

//
// CCParticleStop
//

CCParticleStop* CCParticleStop::create()
{
    CCParticleStop* pParticleStop = new CCParticleStop();
    pParticleStop->initWithDuration();
    pParticleStop->autorelease();
    
    return pParticleStop;
}

bool CCParticleStop::initWithDuration()
{
    if (CCActionInterval::initWithDuration(0.0f))
    {
        
        return true;
    }
    
    return false;
}


CCObject* CCParticleStop::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParticleStop* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParticleStop*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCParticleStop();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration();
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParticleStop::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
}

void CCParticleStop::update(float time)
{
    if (m_pTarget)
    {
        ((CCParticleSystem*)m_pTarget)->stopSystem();
    }
}

//
// CCParticleReset
//

CCParticleReset* CCParticleReset::create()
{
    CCParticleReset* instance = new CCParticleReset();
    instance->initWithDuration();
    instance->autorelease();
    
    return instance;
}

bool CCParticleReset::initWithDuration()
{
    if (CCActionInterval::initWithDuration(0.0f))
    {
        
        return true;
    }
    
    return false;
}


CCObject* CCParticleReset::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParticleReset* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParticleReset*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCParticleReset();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration();
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParticleReset::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
}

void CCParticleReset::update(float time)
{
    if (m_pTarget)
    {
        ((CCParticleSystem*)m_pTarget)->resetSystem();
    }
}


//
// CCParticleSrcPosTo
//

CCParticleSrcPosTo* CCParticleSrcPosTo::create( float duration, const CCPoint& position )
{
    CCParticleSrcPosTo* instance = new CCParticleSrcPosTo();
    instance->initWithDuration( duration, position );
    instance->autorelease();
    
    return instance;
}

bool CCParticleSrcPosTo::initWithDuration( float duration, const CCPoint& position )
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_endPosition = position;
        return true;
    }
    
    return false;
}


CCObject* CCParticleSrcPosTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParticleSrcPosTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParticleSrcPosTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCParticleSrcPosTo();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration( m_fDuration, m_endPosition );
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParticleSrcPosTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_startPosition = ((CCParticleSystemQuad*)pTarget)->getSourcePosition();
    m_delta = ccpSub(m_endPosition, m_startPosition);
}

void CCParticleSrcPosTo::update(float time)
{
    if (m_pTarget)
    {
        ((CCParticleSystemQuad*)m_pTarget)->setSourcePosition(ccp(m_startPosition.x + m_delta.x * time,
                                   m_startPosition.y + m_delta.y * time));
    }
}