//
//  CloudAppPreset.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppPreset.h"
#import "CloudAppUploadTask.h"
#import "CloudAppCredentials.h"

@implementation CloudAppPreset

+ (NSString *)localisedName {
	return @"CloudApp";
}


+ (Class)uploadTaskClass {
	return [CloudAppUploadTask class];
}


+ (Class)credentialsClass {
	return [CloudAppCredentials class];
}


- (id)initWithPropertyListRepresentation:(id)values {
	if ((self = [super initWithPropertyListRepresentation:[values objectForKey:@"super"]])) {
		// Note: set any properties from the values container
	}	
	return self;
}


- (id)propertyListRepresentation {
	NSMutableDictionary *plist = [NSMutableDictionary dictionary];
	[plist setObject:[super propertyListRepresentation] forKey:@"super"];
	
	// Note: set any properties into the values container
	
	return plist;
}

@end
