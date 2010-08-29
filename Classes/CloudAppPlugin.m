//
//  CloudAppPlugin.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppPlugin.h"

@implementation CloudAppPlugin

- (RMUploadPresetConfigurationViewController *)presetConfigurationViewControllerForPreset:(RMUploadPreset *)preset {
	NSViewController *controller = [[NSViewController alloc] initWithNibName:@"PresetConfig" bundle:[NSBundle bundleWithIdentifier:CloudAppBundleIdentifier]];
	return (RMUploadPresetConfigurationViewController *)controller;
}

@end
