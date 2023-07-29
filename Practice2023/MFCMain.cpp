#ifdef _MY_MFC
#include "MFCMain.h"

#pragma region CMain //CWinApp
CMain theApp;

BOOL CMain::InitInstance()
{
	m_pMainWnd = new CMainFrame();//afxwin.h 에 있는 변수
	(*m_pMainWnd).ShowWindow(m_nCmdShow);//afxwin.h 에 있는 변수
	return TRUE;
}
#pragma endregion


#pragma region  CMainFrame // FrameWnd
void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	const TCHAR* msg = _T("Hellow MFC");
	dc.TextOut(100, 100, msg, lstrlen(msg));
}
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(_T("마우스 메시지!"), _T("마우스 메시지"));
}

#pragma endregion 

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



#endif
