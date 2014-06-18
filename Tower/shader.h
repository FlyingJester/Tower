#pragma once

#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

/////
// Intended use:
//
// GLuint vert = TowerCreateShader(vert_src, GL_VERTEX_SHADER);
// GLuint frag = TowerCreateShader(frag_src, GL_FRAGMENT_SHADER);
//
// GLuint prog = TowerCreateProgram(frag, vert);
//

GLuint TowerCreateShader(const char *text, GLenum type);
GLuint TowerCreateProgram(GLuint frag, GLuint vert);
GLuint TowerDefaultFragShader(void);
GLuint TowerDefaultVertShader(void);

GLuint TowerCreateDefaultProgram(void);