//
//  ViewController.h
//  Camera
//
//  Created by 顔班Mac on 13/09/05.
//  Copyright (c) 2013年 顔班Mac. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CameraViewController : UIViewController<UIActionSheetDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate>
{
    UILabel *label;
    NSMutableDictionary* Status; 
}

- (void)showActionSheet;
- (void)endAnimation;
@end
