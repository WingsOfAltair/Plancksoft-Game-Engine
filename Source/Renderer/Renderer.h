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

	void CreateDevice();
	void CreateSwapChain();
	void CreateRenderTargetView();

	void ClearColor(XMFLOAT4 color);
	void Present();

private:
	Window* mWindow;
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
	ComPtr<IDXGISwapChain> mSwapChain;
	ComPtr<ID3D11RenderTargetView> mRenderTargetView;
};