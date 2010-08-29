//
//  RMUploadDestinationViewController.h
//  RMUploadKit
//
//  Created by Keith Duncan on 24/09/2009.
//  Copyright 2009 Realmac Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
	@brief
	Post this once you have completed your work in <tt>-nextStage:</tt> to signal a change in the advancement status.
	
	@detail
	If your validation succeeded, post it with an empty userInfo.
	If an error occurs, return it under the error <tt>RMUploadDestinationConfigurationViewControllerCompletionErrorKey</tt> to signal that the view cannot advance.
 */
extern NSString *const RMUploadPresetConfigurationViewControllerDidCompleteNotificationName;
	
	/*
		If the domain is RMUploadKitBundleIdentifier and the code is RMUploadPresetConfigurationViewControllerErrorValidation, the error isn't presented, but the view doesn't advance.
	 */
	extern NSString *const RMUploadPresetConfigurationViewControllerDidCompleteErrorKey; // NSError

/*
 *	Keys
 */

extern NSString *const RMUploadPresetConfigurationViewControllerLocalisedAdvanceButtonTitleKey;

/*!
	@brief
	Base class for RMUploadCredentials and RMUploadPreset configuration view controllers.
	
	@detail
	You view MUST be 289pt wide, there is no height restriction (within reason).
 */
@interface RMUploadPresetConfigurationViewController : NSViewController

/*!
	@brief
	Observed and set as the 'next' button title.
	
	@detail
	Intended for OAuth based credential view controllers so that they can title the button 'Authenticate'.
 */
@property (readonly) NSString *localisedAdvanceButtonTitle;

/*!
	@brief
	You must capture this action message to perform any validation before proceeding. You MUST validate your credential/preset object here.
	
	Once you have completed your validation, post the <tt>RMUploadDestinationConfigurationViewControllerStageDidCompleteNotificationName</tt> notification to the <tt>[NSNotificationCenter defaultCenter]</tt> on the main thread with self as the object.
	
	The default implementation simply posts the notification.
	
	If your validation returns an error include it in the notification dictionary.
	You can include a recovery attempter under the NSRecoveryAttempterErrorKey key.
		- If you include a recovery attempter, and recover from the error, configuration will continue as if no error had been returned in the first place.
		- If you include a recovery attempter, and don't recover from the error, configuration doesn't continue and the user is returned to the current configuration view controller.
 */
- (IBAction)nextStage:(id)sender;

/*
	View Controller Conveniences
	
		These will be called for you.
 */

- (void)viewWillDisappear:(BOOL)animated;

- (void)viewDidAppear:(BOOL)animated;

@end
