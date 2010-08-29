//***************************************************************************

// Copyright (C) 2009 Realmac Software Ltd
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information of Realmac Software Ltd
// and are protected by copyright law. They may not be disclosed
// to third parties or copied or duplicated in any form, in whole or
// in part, without the prior written consent of Realmac Software Ltd.

// Created by Danny Greg on 06/08/2010. 

//***************************************************************************

#import <Cocoa/Cocoa.h>

//***************************************************************************

/**
 @brief The key used in the params dictionary of a POST request for the filename. 
 
 This can be absent if the paramater is not file data,
 */
extern NSString *const RMPOSTFilenameKey;

/** 
 @brief The key used in the params dictionary of a POST request for the data itself.
 
 This must not be nil or absent from the params dictionary. The value itself can be either NSData, NSString, NSURL or NSNumber in type.
 */
extern NSString *const RMPOSTDataKey;

/**
 @brief The key used in the params dictionary of a POST request for the field name.
 
 This must not be nil or absent from the params dictionary.
 */
extern NSString *const RMPOSTFieldNameKey;

/** 
 @brief Used to specify a "Content-Type" in a POST request/
 
 This is only checked for if the same paramater has an RMPOSTFilenameKey.
 */
extern NSString *const RMPOSTContentTypeKey;

//***************************************************************************

@interface NSURLRequest (RMUploadAdditions)

+ (NSURLRequest *)getRequestWithParameters:(NSDictionary *)params toURL:(NSURL *)url;
+ (NSURLRequest *)postRequestWithParameters:(NSDictionary *)params toURL:(NSURL *)url;
+ (NSURLRequest *)filePostRequestWithParameters:(NSArray *)params toURL:(NSURL *)url;

@end
