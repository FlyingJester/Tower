#pragma once
#include "InitGL.h"
#import <Cocoa/Cocoa.h>
#import <CoreVideo/CVDisplayLink.h>

#ifndef __OBJC__
#error This file has nothing for you.
#endif

@interface TowerView : NSOpenGLView
{
    CVDisplayLinkRef displayLink;
    int shaderProgram;
}
- (void)setShaderProgram:(int)program;
@end