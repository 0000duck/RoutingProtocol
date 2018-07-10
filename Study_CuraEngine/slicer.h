//2.Slicer
//我们通常都把由3D模型生成G-code的过程叫做slicing.
//在CuraEngine中，Slicer只是数量很小的一部分代码，用于生成layers。
//每个layer都有闭合的2D多边形。这些多边形的形成有两步：
//第一步，用一个切割平面同所有三角形做相交运算，得到和这个平面相交的线段就是属于这个layer的，
//这些切割后得到的线段称之为”linesegment”。
//此时，layer里面只是有一些零散的线段。
//第二步，将这些linesegment连起来，形成封闭的多边形。
//由于OptimizedModel已经将各个相邻三角形之间的关系确立好了，这里的slice速度变得很快。
//在进行完slice之后，我们就得到了封闭的多边形曲线，
//这些曲线，要交给Clipper库来进行下一步的处理。Clipper库只能用于处理2D的封闭多边形模型。
//(Clipper的用途请google)。

#ifndef SLICER_H
#define SLICER_H

#include"optimizedModel.h"
#include"polygon.h"

/*
The Slicer creates layers of polygons from an optimized 3D model.
The result of the Slicer is a list of polygons without any order or structure.
*/

class SlicerSegment
{
public:
	Point start, end;
	int faceIndex;
	bool addedToPolygon;
};

class closePolygonResult
{   //The result of trying to find a point on a closed polygon line. This gives back the point index, the polygon index, and the point of the connection.
	//The line on which the point lays is between pointIdx-1 and pointIdx
public:
	Point intersectionPoint;
	int polygonIdx;
	unsigned int pointIdx;
};

class gapCloserResult
{
public:
	int64_t len;
	int polygonIdx;
	unsigned int pointIdxA;
	unsigned int pointIdxB;
	bool AtoB;
};


class SlicerLayer
{
public:
	std::vector<SlicerSegment>segmentList;
	std::map<int, int>faceToSegmentIndex;

	Polygons polygonList;
	Polygons openPolygonList;

	void makePolygons(OptimizedVolume* ov, bool keepNoneClosed, bool extensiveStitching);

private:
	gapCloserResult findPolygonGapCloser(Point ip0, Point ip1);

	closePolygonResult findPolygonPointClosestTo(Point input);
};


class Slicer
{
public:
	std::vector<SlicerLayer> layers;
	Point3 modelSize, modelMin;

	//把优化过的几何体ov按照厚度（thickness）切割成片 即layer
	Slicer(OptimizedVolume* ov,int32_t initial,int32_t thickness,bool keepNoneClosed,bool extensiveStitching);

	//计算一个三角形p0,p1,p2和平面z的相交线的过程
	SlicerSegment project2D(Point3& p0, Point3& p1, Point3& p2, int32_t z)const
	{
		SlicerSegment seg;
		seg.start.X = p0.x + int64_t(p1.x - p0.x)*int64_t(z - p0.z) / int64_t(p1.z - p0.z);
		seg.start.Y = p0.y + int64_t(p1.y - p0.y) * int64_t(z - p0.z) / int64_t(p1.z - p0.z);
		seg.end.X = p0.x + int64_t(p2.x - p0.x) * int64_t(z - p0.z) / int64_t(p2.z - p0.z);
		seg.end.Y = p0.y + int64_t(p2.y - p0.y) * int64_t(z - p0.z) / int64_t(p2.z - p0.z);
		return seg;
	}

	void dumpSegmentsToHTML(const char* filename);
};


#endif // !SLICER_H
