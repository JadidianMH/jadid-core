#include "scene.h"
#include <algorithm>

Scene::Scene(const std::string &sceneName, const int number)
    : sceneName(sceneName), sceneNumber(number)
{
}

Scene::~Scene() {
    Clear();
}

const std::vector<GameObject*>& Scene::GetAllGameObjects() const {
    return allGameObjects;
}

void Scene::RegisterGameObject(GameObject* gameObject) {
    allGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(const std::string& name) {
    auto it = std::find_if(allGameObjects.begin(), allGameObjects.end(),
        [&name](GameObject* go) {
            return go->GetName() == name;
        });

    if (it != allGameObjects.end()) {
        delete (*it);
        allGameObjects.erase(it);
    } else {
        AddLog("Game Object not found by " + name + ".");
    }
}

void Scene::Clear() {
    for (auto go : allGameObjects)
        delete go;
    allGameObjects.clear();
}
