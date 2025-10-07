#include "mesh.h"

#include <glad/glad.h>

#include "Entity.h"

template<typename T>
GLuint CreateBuffer(GLuint bufferType, const std::vector<T>& bufferData) {
	/// Create a generic buffer object.
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(bufferType, buffer);
	glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
	return buffer;
}

GLuint CreateVBO(const std::vector<glm::vec3>& vertexData, const std::vector<glm::vec4>& colorData) {
	/// Create a vertex buffer object with vertex & color data.
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	auto total_size = vertexData.size() * sizeof(glm::vec3) + colorData.size() * sizeof(glm::vec4);
	glBufferData(GL_ARRAY_BUFFER, total_size, NULL, GL_STATIC_DRAW);

	auto vertex_data_size = vertexData.size() * sizeof(glm::vec3);
	auto color_data_size = colorData.size() * sizeof(glm::vec4);

	// init vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_data_size, vertexData.data());
	// init colors after vertices
	glBufferSubData(GL_ARRAY_BUFFER, vertex_data_size, color_data_size, colorData.data());

	return buffer;
}

Mesh:: Mesh(
	Entity* entity,
	const std::vector<glm::vec3>& vertices,
	const std::vector<unsigned int>& indices,
	const std::vector<glm::vec4>& colors
) :
	entity(entity),
	vertices(vertices),
	indices(indices),
	indexCount(static_cast<int>(indices.size())),
	VBO(CreateVBO(vertices, colors)),
	EBO(CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indices)) {
};

void Mesh::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// params: 
	// - id
	// - n(items) per group, 
	// - data type, 
	// - is normalized?, 
	// - stride: how many items should it skip between items, 
	// - pointer: offset from buffer start
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);						// vertices
	auto vertex_data_size = sizeof(glm::vec3) * vertices.size();
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) vertex_data_size);		// colors

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}