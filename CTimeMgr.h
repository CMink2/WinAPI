#pragma once
#include "pch.h"
class CTimeMgr
{
	SINGLE(CTimeMgr);
	//�̵����� ���ƾ� �Ѵ�. (��翡 ���� �ұ����� �Ͼ�� �ʵ��� ����)
	//������� �Ÿ��� �ʴ� ���������� ������ �����ؾ� �Ѵ�.
	private:
		LARGE_INTEGER m_curCount;	//���� ī��Ʈ
		LARGE_INTEGER m_prevCount;	//���� ī��Ʈ
		LARGE_INTEGER m_frequency;	//�ʴ� ī��Ʈ

		double m_deltaTime;	//������ ������ �ð� ��.

		UINT m_callCount;	//�ʴ� ȣ�� Ƚ��.

		//1�� ������ ���� ��.
		double m_acc;
		
		//FPS (Frame Per Second)
		UINT m_fps;
		//1 frame �� �ð� �� = delta Time
public:
		//GetTickCount�� ���̸� ������ ���� �ð��� �帧�� üũ�� �� �ִ�. ������ �� ��Ȯ�ϰ� üũ�ϱ� �����.
		//������ 1000�̱� ����
		//100�� ������ �ٲ㼭 ���.
		void Init();	//�ʱ�ȭ �������� ȣ��Ǵ� �Լ�.1
		void Update();
		double GetDeltaTimed();
		float GetDeltaTimef();
		
};

