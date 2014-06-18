#include "shader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char * const Tower_VertexShaderSource = "\
#version 150\n\
uniform vec2 offset;\n\
in vec2 position;\n\
in vec4 color;\n\
in vec2 texcoord;\n\
\
out vec4 color_v;\n\
out vec2 tex;\n\
\
void main(void){\n\
  color_v = color;\n\
  gl_Position = vec4((position+offset), 0.0, 1.0);\n\
  tex = texcoord;\n\
}\n\
";

static const char * const Tower_FragShaderSource = "\
#version 150\n\
\
uniform sampler2D textureSampler;\n\
\
in vec4 color_v;\n\
in vec2 tex;\n\
out vec4 fragColor;\n\
\
void main(void){\n\
  vec4 texcolor = texture(textureSampler, tex);\n\
  fragColor = color_v*texcolor;\n\
}\n\
";

GLuint TowerDefaultFragShader(void){
    return TowerCreateShader(Tower_FragShaderSource, GL_FRAGMENT_SHADER);
}

GLuint TowerDefaultVertShader(void){
    return TowerCreateShader(Tower_VertexShaderSource, GL_VERTEX_SHADER);
}

GLuint TowerCreateDefaultProgram(void){
    return TowerCreateProgram(TowerDefaultFragShader(), TowerDefaultVertShader());
}

GLuint TowerCreateShader(const char *text, GLenum type){
    if(text==NULL){
        printf("[Shader] Error: Emtpy string given.\n");
        return 0;
    }
    GLuint shader = glCreateShader(type);
    if(shader==0){
        fprintf(stderr, "[Shader] Error: Something went terribly wrong, the shader index was 0.\n");
    }
    GLsizei tsize = (GLsizei)strlen(text)+2;

    glShaderSource(shader, 1, &text, &tsize);

    glCompileShader(shader);

    GLint shader_status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status==GL_FALSE) {
        printf("[Shader] Error: Failed to compile shader.\n");

        GLint log_size;
        GLint written = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char *log_text = (char *)malloc(log_size);
        glGetShaderInfoLog(shader, log_size, &written, log_text);
        if(written==0)
            printf("[Shader] Error: No log was written.\n");
        if(written>log_size)
            printf("[Shader] Error: Your OpenGL driver just wrote past the end of my buffer. I told it not to, really!\n");
        printf("%s\n", log_text);
        free(log_text);
        glDeleteShader(shader);

        return 0;
    }
    printf("[Shader] Info: Shader compiled ok. ID number %i.\n", shader);
    return shader;

}

GLuint TowerCreateProgram(GLuint frag, GLuint vert){
    if((glIsShader(frag)==GL_FALSE)||(glIsShader(vert)==GL_FALSE)){
        fprintf(stderr, "[Shader] Error: One or more shader was invalid\n\tFrag %s\tVert %s\n", 
        (glIsShader(frag)==GL_TRUE)?"good":"bad", (glIsShader(vert)==GL_TRUE)?"good":"bad");
        return 0;
    }

    GLint program_status;

    GLint fragstat, vertstat;

    glGetShaderiv(frag, GL_SHADER_TYPE, &fragstat);

    if(fragstat!=GL_FRAGMENT_SHADER)
        fprintf(stderr, "[Shader] Error: Invalid fragment shader.\n");

    glGetShaderiv(vert, GL_SHADER_TYPE, &vertstat);

    if(vertstat!=GL_VERTEX_SHADER)
        fprintf(stderr, "[Shader] Error: Invalid vertex shader.\n");

    if((fragstat!=GL_FRAGMENT_SHADER)||(vertstat!=GL_VERTEX_SHADER)){
        fprintf(stderr, "[Shader] Error: Bad shader(s). Exiting.\n");
        return 0;

    }

    GLuint prog = glCreateProgram();

    glAttachShader(prog, frag);
    glAttachShader(prog, vert);
    fprintf(stderr, "[Shader] Info: Linking Program.\n");
    glLinkProgram(prog);

    glGetProgramiv(prog, GL_LINK_STATUS, &program_status);

    if(!program_status){
        fprintf(stderr, "[Shader] Error: Could not link program.\n");
        GLint log_size;
        char *log_text;

        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &log_size);
        log_text = (char *)malloc(log_size+1);
        glGetProgramInfoLog(prog, log_size, NULL, log_text);
        fprintf(stderr, "%s\n", log_text);
        free(log_text);
        glDeleteProgram(prog);

        return 0;

    }
    fprintf(stderr, "[Shader] Info: Program linked ok.\n");
    return prog;

}