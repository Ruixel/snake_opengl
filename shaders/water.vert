#version 330 core

layout (location = 0) in vec3 position;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float timer;

void main() {
    float tX = timer + position.x;
    float tY = timer + position.z;

    vec3 pos = vec3(position.x, sin(tX) * cos(tY), position.z);
    gl_Position = projection * view * model * vec4(pos, 1.0);

    ourColor = vec3(position.z/5, position.z /5, position.z /5);
    //gl_Position = model * vec4(position.x, sin(position.y), position.z, 1.0);
}
