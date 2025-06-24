#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "Shader.h"

class Object
{
public:
    Object(const glm::vec3& position);
    virtual ~Object();

    // Render object using shader
    virtual void render(const Shader& shader) const;
    // Returns true if ray intersects object
    virtual bool intersectRay(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const;
    glm::vec3 getPosition() const;

protected:
    glm::vec3 m_position;
    float m_scale;
    float m_pickRadius;
};

#endif // OBJECT_H
