#pragma once
#include <vector>
#include <string>
#include "scene.h"


class SceneManager {
private:
    static std::vector<Scene*> scenes;
    static Scene* activeScene;

public:
    static Scene* CreateScene(const std::string& name);

    static void UnloadScene(Scene* scene);

    static void SetActiveScene(Scene* scene);

    static Scene* GetActiveScene();

    static Scene* GetSceneByName(const std::string& name);

    static void ClearAllScenes();
};
