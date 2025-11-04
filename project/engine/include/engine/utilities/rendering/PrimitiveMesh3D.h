#pragma once

#include "PrimitiveMesh.h"

namespace EisEngine {
    namespace components{ class Mesh3D;}
    namespace rendering {

    struct PrimitiveMesh3D : public PrimitiveMesh {
        friend EisEngine::components::Mesh3D;
    public:
        explicit PrimitiveMesh3D(const std::vector<Vector3> &shapeVertices,
                                 const std::vector<unsigned int> &shapeIndices,
                                 const std::vector<Vector3>* shapeNormals = nullptr,
                                 const std::vector<Vector2>* shapeUVs = nullptr);
        /// \n Access the mesh's vertices.
        [[nodiscard]] std::vector<Vector3> GetVertices() const override;
        [[nodiscard]] std::vector<Vector3> GetNormals() const;
        [[nodiscard]] std::vector<Vector2> GetUVs() const;
    private:
        const std::vector<glm::vec3> vertices;
        const std::vector<glm::vec3> normals;
        const std::vector<glm::vec2> uvs;
    };

    } // rendering
} // EisEngine
