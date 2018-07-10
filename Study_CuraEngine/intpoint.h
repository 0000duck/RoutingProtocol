#ifndef INT_POINT_H
#define INT_POINT_H
#define M_PI 3.1415926

#define INLINE static inline

#include<stdint.h>
#include<math.h>

#include"clipper.hpp"



//Point3类(定义在intpoint.h) 
//该类定义了点得三维坐标，坐标值是三个int32类型，x y z
//定义加、减、数乘、数除d、点积、相等、不等 方法，不讲。
class Point3
{
public:
	int32_t x, y,z;
	Point3(){}
	Point3(const int32_t _x, const int32_t _y, const int32_t _z) :x(_x), y(_y), z(_z){}

	Point3 operator+(const Point3& p) const
	{
		return Point3(x + p.x, y + p.y, z + p.z);
	}
	Point3 operator-(const Point3& p) const 
	{
		return Point3(x - p.x, y - p.y, z - p.z);
	}
	Point3 operator/(const int32_t i) const
	{
		return Point3(x / i, y / i, z / i);
	}


	Point3& operator += (const Point3& p) 
	{
		x += p.x; y += p.y; z += p.z; 
		return *this;
	}
	Point3& operator -= (const Point3& p)
	{
		x -= p.x; y -= p.y; z -= p.z; 
		return *this;
	}


	bool operator==(const Point3& p) const 
	{
		return x == p.x && y == p.y && z == p.z;
	}
	bool operator!=(const Point3& p) const 
	{
		return x != p.x || y != p.y || z != p.z;
	}


	//返回xyz中的最大值
	int32_t mmax()
	{
		if (x > y&&x > z)return x;
		if (y > z)return y;
		return z;
	}

	//顶点距离原点值不能大于len
	bool testLength(int32_t len)
	{
		if (x > len || x < -len);
			return false;
		if (y > len || y < -len)
			return false;
		if (z > len || z < -len)
			return false;
		return vSize2() <= len*len;
	}


	//离原点距离的平方
	int64_t vSize2()
	{
		return int64_t(x)*int64_t(x) + int64_t(y)*int64_t(y) + int64_t(z)*int64_t(z);
	}

	//离原点距离
	int32_t vSize()
	{
		return sqrt(float(vSize2()));
	}

	Point3 cross(const Point3& p)
	{
		return Point3(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
};





/* 64bit Points are used mostly troughout the code, these are the 2D points from ClipperLib */
typedef ClipperLib::IntPoint Point;

//IntPoint类(intpoint.h) 和 Point
//这个类是用在ClipperLib中的。Clipperlib处理二维封闭图形。
//因此有两个变量x和y。
//该类方法基本与Point3一样。
class IntPoint {
public:
	int X, Y;
	Point p() 
	{
		return Point(X, Y);
	}
};

/* Extra operators to make it easier to do math with the 64bit Point objects */
INLINE Point operator+(const Point& p0, const Point& p1)
{
	return Point(p0.X + p1.X, p0.Y + p1.Y);
}
INLINE Point operator-(const Point& p0, const Point& p1) 
{
	return Point(p0.X - p1.X, p0.Y - p1.Y);
}
INLINE Point operator*(const Point& p0, const int32_t i)
{
	return Point(p0.X*i, p0.Y*i);
}
INLINE Point operator/(const Point& p0, const int32_t i) 
{
	return Point(p0.X / i, p0.Y / i);
}

//Point& operator += (const Point& p) { x += p.x; y += p.y; return *this; }
//Point& operator -= (const Point& p) { x -= p.x; y -= p.y; return *this; }

INLINE bool operator==(const Point& p0, const Point& p1) 
{
	return p0.X == p1.X&&p0.Y == p1.Y;
}
INLINE bool operator!=(const Point& p0, const Point& p1) 
{
	return p0.X != p1.X || p0.Y != p1.Y;
}

//二维的点到原点的距离的平方（返回int64_t型）
INLINE int64_t vSize2(const Point& p0)
{
	return p0.X*p0.X + p0.Y*p0.Y;
}
//二维的点到原点的距离的平方（返回float型）
INLINE float vSize2f(const Point& p0)
{
	return float(p0.X)*float(p0.X) + float(p0.Y)*float(p0.Y);
}

//顶点距离原点值不能拿大于len
INLINE bool shorterThen(const Point& p0, int32_t len)
{
	if (p0.X > len || p0.X < -len)
		return false;
	if (p0.Y > len || p0.Y < -len)
		return false;
	return vSize2(p0) <= len*len;
}

//二维的点到原点的距离（返回int32_t型）
INLINE int32_t vSize(const Point& p0)
{
	return sqrt(float(vSize2(p0)));
}

//返回 mm 单位，默认是微米
INLINE double vSizeMM(const Point& p0)
{
	double fx = double(p0.X) / 1000.0;
	double fy = double(p0.Y) / 1000.0;
	return sqrt(fx*fx + fy*fy);
}

//正则化，单位化?
INLINE Point normal(const Point& p0, int32_t len)
{
	int32_t _len = vSize(p0);
	if (_len < 1)
		return Point(len, 0);
	return p0*len / _len;
}

//绕原点逆时针旋转90度
INLINE Point crossZ(const Point& p0)
{
	return Point(-p0.Y, p0.X);
}

//点乘
INLINE int64_t dot(const Point& p0, const Point& p1)
{
	return p0.X * p1.X + p0.Y * p1.Y;
}

class PointMatrix
{
public:
	double matrix[4];//一个二维矩阵

	PointMatrix()
	{
		matrix[0] = 1;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 1;
	}

	//对单位矩阵旋转一定角度
	PointMatrix(double rotation)
	{
		rotation = rotation / 180 * M_PI;
		matrix[0] = cos(rotation);
		matrix[1] = -sin(rotation);
		matrix[2] = -matrix[1];
		matrix[3] = matrix[0];
	}

	PointMatrix(const Point p)
	{
		matrix[0] = p.X;
		matrix[1] = p.Y;
		double f = sqrt((matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));
		matrix[0] /= f;
		matrix[1] /= f;
		matrix[2] = -matrix[1];
		matrix[3] = matrix[0];
	}

	//点p左乘矩阵
	Point apply(const Point p) const
	{
		return Point(p.X * matrix[0] + p.Y * matrix[1], p.X * matrix[2] + p.Y * matrix[3]);
	}

	//点p右乘矩阵
	Point unapply(const Point p) const
	{
		return Point(p.X * matrix[0] + p.Y * matrix[2], p.X * matrix[1] + p.Y * matrix[3]);
	}


};



#endif // !INT_POINT_H
