#include <Window/Window.h>
#include <Renderer/RendererManager.h>

#include <Object/Object.h>
#include <Object/Camera.h>
#include <Object/ObjectTypes/Cube.h>		

int main()
{
	std::vector<Object*> objects;
	Window* basicWindow = new Window({ 1280, 720 }, "Plancksoft Game Engine");
	printf("Initializing window...\n");
	basicWindow->Initialize();
	printf("Window initialized.\n");

	printf("Creating Renderer...\n");
	Renderer* basicRenderer = RendererManager::CreateRenderer(basicWindow);
	printf("Renderer created.\n");

	Camera* basicCamera = new Camera({ 0.0f, 0.0f, 3.0f }, { basicWindow->GetSize().X, basicWindow->GetSize().Y });

	Cube* cubeProp = new Cube();
	objects.push_back(cubeProp);

	bool first = true;

	while (basicWindow->IsVisible())
	{
		if (first)
			printf("Attempting to Run Rendering Engine...\n");
		basicWindow->Run();
		if (first) {
			printf("Running Rendering Engine Successfully...\n");
			first = false;
		}
		basicRenderer->ClearColor({ 0.5f, 0.2f, 0.6f, 1.0f });

		basicCamera->HandleInputs(basicWindow->GetWindowHandler());
		basicCamera->UpdateMatrix();

		basicRenderer->SetPipeline();

		for (auto& object : objects)
		{
			object->SetProps();
			object->Update();
			object->UpdateMatrix(basicCamera->GetViewMatrix(), basicCamera->GetProjectionMatrix());
			basicRenderer->Draw(object->GetIndexCount());
		}

		basicRenderer->Present();
	}

	delete basicCamera;
	delete basicWindow;
	delete basicRenderer;

	printf("Rendering Engine Closed.\n");
	return 0;
}