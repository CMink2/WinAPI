// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

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
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    //GetMessage의 특징. 반환은 True False이다.
    //메세지 큐에서 메세지가 확인될 때까지 대기한다. 메세지 큐에 메세지가 있으면 값을 반환한다.
    // PROGAAM => Run in Memory -> PROCESS hava Windows. 
    // Windows turn off. -> Kill Process.
    //False의 반환 조건은 WM_QUIT 메세지를 받을 때이다. -> WM_QUIT가 반환되면 프로그램이 종료된다.
    //즉 Window Program은 Message를 입력해야만 동작하는 프로그램이다. (메세지가 없으면 무한 대기.)
    while (GetMessage(&msg, nullptr, 0, 0)/*Process의 메세지 큐에서 읽어온다. 수 많은 메세지들은 포커스 중인 프로세스에 넣어준다.*/)
    {
        //꺼낸 메세지의 실행 윈도우가 현재 윈도우가 아니면 
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            //발생한 윈도우 메세지를 프로시저로 처리하라는 명령이다.
            TranslateMessage(&msg);
            //관련 윈도우로 보낸다.
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //윈도우 클래스 확장. (구조체)
    WNDCLASSEXW wcex;

    //구조체 멤버들.
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    //RegisterClassExW = 윈도우가 지정한 함수이다. 윈도우에서 이미 생성된 라이브러리 함수이기에 원본을 보기 어렵다.
    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//윈도우 프로시저.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // Pixel : 색을 구성하는 화소의 최소단위. 색의 값을 담고있는 메모리이다.
            //윈도우 좌표 : 0,0은 좌상단. Pixel단위로 이동한다.
            //window API에서 구현된 사각형 그리기 함수.
            Rectangle(hdc, 10, 10, 110, 110);
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
