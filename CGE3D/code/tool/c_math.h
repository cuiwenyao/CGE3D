#pragma once
//��ʵ֤�����ַ�ʽ����
namespace CM
{
	//float
	typedef struct 
	{
		float x;
		float y;
	}vecf2;
	typedef struct VECF3 
	{
		float x;
		float y;
		float z;
		struct VECF3();
		struct VECF3(float f1);
		struct VECF3(float f1, float f2, float f3);
	}vecf3;
	typedef struct VECF4
	{
		float x;
		float y;
		float z;
		float w;
		struct VECF4();
		struct VECF4(float f1);
		struct VECF4(const vecf3&v1, float f1);
	}vecf4;
	typedef struct
	{
		vecf2 x;
		vecf2 y;
	}matf2;
	typedef struct MAT_F3
	{
		vecf3 x;
		vecf3 y;
		vecf3 z;
	}matf3;
	typedef struct
	{
		vecf4 x;
		vecf4 y;
		vecf4 z;
		vecf4 w;
	}matf4;
	//����
	typedef struct
	{
		int x;
		int y;
	}veci2;
	typedef struct
	{
		int x;
		int y;
		int z;
	}veci3;
	typedef struct
	{
		int x;
		int y;
		int z;
		int w;
	}veci4;
	typedef struct
	{
		veci2 x;
		veci2 y;
	}mati2;
	typedef struct
	{
		veci3 x;
		veci3 y;
		veci3 z;
	}mati3;
	typedef struct
	{
		veci4 x;
		veci4 y;
		veci4 z;
		veci4 w;
	}mati4;


	//�������㺯��
	//vecf3
	//ȡ��
	vecf3 negate(const vecf3& v1);
	//ȡģ
	float length(const vecf3& v1);
	//��λ��
	vecf3 normalizing(const vecf3& v1);
	//���
	float dot(const vecf3& v1, const vecf3& v2);
	//���
	vecf3 cross(const vecf3& v1, const vecf3& v2);
	//��ȡ�����н�����ֵ
	float getcos(const vecf3& v1, const vecf3& v2);
	//��ȡ�����н�����ֵ
	float getsin(const vecf3& v1, const vecf3& v2);

	//matf3
	//ȡ��
	vecf3 negate(const matf3& m1);
	//ȡģ
	float length(const matf3& m1);
	//��λ��
	vecf3 normalizing(const matf3& m1);

}

