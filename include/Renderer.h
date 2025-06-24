#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include "Scene.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    void render(const Scene& scene);
    // Converts screen coordinates to a world-space ray
    void screenPosToWorldRay(int mouseX, int mouseY, glm::vec3& out_origin, glm::vec3& out_direction) const;

private:
    int m_width;
    int m_height;
    Shader m_shader;
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif // RENDERER_H
