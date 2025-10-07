#pragma once

#include <glm.hpp>
#include "Shader.h"

using Color = glm::vec4;

struct Entity;

class Renderer {
public:
	Renderer(Entity* entity, Color color);

    /// \n Applies rendering data to the active shader before drawing meshes.
    virtual void ApplyData(Shader& shader);

    /// \n Sets a renderer's color to the provided value.
    void SetColor(Color newColor) { m_color = newColor; };
    /// \n returns the renderer's color in RGBA%.
    [[nodiscard]] Color GetColor() { return m_color; }

private:
    Color m_color;
    Entity* entity = nullptr;
};
