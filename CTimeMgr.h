#pragma once
#include "pch.h"
class CTimeMgr
{
	SINGLE(CTimeMgr);
	//이동량이 같아야 한다. (사양에 따라 불균형이 일어나지 않도록 수정)
	//가고싶은 거리를 초당 프레임으로 나눠서 설정해야 한다.
	private:
		LARGE_INTEGER m_curCount;	//현재 카운트
		LARGE_INTEGER m_prevCount;	//이전 카운트
		LARGE_INTEGER m_frequency;	//초당 카운트

		double m_deltaTime;	//프레임 사이의 시간 값.

		UINT m_callCount;	//초당 호출 횟수.

		//1초 연산을 위한 값.
		double m_acc;
		
		//FPS (Frame Per Second)
		UINT m_fps;
		//1 frame 당 시간 값 = delta Time
public:
		//GetTickCount의 차이를 나눠서 현실 시간의 흐름을 체크할 수 있다. 하지만 더 정확하게 체크하기 힘들다.
		//단위가 1000이기 때문
		//100만 단위로 바꿔서 계산.
		void Init();	//초기화 목적으로 호출되는 함수.1
		void Update();
		double GetDeltaTimed();
		float GetDeltaTimef();
		
};

