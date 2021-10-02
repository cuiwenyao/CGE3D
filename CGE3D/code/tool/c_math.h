#pragma once
//事实证明这种方式可行
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
	//整型
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


	//向量运算函数
	//vecf3
	//取反
	vecf3 negate(const vecf3& v1);
	//取模
	float length(const vecf3& v1);
	//单位化
	vecf3 normalizing(const vecf3& v1);
	//点乘
	float dot(const vecf3& v1, const vecf3& v2);
	//叉乘
	vecf3 cross(const vecf3& v1, const vecf3& v2);
	//获取向量夹角余弦值
	float getcos(const vecf3& v1, const vecf3& v2);
	//获取向量夹角余弦值
	float getsin(const vecf3& v1, const vecf3& v2);

	//matf3
	//取反
	vecf3 negate(const matf3& m1);
	//取模
	float length(const matf3& m1);
	//单位化
	vecf3 normalizing(const matf3& m1);

}

