//
//  NativeBridge.h
//  gamefeat-Cocos2dX
//
//  Created by Sacchy on 2013/08/23.
//

#ifndef _BROWSER_LAUNCHER_H_
#define _BROWSER_LAUNCHER_H_

#include <stddef.h>

namespace Cocos2dExt {
    
    class NativeBridge
    {
    public:
        static void showBlueTooth();
        static void sendDataBlueTooth();
        static void showCamera();
    };
    
} // end of namespace Cocos2dExt

#endif // _BROWSER_LAUNCHER_H_
