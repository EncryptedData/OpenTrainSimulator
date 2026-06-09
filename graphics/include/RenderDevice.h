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
        RenderDevice(std::function<void(VkInstance, VkSurfaceKHR*)> buildSurface,
            const std::vector<std::string>& requiredExtensions,
            int windowWidth,
            int windowHeight);
        ~RenderDevice();

        VkDescriptorPool CreateDescriptorPool(VkDescriptorPoolSize* poolSizes, uint32_t poolSizesCount);

        VkInstance GetVkInstance() const;

        VkDevice GetVkDevice() const;

        VkPhysicalDevice GetVkPhysicalDevice() const;

        VkQueue GetVkQueue() const;

        void BeginFrame(int windowWidth, int windowHeight);

        VkCommandBuffer CreateCommandBuffer();

        void EndFrame();

    private:
        VkInstance _instance{};
        VkPhysicalDevice _physicalDevice{};
        VkDevice _device{};
        VkQueue _graphicsQueue{};
        uint32_t _graphicsQueueIndex{};
        VkSurfaceKHR _surface{};
        VkSwapchainKHR _swapChain{};
        VkFormat _swapChainFormat{};
        VkCommandPool _commandPool{};
        std::vector<VkImage> _swapChainImages{};
        std::vector<VkImageView> _swapChainImageViews{};
        std::vector<VkDescriptorPool> _descriptorPools{};
        std::vector<VkCommandBuffer> _commandBuffers{};
        int _windowWidth;
        int _windowHeight;

        void InitVulkan(std::function<void(VkInstance, VkSurfaceKHR*)>& buildSurface, const std::vector<std::string>& requiredExtensions);

        void InitSwapChain();
        void DestroySwapChain();
        void UpdateSwapChainIfNeeded(int windowWidth, int windowHeight);
        void InitCommandPool();
    };
}
