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

//문자열을 사용할 때 TEXT로 묶어야 유니코드 변환이 쉽다.
LPCTSTR exTitle = TEXT("예제용 타이틀");


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

	WndClass.cbClsExtra = 0;										//cbClsExtra, cbWndExtra는 예약 공간이다. 윈도우즈가 내부적으로 사용하며 아주 특수한 경우에 사용하는 영역이다.
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//배경색으로 칠할 브러시 또는 색을 지정한다.
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);					//Cursor 모양을 설정한다.
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//Icon  모양을 설정한다.
	WndClass.hInstance = hInstance;									//윈도우 프로그램의 번호다.	
	WndClass.lpfnWndProc = WndProc;									//윈도우의 메시지 처리 함수를 지정한다. (이전에 선언한 CallBack함수이다.)
	WndClass.lpszClassName = lpszClass;								//Class 의 이름을 설정한다.
	WndClass.lpszMenuName = NULL;									//이 프로그램에서 사용할 메뉴를 지정한다.
	WndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우의 스타일을 정의 (어떤 형태를 가질 것인가?)
	RegisterClass(&WndClass);										//레지스터 함수의 일종으로 WNDCLASS의 번지를 전달한다.

	/*
		위 코드 해석:
		여유 공간을 사용하지 않고 흰색 배경에 커서와 아이콘은 운영체제가 지원하는 것을 사용한다.
		윈도우 클래스를 등록한 프로그램은 hInstance이며 전달되는 메시지 처리는 WndProc이 해결한다.
	*/


	//CreateWindow명령을 통해서 메인 Windows를 만들 수 있다.
	hWnd = CreateWindow(lpszClass, exTitle, WS_CAPTION| WS_HSCROLL|WS_VSCROLL| WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU|WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);

	//hWnd 인수는 화면으로 출력하고자 하는 윈도우의 핸들이다.
	//sw_hide는 숨기기, sw_minimize는 최소화, sw_restore는 활성화시킨다.
	//SW_SHOWNORMAL : 윈도우를 활성화 하며 보여준다.

	ShowWindow(hWnd, SW_SHOWNORMAL);


	//메시지 루프 (메시지에 따라서 처리하는 루프) WinMain 함수 끝에 위치한다.
	//순차적 실행이 아닌 메시지에 따른 실행.
	while (GetMessage(&Message, NULL, 0, 0))	//Bool GetMessage() :  메시지 큐에서 메시지를 읽어온다. Queue : 임시 저장공간.(선입선출구조) 종료 메시지 : WM_QUIT일 경우 False, 나머지는 True를 반환한다.
	{
		TranslateMessage(&Message);				//Bool TranslateMessage() : 키보드 입력 메시지를 가공하여 프로그램에서 쓰기 쉽게 해주는 함수. 키보드를 누르면 ~문자가 입력되었다는 메시지를 생성.
		DispatchMessage(&Message);				//Bool DispatchMessage() : 메시지 큐에서 꺼낸 메시지를 윈도우의 메시지 처리 함수로 전달.(위 코드에서는 WndProc으로 전달된다.)

		/*
			메시지 신호의 종류
			WN_QUIT : 종료 시그널.
			WM_LBUTTONDOWN : 마우스 좌측 버튼
			WM_KEYDOWN : 키보드 누름.
			WM_CHAR : 키보드로 부터 문자가 눌릴 때.
			WM_PAINT : 화면을 다시 그릴 때.
			WM_DESTROY : 윈도우가 메모리에서 파괴될 때 발생.
		*/
	}

	/*
		위 메시지 루프에 사용되는 함수들은 MSG 구조체를 사용한다.
		hwnd : 메시지를 받을 윈도우 핸들.
		message : 메시지의 종류. (가장 중요)
		wParam : 전달된 메시지의 부가적 정보.
		IParam : 전달된 메시지의 부가적 정보.
		time : 메시지의 발생 시간.
		pt : 마우스의 위치. (Pointer의 약어.)
	*/



	return (int)Message.wParam;
}

/*
	Windows는 Dos와 다르게 순차적 처리가 아닌 메시지를 이용해 특정
	사건이 발생할 때 처리한다. 아래는 메시지를 처리하는  함수이다.

	메시지 루프 : 메시지 구동 시스템이라고 한다.(Message Driven System)
*/

//Windows Procedure의 약어이다. 이 함수는 메시지가 발생할 때 처리하는 명령을 기술한 함수이다.
/*
	WndProc의 특징
	1. 운영체제에서 호출한다.(WinMain에서 호출 X)
	2. 위와 같이 운영체제에서 호출하는 함수를 CallBack 함수라고 한다.
	3. 다음 함수의 인수들은 MSG 구조체에 인수들과 같다.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	//hWnd = 핸들, iMessage = 메시지의 종류, wParam, iParam = 부가정보.
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//처리하지 않은 남은 메시지들을 DefWindowProc 함수에게 넘긴다.
	/*
		대부분 윈도우의 이동이나 크기 조정 같은 것을 넘긴다.
	*/
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}