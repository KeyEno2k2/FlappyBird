#include "GameLoop.h"
#include "TextureManager.h"
#include <cstdlib>
#include <ctime>
#include <sstream>  // Dodaj ten nagłówek, aby móc korzystać z stringstream

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    birdVelocity = 0.0f;
    gravity = 0.3f;
    lastPipeTime = 0;
    isGameOver = false;
    currentFrame = 0;
    lastFrameTime = 0;
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
        LoadBirdTextures();
        background = TextureManager::Texture("Image/background.png", renderer);
        gameOverTexture = TextureManager::Texture("Image/gameover.png", renderer);
        if (!gameOverTexture) {
            cout << "Failed to load Gameover.png" << endl;
        }
        gameOverRect.w = 192;
        gameOverRect.h = 42;
        gameOverRect.x = (WIDTH - gameOverRect.w) / 2;
        gameOverRect.y = (HEIGHT - gameOverRect.h) / 2;
        LoadNumberTextures();
        score = 0;
        pipes.push_back(new Pipe(renderer, 500, 200));
        lastFrameTime = SDL_GetTicks();
    }
}

void GameLoop::LoadBirdTextures() {
    birdTextures[0] = TextureManager::Texture("Image/yellowbird1.png", renderer);
    birdTextures[1] = TextureManager::Texture("Image/yellowbird2.png", renderer);
    birdTextures[2] = TextureManager::Texture("Image/yellowbird3.png", renderer);

    for (int i = 0; i < 3; i++) {
        if (!birdTextures[i]) {
            cout << "Failed to load bird texture " << i + 1 << endl;
        }
    }
}

void GameLoop::LoadNumberTextures() {
    for (int i = 0; i < 10; i++) {
        std::stringstream ss;
        ss << "Image/" << i << ".png";
        std::string filename = ss.str();
        numberTextures[i] = TextureManager::Texture(filename.c_str(), renderer);
        if (!numberTextures[i]) {
            cout << "Failed to load " << filename << endl;
        }
        numberRects[i].w = 24; // Szerokość obrazka cyfry
        numberRects[i].h = 36; // Wysokość obrazka cyfry
    }
}

void GameLoop::Event()
{
    SDL_PollEvent(&event1);
    if (event1.type == SDL_QUIT)
    {
        GameState = false;
    }

    if (isGameOver && event1.type == SDL_MOUSEBUTTONDOWN)
    {
        ResetGame();
    }

    if (event1.type == SDL_MOUSEBUTTONDOWN)
    {
        birdVelocity = -6.0f;
        cout << "Pressed!" << endl;
    }

    if (event1.type == SDL_KEYDOWN)
    {
        if (event1.key.keysym.sym == SDLK_SPACE)
        {
            birdVelocity = -6.0f;
            cout << "SPACE!" << endl;
        }
    }
}

void GameLoop::UpdateBirdAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= 100) { // Zmiana ramki co 100 ms
        currentFrame = (currentFrame + 1) % 3;
        lastFrameTime = currentTime;
    }
}

void GameLoop::Update()
{
    if (isGameOver) return;

    UpdateBirdAnimation(); // Aktualizacja animacji ptaka

    destPlayer.y += static_cast<int>(birdVelocity);
    birdVelocity += gravity;

    srcPlayer.h = 64;
    srcPlayer.w = 90;
    srcPlayer.x = srcPlayer.y = 0;

    destPlayer.h = 32;
    destPlayer.w = 45;
    destPlayer.x = 10;

    if (SDL_GetTicks() - lastPipeTime > 2000)
    {
        int y = rand() % (HEIGHT - 320);
        pipes.push_back(new Pipe(renderer, WIDTH, y));
        lastPipeTime = SDL_GetTicks();
    }

    for (auto pipe : pipes)
    {
        pipe->Update();
    }

    auto iter = pipes.begin();
    while (iter != pipes.end())
    {
        if ((*iter)->GetX() + (*iter)->GetWidth() < 0)
        {
            delete *iter;
            iter = pipes.erase(iter);
            score++; // Inkrementacja wyniku
        }
        else
        {
            ++iter;
        }
    }

    for (auto pipe : pipes)
    {
        if (SDL_HasIntersection(&destPlayer, &pipe->GetTopRect()) || SDL_HasIntersection(&destPlayer, &pipe->GetBottomRect()))
        {
            isGameOver = true;
            cout << "Collision detected. Game Over!" << endl;
            return;
        }
    }

    if (destPlayer.y + destPlayer.h > HEIGHT || destPlayer.y < 0)
    {
        isGameOver = true;
        cout << "Bird out of bounds. Game Over!" << endl;
    }
}

void GameLoop::RenderScore() {
    std::stringstream ss;
    ss << score;
    std::string scoreStr = ss.str();
    int x = 10;  // Zaczynamy od lewej strony ekranu
    int y = 10;
    for (char c : scoreStr) {
        int digit = c - '0';
        numberRects[digit].x = x;
        numberRects[digit].y = y;
        SDL_RenderCopy(renderer, numberTextures[digit], NULL, &numberRects[digit]);
        x += numberRects[digit].w + 5; // Przesuwamy się w prawo dla kolejnej cyfry
    }
}

void GameLoop::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, birdTextures[currentFrame], &srcPlayer, &destPlayer); // Użyj odpowiedniej ramki animacji
    for (auto pipe : pipes)
    {
        pipe->Render();
    }

    RenderScore();

    if (isGameOver)
    {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
        cout << "Rendering Game Over screen" << endl;
        RenderScore();
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

void GameLoop::ResetGame()
{
    isGameOver = false;
    birdVelocity = 0.0f;
    destPlayer.y = HEIGHT / 2;
    pipes.clear();
    lastPipeTime = SDL_GetTicks();
    score = 0;
    pipes.push_back(new Pipe(renderer, 500, 200));
    cout << "Game reset" << endl;
}
