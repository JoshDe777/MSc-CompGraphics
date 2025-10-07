#include "Renderer.h"
#include "Entity.h"

Renderer::Renderer(Entity* entity, Color color) : 
	entity(entity),
	m_color(color) {}

void Renderer::ApplyData(Shader& shader) { 
	shader.setVector("color", m_color);
}
