#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <wrl.h>

using namespace Microsoft::WRL;

class Window;

class Renderer
{
public:
	Renderer(Window* pWindow);
	~Renderer() = default;

	void SetPipeline();

	void ClearColor(XMFLOAT4 color);
	void Draw(uint32_t indexCount);
	void Present();

	ComPtr<ID3D11Device> GetDevice() const { return mDevice; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return mDeviceContext; }

private:
	void CreateDevice();
	void CreateSwapChain();
	void CreateRenderTargetView();
	void CreateShaders();
	void CreateInputLayout();

private:
	Window* mWindow;
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
	ComPtr<IDXGISwapChain> mSwapChain;
	ComPtr<ID3D11RenderTargetView> mRenderTargetView;

	ComPtr<ID3D11VertexShader> mVertexShader;
	ComPtr<ID3DBlob> mVertexShaderBlob;
	ComPtr<ID3D11PixelShader> mPixelShader;

	ComPtr<ID3D11InputLayout> mInputLayout;
};