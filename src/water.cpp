#include "water.h"

water::water()
{
    waterShader.load("shaders/water.vert", "shaders/water.frag");
    this->generatePlaneMesh();
}

void water::generatePlaneMesh()
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLfloat v = 0.0f;

    // Generate values for the VBOs
    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        for (int j = 0; j < VERTEX_COUNT; j++)
        {
            v = (GLfloat)(j/(VERTEX_COUNT - 1) * SIZE);
            vertices.push_back(v);
            vertices.push_back(0);
            v = (GLfloat)(i/(VERTEX_COUNT - 1) * SIZE);
            vertices.push_back(v);
        }
    }

    // Generate values for the EBO
    for (int z = 0; z < VERTEX_COUNT-1; z++)
    {
        for (int x = 0; x < VERTEX_COUNT-1; x++)
        {
            int topLeft     = (z*VERTEX_COUNT) + x;
            int topRight    = topLeft + 1;
            int bottomLeft  = ((z+1)*VERTEX_COUNT) + x;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    this->indexNum = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);
    model_mat = glm::rotate(model_mat, glm::radians(30.0f), glm::vec3(1, 0, 0));

    waterMesh.loadToVAO(vertices, indices);
}

void water::renderMesh(glm::mat4 view_mat, glm::mat4 projection_mat)
{
    waterShader.use();
    waterMesh.bindVAO();

    GLuint modelLoc = glGetUniformLocation(waterShader.program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_mat));

    GLuint viewLoc = glGetUniformLocation(waterShader.program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_mat));

    GLuint projectionLoc = glGetUniformLocation(waterShader.program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_mat));

    GLuint timerLoc = glGetUniformLocation(waterShader.program, "timer");
    glUniform1f(timerLoc, t.getElapsedTime().asSeconds());

    glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
