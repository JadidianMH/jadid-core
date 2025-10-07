#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "scene.h"
#include "game_object.h"
#include "component.h"
#include "transform.h"
#include "sprite_renderer.h"
#include "input_manager.h"
#include "scene_manager.h"
#include <iostream>

namespace py = pybind11;

PYBIND11_MODULE(engine, m) {
    m.doc() = "Bindings for game engine (selective exposure)";

    py::class_<Vector2>(m, "Vector2")
        .def(py::init<>())
        .def_readwrite("x", &Vector2::x)
        .def_readwrite("y", &Vector2::y);

    py::class_<Scene>(m, "Scene")
        .def("get_name", &Scene::getSceneName);

    py::class_<Component>(m, "Component")
        .def("get_gameobject", [](Component* c) {
            return c->gameObject;
        }, py::return_value_policy::reference);

    py::class_<Transform, Component>(m, "Transform")
        .def("move", &Transform::move)
        .def("set_position", &Transform::setPosition)
        .def("scale", &Transform::scale)
        .def("rotate", &Transform::rotate)
        .def("get_position", &Transform::getPosition)
        .def("get_scale", &Transform::getScale)
        .def("get_rotation", &Transform::getRotation);

    py::class_<SpriteRenderer, Component>(m, "SpriteRenderer")
        .def("get_zindex", [](SpriteRenderer* s) { return s->zIndex; })
        .def("set_zindex", [](SpriteRenderer* s, int z) { s->zIndex = z; });

    py::class_<GameObject>(m, "GameObject")
        .def(py::init<const std::string&>(), py::arg("name"))
        .def("get_name", &GameObject::GetName)
        .def("add_transform", [](GameObject &obj) -> Transform* {
            return obj.AddComponent<Transform>();
        }, py::return_value_policy::reference)
        .def("get_transform", [](GameObject &obj) -> Transform* {
            return obj.GetComponent<Transform>();
        }, py::return_value_policy::reference)
        .def("add_sprite_renderer", [](GameObject &obj, const std::string& path, int z) -> SpriteRenderer* {
            return obj.AddComponent<SpriteRenderer>(path, z);
        }, py::arg("sprite_path"), py::arg("z") = 0, py::return_value_policy::reference)
        .def("get_sprite_renderer", [](GameObject &obj) -> SpriteRenderer* {
            return obj.GetComponent<SpriteRenderer>();
        }, py::return_value_policy::reference);

    m.def("get_key", [](int scancode) {
        return Input::GetKey(static_cast<SDL_Scancode>(scancode));
    }, py::arg("scancode"));

    m.def("get_key_down", [](int scancode) {
        return Input::GetKeyDown(static_cast<SDL_Scancode>(scancode));
    }, py::arg("scancode"));

    m.def("get_key_up", [](int scancode) {
        return Input::GetKeyUp(static_cast<SDL_Scancode>(scancode));
    }, py::arg("scancode"));

    m.def("create_scene", [](const std::string& name) -> Scene* {
        try {
            Scene* scene = SceneManager::CreateScene(name);
            if (!scene)
                throw std::runtime_error("SceneManager::CreateScene returned nullptr (scene not created)");
            return scene;
        }
        catch (const std::exception& e) {
            PyErr_SetString(PyExc_RuntimeError, e.what());
            return nullptr;
        }
        catch (...) {
            PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception in create_scene");
            return nullptr;
        }
    }, py::arg("name"), py::return_value_policy::reference);


    m.def("unload_scene", [](Scene* s) {
        SceneManager::UnloadScene(s);
    }, py::arg("scene"));

    m.def("set_active_scene", [](Scene* s) {
        SceneManager::SetActiveScene(s);
    }, py::arg("scene"));

    m.def("get_active_scene", []() -> Scene* {
        return SceneManager::GetActiveScene();
    }, py::return_value_policy::reference);

    m.def("get_scene_by_name", [](const std::string& name) -> Scene* {
        return SceneManager::GetSceneByName(name);
    }, py::arg("name"), py::return_value_policy::reference);

    m.def("clear_all_scenes", []() {
        SceneManager::ClearAllScenes();
    }),

    m.def("log", &AddLog, "Add a message to debug logs");

    m.def("clear_logs", &ClearLogs);
}
