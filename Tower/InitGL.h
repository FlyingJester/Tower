#pragma once


#include <OpenGL/CGLTypes.h>

#ifndef __OBJC__
typedef void NSWindow;
typedef void NSOpenGLView;
#else
#import <AppKit/NSWindow.h>
#import <AppKit/NSOpenGLView.h>
#endif

#include "drawingOperation.hpp"

#ifdef __cplusplus
extern "C" {
#endif

CGLContextObj InitGL(NSWindow *aWindow);
void FlipScreen(NSWindow *aWindow, NSOpenGLView *aView);
void CGL_FlipScreen(const struct DrawingState *aState);

#ifdef __cplusplus
}
#endif