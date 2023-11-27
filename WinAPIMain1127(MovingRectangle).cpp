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


//object Position struct.
POINT objectPos = { 500, 300 }; //(x, y)
//object size
POINT objectSize = { 100, 100 };    //object size.

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

   //CreateWindow() 윈도우를 생성한다. (Kernel Object = 객체가 메모리 공간에 잡힘. 하지만 메모리 공간의 주소가 운영체제 구간에 잡혀서 조정할 수 없다. ) 
   //Window가 잡고있는 Kernel Object는 우리에게 ID를 준다.  = > 다룰 수 있게 하기 위함 -> Window Handle.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //window를 직접 다룰 수 없다. -> kernel Object이기 때문이다. -> 해결하기 위해 Handle을 통해서 id 값을 받아온다. -> id값을 이용해 객체를 조작하는 함수를 사용해 조작한다.

   //show window window를 보이게 하는 것이다. => Handle id를 받아 주소를 설정한다.
   //뒤에 들어가는 인자는 true, false이다.
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
//  Switch Case 문에서 Case 내부 지역 변수를 선언하기 위해서는 중괄호로 Block을 표시해야 한다.
//
//윈도우 프로시저. (해당 윈도우에 들어온 메세지를 처리하는 함수) 함수 포인터로 이용해 사용한다.
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
            objectPos.y -= 10;
            //call inavlidate rect condition 무효화 영역 발생 호출하기.
            InvalidateRect(hWnd, nullptr, true);   //rect에 nullptr을 넣으면 전체를 의미한다.
                                                    //Erase에 true를 넣으면 기존에 영역을 지워준다. false 이면 기존에 영역을 지우지 않는다.
            break;
        case VK_DOWN:
            objectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            objectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            objectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
        //press 'W' = Ascii code value check. 대문자 기준으로 체크한다.
        case 'W':
            break;

        }
        
    }
        break;
    //Release key.
    case WM_KEYUP:
    {

    }
        break;
    //left button down. (mouse) Mouse Position. 4byte x position = 2byte, y position = 2byte.
    case WM_LBUTTONDOWN:
    {
        objectPos.x = LOWORD(lParam);   //get x position.
        objectPos.y = HIWORD(lParam);   //get y position.
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
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
        //무효화 영역 (Invalidate Rect)
        /*
            Window 프로그램 창이 다른 창으로 인해 가려진 경우 (뒤에 있는 윈도우가 안보임.)
            다시 뒤에 있는 위도우를 클릭 -> 포커싱이 바뀌며 다시앞으로 나옴. -> 기존에 가려졌던 부분을 다시 채워서 그려야한다. ->과연 그럴까?

            창을 최소화 했다가 다시 키울 때 발생한다.
            창을 가렸을때는 발생하지 않는다. (이전에는 가려졌다가 다시 그릴 때 발생했다.)
        */

        //Kernel Object 사용법
        /*
            H가 붙어있으면 Handle이다. 
            HPEN = pen Handle
            HBRUSH = Brush Handle
            HWND = Window Handle
            HDC = Divice Context Handle
            Handle을 사용해 id를 받아서 사용한다.
            Handle은 생성할 때 아래와 같은 구조체를 매 번 생성한다.
            struct __name
            {
                int a
            } typedef name;

            왜 같은 형식의 구조체를 계속 만들까? 
                1. Kernel Object이지만 모두 하는 역할이 다르다.
                2. 만약 한 변수에 모든 Kernel Object ID를 받으면 형태 구분이 안된다. (pen, DC, Window)
                3. 즉 Kernel Object의 타입을 구분하기 위해서 별개의 자료형으로 만든 것이다.
                즉 id를 구분하기 쉽게하고 오류를 줄이기 위해서이다.
        */
        //Divice Context
        /*
            Divice Context = 그리기 작업을 수행하기 위한 데이터의 집합.
            Window에 무엇인가를 그리기 위해선 DC가 필요하다.
            Divice Context를 만들어 ID를 반환하는 함수. Window Handle을 주어 윈도우를 설정한다.(목적지)
            현재 윈도우 (DC의 목적지) Black Pen (DC의 기본 Pen), White (DC의 기본 Brush)
        */

            PAINTSTRUCT ps;

           
            HDC hdc = BeginPaint(hWnd, &ps);    //Divice Context Handle. -> Diveice Context(그리기 관련) = Kernel Object.
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // Pixel : 색을 구성하는 화소의 최소단위. 색의 값을 담고있는 메모리이다.
            //윈도우 좌표 : 0,0은 좌상단. Pixel단위로 이동한다.
            //window API에서 구현된 사각형 그리기 함수.
            //Window Handle = Window를 구성하는 kernel object의 id 값.

            //직접 펜을 만들어서 DC에 주겠다.
            /*style, width, colorREF*/
            HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 128, 0));

            //Get Stock Object (get already object) 자주쓰는 오브젝트 불러오기.
            HBRUSH hbrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

            //CreateSolidBrush(color) make a brush kernel object.
            
            //Select Object. Divice Context의 구성 Handle을 바꿔끼는 함수이다.
            //Device Context가 위에서 설정한 Pen을 받는 것이다. 기존의 Default Pen은? => 다시 변수하나 만들어서 지정해준다.
            //HGDIOBJ = void pointer type. casting이 필요하다. 범용적으로 사용하기 위해서이다. malloc과 비슷한 느낌이다.

            //change pen and brush object.
            HPEN defaultPen = (HPEN)SelectObject(hdc, hpen);
            HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, hbrush);

            //drawing rectangle.
            //dynamic position drawing.
            Rectangle(hdc, objectPos.x - objectSize.x / 2, 
                objectPos.y - objectSize.y / 2, 
                objectPos.x + objectSize.x / 2, 
                objectPos.y + objectSize.y / 2);   //사각형을 받아온 Divice Context에 해당 좌표에 그려주세요.
            

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
