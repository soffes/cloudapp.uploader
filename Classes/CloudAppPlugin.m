//
//  CloudAppPlugin.m
//  CloudApp
//
//  Created by Sam Soffes on 8/29/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//

#import "CloudAppPlugin.h"
#import "CloudAppCredentialsViewController.h"
#import "CloudAppPresetViewController.h"

@implementation CloudAppPlugin

- (RMUploadPresetConfigurationViewController *)credentialsConfigurationViewControllerForCredentials:(RMUploadCredentials *)credentials {
	CloudAppCredentialsViewController *viewController = [[CloudAppCredentialsViewController alloc] init];
	return viewController;
}


- (RMUploadPresetConfigurationViewController *)presetConfigurationViewControllerForPreset:(RMUploadPreset *)preset {
	CloudAppPresetViewController *controller = [[CloudAppPresetViewController alloc] init];
	return controller;
}

@end
