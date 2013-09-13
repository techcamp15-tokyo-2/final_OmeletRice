//
//  BlockSprite.h
//  nyangame
//
//  Created by Sacchy on 2013/08/15.
//
//

#ifndef nyangame_BlockSprite_h
#define nyangame_BlockSprite_h

#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::CCSprite
{
protected:
    const char* getBlockImageFileName(kBlock blockType);
    
public:
    CC_SYNTHESIZE_READONLY(kBlock,m_blockType,BlockType);
    CC_SYNTHESIZE_READONLY(int, m_nextPosX, NextPosX);
    CC_SYNTHESIZE_READONLY(int, m_nextPosY, NextPosY);
    
    void initNextPos();
    void setNextPos(int nextPosX, int nextPosY);
    
    BlockSprite();
    virtual ~BlockSprite();
    virtual bool initWithBlockType(kBlock blockType);
    static BlockSprite* createWithBlockType(kBlock blockType);
};

#endif
