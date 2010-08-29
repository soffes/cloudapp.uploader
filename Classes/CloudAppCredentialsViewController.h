//
//  CloudAppCredentialsViewController.h
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "ASIHTTPRequestDelegate.h"

@class CloudAppCredentials;
@class ASIHTTPRequest;

@interface CloudAppCredentialsViewController : RMUploadPresetConfigurationViewController <ASIHTTPRequestDelegate> {

	ASIHTTPRequest *_request;
}

@property (retain) CloudAppCredentials *representedObject;

@property (readonly) IBOutlet NSTextField *loginEmailField;
@property (readonly) IBOutlet NSTextField *loginPasswordField;

@property (readonly, assign, getter=isAuthenticating) BOOL authenticating;

- (IBAction)nextStage:(id)sender;

@end
