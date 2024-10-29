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

	std::string absolutePath = ResourceImporter::GetAbsolutePath();

	ResourceImporter::ReadStaticMeshFile((std::filesystem::path(absolutePath) / "Resources/Lantern.gltf").string(), mMesh);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Lantern_baseColor.png").string(), mBaseColor);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Lantern_emissive.png").string(), mEmmisive);
	ResourceImporter::ReadTextureFile((std::filesystem::path(absolutePath) / "Resources/Lantern_normal.png").string(), mNormal);

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
