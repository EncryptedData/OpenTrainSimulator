
#include <RenderDevice.h>
#include "SDLWindow.h"
#include "ImguiRenderer.h"

int main()
{
    int windowWidth;
    int windowHeight;

    SDLWindow window{};
    window.GetWindowSize(windowWidth, windowHeight);

    std::vector<std::string> requiredSDLVulkanLayers{};
    window.GetRequiredVulkanExtensions(requiredSDLVulkanLayers);
    OpenTrainSimulator::Graphics::RenderDevice renderDevice{window.GetSurfaceFactory(), requiredSDLVulkanLayers, windowWidth, windowHeight};

    ImguiRenderer imguiRenderer{window, renderDevice};

    while (window.GetShouldContinue())
    {
        window.Update();
        window.GetWindowSize(windowWidth, windowHeight);

        renderDevice.BeginFrame(windowWidth, windowHeight);

        imguiRenderer.BeginFrame();

        imguiRenderer.Render();

        imguiRenderer.EndFrame();

        renderDevice.EndFrame();
    }

    return 0;
}