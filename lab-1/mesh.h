#pragma once

#include <vector>
#include "glm.hpp"

struct Mesh {
public:
	Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices) : 
		vertices(vertices),
		indices(indices),
		indexCount(static_cast<int>(indices.size())) {};

	/// \n Draws the mesh onto the screen once per frame.
	void draw();

	std::vector<glm::vec3>& GetVertices() { return vertices; }
private:
	std::vector<glm::vec3> vertices;
	const std::vector<unsigned int> indices;
	const int indexCount;

	/// \n Vertex Buffer Object -> contains vertex attribute and index data.
	unsigned int VBO = 0;
	/// \n Element Buffer Object -> stores index data to avoid reusing coordinates in triangles.
	unsigned int EBO = 0;
};
