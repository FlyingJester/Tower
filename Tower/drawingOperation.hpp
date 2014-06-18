#pragma once

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
typedef void NSOpenGLView;
#endif

struct DrawingState {
    NSOpenGLView  *const * mView;
    unsigned mShader;
    unsigned mOffsetUniform;
};

#ifdef __cplusplus

namespace tower{
namespace gfx{


class DrawingOperation {
public:
    virtual ~DrawingOperation();
    virtual void call(const DrawingState *) = 0;
};

/////
// A very basic symbol to pass, the FlipScreen.

class FlipScreen : public DrawingOperation {
public:
    FlipScreen();
    virtual ~FlipScreen(){}
    virtual void call(const struct DrawingState *);
};

/////
// Another simple symbol, fills the screen with a certain color.
class ColorScreen : public DrawingOperation {
unsigned char mColor[4];
public:
    ColorScreen(unsigned int color){
        memcpy(mColor, &color, 4);
    }
    ColorScreen(unsigned char color[4]){
        memcpy(mColor, color, 4);
    }
    virtual ~ColorScreen() {}
    virtual void call(const struct DrawingState *);
    
};

}
}

void TowerPushDrawQueue(tower::gfx::DrawingOperation *aOperation);

extern "C"{
#endif
size_t TowerGetNumberOfFinishedFrames(void);
void TowerIncNumberOfFinishedFrames(void);
void TowerDecNumberOfFinishedFrames(void);
void TowerPopDrawQueue(const struct DrawingState * aState);
void TowerInitDrawQueue(void);
#ifdef __cplusplus
}
#endif