//
//  CloudAppCredentials.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppCredentials.h"

NSString *const CloudAppCredentialsEmailKey = @"email";
NSString *const CloudAppCredentialsDigestKey = @"digest";

@implementation CloudAppCredentials

@synthesize email;
@synthesize digest;

+ (NSSet *)_propertyKeys {
	return [NSSet setWithObjects:
			CloudAppCredentialsEmailKey,
			CloudAppCredentialsDigestKey,
			nil];
}


+ (NSSet *)keyPathsForValuesAffectingValueForKey:(NSString *)key {
	NSMutableSet *keyPaths = [[super keyPathsForValuesAffectingValueForKey:key] mutableCopy];
	
	if ([key isEqualToString:RMUploadCredentialsDirtyKey]) {
		[keyPaths unionSet:[NSSet setWithObjects:
							CloudAppCredentialsEmailKey,
							CloudAppCredentialsDigestKey,
							nil]];
	}
	
	if ([key isEqualToString:RMUploadCredentialsUserIdentifierKey]) {
		[keyPaths addObject:CloudAppCredentialsEmailKey];
	}
	
	return keyPaths;
}


- (id)initWithPropertyListRepresentation:(id)values {
	if ((self = [super initWithPropertyListRepresentation:[values objectForKey:@"super"]])) {
		if ([values valueForKey:CloudAppCredentialsEmailKey] != nil) {
			self.email = [values valueForKey:CloudAppCredentialsEmailKey];
		}
	
		if ([values valueForKey:CloudAppCredentialsDigestKey] != nil) {
			self.digest = [values valueForKey:CloudAppCredentialsDigestKey];
		}
	}	
	return self;
}


- (id)propertyListRepresentation {
	NSMutableDictionary *plist = [NSMutableDictionary dictionary];
	[plist setObject:[super propertyListRepresentation] forKey:@"super"];
	
	if (self.email != nil) {
		[plist setObject:self.email forKey:CloudAppCredentialsEmailKey];
	}
	
	if (self.digest != nil) {
		[plist setObject:self.digest forKey:CloudAppCredentialsDigestKey];
	}
	
	return plist;
}


- (NSString *)userIdentifier {
	return self.email;
}

@end
