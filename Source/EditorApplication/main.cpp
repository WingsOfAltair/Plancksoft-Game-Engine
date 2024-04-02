#include <Runtime/Application/Application.h>

#include <Runtime/Graphics/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/Application/ApplicationManager.h>
#include <Runtime/Graphics/Command/CommandList.h>

#include <Runtime/World/ObjectPipeline.h>

#include <Runtime/World/Helmet.h>
#include <Runtime/World/Lantern.h>	
#include <Runtime/World/Fox.h>

#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
std::vector<std::shared_ptr<GameObject>> objects;

struct LightCBData
{
	XMFLOAT3 ambientColor;
	float ambientIntensity;

	XMFLOAT3 lightColor;
	float lightIntensity;
	XMFLOAT3 lightPosition;
};

int main()
{
	auto app = ApplicationManager::GetInstance().GetApplication();
	auto camera = CameraManager::GetInstance().GetCamera();

	auto pipelineObject = std::make_shared<ObjectPipeline>();

	auto helmet = std::make_shared<Helmet>();
	objects.push_back(helmet);
	auto lantern = std::make_shared<Lantern>();
	objects.push_back(lantern);		 
	auto fox = std::make_shared<Fox>();
	objects.push_back(fox);

	LightCBData lightData = {};
	lightData.ambientColor = XMFLOAT3(1.0f, 1.0f, 1.0f);
	lightData.ambientIntensity = 0.3f;
	lightData.lightColor = { 0.3f, 0.7f, 0.2f };
	lightData.lightIntensity = 1.0f;
	lightData.lightPosition = { 0.0f, 0.0f, 0.0f };

	GraphicsBufferDesc lightDesc = {};
	lightDesc.ResourceUsage = ResourceUsage::DYNAMIC;
	lightDesc.CPUAccess = BufferCPUAccess::WRITE;
	lightDesc.Usage = BufferUsage::CONSTANT_BUFFER;
	lightDesc.SizeInBytes = sizeof(LightCBData);
	lightDesc.StructureByteStride = sizeof(LightCBData);
	lightDesc.MiscFlags = 0;
	lightDesc.InitialData = &lightData;

	auto lightCB = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(lightDesc);


	while (app->IsRunning())
	{
		app->Run();
		camera->UpdateViewMatrix();
		camera->HandleInputs(WindowManager::GetInstance().GetWindow()->GetWindowHandle());

		app->GetCommandList()->BindPipeline(pipelineObject->GetPipeline());

		if(glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_R) == GLFW_PRESS)
			lightData.lightPosition = camera->GetPosition();
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_1) == GLFW_PRESS)
			lightData.lightColor = { 1.0f, 0.0f, 0.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_2) == GLFW_PRESS)
			lightData.lightColor = { 0.0f, 1.0f, 0.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_3) == GLFW_PRESS)
			lightData.lightColor = { 0.0f, 0.0f, 1.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_5) == GLFW_PRESS)
			lightData.lightColor = { 1.0f, 1.0f, 1.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_6) == GLFW_PRESS)
			lightData.lightColor = { 0.0f, 0.0f, 0.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_7) == GLFW_PRESS)
			lightData.lightColor = { 1.0f, 1.0f, 0.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_8) == GLFW_PRESS)
			lightData.lightColor = { 0.0f, 1.0f, 1.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_9) == GLFW_PRESS)
			lightData.lightColor = { 1.0f, 0.0f, 1.0f };
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_F1) == GLFW_PRESS)
			pipelineObject->GetPipeline()->SetPrimitiveMode(PrimitiveMode::TriangleList);
		if (glfwGetKey(WindowManager::GetInstance().GetWindow()->GetWindowHandle(), GLFW_KEY_F2) == GLFW_PRESS)
			pipelineObject->GetPipeline()->SetPrimitiveMode(PrimitiveMode::LineList);
			
		for (auto& object : objects)
		{
			object->Update();

			app->GetCommandList()->BindVertexBuffer({ object->GetMesh()->GetPositionBuffer(), object->GetMesh()->GetTexCoordBuffer(), object->GetMesh()->GetNormalBuffer()});
			app->GetCommandList()->BindIndexBuffer({ object->GetMesh()->GetIndexBuffer() });


			app->GetCommandList()->UpdateDynamicBuffer(object->GetModelCB(), &object->GetModelMatrix(), sizeof(CBData));
			app->GetCommandList()->UpdateDynamicBuffer(lightCB, &lightData, sizeof(LightCBData));
			app->GetCommandList()->BindResources({ object->GetBaseColor()->GetTextureView(), object->GetEmmisive()->GetTextureView(), object->GetNormal()->GetTextureView()}, {pipelineObject->GetSampler()}, { lightCB }, ShaderStage::PixelShader);
			app->GetCommandList()->BindResources({}, {}, { object->GetModelCB() }, ShaderStage::VertexShader);

			app->GetCommandList()->DrawIndexed((uint32)object->GetMesh()->GetIndices().size(), 0, 0);
		}

		GraphicsManager::GetInstance().GetMainDevice()->ExecuteCommandLists({ app->GetCommandList() });
		GraphicsManager::GetInstance().GetMainDevice()->Present();
	}

	return 0;
}
