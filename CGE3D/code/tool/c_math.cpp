#include "c_math.h"
#include <algorithm>

namespace CM
{
	//vecf3
	//���캯��
	VECF3::VECF3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	//���캯��
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
	//���������
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
	//�������㺯��
	//ȡ��
	vecf3 CM::negate(const vecf3& v1)
	{
		return vecf3(0) - v1;
	}
	//ȡģ
	float CM::length(const vecf3& v1)
	{
		return sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	}
	//��λ��
	vecf3 CM::normalizing(const vecf3& v1)
	{
		float length = CM::length(v1);
	}
	//���
	float  CM::dot(const vecf3& v1, const vecf3& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
	//���
	vecf3  CM::cross(const vecf3& v1, const vecf3& v2)
	{
		return vecf3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}
	//��ȡ�����н�����ֵ
	float  CM::getcos(const vecf3& v1, const vecf3& v2)
	{
		return dot(v1, v2) / (length(v1) * length(v2));
	}
	//��ȡ�����н�����ֵ
	float  CM::getsin(const vecf3& v1, const vecf3& v2)
	{
		return sqrt(1 - getcos(v1, v2) * getcos(v1, v2));
	}


	//mat



}