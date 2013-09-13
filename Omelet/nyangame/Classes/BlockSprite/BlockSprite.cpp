//
//  BlockSprite.cpp
//  nyangame
//
//  Created by Sacchy on 2013/08/15.
//
//

#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
    initNextPos();
}

BlockSprite::~BlockSprite()
{
    
}

BlockSprite* BlockSprite::createWithBlockType(kBlock blockType)
{
    BlockSprite *pRet = new BlockSprite();

    if (pRet && pRet->initWithBlockType(blockType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BlockSprite::initWithBlockType(kBlock blockType)
{
    if (!CCSprite::initWithFile(getBlockImageFileName(blockType)))
    {
        return false;
    }
    
    m_blockType = blockType;
    
    return true;
}

const char* BlockSprite::getBlockImageFileName(kBlock blockType)
{
    switch (blockType)
    {
        case kBlockAttack:
            return PNG_ATTACK_PUZZLE;
        case kBlockDeffence:
            return PNG_DEFFENCE_PUZZLE;
        case kBlockDummy:
            return PNG_DUMMY_PUZZLE;
        case kBlockSkillOne:
            return PNG_SKILLONE_PUZZLE;
        case kBlockSkillTwo:
            return PNG_SKILLTWO_PUZZLE;
        default:
            CCAssert(false, "invalid blockType");
            return "";
    }
}

// 移動先の初期化
void BlockSprite::initNextPos()
{
    m_nextPosX = -1;
    m_nextPosY = -1;
}

// 移動先インデックスをセット
void BlockSprite::setNextPos(int nextPosX, int nextPosY)
{
    m_nextPosX = nextPosX;
    m_nextPosY = nextPosY;
}