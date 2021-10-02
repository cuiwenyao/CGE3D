/*
本文档是全局的配置文件，包括一些常量的值。
使用者可以通过自行编写外部config.h文件来覆盖本文档中定义的常量的值。

*/

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

//#define USE_EXTERNAL_CONFIG
#ifdef USE_EXTERNAL_CONFIG
#include "config.h"
#endif 

#ifndef SCR_WIDTH
#define SCR_WIDTH 800
#endif

#ifndef SCR_HEIGHT
#define SCR_HEIGHT 600
#endif

#ifndef OPENGL_MAJOR_VERSION
#define OPENGL_MAJOR_VERSION 3
#endif 

#ifndef OPENGL_MINOR_VERSION
#define OPENGL_MINOR_VERSION 3
#endif 

#ifndef WINDOW_NAME
#define WINDOW_NAME "CGE3D"
#endif

#ifndef IS_FULLSCREEN
#define IS_FULLSCREEN 0
#endif

#ifndef WINDOW_MAX_FPS
#define WINDOW_MAX_FPS 30
#endif

#ifndef FAR_PLANE
#define FAR_PLANE 1000.0f
#endif

#ifndef NEAR_PLANE
#define NEAR_PLANE 0.01f
#endif

typedef enum
{
	WINDOW_MODE_FULLSCREEN,
	WINDOW_MODE_WINDOWED,
	WINDOW_MODE_WINDOWED_FULLSCREEN
}WINDOW_MODE;

typedef enum
{
	WINDOW_OPENING,//窗口已打开
	WINDOW_ACTIVE,//窗口已激活
	WINDOW_INACTIVE,//窗口未激活
	WINDOW_CLOSED   //窗口已关闭
}WINDOW_STATUS;

//纹理环绕方式
typedef enum
{
	TEXTURE_SURROUND_REPEAT = 0,
	TEXTURE_SURROUND_MIRRORED_REPEAT = 1,
	TEXTURE_SURROUND_CLAMP_TO_EDGE = 2,
	TEXTURE_SURROUND_CLAMP_TO_BORDER = 3
}TEXTURE_SURROUND;
//纹理过滤方式
typedef enum
{
	TEXTURE_FILTERING_NEAREST = 0,
	TEXTURE_FILTERING_LINEAR = 1
}TEXTURE_FILTERING;
//多级渐远纹理过滤方式
typedef enum
{
	TEXTURE_NEAREST_MIPMAP_NEAREST = 0,
	TEXTURE_LINEAR_MIPMAP_NEAREST = 1,
	TEXTURE_NEAREST_MIPMAP_LINEAR = 2,
	TEXTURE_LINEAR_MIPMAP_LINEAR = 3
}TEXTURE_MIPMAP_FILTERING;
//texture 类型
typedef enum
{
	TEXTURE_TYPE_AMBIENT = 0,
	TEXTURE_TYPE_SPECULAR = 1,
	TEXTURE_TYPE_DIFFUSE = 2
}TEXTURE_TYPE;


typedef enum 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
}Camera_Movement;

typedef enum
{
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7, 
	NUM_8,
	NUM_9,
	NUM_0,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_CAPS,
	KEY_SHIFT,
	KEY_ENTER,
	KEY_CTRL,
	KEY_ESC
}KEY_TYPE;

