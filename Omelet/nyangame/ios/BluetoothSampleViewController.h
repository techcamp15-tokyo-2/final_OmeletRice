//
//  BluetoothSampleViewController.h
//  BluetoothSample
//
//  Created by Hiroshi Hashiguchi on 10/12/14.
//  Copyright 2010 . All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

#define PARAM 0
#define NAME 1
#define SKILL 2
#define HP 3
#define ATK 4
#define DEF 5
#define SPD 6

@interface BluetoothSampleViewController : UIViewController <GKPeerPickerControllerDelegate, GKSessionDelegate, UIImagePickerControllerDelegate,UIActionSheetDelegate, UINavigationControllerDelegate>{

	GKSession* session_;
	NSString* peearID_;
	
	UILabel* message_;

	UITextView* textView_;
	UITextField* sendText_;
	
	UIImageView* imageView_;
    
    BOOL connected;
}

@property (nonatomic, retain) GKSession* session;
@property (nonatomic, retain) NSString* peerID;

@property (nonatomic, retain) IBOutlet UILabel* message;

@property (nonatomic, retain) IBOutlet UITextView* textView;
@property (nonatomic, retain) IBOutlet UITextField* sendText;
@property (nonatomic, retain) IBOutlet UIImageView* imageView;

- (void)button_Tapped;
- (void)connect;
- (IBAction)sendText:(id)sender;
- (IBAction)sendPhoto:(id)sender;

- (void)initFmdb;




@end

