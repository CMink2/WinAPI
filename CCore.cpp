#include "CCore.h"
#include"pch.h"
#include"CObject.h"
#include"CTimeMgr.h"
#include"CKeyMgr.h"
//인스턴스 초기화.
CCore* CCore::m_instance = nullptr;
CObject g_obj;

CCore2::CCore2() :m_hWnd(0), m_ptResolution{}, m_dc(0)
{

}

CCore2::~CCore2()
{
	//kernel object인 dc 해제.
	ReleaseDC(m_hWnd, m_dc);
}

int CCore2::Init(HWND _hwnd, POINT _ptRe)
{
	//윈도우 정보 받아오기.
	m_hWnd = _hwnd;			//handle 값 받아오기.
	m_ptResolution = _ptRe;	//Resolution 값 받아오기.

	//실제 해상도에 맞도록 조정하기. 해상도 = 순수하게 그려질 영역의 크기.
	//window version에 따라 창의 두께가 다르다. 실제 사이즈는 두께를 감안해서 크게 설정한다.
	//RECT (left, top, right, bottom)을 가진 구조체.
	//해상도 크기.
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	//dw style = window의 구조 비트연산으로 정의된 값들이 있다.
	//menu가 있음으로 감안해서 계산하도록 true 인자를 준다.
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);	//윈도우의 크기를 내가 지정한 해상도가 나오도록 잡아준다. (두께를 알아서 계산)
	SetWindowPos(_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	_ptRe.x;
	_ptRe.y;

	//dc의 handle 받아오기.
	m_dc = GetDC(m_hWnd);	//메세지와 엮여있지 않음으로 메세지 큐에 쌓일 일이 없다. 대신 프로그램 종료 시 해제해야 한다.
	
	//manager 초기화
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();

	//object.
	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore2::Update()
{
	//object의 현재 포지션,
	Vec2 currentPos = g_obj.GetPos();
	//비동기식 키 입력 (키가 눌렸냐 물어봄.) => 상태값을 반환한다.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	//비트 연산 했을 때 최상단 자릿수가 있으면 true
	{
		currentPos.x -= 200.f * CTimeMgr::GetInstance()->GetDeltaTimef();
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		currentPos.x += 200.f * CTimeMgr::GetInstance()->GetDeltaTimef();
	}
	//change position.
	g_obj.SetPos(currentPos);
}

void CCore2::Render()
{
	//그리기 작업. (drawing) 그리기 위해선 Device Context가 필요하다. 
	//게임 속 Renderring은 매 순간(frame) 다시 그리는 행위이다. (특정 변화만 그리는 것이 아니다.) 조금의 움직임이 있던 없던 그린다.
	//이동한 오브젝트 위치로 그리기.
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_dc, 
		vPos.x - vScale.x/2.f, 
		vPos.y - vScale.y / 2.f, 
		vPos.x + vScale.x / 2.f, 
		vPos.y + vScale.y / 2.f);
	/*
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f)
		);
	*/
}


void CCore2::Progress()
{
	//Manager Update.
	CTimeMgr::GetInstance()->Update();	// 매 프레임마다 타임매니저 업데이트.

	//update.
	Update();
	//render
	Render();
}

HWND CCore2::GetHandle()
{
	return m_hWnd;
}
