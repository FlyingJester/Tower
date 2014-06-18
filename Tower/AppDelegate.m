#import "AppDelegate.h"
#include "InitGL.h"
#import <AppKit/NSWindow.h>
#include <stdio.h>

#include "game.h"
#include <pthread.h>

CGLContextObj worldObj;

@interface HelloWorld : NSObject {}
- (void) loop;
@end

@implementation HelloWorld
- (void) loop{
    TowerHelloWorld(); //Never to return...
}
@end

void *TowerHelloWrap(void *_){
    CGLSetCurrentContext(worldObj);
    TowerHelloWorld();
    return NULL;
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSWindow *lMainWindow = [self window];    
    worldObj = InitGL(lMainWindow);
    CGLRetainContext(worldObj);
    TowerInitDrawQueue();
    //[NSThread detachNewThreadSelector:@selector(loop) toTarget:[HelloWorld alloc] withObject:nil];
    
    //while(![NSThread isMultiThreaded]){}
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&thread, &attr, TowerHelloWrap, NULL);
    
}

@end
