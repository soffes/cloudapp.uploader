//***************************************************************************

// Copyright (C) 2009 Realmac Software Ltd
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information of Realmac Software Ltd
// and are protected by copyright law. They may not be disclosed
// to third parties or copied or duplicated in any form, in whole or
// in part, without the prior written consent of Realmac Software Ltd.

// Created by Danny Greg on 25/3/2009 

//***************************************************************************

#import <Cocoa/Cocoa.h>

@class RMUploadPreset;
@class RMUploadCredentials;

/*!
	@file
 */

/*
	Notifications
 */

/*!
	@brief		This allows you to update the status text outside of the established notification pattern.
	
		The <tt>userInfo</tt> dictionary should contain the <tt>RMUploadTaskStatusInfoKey</tt>
 */
extern NSString *const RMUploadTaskUpdateStatusTextNotificationName;

/*!
    @brief   The upload task should post this this whenever it is updated in its progress. If this is never posted, the framework will assume an indeterminate upload is taking place.
    This notification MUST be posted using the <tt>+[NSNotificationCenter defaultCenter]</tt> object. The object for the notification should be the <tt>RMUploadTask</tt> posting the notification.
				The object for the notification should be the <tt>RMUploadTask</tt> posting the notification.
				The userinfo dictionary should also contain the following keys and values:
					
					<tt>RMUploadTaskProgressTotalKey</tt> : This should remain the same throughout the upload. <tt>[NSNumber numberWithDouble:]</tt>
					<tt>RMUploadTaskProgressCurrentKey</tt> : The amount of progress that has already happened, this can be measured by any unit you like but should be the same as the one used for <tt>RMUploadTaskProgressTotalKey</tt>. <tt>[NSNumber numberWithDouble:]</tt>
*/
extern NSString *const RMUploadTaskDidReceiveProgressNotificationName;

	extern NSString *const RMUploadTaskProgressTotalKey;
	extern NSString *const RMUploadTaskProgressCurrentKey;

/*!
    @brief	The upload task should post this whenever it has finished uploading each object to the target. <em>NOT</em> when it has completed. The object for the notification should be the <tt>RMUploadTask</tt> posting the notification.
			This notification MUST be posted using the <tt>+[NSNotificationCenter defaultCenter]</tt> object. The object for the notification should be the <tt>RMUploadTask</tt> posting the notification.
			
			The userInfo dictionary should also contain the following keys and values:
				<tt>RMUploadTaskResourceLocationKey</tt> : where the data was uploaded to. (<tt>NSURL</tt>).
				<tt>RMUploadTaskErrorKey</tt> : an NSError object, indicating what when wrong with the upload. (<tt>NSError</tt>).
			
			A single task might transfer more than one object, so a task can post many of these.
			You may post this notification to indicate additional errors, such as failure to add a photo to a group or photoset.
*/
extern NSString *const RMUploadTaskDidFinishTransactionNotificationName;

	extern NSString *const RMUploadTaskResourceLocationKey;
	extern NSString *const RMUploadTaskErrorKey;

/*!
    @brief	The upload task should post this once it has at least attempted to perform its operations.
			This will vary from task to task, for instance an example Flickr task will first first attempt to upload the image, if that fails it will post the completion notification including the error. If the upload completed it may then attempt to add the image to a group or photoset, these may fail; but don't indicate that the upload failed completely.
			
			This notification MUST be posted using the <tt>+[NSNotificationCenter defaultCenter]</tt> object. The object for the notification should be the <tt>RMUploadTask</tt> posting the notification.
			This notification doesn't indicate that the task <b>succeeded</b> just that it completed.
			
			This notification must also be posted once you have successfully cancelled.
*/
extern NSString *const RMUploadTaskDidCompleteNotificationName;

/*!
	@brief   This should be an NSString, it can be passed in the userinfo dictionary of <em>any</em> task notification and is displayed in the interface to let the user know what's happening.
	An empty valueForKey: will be ignored, pass +[NSNull null] to clear the previous message.
	The value should be localised.
 */
extern NSString *const RMUploadTaskStatusInfoKey;

/*
	File Constants
 */

