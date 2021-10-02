#pragma once
#include "../Global_config.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera();
	glm::mat4 GetViewMatrix();
	void process_keyboard_input(Camera_Movement direction);
	void process_mouse_input();
	void process_mouse_scroll_input();

private:
	const glm::vec3 DEFAULT_POSITION = { 0.0f, 10.0f, 10.0f };
	const glm::vec3 DEFAULT_FRONT = { 0.0f, 0.0f, -1.0f };
	const glm::vec3 DEFAULT_UP = { 0.0f, 1.0f, 0.0f };
	const glm::vec3 DEFAULT_WORLD_UP={ 0.0f, 1.0f, 0.0f };
	const float DEFAULT_YAW = -90;//保证初始直视z州负方向
	const float DEFAULT_PITCH = 0.0f;
	const float DEFAULT_SPEED = 2.5f;
	const float DEFAULT_SENSITIVITY = 0.1f;
	const float DEFAULT_ZOOM = 45.0f;
	
	void updateCameraVectors();
};