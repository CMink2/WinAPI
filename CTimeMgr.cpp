#include"pch.h"
#include "CTimeMgr.h"
#include"CCore.h"

//union 값을 매개변수로 받는다.
CTimeMgr::CTimeMgr() 
	: m_curCount{}
	, m_prevCount{}
	, m_frequency{}
	, m_deltaTime(0)
	, m_callCount(0)
	, m_acc(0)
{}
CTimeMgr::~CTimeMgr() {}
void CTimeMgr::Init()
{
	//100만 = 1초로 환산하는 함수. GetTickCount와 같은 역할.
	//현재 카운트
	QueryPerformanceCounter(&m_prevCount);		
	//초당 카운트 횟수.
	QueryPerformanceFrequency(&m_frequency);	//초당 카운트 빈도.
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_curCount);

	//현재 프레임에서 이전 프레임 카운팅과의 차이.
	m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / m_frequency.QuadPart;

	//deltaTime 의 역수 = FPS (Frame Per Second) 하지만 잘 사용하지 않는다.

	//이전 카운트 갱신하기.
	m_prevCount = m_curCount;

	//호출 횟수 올리기
	m_callCount++;

	//값 누적시키기.
	m_acc += m_deltaTime;	//흘러가는 시간.

							//1초가 되면 출력하기.
	if (m_acc >= 1.)
	{
		m_fps = m_callCount;
		m_acc = 0.;
		m_callCount = 0;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_fps, m_deltaTime);
		SetWindowText(CCore2::GetInstance()->GetHandle(), szBuffer);
	}
}	//매 프레임 마다 호출하는 함수.

double CTimeMgr::GetDeltaTimed()
{
	return m_deltaTime;
}

float CTimeMgr::GetDeltaTimef()
{
	return (float)m_deltaTime;
}

