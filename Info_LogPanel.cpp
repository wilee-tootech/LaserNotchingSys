// Info_LogPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Info_LogPanel.h"
#include "./Include/EXTERN/FileMgr.h"
#include "./RECIPE_MODULE/RecipeManager.h"

// CInfo_LogPanel

#define LOG_DIRECTORY_NAME "\\LOG\\"

IMPLEMENT_DYNCREATE(CInfo_LogPanel, CProjectBaseView)

CInfo_LogPanel::CInfo_LogPanel()
	: CProjectBaseView(CInfo_LogPanel::IDD)
{

}

CInfo_LogPanel::~CInfo_LogPanel()
{
}

void CInfo_LogPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FPSPREAD_LOG, m_spreadLog);
}

BEGIN_MESSAGE_MAP(CInfo_LogPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR, &CInfo_LogPanel::OnMcnSelectMonthcalendar1)
END_MESSAGE_MAP()


// CInfo_LogPanel 진단입니다.

#ifdef _DEBUG
void CInfo_LogPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfo_LogPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfo_LogPanel 메시지 처리기입니다.
void CInfo_LogPanel::Init()
{
	Open();
}


void CInfo_LogPanel::Open()
{
	CFileMgr* FileMgr = new CFileMgr;

	//CString strPath = FileMgr->GetNowExePath();
	CString strPath  = RecipeMgr->m_StRecipePath.m_strEquimentPath;
	PathRemoveFileSpec(strPath.GetBuffer(_MAX_PATH));
	strPath.ReleaseBuffer(-1);
	strPath += LOG_DIRECTORY_NAME;
	

	if(FileMgr->GetDirExists(strPath) == FALSE)
	{
		FileMgr->CreateUserDir(strPath);
	}

	//2025.03.21 현재설정된 날짜로 조회
	CTime t;
	CMonthCalCtrl *pCalendar = (CMonthCalCtrl*)GetDlgItem( IDC_MONTHCALENDAR );   
	pCalendar->GetCurSel(t);  
	CString strDate;
	strDate.Format( _T("%d-%02d-%02d"), t.GetYear(), t.GetMonth(), t.GetDay());  


	//strPath += FileMgr->GetDateTime_YYYY_MM_DD();
	strPath += strDate;
	strPath += _T(".txt");


	if(FileMgr->GetFileExists(strPath) == FALSE)
	{
		if(FileMgr->CreateUserFile(strPath) == FALSE)
		{
			delete FileMgr;
			return;
		}
	}

	int nFileLineCount = FileMgr->GetFileLineCount(strPath);


	//0 , 1  , 2 
	//No,Time,DESCRIPTION
	m_spreadLog.SetReDraw(FALSE);	
	m_spreadLog.SetMaxRows(nFileLineCount); //열 셋팅
	m_spreadLog.SetMaxCols(2);	  //행 셋팅

	CString strTemp = TEXT("");
	int i = 0;

	m_spreadLog.SetCol(0);
	m_spreadLog.SetRow(0);

	m_spreadLog.SetText(_T("NO"));
	m_spreadLog.SetCol(1);
	m_spreadLog.SetText(_T("Date Time"));
	m_spreadLog.SetCol(2);
	m_spreadLog.SetText(_T("Description"));




	for(i=0;i<nFileLineCount+1;i++)
	{
		m_spreadLog.SetRowHeight(i,20); //SetRowHeight
	}

	for(i=0;i<3;i++)
	{
		switch(i)
		{
		case 0:
			m_spreadLog.SetColWidth(i,10);
			break;
		case 1:
			m_spreadLog.SetColWidth(i,30);
			break;
		case 2:
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			if (screenWidth < 1500)
			{
				m_spreadLog.SetColWidth(i,96);
			} else
			{
				m_spreadLog.SetColWidth(i,70);
			}
			break;
		}
	}

	m_spreadLog.SetCol(0);
	for(i=0;i<nFileLineCount;i++)
	{
		m_spreadLog.SetRow(i+1);
		strTemp.Format(_T("%d"),i+1);
		m_spreadLog.SetText(strTemp);
	}


	//Jam Log 출력.
	vector<CString> vec;
	vector<CString>::iterator itr;
	CString strSource = TEXT("");

	FILE* f = NULL;
	TCHAR szBuffer[512];
	int  nRow = 1;
	int  nCol = 1;

	CString strLogMsg = TEXT("");

	memset(szBuffer,0,sizeof(szBuffer));


	_tfopen_s(&f,strPath,_T("r"));

	std::wstring strConvert;
	if(f != NULL)
	{
		while(_fgetts(szBuffer,512,f)) //_fgetts
		{
			//FileMgr->Convert_MultiByteCharToWideChar(szBuffer,strConvert);
			m_spreadLog.SetRow(nRow);
			m_spreadLog.SetCol(nCol);
			//strSource = strConvert.c_str();
			strSource = (CString)szBuffer;
			if(FileMgr->SetStringParsing(strSource,',',&vec))
			{
				for(itr = vec.begin(); itr != vec.end(); itr++)
				{
					m_spreadLog.SetCol(nCol);
					strLogMsg = (*itr);
					strLogMsg.TrimRight(_T("\r\n"));
					m_spreadLog.SetText(strLogMsg);
					nCol++;
				}
			}
			vec.clear();
			nRow++;
			nCol=1;
		}
	}

	m_spreadLog.SetReDraw(TRUE);
	fclose(f);
	delete FileMgr;
}


