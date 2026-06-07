#include "SDLWindow.h"

#include <exception>
#include <stdexcept>
#include <SDL3/SDL.h>

#include "SDL3/SDL_vulkan.h"

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

void SDLWindow::GetRequiredVulkanExtensions(std::vector<std::string> &layers) const
{
    Uint32 requestExtensionsCount;
    auto requestedInstanceExtensions = SDL_Vulkan_GetInstanceExtensions(&requestExtensionsCount);

    for (Uint32 i = 0; i < requestExtensionsCount; i++)
    {
        layers.emplace_back(requestedInstanceExtensions[i]);
    }
}

std::function<void(VkInstance, VkSurfaceKHR*)> SDLWindow::GetSurfaceFactory() const
{
    return [&](VkInstance instance, VkSurfaceKHR* surface)
    {
        if (!SDL_Vulkan_CreateSurface(_window, instance, nullptr, surface))
        {
            throw std::runtime_error("SDL failed to create surface");
        }
    };
}

SDLWindow::~SDLWindow()
{
    if (_window)
    {
        SDL_DestroyWindow(_window);
    }

    SDL_Quit();
}
