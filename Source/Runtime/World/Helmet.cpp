#include "Helmet.h"

#include <Runtime/Resources/ResourceImporter.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>

#include <Runtime/Graphics/GraphicsManager.h>

Helmet::Helmet()
{
	mMesh = std::make_shared<Mesh>();
	mBaseColor = std::make_shared<TextureResource>();
	mEmmisive = std::make_shared<TextureResource>();
	mNormal = std::make_shared<TextureResource>();

	ResourceImporter::ReadStaticMeshFile(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\DamagedHelmet.gltf)", mMesh);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_albedo.jpg)", mBaseColor);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_emissive.jpg)", mEmmisive);
	ResourceImporter::ReadTextureFile(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_normal.jpg)", mNormal);

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
	mModelData.Rotation = { 90.0f, 0.0f, 0.0f };
	mModelData.Scale = { 1.0f, 1.0f, 1.0f };
}

void Helmet::Update()
{
	GameObject::Update();

	mModelData.Rotation.y += 0.5f;
}
