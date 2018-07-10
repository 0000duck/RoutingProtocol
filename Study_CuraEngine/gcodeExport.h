#ifndef GCODEEXPORT_H
#define GCODEEXPORT_H

#include<stdio.h>

#include"intpoint.h"
#include"settings.h"

class GCodeExport
{
private:
	FILE* f;
	double extrusionAmount;
	double extrusionPerMM;
	double retractionAmount;
	double extruderSwitchRetraction;
	double minimalExtrusionBeforeRetraction;
	double extrusionAmountAtPreviousRetraction;
	Point3 currentPosition;
	Point extruderOffset[MAX_EXTRUDERS];
	int currentSpeed, retractionSpeed;
	int zPos;
	bool isRetracted;
	int extruderNr;
	int currentFanSpeed;
	int flavor;

	double totalFilament[MAX_EXTRUDERS];

public:
	double totalPrintTime;

	GCodeExport();
	~GCodeExport();

	void replaceTagInStart(const char* tag, const char* replaceValue);

	void setExtruderOffset(int id, Point p);

	void setFlavor(int flavor);
	int getFlavor();

	void setFilename(const char* filename);

	bool isValid();

	void setExtrusion(int layerThickness, int filamentDiameter, int flow);

	void setRetractionSettings(int retractionAmount, int retractionSpeed, int extruderSwitchRetraction, int minimalExtrusionBeforeRetraction);

	void setZ(int z);

	Point getPositionXY();

	int getPositionZ();

	int getExtruderNr();

	double getTotalFilamentUsed(int e);

	double getTotalPrintTime();

	void addComment(const char* comment, ...);

	void addLine(const char* line, ...);

	void resetExtrusionValue();

	void addDelay(double timeAmount);

	void addMove(Point p, int speed, int lineWidth);

	void addRetraction();

	void switchExtruder(int newExtruder);

	void addCode(const char* str);

	void addFanCommand(int speed);

	int getFileSize();
	void tellFileSize();
};






#endif // !GCODEEXPORT_H
