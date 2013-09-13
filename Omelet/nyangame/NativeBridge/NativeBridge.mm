//
//  NativeBridge.mm
//  gamefeat-Cocos2dX
//
//  Created by Sacchy on 2013/08/23.
//

#include "NativeBridge.h"
#include "NativeBridge_objc.h"

static void static_showBlueTooth()
{
    [NativeBridge showBlueTooth];
}

static void static_sendDataBlueTooth()
{
    [NativeBridge sendDataBlueTooth];
}

static void static_showCamera()
{
    [NativeBridge showCamera];
}

namespace Cocos2dExt
{
    void NativeBridge::showBlueTooth()
    {
        static_showBlueTooth();
    }
    
    void NativeBridge::sendDataBlueTooth()
    {
        static_sendDataBlueTooth();
    }
    
    void NativeBridge::showCamera()
    {
        static_showCamera();
    }
}