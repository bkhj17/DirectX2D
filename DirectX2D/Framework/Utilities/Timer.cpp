#include "framework.h"

Timer::Timer()
{
	//������ �ð������� ���� ���
	//QueryPerformanceFrequency : 1�ʵ����� cpu������ ��ȯ
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	//QueryPerformanceCounter : ���� CPU ������ ��ȯ
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

	timeScale = 1.0f / (float)periodFrequency;	//������ ���� ����. ������ ������ ���� ���ϱ� �������� �� ����
}

Timer::~Timer()
{
}

void Timer::Update()
{
	//(���� ������ - ���� �ð� ������) * 1/1�ʴ������� => ���� �ð�(�ʴ���)
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	elapsedTime = (float)(curTime - lastTime)*timeScale;

	if (lockFPS != 0) {
		while (elapsedTime < (1.0f / lockFPS)) {
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			elapsedTime = (float)(curTime - lastTime) * timeScale;
		}
	}
	lastTime = curTime;

	frameCount++;
	oneSecCount += elapsedTime;

	if (oneSecCount >= 1.0f) {	//1�� �̻� �����ٸ�
		frameRate = frameCount;
		frameCount = 0;
		oneSecCount = 0.0f;
	}
}