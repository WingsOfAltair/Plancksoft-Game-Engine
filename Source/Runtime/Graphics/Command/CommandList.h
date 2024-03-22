#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Graphics/Device/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

#include <DirectXMath.h>
using namespace DirectX;

#include <vector>
#include <memory>

class Framebuffer;
class Pipeline;
class GraphicsBuffer;
class TextureView;
class Sampler;

class CommandList : public GraphicsDeviceObject
{
public:
	CommandList(std::shared_ptr<GraphicsDevice> device);
	virtual ~CommandList() override = default;

	DeviceObjectType GetDeviceType() noexcept override { return DeviceObjectType::CommandList; }

	ComPtr<ID3D11CommandList>& GetCommandList() { return mCommandList; }
	ComPtr<ID3D11DeviceContext>& GetDeferredContext() { return mDeferredContext; }

	void BindFramebuffer(std::shared_ptr<Framebuffer> framebuffer);
	void BindPipeline(std::shared_ptr<Pipeline> pipeline);
	void BindViewport(XMUINT2 windowSize);
	void BindVertexBuffer(const std::vector<std::shared_ptr<GraphicsBuffer>>& vertexBuffer);
	void BindIndexBuffer(std::shared_ptr<GraphicsBuffer> indexBuffer);
	void BindResources(const std::vector<std::shared_ptr<TextureView>>& textureViews, const std::vector<std::shared_ptr<Sampler>>& samplers, const std::vector<std::shared_ptr<GraphicsBuffer>>& constantBuffers, ShaderStage stage);
	void DrawIndexed(uint32 indexCount, uint32 indexOffset, uint32 vertexOffset);
	void ClearBuffer(std::shared_ptr<Framebuffer> framebuffer, XMFLOAT3 color);
	void UpdateDynamicBuffer(std::shared_ptr<GraphicsBuffer> buffer, void* data, uint32 size);
	void ClearCommandList() { mCommandList.Reset(); }

private:
	ComPtr<ID3D11CommandList> mCommandList;
	ComPtr<ID3D11DeviceContext> mDeferredContext;
};
