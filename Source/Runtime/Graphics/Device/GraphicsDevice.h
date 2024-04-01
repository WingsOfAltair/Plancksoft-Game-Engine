#pragma once

#include <memory>
#include <vector>

#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace Microsoft::WRL;
using namespace DirectX;

class GraphicsDeviceObject;
class Swapchain;
class Framebuffer;
class Texture;
class TextureView;
class Shader;
class Pipeline;
class Sampler;
class CommandList;
class GraphicsBuffer;
class ResourceLayout;

struct SwapchainDesc;
struct FramebufferDesc;
struct TextureDesc;
struct TextureViewDesc;
struct ShaderDesc;
struct PipelineDesc;
struct SamplerDesc;
struct CommandListDesc;
struct GraphicsBufferDesc;
struct ResourceLayoutDesc;

class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
{
public:
	GraphicsDevice();
	~GraphicsDevice() = default;


	std::shared_ptr<Swapchain> CreateSwapchain(const SwapchainDesc& desc);
	std::shared_ptr<Framebuffer> CreateFramebuffer(const FramebufferDesc& desc);
	std::shared_ptr<Texture> CreateTexture(const TextureDesc& desc);
	std::shared_ptr<TextureView> CreateTextureView(const TextureViewDesc& desc);
	std::shared_ptr<Shader> CreateShader(const ShaderDesc& desc);
	std::shared_ptr<Pipeline> CreatePipeline(const PipelineDesc& desc);
	std::shared_ptr<Sampler> CreateSampler(const SamplerDesc& desc);
	std::shared_ptr<CommandList> CreateCommandList();
	std::shared_ptr<GraphicsBuffer> CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
	std::shared_ptr<ResourceLayout> CreateResourceLayout(const ResourceLayoutDesc& desc) {}

	ComPtr<ID3D11Device>& GetD3D11Device() noexcept { return mD3D11Device; }
	ComPtr<ID3D11DeviceContext>& GetD3D11ImmediateContext() noexcept { return mD3D11ImmediateContext; }

	std::shared_ptr<Swapchain>& GetSwapchain() noexcept { return mSwapchain; }

	void ExecuteCommandLists(std::vector<std::shared_ptr<CommandList>> commandLists);
	void Present();
private:
	std::vector<std::shared_ptr<GraphicsDeviceObject>> mDeviceObjects;
	std::shared_ptr<Swapchain> mSwapchain;

	ComPtr<ID3D11Device> mD3D11Device;
	ComPtr<ID3D11DeviceContext> mD3D11ImmediateContext;
};
