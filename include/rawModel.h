#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <vector>

// VAO, VBO & EBO
int createVAO();

template<class val>
int createVBO(std::vector<val> valArray, int valSize, int placement);

template<class val>
int createEBO(std::vector<val> valArray);

class rawModel
{
private:
    GLuint VAO;

public:
    void loadToVAO(std::vector<GLfloat> vertices,
                   std::vector<GLuint> indices);

    void bindVAO();
};

#endif // RAWMODEL_H
