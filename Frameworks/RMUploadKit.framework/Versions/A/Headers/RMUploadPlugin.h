//***************************************************************************

// Copyright (C) 2009 Realmac Software Ltd
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information of Realmac Software Ltd
// and are protected by copyright law. They may not be disclosed
// to third parties or copied or duplicated in any form, in whole or
// in part, without the prior written consent of Realmac Software Ltd.

// Created by Keith Duncan on 25/03/2009

//***************************************************************************

#import <Foundation/Foundation.h>

@class RMUploadPreset;
@class RMUploadCredentials;

@class RMUploadPresetConfigurationViewController;
@class RMUploadMetadataConfigurationViewController;

/*!
	@file
 */

/*
 *	Plugin Bundle Info.plist Keys
 */

/*!
	@brief	Info.plist key, the framework will only load the plugin iff the framework CFBundleVersion number is greater than or equal to the given number.
			It is REQUIRED. The key you must include in the plist MUST NOT include the 'key' suffix, it should be RMUploadPluginBundleMinimumFrameworkBundleVersion.
 */
extern NSString *const RMUploadPluginBundleMinimumFrameworkBundleVersionKey;

/*!
	@brief	Info.plist key, an array of your account classes.
	
	This key should map to either:
	- an single NSString naming your preset class
	- an (NSArray) of the above strings
  */
extern NSString *const RMUploadPluginDestinationTypesKey;

/*!
	@brief
	This is used by <tt>+[RMUploadCredentials serviceURL]</tt> to construct the result.
 */
extern NSString *const RMUploadPluginServiceHostKey;

/*!
	@brief
	This is used by <tt>+[RMUploadCredentials serviceURL]</tt> to construct the result.
 */
extern NSString *const RMUploadPluginServiceUseSSLKey;

/*
 *	Keys
 */

extern NSString *const RMUploadPluginCredentialsKey;
extern NSString *const RMUploadPluginPresetsKey;

/*!
	@brief	Plugin bundle principal class. 
 
	This class deals with asking for various elements of the plugin when needed and also provides 
 
	The methods which return an NSViewController have assertions performed on the return value, if any of these conditions are true an exception will be thrown:
					- Your view controller MUST NOT be nil.
					- Your view controller's view MUST NOT have a superview.
 
	If you are returning a view controller, make no assumptions on how we will use the view, it may be in a sheet one version, and a window the next. Therefore do not call any methods to deal with closing windows etc. post the relevant methods through the plugin API.
 
	@detail
 
	\code
					   >> RMUploadCredentials
					 /		   (^)
	RMUploadPlugin <		   (|)
					 \		   (|)
					   >> RMUploadPreset
	\endcode
 */
@interface RMUploadPlugin : NSObject

/*!
	@brief	Designated initialiser.
	@discussion It is worth noting that plugins may be initialised concurrently and therefore no guarantees are made about the initialisation environment.
 
	@param bundle The instance of NSBundle representing the plugin wrapper.
 */
- (id)initWithBundle:(NSBundle *)bundle;

/*!
	@brief The bundle in which the plugin is situated.
	
	If your plugin requires access to any resources, this method is a helper to get access to the NSBundle instance for your plugin. 
 */
@property (readonly, retain) NSBundle *bundle;

/*!
	@brief The <tt>RMUploadCredentials</tt> objects representing previously saved credentials.
 */
@property (nonatomic, readonly, copy) NSSet *credentials;

/*!
	@brief
	These are the preset destinations, these are the only objects that should be displayed in the interface.
 */
@property (nonatomic, readonly, copy) NSSet *presets;

/*!
	@brief
	This method is REQUIRED if your preset requires credentials and returns a class from <tt>+credentialsClass</tt>.
 
	Used to return an NSViewController whose view allows the user to configure credentials, such as the username/password and or a token.
			
	You MUST NOT configure the plugin<->>credentials relationship in this method, this will be done for you if required.
 
	@detail
	The credentials object to configure is provided in the represented object property of the view controller you return.
 */
- (RMUploadPresetConfigurationViewController *)credentialsConfigurationViewControllerForCredentials:(RMUploadCredentials *)credentials;

/*!
	@brief
	This method is REQUIRED.
	
	@detail
	The preset object to configure is provided in the represented object property of the view controller you return.
	If you have no properties requiring configuration, return nil.
 */
- (RMUploadPresetConfigurationViewController *)presetConfigurationViewControllerForPreset:(RMUploadPreset *)preset;

/*!
	@brief
	This method is OPTIONAL.
	
	@detail
	If your plugin supports additional metadata set by the user at upload time this view will be placed in your plugin's section of the metadata view. The represented object of this will be a KVC container, the contents of which will be passed in the uploadinfo to upload tasks. However we make no guarantee that they will be the same object, just that any keys set here will be accessible from the uploadinfo.
 
	If you do add keys to this container they <em>must</em> be namespaced to your plugin.
 */
- (RMUploadMetadataConfigurationViewController *)additionalMetadataViewControllerForPresetClass:(Class)presetClass;

@end
