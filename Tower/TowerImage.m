#include "TowerImage.h"
#import <AppKit/NSImage.h>
#import <Foundation/Foundation.h>

#include <stdlib.h>

struct TowerImageRGBA *TowerImageLoadFile(const char *aName){
    NSString *lName = [NSString stringWithCString:aName encoding:NSUTF8StringEncoding];
    
    NSData * lData = [NSData dataWithContentsOfFile:lName];
    NSBitmapImageRep * lBitmap = [NSBitmapImageRep imageRepWithData:lData];
    
    
    if(lBitmap==nil)
        return NULL;
        
    struct TowerImageRGBA *lReturn = malloc(sizeof(struct TowerImageRGBA));
    
    CGImageSourceRef myImageSourceRef = CGImageSourceCreateWithURL(
                    (__bridge CFURLRef)([[NSURL alloc] initFileURLWithPath:lName]), NULL);

    CGImageRef lImageRef = CGImageSourceCreateImageAtIndex(myImageSourceRef, 0, NULL);

    CFDataRef ldata = CGDataProviderCopyData(CGImageGetDataProvider(lImageRef));

    size_t lLen = CFDataGetLength(ldata);

    lReturn->RGBA = malloc(lLen);
    
    memcpy(lReturn->RGBA, CFDataGetBytePtr(ldata), lLen);
    
    CGDataProviderRelease((CGDataProviderRef)ldata);
    CGImageRelease(lImageRef);
    CFRelease(myImageSourceRef);
    
    lReturn->w = CGImageGetWidth(lImageRef);
    lReturn->h = CGImageGetHeight(lImageRef);
    
    return lReturn;
}