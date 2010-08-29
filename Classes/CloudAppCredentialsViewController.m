//
//  CloudAppCredentialsViewController.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppCredentialsViewController.h"
#import "CloudAppCredentials.h"

@interface CloudAppCredentialsViewController ()
@property (readwrite, assign, getter=isAuthenticating) BOOL authenticating;
@end

@implementation CloudAppCredentialsViewController

@dynamic representedObject;
@synthesize loginUsernameField;
@synthesize loginPasswordField;
@synthesize authenticating = _authenticating;

- (id)init {
	if ((self = [super initWithNibName:@"CredentialsView" bundle:[NSBundle bundleWithIdentifier:CloudAppBundleIdentifier]])) {
		
	}
	return self;
}


- (IBAction)nextStage:(id)sender {
	BOOL (^validateTextField)(NSTextField *) = ^ (NSTextField *field) {
		[field validateEditing];
		if ([field stringValue] != nil && [[field stringValue] length] > 0) return YES;
		
//		[self highlightErrorInView:field];
		
		NSDictionary *validationNotificationInfo = [NSDictionary dictionaryWithObjectsAndKeys:
													[NSError errorWithDomain:RMUploadKitBundleIdentifier code:RMUploadPresetConfigurationViewControllerErrorValidation userInfo:nil], RMUploadPresetConfigurationViewControllerDidCompleteErrorKey,
													nil];
		[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadPresetConfigurationViewControllerDidCompleteNotificationName object:self userInfo:validationNotificationInfo];
		
		return NO;
	};
	if (!validateTextField([self loginUsernameField])) return;
	if (!validateTextField([self loginPasswordField])) return;
	
	
	// Add `Accept: application/json`
//	RMEmberContext *context = [RMUploaderEmber newContextWithCredentials:nil];
//	[self setLoginConnection:[RMUploadURLConnection connectionWithRequest:[context requestLoginWithUsername:[[self loginUsernameField] stringValue] password:[[self loginPasswordField] stringValue]] delegate:self]];
	
	[self setAuthenticating:YES];
}

@end
