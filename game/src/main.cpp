
#include <RenderDevice.h>
#include "SDLWindow.h"

int main()
{
    SDLWindow window{};

    std::vector<std::string> requiredSDLVulkanLayers{};
    window.GetRequiredVulkanExtensions(requiredSDLVulkanLayers);
    OpenTrainSimulator::Graphics::RenderDevice renderDevice{window.GetSurfaceFactory(), requiredSDLVulkanLayers};

    while (window.GetShouldContinue())
    {
        window.Update();
    }

    return 0;
}