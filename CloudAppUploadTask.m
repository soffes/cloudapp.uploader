//
//  CloudAppUploadTask.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppUploadTask.h"

#import "CloudAppConstants.h"

@implementation CloudAppUploadTask

- (id)initWithPreset:(RMUploadPreset *)destination uploadInfo:(id)uploadInfo
{	
	self = [super init];
	if (self == nil) return nil;
	
	// Note: store whatever you need from the destination and uploadInfo to be retrieved when uploading.
	
	return self;
}

- (void)upload
{
	
}

- (void)cancel
{
	[super cancel];
	
	[[NSNotificationCenter notificationCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self];
}

@end
