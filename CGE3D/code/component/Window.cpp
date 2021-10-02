#pragma once
#include "Window.h"
#include <Windows.h>


Window::Window(std::string window_name,
	int window_width,
	int window_height,
	WINDOW_MODE window_mode)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window_name = window_name;
	this->window_width = window_width;
	this->window_height = window_height;
	this->window_mode = window_mode;
	this->first_mouse = true;
	this->generate_glfw_window();
	this->active_window();
	this->make_context_current();
	this->update();
	glEnable(GL_DEPTH_TEST);
}

//更新窗口信息 窗口有所变化之后都要调用该函数
void Window::update()
{
	if (this->window_status==WINDOW_CLOSED)
		return;
	int pre_wid = this->window_width;
	int pre_hei = this->window_height;
	glfwGetFramebufferSize(this->window, &this->window_width, &this->window_height);
	glViewport(0, 0, this->window_width, this->window_height);
	if(pre_hei!=this->window_height||pre_wid!=this->window_width)
		std::cout << this->window_width <<" "<< this->window_height << std::endl;
}
//绘制窗口
void Window::draw()
{
	while (Global_valuable::WINDOW_NUM)
	{
		this->processInput();
		if (!(this->window_status == WINDOW_ACTIVE))
			continue;

		this->scene->draw();

		//先将绘制好的图像显示出来再清空屏幕
		glfwSwapBuffers(this->window);
		glfwPollEvents();

		//if (Global_valuable::DELTA_FRAME_TIME < (1 / WINDOW_MAX_FPS))
			//Sleep(((1 / WINDOW_MAX_FPS)- Global_valuable::DELTA_FRAME_TIME));
		//std::cout <<"fps: "<< 1 / Global_valuable::DELTA_FRAME_TIME << std::endl;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
}
void Window::make_context_current()
{
	glfwMakeContextCurrent(this->window);
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
}
void Window::generate_glfw_window()
{
	if (window_mode == WINDOW_MODE_WINDOWED)
	{
		this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, window_name.c_str(), NULL, NULL);
	}
	else if (window_mode == WINDOW_MODE_FULLSCREEN)
	{
		this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, window_name.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else if (window_mode == WINDOW_MODE_WINDOWED_FULLSCREEN)
	{
		this->monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(this->monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		this->window_width = mode->width;
		this->window_height = mode->height;
		this->window = glfwCreateWindow(mode->width, mode->height, window_name.c_str(), this->monitor, NULL);
	}
	if (this->window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	else
	{
		Global_valuable::WINDOW_NUM++;
		Global_valuable::WINDOW_WIDTH = this->window_width;
		Global_valuable::WINDOW_HEIGHT = this->window_height;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		this->active_window();
	}
}
void Window::change_window_mode(WINDOW_MODE new_window_mode)
{
	std::cout << "change_window_mode " << this->window_name << "现在还剩下 " << Global_valuable::WINDOW_NUM << "个窗口" << std::endl;
	this->close_window();
	this->window_mode = new_window_mode;
	this->window_status = WINDOW_OPENING;
	this->generate_glfw_window();
	this->make_context_current();
}

void Window::change_window_size(int window_width, int window_height)
{
	this->window_width = window_width;
	this->window_height = window_height;
	glfwSetWindowSize(this->window, window_width, window_height);
}
void Window::change_window_title(const char* new_title)
{
	glfwSetWindowTitle(this->window, "new title");
	std::cout << "glfwSetWindowTitle " << this->window_name <<"现在还剩下 "<<Global_valuable::WINDOW_NUM<<"个窗口" << std::endl;
}
void Window::active_window()
{
	if (this->window_status != WINDOW_CLOSED)
	{
		this->window_status = WINDOW_ACTIVE;
		glfwMakeContextCurrent(this->window);
		std::cout << "active_window " << this->window_name << "现在还剩下 " << Global_valuable::WINDOW_NUM << "个窗口" << std::endl;
	}
}
void Window::inactive_window()
{
	if (this->window_status != WINDOW_CLOSED)
	{
		this->window_status = WINDOW_INACTIVE;
		std::cout << "inactive_window " << this->window_name << "现在还剩下 " << Global_valuable::WINDOW_NUM << "个窗口" << std::endl;
	}

}
void Window::close_window()
{
	if (this->window_status != WINDOW_CLOSED)
	{
		glfwDestroyWindow(this->window);
		this->window_status = WINDOW_CLOSED;
		Global_valuable::WINDOW_NUM--;
		std::cout << "close_window " << this->window_name << "现在还剩下 " << Global_valuable::WINDOW_NUM << "个窗口" << std::endl;
	}
}
void Window::processInput()
{
	Global_valuable::CUR_FRAME_TIME = glfwGetTime();
	Global_valuable::DELTA_FRAME_TIME = Global_valuable::CUR_FRAME_TIME - Global_valuable::LAST_FRAME_TIME;
	Global_valuable::LAST_FRAME_TIME = Global_valuable::CUR_FRAME_TIME;


	this->process_keyboard_input();
	this->process_mouse_input();
	this->process_mouse_scroll_input();

}

void Window::process_keyboard_input()
{
	if (!(this->window))
	{
		std::cout << "error 该窗口不存在" << std::endl;
		return;
	}
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (!(this->window_status == WINDOW_CLOSED))
			this->close_window();
	}
	if (glfwGetKey(this->window, GLFW_KEY_F1) == GLFW_PRESS)
	{
		if (this->window_status != WINDOW_ACTIVE)
			this->active_window();
	}
	if (glfwGetKey(this->window, GLFW_KEY_F2) == GLFW_PRESS)
	{
		if (this->window_status != WINDOW_INACTIVE)
			this->inactive_window();
	}
	if (glfwGetKey(this->window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		this->change_window_title("new title");
	}
	if (glfwGetKey(this->window, GLFW_KEY_F4) == GLFW_PRESS)
	{
		this->change_window_mode(WINDOW_MODE_WINDOWED);
	}
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_W);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_A);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_S);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_D);
	}
	if (glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_Z);
	}
	if (glfwGetKey(this->window, GLFW_KEY_X) == GLFW_PRESS)
	{
		this->scene->process_keyboard_input(KEY_X);
	}
}
void Window::process_mouse_input()
{
	if (!(this->window))
	{
		std::cout << "error 该窗口不存在" << std::endl;
		return;
	}
	Global_valuable::LAST_MOUSE_X = Global_valuable::CUR_MOUSE_X;
	Global_valuable::LAST_MOUSE_Y = Global_valuable::CUR_MOUSE_Y;
	glfwGetCursorPos(this->window, &Global_valuable::CUR_MOUSE_X, &Global_valuable::CUR_MOUSE_Y);

	if (this->first_mouse)
	{
		this->first_mouse = false;
		Global_valuable::LAST_MOUSE_X = Global_valuable::CUR_MOUSE_X;
		Global_valuable::LAST_MOUSE_Y = Global_valuable::CUR_MOUSE_Y;
	}
	this->scene->process_mouse_input();
}
void Window::process_mouse_scroll_input()
{
	this->scene->process_mouse_scroll_input();
}
void Window::attach_scene(Scene* scene)
{
	this->scene = scene;
}