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
    if(mImage->last_shader != aState->mShader){
        mImage->setAttribs(
            glGetAttribLocation(aState->mShader, "position"),
            glGetAttribLocation(aState->mShader, "texcoord"),
            glGetAttribLocation(aState->mShader, "color"),
            aState->mShader
        );
    }
    
    glUniform2fv(aState->mOffsetUniform, 1, mOffsets);
    mImage->Draw();
    
    
}