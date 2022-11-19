#pragma once
#include <_Window.h>

namespace NRT
{
	struct UserInterface
	{
		// only one UserInterface instance is allowed
		static UserInterface* __userInterface;
		static OpenGL::OpenGLInit openglInit;
		Window::WindowManager wm;
		Window::Window* mainWindow;

		UserInterface() = delete;
		UserInterface(Window::Window::Data const& _data)
			:
			wm(_data),
			mainWindow(&wm.windows.begin->data)
		{
			if (__userInterface)throw std::runtime_error{ "Cannot construct new UserInterface if there exists one!" };
			__userInterface = this;
			printInfo();
		}
		static void printInfo()
		{
			openglInit.printRenderer();
		}
		void bindMainWindow(OpenGL::OpenGL* _openGL)
		{
			wm.makeCurrent(0);
			wm.init(0, _openGL);
		}
		Window::Window& createWindow(Window::Window::Data const& _data)
		{
			wm.createWindow(_data);
			return wm.windows.end->data;
		}
		void bindWindow(Window::Window& _window, OpenGL::OpenGL* _openGL)
		{
			_window.init(_openGL);
		}
		void mainLoop()
		{
			glfwSwapInterval(0);
			while (!wm.close())
			{
				if (&wm.windows[0].data != mainWindow)
				{
					wm.closeAll();
				}
				wm.pullEvents();
				wm.render();
				wm.swapBuffers();
			}
		}
	};
	UserInterface* UserInterface::__userInterface = nullptr;
	OpenGL::OpenGLInit UserInterface::openglInit = OpenGL::OpenGLInit(4, 5);
}