#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
	GameState = false;
	birdVelocity = 0.0f;
	gravity = 0.3f;
	lastPipeTime = 0;
}

GameLoop::~GameLoop()
{
	for (auto pipe: pipes)
	{
		delete pipe;
	}
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
		player = TextureManager::Texture("Image/yellowbird2.png", renderer);
		background = TextureManager::Texture("Image/background.png", renderer);
		pipes.push_back(new Pipe(renderer, 500, 200));
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
		birdVelocity = -6.0f;
		 cout << "Pressed!" << endl;
	}

	//Keyboard Events
	if (event1.type == SDL_KEYDOWN)
	{
		if (event1.key.keysym.sym == SDLK_SPACE)
		{
			birdVelocity = -6.0f;
			cout << "SPACE!" << endl;
		}
	}

}

void GameLoop::Update()
{
	destPlayer.y += static_cast<int>(birdVelocity);
	birdVelocity += gravity;
	// Source Dimension:
	srcPlayer.h = 64;
	srcPlayer.w = 90;
	srcPlayer.x = srcPlayer.y = 0;

	// Destination Dimension
	destPlayer.h = 32;
	destPlayer.w = 45;
	destPlayer.x = 10;
	destPlayer.y++;

	if (SDL_GetTicks() - lastPipeTime > 2000)
	{
		int y = rand() % (HEIGHT - 320);
		pipes.push_back(new Pipe(renderer, WIDTH, y));
		lastPipeTime = SDL_GetTicks();
	}

	for (auto pipe : pipes)
	{
		pipe -> Update();
	}

	auto iter = pipes.begin();
	while (iter != pipes.end())
	{
		if ((*iter) -> GetX() + (*iter) -> GetWidth() < 0)
		{
			delete *iter;
			iter = pipes.erase(iter);
		} else {
			++iter;
		}
	}

	for (auto pipe : pipes)
	{
		if (SDL_HasIntersection(&destPlayer, &pipe ->GetTopRect()) || SDL_HasIntersection(&destPlayer, &pipe -> GetBottomRect()))
		{
			GameState = false;
		}
	}

}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, player, &srcPlayer, &destPlayer);
	for (auto pipe : pipes)
	{
		pipe -> Render();
	}
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