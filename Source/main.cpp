#include <Window/Window.h>
#include <Renderer/RendererManager.h>

#include <Object/Object.h>
#include <Object/Camera.h>
#include <Object/ObjectTypes/Cube.h>	
#include <Object/ObjectTypes/Sphere.h>

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

	Camera* basicCamera = new Camera({ 0.0f, 0.0f, 5.0f }, XMINT2(1280,720));

	Cube* cubeProp = new Cube(Cube::Vertices, Cube::Indices, { 0.0f, 0.0f, 0.0f }, { 0.0f, 6.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
	
	Sphere* sphereProp = new Sphere(Sphere::SphereVertices, Sphere::SphereIndices, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	
	objects.push_back(cubeProp);
	objects.push_back(sphereProp);

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
		basicRenderer->ClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

		basicCamera->HandleInputs(basicWindow->GetWindowHandler());
		basicCamera->UpdateMatrix();

		basicRenderer->SetPipeline();

		for (auto& object : objects)
		{
			if (Sphere* sphere = dynamic_cast<Sphere*>(object)) {
				for (auto& vertex : sphere->SphereVertices) {
					vertex.color = { 1.0f, 1.0f, 0.0f, 1.0f };
				}
			}
			object->SetProps();
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