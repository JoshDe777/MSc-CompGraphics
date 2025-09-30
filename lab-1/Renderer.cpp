#include "Renderer.h"

Renderer::Renderer(const Color& color) : m_color(color) {}

void Renderer::ApplyData(Shader& shader) { shader.setVector("color", m_color); }
