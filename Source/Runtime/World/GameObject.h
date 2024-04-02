#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resources/Mesh/Mesh.h>
#include <Runtime/Resources/Texture/TextureResource.h>

#include <memory>

#include <Runtime/World/CameraManager.h>

struct CBData
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};

struct ModelData
{
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;
};

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	std::shared_ptr<Mesh>& GetMesh() { return mMesh; }
	std::shared_ptr<TextureResource>& GetBaseColor() { return mBaseColor; }
	std::shared_ptr<TextureResource>& GetEmmisive() { return mEmmisive; }
	std::shared_ptr<TextureResource>& GetNormal() { return mNormal; }

	std::shared_ptr<GraphicsBuffer>& GetModelCB() { return mModelCB; }
	
	CBData& GetModelMatrix() { return mModelMatrix; }
	ModelData& GetModelData() { return mModelData; }

	virtual void Update()
	{
		mModelMatrix.World = XMMatrixTranspose(XMMatrixScaling(mModelData.Scale.x, mModelData.Scale.y, mModelData.Scale.z) * 
			XMMatrixRotationRollPitchYaw(XMConvertToRadians(mModelData.Rotation.x), XMConvertToRadians(mModelData.Rotation.y), XMConvertToRadians(mModelData.Rotation.z)) * 
			XMMatrixTranslation(mModelData.Position.x, mModelData.Position.y, mModelData.Position.z));
		mModelMatrix.View = XMMatrixTranspose(CameraManager::GetInstance().GetCamera()->GetViewMatrix());
		mModelMatrix.Projection = XMMatrixTranspose(CameraManager::GetInstance().GetCamera()->GetProjectionMatrix());
	}

protected:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<TextureResource> mBaseColor;
	std::shared_ptr<TextureResource> mEmmisive;
	std::shared_ptr<TextureResource> mNormal;

	std::shared_ptr<GraphicsBuffer> mModelCB;

	CBData mModelMatrix;
	ModelData mModelData;
};
