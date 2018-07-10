#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

#include"gcodeExport.h"
#include"settings.h"
#include"logoutput.h"
#include"modelFile.h"
#include"gettime.h"
#include"optimizedModel.h"
#include"slicer.h"


#define VERSION "13.11"//curaEngine版本

int maxObjectHeight;



void print_usage()
{
	printf("usage: CuraEngine [-h] [-v] [-m 3x3matrix] [-s <settingkey>=<value>] -o <output.gcode> <model.stl>\n");
}

void signal_FPE(int n)
{
	(void)n;
	printf("Arithmetic exception.\n");
	exit(1);
}

//将 stl 文件面片数据传入 PrintObject 的 meshes 中
void processFile(const char* input_filename, ConfigSettings& config, GCodeExport& gcode, bool firstFile)
{
	for (unsigned int n = 1; n < MAX_EXTRUDERS; n++)
	{
		gcode.setExtruderOffset(n, config.extruderOffset[n].p());
	}
	gcode.setFlavor(config.gcodeFlavor);

	double t = getTime();
	log("Loading %s from disk...\n", input_filename);
	SimpleModel* m = loadModel(input_filename, config.matrix);
	if (!m)
	{
		log("Failed to load model:%s\n", input_filename);
		return;
	}
	log("Loaded from disk in %5.3fs\n", timeElapsed(t));
	log("Analyzing and optimizing model...\n");
	OptimizedModel* om = new OptimizedModel(m, Point3(config.objectPosition.X, config.objectPosition.Y, -config.objectSink));
	for (unsigned int v = 0; v < m->volumes.size(); v++)
	{
		log("  Face counts: %i -> %i %0.1f%%\n", (int)m->volumes[v].faces.size(), (int)om->volumes[v].faces.size(), float(om->volumes[v].faces.size()) / float(m->volumes[v].faces.size()) * 100);
		log("  Vertex counts: %i -> %i %0.1f%%\n", (int)m->volumes[v].faces.size() * 3, (int)om->volumes[v].points.size(), float(om->volumes[v].points.size()) / float(m->volumes[v].faces.size() * 3) * 100);
	}
	delete m;
	log("Optimize model %5.3fs \n", timeElapsed(t));
	//om->saveDebugSTL("c:\\models\\output.stl");
	//om->saveDebugSTL("C:\\Users\\asus\\Desktop\\models\\output.stl");


	log("Slicing model...\n");
	vector<Slicer*> slicerList;
	for (unsigned int volumeIdx = 0; volumeIdx < om->volumes.size(); volumeIdx++)
	{
		slicerList.push_back(new Slicer(&om->volumes[volumeIdx], config.initialLayerThickness / 2, config.layerThickness, config.fixHorrible & FIX_HORRIBLE_KEEP_NONE_CLOSED, config.fixHorrible & FIX_HORRIBLE_EXTENSIVE_STITCHING));
		slicerList[volumeIdx]->dumpSegmentsToHTML("C:\\models\\output.html");
		//slicerList[volumeIdx]->dumpSegmentsToHTML("C:\\Users\\asus\\Desktop\\models\\output.html");

	}
    log("Sliced model in %5.3fs\n", timeElapsed(t));

}


