#include "CCore.h"
#include"pch.h"
//�ν��Ͻ� �ʱ�ȭ.
CCore* CCore::m_instance = nullptr;

CCore2::CCore2()
{

}

CCore2::~CCore2()
{

}

int CCore2::Init(HWND _hwnd, POINT _ptRe)
{
	//������ ���� �޾ƿ���.
	m_hWnd = _hwnd;
	m_ptResolution = _ptRe;

	//���� �ػ󵵿� �µ��� �����ϱ�.
	return E_FAIL;
	//return S_OK;
}

void CCore2::Progress()
{

}