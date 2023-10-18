#include "Shader.hpp"

Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath): programID(0) {
    // read the shaders
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Couldn't read shader files" << e.what() << std::endl;
        EXIT_FAILURE;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();;

    uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkShader(vertex);

    uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkShader(fragment);

    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkProgram(programID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::setBool(const std::string name, const bool value) const {
    int vertexColorLocation = glGetUniformLocation(programID, name.c_str());
    glUniform1i(vertexColorLocation, value);
}

void Shader::setVec4(const std::string name, const float v1, const float v2, const float v3, const float v4) const {
    int vertexColorLocation = glGetUniformLocation(programID, name.c_str());
    if (vertexColorLocation == -1) {
        std::cerr<<"Couldn't find uniform slocation\n";
        return;
    }
    glUniform4f(vertexColorLocation, v1, v2, v3, v4);
}

void Shader::setInt(const std::string name, const int value) const {
    int vertexColorLocation = glGetUniformLocation(programID, name.c_str());
    glUniform1f(vertexColorLocation, value);
}

void Shader::setFloat(const std::string name, const float value) const {
    int vertexColorLocation = glGetUniformLocation(programID, name.c_str());
    glUniform1f(vertexColorLocation, value);
}

void Shader::checkShader(const unsigned int shader) const {
    // check compilation
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Couldn't check shader compilation: " << infoLog << std::endl;
        EXIT_FAILURE;
    }
}

void Shader::checkProgram(const unsigned int programID) const {
    // check linking
    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cout << "Couldn't check program linking: " << infoLog << std::endl;
        EXIT_FAILURE;
    }
}