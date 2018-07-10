#ifndef SETTINGS_H
#define SETTINGS_H


#include<vector>

#include"floatpoint.h"


//ģ���޸�(fix horrible) 
#define FIX_HORRIBLE_UNION_ALL_TYPE_A    0x01 //����A�������ͼ������ģ���ص����ֵ��ڿ׺�ϸ�������������
#define FIX_HORRIBLE_UNION_ALL_TYPE_B    0x02 //����B��ֻ�����ص����ֵ����ͣ��ڲ�ϸ�ڲ�������
#define FIX_HORRIBLE_EXTENSIVE_STITCHING 0x04 //�㷺ƴ��(extensive stitching)��ʹ�� touching polygon �㷨ȥ��ģ�������еĶ�����������
#define FIX_HORRIBLE_UNION_ALL_TYPE_C    0x08
#define FIX_HORRIBLE_KEEP_NONE_CLOSED    0x10

//gcode����

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

	//�Ĳģ�Filament��
	int filamentDiameter;//�߲ĵ�ֱ��
	int filamentFlow;//���ü��������������ȱʡֵ�İٷֱ�

	int extrusionWidth;//��ѹ���
	int insetCount;//�������
	int downSkinCount;//�±������
	int upSkinCount;//�ϱ������
	int sparseInfillLineDistance;//ϡ������ߵľ���
	int infillOverlap;//����ص�

					  //ȹ��(Skirt) ��ģ�͵ײ���Χ��ӡһЩ�����ߣ���ʹ���� Brim �� Raft ʱȹ����Ч��
	int skirtDistance;//ȹ�ھ���
	int skirtLineCount;//ȹ������Ŀ��ȹ���ߵ�Ȧ��
	int skirtMinLength;//ȹ���ߵ���С����

					   //�س�(Retraction)
	int retractionAmount;//�س���
	int retractionAmountExtruderSwitch;//�س�����ѹ����
	int retractionSpeed;//�س���ٶ�
	int retractionMinimalDistance;//�س���С����
	int minimalExtrusionBeforeRetraction;//�س���С��ѹ���ȣ���ֹ�س�ǰ���������С������һ��˿�ڼ������з���Ħ������ϸ�������ʻǰ��������С�ڸó��ȣ���ô�㲻��س顣
	int enableCombing;//ʹ����·:�Ƿ����� �ô�ӡ���ڿ�ʻ֮ǰ����һ�£���ֹ�������С��
	int enableOozeShield;//ʹ���ⲿ��©������
	int multiVolumeOverlap;//�����ص�

	int initialSpeedupLayers;
	int initialLayerSpeed;
	int printSpeed;//��ӡ�ٶȣ���ӡʱ��ͷ���ƶ��ٶ�
	int infillSpeed;//����ٶȣ����ٿ�������ʱ�䣬����Ӱ��Ч��
	int moveSpeed;//�ƶ��ٶ�
	int fanFullOnLayerNr;

	//֧�ţ�Support��
	//Support material
	int supportAngle;//����֧�ŵ����սǶ�
	int supportEverywhere;//����֧�ţ�ģ���ڲ������ղ���Ҳ�Ὠ��֧��
	int supportLineDistance;
	int supportXYDistance;//X/Y ���루X/Y distance)��֧�Ų�����ˮƽ����ľ��롣Ϊ��ֹ֧�ź�ģ��ճ��һ������á�
	int supportZDistance;//Z ���루Z distance����֧�Ų����ڴ�ֱ����ľ��롣̫С��ʹ��ģ�ͺ�֧��ճ��̫�������԰��룬̫���˻����֧��Ч�����á�
	int supportExtruder;

	//Cool settings ��ȴ
	int minimalLayerTime;//��ӡһ�����С��ȴʱ��
	int minimalFeedrate;//��С�����ٶ�
	int coolHeadLift;//����ȫ�ٸ߶ȣ�ָ����ĳ���߶� ��ȴ����ȫ�ٴ�
	int fanSpeedMin;//��С�ٶȣ�Ϊ�˵��������ٶ�ȥ��Ͻ��ʹ�ӡ�ٶ���ȴ����ӡ��Ϊ����ȴ�������ٶȿ��Դﵽ���ٶ����ޡ�\ ���û��ѡ����ȴͷ������cool head lift),��ô��ʹ�ò��ӡʱ�������С���ӡʱ��Ҳ����ν�������ѡ����ȴͷ��������ô��ӡ����ͷ���ƶ����Աߵȴ�һ�ᣬֱ�����ĵ�����С��ӡʱ�䣬Ȼ�������ӡ
	int fanSpeedMax;//����ٶ�

					//�׵�(Raft)������ 3D ģ�������ȴ�ӡһ���и߶ȵĻ��������Ա�֤�ι̵�ճ���ȴ��ϣ���Ҳ��̫����ȥ��
					//Raft settings
	int raftMargin;//������ȣ������������ʹ�õ�����������������С��ӡ����
	int raftLineSpacing;//������ࣺ��ӡ�׵�ʱ������֮��ľ��룬���Կ��Ƶ׵�����̶ܳ�
	int raftBaseThickness;//�������ȣ���ײ�ĺ�ȣ���Ȳ���̫�󣬷��������ȡ����
	int raftBaseLinewidth;//�������߿�
	int raftInterfaceThickness;//�ӿڲ��ȣ������ϲ�ĺ��
	int raftInterfaceLinewidth;//�ӿڲ��߿������ӿڲ������Ŀ��

	FMatrix3x3 matrix;
	IntPoint objectPosition;
	int objectSink;

	int fixHorrible;//ģ���޸���
	int spiralizeMode;//����ģʽ��
	int gcodeFlavor;//gcode���ͣ�

	IntPoint extruderOffset[MAX_EXTRUDERS];//��ѹ��ƫ�ƣ���
	const char* startCode;
	const char* endCode;

	ConfigSettings();
	bool setSetting(const char* key, const char* value);
};


#endif//SETTINGS_H