//void CInfo_LogPanel::Open()
//{
//	CFileMgr* FileMgr = new CFileMgr;
//
//	//CString strPath = FileMgr->GetNowExePath();
//	CString strPath  = RecipeMgr->m_StRecipePath.m_strEquimentPath;
//	PathRemoveFileSpec(strPath.GetBuffer(_MAX_PATH));
//	strPath.ReleaseBuffer(-1);
//	strPath += LOG_DIRECTORY_NAME;
//	
//
//	if(FileMgr->GetDirExists(strPath) == FALSE)
//	{
//		FileMgr->CreateUserDir(strPath);
//	}
//
//
//	strPath += FileMgr->GetDateTime_YYYY_MM();
//	strPath += _T(".txt");
//
//	if(FileMgr->GetFileExists(strPath) == FALSE)
//	{
//		if(FileMgr->CreateUserFile(strPath) == FALSE)
//		{
//			delete FileMgr;
//			return;
//		}
//	}
//
//	int nFileLineCount = FileMgr->GetFileLineCount(strPath);
//
//
//	//0 , 1  , 2 
//	//No,Time,DESCRIPTION
//	m_spreadLog.SetReDraw(FALSE);	
//	m_spreadLog.SetMaxRows(nFileLineCount); //열 셋팅
//	m_spreadLog.SetMaxCols(2);	  //행 셋팅
//
//	CString strTemp = TEXT("");
//	int i = 0;
//
//	m_spreadLog.SetCol(0);
//	m_spreadLog.SetRow(0);
//
//	m_spreadLog.SetText(_T("NO"));
//	m_spreadLog.SetCol(1);
//	m_spreadLog.SetText(_T("Date Time"));
//	m_spreadLog.SetCol(2);
//	m_spreadLog.SetText(_T("Description"));
//
//
//
//
//	for(i=0;i<nFileLineCount+1;i++)
//	{
//		m_spreadLog.SetRowHeight(i,20); //SetRowHeight
//	}
//
//	for(i=0;i<3;i++)
//	{
//		switch(i)
//		{
//		case 0:
//			m_spreadLog.SetColWidth(i,10);
//			break;
//		case 1:
//			m_spreadLog.SetColWidth(i,30);
//			break;
//		case 2:
//			m_spreadLog.SetColWidth(i,96);
//			break;
//		}
//	}
//
//	m_spreadLog.SetCol(0);
//	for(i=0;i<nFileLineCount;i++)
//	{
//		m_spreadLog.SetRow(i+1);
//		strTemp.Format(_T("%d"),i+1);
//		m_spreadLog.SetText(strTemp);
//	}
//
//
//	//Jam Log 출력.
//	vector<CString> vec;
//	vector<CString>::iterator itr;
//	CString strSource = TEXT("");
//
//	FILE* f = NULL;
//	TCHAR szBuffer[512];
//	int  nRow = 1;
//	int  nCol = 1;
//
//	CString strLogMsg = TEXT("");
//
//	memset(szBuffer,0,sizeof(szBuffer));
//
//
//	_tfopen_s(&f,strPath,_T("r"));
//
//	std::wstring strConvert;
//	if(f != NULL)
//	{
//		while(_fgetts(szBuffer,512,f)) //_fgetts
//		{
//			//FileMgr->Convert_MultiByteCharToWideChar(szBuffer,strConvert);
//			m_spreadLog.SetRow(nRow);
//			m_spreadLog.SetCol(nCol);
//			//strSource = strConvert.c_str();
//			strSource = (CString)szBuffer;
//			if(FileMgr->SetStringParsing(strSource,',',&vec))
//			{
//				for(itr = vec.begin(); itr != vec.end(); itr++)
//				{
//					m_spreadLog.SetCol(nCol);
//					strLogMsg = (*itr);
//					strLogMsg.TrimRight(_T("\r\n"));
//					m_spreadLog.SetText(strLogMsg);
//					nCol++;
//				}
//			}
//			vec.clear();
//			nRow++;
//			nCol=1;
//		}
//	}
//
//	m_spreadLog.SetReDraw(TRUE);
//	fclose(f);
//	delete FileMgr;
//}

void CInfo_LogPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static BOOL bFirstConnected = FALSE;

	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		if(bFirstConnected)
			Init();
		else
			bFirstConnected = TRUE;
	}
}


BOOL CInfo_LogPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	return TRUE;
	//return CProjectBaseView::OnEraseBkgnd(pDC);
}


void CInfo_LogPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0));
    ShowScrollBar(SB_BOTH, FALSE);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	if (screenWidth < 1500)
    {
        // 70% 비율
        double scale = 0.9;

        // 내부 컨트롤 크기 조정
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // 다이얼로그 좌표로 변환

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height());
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
    }
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
}


void CInfo_LogPanel::OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	Open();
}
