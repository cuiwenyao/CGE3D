/*
渲染器::场景
场景包含elements
*/

#pragma once
#include "../Global_config.h"
#include "../global_valuable/Global_valuable.h"
#include "../element/object.h"
#include "../element/camera.h"


class Scene
{
public:
	std::string name;
	Camera* primary_camera;
	std::vector<Object*> objects;
	std::vector<Camera*> cameras;

	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 view_mat = glm::mat4(1.0f);
	glm::mat4 projection_mat = glm::mat4(1.0f);

	Scene();
	void draw();
	void add_object(Object* object, size_t* object_index);//添加一个camera并返回对应的index;
	void add_camera(Camera* camera,size_t * camera_index);//添加一个camera并返回对应的index;
	void set_primary_camera(size_t camera_index); // 设置primary_camera，index来自cameras
	void process_input(KEY_TYPE key_type);
	void process_keyboard_input(KEY_TYPE key_type);
	void process_mouse_input();
	void process_mouse_scroll_input();
private:

};