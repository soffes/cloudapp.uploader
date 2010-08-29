//
//  CloudAppCredentials.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppCredentials.h"

NSString *const CloudAppCredentialsUsernameKey = @"username";
NSString *const CloudAppCredentialsDigestKey = @"digest";

@implementation CloudAppCredentials

@synthesize username;
@synthesize digest;

+ (NSSet *)_propertyKeys {
	return [NSSet setWithObjects:
			CloudAppCredentialsUsernameKey,
			CloudAppCredentialsDigestKey,
			nil];
}


+ (NSSet *)keyPathsForValuesAffectingValueForKey:(NSString *)key {
	NSMutableSet *keyPaths = [[super keyPathsForValuesAffectingValueForKey:key] mutableCopy];
	
	if ([key isEqualToString:RMUploadCredentialsDirtyKey]) {
		[keyPaths unionSet:[NSSet setWithObjects:
							CloudAppCredentialsUsernameKey,
							CloudAppCredentialsDigestKey,
							nil]];
	}
	
	if ([key isEqualToString:RMUploadCredentialsUserIdentifierKey]) {
		[keyPaths addObject:CloudAppCredentialsUsernameKey];
	}
	
	return keyPaths;
}


- (id)initWithPropertyListRepresentation:(id)values {
	if ((self = [super initWithPropertyListRepresentation:[values objectForKey:@"super"]])) {
		if ([values valueForKey:CloudAppCredentialsUsernameKey] != nil) {
			self.username = [values valueForKey:CloudAppCredentialsUsernameKey];
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
	
	if (self.username != nil) {
		[plist setObject:self.username forKey:CloudAppCredentialsUsernameKey];
	}
	
	if (self.digest != nil) {
		[plist setObject:self.digest forKey:CloudAppCredentialsDigestKey];
	}
	
	return plist;
}


- (NSString *)userIdentifier {
	return self.username;
}

@end
