
#include "RenderDevice.h"
#include "SDLWindow.h"

class ImguiRenderer
{
public:
    ImguiRenderer(SDLWindow& sdlWindow, OpenTrainSimulator::Graphics::RenderDevice& renderDevice);
    ~ImguiRenderer();

    void BeginFrame();

    void Render();

    void EndFrame();

private:
    SDLWindow& _sdlWindow;
    OpenTrainSimulator::Graphics::RenderDevice& _renderDevice;
    VkDescriptorPool _descriptorPool;
};