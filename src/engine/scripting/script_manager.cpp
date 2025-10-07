#include "script_manager.h"
#include <filesystem>
#include <python3.13/Python.h>
#include "debug.h"

namespace fs = std::filesystem;

std::vector<PyObject*> ScriptManager::scripts;

void ScriptManager::start() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Add libs to python by default
    PyRun_SimpleString(
        "import sys, io\n"
        "if not hasattr(sys.stdout, 'buffer'):\n"
        "    sys.stdout = io.TextIOWrapper(open(1, 'wb'), encoding='utf-8', errors='replace')\n"
        "else:\n"
        "    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')\n"
        "sys.stderr = sys.stdout\n"
    );


    // Get a borrowed reference to sys.path
    PyObject* sysPath = PySys_GetObject("path");

    // Add current working directory (useful for engine imports)
    std::string cwd = fs::current_path().string();
    PyObject* pyCwd = PyUnicode_FromString(cwd.c_str());
    PyList_Append(sysPath, pyCwd);
    Py_DECREF(pyCwd);

    // Add scripts folder to sys.path
    std::string scriptsPath;
    try {
        scriptsPath = fs::canonical(fs::path("../scripts")).string();
    } catch (const std::exception&) {
        scriptsPath = (fs::path("../scripts")).make_preferred().string();
    }

    if (fs::exists(scriptsPath)) {
        PyObject* pyScripts = PyUnicode_FromString(scriptsPath.c_str());
        PyList_Append(sysPath, pyScripts);
        Py_DECREF(pyScripts);
    } else {
        AddLog("Warning: scripts path does not exist: " + scriptsPath);
    }

    // Debug: print sys.path
    PyObject* sysPathRepr = PyObject_Repr(sysPath);
    if (sysPathRepr) {
        const char* reprStr = PyUnicode_AsUTF8(sysPathRepr);
        if (reprStr) {
            AddLog(std::string("python sys.path = ") + reprStr);
        }
        Py_DECREF(sysPathRepr);
    }

    // Load all .py modules from the scripts folder
    for (const auto& entry : fs::directory_iterator(scriptsPath)) {
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".py") {
            std::string moduleNameStr = entry.path().stem().string();
            PyObject* moduleName = PyUnicode_FromString(moduleNameStr.c_str());

            AddLog("Trying to load Python script: " + entry.path().string());

            PyObject* module = PyImport_Import(moduleName);
            Py_DECREF(moduleName);

            if (!module) {
                PyErr_Print();
                AddLog("Failed to load module: " + moduleNameStr);
            } else {
                AddLog("Module loaded: " + moduleNameStr);
                scripts.push_back(module);
            }
        }
    }
}

void ScriptManager::runStart() {
    for (auto module : scripts) {

        PyObject* moduleNameObj = PyObject_GetAttrString(module, "__name__");
        std::string moduleName = moduleNameObj ? PyUnicode_AsUTF8(moduleNameObj) : "<unknown>";

        PyObject* func = PyObject_GetAttrString(module, "start");
        if (func && PyCallable_Check(func)) {
            PyObject* result = PyObject_CallObject(func, nullptr);
            if (!result) {
                PyErr_Print();
                AddLog("Error while running start() in module: " + moduleName);
            } else {
                Py_DECREF(result);
            }
        } else {
            AddLog("No start() found in module: " + moduleName);
        }

        Py_XDECREF(func);
        Py_XDECREF(moduleNameObj);
    }
}

void ScriptManager::runUpdate() {
    for (auto module : scripts) {
        PyObject* func = PyObject_GetAttrString(module, "update");
        if (func && PyCallable_Check(func)) {
            PyObject* result = PyObject_CallObject(func, nullptr);
            if (!result) PyErr_Print();
            else Py_DECREF(result);
        }
        Py_XDECREF(func);
    }
}

void ScriptManager::runHarchiMarametehCpuUpdate() {
    for (auto module : scripts) {
        PyObject* func = PyObject_GetAttrString(module, "harchiMarametehCpuUpdate");
        if (func && PyCallable_Check(func)) {
            PyObject* result = PyObject_CallObject(func, nullptr);
            if (!result) PyErr_Print();
            else Py_DECREF(result);
        }
        Py_XDECREF(func);
    }
}

void ScriptManager::shutdown() {
    for (auto module : scripts) {
        Py_DECREF(module);
    }
    scripts.clear();

    if (Py_IsInitialized()) {
        // Flush Python output buffers before shutdown
        PyRun_SimpleString(
            "import sys; sys.stdout.flush(); sys.stderr.flush()"
        );
        Py_Finalize();
    }
}
