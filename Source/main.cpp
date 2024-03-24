#include <Window/Window.h>
#include <Renderer/Renderer.h>

int main()
{
	Window* basicWindow = new Window({ 1280, 720 }, "Plancksoft Game Engine");
	basicWindow->Initialize();

	Renderer* basicRenderer = new Renderer(basicWindow);
	
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
	}

	delete basicWindow;
	printf("Rendering Engine Closed.\n");
	return 0;
}