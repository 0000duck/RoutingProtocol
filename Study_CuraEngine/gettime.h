#ifndef GETTIME_H
#define GETTIME_H


#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <stddef.h>
#endif


//ϵͳ����������ʱ��΢��
static inline double getTime()
{
#ifdef WIN32
	return double(GetTickCount()) / 1000.0;//GetTickCount()��ϵͳ����������ʱ����� ���ڷ���΢��
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return double(tv.tv_sec) + double(tv.tv_usec) / 1000000.0;
#endif
}

double timeElapsed(double &t, bool all_time = false);

#endif//GETTIME_H