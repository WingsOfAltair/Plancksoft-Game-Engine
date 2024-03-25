#include "Renderer.h"

#include <Window/Window.h>

#include<stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>

std::string GetProjectDirectory()
{
	std::string fullPath(__FILE__);
	size_t found = fullPath.find_last_of("/\\");
	if (found != std::string::npos)
	{
		std::string projectDir = fullPath.substr(0, found);

		found = projectDir.find_last_of("/\\");
		if (found != std::string::npos)
		{
			return projectDir.substr(0, found + 1);
		}
	}

	return "";
}

std::string ReadHLSLFile(const std::string& fileName)
{
	std::string absolutePath = GetProjectDirectory() + "Shaders\\" + fileName;
	std::ifstream file(absolutePath);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << absolutePath << "\n";
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	return buffer.str();
}

Renderer::Renderer(Window* pWindow) : mWindow(pWindow), mDevice(nullptr), mDeviceContext(nullptr),
mSwapChain(nullptr), mRenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTargetView();
	CreateShaders(); 
	CreateInputLayout();
}

void Renderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1,
		D3D11_SDK_VERSION, mDevice.GetAddressOf(), nullptr, mDeviceContext.GetAddressOf())))
	{
		printf("Failed to create d3d11 device and context.\n");
		abort();
	}
	else
	{
		printf("Successfully created d3d11 device.\n");
	}

}

void Renderer::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferCount = 1;
	swapchainDesc.BufferDesc.Width = mWindow->GetSize().X;
	swapchainDesc.BufferDesc.Height = mWindow->GetSize().Y;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.OutputWindow = mWindow->GetWindowNativeHandler();
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.Windowed = true;

	ComPtr<IDXGIDevice> dxgiDevice;
	mDevice.As(&dxgiDevice);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	ComPtr<IDXGIFactory> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	if (FAILED(dxgiFactory->CreateSwapChain(mDevice.Get(), &swapchainDesc, mSwapChain.GetAddressOf()))) {
		printf("Failed to create swapchain.\n");
		abort();
	}
	else {
		printf("Created swapchain successfully.\n");
	}
}

void Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> colorBuffer;
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(&colorBuffer));

	if (FAILED(mDevice->CreateRenderTargetView(colorBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf())))
	{
		printf("Failed to create render target view!\n");
		abort();
	}
	else {
		printf("Successfully created render target view!\n");
	}
}

void Renderer::CreateShaders()
{
	ComPtr<ID3DBlob> ErrorBlob;
	const std::string pixelShaderCode = ReadHLSLFile("PixelShader.hlsl");
	
	D3DCompile(pixelShaderCode.c_str(), pixelShaderCode.length(), nullptr, nullptr
		, nullptr, "main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &mVertexShaderBlob,
		&ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
			printf("%s", (char*)ErrorBlob->GetBufferPointer());

	if (FAILED(mDevice->CreatePixelShader(mVertexShaderBlob->GetBufferPointer(),
		mVertexShaderBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf())))
	{
		printf("Failed to create pixel shader.\n");
		abort();
	}
	else {
		printf("Successfully created pixel shader.\n");
	}

	const std::string vertexShaderCode = ReadHLSLFile("VertexShader.hlsl");

	D3DCompile(vertexShaderCode.c_str(), vertexShaderCode.length(), nullptr, nullptr,
		nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &mVertexShaderBlob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char*)ErrorBlob->GetBufferPointer());

	if (FAILED(mDevice->CreateVertexShader(mVertexShaderBlob->GetBufferPointer(),
		mVertexShaderBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf())))
	{
		printf("Failed to create vertex shader.\n");
		abort();
	}
	else {
		printf("Successfully created vertex shader.\n");
	}
}

void Renderer::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA, 0
		}, 
		{
			"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};

	mDevice->CreateInputLayout(inputElementDesc, 2, mVertexShaderBlob->GetBufferPointer(),
		mVertexShaderBlob->GetBufferSize(), mInputLayout.GetAddressOf());
}

void Renderer::SetPipeline()
{
	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
	mDeviceContext->PSSetShader(mPixelShader.Get(), nullptr, 0);
	mDeviceContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
	mDeviceContext->IASetInputLayout(mInputLayout.Get());
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)mWindow->GetSize().X;
	viewport.Height = (float)mWindow->GetSize().Y;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	mDeviceContext->RSSetViewports(1, &viewport);
}

void Renderer::ClearColor(XMFLOAT4 color)
{
	float clearColor[] = { color.x, color.y, color.z, color.w };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), clearColor);
}

void Renderer::Draw(uint32_t indexCount)
{
	mDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void Renderer::Present()
{
	mSwapChain->Present(1, 0);
}
