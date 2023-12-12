#include"pch.h"
#include "CTimeMgr.h"
#include"CCore.h"

//union ���� �Ű������� �޴´�.
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
	//100�� = 1�ʷ� ȯ���ϴ� �Լ�. GetTickCount�� ���� ����.
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_prevCount);		
	//�ʴ� ī��Ʈ Ƚ��.
	QueryPerformanceFrequency(&m_frequency);	//�ʴ� ī��Ʈ ��.
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_curCount);

	//���� �����ӿ��� ���� ������ ī���ð��� ����.
	m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / m_frequency.QuadPart;

	//deltaTime �� ���� = FPS (Frame Per Second) ������ �� ������� �ʴ´�.

	//���� ī��Ʈ �����ϱ�.
	m_prevCount = m_curCount;

	//ȣ�� Ƚ�� �ø���
	m_callCount++;

	//�� ������Ű��.
	m_acc += m_deltaTime;	//�귯���� �ð�.

							//1�ʰ� �Ǹ� ����ϱ�.
	if (m_acc >= 1.)
	{
		m_fps = m_callCount;
		m_acc = 0.;
		m_callCount = 0;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_fps, m_deltaTime);
		SetWindowText(CCore2::GetInstance()->GetHandle(), szBuffer);
	}
}	//�� ������ ���� ȣ���ϴ� �Լ�.

double CTimeMgr::GetDeltaTimed()
{
	return m_deltaTime;
}

float CTimeMgr::GetDeltaTimef()
{
	return (float)m_deltaTime;
}

