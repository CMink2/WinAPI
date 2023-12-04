#include "CCore.h"
#include"pch.h"
#include"CObject.h"
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
	
	//object.
	g_obj.m_Pos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_Scale = POINT{ 100, 100 };

	return S_OK;
}

void CCore2::Update()
{
	//�񵿱�� Ű �Է� (Ű�� ���ȳ� ���.) => ���°��� ��ȯ�Ѵ�.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	//��Ʈ ���� ���� �� �ֻ�� �ڸ����� ������ true
	{
		g_obj.m_Pos.x -= 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_Pos.x += 1;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		g_obj.m_Pos.x -= 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		g_obj.m_Pos.x += 1;
	}
	g_obj.m_Pos;
}

void CCore2::Render()
{
	//�׸��� �۾�. (drawing) �׸��� ���ؼ� Device Context�� �ʿ��ϴ�. 
	//���� �� Renderring�� �� ����(frame) �ٽ� �׸��� �����̴�. (Ư�� ��ȭ�� �׸��� ���� �ƴϴ�.) ������ �������� �ִ� ���� �׸���.
	//�̵��� ������Ʈ ��ġ�� �׸���.
	Rectangle(m_dc, g_obj.m_Pos.x - g_obj.m_Scale.x / 2,
		g_obj.m_Pos.y - g_obj.m_Scale.y / 2,
		g_obj.m_Pos.x + g_obj.m_Scale.x / 2,
		g_obj.m_Pos.y + g_obj.m_Scale.y / 2);
}


void CCore2::Progress()
{
	//���� ī��Ʈ.
	static int iPrevCount = GetTickCount();

	//���� ī��Ʈ
	int iCurCount = GetTickCount();
	//1�ʰ� ������ ����.
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
	}

	//update.
	Update();
	//render
	Render();
}