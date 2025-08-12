#include <iostream>
#include "engine.h"

using namespace std;

static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;

int main() {

    Engine::PrepareEngine();
    Engine::RunEngine();

    return 0;

}