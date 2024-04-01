#pragma once

#include <Runtime/Core/Core.h>

#include <memory>

class Shader;
class Pipeline;
class Sampler;

class ObjectPipeline
{
public:
	ObjectPipeline();
	ObjectPipeline(const ObjectPipeline&) = delete;
	ObjectPipeline& operator=(const ObjectPipeline&) = delete;
	~ObjectPipeline() = default;

	std::shared_ptr<Shader>& GetVertexShader() { return mVertexShader; }
	std::shared_ptr<Shader>& GetPixelShader() { return mPixelShader; }
	std::shared_ptr<Pipeline>& GetPipeline() { return mPipeline; }
	std::shared_ptr<Sampler>& GetSampler() { return mSampler; }

private:
	std::shared_ptr<Shader> mVertexShader;
	std::shared_ptr<Shader> mPixelShader;
	std::shared_ptr<Pipeline> mPipeline;
	std::shared_ptr<Sampler> mSampler;

};
