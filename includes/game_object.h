#pragma once
#include <string>
#include <utility>
#include <vector>
#include "component.h"
#include "debug.h"
#include "renderQueue.h"

class GameObject
{
private:
    std::vector<Component*> components;
    std::string nameGameObject;
public:
    GameObject(const std::string& name)
    {
        nameGameObject = name;
        RegisterGameObject(this);
    }
    ~GameObject()
    {
        for (auto component : components) delete component;
    }

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        T* comp = new T(this, std::forward<Args>(args)...);
        components.push_back(comp);
        AddLog("Added component to "+ nameGameObject +".");
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
            }
        }

        return nullptr;
    }

};