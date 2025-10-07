#pragma once

#include <vector>
#include "glm.hpp"

struct Entity;

struct Mesh {
public:
	Mesh(
		Entity* entity,
		const std::vector<glm::vec3>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<glm::vec4>& colors
	);

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

	Entity* entity = nullptr;
};
