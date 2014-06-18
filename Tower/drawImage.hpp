#pragma once
#include "drawingOperation.hpp"
#include "location.hpp"
#include "image.hpp"

namespace tower {
namespace gfx {

class drawImage : public Location, public DrawingOperation {
    float mOffsets[2];
protected:
    Image *mImage;
public:
    drawImage(Image *aImage, Location *aLoc, int offsetX, int offsetY);
    virtual void call(const DrawingState *aState);
};


}
}