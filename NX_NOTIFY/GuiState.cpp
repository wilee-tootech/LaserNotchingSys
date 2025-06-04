// GuiState.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GuiState.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "./EXTERN/FileMgr.h"
#include "./EXTERN/cttextctrl.h"

#include "resource.h"

// CGuiState 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGuiState, CDialogEx)

CGuiState*  GuiState = NULL;

CGuiState::CGuiState(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STATE_DLG, pParent)
{
	m_strMsg	= _T("");
	m_nStateNo	= -1;
	m_nStep		= 1;

	m_nTimerID		= 1;
	m_nTimerDelay	= 300;
}

CGuiState::~CGuiState()
{
	if(m_brsDlg) DeleteObject(m_brsDlg);
}

void CGuiState::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGuiState, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGuiState 메시지 처리기입니다.

BOOL CGuiState::Create(CWnd* pParentWnd)
{
	return Create(MAKEINTRESOURCE(IDD_STATE_DLG), pParentWnd);
}

BOOL CGuiState::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CGuiState::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if(nCtlColor == CTLCOLOR_DLG)
	{
		hbr = m_brsDlg;
		return hbr;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CGuiState::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(m_nTimerID);
	CDialogEx::OnClose();
}


void CGuiState::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		SetTimer(m_nTimerID, m_nTimerDelay, NULL);
		SetStatusDescription();
	}
}


void CGuiState::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CExtDllState State;
	CClientDC dc(this);
	//회전용.
	HDC hMemDC;
	HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hOldBitmap;
	hOldBitmap = NULL;
	hBitmap1 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW1));
	hBitmap2 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW2));
	hBitmap3 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW3));
	hBitmap4 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW4));
	hMemDC	 = CreateCompatibleDC(dc);

	//Mask용
	HDC hMaskMemDC;
	HBITMAP hBitmapMask, hOldBitmapMask;
	hOldBitmapMask = NULL;
	hBitmapMask = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEMASK));
	hMaskMemDC = CreateCompatibleDC(dc);
	hOldBitmapMask = (HBITMAP)SelectObject(hMaskMemDC,hBitmapMask);

	switch(m_nStep)
	{
	case 1: 
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap1);
		m_nStep++;
		break;
	case 2: 
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap2);
		m_nStep++;
		break;
	case 3: 
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap3);
		m_nStep++;
		break;
	case 4: 
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap4);
		m_nStep = 1;
		break;
	}

	BitBlt(dc,20,20,300,300,hMaskMemDC,0,0,SRCCOPY);
	BitBlt(dc,20,20,300,300,hMemDC,0,0,SRCAND);


	SelectObject(hMaskMemDC, hOldBitmapMask);
	SelectObject(hMemDC, hOldBitmap);

	DeleteObject(hBitmap1);
	DeleteObject(hBitmap2);
	DeleteObject(hBitmap3);
	DeleteObject(hBitmap4);
	DeleteDC(hMemDC);

	DeleteObject(hBitmapMask);
	DeleteDC(hMaskMemDC);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CGuiState::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int cx = GetSystemMetrics(SM_CXSCREEN); // 가로
	int cy = GetSystemMetrics(SM_CYSCREEN); // 세로

	RECT rect;
	GetWindowRect(&rect);    // 해당 윈도우의 크기를 구한다.
	int left = (cx - (rect.right - rect.left)) / 2;  // Dialog 중앙에 위치할 x값
	int top = (cy - (rect.bottom - rect.top)) / 2;  // Dialog 중앙에 위치할 y값

	MoveWindow(left, top + 250, rect.right - rect.left, rect.bottom - rect.top, true);
	m_brsDlg = CreateSolidBrush(RGB(0,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGuiState::SetStatusDescription()
{
	CFileMgr* FileMgr = new CFileMgr;
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	if(FileMgr->GetDirExists(strPath) == false)
	{
		FileMgr->CreateUserDir(strPath);
	}

	strPath += ALARM_CONFIG_FILE_NAME;

	if(FileMgr->GetFileExists(strPath) == false)
	{
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection = TEXT("");
	CString strAlarm   = TEXT("");

	strSection = _T("STATE LIST");
	strAlarm.Format(_T("%d"),m_nStateNo);
	//Alarm List
	m_strMsg = FileMgr->ReadString(strSection, strAlarm, strPath);

	strAlarm.Format(_T("STATE NO : %d"),m_nStateNo);
	SetWindowText(strAlarm);

	CCttextctrl* pAlarmMsg = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_MSG);
	pAlarmMsg->SetCaption(m_strMsg);
	delete FileMgr;
}

void CGuiState::SetStateNumber(int nStateNo)
{
	m_nStateNo = nStateNo;
}
