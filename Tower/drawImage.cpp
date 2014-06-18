#include "drawImage.hpp"
#include <OpenGL/gl3.h>

#define F(X) static_cast<float>(x)

using tower::gfx::drawImage;

drawImage::drawImage(tower::gfx::Image *aImage, Location *aLoc, int offsetX, int offsetY)
            : Location(aLoc->x-offsetX, aLoc->y-offsetY)
            , mImage(aImage)
            , mOffsets {(float)offsetX, (float)offsetY} {
        aImage->incRef();
}

void drawImage::call(const DrawingState *aState){
    
        //aState->mShader = 3;
        mImage->setAttribs(
            glGetAttribLocation(3, "position"),
            glGetAttribLocation(3, "texcoord"),
            glGetAttribLocation(3, "color"),
            3
        );
    
    float offsets[] = {0.0f, 0.0f};
    glUniform2fv(aState->mOffsetUniform, 1, offsets);
    mImage->Draw();
    
    
}