//***************************************************************************

// Copyright (C) 2009 Realmac Software Ltd
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information of Realmac Software Ltd
// and are protected by copyright law. They may not be disclosed
// to third parties or copied or duplicated in any form, in whole or
// in part, without the prior written consent of Realmac Software Ltd.

// Created by Keith Duncan on 26/03/2009

//***************************************************************************

#import <Foundation/Foundation.h>

#import "RMUploadKit/AFPropertyListProtocol.h"

@class RMUploadCredentials;
@class RMUploadPlugin;

/*!
	@file
 */

extern NSString *const RMUploadPresetNameKey;

extern NSString *const RMUploadPresetDirtyKey;

/*!
	@brief
	A representation of configurable options for a service.
 */
@interface RMUploadPreset : NSObject <AFPropertyList, NSCopying>

/*!
	@brief Called to initialise a preset from disk.
	
	We provide you with the representation that you return in <tt>propertyListRepresentation</tt> to hand off to the framework for saving.
 
	If you follow the <tt>-propertyListRepresentation</tt> example implementation, be sure to pass only the superclass representation to the superclass inititializer.
 
	An example implementation would be:
	\code
	- (id)initWithPropertyListRepresentation:(id)values {
		id superRepresentation = [values objectForKey:@"super"];
 
		self = [super initWithPropertyListRepresentation:superRepresentation];
		if (self == nil) return nil;
		
		[self setProperty:[values objectForKey:@"myKey"]];
		
		return self;
	}
	\endcode
 
	\param values The property list representation that was stored on disk.
 */
- (id)initWithPropertyListRepresentation:(id)values;

/*!
	@brief A representation of the instance that can be saved to a plist.
 
	In order to save accounts they will be turned into a plist, therefore here you need to return a representation of your object that can be saved safely into one. You must also call the super's implementation at the top of the method.
	
	It is essential that you include, and namespace the representation of the superclass. You MUST NOT assume the class of the superclass' representation, simply that it is suitable for inclusion in a property list written to disk.
 
	An example implementation would be:
	\code
	- (id)propertyListRepresentation {
		id superRepresentation = [super propertyListRepresentation];
 
		NSMutableDictionary *propertyListRepresentation = [NSMutableDictionary dictionary];
		[propertyListRepresentation setObject:superRepresentation forKey:@"super"];
 
		[propertyListRepresentation setValue:[self property] forKey:@"myKey"];
 
		return propertyListRepresentation;
	}
	\endcode
 */
- (id)propertyListRepresentation;

/*!
	@brief An identifier for the preset.
 */
@property (readonly, copy) NSURL *URIRepresentation;

/*!
	@brief The credentials the preset should use.
 
	This is a to-one relationship.
 */
@property (readonly, assign) RMUploadCredentials *authentication;

/*!
	@brief The plugin that owns the preset.
 */
@property (readonly, assign) RMUploadPlugin *plugin;

/*!
	@brief	This is the user provided name for the preset.
 */
@property (copy) NSString *name;

/*!
	@brief	Set this key to YES to cause the preset to be persisted to disk.
 
	This method is observed using key-value observing, when triggered your account will be saved.
 
	If you want to trigger a save automatically, you can return dependent keys in <tt>+keyPathsForValuesAffectingValueForKey:</tt> ensuring that you include the results from super.
 */
@property (getter=isDirty) BOOL dirty;

/*!
	@brief The UTIs that the account supports.
	
	This method is REQUIRED.
	
	The default implementation returns an empty set.
 
	\returns A set of UTI strings which the account supports.
 */
@property (readonly) NSSet *acceptedTypes;

/*!
	@brief
	This method MUST return a valid, non-nil URL, however overriding this method is optional if the class method of the same signature returns a valid value.
	
	This is used to graph and determine the geographical destination of the files.
 */
@property (readonly) NSURL *serviceURL;

@end

@interface RMUploadPreset (RMUploadMetadata)

/*!
	@brief
	This is used to determine if your preset requires or allows saved credentials, which can be shared between presets.
	
	@detail
	The default implementation returns Nil, return an RMUploadCredentials class if you support saved credentials.
 */
+ (Class)credentialsClass;

/*!
	@brief The class that you wish to use as the uploadTask for this account.
 
	This is used by <tt>-uploadTasksForPreset:objects:</tt> to instantiate and return your upload task.
	
	This method is REQUIRED, and if not implemented the framework throws an exception.
	
	@returns The uploadTask class.
 */
+ (Class)uploadTaskClass;

/*! 
	@returns The name for the destination type, preferably localised.
 */
+ (NSString *)localisedName;

/*!
	@returns The icon for the destination type.
 */
+ (NSImage *)icon;

/*!
	@brief
	This method constructs the URL from your Info.plist.
	
	If sent to a preset whose bundle RMUploadPluginServiceHostKey is nil, it will throw an exception.
 
	@detail
	This will be most useful for your own web services where you can use the Info.plist preprocessor to switch between development and deployment endpoints.
 */
+ (NSURL *)serviceURL;

@end
