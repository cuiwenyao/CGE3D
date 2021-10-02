#include "c_math.h"
#include <algorithm>

namespace CM
{
	//vecf3
	//构造函数
	VECF3::VECF3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	//构造函数
	VECF3::VECF3(float f1)
	{
		this->x = f1;
		this->y = f1;
		this->z = f1;
	}
	VECF3::VECF3(float f1, float f2, float f3)
	{
		this->x = f1;
		this->y = f2;
		this->z = f3;
	}
	//重载运算符
	vecf3 operator+(const vecf3& v1, const vecf3& v2)
	{
		return VECF3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}
	vecf3 operator+(const vecf3& v1, float a)
	{
		return VECF3(v1.x + a, v1.y + a, v1.z + a);
	}
	vecf3 operator-(const vecf3& v1, const vecf3& v2)
	{
		return VECF3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}
	vecf3 operator-(const vecf3& v1, float a)
	{
		return VECF3(v1.x - a, v1.y - a, v1.z - a);
	}
	//向量运算函数
	//取反
	vecf3 CM::negate(const vecf3& v1)
	{
		return vecf3(0) - v1;
	}
	//取模
	float CM::length(const vecf3& v1)
	{
		return sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	}
	//单位化
	vecf3 CM::normalizing(const vecf3& v1)
	{
		float length = CM::length(v1);
	}
	//点乘
	float  CM::dot(const vecf3& v1, const vecf3& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
	//叉乘
	vecf3  CM::cross(const vecf3& v1, const vecf3& v2)
	{
		return vecf3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}
	//获取向量夹角余弦值
	float  CM::getcos(const vecf3& v1, const vecf3& v2)
	{
		return dot(v1, v2) / (length(v1) * length(v2));
	}
	//获取向量夹角余弦值
	float  CM::getsin(const vecf3& v1, const vecf3& v2)
	{
		return sqrt(1 - getcos(v1, v2) * getcos(v1, v2));
	}


	//mat



}