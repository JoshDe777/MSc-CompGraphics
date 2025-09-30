#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"

#include <filesystem>

namespace fs = std::filesystem;

class Shader {
public:
	/// \n Creates a shader from the given shader programs.
	explicit Shader(const unsigned int& vertexShaderProgram, const unsigned int& fragmentShaderProgram);

	/// \n Applies the shader to the rendering pipeline.
	void Apply(const glm::mat4& newVPMatrix);

    /// \n Sets a given uniform matrix in the shader program to the specified value.
    /// @param uniformName - a string representing the name of the matrix whose values are to be set.
    /// @param matrix - a 4x4 matrix representing the new desired value.
    void setMatrix(const std::string& uniformName, glm::mat4 matrix) const;

    /// \n Sets a given uniform vector in the shader program to the specified value.
    /// @param uniformName - a string representing the name of the vector whose values are to be set.
    /// @param vector - a 4D-vector representing the new desired value.
    void setVector(const std::string& uniformName, glm::vec4 vector) const;

    /// \n Multiplies the provided view-projection with the model matrix to give object position in camera space.
    /// @param modelMatrix: a 4x4 matrix representing object coordinates in world space.
    /// @param vpMatrix: a 4x4 matrix representing the screen projection from the camera's position.
    /// @return a 4x4 matrix representing object coordinates in camera space.
    [[nodiscard]] glm::mat4 CalculateMVPMatrix(const glm::mat4& modelMatrix) const { return vpMatrix * modelMatrix; }

    /// \n The relative path to access the default vertex shader program definition.
    static const fs::path defaultVertexShaderPath;
    /// \n The relative path to access the default fragment shader program definition.
    static const fs::path defaultFragmentShaderPath;
private:
    /// \n The OpenGL shader program.
    unsigned int shaderProgram = 0;
    /// \n This component's vertex shader.
    unsigned int vertexShader = 0;
    /// \n This component's fragment shader.
    unsigned int fragmentShader = 0;

    /// \n The last saved view-projection matrix.
    glm::mat4 vpMatrix = glm::mat4(1.0f);
};
