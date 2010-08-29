//
//  CloudAppUploadTask.h
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "ASIHTTPRequestDelegate.h"
#import "ASIProgressDelegate.h"

@class ASIHTTPRequest;
@class ASIFormDataRequest;

@interface CloudAppUploadTask : RMUploadTask <ASIHTTPRequestDelegate, ASIProgressDelegate> {
	
	RMUploadPreset *_destination;
	id _uploadInfo;
	
	ASIHTTPRequest *_cloudRequest;
	ASIFormDataRequest *_s3Request;
}

@end
