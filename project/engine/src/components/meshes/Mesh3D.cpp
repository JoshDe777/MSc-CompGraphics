#include "engine/components/meshes/Mesh3D.h"

namespace EisEngine::components {
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
        // to do
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

    void Mesh3D::draw() {
        // to do
    }
}