//
//  CloudAppCredentialsViewController.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppCredentialsViewController.h"
#import "CloudAppCredentials.h"
#import "ASIHTTPRequest.h"

@interface CloudAppCredentialsViewController ()
@property (readwrite, assign, getter=isAuthenticating) BOOL authenticating;
- (void)_cancelRequest;
- (void)_failWithError:(NSError *)error;
@end

@interface CloudAppCredentialsViewController (RequestDelegate) <ASIHTTPRequestDelegate>
@end

@implementation CloudAppCredentialsViewController

@dynamic representedObject;
@synthesize loginUsernameField;
@synthesize loginPasswordField;
@synthesize authenticating = _authenticating;

#pragma mark NSObject

- (id)init {
	if ((self = [super initWithNibName:@"CredentialsView" bundle:[NSBundle bundleWithIdentifier:CloudAppBundleIdentifier]])) {
		
	}
	return self;
}


- (void)dealloc {
	[self _cancelRequest];	
	[super dealloc];
}


#pragma mark Actions

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
	
	[self _cancelRequest];
	_request = [[ASIHTTPRequest alloc] initWithURL:[NSURL URLWithString:@"http://my.cl.ly/items"]];
	[_request addRequestHeader:@"Accept" value:@"application/json"];
	[_request addBasicAuthenticationHeaderWithUsername:[[self loginUsernameField] stringValue] andPassword:[[self loginPasswordField] stringValue]];
	_request.delegate = self;
	[_request startAsynchronous];
	
	[self setAuthenticating:YES];
}


#pragma mark Private Methods

- (void)_cancelRequest {
	[self setAuthenticating:NO];
	_request.delegate = nil;
	[_request cancel];
	[_request release];
	_request = nil;
}


- (void)_failWithError:(NSError *)error {
	NSDictionary *notificationInfo = [NSDictionary dictionaryWithObjectsAndKeys:
									  error, RMUploadPresetConfigurationViewControllerDidCompleteErrorKey,
									  nil];
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadPresetConfigurationViewControllerDidCompleteNotificationName object:self userInfo:notificationInfo];
}

@end


@implementation CloudAppCredentialsViewController (RequestDelegate)

- (void)requestReceivedResponseHeaders:(ASIHTTPRequest *)request {
	if ([request responseStatusCode] != 200) {
		NSDictionary *errorInfo = [NSDictionary dictionaryWithObjectsAndKeys:
								   @"Invalid username and password", NSLocalizedDescriptionKey,
								   nil];
		NSError *error = [NSError errorWithDomain:CloudAppBundleIdentifier code:0 userInfo:errorInfo];
		
		[self _failWithError:error];
		return;
	}
	
	[self.representedObject setUsername:[[self loginUsernameField] stringValue]];
	[self.representedObject setDigest:@"ASDF"];
	
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadPresetConfigurationViewControllerDidCompleteNotificationName object:self];
	[self _cancelRequest];
}


- (void)requestFailed:(ASIHTTPRequest *)request {
	[self _failWithError:[request error]];
	[self _cancelRequest];
}

@end
