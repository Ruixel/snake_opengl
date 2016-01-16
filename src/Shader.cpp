#include "../include/Shader.h"

using namespace std;

void Shader::load(const GLchar* vertexPath, const GLchar* fragmentPath) {
    // Create relevant variables
    string vertexCode;
    string fragmentCode;

    ifstream vShaderFile;
    ifstream fShaderFile;

    // Get the ifstreams to cry when something doesn't go their way
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try {
        // open that shit up
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;

        // place buffer into stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert those streams of tears into strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch(ifstream::failure e) {
        cout << "Error: The shaders weren't loaded properly :(" << endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // Time to compile that shit
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    cout << vShaderCode << endl;
    cout << fShaderCode << endl;

    // Compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "Vertex Compilation Error: " << infoLog << endl;
    }

    // Compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "Fragment Compilation Error: " << infoLog << endl;
    }

    // Shader Program time
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);

    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        cout << "Shader Link Compilation Error: \n" << infoLog << endl;
    }

    // Last but not least, get rid of them shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(this->program); }
