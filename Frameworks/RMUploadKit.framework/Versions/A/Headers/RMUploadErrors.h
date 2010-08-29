//
//  RMUploadErrors.h
//  RMUploadKit
//
//  Created by Keith Duncan on 05/08/2010.
//  Copyright 2010 Realmac Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
	@brief
	These correspond to the <tt>RMUploadKitBundleIdentifier</tt> domain.
 */
enum {
	//
	RMUploadErrorNone = 0,
	RMUploadErrorUnknown = -1,
	
	// [-100, -199]
	RMUploadPresetConfigurationViewControllerErrorValidation = -100,
	
};
typedef NSInteger RMUploadKitErrorCode;
