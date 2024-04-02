#include "ResourceImporter.h"

#include <Runtime/Resources/Mesh/Mesh.h>
#include <Runtime/Resources/Texture/TextureResource.h>

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void ResourceImporter::ReadStaticMeshFile(const std::string& absolutePath, std::shared_ptr<Mesh> mesh)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(absolutePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		DEV_LOG(TE_FATAL, "ResourceImporter", "Failed to load mesh file: %s", importer.GetErrorString());
		return;
	}

	aiMesh* pMesh;

	if (scene->HasMeshes())
		pMesh = scene->mMeshes[0];

	// If mesh has positions, create position and index buffer
	if (pMesh->HasPositions()) {
		mesh->GetPositions().resize(pMesh->mNumVertices);
		for (int i = 0; i < pMesh->mNumVertices; i++)
			mesh->GetPositions()[i] = { pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z };

		for (int i = 0; i < pMesh->mNumFaces; i++)
		{
			aiFace face = pMesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
				mesh->GetIndices().push_back(face.mIndices[j]);
		}
	}

	// If mesh has texture coordinates, create texture coordinate buffer
	if (pMesh->HasTextureCoords(0))
	{
		mesh->GetTexCoords().resize(pMesh->mNumVertices);
		for (int i = 0; i < pMesh->mNumVertices; i++)
			mesh->GetTexCoords()[i] = { pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y };
	}

	// If mesh has normals, create normal buffer
	if (pMesh->HasNormals())
	{
		mesh->GetNormals().resize(pMesh->mNumVertices);
		for (int i = 0; i < pMesh->mNumVertices; i++)
			mesh->GetNormals()[i] = { pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z };
	}

	// If mesh has tangents, create tangent buffer
	if (pMesh->HasTangentsAndBitangents())
	{
		mesh->GetTangents().resize(pMesh->mNumVertices);
		for (int i = 0; i < pMesh->mNumVertices; i++)
			mesh->GetTangents()[i] = { pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z };
	}

	// If mesh has bitangents, create bitangent buffer
	if (pMesh->HasTangentsAndBitangents())
	{
		mesh->GetBinormals().resize(pMesh->mNumVertices);
		for (int i = 0; i < pMesh->mNumVertices; i++)
			mesh->GetBinormals()[i] = { pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z };
	}

	mesh->AllocateVertex();
	mesh->AllocateIndex();
}

void ResourceImporter::ReadTextureFile(const std::string& absolutePath, std::shared_ptr<TextureResource> texture)
{
	int width, height, channels;
	stbi_uc* data = stbi_load(absolutePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!data)
	{
		DEV_LOG(TE_FATAL, "ResourceImporter", "Failed to load texture file: %s", absolutePath.c_str());
		return;
	}

	texture->SetTexture(data, width, height, channels);
	
	texture->AllocateTexture();

	stbi_image_free(data);
}
