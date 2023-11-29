// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"
#include <vector>
#include "pch.h"
#include "CCore.h"
#define MAX_LOADSTRING 100
using namespace std;
// 전역 변수:
//main에서 받은 Hinstance를 기억한다.
HINSTANCE hInst;                                // 현재 인스턴스입니다. HINSTANCE의 값은 Process가 실행되는 Memory의 주소이다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다. 2byte char 변수.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND ghWnd;

//물체가 여러개 있다면? -> 모든 물체를 매번 다시그려야 한다. (겹치는 경우)
/*
	Renderring : 화면을 그리기.
	Frame : 화면의 갱신 주기.
*/

struct ObjInfo
{
	//object Position struct.
	POINT objectPos = { 500, 300 }; //(x, y)
	//object size
	POINT objectSize = { 100, 100 };    //object size.    
}typedef objinfo;
vector<objinfo> vecInfo;    //vector 전체는 전역변수. 관린하는 변수들은 Heap Memory.
//mouse left top position.
POINT g_ptLT;
//mouse right bottom position.
POINT g_ptRB;
bool isClick = false;

//기존의 main과 이름이 다르지만 main과 같은 역할을 수행한다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,     /*현재 Process의 실행 주소. (가상 메모리 주소 반환)*/
	_In_opt_ HINSTANCE hPrevInstance,  /*이전 Process의 실행 주소. (가상 메모리 주소 반환)*/
	_In_ LPWSTR    lpCmdLine, /*커멘드 라인 : 명령어 입력.*/
	_In_ int       nCmdShow)
{
	//unrefercenced parameter 해당 코드가 아무의미 없다는 뜻이다.
	//주석.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);         //103 id에 해당하는 문자 정보를 ResourceTable에서 가져와라.
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);      //109 id에 해당하는 문자 정보를 ResourceTable에서 가져와라
	//윈도우 정보를 넘겨준다.
	MyRegisterClass(hInstance);

	// 윈도우를 생성한다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//Core를 초기화 한다. (만약 코어 생성이 안될 시 프로그램을 종료한다.
	if (FAILED(CCore2::GetInstance()->Init(ghWnd, { 1280, 720 })))
	{
		MessageBox(ghWnd, L"Core 객체 초기화 실패", L"Error", MB_OK);
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;

	//wm_timer 메세지가 들어온다.
	//SetTimer(ghWnd, 0, 0, nullptr);
	
	// 기본 메시지 루프입니다:
	//GetMessage의 특징. 반환은 True False이다.
	//메세지 큐에서 메세지가 확인될 때까지 대기한다. 메세지 큐에 메세지가 있으면 값을 반환한다.
	// PROGAAM => Run in Memory -> PROCESS hava Windows. 
	// Windows turn off. -> Kill Process.
	//False의 반환 조건은 WM_QUIT 메세지를 받을 때이다. -> WM_QUIT가 반환되면 프로그램이 종료된다.
	
	//즉 Window Program은 Message를 입력해야만 동작하는 프로그램이다. (메세지가 없으면 무한 대기.)
	/*
	while (GetMessage(&msg, nullptr, 0, 0)/*Process의 메세지 큐에서 읽어온다. 수 많은 메세지들은 포커스 중인 프로세스에 넣어준다.)
	{
		//Peek : 몰래 보다.
		PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);	//마지막 인자는 메세지의 제거 여부를 선택한다. PM_REMOVE는 메세지 큐에서 메세지를 제거한다.
		//꺼낸 메세지의 실행 윈도우가 현재 윈도우가 아니면 
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			//발생한 윈도우 메세지를 프로시저로 처리하라는 명령이다.
			TranslateMessage(&msg);
			//관련 윈도우로 보낸다.
			DispatchMessage(&msg);
		}
	}*/
	
	while (true)
	{
		//PeekMessage의 반환 값은 ? True, false.
		//True : 메세지가 있으면 true
		//False : 메세지가 없으면 False.
		//Message가 있는 경우.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))	
		{
			
			int iTime = GetTickCount();
			//처리하기 전에 WM_QUIT인지 확인한다.
			if (WM_QUIT == msg.message)
				break;	//excape this Loop.
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		}
		//Message가 없는 경우 호출.
		else 
		{
			//Game 관련된 Client 처리를 한다.
			//게임 프로세스 실행.
			CCore2::GetInstance()->Progress();
			
		}
		
	}
	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{

	WNDCLASSEXW wcex;


	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


	return RegisterClassExW(&wcex);
}

//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 

	
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	ghWnd = hWnd;
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd/*Window Handle*/, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//event press any key.
		//WPARAM, LPARAM = sub parameter key or mouse (키인지 마우스인지 알려주는 파라미터 값.
	case WM_KEYDOWN:
	{

		switch (wParam)
		{
			//press up arrow.
		case VK_UP:
			//objectPos.y -= 10;
			//call inavlidate rect condition 무효화 영역 발생 호출하기.
			//InvalidateRect(hWnd, nullptr, true);  
			break;
		case VK_DOWN:
			//objectPos.y += 10;
			//InvalidateRect(hWnd, nullptr, true);
			break;
		case VK_LEFT:
			//objectPos.x -= 10;
			//InvalidateRect(hWnd, nullptr, true);
			break;
		case VK_RIGHT:
			//objectPos.x += 10;
			//InvalidateRect(hWnd, nullptr, true);
			//press 'W' = Ascii code value check. 대문자 기준으로 체크한다.
		case 'W':
			break;

		}

	}
		break;
	//timer message. 타이머를 통해서 깜빡임 현상 줄이기.
	case WM_TIMER:
		InvalidateRect(hWnd, nullptr, true);
		break;
	//Release key.
	case WM_KEYUP:
	{

	}
	break;
	//left button down. (mouse) Mouse Position. 4byte x position = 2byte, y position = 2byte.
	case WM_LBUTTONDOWN:
	{
		
		//마우스를 누른 순간 좌상단 좌표 지정.
		//start position.
		g_ptLT.x = LOWORD(lParam);   //get x position.
		g_ptLT.y = HIWORD(lParam);   //get y position.
		isClick = true;
	}
	break;
	//move mouse
	case WM_MOUSEMOVE:
	{
		//end position.
		g_ptRB.x = LOWORD(lParam);   //get x position.
		g_ptRB.y = HIWORD(lParam);   //get y position.
		//다시그리기.
		//InvalidateRect(hWnd, nullptr, true);
		break;
	}

	case WM_LBUTTONUP:
	{
		objinfo objectInfo = {};
		//get center position.
		objectInfo.objectPos.x = (g_ptLT.x + g_ptRB.x) / 2;
		objectInfo.objectPos.y = (g_ptLT.y + g_ptRB.y) / 2;

		//get size abs = absolute 절댓값 함수.
		objectInfo.objectSize.x = abs(g_ptLT.x - g_ptRB.x);
		objectInfo.objectSize.y = abs(g_ptLT.y - g_ptRB.y);
		vecInfo.push_back(objectInfo);
		isClick = false;
	}
	//메세지의 처리 과정.
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:  //MSDN에서 WM_PAINT가 발생하는 경우 : 무효화 영역이 발생한 경우.
	{
		

		PAINTSTRUCT ps;


		HDC hdc = BeginPaint(hWnd, &ps);    
		
		

		
		HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 128, 0));

		
		HBRUSH hbrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

		

		

		
		HPEN defaultPen = (HPEN)SelectObject(hdc, hpen);
		HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, hbrush);

		
		if(isClick)
			Rectangle(hdc, g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y);

		
		for (size_t i = 0; i < vecInfo.size(); i++)
		{
			Rectangle(hdc, vecInfo[i].objectPos.x-vecInfo[i].objectSize.x/2,
				vecInfo[i].objectPos.y - vecInfo[i].objectSize.y / 2,
				vecInfo[i].objectPos.x + vecInfo[i].objectSize.x / 2,
				vecInfo[i].objectPos.y + vecInfo[i].objectSize.y / 2
				);
		}

		//return default object.
		SelectObject(hdc, defaultPen);
		SelectObject(hdc, defaultBrush);

		//delete create object. (Kernel Object Delete) we can't delete this object -> request O/S -> Delete this id Object.
		DeleteObject(hpen);
		//brush = stock object => don't delete.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
