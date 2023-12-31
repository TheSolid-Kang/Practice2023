#ifdef _MY_WIN32
#include <Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hwnd;
	MSG msg = { 0 };

	//윈도우 클래스 초기화 및 운영체제에 등록
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//CS_HREDRAW나 CS_VREDRAW는 클라이언트 영역(작업영역, 사용자 영역)의 폭과 높이가 변경되었을 경우 전부 다시 그리도록 해준다.
	wndClass.lpfnWndProc = WndProc;//함수 
	wndClass.cbClsExtra = NULL;//여분 메모리 0바이트
	wndClass.cbWndExtra = NULL;//여분 메모리 0바이트
	wndClass.hInstance = hInstance; // 매개변수로 받은 인스턴스 핸들
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//아이콘 모양
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//흰색 배경
	wndClass.lpszMenuName = NULL; //메뉴(NULL -> 메뉴 없음)
	wndClass.lpszClassName = TEXT("Hello Class");//윈도우 클래스 이름
	if (false == RegisterClass(&wndClass))
		return 1;

	//윈도우 생성 후 화면에 출력
	hwnd = CreateWindow(TEXT("Hello Class") //lpClassName
		, TEXT("Hellow SDK") //, lpWindowName
		, WS_OVERLAPPEDWINDOW//, dwStyle
		, CW_USEDEFAULT//, x
		, CW_USEDEFAULT//, y
		, CW_USEDEFAULT//, nWidth
		, CW_USEDEFAULT//, nHeight 
		, NULL//, hWndParent
		, NULL//, hMenu
		, hInstance//, hInstance
		, NULL);//, lpParam

	ShowWindow(hwnd, nCmdShow);


	//메시지 큐에 담긴 메시지 하나씩 꺼내서 처리한다.
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//CloseHandle(hInstance);
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT massge, WPARAM wParam, LPARAM lPram)
{
	HDC hdc;
	PAINTSTRUCT paint_struct;
	const TCHAR* str = TEXT("Hellow, SDK");

	//발생한 메시지의 종류에 따라 처리하는 로직 구현
	switch (massge)
	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("마우스 클릭"), TEXT("마우스 메시지"), MB_OK);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &paint_struct);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &paint_struct);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//응용 프로그램이 처리하지 못 한 메시지를 운영체제가 처리하도록 하는 함수
	return DefWindowProc(hwnd, massge, wParam, lPram);
}


#endif
