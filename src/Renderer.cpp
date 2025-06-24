#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>


Renderer::Renderer(int width, int height)
    : m_width(width), m_height(height),
    m_shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH)
{
    m_projection = glm::perspective(glm::radians(45.0f), (float)m_width / m_height, 0.1f, 100.0f);
    m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                         glm::vec3(0.0f, 0.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f));
}


Renderer::~Renderer()
{}


void Renderer::render(const Scene& scene)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();
    m_shader.setMat4("projection", m_projection);
    m_shader.setMat4("view", m_view);

    // Set view position (camera position)
    m_shader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));
    m_shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    scene.render(m_shader);
}


void Renderer::screenPosToWorldRay(int mouseX, int mouseY, glm::vec3& out_origin, glm::vec3& out_direction) const
{
    float x = (2.0f * mouseX) / m_width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / m_height;
    float z = 1.0f;
    glm::vec3 ray_nds = glm::vec3(x, y, z);

    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
    glm::mat4 invProjection = glm::inverse(m_projection);
    glm::vec4 ray_eye = invProjection * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    glm::mat4 invView = glm::inverse(m_view);
    glm::vec4 ray_world = invView * ray_eye;
    out_direction = glm::normalize(glm::vec3(ray_world));
    out_origin = glm::vec3(glm::inverse(m_view)[3]); // camera position
}
