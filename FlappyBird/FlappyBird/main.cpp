#include "GameLoop.h"

GameLoop* g = new GameLoop();

using namespace std;

int main(int argc, char** argv)
{
	g->Initialize();
	while (1)
	{
		g->Render();

	}
	g->Clear();

	return 0;
}


// Funkcja WinMain
int WinMain(int argc, char* argv[]) {
    // Wywołaj funkcję main
    return main(argc, argv);
}