//
//  CCPlaySE.cpp
//  nyangame
//
//  Created by Sacchy on 2013/08/14.
//
//

#include "CCPlaySE.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCPlaySE::CCPlaySE(std::string sound)
{
    m_sound = sound;
}

CCPlaySE* create(std::string sound)
{
    CCPlaySE* pRet = new CCPlaySE(sound);

    if (pRet)
    {
        pRet->autorelease();
    }
    
    return pRet;
}

void CCPlaySE::update(float time)
{
    CC_UNUSED_PARAM(time);
    SimpleAudioEngine::sharedEngine()->playEffect(m_sound.c_str());
}

#if 0
CCFiniteTimeAction* CCPlaySE::reverse(void)
{
    return (CCFiniteTimeAction*)(CCPlaySE::create(m_sound));
}
#endif

CCObject* CCPlaySE::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCPlaySE* pRet = NULL;
    
    if (pZone && pZone->m_pCopyObject)
    {
        pRet = (CCPlaySE*) (pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCPlaySE(m_sound);
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}