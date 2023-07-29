#ifdef _MY_MFC
#include <afxwin.h>
//initiate application program class
class CMain : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
//initiate main window class
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	~CMainFrame();

protected:
	//fx == function
	//application framework
	//tx == treatment
	//rx == receiver
	//tx == transfer
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};
CMain theApp;

BOOL CMain::InitInstance()
{
	m_pMainWnd = new CMainFrame();
	(*m_pMainWnd).ShowWindow(m_nCmdShow);
	return TRUE;
}

CMainFrame::CMainFrame()
{
	Create(NULL, _T("HellowMFC"));
}

CMainFrame::~CMainFrame()
{

}
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
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



#endif
