#pragma once
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
	CMainFrame() { Create(NULL, _T("HellowMFC")); }
	~CMainFrame() { }

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