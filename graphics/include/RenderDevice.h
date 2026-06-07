#pragma once
#include <functional>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace OpenTrainSimulator::Graphics
{
    class RenderDevice
    {
    public:
        RenderDevice(std::function<void(VkInstance, VkSurfaceKHR*)> buildSurface, const std::vector<std::string>& requiredExtensions);
        ~RenderDevice();

    private:
        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkQueue _graphicsQueue;
    };
}
