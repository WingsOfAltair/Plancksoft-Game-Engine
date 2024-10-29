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

	std::string absolutePath = ResourceImporter::GetAbsolutePath();

	ResourceImporter::ReadStaticMeshFile((std::filesystem::path(absolutePath) / "Resources/DamagedHelmet.gltf").string(), mMesh);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Default_albedo.jpg").string(), mBaseColor);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Default_emissive.jpg").string(), mEmmisive);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Default_normal.jpg").string(), mNormal);

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
