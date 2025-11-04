#include "engine/utilities/rendering/PrimitiveMesh3D.h"
#include "engine/utilities/Vector2.h"

namespace EisEngine {
    namespace rendering {
        // converts a std::vector of Vector3's to a std::vector of glm::vec3's.
        std::vector<glm::vec3> Vector3ToGlmVector(const std::vector<Vector3>& v){
            std::vector<glm::vec3> result = {};
            for(auto i : v)
                result.emplace_back((glm::vec3) i);
            return result;
        }

        // converts a std::vector of Vector2's to a std::vector of glm::vec2's.
        std::vector<glm::vec2> Vector2ToGlmVector(const std::vector<Vector2>& v){
            std::vector<glm::vec2> result = {};
            for(auto i : v)
                result.emplace_back((glm::vec2) i);
            return result;
        }

        std::vector<glm::vec3> InitNormals(const std::vector<Vector3>* normals, const int& vCount){
            std::vector<glm::vec3> result = {};
            // if object has no normals, default to down.
            if(!normals){
                for(auto i = 0; i < vCount; i++)
                    result.emplace_back(0, 0, -1);
            }
            else
                result = Vector3ToGlmVector(*normals);

            return result;
        }

        std::vector<glm::vec2> InitUVs(const std::vector<Vector2>* uvs, const int& vCount){
            std::vector<glm::vec2> result = {};
            // if object has no uvs, default to (0, 0)
            if(!uvs){
                for(auto i = 0; i < vCount; i++)
                    result.emplace_back(0, 0);
            }
            else
                result = Vector2ToGlmVector(*uvs);

            return result;
        }

        PrimitiveMesh3D::PrimitiveMesh3D(const std::vector<Vector3> &shapeVertices,
                                         const std::vector<unsigned int> &shapeIndices,
                                         const std::vector<Vector3>* shapeNormals,
                                         const std::vector<Vector2>* shapeUVs) :
                                         vertices(Vector3ToGlmVector(shapeVertices)),
                                         normals(InitNormals(shapeNormals, (int) shapeVertices.size())),
                                         uvs(InitUVs(shapeUVs, (int) shapeVertices.size())),
                                         PrimitiveMesh(shapeVertices, shapeIndices) {}

        std::vector<Vector3> PrimitiveMesh3D::GetVertices() const {
            std::vector<Vector3> result = {};
            result.reserve(vertices.size());
            for(auto i : vertices)
                result.emplace_back(i);
            return result;
        }

        std::vector<Vector3> PrimitiveMesh3D::GetNormals() const {
            std::vector<Vector3> result = {};
            result.reserve(normals.size());
            for(auto i : normals)
                result.emplace_back(i);
            return result;
        }

        std::vector<Vector2> PrimitiveMesh3D::GetUVs() const {
            std::vector<Vector2> result = {};
            result.reserve(uvs.size());
            for(auto i : uvs)
                result.emplace_back(i);
            return result;
        }
    } // rendering
} // EisEngine