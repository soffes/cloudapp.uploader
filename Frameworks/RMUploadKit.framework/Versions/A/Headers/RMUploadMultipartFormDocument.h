//
//  DSMultipartFormDocument.h
//  Courier
//
//  Created by Keith Duncan on 29/04/2010.
//  Copyright 2010 Realmac Software. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
	@brief
	This format is described in RFC 2388 [http://tools.ietf.org/html/rfc2388]
	
	@detail
	The order you add values in is unpreserved.
 */
@interface RMUploadMultipartFormDocument : NSObject

/*!
	@brief
	Fetch a previously stored value for the field key.
 */
- (NSString *)valueForField:(NSString *)fieldname;

/*!
	@brief
	The fieldname must be unique per document, setting a value for an existing fieldname will overwrite the previous value.
 */
- (void)setValue:(NSString *)value forField:(NSString *)fieldname;

/*!
	@brief
	Unordered collection of previously added URLs using <tt>-addFileByReferencingURL:withFilename:toField:</tt>.
 */
- (NSSet *)fileLocationsForField:(NSString *)fieldname;

/*!
	@brief
	Form documents support multiple files per-fieldname.
	
	@param filename
	This is optional, excluding it will use the last path component.
 */
- (void)addFileByReferencingURL:(NSURL *)location withFilename:(NSString *)filename toField:(NSString *)fieldname;

/*!
	@brief
	Serialise everything into a data object.
	
	@param contentTypeRef
	Contains the generated multipart boundary.
 */
- (void)getFormData:(NSData **)dataRef contentType:(NSString **)contentTypeRef;

@end
