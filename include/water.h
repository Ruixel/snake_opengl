#ifndef WATER_H
#define WATER_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/System.hpp>

#include "rawModel.h"
#include "Shader.h"

class water
{
private:
    float SIZE = 10;
    float VERTEX_COUNT = 32;

    float x, z;
    Shader waterShader;
    rawModel waterMesh;
    glm::mat4 model_mat;

    int indexNum;
    sf::Clock t;

    void generatePlaneMesh();

public:
    // Constructor
    water();

    void renderMesh(glm::mat4 view_mat, glm::mat4 projection_mat);
};

#endif // WATER_H
