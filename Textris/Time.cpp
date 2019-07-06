#include "pch.h"
#include "Time.h"

Time::Time(const int nFPS = 60) :MAX_DELTA_TIME(1.5f / nFPS), MY_DELTA_TIME(1.0f / nFPS)
{
	mv_bIsQuit = false;
}

Time::~Time()
{
}

void Time::UpdateFPS(void (*Update)())
{
	float fPrevTime = 0;	//한 프레임 실행 이전 시간 (T)
	float fCurTime = clock() * 0.001f;	//한 프레임 실행 이후 시간 (T')
	float time = 0;	//게임 내 경과 시간 (CPU 사정에 따라 실제 경과 시간과 다름)
	float acc = 0;	//누산기용 변수
	float fFrameTime;
	float max = 0;

	while (mv_bIsQuit == false)
	{
		fPrevTime = fCurTime;
		fCurTime = clock() * 0.001f;
		fFrameTime = fCurTime - fPrevTime;		//한 프레임당 걸린 시간 (ΔT = T' - T)

		if (fFrameTime > MAX_DELTA_TIME)		//최대 ΔT 제한
		{
			fFrameTime = MAX_DELTA_TIME;
		}
		acc += fFrameTime;

		while (acc >= MY_DELTA_TIME)
		{
			Update();
			acc -= MY_DELTA_TIME;
			time += MY_DELTA_TIME;
		}

		//render
	}
}

float Time::GetDeltaTime()
{
	return MY_DELTA_TIME;
}
