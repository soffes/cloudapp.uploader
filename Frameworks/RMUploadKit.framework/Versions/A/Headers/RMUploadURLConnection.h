//***************************************************************************

// Copyright (C) 2009 Realmac Software Ltd
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information of Realmac Software Ltd
// and are protected by copyright law. They may not be disclosed
// to third parties or copied or duplicated in any form, in whole or
// in part, without the prior written consent of Realmac Software Ltd.

// Created by Danny Greg on 24/7/2009 

//***************************************************************************

#import <Cocoa/Cocoa.h>

//***************************************************************************

typedef void (^RMUploadURLConnectionCompletionBlock)(NSData *responseData, NSError *responseError);

//***************************************************************************

@protocol RMUploadURLConnectionDelegate;

/**
	@brief A replacement of NSURLConnection, wrapping it with a different API. 
 
	It uses a similar delegate system as NSURLConnection but provides different information as you go.
*/

@interface RMUploadURLConnection : NSObject

/**
	The connection's delegate.
 */
@property (assign) id delegate;

/**
	@brief A block called when the connection completes, either successfully or unsuccessfully
 */
@property (copy) RMUploadURLConnectionCompletionBlock completionBlock;

/*!
	@brief YES when all data has been received back from the server
 */
@property (readonly) BOOL completed;

/**
	@brief A slot to store any context info required, handy for delegate callbacks.
 */
@property (retain) id userInfo;

/**
	@brief A convenience constructor that initialises with an NSURLRequest and sends the request immediately.
*/
+ (RMUploadURLConnection *)connectionWithRequest:(NSURLRequest *)request delegate:(id <RMUploadURLConnectionDelegate>)delegate;

/**
	@brief A simple convenience constructor.
*/
+ (RMUploadURLConnection *)connectionWithRequest:(NSURLRequest *)request completionBlock:(RMUploadURLConnectionCompletionBlock)completionBlock;

/**
	@brief Builds a GET URL from the URL and paramaters provided and then sends the request.
 
	@param params An NSDictionary expecting key/value pairs of strings, where each key/value pair is for a key in the API that you are sending to.
	@param url The base URL for the request.
*/
- (void)sendGetRequestWithParameters:(NSDictionary *)params toURL:(NSURL *)url;

/**
	@brief If you are using a POST request to send a file then this is a helpful option.
 
	You build up an array of dictionaries containing the keys described below to describe the data sent for each field in the request.
 
	@param params An array of dictionaries using the <code>RMPOSTFilenameKey</code>, <code>RMPOSTDataKey</code> and <code>RMPOSTFieldNameKey</code> keys. 
	@param url The base URL for the request.
*/
- (void)sendFilePostRequestWithParameters:(NSArray *)params toURL:(NSURL *)url;

/** 
	@brief Sends a POST request with the same API as a GET request.
 
	Useful for simple POST requests that do not require files.
 
	@param params An NSDictionary expecting key/value pairs, where each key/value pair is for a key in the API that you are sending to. Unlike GET requests the value does not have to be a string but can be any type of data that POST requests store in <code>RMPOSTDataKey</code>s.
	@param url The base URL for the request.
 */
- (void)sendPostRequestWithParameters:(NSDictionary *)params toURL:(NSURL *)url;

/**
	@brief Sends the provided request and starts delegate notifications.
 
	@param request The NSURLRequest that you wish to send.
*/
- (void)sendURLRequest:(NSURLRequest *)request;

/**
	@brief Cancels any transferrs.
 
	The delegate will not receive any more messages.
*/
- (void)cancel;

@end

/**
	@brief The delegate for RMURLConnection.
*/

@protocol RMUploadURLConnectionDelegate <NSObject>

 @optional

/**
	@brief This is called periodically as the download progresses.
	
	@param connection The RMURLConnection that is sending the message.
	@param currentProgress A value between 0.0 and 1.0.
 */
- (void)connection:(RMUploadURLConnection *)connection downloadProgressed:(float)currentProgress;

/**
	@brief This is called periodically as the upload progresses.
	
	@param connection The RMURLConnection that is sending the message.
	@param currentProgress A value between 0.0 and 1.0.
 */
- (void)connection:(RMUploadURLConnection *)connection uploadProgressed:(float)currentProgress;

 @required

/**
	@brief Called if a connection fails, providing an NSError with the cause.
	
	@param connection The RMURLConnection that is sending the message.
	@param error An NSError object representing the error that caused the connection to fail.
 */
- (void)connection:(RMUploadURLConnection *)connection didFailWithError:(NSError *)error;

/**
	@brief This is called periodically as the upload progresses.
	
	@param connection The RMURLConnection that is sending the message.
	@param data The data returned by the server after sending the connection's request.
 */
- (void)connection:(RMUploadURLConnection *)connection didCompleteWithData:(NSData *)data;

 @optional

/**
	@brief Behaves identically to the NSURLConnection delegate equivalent.
 */
- (void)connection:(RMUploadURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/** 
	@brief Behaves identically to the NSURLConnection delegate equivalent.
 */
- (void)connection:(RMUploadURLConnection *)connection didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@end
