#include<stdarg.h>

#include"gcodeExport.h"
//#include "pathOrderOptimizer.h"
#include "settings.h"

#if defined(__APPLE__) && defined(__MACH__)
//On MacOS the file offset functions are always 64bit.
#define off64_t off_t
#define ftello64 ftello
#define fseeko64 fseeko
#endif

GCodeExport::GCodeExport()
	:currentPosition(0,0,0)
{
	extrusionAmount = 0;
	extrusionPerMM = 0;
	retractionAmount = 4.5;
	minimalExtrusionBeforeRetraction = 0.0;
	extrusionAmountAtPreviousRetraction = -10000;
	extruderSwitchRetraction = 14.5;
	extruderNr = 0;
	currentFanSpeed = -1;

	totalPrintTime = 0.0;
	for (unsigned int e = 0; e < MAX_EXTRUDERS; e++)
	{
		totalFilament[e] = 0.0;
	}

	currentSpeed = 0;
	retractionSpeed = 45;
	isRetracted = true;
	memset(extruderOffset, 0, sizeof(extruderOffset));
	f = stdout;
}

GCodeExport::~GCodeExport()
{
	if (f)
		fclose(f);
}

void GCodeExport::replaceTagInStart(const char * tag, const char * replaceValue)
{
	long oldPos = ftell(f);

	char buffer[1024];
	fseek(f, 0, SEEK_SET);
	fread(buffer, 1024, 1, f);

	char* c = strstr(buffer, tag);
	memset(c, ' ', strlen(tag));
	if (c) memcpy(c, replaceValue, strlen(replaceValue));

	fseek(f, 0, SEEK_SET);
	fwrite(buffer, 1024, 1, f);

	fseek(f, oldPos, SEEK_SET);

}

void GCodeExport::setExtruderOffset(int id, Point p)
{
	extruderOffset[id] = p;

}

void GCodeExport::setFlavor(int flavor)
{
	this->flavor = flavor;
}

int GCodeExport::getFlavor()
{
	return this->flavor;
}

void GCodeExport::setFilename(const char * filename)
{
	f = fopen(filename, "w+");
}

bool GCodeExport::isValid()
{
	return  f != NULL;
}

void GCodeExport::setExtrusion(int layerThickness, int filamentDiameter, int flow)
{
	double filamentArea = M_PI * (double(filamentDiameter) / 1000.0 / 2.0) * (double(filamentDiameter) / 1000.0 / 2.0);
	if (flavor == GCODE_FLAVOR_ULTIGCODE)//UltiGCode uses volume extrusion as E value, and thus does not need the filamentArea in the mix.
		extrusionPerMM = double(layerThickness) / 1000.0;
	else
		extrusionPerMM = double(layerThickness) / 1000.0 / filamentArea * double(flow) / 100.0;
}

void GCodeExport::setRetractionSettings(int retractionAmount, int retractionSpeed, int extruderSwitchRetraction, int minimalExtrusionBeforeRetraction)
{
	this->retractionAmount = double(retractionAmount) / 1000.0;
	this->retractionSpeed = retractionSpeed;
	this->extruderSwitchRetraction = double(extruderSwitchRetraction) / 1000.0;
	this->minimalExtrusionBeforeRetraction = double(minimalExtrusionBeforeRetraction) / 1000.0;
}

void GCodeExport::setZ(int z)
{
	this->zPos = z;
}

Point GCodeExport::getPositionXY()
{
	return Point(currentPosition.x, currentPosition.y);
}

int GCodeExport::getPositionZ()
{
	return currentPosition.z;
}

int GCodeExport::getExtruderNr()
{
	return extruderNr;
}

double GCodeExport::getTotalFilamentUsed(int e)
{
	if (e == extruderNr)
		return totalFilament[e] + extrusionAmount;
	return totalFilament[e];
}

double GCodeExport::getTotalPrintTime()
{
	return totalPrintTime;
}

void GCodeExport::addComment(const char * comment, ...)
{
	va_list args;
	va_start(args, comment);
	fprintf(f, ";");
	vfprintf(f, comment, args);
	fprintf(f, "\n");
	va_end(args);
}

void GCodeExport::addLine(const char * line, ...)
{
	va_list args;
	va_start(args, line);
	vfprintf(f, line, args);
	fprintf(f, "\n");
	va_end(args);
}

