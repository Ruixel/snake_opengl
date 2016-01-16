#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
private:

public:
    GLuint program;

    void use();
    void load(const GLchar* vertexPath, const GLchar* fragmentPath);
};

#endif // SHADER_H
