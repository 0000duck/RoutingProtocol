//2.Slicer
//����ͨ��������3Dģ������G-code�Ĺ��̽���slicing.
//��CuraEngine�У�Slicerֻ��������С��һ���ִ��룬��������layers��
//ÿ��layer���бպϵ�2D����Ρ���Щ����ε��γ���������
//��һ������һ���и�ƽ��ͬ�������������ཻ���㣬�õ������ƽ���ཻ���߶ξ����������layer�ģ�
//��Щ�и��õ����߶γ�֮Ϊ��linesegment����
//��ʱ��layer����ֻ����һЩ��ɢ���߶Ρ�
//�ڶ���������Щlinesegment���������γɷ�յĶ���Ρ�
//����OptimizedModel�Ѿ�����������������֮��Ĺ�ϵȷ�����ˣ������slice�ٶȱ�úܿ졣
//�ڽ�����slice֮�����Ǿ͵õ��˷�յĶ�������ߣ�
//��Щ���ߣ�Ҫ����Clipper����������һ���Ĵ���Clipper��ֻ�����ڴ���2D�ķ�ն����ģ�͡�
//(Clipper����;��google)��

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

	//���Ż����ļ�����ov���պ�ȣ�thickness���и��Ƭ ��layer
	Slicer(OptimizedVolume* ov,int32_t initial,int32_t thickness,bool keepNoneClosed,bool extensiveStitching);

	//����һ��������p0,p1,p2��ƽ��z���ཻ�ߵĹ���
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
