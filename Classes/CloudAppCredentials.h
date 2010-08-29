//
//  CloudAppCredentials.h
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

@interface CloudAppCredentials : RMUploadCredentials

@property (copy) NSString *email;
@property (copy) NSString *digest;

@end