void GCodeExport::resetExtrusionValue()
{
	if (extrusionAmount != 0.0)
	{
		fprintf(f, "G92 E0\n");
		totalFilament[extruderNr] += extrusionAmount;
		extrusionAmountAtPreviousRetraction -= extrusionAmount;
		extrusionAmount = 0.0;
	}
}

void GCodeExport::addDelay(double timeAmount)
{
	fprintf(f, "G4 P%d\n", int(timeAmount * 1000));
}

void GCodeExport::addMove(Point p, int speed, int lineWidth)
{
	if (lineWidth != 0)
	{
		Point diff = p - getPositionXY();
		if (isRetracted)
		{
			if (flavor == GCODE_FLAVOR_ULTIGCODE)
			{
				fprintf(f, "G11\n");
			}
			else {
				fprintf(f, "G1 F%i E%0.5lf\n", retractionSpeed * 60, extrusionAmount);
				currentSpeed = retractionSpeed;
			}
			if (extrusionAmount > 10000.0) //According to https://github.com/Ultimaker/CuraEngine/issues/14 having more then 21m of extrusion causes inaccuracies. So reset it every 10m, just to be sure.
				resetExtrusionValue();
			isRetracted = false;
		}
		extrusionAmount += extrusionPerMM * double(lineWidth) / 1000.0 * vSizeMM(diff);
		fprintf(f, "G1");
	}
	else {
		fprintf(f, "G0");
	}

	if (currentSpeed != speed)
	{
		fprintf(f, " F%i", speed * 60);
		currentSpeed = speed;
	}
	fprintf(f, " X%0.2f Y%0.2f", float(p.X - extruderOffset[extruderNr].X) / 1000, float(p.Y - extruderOffset[extruderNr].Y) / 1000);
	if (zPos != currentPosition.z)
		fprintf(f, " Z%0.2f", float(zPos) / 1000);
	if (lineWidth != 0)
		fprintf(f, " E%0.5lf", extrusionAmount);
	fprintf(f, "\n");

	currentPosition = Point3(p.X, p.Y, zPos);


}

void GCodeExport::addRetraction()
{
	if (retractionAmount > 0 && !isRetracted && extrusionAmountAtPreviousRetraction + minimalExtrusionBeforeRetraction < extrusionAmount)
	{
		if (flavor == GCODE_FLAVOR_ULTIGCODE)
		{
			fprintf(f, "G10\n");
		}
		else {
			fprintf(f, "G1 F%i E%0.5lf\n", retractionSpeed * 60, extrusionAmount - retractionAmount);
			currentSpeed = retractionSpeed;
		}
		extrusionAmountAtPreviousRetraction = extrusionAmount;
		isRetracted = true;
	}
}

void GCodeExport::switchExtruder(int newExtruder)
{
	if (extruderNr == newExtruder)
		return;

	resetExtrusionValue();
	extruderNr = newExtruder;

	if (flavor == GCODE_FLAVOR_ULTIGCODE)
	{
		fprintf(f, "G10 S1\n");
	}
	else {
		fprintf(f, "G1 F%i E%0.4lf\n", retractionSpeed * 60, extrusionAmount - extruderSwitchRetraction);
		currentSpeed = retractionSpeed;
	}
	isRetracted = true;
	fprintf(f, "T%i\n", extruderNr);
}

void GCodeExport::addCode(const char * str)
{
	fprintf(f, "%s\n", str);
}

void GCodeExport::addFanCommand(int speed)
{
	if (currentFanSpeed == speed)
		return;
	if (speed > 0)
	{
		if (flavor == GCODE_FLAVOR_MAKERBOT)
			fprintf(f, "M126 T0 ; value = %d\n", speed * 255 / 100);
		else
			fprintf(f, "M106 S%d\n", speed * 255 / 100);
	}
	else
	{
		if (flavor == GCODE_FLAVOR_MAKERBOT)
			fprintf(f, "M127 T0\n");
		else
			fprintf(f, "M107\n");
	}
	currentFanSpeed = speed;
}

int GCodeExport::getFileSize()
{
	return ftell(f);
}

void GCodeExport::tellFileSize()
{
	float fsize = (float)ftell(f);
	if (fsize > 1024 * 1024) {
		fsize /= 1024.0*1024.0;
		fprintf(stderr, "Wrote %5.1f MB.\n", fsize);
	}
	if (fsize > 1024) {
		fsize /= 1024.0;
		fprintf(stderr, "Wrote %5.1f kilobytes.\n", fsize);
	}
}
