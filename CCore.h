#pragma once
#include "define.h"
//Program의 중추 클래스.
/*
	프로그램의 중추가 되는 클래스가 여러개 있으면? -> 절대 안됨. -> 딱 하나만 존재해야 한다.

	Singleton Pattern
	* 해당 클래스로 생성 가능한 객체의 개수는 1개로 제한된다.
		* 생성자가 Private로 선언되어 외부에서 생성이 불가능해야 한다.
		* 내부 멤버 함수로 클래스를 생성해주도록 한다. (객체를 만드는 함수를 만들려면 객체가 있어야한다? -> static으로 선언해 접근한다.)
	* 언제 어디서나 호출이 가능해야 한다. (어디서든 쉽게 접근이 가능하다. -> EXTERN으로 선언 시 어디선가 여러 개의 객체가 생성 될 수 있다. X)

*/

//객체 주소를 주는 방식으로 만든 싱글톤.
class CCore
{
	public:
		//객체를 얻어오는 함수. 
		//static으로 선언하면 정적 변수이기 떄문에 먼저 메모리에 할당된다. 따라서 객체가 없더라도 호출이 가능하다. 
		//단 객체 내부의 멤버에 접근이 불가능하다. this 키워드가 없다.
		//하지만 static으로 선언한 정적 멤버는 접근이 가능하다.
		static CCore* GetInstance()
		{
			//최초 호출된 경우. 새로 생성한다.
			if (m_instance == nullptr)
				m_instance = new CCore;
			//이미 호출됬던 경우 기존의 변수를 반환한다.
			return m_instance;
		}
		
		//객체를 반환하는 함수.
		static void Release()
		{
			//메모리 해제.
			delete m_instance;
			//nullptr로 변환. (참조 주소)
			m_instance = nullptr;
		}
	private:
		static CCore* m_instance;
		CCore();
		~CCore();
};


class CCore2
{
	SINGLE(CCore2);
	private:
		CCore2();
		~CCore2();
		HWND m_hWnd;	//windows handle
		POINT m_ptResolution;	//main window's Resolution
	public:
		//초기화 함수.
		int Init(HWND _hwnd, POINT _ptRe);
		//작업 진행 함수.
		void Progress();
};

/*
	지역
	전역
	정적 ( 데이터 영역 )
		1. 함수 내부 선언 -> 해당 함수에서만 접근이 가능하다. (전역변수와의 차이점)
		2. 파일에 선언 -> 다른 파일에 같은 이름의 전역 변수가 있을 경우 오류가 발생한다.
		3. 클래스 내부에 선언 -> 정적 멤버 (데이터 영역 사용) 객체를 아무리 많이 생성해도 데이터 영역에만 설정된 변수는 변하지 않는다. 클래스 내부에서만 접근이 가능하다.

	동적 메모리 할당으로 생성된 친구들 -> Heap 영역.
*/