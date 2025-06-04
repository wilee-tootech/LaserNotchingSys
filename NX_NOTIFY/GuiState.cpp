// GuiState.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GuiState.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "./EXTERN/FileMgr.h"
#include "./EXTERN/cttextctrl.h"

#include "resource.h"

// CGuiState ��ȭ �����Դϴ�.

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


// CGuiState �޽��� ó�����Դϴ�.

BOOL CGuiState::Create(CWnd* pParentWnd)
{
	return Create(MAKEINTRESOURCE(IDD_STATE_DLG), pParentWnd);
}

BOOL CGuiState::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CGuiState::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if(nCtlColor == CTLCOLOR_DLG)
	{
		hbr = m_brsDlg;
		return hbr;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


void CGuiState::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	KillTimer(m_nTimerID);
	CDialogEx::OnClose();
}


void CGuiState::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(bShow)
	{
		SetTimer(m_nTimerID, m_nTimerDelay, NULL);
		SetStatusDescription();
	}
}


void CGuiState::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CExtDllState State;
	CClientDC dc(this);
	//ȸ����.
	HDC hMemDC;
	HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hOldBitmap;
	hOldBitmap = NULL;
	hBitmap1 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW1));
	hBitmap2 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW2));
	hBitmap3 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW3));
	hBitmap4 = (HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ROTATEARROW4));
	hMemDC	 = CreateCompatibleDC(dc);

	//Mask��
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	int cx = GetSystemMetrics(SM_CXSCREEN); // ����
	int cy = GetSystemMetrics(SM_CYSCREEN); // ����

	RECT rect;
	GetWindowRect(&rect);    // �ش� �������� ũ�⸦ ���Ѵ�.
	int left = (cx - (rect.right - rect.left)) / 2;  // Dialog �߾ӿ� ��ġ�� x��
	int top = (cy - (rect.bottom - rect.top)) / 2;  // Dialog �߾ӿ� ��ġ�� y��

	MoveWindow(left, top + 250, rect.right - rect.left, rect.bottom - rect.top, true);
	m_brsDlg = CreateSolidBrush(RGB(0,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
