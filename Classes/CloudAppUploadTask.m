//
//  CloudAppUploadTask.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppUploadTask.h"
#import "CloudAppCredentials.h"
#import "ASIFormDataRequest.h"
#import "JSON.h"

@interface CloudAppUploadTask (PrivateMethods)
- (void)_cancelRequest:(ASIHTTPRequest *)aRequest;
- (void)_failWithError:(NSError *)error;
- (void)_postCompletionNotification;
@end


@implementation CloudAppUploadTask

#pragma mark NSObject

- (void)dealloc {
	[self _cancelRequest:_cloudRequest];
	[self _cancelRequest:_s3Request];
	[_destination release];
	[_uploadInfo release];
	[super dealloc];
}


#pragma mark RMUploadTask

- (id)initWithPreset:(RMUploadPreset *)destination uploadInfo:(id)uploadInfo {	
	if ((self = [super init])) {
		_destination = [destination retain];
		_uploadInfo = [uploadInfo retain];
	}
	return self;
}


- (void)upload {
	NSString *digest = [(CloudAppCredentials *)[_destination authentication] digest];
	
	[self _cancelRequest:_cloudRequest];

	_cloudRequest = [[ASIHTTPRequest alloc] initWithURL:[NSURL URLWithString:@"http://my.cl.ly/items/new"]];
	_cloudRequest.delegate = self;
	[_cloudRequest addRequestHeader:@"Authentication" value:[NSString stringWithFormat:@"Basic %@", digest]];\
	[_cloudRequest addRequestHeader:@"Accept" value:@"application/json"];
	[_cloudRequest startAsynchronous];
}


- (void)cancel {
	[super cancel];
	
	[self _cancelRequest:_cloudRequest];
	_cloudRequest = nil;
	
	[self _cancelRequest:_s3Request];
	_s3Request = nil;
	
	[self _postCompletionNotification];
}


#pragma mark Private Methods

- (void)_cancelRequest:(ASIHTTPRequest *)aRequest {
	aRequest.delegate = nil;
	[aRequest cancel];
	[aRequest release];
}


- (void)_failWithError:(NSError *)error {
	NSDictionary *notificationInfo = [NSDictionary dictionaryWithObjectsAndKeys:
									  error, RMUploadTaskErrorKey,
									  nil];
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self userInfo:notificationInfo];
}


- (void)_postCompletionNotification {
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self];
}


#pragma mark ASIHTTPRequestDelegate

- (void)requestFinished:(ASIHTTPRequest *)request {
	// Getting upload data finished
	if (request == _cloudRequest) {
		if ([_cloudRequest responseStatusCode] != 200) {
			NSDictionary *errorInfo = [NSDictionary dictionaryWithObjectsAndKeys:
									   @"Something went wrong. Boo.", NSLocalizedDescriptionKey,
									   nil];
			NSError *error = [NSError errorWithDomain:CloudAppBundleIdentifier code:0 userInfo:errorInfo];			
			[self _failWithError:error];
		}
		
		NSDictionary *s3Info = [[_cloudRequest responseString] JSONValue];
		NSLog(@"S3 info: %@", s3Info);
		
		// Clean up
		[self _cancelRequest:_cloudRequest];
		_cloudRequest = nil;
	}
	
	// Upload to S3 finished
	else {
		// Clean up
		[self _cancelRequest:_s3Request];
		_s3Request = nil;
	}
	
	[self _postCompletionNotification];
}


- (void)requestFailed:(ASIHTTPRequest *)request {
	[self _failWithError:[request error]];
//	[self _cancelRequest:request];
}

@end
