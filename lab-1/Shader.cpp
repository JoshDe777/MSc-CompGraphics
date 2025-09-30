#include "Shader.h"
#include "gtc/type_ptr.hpp"

Shader::Shader(const unsigned int& vertexShaderProgram, const unsigned int& fragmentShaderProgram) :
    vertexShader(vertexShaderProgram),
    fragmentShader(fragmentShaderProgram) {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
}

void Shader::Apply(const glm::mat4& newVPMatrix) {
    glUseProgram(shaderProgram);
    vpMatrix = newVPMatrix;
    setMatrix("mvp", vpMatrix);
    setVector("color", glm::vec4(1, 1, 1, 1));
}

void Shader::setMatrix(const std::string& uniformName, glm::mat4 matrix) const {
    auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::setVector(const std::string& uniformName, glm::vec4 vector) const {
    auto uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
}

const fs::path Shader::defaultVertexShaderPath = "vertexShader.vert";
const fs::path Shader::defaultFragmentShaderPath = "fragmentShader.frag";