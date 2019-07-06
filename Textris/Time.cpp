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
	float fPrevTime = 0;	//�� ������ ���� ���� �ð� (T)
	float fCurTime = clock() * 0.001f;	//�� ������ ���� ���� �ð� (T')
	float time = 0;	//���� �� ��� �ð� (CPU ������ ���� ���� ��� �ð��� �ٸ�)
	float acc = 0;	//������ ����
	float fFrameTime;
	float max = 0;

	while (mv_bIsQuit == false)
	{
		fPrevTime = fCurTime;
		fCurTime = clock() * 0.001f;
		fFrameTime = fCurTime - fPrevTime;		//�� �����Ӵ� �ɸ� �ð� (��T = T' - T)

		if (fFrameTime > MAX_DELTA_TIME)		//�ִ� ��T ����
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
