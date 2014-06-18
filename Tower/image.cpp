#include "image.hpp"
#include <libkern/OSAtomic.h>

#include <OpenGL/gl3.h>

#include <assert.h>

#define F(x) (float)x

using tower::gfx::Image;

void Image::incRef(){
    OSAtomicIncrement32((volatile int32_t *)(&refs));
}

Image::Image(int x, int y, int w, int h, const unsigned RGBA[w*h*sizeof(unsigned)]){
    glGenTextures(1, &texture);
    assert(texture);
    glGenBuffers(NUM_BUFFERS, buffers);
    
    assert(buffers[0]);
    assert(buffers[1]);
    assert(buffers[2]);

    float lVertex[] = {
    
    -1.0, -1.0,
    1.0, -1.0,
    1.0, 1.0,
    -1.0, 1.0,
    
    /*
        F(x),   F(y),
        F(x+w), F(y),
        F(x+w), F(y+h),
        F(x),   F(y+h)
    */
    };
    
    static const float cTexCoord[] = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
    };
    
    static const float cColor[] = {
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f
    };
    
    glBindTexture(GL_TEXTURE_2D, texture);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA);
    
    glGenVertexArrays(1, &vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(lVertex), lVertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(cTexCoord), cTexCoord, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[COLOR_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(cColor), cColor, GL_STATIC_DRAW); 
    
    glBindVertexArray(0);
}

void Image::updateAttribs() const{
    
    static const int comps[] = {
        2, 2, 4
    };
    
    glBindVertexArray(vao);
    
    for(int i = 0; i<NUM_BUFFERS; i++){
        assert(attributes[i]>=0);
        glEnableVertexAttribArray(attributes[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glVertexAttribPointer(attributes[i], comps[i], GL_FLOAT, GL_FALSE, 
        comps[i]*4, NULL);
    }
    glBindVertexArray(0);
}

void Image::Draw(void) const{
    this->updateAttribs();
    
    glBindVertexArray(vao);
    glEnable(GL_TEXTURE_2D);
    glEnableVertexAttribArray(attributes[0]);
    glEnableVertexAttribArray(attributes[1]);
    glEnableVertexAttribArray(attributes[2]);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    

}

