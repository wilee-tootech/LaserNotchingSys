// GuiError.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GuiError.h"
#include "afxdialogex.h"

#include "./EXTERN/FileMgr.h"
#include "./EXTERN/cttextctrl.h"
#include "ExtDllState.h"
#include <wingdi.h>
#include "resource.h"
#include <locale>


// CGuiError 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGuiError, CDialogEx)
CGuiError *GuiError = NULL;

CGuiError::CGuiError(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ERROR_DLG, pParent)
{
	CExtDllState State;
	m_nErrorNo			= -1;
	m_nAlarmNo			= -1;
	m_nTimerDelayTime	= 50;
	m_nDispCount		= 1000/m_nTimerDelayTime;
	m_bDisp				= FALSE;
	m_bError			= FALSE;
	m_bAlarm			= FALSE;
	
}

CGuiError::~CGuiError()
{
	CExtDllState State;
	if(m_brsDlg) DeleteObject(m_brsDlg);
}

void CGuiError::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState State;
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGuiError, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CGuiError 메시지 처리기입니다.


BOOL CGuiError::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}
BOOL CGuiError::Create(CWnd* pParentWnd)
{
	CExtDllState State;
	return Create(MAKEINTRESOURCE(IDD_ERROR_DLG),pParentWnd);
}

HBRUSH CGuiError::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CExtDllState State;

	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if(nCtlColor == CTLCOLOR_DLG)
	{
		hbr = m_brsDlg;
		return m_brsDlg;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CGuiError::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CExtDllState State;

	KillTimer(ERROR_DLG_TIMER_ID);
	CDialogEx::OnClose();
}


