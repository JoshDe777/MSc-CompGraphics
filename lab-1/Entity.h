#pragma once

#include <vector>

#include <glm.hpp>
#include "mesh.h"
#include "Renderer.h"

struct Entity {
public:
	Entity(
		const std::vector<glm::vec3>& vertices, 
		const std::vector<unsigned int>& indices, 
		const std::vector<glm::vec4>& colors) :
		mesh(this, vertices, indices, colors), renderer(this, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
	};
	Mesh mesh;
	Renderer renderer;
};
