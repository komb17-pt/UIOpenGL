#include "Button.h"
#include "MeshData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>


Button::Button(const glm::vec3& position)
    : Object(position)
{
    m_scale = 1.2f;
}


Button::~Button()
{}


void Button::render(const Shader& shader) const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(60.f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(m_scale));
    shader.setMat4("model", model);
    shader.setVec3("objectColor", glm::vec3(0.0f, 1.0f, 0.0f)); // green color for button

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


bool Button::intersectRay(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const
{
    return Object::intersectRay(rayOrigin, rayDir);
}
