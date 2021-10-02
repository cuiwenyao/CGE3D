/*
window 
*/

#pragma once
#include "../Global_config.h"
#include "../global_valuable/Global_valuable.h"
#include "../element/camera.h"
#include "../draw/scene.h"
class Window
{
public:
	Camera* camera;
	Scene* scene;
	GLFWwindow* window;
	GLFWmonitor* monitor;
	WINDOW_MODE window_mode;
	WINDOW_STATUS window_status;
	std::string window_name;
	int window_width;
	int window_height;
	bool first_mouse;

	Window(std::string window_name, 
		int window_width,
		int window_height,
		WINDOW_MODE window_mode);

	void update();
	void draw();
	void make_context_current();
	void generate_glfw_window();
	void change_window_mode(WINDOW_MODE new_window_mode);
	void change_window_size(int window_width, int window_height);
	void change_window_title(const char* new_title);
	void active_window();
	void inactive_window();
	void close_window();
	void processInput();
	void process_keyboard_input();
	void process_mouse_input();
	void process_mouse_scroll_input();
	void attach_scene(Scene* scene);

private:

};