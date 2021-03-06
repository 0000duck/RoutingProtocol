#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

extern int verbose_level;

void logError(const char* fmt, ...);
void _log(const char* fmt, ...);
#define log _log
void logProgress(const char* type, int value, int maxValue);

#endif//LOGOUTPUT_H