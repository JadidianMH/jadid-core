#pragma once
#include <string>
#include <vector>
#include "game_object.h"

class Scene {
private:
    std::vector<GameObject*> allGameObjects;
    int sceneNumber = 0;
    std::string sceneName;

public:
    Scene(const std::string& sceneName, int number);
    ~Scene();

    int getSceneNumber() const { return sceneNumber; }
    const std::string& getSceneName() const { return sceneName; }

    void RegisterGameObject(GameObject* gameObject);
    void RemoveGameObject(const std::string& name);

    const std::vector<GameObject*>& GetAllGameObjects() const;
    void Clear();
};