void CGuiError::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CExtDllState State;
	m_nDispCount++;

	CClientDC dc(this);

	if((m_nDispCount*m_nTimerDelayTime) >= 1000)
	{
		m_bDisp = !m_bDisp;
		m_nDispCount = 0;
	}

	if(m_bDisp) // 20*50 == 100
	{
		//Visible
		HDC hMemDC;
		HBITMAP hBitMap, hOldBitmap;
		int bx, by;
		BITMAP bit;

		//비트맵 로딩
		//hBitMap = (HBITMAP) LoadImage(NULL, TEXT("image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		hBitMap     =(HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ERROR));
		//hBitMap     =(HBITMAP)LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ERROR), IMAGE_BITMAP, 0, 0, 0);
		//메모리 DC 생성.
		hMemDC		= CreateCompatibleDC(dc);
		//hBitMap이 선택되기 전의 핸들을 저장해 둔다.
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitMap);
		//비트맵 정보를 알아낸다.
		GetObject(hBitMap, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
        //RGB(192.192.192) Gray color를 투명하게 만들고 그린다.
		TransparentBlt(dc,40,100,bx,by, hMemDC, 0, 0, bx, by, RGB(255,255,255));
		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitMap);
		DeleteDC(hMemDC);
	}
	else
	{
		//Visible
		CRect rt;
		rt.top = 100;
		rt.left = 40;
		rt.right = rt.left + 120;
		rt.bottom = rt.top + 100;

		InvalidateRect(&rt);

		HDC hMemDC;
		HBITMAP hBitMap, hOldBitmap;
		int bx, by;
		BITMAP bit;

		//비트맵 로딩
		//hBitMap = (HBITMAP) LoadImage(NULL, TEXT("image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		hBitMap     =(HBITMAP)LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ERROR_DISABLE));
		//hBitMap     =(HBITMAP)LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ERROR), IMAGE_BITMAP, 0, 0, 0);
		//메모리 DC 생성.
		hMemDC		= CreateCompatibleDC(dc);
		//hBitMap이 선택되기 전의 핸들을 저장해 둔다.
		hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitMap);
		//비트맵 정보를 알아낸다.
		GetObject(hBitMap, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;


		//RGB(192.192.192) Gray color를 투명하게 만들고 그린다.
		TransparentBlt(dc,40,100,bx,by, hMemDC, 0, 0, bx, by, RGB(0,0,0));
		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitMap);
		DeleteDC(hMemDC);


	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CGuiError::OnInitDialog()
{
	CExtDllState State;
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int cx = GetSystemMetrics(SM_CXSCREEN); // 가로
	int cy = GetSystemMetrics(SM_CYSCREEN); // 세로

	RECT rect;
	GetWindowRect(&rect);    // 해당 윈도우의 크기를 구한다.
	int left = (cx - (rect.right - rect.left)) / 2;  // Dialog 중앙에 위치할 x값
	int top = (cy - (rect.bottom - rect.top)) / 2;  // Dialog 중앙에 위치할 y값

	MoveWindow(left, top, rect.right - rect.left, rect.bottom - rect.top, true);

	m_brsDlg = CreateSolidBrush(RGB(0,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGuiError::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState State;
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		SetTimer(ERROR_DLG_TIMER_ID,m_nTimerDelayTime,NULL);
		SetStatusDescription();
	}
}

void CGuiError::SetStatusDescription()
{

	CFileMgr* FileMgr = new CFileMgr;
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	CString strSection = TEXT("");
	CString strError   = TEXT("");
	CString strErrorList = TEXT("");

	CString strErrorListCoorection1 = TEXT("");
	CString strErrorListCoorection2 = TEXT("");
	CString strErrorListDisp		= TEXT("");

	if(FileMgr->GetDirExists(strPath) == FALSE)
	{
		FileMgr->CreateUserDir(strPath);
	}
	if(m_bError)
	{
		SetDlgItemText(IDC_CTTEXTCTRL_TITLE, _T("ERROR"));
		strPath += ERROR_CONFIG_FILE_NAME;
		strSection = _T("ERROR LIST");
		strError.Format(_T("%d"),m_nErrorNo);
		
	}
	else
	{
		SetDlgItemText(IDC_CTTEXTCTRL_TITLE, _T("ALARM"));
		strPath += ALARM_CONFIG_FILE_NAME;
		strSection = _T("ALARM  LIST");
		strError.Format(_T("%d"),m_nAlarmNo);

	}

	if(FileMgr->GetFileExists(strPath) == FALSE)
	{
		if(FileMgr->CreateUserFile(strPath) == FALSE)
		{
			delete FileMgr;
			return;
		}
	}


	//Error List or Alarm List
	strErrorList   = FileMgr->ReadString(strSection, strError, strPath);
	int nStrCount  = strErrorList.GetLength();
	int nFindIndex = strErrorList.Find(_T("\\n"));

	if(nStrCount > 0)
	{
		if(nFindIndex > -1)
		{
			strErrorListCoorection1 = strErrorList.Left(nFindIndex-2); //64 39 39+2
			strErrorListCoorection2 = strErrorList.Mid(nFindIndex+2,nStrCount-(nFindIndex+2));
		}
		else
		{
			strErrorListCoorection1 = strErrorList;
		}
	}

	if(nFindIndex > -1)
	{
		m_strErrorMsg.Format(_T("%s\n%s"),strErrorListCoorection1,strErrorListCoorection2);
		strErrorListDisp = strErrorListCoorection1 + " " + strErrorListCoorection2;
	}
	else
	{
		m_strErrorMsg.Format(_T("%s"),strErrorListCoorection1);
		strErrorListDisp = strErrorListCoorection1;
	}

	if(m_bError)
		strError.Format(_T("Error NO : %d"),m_nErrorNo);
	else
		strError.Format(_T("Alarm NO : %d"),m_nAlarmNo);

	SetWindowText(strError);

	//Action List
	strSection = _T("ACTION LIST");
	strError.Format(_T("%d"),m_nErrorNo);

	CString strActionList = TEXT("");

	CString strActionListCoorection[5] = {_T(""),};

	CString strActionListDisp		= TEXT("");


	
	//Error List
	strActionList   = FileMgr->ReadString(strSection, strError, strPath);

	int nCnt = 0;
	TCHAR szSeps[]		= _T("/");
	TCHAR *szToken		= NULL;
	TCHAR *szContext	= NULL;
	//2021.01.07 jjsjong
	//szToken = _tcstok_s((wchar_t*)strActionList.GetBuffer(),szSeps,&szContext);
	szToken = _tcstok_s( (TCHAR *)(const TCHAR *)strActionList.GetBuffer(), szSeps, &szContext );

	while(szToken != NULL)
	{

		if(nCnt < 5)
		{
			strActionListCoorection[nCnt].Format(_T("%s"),szToken,&szContext);
			nCnt++;
		}

		//szToken = _tcstok_s(NULL,szSeps,&szContext);
		szToken = _tcstok_s( NULL, szSeps, &szContext );

	}

	switch (nCnt)
	{
	case 1: 
		strActionListDisp.Format(_T("%s")		
			,strActionListCoorection[0]);
		break;
	case 2:
		strActionListDisp.Format(_T("%s\n%s")	
			,strActionListCoorection[0], 
			strActionListCoorection[1]);
		break;
	case 3:
		strActionListDisp.Format(_T("%s\n%s\n%s")	
			,strActionListCoorection[0]
			,strActionListCoorection[1]
			,strActionListCoorection[2]);
		break;
	case 4:
		strActionListDisp.Format(_T("%s\n%s\n%s\n%s")
			,strActionListCoorection[0]
			,strActionListCoorection[1]
			,strActionListCoorection[2]
			,strActionListCoorection[3]);
		break;
	case 5:
		strActionListDisp.Format(_T("%s\n%s\n%s\n%s\n%s")	
			,strActionListCoorection[0]
			,strActionListCoorection[1]
			,strActionListCoorection[2]
			,strActionListCoorection[3]
			,strActionListCoorection[4]);
		break;
	}



		//Display
	CCttextctrl* pErrorMsg = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_MSG);
	pErrorMsg->SetCaption(m_strErrorMsg);

	CCttextctrl* pActionMsg = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_ACTION);
	pActionMsg->SetCaption(strActionListDisp);

	//Error List Write

	strPath = FileMgr->GetNowExePath();
	strPath += JAM_DIRECTORY_NAME;

	if(FileMgr->GetDirExists(strPath) == FALSE)
	{
		FileMgr->CreateUserDir(strPath);
	}


	strPath += FileMgr->GetDateTime_YYYY_MM();
	strPath += _T(".txt");

	if(FileMgr->GetFileExists(strPath) == FALSE)
	{
		if(FileMgr->CreateUserFile(strPath) == FALSE)
		{
			delete FileMgr;
			return;
		}
	}

	FILE* f = NULL;
	CString strJam = TEXT("");
	//2021.01.07 jjsjong
	//wchar_t* szLocale = _tsetlocale(LC_ALL, NULL);
	//wchar_t* szOldLocale = _tcsdup(szLocale);
	TCHAR *szLocale = _tsetlocale(LC_ALL, _T("")); 
	TCHAR* szOldLocale = _tcsdup(szLocale);

	_tsetlocale(LC_ALL, _T("Korean"));
	strJam.Format(_T("%d,%s,%s\n"),m_nErrorNo,FileMgr->GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(),strErrorListDisp);

	if(FileMgr->GetFileExists(strPath) == false)
		_tfopen_s(&f, strPath,_T("w+"));
	else
		_tfopen_s(&f, strPath,_T("a+"));

	if(f != NULL)
	{
		_ftprintf(f,strJam);
	}

	if(f != NULL)
	{
		fclose(f);
		f = NULL;
	}
	delete FileMgr;
	free(szOldLocale);

}

void CGuiError::SetErrorNumber(int nErrorrNo)
{
	CExtDllState State;
	m_nErrorNo = nErrorrNo;
}


void CGuiError::SetAlarmNumber(int nAlarmNo)
{
	CExtDllState State;
	m_nAlarmNo = nAlarmNo;
}



void CGuiError::SetError(BOOL bFlag)
{
	CExtDllState State;
	m_bError = bFlag;
}


void CGuiError::SetAlarm(BOOL bFlag)
{
	CExtDllState State;
	m_bAlarm = bFlag;
}


