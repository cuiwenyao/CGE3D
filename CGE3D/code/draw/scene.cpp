#include "scene.h"

Scene::Scene()
{
	;
}

void Scene::draw()
{
	this->projection_mat = glm::perspective(glm::radians(this->primary_camera->Zoom), (float)(Global_valuable::WINDOW_WIDTH) / (float)(Global_valuable::WINDOW_HEIGHT), NEAR_PLANE, FAR_PLANE);
	//this->projection_mat = glm::perspective(glm::radians(this->primary_camera->Zoom), (float)(Global_valuable::WINDOW_WIDTH) / (float)(Global_valuable::WINDOW_HEIGHT), 0.01f, 100.0f);
	this->view_mat = this->primary_camera->GetViewMatrix();
	for (size_t i = 0; i < this->objects.size(); i++)
	{
		this->objects.at(i)->view_mat = this->view_mat;
		this->objects.at(i)->projection_mat = this->projection_mat;
		this->objects.at(i)->draw();
	}
}
void Scene::add_object(Object* object, size_t* object_index)//添加一个camera并返回对应的index;
{
	if (!object)
	{
		std::cout << "error null object" << std::endl;
		return;
	}
	this->objects.push_back(object);
	if (object_index)
	{
		*object_index = this->objects.size() - 1;
	}
}

void  Scene::add_camera(Camera* camera, size_t* camera_index)//添加一个camera并返回对应的index;
{
	if (!camera)
	{
		std::cout << "error null camera" << std::endl;
		return;
	}
	this->cameras.push_back(camera);
	if (camera_index)
	{
		*camera_index = this->cameras.size() - 1;
	}
	//默认将第一个camera设为主cmaera
	if (this->cameras.size() == 1)
	{
		this->set_primary_camera(0);
	}
}
void  Scene::set_primary_camera(size_t camera_index) // 设置primary_camera，index来自cameras
{
	if (camera_index >= this->cameras.size())
	{
		std::cout << "index too large" << std::endl;
		return;
	}
	this->primary_camera = this->cameras.at(camera_index);

}
void  Scene::process_input(KEY_TYPE key_type)
{
	this->process_keyboard_input(key_type);
	this->process_mouse_input();
	this->process_mouse_scroll_input();
}
void  Scene::process_keyboard_input(KEY_TYPE key_type)
{
	switch (key_type)
	{
	case KEY_W:
		this->primary_camera->process_keyboard_input(FORWARD);
		break;
	case KEY_A:
		this->primary_camera->process_keyboard_input(LEFT);
		break;
	case KEY_S:
		this->primary_camera->process_keyboard_input(BACKWARD);
		break;
	case KEY_D:
		this->primary_camera->process_keyboard_input(RIGHT);
		break;
	case KEY_Z:
		this->primary_camera->Position += glm::normalize(this->primary_camera->Front);
		break;
	case KEY_X:
		this->primary_camera->Position -= glm::normalize(this->primary_camera->Front);
		break;
	}
}
void  Scene::process_mouse_input()
{
	this->primary_camera->process_mouse_input();
}
void  Scene::process_mouse_scroll_input()
{
	this->primary_camera->process_mouse_scroll_input();
}