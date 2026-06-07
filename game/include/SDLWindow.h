#pragma once
#include <functional>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

struct SDL_Window;

class SDLWindow
{
public:
    SDLWindow();
    ~SDLWindow();

    void Update();

    bool GetShouldContinue() const;

    void GetRequiredVulkanExtensions(std::vector<std::string>& layers) const;

    [[nodiscard]] std::function<void(VkInstance, VkSurfaceKHR*)> GetSurfaceFactory() const;

private:
    SDL_Window* _window;
    bool _shouldContinue;
};