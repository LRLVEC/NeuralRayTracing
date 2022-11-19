#include <cstdio>
#include <renderer.h>

int main()
{
	printf("Fuck!\n");
	OpenGL::OpenGLInit init(4, 5);
	Window::Window::Data winParameters1
	{
		"NBodyCUDA1",
		{
			{800,800},
			true,false
		}
	};
	Window::Window::Data winParameters2
	{
		"NBodyCUDA2",
		{
			{400,400},
			true,false
		}
	};
	

	Window::WindowManager wm(winParameters1);
	wm.createWindow(winParameters2);
	wm.windows[0].data.makeCurrent();
	OpenGL::NBodyCUDA nBody1(20 * 1, false, String<char>("./"));
	::printf("Num particles1: %d\n", nBody1.particles.particles.length);
	wm.init(0, &nBody1);

	wm.windows[1].data.makeCurrent();
	OpenGL::NBodyCUDA nBody2(10 * 1, false, String<char>("./"));
	::printf("Num particles2: %d\n", nBody2.particles.particles.length);
	wm.init(1, &nBody2);
	
	CUDA::OpenGLDeviceInfo intro;
	intro.printInfo();
	init.printRenderer();
	glfwSwapInterval(0);
	FPS fps;
	fps.refresh();
	while (!wm.close())
	{
		wm.pullEvents();
		wm.render();
		wm.swapBuffers();
		fps.refresh();
		::printf("\r%.2lf    ", fps.fps);
		//fps.printFPS(1);
	}
	return 0;
}