/*!
	@brief The URL of the file to be uploaded. (NSURL)
 */
extern NSString *const RMUploadFileURLKey;

/*!
	@brief The title of the file to be uploaded. (NSString)
 */
extern NSString *const RMUploadFileTitleKey;

/*!
	@brief The date that the file to be uploaded was originally created. (NSDate)
 */
extern NSString *const RMUploadFileOriginalDateKey;

/*!
	@brief If the file represents a web site in some form, this key is that URL. (NSURL)
 */
extern NSString *const RMUploadFileOriginalURLKey;

/*!
	@brief The user's description of the file. (NSString)
 */
extern NSString *const RMUploadFileDescriptionKey;

/*!
	@brief An array of NSStrings representing tags. (NSArray of NSString)
 */
extern NSString *const RMUploadFileTagsKey;

/*
	Task Protocol
 */

/*!
    @brief An upload task represents an ecapsulated upload transaction with the target destination. This includes <em>not only</em> the upload of the file itself, but also any further transactions with the destination to set any relevant metadata.
 
 All upload tasks must implement the "upload" method. It is called by the Upload Queue when it is this task's turn to upload.
 
    The object is expected to notify the framework with <tt>RMUploadTaskStartedUploadingNotificationName</tt>, <tt>RMUploadTaskDidReceiveProgressNotificationName</tt>, <tt>RMUploadTaskFinishedUploadingNotificationName</tt> and <tt>RMUploadTaskDidCompleteNotificationName</tt> notifications.
*/
@interface RMUploadTask : NSObject

/*!
    @brief   This is the designated initialiser.
    @param	destination		The object representing the preset which is being used to upload the data.
	@param	uploadInfo	The data which is being uploaded. What is being sent is down from the host application. It is the plugin's responsibiltiy to check for nil values and what keys the object contains. It contains any keys set in your metadata view and any of the following default keys:
	
	<tt>RMUploadFileURLKey</tt> : The location of the file to be uploaded on disk. This comes in the form of a URL. (NSURL) <br/>
 
	<tt>RMUploadTitleKey</tt> : The title of the file to be uploaded. (NSString) <br/>
 
	<tt>RMUploadOriginalDateKey</tt> : This is the date when the image was taken/snapped/modified. For example, in Flickr's "date taken" field you would pass this value. For any APIs requiring the current date of the upload the plugin is required to pass it on however it feels is appropriate. (NSDate) <br/>
 
	<tt>RMUploadRatingKey</tt> : This is a short between 1 and 5. (NSNumber) <br/>
 
	<tt>RMUploadOriginalURLKey</tt> : If the file is a websnap, this will be passed as the URL of where the websnap was taken. (NSURL) <br/>
 
	<tt>RMUploadDescriptionKey</tt> : Any additional comments provided by the user. Such as the "description" field in LittleSnapper. (NSString) <br/>
 
	<tt>RMUploadTagsKey</tt> : An array of tags associated with the file as NSString objects. (NSArray) <br/>
*/
- (id)initWithPreset:(RMUploadPreset *)destination uploadInfo:(id)uploadInfo;

/*!	
	@brief
	The destination you were initalised with.
 */
@property (readonly) RMUploadPreset *destination;

/*!
	@brief
	Should be used to extract upload relevant information using <tt>-valueForKey:</tt>.
 */
@property (readonly) id uploadInfo;

/*!
    @brief   The central method to the class. How it is implemented is entirely up to the plugin developer. 
	
	Ensure, however, that you are posting the correct notifications. 
	
	Read the article "Uploading" for more information.
	
	A thread local run loop will be available when this method is called, you SHOULD use <tt>+[NSRunLoop currentRunLoop]</tt> instead of the main run loop or creating your own background thread.
 */
- (void)upload;

/*!
    @brief   This should immediately cease any uploading that the task is performing.
  
	If overridden, ensure you call the super's implementation, and then post the <tt>RMUploadTaskDidCompleteNotificationName</tt> notification once you have completed your work.
*/
- (void)cancel;

/*!
	@brief
	Set when the -cancel message is received.
 */
@property (readonly, getter=isCancelled) BOOL cancelled;

@end
