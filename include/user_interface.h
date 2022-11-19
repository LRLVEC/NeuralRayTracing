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
		UserInterface(Window::Window::Data const& _data);
		// print render gpu infomation
		static void printInfo();
		// create new window
		Window::Window& createWindow(Window::Window::Data const& _data);
		// bind OpenGL class to window
		void bindWindow(Window::Window& _window, OpenGL::OpenGL* _openGL);
		// bind OpenGL class to main window
		void bindMainWindow(OpenGL::OpenGL* _openGL);
		// ui main loop
		void mainLoop();
	};
}