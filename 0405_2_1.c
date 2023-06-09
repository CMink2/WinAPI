#include<Windows.h>					//Dos와 다르게 Windows에서는 API에 사용하는 함수, 상수들이 모두 Windows.h에 정의되어 있다.

/*
	DOS에서는 main함수 하나만으로 프로그래밍이 가능하지만
	WinAPI는 WndProc함수와 WinMain 함수 두개가 모두 필요하다.
	WinMain은 Windows창을 표시해주는 역할만을 한다.
	WndProc에서 실질적으로 함수 처리를 한다.
	CALLBACK 정의는 호환성을 위한 메크로 정의이므로 당분간은 상관하지 않아도 된다.
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//hInstance를 저장할 전역 변수.
HINSTANCE g_hInst;

//WindowsClass를 정의하는데 사용되는 값.
//제목이 다음 TEXT와 같이 설정된다.
LPCTSTR lpszClass = TEXT("First");


//데스크톱 개발환경으로 들어오면 main함수를 사용할 수 없고 WinMain 함수가 이를 대체한다.

/*
	hInstance는 프로그램 Instance의 핸들이다.
	hPrevInstance는 바로 앞에 사용된 Instance의 핸들이다.
	lspzCmdParam main함수에 전달되는 인수이다. 보통 실행 직전에 열은 파일의 경로가 전달된다.
	nCmdShow는 프로그램이 실행될 형태이며 최소화 보통 모양 등이 전달된다.

	이들중 hInstance가 가장 많이 사용된다.

	Handle은 구분하기 위한 정수형의 인덱스이다.
	Instance란 프로그램 하나를 칭하는 용어이다.
	hInstance는 프로그램 자체를 나타내는 인수 값이다. 
*/

/*
	같은 메모장을 2개 키더라도 OS는 서로 다른 프로그램으로 인식한다.
	따라서 hInstance는 우리가 서로 다른 프로그램에 접근하기 위한 대명사이다.
	하지만 아래 코드에서 hInstance는 지역 변수이기 때문에 사라진다.
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	//hInstance에 저장된 값을 전역변수인 g_hInst에 저장하므로서 프로그램이 끝나기 전까지 기억되도록 한다.
	g_hInst = hInstance;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY :
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}