int main(int argc, char **argv)
{
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
	//Lower the process priority on linux and mac.
	setpriority(PRIO_PROCESS, 0, 10);
#endif
	signal(SIGFPE, signal_FPE);//浮点指针错误

	GCodeExport gcode;
	ConfigSettings config;

	int fileNr = 0;

	//设置环境
	config.filamentDiameter = 2890;
	config.filamentFlow = 100;
	config.initialLayerThickness = 300;
	config.layerThickness = 100;
	config.extrusionWidth = 400;
	config.insetCount = 2;
	config.downSkinCount = 6;
	config.upSkinCount = 6;
	config.initialSpeedupLayers = 4;
	config.initialLayerSpeed = 20;
	config.printSpeed = 50;
	config.infillSpeed = 50;
	config.moveSpeed = 200;
	config.fanFullOnLayerNr = 2;
	config.skirtDistance = 6000;
	config.skirtLineCount = 1;
	config.skirtMinLength = 0;
	config.sparseInfillLineDistance = 100 * config.extrusionWidth / 20;
	config.infillOverlap = 15;
	config.objectPosition.X = 102500;
	config.objectPosition.Y = 102500;
	config.objectSink = 0;
	config.supportAngle = 68;//修改了一下
	config.supportEverywhere = 1;//修改了一下
	config.supportLineDistance = config.sparseInfillLineDistance;
	config.supportExtruder = -1;
	config.supportXYDistance = 700;
	config.supportZDistance = 150;
	config.retractionAmount = 4500;
	config.retractionSpeed = 45;
	config.retractionAmountExtruderSwitch = 14500;
	config.retractionMinimalDistance = 1500;
	config.minimalExtrusionBeforeRetraction = 100;
	config.enableOozeShield = 0;
	config.enableCombing = 1;
	config.multiVolumeOverlap = 0;

	config.minimalLayerTime = 5;
	config.minimalFeedrate = 10;
	config.coolHeadLift = 1;
	config.fanSpeedMin = 100;
	config.fanSpeedMax = 100;

	config.raftMargin = 5000;
	config.raftLineSpacing = 1000;
	config.raftBaseThickness = 0;
	config.raftBaseLinewidth = 0;
	config.raftInterfaceThickness = 0;
	config.raftInterfaceLinewidth = 0;

	config.spiralizeMode = 0;
	config.fixHorrible = 0;
	config.gcodeFlavor = GCODE_FLAVOR_REPRAP;

	config.startCode =
		"M109 S210     ;Heatup to 210C\n"
		"G21           ;metric values\n"
		"G90           ;absolute positioning\n"
		"G28           ;Home\n"
		"G1 Z15.0 F300 ;move the platform down 15mm\n"
		"G92 E0        ;zero the extruded length\n"
		"G1 F200 E5    ;extrude 5mm of feed stock\n"
		"G92 E0        ;zero the extruded length again\n";
	config.endCode =
		"M104 S0                     ;extruder heater off\n"
		"M140 S0                     ;heated bed heater off (if you have it)\n"
		"G91                            ;relative positioning\n"
		"G1 E-1 F300                    ;retract the filament a bit before lifting the nozzle, to release some of the pressure\n"
		"G1 Z+0.5 E-5 X-20 Y-20 F9000   ;move Z up a bit and retract filament even more\n"
		"G28 X0 Y0                      ;move X/Y to min endstops, so the head is out of the way\n"
		"M84                         ;steppers off\n"
		"G90                         ;absolute positioning\n";

	fprintf(stderr, "Cura_SteamEngine version %s\n", VERSION);
	argv[1] = "-o";
	argc++;
	argv[2] = "Laurana_cura.gcode";//Laurana_cura.gcode
	argc++;
	argv[3] = "Laurana.stl";//Laurana.stl
	argc++;

	for (int argn = 1; argn < argc; argn++)
	{
		char* str = argv[argn];
		if (str[0] == '-')
		{
			for (str++; *str; str++)
			{
				switch (*str)
				{
				case 'h'://显示帮助？
					print_usage();
					exit(1);
				case 'v'://使能够输出 log 信息。（模型载入时间、切片时间等等）？
					verbose_level++;
					break;
				case 'b':
					argn++;
					binaryMeshBlob = fopen(argv[argn], "rb");
					break;
				case 'o':
					argn++;
					gcode.setFilename(argv[argn]);
					if (!gcode.isValid())
					{
						logError("Failed to open %s for output.\n", argv[argn]);
						exit(1);
					}
					break;
				case 's'://输入 key 键对应的 value 值，中间不能有空格。？
				{
					argn++;
					char* valuePtr = strchr(argv[argn], '=');
					if (valuePtr)
					{
						*valuePtr++ = '\0';

						if (!config.setSetting(argv[argn], valuePtr))
							printf("Setting found: %s %s\n", argv[argn], valuePtr);
					}
				}
				break;
				case 'm':
					argn++;
					sscanf(argv[argn], "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
						&config.matrix.m[0][0], &config.matrix.m[0][1], &config.matrix.m[0][2],
						&config.matrix.m[1][0], &config.matrix.m[1][1], &config.matrix.m[1][2],
						&config.matrix.m[2][0], &config.matrix.m[2][1], &config.matrix.m[2][2]);
					break;
				default:
					logError("Unknown option: %c\n", *str);
					break;
				}
			}
		}
		else {
			if (!gcode.isValid())
			{
				logError("No output file specified\n");
				return 1;
			}
			gcode.addComment("Generated with Cura_SteamEngine %s", VERSION);
			processFile(argv[argn], config, gcode, fileNr == 0);
			fileNr++;
		}
	}

	if (gcode.isValid())
	{
		gcode.addFanCommand(0);
		gcode.addRetraction();
		gcode.setZ(maxObjectHeight + 5000);
		gcode.addMove(gcode.getPositionXY(), config.moveSpeed, 0);
		gcode.addCode(config.endCode);
		log("Print time: %d\n", int(gcode.getTotalPrintTime()));
		log("Filament: %d\n", int(gcode.getTotalFilamentUsed(0)));
		log("Filament2: %d\n", int(gcode.getTotalFilamentUsed(1)));

		if (gcode.getFlavor() == GCODE_FLAVOR_ULTIGCODE)
		{
			char numberString[16];
			sprintf(numberString, "%d", int(gcode.getTotalPrintTime()));
			gcode.replaceTagInStart("<__TIME__>", numberString);
			sprintf(numberString, "%d", int(gcode.getTotalFilamentUsed(0)));
			gcode.replaceTagInStart("<FILAMENT>", numberString);
			sprintf(numberString, "%d", int(gcode.getTotalFilamentUsed(1)));
			gcode.replaceTagInStart("<FILAMEN2>", numberString);
		}
	}





}