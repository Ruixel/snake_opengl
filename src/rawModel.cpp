#include "rawModel.h"

void rawModel::loadToVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{
    // Generate & Bind the VAO
    this->VAO = createVAO();
    this->bindVAO();

    // Generate the EBO/VBOs
    createEBO(indices);
    createVBO(vertices, 3, 0);
    //createVBO(texCoords, 2, 1);
    //createVBO(normals, 3, 2);

    glBindVertexArray(0);
}

void rawModel::bindVAO()
{
    glBindVertexArray(VAO);
}

int createVAO()
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}

template<class val>
int createVBO(std::vector<val> valArray, int valSize, int placement)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(val) * valArray.size(),
                 valArray.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, valSize, GL_FLOAT, GL_FALSE,
                          valSize * sizeof(val), (GLvoid*)0);

    glEnableVertexAttribArray(placement);

    return VBO;
}

template<class val>
int createEBO(std::vector<val> valArray)
{
    GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(val) * valArray.size(),
                 valArray.data(), GL_STATIC_DRAW);

    return EBO;
}
