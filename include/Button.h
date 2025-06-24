#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"

class Button : public Object
{
public:
    Button(const glm::vec3& position);
    virtual ~Button();

    virtual void render(const Shader& shader) const override;
    virtual bool intersectRay(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const override;
};

#endif // BUTTON_H
