#include "drawingOperation.hpp"
#include "initGL.h"
#include <atomic>

#include <OpenGL/gl3.h>
#include "concurrent_queue.hpp"
#include <stdio.h>

#define F(x) ((float)x)

typedef std::atomic<size_t> atomic_size;
typedef tower::concurrent::concurrent_queue<tower::gfx::DrawingOperation *> drawQueue_t;

volatile atomic_size num_flipscreens;

drawQueue_t drawQueue;
/*
template<>
tower::gfx::DrawingOperation* 
tower::concurrent::concurrent_queue<tower::gfx::DrawingOperation*>::pop(){
    _mutex.lock();
    tower::gfx::DrawingOperation* ret = _queue.front();
    _queue.pop();
    _mutex.unlock();
    return ret;
}
*/
tower::gfx::DrawingOperation::~DrawingOperation(){

}

void tower::gfx::ColorScreen::call(const struct DrawingState *){
    glClearColor(F(mColor[0])/255.0f, F(mColor[1])/255.0f, F(mColor[2])/255.0f, F(mColor[3])/255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 255);
}

void tower::gfx::FlipScreen::call(const DrawingState *aState){
    CGL_FlipScreen(aState);
    TowerDecNumberOfFinishedFrames();
}
tower::gfx::FlipScreen::FlipScreen(){
    TowerIncNumberOfFinishedFrames();
}
    
size_t TowerGetNumberOfFinishedFrames(void){
    return num_flipscreens.load();
}
void TowerIncNumberOfFinishedFrames(void){
    num_flipscreens++;
}
void TowerDecNumberOfFinishedFrames(void){
    num_flipscreens--;
}


void TowerPushDrawQueue(tower::gfx::DrawingOperation *aOperation){
    drawQueue.push(aOperation);
}

void TowerPopDrawQueue(const struct DrawingState * aState){
    
    tower::gfx::DrawingOperation *op = drawQueue.pop();
    if(op==nullptr)
        return;
    printf("Popped an operation.\n");
    op->call(aState);
    delete op;
    
}

void TowerInitDrawQueue(void){
    num_flipscreens.store(0);
}