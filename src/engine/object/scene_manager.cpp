#include "scene_manager.h"
#include "algorithm"

std::vector<Scene*> SceneManager::scenes;
Scene* SceneManager::activeScene = nullptr;

Scene* SceneManager::CreateScene(const std::string& name) {
    int number = static_cast<int>(scenes.size()) + 1;
    Scene* scene = new Scene(name, number);
    scenes.push_back(scene);

    if (!activeScene) {
        activeScene = scene;
    }

    AddLog("Scene created: " + name);
    return scene;
}

void SceneManager::UnloadScene(Scene* scene) {
    auto it = std::find(scenes.begin(), scenes.end(), scene);
    if (it != scenes.end()) {
        if (activeScene == scene) {
            activeScene = nullptr;
        }

        delete scene;
        scenes.erase(it);

        AddLog("Scene unloaded.");
    } else {
        AddLog("Scene not found for unloading.");
    }
}

void SceneManager::SetActiveScene(Scene* scene) {
    auto it = std::find(scenes.begin(), scenes.end(), scene);
    if (it != scenes.end()) {
        activeScene = scene;
        AddLog("Active scene set to: " + scene->getSceneName());
    } else {
        AddLog("Scene not found to set active.");
    }
}

Scene* SceneManager::GetActiveScene() {
    return activeScene;
}

Scene* SceneManager::GetSceneByName(const std::string& name) {
    for (auto scene : scenes) {
        if (scene->getSceneName() == name) return scene;
    }
    return nullptr;
}

void SceneManager::ClearAllScenes() {
    for (auto scene : scenes)
        delete scene;
    scenes.clear();
    activeScene = nullptr;
    AddLog("All scenes cleared.");
}