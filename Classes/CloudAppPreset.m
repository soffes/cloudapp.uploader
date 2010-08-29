//
//  CloudAppPreset.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppPreset.h"
#import "CloudAppUploadTask.h"

@implementation CloudAppPreset

+ (NSString *)localisedName {
	return @"CloudApp";
}


+ (Class)uploadTaskClass {
	return [CloudAppUploadTask class];
}


//+ (Class)credentialsClass {
//	return [CloudAppCredentials class];
//}


- (id)initWithPropertyListRepresentation:(id)values {
	id superRepresentation = [values objectForKey:@"super"];
	self = [super initWithPropertyListRepresentation:superRepresentation];
	if (self == nil) return nil;
	
	// Note: set any properties from the values container
	
	return self;
}


- (id)propertyListRepresentation {
	id superRepresentation = [super propertyListRepresentation];
	
	NSMutableDictionary *plist = [NSMutableDictionary dictionary];
	[plist setObject:superRepresentation forKey:@"super"];
	
	// Note: set any properties into the values container
	
	return plist;
}

@end
