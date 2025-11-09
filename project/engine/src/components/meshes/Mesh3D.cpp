#include "engine/components/meshes/Mesh3D.h"

namespace EisEngine::components {
    void GLCheckError(const char* context) {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            DEBUG_ERROR("OpenGL Error: (" + std::string(context) + "): " + std::to_string(error))
        }
    }

    // create and fill an openGL buffer object of the specified type.
    template<typename T>
    GLuint CreateBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(bufferType, buffer);
        glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
        return buffer;
    }

    GLuint CreateVBO(const PrimitiveMesh3D& primitive){
        // buffer initialization
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        // data preparation
        const auto& vertices = Vec3VectorToGlm(primitive.GetVertices());
        auto vsize = vertices.size() * sizeof(glm::vec3);
        const auto& normals = Vec3VectorToGlm(primitive.GetNormals());
        auto nsize = normals.size() * sizeof(glm::vec3);
        const auto& uvs = Vec2VectorToGlm(primitive.GetUVs());
        auto uvsize = uvs.size() * sizeof(glm::vec2);
        auto total_buffer_size = GLsizeiptr(vsize + nsize + uvsize);

        // buffer population
        glBufferData(GL_ARRAY_BUFFER, total_buffer_size, nullptr, GL_STATIC_DRAW);
        int offset = 0;
        glBufferSubData(GL_ARRAY_BUFFER, offset, vsize, vertices.data());
        offset += vsize;
        glBufferSubData(GL_ARRAY_BUFFER, offset, nsize, normals.data());
        offset += nsize;
        glBufferSubData(GL_ARRAY_BUFFER, offset, uvsize, uvs.data());

        return buffer;
    }

    Mesh3D::Mesh3D(EisEngine::Game &engine, EisEngine::ecs::guid_t owner, const PrimitiveMesh3D &_primitive) :
    Component(engine, owner),
    primitive(_primitive),
    VBO(CreateVBO(_primitive)),
    EBO(CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitive.indices)) { }

    Mesh3D::Mesh3D(EisEngine::components::Mesh3D &&other)  noexcept  :
            Component(other),
            primitive(other.primitive)
    {
        owner = other.owner;
        std::swap(this->VBO, other.VBO);
        std::swap(this->EBO, other.EBO);
    }

    void Mesh3D::Invalidate() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        Component::Invalidate();
    }

    void Mesh3D::draw(const unsigned int& shaderProgram) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // test index order matching?
        glDisable(GL_CULL_FACE);

        // draw vertices
        auto vpos = glGetAttribLocation(shaderProgram, "aPos");
        glEnableVertexAttribArray(vpos);
        glVertexAttribPointer(vpos, 3, GL_FLOAT, GL_FALSE,
                              0, nullptr);
        const auto& vertices = Vec3VectorToGlm(primitive.GetVertices());
        auto offset = vertices.size() * sizeof(glm::vec3);

        // add normals - not yet used for now.
        /*auto norm = glGetAttribLocation(shaderProgram, "normal");
        glVertexAttribPointer(norm, 3, GL_FLOAT, GL_TRUE,
                              sizeof(glm::vec3), (GLvoid*)offset);
        const auto& normals = Vec3VectorToGlm(primitive.GetNormals());
        offset += normals.size() * sizeof(glm::vec3);*/

        // add uvs
        auto uv = glGetAttribLocation(shaderProgram, "texCoords");
        glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE,
                              0, (GLvoid*)offset);
        glEnableVertexAttribArray(uv);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glDrawElements(GL_TRIANGLES, primitive.indexCount, GL_UNSIGNED_INT, nullptr);
        GLCheckError("DrawElements");

        glEnable(GL_CULL_FACE);
    }
}