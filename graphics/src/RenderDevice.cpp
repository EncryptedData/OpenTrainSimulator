
#include <VkBootstrap.h>

#include "RenderDevice.h"

namespace OpenTrainSimulator::Graphics
{
    RenderDevice::RenderDevice(std::function<void(VkInstance, VkSurfaceKHR*)> buildSurface,
        const std::vector<std::string>& requiredExtensions,
        int windowWidth,
        int windowHeight) :
        _windowWidth{windowWidth},
        _windowHeight{windowHeight}
    {
        InitVulkan(buildSurface, requiredExtensions);
        InitSwapChain();
    }

    RenderDevice::~RenderDevice()
    {
        vkDeviceWaitIdle(_device);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);

        for (auto& descriptorPool : _descriptorPools)
        {
            vkDestroyDescriptorPool(_device, descriptorPool, nullptr);
        }

        vkDestroyDevice(_device, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }

    VkDescriptorPool RenderDevice::CreateDescriptorPool(VkDescriptorPoolSize* poolSizes, uint32_t poolSizesCount)
    {
        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 1000;
        poolInfo.poolSizeCount = poolSizesCount;
        poolInfo.pPoolSizes = poolSizes;

        VkDescriptorPool pool;
        auto result = vkCreateDescriptorPool(_device, &poolInfo, nullptr, &pool);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a Descriptor pool");
        }

        _descriptorPools.emplace_back(pool);

        return pool;
    }

    VkInstance RenderDevice::GetVkInstance() const
    {
        return _instance;
    }

    VkDevice RenderDevice::GetVkDevice() const
    {
        return _device;
    }

    VkPhysicalDevice RenderDevice::GetVkPhysicalDevice() const
    {
        return _physicalDevice;
    }

    VkQueue RenderDevice::GetVkQueue() const
    {
        return _graphicsQueue;
    }

    void RenderDevice::BeginFrame(int windowWidth, int windowHeight)
    {
        UpdateSwapChainIfNeeded(windowWidth, windowHeight);
    }

    VkCommandBuffer RenderDevice::CreateCommandBuffer()
    {
        VkCommandBufferAllocateInfo commandBufferAllocInfo{};
        commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocInfo.pNext = nullptr;
        commandBufferAllocInfo.commandPool = _commandPool;
        commandBufferAllocInfo.commandBufferCount = 1;
        commandBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        VkCommandBuffer commandBuffer;
        if (vkAllocateCommandBuffers(_device, &commandBufferAllocInfo, &commandBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate Vulkan Command Buffer");
        }

        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        commandBufferBeginInfo.pNext = nullptr;
        commandBufferBeginInfo.pInheritanceInfo = nullptr;

        if (vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to begin Vulkan Commadn buffer");
        }


        _commandBuffers.emplace_back(commandBuffer);

        return commandBuffer;
    }

    void RenderDevice::EndFrame()
    {
        for (auto& commandBuffer : _commandBuffers)
        {
            if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to end command buffer");
            }
        }


    }

    void RenderDevice::InitVulkan(std::function<void(VkInstance, VkSurfaceKHR*)>& buildSurface, const std::vector<std::string>& requiredExtensions)
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
            .enable_extension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
            .enable_extension(VK_EXT_SHADER_OBJECT_EXTENSION_NAME)
            .request_validation_layers()
            .use_default_debug_messenger()
            .build();

        if (!builderResult)
        {
            throw std::runtime_error("Failed to init Vulkan");
        }

        vkb::Instance vkbInstance = builderResult.value();
        _instance = vkbInstance.instance;

        buildSurface(_instance, &_surface);

        vkb::PhysicalDeviceSelector selector{vkbInstance};
        auto selectorResult = selector
            .set_surface(_surface)
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

        auto vkbQueueRequestResult = vkbDevice.get_queue_and_index(vkb::QueueType::graphics);
        if (!vkbQueueRequestResult)
        {
            throw std::runtime_error("Failed to request Graphics queue");
        }


        _graphicsQueue = vkbQueueRequestResult.value().first;
        _graphicsQueueIndex = vkbQueueRequestResult.value().second;
    }

    void RenderDevice::InitSwapChain()
    {
        vkb::SwapchainBuilder swapChainBuilder{_physicalDevice, _device, _surface};

        auto swapChainBuilderResult = swapChainBuilder
            .use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(_windowWidth, _windowHeight)
            .build();

        if (!swapChainBuilderResult)
        {
            throw std::runtime_error("Failed to build vulkan swapchain");
        }

        auto vkbSwapChain = swapChainBuilderResult.value();

        _swapChain = vkbSwapChain.swapchain;
        _swapChainImages = vkbSwapChain.get_images().value();
        _swapChainImageViews = vkbSwapChain.get_image_views().value();
        _swapChainFormat = vkbSwapChain.image_format;
    }

    void RenderDevice::DestroySwapChain()
    {
        vkDestroySwapchainKHR(_device, _swapChain, nullptr);

        for (auto& imageView : _swapChainImageViews)
        {
            vkDestroyImageView(_device, imageView, nullptr);
        }

        for (auto& image : _swapChainImages)
        {
            vkDestroyImage(_device, image, nullptr);
        }

        _swapChain = VK_NULL_HANDLE;
        _swapChainImages.clear();
        _swapChainImageViews.clear();
    }

    void RenderDevice::UpdateSwapChainIfNeeded(int windowWidth, int windowHeight)
    {
        if (_windowHeight == windowHeight && _windowWidth == windowWidth)
        {
            return;
        }

        DestroySwapChain();

        _windowHeight = windowHeight;
        _windowWidth = windowWidth;

        InitSwapChain();
    }

    void RenderDevice::InitCommandPool()
    {
        VkCommandPoolCreateInfo commandPoolCreateInfo{};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.pNext = nullptr;
        commandPoolCreateInfo.queueFamilyIndex = _graphicsQueueIndex;
        commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(_device, &commandPoolCreateInfo, nullptr, &_commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan Command Queue");
        }
    }
}
