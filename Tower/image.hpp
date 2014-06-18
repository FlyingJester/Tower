#pragma once

namespace tower {
namespace gfx {

class Image {
friend class Location;

public:
    Image(int x, int y, int w, int h, const unsigned RGBA[w*h*sizeof(unsigned)]);
    enum {VERTEX_BUFFER, TEXCOORD_BUFFER, COLOR_BUFFER, NUM_BUFFERS};

    unsigned last_shader;
protected:


    unsigned refs;
    
    unsigned buffers[3];
    
    int attributes[3];
    
    unsigned texture, vao;
    
    int x, y;
    unsigned w, h;

    virtual void updateAttribs(void) const;

public:
        
    virtual inline bool setAttribs(int aVert, int aTexCoord, int aColor, unsigned aShader){
        attributes[VERTEX_BUFFER] = aVert; 
        attributes[TEXCOORD_BUFFER] = aTexCoord; 
        attributes[COLOR_BUFFER] = aColor;
        
        last_shader = aShader;
        
        bool success =  ( (aVert>= 0) && (aTexCoord >= 0) && (aColor >= 0) );
        if(success)
            updateAttribs();
            
        return success;
    }
    
    virtual void incRef();
    
    virtual void Draw(void) const;
    
    

};



}
}