#include "CommandList.h"

#include <Runtime/Graphics/Device/GraphicsDevice.h>

#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/Sampler/Sampler.h>

#include <Runtime/Graphics/Texture/TextureView.h>

CommandList::CommandList(std::shared_ptr<GraphicsDevice> device)
{
	mOwnerDevice = device;

	DEV_ASSERT(SUCCEEDED(device->GetD3D11Device()->CreateDeferredContext(0, mDeferredContext.GetAddressOf())), "CommandList", "Failed to create deferred context.");
}

void CommandList::BindFramebuffer(std::shared_ptr<Framebuffer> framebuffer)
{
	mDeferredContext->OMSetRenderTargets(1, framebuffer->GetColorTextureView().GetAddressOf(), framebuffer->GetDepthTextureView().Get());
}

void CommandList::BindPipeline(std::shared_ptr<Pipeline> pipeline)
{
	for (auto& shader : pipeline->GetShaders())
	{
		switch (shader->GetShaderType())
		{
		case ShaderType::VERTEX_SHADER:
		{
			mDeferredContext->VSSetShader(shader->GetVertexShader().Get(), nullptr, 0);
			break;
		}
		case ShaderType::PIXEL_SHADER:
		{
			mDeferredContext->PSSetShader(shader->GetPixelShader().Get(), nullptr, 0);
			break;
		}
		default:
		{
			DEV_ASSERT(false, "CommandList", "Invalid shader type.");
			break;
		}
		}
	}

	mDeferredContext->IASetInputLayout(pipeline->GetInputLayoutObject().Get());
	float factor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	mDeferredContext->OMSetBlendState(pipeline->GetBlendObject().Get(), factor, D3D11_APPEND_ALIGNED_ELEMENT);
	mDeferredContext->OMSetDepthStencilState(pipeline->GetDepthStencilObject().Get(), 0);
	mDeferredContext->RSSetState(pipeline->GetRasterizerObject().Get());
	mDeferredContext->IASetPrimitiveTopology(pipeline->GetPrimitiveTopology());
}

void CommandList::BindViewport(XMUINT2 windowSize)
{
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)windowSize.x;
	viewport.Height = (float)windowSize.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	mDeferredContext->RSSetViewports(1, &viewport);
}

void CommandList::BindVertexBuffer(const std::vector<std::shared_ptr<GraphicsBuffer>>& vertexBuffer)
{
	for (uint32 i = 0; i < vertexBuffer.size(); i++)
	{
		uint32 stride = vertexBuffer[i]->GetStructureByteStride();
		uint32 offset = 0;
		mDeferredContext->IASetVertexBuffers(i, 1, vertexBuffer[i]->GetBuffer().GetAddressOf(), &stride, &offset);
	}
}

void CommandList::BindIndexBuffer(std::shared_ptr<GraphicsBuffer> indexBuffer)
{
	mDeferredContext->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void CommandList::BindResources(const std::vector<std::shared_ptr<TextureView>>& textureViews, const std::vector<std::shared_ptr<Sampler>>& samplers, const std::vector<std::shared_ptr<GraphicsBuffer>>& constantBuffers, ShaderStage stage)
{
	ID3D11ShaderResourceView* srvs[16] = {};
	ID3D11SamplerState* samplersStates[16] = {};
	ID3D11Buffer* buffers[16] = {};

	for (uint32 i = 0; i < textureViews.size(); i++)
	{
		srvs[i] = textureViews[i]->GetTextureView().Get();
	}

	for (uint32 i = 0; i < samplers.size(); i++)
	{
		samplersStates[i] = samplers[i]->GetSamplerState().Get();
	}

	for (uint32 i = 0; i < constantBuffers.size(); i++)
	{
		buffers[i] = constantBuffers[i]->GetBuffer().Get();
	}

	switch (stage)
	{
	case ShaderStage::VertexShader:
	{
		mDeferredContext->VSSetShaderResources(0, (uint32)(textureViews.size()), srvs);
		mDeferredContext->VSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->VSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	case ShaderStage::PixelShader:
	{
		mDeferredContext->PSSetShaderResources(0, (uint32)textureViews.size(), srvs);
		mDeferredContext->PSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->PSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	case ShaderStage::ComputeShader:
	{
		mDeferredContext->CSSetShaderResources(0, (uint32)textureViews.size(), srvs);
		mDeferredContext->CSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->CSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	case ShaderStage::GeometryShader:
	{
		mDeferredContext->GSSetShaderResources(0, (uint32)textureViews.size(), srvs);
		mDeferredContext->GSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->GSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	case ShaderStage::HullShader:
	{
		mDeferredContext->HSSetShaderResources(0, (uint32)textureViews.size(), srvs);
		mDeferredContext->HSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->HSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	case ShaderStage::DomainShader:
	{
		mDeferredContext->DSSetShaderResources(0, (uint32)textureViews.size(), srvs);
		mDeferredContext->DSSetSamplers(0, (uint32)samplers.size(), samplersStates);
		mDeferredContext->DSSetConstantBuffers(0, (uint32)constantBuffers.size(), buffers);
		break;
	}
	default:
	{
		DEV_ASSERT(false, "CommandList", "Invalid shader stage.");
		break;
	}
	}
}

void CommandList::DrawIndexed(uint32 indexCount, uint32 indexOffset, uint32 vertexOffset)
{
	mDeferredContext->DrawIndexed(indexCount, indexOffset, vertexOffset);
}

void CommandList::ClearBuffer(std::shared_ptr<Framebuffer> framebuffer, XMFLOAT3 color)
{
	float frameColor[] = { color.x, color.y, color.z, 1.0f };
	mDeferredContext->ClearRenderTargetView(framebuffer->GetColorTextureView().Get(), frameColor);
	mDeferredContext->ClearDepthStencilView(framebuffer->GetDepthTextureView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void CommandList::UpdateDynamicBuffer(std::shared_ptr<GraphicsBuffer> buffer, void* data, uint32 size)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	mDeferredContext->Map(buffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, data, size);
	mDeferredContext->Unmap(buffer->GetBuffer().Get(), 0);
}
