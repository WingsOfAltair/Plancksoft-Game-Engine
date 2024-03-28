#pragma once

#include <DirectXMath.h>
using namespace DirectX;

struct VertexData
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct WorldData
{
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;
};

struct TransformData
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};