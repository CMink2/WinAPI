#include "CCore.h"
#include"pch.h"
//인스턴스 초기화.
CCore* CCore::m_instance = nullptr;

CCore2::CCore2()
{

}

CCore2::~CCore2()
{

}

int CCore2::Init(HWND _hwnd, POINT _ptRe)
{
	//윈도우 정보 받아오기.
	m_hWnd = _hwnd;
	m_ptResolution = _ptRe;

	//실제 해상도에 맞도록 조정하기.
	return E_FAIL;
	//return S_OK;
}

void CCore2::Progress()
{

}