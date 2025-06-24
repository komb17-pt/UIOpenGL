#include "Object.h"
#include "MeshData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>


Object::Object(const glm::vec3& position)
    : m_position(position), m_scale(1.0f), m_pickRadius(0.75f)
{}


Object::~Object()
{}


void Object::render(const Shader& shader) const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(60.f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(m_scale));
    shader.setMat4("model", model);
    shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    // Create VAO and VBO for cube data
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}


glm::vec3 Object::getPosition() const
{
    return m_position;
}


bool Object::intersectRay(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const
{
    // Simple ray-sphere intersection test
    glm::vec3 oc = rayOrigin - m_position;
    float a = glm::dot(rayDir, rayDir);
    float b = 2.0f * glm::dot(oc, rayDir);
    float c = glm::dot(oc, oc) - m_pickRadius * m_pickRadius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}
