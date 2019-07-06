#ifndef _TIME_CLASS
#define _TIME_CLASS
#include <time.h>

class Time
{
private:
	const float MAX_DELTA_TIME;	//�ִ� ��Ÿ Ÿ��
	const float MY_DELTA_TIME;
	int mv_nFramePerSec;
	bool mv_bIsQuit;

public:
	Time(const int nFPS);
	~Time();

	void UpdateFPS(void (*Update)());
	float GetDeltaTime();
};

#endif