//
//  CloudAppPlugin.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppPlugin.h"

#import "CloudAppConstants.h"

@implementation CloudAppPlugin

- (RMUploadPresetConfigurationViewController *)presetConfigurationViewControllerForPreset:(RMUploadPreset *)preset
{
	// Note: this can be your own subclass of NSViewController if you wish.
	NSViewController *controller = [[NSViewController alloc] initWithNibName:@"PresetConfig" bundle:CloudAppBundleIdentifier];
	return controller;
}

@end
