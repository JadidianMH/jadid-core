#pragma once
#include <string>
#include <utility>
#include <vector>
#include "component.h"

class GameObject
{
private:
    std::vector<Component*> components;
    std::string nameGameObject;
public:
    GameObject(const std::string& name)
    {
        nameGameObject = name;
    }
    ~GameObject()
    {
        for (auto component : components) delete component;
    }

    template<typename T, typename ...Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value," this Component is not derived from Component");
        T* comp = new T(std::forward<Args>(args)...);
        components.push_back(comp);
        return comp;
    }

    template<typename T>
    T* GetComponent()
    {
        for (auto comp : components)
        {
            if (T* casted = dynamic_cast<T*>(comp))
            {
                return casted;
            } else
            {
                return nullptr;
            }
        }
    }

};