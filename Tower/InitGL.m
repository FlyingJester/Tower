#include "InitGL.h"
#include "stdio.h"
#include "shader.h"
#include <assert.h>

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#include "TowerView.h"

void TowerViewSignalRedraw(void){
}

CGLContextObj InitGL(NSWindow *aWindow){
    assert(aWindow);

    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
    {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize , 24 ,
        NSOpenGLPFAAlphaSize , 8 ,
        NSOpenGLPFADoubleBuffer ,
        NSOpenGLPFAAccelerated ,
        NSOpenGLPFANoRecovery ,
        0
    };
    
    NSOpenGLPixelFormat *lPixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    NSOpenGLView *lView = [[TowerView alloc] initWithFrame:[[aWindow contentView] bounds] pixelFormat:lPixelFormat];
    NSOpenGLContext* mainContext =[lView openGLContext];
    [mainContext makeCurrentContext];
    [[aWindow contentView] addSubview:lView];
    
    glClearColor(0, 0, 0, 255);

    printf("[NSGL] Added OpenGL view to window %i\n", (int)(long)[aWindow windowNumber]);
    
    GLuint prog = TowerCreateDefaultProgram();
    printf("[NSGL] Created default shader program %i.\n", prog);
    glUseProgram(prog);
    
    CGLContextObj ctx = CGLGetCurrentContext();
    assert(ctx);
    assert(ctx = [mainContext CGLContextObj]);
    //Set Threading.
    CGLError err =  CGLEnable(ctx, kCGLCEMPEngine);
    assert(err==kCGLNoError);
    
    NSOpenGLPixelFormat *lPixelFormat2 = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    NSOpenGLContext *newContext = [[NSOpenGLContext alloc] initWithFormat:lPixelFormat2 shareContext:mainContext];
    
    
    [newContext makeCurrentContext];
    CGLContextObj newCtx = CGLGetCurrentContext();
    
    assert(newCtx);
    assert(newCtx == [newContext CGLContextObj]);
    
    glUseProgram(prog);
    glClearColor(0, 0, 0, 255);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    
    [[lView openGLContext] makeCurrentContext];
    glUseProgram(prog);
    glClearColor(0, 0, 0, 255);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    return newCtx;
    
}

void CGL_FlipScreen(const struct DrawingState *aState){
    
    [[*(aState->mView) openGLContext] makeCurrentContext];
    [[*(aState->mView) openGLContext] flushBuffer];
    glClear(GL_COLOR_BUFFER_BIT);
   
}

void FlipScreen(NSWindow *aWindow, NSOpenGLView *aView){



    
}