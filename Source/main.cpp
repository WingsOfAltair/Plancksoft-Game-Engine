#include <Window/Window.h>
#include <Renderer/RendererManager.h>

#include <Object/Object.h>
#include <Object/Camera.h>

#include <vector>

std::vector<VertexData> vertices =
{
	{ {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f } },
	{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f } },
	{ {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f } },
	{ {0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f } },

	{ {-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f } },
	{ {-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f } },
	{ {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f } },
	{ {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 1.0f } },
};	 

std::vector<uint32_t> indices = {
	// Front face
   0, 1, 2,
   0, 2, 3,

   // Back face
   4, 6, 5,
   4, 7, 6,

   // Top face
   1, 5, 6,
   1, 6, 2,

   // Bottom face
   0, 3, 7,
   0, 7, 4,

   // Left face
   3, 2, 6,
   3, 6, 7,

   // Right face
   0, 4, 5,
   0, 5, 1
};

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

	Camera* basicCamera = new Camera({ 0.0f, 0.0f, 3.0f }, XMINT2(1280,720));

	Object* cube = new Object(vertices, indices);
	objects.push_back(cube);

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