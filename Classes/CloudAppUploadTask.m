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
@end


@implementation CloudAppUploadTask

#pragma mark NSObject

- (void)dealloc {
	// TODO: uncomment these once we're sure we aren't causing bad access
//	[self _cancelRequest:_cloudRequest];
//	[self _cancelRequest:_s3Request];
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
	NSLog(@"[CloudApp.uploader] Start upload");
	
	[self _cancelRequest:_cloudRequest];

	_cloudRequest = [[ASIHTTPRequest alloc] initWithURL:[NSURL URLWithString:@"http://my.cl.ly/items/new"]];
	_cloudRequest.delegate = self;
	[_cloudRequest addRequestHeader:@"Accept" value:@"application/json"];
	[_cloudRequest startAsynchronous];
}


- (void)cancel {
	[super cancel];
	
	[self _cancelRequest:_cloudRequest];
	_cloudRequest = nil;
	
	[self _cancelRequest:_s3Request];
	_s3Request = nil;
	
	// TODO: Show canceled
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self];
}


#pragma mark Private Methods

- (void)_cancelRequest:(ASIHTTPRequest *)aRequest {
	aRequest.delegate = nil;
	aRequest.uploadProgressDelegate = nil;
	[aRequest cancel];
	[aRequest release];
}


- (void)_failWithError:(NSError *)error {
	NSDictionary *notificationInfo = [NSDictionary dictionaryWithObjectsAndKeys:
									  error, RMUploadTaskErrorKey,
									  nil];
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self userInfo:notificationInfo];
}


#pragma mark ASIHTTPRequestDelegate

- (void)authenticationNeededForRequest:(ASIHTTPRequest *)request {
	if ([request authenticationRetryCount] == 0) {
		CloudAppCredentials *credentials = (CloudAppCredentials *)[_destination authentication];
		[request applyCredentials:[NSDictionary dictionaryWithObjectsAndKeys:credentials.email, kCFHTTPAuthenticationUsername, credentials.password, kCFHTTPAuthenticationPassword, nil]];
		[request retryUsingSuppliedCredentials];
	} else {
		[request cancelAuthentication];
	}
}


- (void)requestFinished:(ASIHTTPRequest *)request {
	NSLog(@"[CloudApp.uploader] request finished: %@", request);
	
	// Getting upload data finished
	if (request == _cloudRequest) {
		if ([_cloudRequest responseStatusCode] != 200) {
			NSDictionary *errorInfo = [NSDictionary dictionaryWithObjectsAndKeys:
									   @"Something went wrong. Boo.", NSLocalizedDescriptionKey,
									   nil];
			NSError *error = [NSError errorWithDomain:CloudAppBundleIdentifier code:0 userInfo:errorInfo];			
			[self _failWithError:error];
		}
		
		// S3 Data
		NSDictionary *s3Info = [[_cloudRequest responseString] JSONValue];
		NSDictionary *params = [s3Info objectForKey:@"params"];
		
		// Clean up
		[self _cancelRequest:_cloudRequest];
		_cloudRequest = nil;
		
		// Start S3 request
		_s3Request = [[ASIFormDataRequest alloc] initWithURL:[NSURL URLWithString:[s3Info objectForKey:@"url"]]];
		_s3Request.delegate = self;
		_s3Request.uploadProgressDelegate = self;
		_s3Request.shouldRedirect = YES;
		for (NSString *param in params) {
			[_s3Request setPostValue:[params objectForKey:param] forKey:param];
		}
		NSString *filePath = [(NSURL *)[_uploadInfo valueForKey:RMUploadFileURLKey] path];
		[_s3Request addFile:filePath forKey:@"file"];
		[_s3Request addRequestHeader:@"Accept" value:@"application/json"];
		
		[_s3Request startAsynchronous];
	}
	
	// Upload to S3 finished
	else {
		NSLog(@"[CloudApp.uploader] Complete: %@", [_s3Request responseString]);
		NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:
								  [NSURL URLWithString:@"http://google.com"], RMUploadTaskResourceLocationKey,
								  nil];
		[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidFinishTransactionNotificationName object:self userInfo:userInfo];
		
		// Clean up
		[self _cancelRequest:_s3Request];
		_s3Request = nil;
		
		// Finish
		[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self];
	}
}


- (void)requestFailed:(ASIHTTPRequest *)request {
	NSLog(@"[CloudApp.uploader] request failed: %@", [request error]);
	[self _failWithError:[request error]];
}


#pragma mark ASIProgressDelegate

// TODO: Fix this. Ugh.

//- (void)setDoubleValue:(double)newProgress {
//	NSLog(@"[CloudApp.uploader] setting progress: %f", newProgress);
//	NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:
//							  [NSNumber numberWithDouble:newProgress], RMUploadTaskProgressCurrentKey,
//							  [NSNumber numberWithDouble:1.0], RMUploadTaskProgressTotalKey,
//							  nil];
//	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidReceiveProgressNotificationName object:self userInfo:userInfo];
//	NSLog(@"[CloudApp] set progress: %f", newProgress);
//}

@end
