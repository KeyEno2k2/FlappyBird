#include "GameLoop.h"

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    GameState = false;
    // Source Dimension:
    p.setSource(0, 0, 90, 64);
    // Destination Dimension
    p.setDest(10, 20, 90, 64);
}


bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        window = NULL;
    } else {
        cout << "Sukces!" << endl;
		GameState = true;
		p.CreateTexture("Image/bird2.png", renderer, p.getTexture());
		background = TextureManager::Texture("Image/background.png", renderer);
    }
}

void GameLoop::Event()
{
	SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT)
	{
		GameState = false;
	}

	//Mouse Events
	if (event1.type == SDL_MOUSEMOTION)
	{
		cout << event1.motion.x << " " << event1.motion.y << endl;
	}

	if (event1.type == SDL_MOUSEBUTTONDOWN)
	{
		 cout << "Pressed!" << endl;
	}

	//Keyboard Events
	if (event1.type == SDL_KEYDOWN)
	{
		if (event1.key.keysym.sym == SDLK_SPACE)
		{
			cout << "SPACE!" << endl;
		}
	}

}

void GameLoop::Update()
{

}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	p.Render(renderer, p.getTexture(), p.getSrc(), p.getDest());
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
