// Info_JamPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Info_JamPanel.h"
#include "./Include/EXTERN/FileMgr.h"

#include <vector>
#include <locale>

using std::vector;
using namespace std;

#define JAM_DIRECTORY_NAME "\\JAM\\"

// CInfo_JamPanel

IMPLEMENT_DYNCREATE(CInfo_JamPanel, CProjectBaseView)

CInfo_JamPanel::CInfo_JamPanel()
	: CProjectBaseView(CInfo_JamPanel::IDD)
{

}

CInfo_JamPanel::~CInfo_JamPanel()
{
}

void CInfo_JamPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FPSPREAD_JAM_LOG, m_spreadJam);
}

BEGIN_MESSAGE_MAP(CInfo_JamPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CInfo_JamPanel 진단입니다.

#ifdef _DEBUG
void CInfo_JamPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfo_JamPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfo_JamPanel 메시지 처리기입니다.
void CInfo_JamPanel::Init()
{
	Open();
}

void CInfo_JamPanel::Open()
{
	CFileMgr* FileMgr = new CFileMgr;

	CString strPath = FileMgr->GetNowExePath();
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

	int nFileLineCount = FileMgr->GetFileLineCount(strPath);


	//0 , 1      , 2  , 3
	//No,Error No,Time,DESCRIPTION
	m_spreadJam.SetReDraw(FALSE);	
	m_spreadJam.SetMaxRows(nFileLineCount); //열 셋팅
	m_spreadJam.SetMaxCols(3);	  //행 셋팅

	CString strTemp = TEXT("");
	int i = 0;

	m_spreadJam.SetCol(0);
	m_spreadJam.SetRow(0);

	m_spreadJam.SetText(_T("NO"));
	m_spreadJam.SetCol(1);
	m_spreadJam.SetText(_T("Error No"));
	m_spreadJam.SetCol(2);
	m_spreadJam.SetText(_T("Date Time"));
	m_spreadJam.SetCol(3);
	m_spreadJam.SetText(_T("Description"));




	for(i=0;i<nFileLineCount+1;i++)
	{
		m_spreadJam.SetRowHeight(i,20); //SetRowHeight
	}

	for(i=0;i<4;i++)
	{
		switch(i)
		{
		case 0:
		case 1:
			m_spreadJam.SetColWidth(i,10); //SetColWidth
			break;
		case 2:
			m_spreadJam.SetColWidth(i,20);
			break;
		case 3:
			m_spreadJam.SetColWidth(i,96);
			break;
		}
	}

	m_spreadJam.SetCol(0);
	for(i=0;i<nFileLineCount;i++)
	{
		m_spreadJam.SetRow(i+1);
		strTemp.Format(_T("%d"),i+1);
		m_spreadJam.SetText(strTemp);
	}


	//Jam Log 출력.
	vector<CString> vec;
	vector<CString>::iterator itr;
	CString strSource = TEXT("");

	FILE* f = NULL;
	TCHAR szBuffer[512];
	int  nRow = 1;
	int  nCol = 1;

	CString strErrorMsg = TEXT("");


	memset(szBuffer,0,sizeof(szBuffer));


	_tfopen_s(&f,strPath,_T("r"));

	//std::wstring strConvert;

	//wchar_t* szLocale = _tsetlocale(LC_ALL, NULL);
	//wchar_t* szOldLocale = _tcsdup(szLocale);
	//TCHAR *szLocale = _tsetlocale(LC_ALL, _T("")); 
	//TCHAR* szOldLocale = _tcsdup(szLocale);


	_tsetlocale(LC_ALL, _T("Korean"));

	if(f != NULL)
	{
		while(_fgetts(szBuffer,512,f)) //_fgetts
		{

			//FileMgr->Convert_MultiByteCharToWideChar(szBuffer,strConvert);
			m_spreadJam.SetRow(nRow);
			m_spreadJam.SetCol(nCol);
			//strSource = strConvert.c_str();
			strSource = (CString)szBuffer;
			if(FileMgr->SetStringParsing(strSource,',',&vec))
			{
				for(itr = vec.begin(); itr != vec.end(); itr++)
				{
					m_spreadJam.SetCol(nCol);

					strErrorMsg = (*itr);
					strErrorMsg.TrimRight(_T("\r\n"));

					m_spreadJam.SetText(strErrorMsg);
					nCol++;
				}
			}
			vec.clear();
			nRow++;
			nCol=1;
		}
	}

	m_spreadJam.SetReDraw(TRUE);
	fclose(f);
	delete FileMgr;
	//free(szOldLocale);
}

void CInfo_JamPanel::Display()
{

}

void CInfo_JamPanel::OnShowWindow(BOOL bShow, UINT nStatus)
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


BOOL CInfo_JamPanel::OnEraseBkgnd(CDC* pDC)
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


void CInfo_JamPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
}
