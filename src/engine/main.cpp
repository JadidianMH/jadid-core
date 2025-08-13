#include <iostream>
#include "engine.h"

using namespace std;

int main() {

    auto [window, surface] = Engine::PrepareEngine();
    Engine::RunEngine(window, surface);
    Engine::QuitEngine(window);

    return 0;

}

