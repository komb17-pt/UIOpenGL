#include "Scene.h"
#include <algorithm>
#include <iostream>


Scene::Scene()
{}


Scene::~Scene()
{
    clear();
}


void Scene::addObject(std::unique_ptr<Object> obj)
{
    m_objects.push_back(std::move(obj));
    std::cout << "Object added to scene." << m_objects.size() << std::endl;
}


void Scene::removeObject(Object* obj)
{
    auto it = std::remove_if(m_objects.begin(), m_objects.end(),
        [obj](const std::unique_ptr<Object>& p)
        {
            return p.get() == obj;
        }
    );

    if(it != m_objects.end())
    {
        m_objects.erase(it, m_objects.end());
        std::cout << "Object removed from scene." << m_objects.size() << std::endl;
    }
}


void Scene::render(const Shader& shader) const
{
    for(const auto& obj : m_objects)
    {
        obj->render(shader);
    }
}


Object* Scene::pickObject(const glm::vec3& rayOrigin, const glm::vec3& rayDir) const
{
    // Iterate over objects and return first one whose bounding sphere is hit.
    for(const auto& obj : m_objects)
    {
        if (obj->intersectRay(rayOrigin, rayDir))
        {
            return obj.get();
        }
    }

    return nullptr;
}


void Scene::clear()
{
    m_objects.clear();
    std::cout << "Scene cleared. Object count: " << getObjectCount() << std::endl;
}


size_t Scene::getObjectCount() const
{
    return m_objects.size();
}
