#include <iostream>
#include "engine.h"

using namespace std;

int main() {

    const bool DEBUG = true;

    auto [window, renderer] = Engine::PrepareEngine(DEBUG);
    Engine::RunEngine(window, renderer, DEBUG);
    Engine::QuitEngine(window, renderer);

    return 0;

}

