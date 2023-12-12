#include "CCore.h"
#include"pch.h"
#include"CObject.h"
#include"CTimeMgr.h"
#include"CKeyMgr.h"
//�ν��Ͻ� �ʱ�ȭ.
CCore* CCore::m_instance = nullptr;
CObject g_obj;

CCore2::CCore2() :m_hWnd(0), m_ptResolution{}, m_dc(0)
{

}

CCore2::~CCore2()
{
	//kernel object�� dc ����.
	ReleaseDC(m_hWnd, m_dc);
}

int CCore2::Init(HWND _hwnd, POINT _ptRe)
{
	//������ ���� �޾ƿ���.
	m_hWnd = _hwnd;			//handle �� �޾ƿ���.
	m_ptResolution = _ptRe;	//Resolution �� �޾ƿ���.

	//���� �ػ󵵿� �µ��� �����ϱ�. �ػ� = �����ϰ� �׷��� ������ ũ��.
	//window version�� ���� â�� �β��� �ٸ���. ���� ������� �β��� �����ؼ� ũ�� �����Ѵ�.
	//RECT (left, top, right, bottom)�� ���� ����ü.
	//�ػ� ũ��.
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	//dw style = window�� ���� ��Ʈ�������� ���ǵ� ������ �ִ�.
	//menu�� �������� �����ؼ� ����ϵ��� true ���ڸ� �ش�.
	AdjustWindowRect(&rt, WS_OVERLAPPED, true);	//�������� ũ�⸦ ���� ������ �ػ󵵰� �������� ����ش�. (�β��� �˾Ƽ� ���)
	SetWindowPos(_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	_ptRe.x;
	_ptRe.y;

	//dc�� handle �޾ƿ���.
	m_dc = GetDC(m_hWnd);	//�޼����� �������� �������� �޼��� ť�� ���� ���� ����. ��� ���α׷� ���� �� �����ؾ� �Ѵ�.
	
	//manager �ʱ�ȭ
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();

	//object.
	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore2::Update()
{
	//object�� ���� ������,
	Vec2 currentPos = g_obj.GetPos();
	//�񵿱�� Ű �Է� (Ű�� ���ȳ� ���.) => ���°��� ��ȯ�Ѵ�.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	//��Ʈ ���� ���� �� �ֻ�� �ڸ����� ������ true
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
	//�׸��� �۾�. (drawing) �׸��� ���ؼ� Device Context�� �ʿ��ϴ�. 
	//���� �� Renderring�� �� ����(frame) �ٽ� �׸��� �����̴�. (Ư�� ��ȭ�� �׸��� ���� �ƴϴ�.) ������ �������� �ִ� ���� �׸���.
	//�̵��� ������Ʈ ��ġ�� �׸���.
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
	CTimeMgr::GetInstance()->Update();	// �� �����Ӹ��� Ÿ�ӸŴ��� ������Ʈ.

	//update.
	Update();
	//render
	Render();
}

HWND CCore2::GetHandle()
{
	return m_hWnd;
}
