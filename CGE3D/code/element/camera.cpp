#include "camera.h"
#include "../global_valuable/Global_valuable.h"

Camera::Camera()
{
	//对于成员变量的初始化一定要放在构造函数中
	this->Position = DEFAULT_POSITION;
	this->Front = DEFAULT_FRONT;
	this->Up = DEFAULT_UP;
	this->WorldUp = DEFAULT_WORLD_UP;
	this->Yaw = DEFAULT_YAW;
	this->Pitch = DEFAULT_PITCH;
	this->MovementSpeed = DEFAULT_SPEED;
	this->MouseSensitivity = DEFAULT_SENSITIVITY;
	this->Zoom = DEFAULT_ZOOM;

	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	//摄像机位置，目标位置，摄像机的上轴
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::process_keyboard_input(Camera_Movement direction)
{
	float velocity = MovementSpeed * Global_valuable::DELTA_FRAME_TIME;
	if (direction == FORWARD)
	{
		Position += Front * velocity;
	}
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}
void  Camera::process_mouse_input()
{
	Yaw += MouseSensitivity * (Global_valuable::CUR_MOUSE_X - Global_valuable::LAST_MOUSE_X);
	Pitch -= MouseSensitivity * (Global_valuable::CUR_MOUSE_Y - Global_valuable::LAST_MOUSE_Y);

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateCameraVectors();
}

void Camera::process_mouse_scroll_input()
{
	Zoom -= (float)(Global_valuable::CUR_MOUSE_S - Global_valuable::LAST_MOUSE_S);
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	this->Front = glm::normalize(front);
	this->Right = glm::normalize(glm::cross(Front, WorldUp)); 
	this->Up = glm::normalize(glm::cross(Right, Front));
}