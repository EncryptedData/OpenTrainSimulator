
#include <VkBootstrap.h>

#include "RenderDevice.h"

namespace OpenTrainSimulator::Graphics
{
    RenderDevice::RenderDevice(std::function<void(VkInstance, VkSurfaceKHR*)> buildSurface,
        const std::vector<std::string>& requiredExtensions)
    {
        vkb::InstanceBuilder builder;

        for (auto& layer : requiredExtensions)
        {
            builder.enable_extension(layer.c_str());
        }

        auto builderResult = builder
            .set_app_name("OpenTrainSimulator")
            .set_engine_name("OpenTrainSimulator")
            .set_engine_version(0,0,1)
            .request_validation_layers()
            .use_default_debug_messenger()
            .build();

        if (!builderResult)
        {
            throw std::runtime_error("Failed to init Vulkan");
        }

        vkb::Instance vkbInstance = builderResult.value();
        _instance = vkbInstance.instance;

        VkSurfaceKHR surface;
        buildSurface(_instance, &surface);

        vkb::PhysicalDeviceSelector selector{vkbInstance};
        auto selectorResult = selector
            .set_surface(surface)
            .set_minimum_version(1, 1)
            .select();

        if (!selectorResult)
        {
            throw std::runtime_error("Failed to select Vulkan Device");
        }

        const vkb::PhysicalDevice& vkbPhysicalDevice = selectorResult.value();
        _physicalDevice = vkbPhysicalDevice.physical_device;

        vkb::DeviceBuilder deviceBuilder{vkbPhysicalDevice};
        auto deviceBuilderResult = deviceBuilder.build();

        if (!deviceBuilderResult)
        {
            throw std::runtime_error("Failed to build VkDevice");
        }

        const vkb::Device& vkbDevice = deviceBuilderResult.value();
        _device = vkbDevice.device;

        auto vkbQueueRequestResult = vkbDevice.get_queue(vkb::QueueType::graphics);
        if (!vkbQueueRequestResult)
        {
            throw std::runtime_error("Failed to request Graphics queue");
        }

        _graphicsQueue = vkbQueueRequestResult.value();
    }

    RenderDevice::~RenderDevice()
    {
    }
}
