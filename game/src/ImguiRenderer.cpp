
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_vulkan.h>

#include "ImguiRenderer.h"

ImguiRenderer::ImguiRenderer(SDLWindow &sdlWindow, OpenTrainSimulator::Graphics::RenderDevice& renderDevice) :
    _sdlWindow{sdlWindow},
    _renderDevice{renderDevice}
{
    //1: create descriptor pool for IMGUI
    // the size of the pool is very oversize, but it's copied from imgui demo itself.
    VkDescriptorPoolSize pool_sizes[] =
    {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    _descriptorPool = _renderDevice.CreateDescriptorPool(pool_sizes, std::size(pool_sizes));

    ImGui::CreateContext();

    ImGui_ImplSDL3_InitForVulkan(_sdlWindow.GetWindow());

    ImGui_ImplVulkan_InitInfo initInfo{};
    initInfo.Instance = _renderDevice.GetVkInstance();
    initInfo.PhysicalDevice = _renderDevice.GetVkPhysicalDevice();
    initInfo.Device = _renderDevice.GetVkDevice();
    initInfo.Queue = _renderDevice.GetVkQueue();
    initInfo.DescriptorPool = _descriptorPool;
    initInfo.MinImageCount = 3;
    initInfo.ImageCount = 3;
    ImGui_ImplVulkan_Init(&initInfo);

}

ImguiRenderer::~ImguiRenderer()
{
    vkDeviceWaitIdle(_renderDevice.GetVkDevice());
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ImguiRenderer::BeginFrame()
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
}

void ImguiRenderer::Render()
{
    //ImGui::ShowDemoWindow();

    auto commandBuffer = _renderDevice.CreateCommandBuffer();

    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer, nullptr);

}

void ImguiRenderer::EndFrame()
{
    ImGui::EndFrame();
}
