#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Object.h"
#include "Shader.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void addObject(std::unique_ptr<Object> obj);
    void removeObject(Object* obj);
    void render(const Shader& shader) const;
    // Returns a pointer to the object under the ray, or nullptr if none hit
    Object* pickObject(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const;
    void clear();
    size_t getObjectCount() const;

private:
    std::vector<std::unique_ptr<Object>> m_objects;
};

#endif // SCENE_H
