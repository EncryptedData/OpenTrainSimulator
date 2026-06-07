#include "SDLWindow.h"

#include <exception>
#include <SDL3/SDL.h>

SDLWindow::SDLWindow() :
    _shouldContinue{true}
{
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0)
    {
        throw std::exception();
    }

    const SDL_WindowFlags windowFlags = SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
    _window = SDL_CreateWindow("OpenTrainSimulator", 1280, 720, windowFlags);

    if (!_window)
    {
        throw std::exception();
    }

    SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(_window);
}

void SDLWindow::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            _shouldContinue = false;
        }
    }
}

bool SDLWindow::GetShouldContinue() const
{
    return _shouldContinue;
}

SDLWindow::~SDLWindow()
{
    if (_window)
    {
        SDL_DestroyWindow(_window);
    }

    SDL_Quit();
}
