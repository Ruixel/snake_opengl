#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "water.h"

// WINDOW VARIABLES
int WINDOW_WIDTH  = 800;
int WINDOW_HEIGHT = 600;

// LOOP
bool running = true;
GLfloat deltaTime;
sf::Clock timer;

int main()
{
    sf::ContextSettings cSettings;
    cSettings.depthBits = 24;
    cSettings.antialiasingLevel = 8;
    cSettings.stencilBits = 8;

    sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SnakeGL", sf::Style::Default, cSettings);
    window.setFramerateLimit(60);

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);
    if (!GLEW_VERSION_3_3)
        exit(1);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    water objWater;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Game Loop
    timer.restart();
    while (running)
    {
        // Loop Start
        deltaTime = (GLfloat)timer.getElapsedTime().asMilliseconds() / 1000;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1.0f);

        // Event Input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;

            if (event.type == sf::Event::Resized)
            {
                WINDOW_WIDTH = event.size.width;
                WINDOW_HEIGHT = event.size.height;
                glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    running = false;
                    break;
                }
            }
        }

        // Render
        glm::mat4 view;
        view = glm::translate(view, glm::vec3(-5, 0, -8));

        glm::mat4 projection;
        projection = glm::perspective(45.0f, (GLfloat)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

        objWater.renderMesh(view, projection);

        window.display();
    }

    // Delete

    // End
    return 0;
}
