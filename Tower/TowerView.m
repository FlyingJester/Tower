#include "TowerView.h"
#include <OpenGL/gl3.h>
#include "drawingOperation.hpp"

@implementation TowerView
// This is the renderer output callback function

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, 
                            const CVTimeStamp* outputTime, CVOptionFlags flagsIn, 
                            CVOptionFlags* flagsOut, void* displayLinkContext){
                            
    CVReturn result = [(__bridge TowerView*)displayLinkContext getFrameForTime:outputTime];
    return result;
}


- (void)setShaderProgram:(int)program{
    shaderProgram = program;
}

- (void)prepareOpenGL{
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];

    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);

    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void *)(self)); 

    // Set the display link for the current renderer
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);

    // Activate the display link
    CVDisplayLinkStart(displayLink);
}
 

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime{
    volatile size_t lFrames = TowerGetNumberOfFinishedFrames();
    if(lFrames > 0){
        printf("Drawing a frame.\n");
        
        [[self openGLContext] makeCurrentContext];
        
        struct DrawingState lState;
        
        lState.mView = &self;
        lState.mShader = self->shaderProgram;
        lState.mOffsetUniform = glGetUniformLocation(lState.mShader, "offset");
        
        assert(lState.mOffsetUniform>=0);
        
        glUseProgram(lState.mShader);
        
        while(TowerGetNumberOfFinishedFrames()>0)
            TowerPopDrawQueue(&lState);
            
    }
    else{
        printf("Skipping frame draw until a frame is ready.\n");
    }
    return kCVReturnSuccess;
}

- (void)dealloc {
 CVDisplayLinkRelease(displayLink);
}

@end