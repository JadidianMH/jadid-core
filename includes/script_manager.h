#pragma once
#include <python3.13/Python.h>
#include <vector>

class ScriptManager {
private:
    static std::vector<PyObject*> scripts;

public:
    static void start();
    static void runStart();
    static void runUpdate();
    static void runHarchiMarametehCpuUpdate();
    static void shutdown();
};