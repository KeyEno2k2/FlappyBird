#ifdef _WIN32
#include <windows.h>
#endif

#include "GameLoop.h"

GameLoop* g = new GameLoop();

#ifdef _WIN32
// Define WinMain to call main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    g->Initialize();
    while (g->getGameState()) {
        g->Render();
        g->Event();
        g->Update();
    }
    g->Clear();
    return 0;
}
#else
int main(int argc, char** argv) {
    g->Initialize();
    while (g->getGameState()) {
        g->Render();
        g->Event();
        g->Update();
    }
    g->Clear();
    return 0;
}
#endif
