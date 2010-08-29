//
//  CloudAppUploadTask.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppUploadTask.h"

@implementation CloudAppUploadTask

- (id)initWithPreset:(RMUploadPreset *)destination uploadInfo:(id)uploadInfo {	
	if ((self = [super init])) {
		// Note: store whatever you need from the destination and uploadInfo to be retrieved when uploading.
	}
	return self;
}


- (void)upload {
	
}


- (void)cancel {
	[super cancel];	
	[[NSNotificationCenter defaultCenter] postNotificationName:RMUploadTaskDidCompleteNotificationName object:self];
}

@end
