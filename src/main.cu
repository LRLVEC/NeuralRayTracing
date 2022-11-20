#include <cstdio>
#define _CUDA
#include <_NBody.h>
#include <_ImGui.h>

int main()
{
	try
	{
		printf("Fuck!\n");
		Window::Window::Data mainWindowData
		{
			"Neural Ray Tracing",
			{{1920, 1080}, /*resizable=*/true, /*fullscreen=*/false}
		};
		GUI::UserInterface ui(mainWindowData);
		OpenGL::NBodyCUDA nBody1(20 * 1, false, String<char>("./"));
		::printf("Num particles1: %d\n", nBody1.particles.particles.length);
		ui.bindMainWindow(&nBody1);

		Window::Window::Data smallWindowData
		{
			"Normal",
			{{400, 400}, /*resizable=*/true, /*fullscreen=*/false}
		};
		Window::Window& w = ui.createWindow(smallWindowData);
		OpenGL::NBodyCUDA nBody2(10 * 1, false, String<char>("./"));
		::printf("Num particles2: %d\n", nBody2.particles.particles.length);
		ui.bindWindow(w, &nBody2);

		ui.mainLoop();
		return 0;
	}
	catch (const std::exception& e)
	{
		printf("%s", e.what());
		return 0;
	}
}