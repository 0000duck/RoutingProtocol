#ifndef SETTINGS_H
#define SETTINGS_H


#include<vector>

#include"floatpoint.h"


//模型修复(fix horrible) 
#define FIX_HORRIBLE_UNION_ALL_TYPE_A    0x01 //类型A：软件试图保留子模型重叠部分的内孔和细节连接完好无损
#define FIX_HORRIBLE_UNION_ALL_TYPE_B    0x02 //类型B：只保留重叠部分的外型，内部细节不做处理
#define FIX_HORRIBLE_EXTENSIVE_STITCHING 0x04 //广泛拼接(extensive stitching)：使用 touching polygon 算法去补模型中所有的洞，运算量大。
#define FIX_HORRIBLE_UNION_ALL_TYPE_C    0x08
#define FIX_HORRIBLE_KEEP_NONE_CLOSED    0x10

//gcode类型

/**
* RepRap flavored GCode is Marlin/Sprinter/Repetier based GCode.
*  This is the most commonly used GCode set.
*  G0 for moves, G1 for extrusion.
*  E values give mm of filament extrusion.
*  Retraction is done on E values with G1. Start/end code is added.
*  M106 Sxxx and M107 are used to turn the fan on/off.
**/
#define GCODE_FLAVOR_REPRAP              0
/**
* UltiGCode flavored is Marlin based GCode.
*  UltiGCode uses less settings on the slicer and puts more settings in the firmware. This makes for more hardware/material independed GCode.
*  G0 for moves, G1 for extrusion.
*  E values give mm^3 of filament extrusion. Ignores the filament diameter setting.
*  Retraction is done with G10 and G11. Retraction settings are ignored. G10 S1 is used for multi-extruder switch retraction.
*  Start/end code is not added.
*  M106 Sxxx and M107 are used to turn the fan on/off.
**/
#define GCODE_FLAVOR_ULTIGCODE           1
/**
* Makerbot flavored GCode.
*  Looks a lot like RepRap GCode with a few changes. Requires MakerWare to convert to X3G files.
*   Heating needs to be done with M104 Sxxx T0
*   No G21 or G90
*   Fan ON is M126 T0 (No fan strength control?)
*   Fan OFF is M127 T0
*   Homing is done with G162 X Y F2000
**/
#define GCODE_FLAVOR_MAKERBOT           2



#define MAX_EXTRUDERS 16


class _ConfigSettingIndex
{
public:
	const char*key;
	int* ptr;

	_ConfigSettingIndex(const char*key,int*ptr):key(key),ptr(ptr){}
};

class ConfigSettings
{
private:
	std::vector<_ConfigSettingIndex> _index;
public:
	int layerThickness;
	int initialLayerThickness;

	//耗材（Filament）
	int filamentDiameter;//线材的直径
	int filamentFlow;//设置挤出塑料量相对于缺省值的百分比

	int extrusionWidth;//挤压宽度
	int insetCount;//插入计数
	int downSkinCount;//下表面计数
	int upSkinCount;//上表面计数
	int sparseInfillLineDistance;//稀疏填充线的距离
	int infillOverlap;//填充重叠

					  //裙摆(Skirt) 在模型底层周围打印一些轮廓线，当使用了 Brim 或 Raft 时裙摆无效。
	int skirtDistance;//裙摆距离
	int skirtLineCount;//裙摆线数目：裙摆线的圈数
	int skirtMinLength;//裙摆线的最小长度

					   //回抽(Retraction)
	int retractionAmount;//回抽量
	int retractionAmountExtruderSwitch;//回抽量挤压开关
	int retractionSpeed;//回抽的速度
	int retractionMinimalDistance;//回抽最小距离
	int minimalExtrusionBeforeRetraction;//回抽最小挤压长度：防止回抽前挤出距离过小而导致一段丝在挤出机中反复摩擦而变细。如果空驶前挤出距离小于该长度，那么便不会回抽。
	int enableCombing;//使能绕路:是否梳理 让打印机在空驶之前梳理一下，防止表面出现小洞
	int enableOozeShield;//使能外部渗漏保护层
	int multiVolumeOverlap;//多体重叠

	int initialSpeedupLayers;
	int initialLayerSpeed;
	int printSpeed;//打印速度：打印时喷头的移动速度
	int infillSpeed;//填充速度：加速可以提升时间，但会影响效果
	int moveSpeed;//移动速度
	int fanFullOnLayerNr;

	//支撑（Support）
	//Support material
	int supportAngle;//生成支撑的悬空角度
	int supportEverywhere;//到处支撑：模型内部的悬空部分也会建立支撑
	int supportLineDistance;
	int supportXYDistance;//X/Y 距离（X/Y distance)：支撑材料在水平方向的距离。为防止支撑和模型粘到一起而设置。
	int supportZDistance;//Z 距离（Z distance）：支撑材料在垂直方向的距离。太小会使得模型和支撑粘的太紧，难以剥离，太大了会造成支撑效果不好。
	int supportExtruder;

	//Cool settings 冷却
	int minimalLayerTime;//打印一层的最小冷却时间
	int minimalFeedrate;//最小进料速度
	int coolHeadLift;//风扇全速高度：指定在某个高度 冷却风扇全速打开
	int fanSpeedMin;//最小速度：为了调整风扇速度去配合降低打印速度冷却。打印机为了冷却而降低速度可以达到的速度下限。\ 如果没有选择冷却头提升（cool head lift),那么即使该层打印时间大于最小层打印时间也无所谓。如果勾选了冷却头提升，那么打印机喷头会移动到旁边等待一会，直到消耗到层最小打印时间，然后回来打印
	int fanSpeedMax;//最大速度

					//底垫(Raft)：会在 3D 模型下面先打印一个有高度的基座，可以保证牢固的粘在热床上，但也不太容易去除
					//Raft settings
	int raftMargin;//额外幅度：增大这个数字使得底座更有力，但会缩小打印区域
	int raftLineSpacing;//线条间距：打印底垫时，线条之间的距离，可以控制底垫的疏密程度
	int raftBaseThickness;//基础层厚度：最底层的厚度，厚度不宜太大，否则后期难取下来
	int raftBaseLinewidth;//基础层线宽
	int raftInterfaceThickness;//接口层厚度：底座上层的厚度
	int raftInterfaceLinewidth;//接口层线宽：底座接口层线条的宽度

	FMatrix3x3 matrix;
	IntPoint objectPosition;
	int objectSink;

	int fixHorrible;//模型修复？
	int spiralizeMode;//螺旋模式？
	int gcodeFlavor;//gcode类型？

	IntPoint extruderOffset[MAX_EXTRUDERS];//挤压的偏移？？
	const char* startCode;
	const char* endCode;

	ConfigSettings();
	bool setSetting(const char* key, const char* value);
};


#endif//SETTINGS_H