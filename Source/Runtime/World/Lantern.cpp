#include "Lantern.h"

#include <Runtime/Resources/ResourceImporter.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>

#include <Runtime/Graphics/GraphicsManager.h>

Lantern::Lantern()
{
	mMesh = std::make_shared<Mesh>();
	mBaseColor = std::make_shared<TextureResource>();
	mEmmisive = std::make_shared<TextureResource>();
	mNormal = std::make_shared<TextureResource>();

	ResourceImporter::ReadStaticMeshFile(R"(D:\Projects\glTF-Sample-Models\2.0\Lantern\glTF\Lantern.gltf)", mMesh);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\Lantern\glTF\Lantern_baseColor.png)", mBaseColor);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\Lantern\glTF\Lantern_emissive.png)", mEmmisive);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\Lantern\glTF\Lantern_normal.png)", mNormal);

	mModelMatrix.World = XMMatrixIdentity();
	mModelMatrix.View = XMMatrixIdentity();
	mModelMatrix.Projection = XMMatrixIdentity();

	GraphicsBufferDesc cbDesc = {};
	cbDesc.ResourceUsage = ResourceUsage::DYNAMIC;
	cbDesc.CPUAccess = BufferCPUAccess::WRITE;
	cbDesc.Usage = BufferUsage::CONSTANT_BUFFER;
	cbDesc.SizeInBytes = sizeof(CBData);
	cbDesc.StructureByteStride = sizeof(XMMATRIX);
	cbDesc.MiscFlags = 0;
	cbDesc.InitialData = &mModelMatrix;

	mModelCB = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(cbDesc);

	mModelData.Position = { 0.0f, 0.0f, 0.0f };
	mModelData.Rotation = { 0.0f, 0.0f, 0.0f };
	mModelData.Scale = { 0.5f, 0.5f, 0.5f };
}

void Lantern::Update()
{
	GameObject::Update();

	mModelData.Rotation.y -= 0.5f;
}
