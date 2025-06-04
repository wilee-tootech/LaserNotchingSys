// MainFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxwin.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "PointerContainer.h"
#include "FieldParameter.h"
#include "MainFormView.h"
#include "Defines.h"
#include "Device.h"
#include "InitialTable.h"
#include "TransUnit.h"
#include "NX_KEYPAD\NumberKeyPad.h"

#include "./Include/EXTERN/CColorDefine.h"
#include "./Control/ctpush.h"
#include "./Control/cttextctrl.h"
#include "Control\ControlHeader.h"


#include <stdlib.h>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


// CMainFormView
#define TM_ENC_CHECK		0x10
#define TM_SCANNER_CHECK    0x12
#define TM_STATUS_BUSY		0x13

#define TM_AGING_TEST		0x14

#define MAX_LENGTH					2000//400// 2000mm 까지만 보여주자

IMPLEMENT_DYNCREATE(CMainFormView, CProjectBaseView)

	CMainFormView::CMainFormView()
	: CProjectBaseView(CMainFormView::IDD)
{

	CPointerContainer::SetCMainFormView(this);
	m_DlgBackgroundBrush.CreateSolidBrush(RGB(0x31,0x3e,0x50));

	m_minX = -100;//c->xAxis()->getMinValue();
	m_maxX = 100;//c->xAxis()->getMaxValue();
	m_minY = -100;//c->yAxis()->getMinValue();
	m_maxY = 100;//c->yAxis()->getMaxValue();
	m_pDrawThread1 = NULL;
	m_pDrawThread2 = NULL;
	m_DrawThreadAlive1 = FALSE;
	m_DrawThreadAlive2 = FALSE;

	m_bEncCheckedFlag = TRUE;
	m_bEncCheckedFlag2 = TRUE;

	m_bEncCheckedNonFlag = FALSE;
	m_bEncCheckedNonFlag2 = FALSE;

	m_dEncLaserOnPos = 0;
	m_encoderPosition = 0;
	// m_encoderPositionHEAD2 = 0;

	m_fScaleX = 1.0f; 
	m_fScaleY = 1.0f;
}

CMainFormView::~CMainFormView()
{
	if(m_ScannerHEAD1Vewer.m_hWnd != NULL)
		delete m_ScannerHEAD1Vewer.getChart();

	if(m_ScannerHEAD2Vewer.m_hWnd != NULL)
		delete m_ScannerHEAD2Vewer.getChart();

	if( m_pDrawThread1 != NULL )
	{
		if ( WaitForSingleObject(m_pDrawThread1,1000) == WAIT_TIMEOUT)
			TerminateThread(m_pDrawThread1,0);
		m_pDrawThread1 = NULL;
		m_DrawThreadAlive1 = FALSE;
	}

	if( m_pDrawThread2 != NULL )
	{
		if ( WaitForSingleObject(m_pDrawThread2,1000) == WAIT_TIMEOUT)
			TerminateThread(m_pDrawThread2,0);
		m_pDrawThread2 = NULL;
		m_DrawThreadAlive2 = FALSE;
	}
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCANNER_VIEWER1, m_ScannerHEAD1Vewer);
	DDX_Control(pDX, IDC_SCANNER_VIEWER2, m_ScannerHEAD2Vewer);

	DDX_Control(pDX, IDC_CONTROL_VIEWER1, m_NotchControlVewer1);
	DDX_Control(pDX, IDC_CONTROL_VIEWER2, m_NotchControlVewer2);
	DDX_Control(pDX, IDC_CONTROL_VIEWER3, m_NotchControlVewer3);
	DDX_Control(pDX, IDC_CONTROL_VIEWER4, m_NotchControlVewer4);
	DDX_Control(pDX, IDC_CONTROL_VIEWER5, m_NotchControlVewer5);
	DDX_Control(pDX, IDC_CONTROL_VIEWER6, m_NotchControlVewer6);

	// 메인화면 HEAD1, HEAD2 전체길이 및 노칭길이 기록용
	DDX_Control(pDX, IDC_FPSPREAD_HEAD1_ENC, m_SpreadEncHEAD1);
	DDX_Control(pDX, IDC_FPSPREAD_HEAD2_ENC, m_SpreadEncHEAD2);

	DDX_Control(pDX, IDC_CTLISTCTRL_LOG, m_LogList);
}

BEGIN_MESSAGE_MAP(CMainFormView, CProjectBaseView)
	ON_BN_CLICKED(IDOK, &CMainFormView::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainFormView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CMainFormView::OnBnClickedButtonInit)
//	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMainFormView::OnBnClickedButtonClear)
//	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainFormView::OnBnClickedButtonDelete)
//	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMainFormView::OnBnClickedButtonReset)
	ON_WM_TIMER()
	

	ON_CONTROL(CVN_ViewPortChanged, IDC_SCANNER_VIEWER1, OnViewPortChanged)
	ON_CONTROL(CVN_ViewPortChanged, IDC_SCANNER_VIEWER2, OnViewPortChanged2)

	ON_STN_CLICKED(IDC_MARK_IMAGE, &CMainFormView::OnStnClickedMarkImage)
	ON_STN_CLICKED(IDC_SCANNER_VIEWER2, &CMainFormView::OnStnClickedScannerViewer2)
	ON_STN_CLICKED(IDC_MARK_IMAGE2, &CMainFormView::OnStnClickedMarkImage2)
	ON_STN_CLICKED(IDC_SCANNER_VIEWER1, &CMainFormView::OnStnClickedScannerViewer1)
	ON_BN_CLICKED(IDC_BUTTON_ADD4, &CMainFormView::OnBnClickedButtonAdd4)
//	ON_BN_CLICKED(IDC_BUTTON_INIT4, &CMainFormView::OnBnClickedButtonInit4)
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_CONTROL_VIEWER1, &CMainFormView::OnStnClickedControlViewer1)
	
	
//	ON_BN_CLICKED(IDC_BUTTON_IO_TEST, &CMainFormView::OnBnClickedButtonIoTest)
//	ON_EN_CHANGE(IDC_SETED_ENC_POS, &CMainFormView::OnEnChangeSetedEncPos)
END_MESSAGE_MAP()


// CMainFormView 진단입니다.

#ifdef _DEBUG
void CMainFormView::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainFormView::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainFormView 메시지 처리기입니다.


void CMainFormView::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


// BOOL CMainFormView::OnInitDialog()
// {
// 	CProjectBaseView::OnInitDialog();
// 	return 0;
// }
void CMainFormView::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0, 0));
    ShowScrollBar(SB_BOTH, FALSE);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    if (screenWidth < 1500)
    {
        // 70% 비율
        double scale = 0.88;

        // 다이얼로그 크기 조정
        /*CRect dlgRect;
        GetWindowRect(&dlgRect);
        int newWidth = static_cast<int>(dlgRect.Width() * scale);
        int newHeight = static_cast<int>(dlgRect.Height() * scale);
        MoveWindow(dlgRect.left, dlgRect.top, newWidth, newHeight);*/

        // 내부 컨트롤 크기 조정
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // 다이얼로그 좌표로 변환

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height() * scale);
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top * scale);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
    }


	//m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG2);

	LOGFONT lf;

	this->GetFont()->GetLogFont(&lf);

	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;

	wsprintf(lf.lfFaceName, _T("%s"), TEXT("Tahoma"));

	CFont NewFont;

	NewFont.CreateFontIndirect(&lf);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while (pWnd)
	{
		pWnd->SetFont(&NewFont);
		pWnd = pWnd->GetNextWindow();
	}

	NewFont.Detach();

	InitEncDisplay(RTC_CARD_NUM_1);
	InitEncDisplay(RTC_CARD_NUM_2);

	SetTimer(TM_ENC_CHECK, 50, NULL);
	SetTimer(TM_SCANNER_CHECK, 1000, NULL);
	SetTimer(TM_STATUS_BUSY, 300, NULL);


	m_ScannerHEAD1Vewer.updateViewPort(true, true);
	m_ScannerHEAD2Vewer.updateViewPort(true, true);

	m_NotchControlVewer1.updateViewPort(true, true);
	m_NotchControlVewer2.updateViewPort(true, true);
	m_NotchControlVewer3.updateViewPort(true, true);
	m_NotchControlVewer4.updateViewPort(true, true);
	m_NotchControlVewer5.updateViewPort(true, true);
	m_NotchControlVewer6.updateViewPort(true, true);


	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();

	IniUtil _iniUtil;
	m_strHEAD1Name = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("HEAD1NAME"), sitePath, m_strHEAD1Name);

	CString strSiteName;

	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("siteName"), sitePath, strSiteName);
	if(strSiteName == "SDI_POUCH")
	{
		GetDlgItem(IDC_CTHEAD2_BUSY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXTCTRL26)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD1_BOARD_TEMP4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD1_BOARD_TEMP7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD2_BOARD_TEMP_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD2_BOARD_TEMP_Y)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXTCTRL31)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD1_BOARD_TEMP8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD1_BOARD_TEMP9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD2_SCANNER_TEMP_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD2_SCANNER_TEMP_Y)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTHEAD2_ENC_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTHEAD2_ECN_CNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FPSPREAD_HEAD2_ENC)->ShowWindow(SW_HIDE);

		CWnd* pWnd = GetDlgItem(IDC_CTLISTCTRL_LOG);
		if (pWnd)
		{
			CRect rect;
			pWnd->GetWindowRect(&rect);
			ScreenToClient(&rect);
			rect.top -= 250;

			pWnd->MoveWindow(&rect);
		}

		pWnd = GetDlgItem(IDC_CTHEAD_EVENT_LOG);
		if (pWnd)
		{
			CRect rect;
			pWnd->GetWindowRect(&rect);
			ScreenToClient(&rect);     

			rect.OffsetRect(0, -250);  

			pWnd->MoveWindow(rect);
		}

	}


	RefreshIOViewer();
	//RefreshIOViewerHEAD2();
}


UINT CMainFormView::DrawThreaFunc1(LPVOID pParam)
{
	CDsp *pDsp = CDsp::GetInstance();
	CMainFormView *pDlg = (CMainFormView*)pParam;

	pDlg->m_previousIoState = -1;

	
	pDlg->m_DrawThreadAlive1 = TRUE;

	pDlg->updateIoState(FALSE);

	while(pDlg->m_DrawThreadAlive1)
	{
		if(pDlg->m_ScannerHEAD1Vewer.m_hWnd != NULL)
			pDlg->DrawScannerHead1(&pDlg->m_ScannerHEAD1Vewer);

		if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_LASER_ON)== TRUE)
			pDlg->updateIoState(TRUE);
		else
			pDlg->updateIoState(FALSE);

		Sleep(10);
	}


	return 0;
}


UINT CMainFormView::DrawThreaFunc2(LPVOID pParam)
{
	CDsp *pDsp = CDsp::GetInstance();
	CMainFormView *pDlg = (CMainFormView*) pParam;
	pDlg->m_DrawThreadAlive2 = TRUE;
	while(pDlg->m_DrawThreadAlive2)
	{
		if(pDlg->m_ScannerHEAD2Vewer.m_hWnd != NULL)
			pDlg->DrawScannerHead2(&pDlg->m_ScannerHEAD2Vewer);

		if(pDsp->nGetInputValue(RTC_CARD_NUM_2,RTC_SIG_I_LASER_ON)== TRUE)
			pDlg->updateIoStateHEAD2(TRUE);
		else
			pDlg->updateIoStateHEAD2(FALSE);


		Sleep(10);
	}
	return 0;
}

HBRUSH CMainFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	HBRUSH hbr = CProjectBaseView::OnCtlColor(pDC, pWnd, nCtlColor);

	CRect rect; 
	UINT nID = pWnd->GetDlgCtrlID();
	if(nCtlColor == CTLCOLOR_STATIC)
	{     
		if(nID == IDC_HEAD1_HEAD2 )
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(184,115,51));
			pDC->SetTextCharacterExtra(2);
			return (HBRUSH)::GetStockObject(BLACK_BRUSH);
		}
		else
		{
			pDC->SetBkColor(RGB(0x31,0x3e,0x50));
			pDC->SetTextColor(RGB(0xc5,0xc5,0xc5));

			return (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
	}
	hbr = (HBRUSH)m_DlgBackgroundBrush;
	return hbr;
}


void CMainFormView::UpdateInfo(void)
{
	CFieldParameter *CFieldParameter = CFieldParameter::GetInstance();
	_NOTCH_PATTERN_DATA m_stNotchPatternDataOfHEAD1 = CFieldParameter->GetHEAD1PatternDataOfKoem();
	_NOTCH_PATTERN_DATA m_stNotchPatternDataOfHEAD2 = CFieldParameter->GetHEAD2PatternDataOfKoem();

	CString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11,str12,str13,str14,str15,str16,str17,str18,str19,str20;
	str1.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth1);
	str2.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth2);
	str3.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth3);
	str4.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth4);
	str5.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth5);
	str6.Format("%.1f",m_stNotchPatternDataOfHEAD1.dPitchWidth6);

	str7.Format("%.1f",m_stNotchPatternDataOfHEAD1.dTabHeight);
	str8.Format("%.1f",m_stNotchPatternDataOfHEAD2.dTabHeight);
	str9.Format("%.1f",m_stNotchPatternDataOfHEAD1.dTabWidth);
	str10.Format("%.1f",m_stNotchPatternDataOfHEAD2.dTabWidth);

	str17.Format("%1.f",m_stNotchPatternDataOfHEAD1.dBuriedRegion);
	str18.Format("%1.f",m_stNotchPatternDataOfHEAD2.dBuriedRegion);

	str19.Format("%.1f",m_stNotchPatternDataOfHEAD1.dFlagVariableTotalLength + m_stNotchPatternDataOfHEAD1.dBuriedRegion);
	str20.Format("%.1f",m_stNotchPatternDataOfHEAD2.dFlagVariableTotalLength + m_stNotchPatternDataOfHEAD2.dBuriedRegion);

}

void CMainFormView::UpdateLog(CString strData)
{
	if( m_LogList.ListCount() > MAX_LOG_CNT )  
		m_LogList.ClearList();

	CString strTime;
	CString strDate;
	CString strLog;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;


	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}

	strLog.Format("%s-%s:%s", strDate, strTime, strData);
	m_LogList.AddItem(strLog);

}


void CMainFormView::LogAddData()
{
	// HEAD2
	const size_t maxIndex = 3;  // FIFO 최대 크기
    
	int nSize = m_listOfPositionsHEAD2.size();
	// FIFO 구조로 데이터 추가
	if (m_listOfPositionsHEAD2.size() >= maxIndex) 
	{
		// FIFO 유지: 가장 오래된 데이터 제거 (맨 앞의 요소 삭제)
		m_listOfPositionsHEAD2.erase(m_listOfPositionsHEAD2.begin());
		m_listOfPositionsHEAD2.push_back(m_recordedPositionsHEAD2);
	}
	else
	{
		m_listOfPositionsHEAD2.resize(maxIndex);
		m_listOfPositionsHEAD2[maxIndex-1] = m_recordedPositionsHEAD2;
	}

	size_t targetIndex = 2;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositionsHEAD2.size()) {
		selectedData  = m_listOfPositionsHEAD2[targetIndex];
	}
	nSize = m_listOfPositionsHEAD2.size();

	m_recordedPositionsHEAD2.clear();
	m_recordedPositionsHEAD2.shrink_to_fit();
}

void CMainFormView::OnBnClickedButtonAdd()
{
	const size_t maxIndex = 3;  // FIFO 최대 크기
    
	int nSize = m_listOfPositions.size();
	// FIFO 구조로 데이터 추가
	if (m_listOfPositions.size() >= maxIndex) 
	{
		// FIFO 유지: 가장 오래된 데이터 제거 (맨 앞의 요소 삭제)
		m_listOfPositions.erase(m_listOfPositions.begin());
		m_listOfPositions.push_back(m_recordedPositions);
	}
	else
	{
		m_listOfPositions.resize(maxIndex);
		m_listOfPositions[maxIndex-1] = m_recordedPositions;
	}

	size_t targetIndex = 2;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositions.size()) {
		selectedData  = m_listOfPositions[targetIndex];
	}
	nSize = m_listOfPositions.size();

	m_recordedPositions.clear();
	m_recordedPositions.shrink_to_fit();
}


void CMainFormView::OnBnClickedButtonInit()
{
	//printRecordedPositions();
	//KillTimer(TM_AGING_TEST);


	if(m_NotchControlVewer1.m_hWnd != NULL)
			DrawControlViewer1(&m_NotchControlVewer1);

	if(m_NotchControlVewer2.m_hWnd != NULL)
			DrawControlViewer2(&m_NotchControlVewer2);

	if(m_NotchControlVewer3.m_hWnd != NULL)
			DrawControlViewer3(&m_NotchControlVewer3);

	if(m_NotchControlVewer4.m_hWnd != NULL)
			DrawControlViewer4(&m_NotchControlVewer4);

	if(m_NotchControlVewer5.m_hWnd != NULL)
			DrawControlViewer5(&m_NotchControlVewer5);

	if(m_NotchControlVewer6.m_hWnd != NULL)
			DrawControlViewer6(&m_NotchControlVewer6);

	//m_encoderPosition = 0;

	//if(m_NotchControlVewer1.m_hWnd != NULL)
	//		DrawControlViewer1(&m_NotchControlVewer1);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//InitEncDisplay(RTC_CARD_NUM_1);
	//InitEncDisplay(RTC_CARD_NUM_2);

	/*addPerson(1, "Alice", 25);
    addPerson(2, "Bob", 30);
    addPerson(3, "Charlie", 22);

    std::cout << "\n--- 전체 목록 ---\n";
    printAll();

    std::cout << "\n--- ID 2 조회 ---\n";
    findPerson(2);

    std::cout << "\n--- ID 2 삭제 ---\n";
    removePerson(2);

    std::cout << "\n--- 전체 목록 ---\n";
    printAll();

    std::cout << "\n--- 전체 삭제 실행 ---\n";
    clearAll();

    std::cout << "\n--- 전체 목록 (삭제 후) ---\n";
    printAll();*/

}


//void CMainFormView::OnBnClickedButtonClear()
//{
//	m_listOfPositions.clear();
//	m_listOfPositions.shrink_to_fit();
//	//int nMaxRow = 20;
//	//int nMaxCol = 20;
//	//CString strTemp;
//	//m_SpreadEncHEAD1.SetReDraw(FALSE);
//
//
//	//for(int j = 1; j < nMaxRow  ;j++)
//	//{
//	//	m_SpreadEncHEAD1.SetColWidth(1,20);
//	//	m_SpreadEncHEAD1.SetCol(1);
//	//	m_SpreadEncHEAD1.SetRow(j);
//	//	strTemp.Format(_T(""), j);
//	//	m_SpreadEncHEAD1.SetText(strTemp);
//	//	//m_SpreadEncHEAD1.SetBackColor(RGB(61,178,213));
//
//	//	m_SpreadEncHEAD1.SetColWidth(2,20);
//	//	m_SpreadEncHEAD1.SetCol(2);
//	//	m_SpreadEncHEAD1.SetRow(j);
//	//	strTemp.Format(_T(""), j);
//	//	m_SpreadEncHEAD1.SetText(strTemp);
//	//	m_SpreadEncHEAD1.SetBackColor(clWhite);
//
//	//	m_SpreadEncHEAD1.SetColWidth(2,20);
//	//	m_SpreadEncHEAD1.SetCol(3);
//	//	m_SpreadEncHEAD1.SetRow(j);
//	//	strTemp.Format(_T(""), j);
//	//	m_SpreadEncHEAD1.SetText(strTemp);
//	//	m_SpreadEncHEAD1.SetBackColor(clWhite);
//
//	//	m_SpreadEncHEAD1.SetForeColor(CustomColor::colorBackGraund);
//	//	m_SpreadEncHEAD1.SetTypeHAlign(0);
//	//	m_SpreadEncHEAD1.SetTypeVAlign(2);
//
//
//
//	//}
//
//	//m_SpreadEncHEAD1.SetReDraw(TRUE);
//
//	//int nCurIndex = 0;
//	//nCurIndex = m_SpreadEncHEAD1.GetSelectionCount();
//
//	//nCurIndex = m_SpreadEncHEAD1.GetCol();
//	//nCurIndex = m_SpreadEncHEAD1.GetRow();
//
//	//nCurIndex = m_SpreadEncHEAD1.GetTopRow();
//
//	//nCurIndex = m_SpreadEncHEAD1.GetRow2();
//}


void CMainFormView::DrawControlViewer1(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     0         };
	//double dataX[] =      { 0,  700, 1400, 2100, 2800, 3500,	4200,  4900      };
	size_t targetIndex = 2;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositions.size()) {
		selectedData  = m_listOfPositions[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;
	int i=0;
	for (const auto& data : selectedData )
	{
		dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
	}
	
	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	else
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	
    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
	//------------------------------------ First Tab -------------------------------------------------------
	//ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY2, nSize2)).add(6.5);
 //   StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0x210def);
	//layer0_1->setXData(DoubleArray(dataX, nSize2));

	//------------------------------------ Laser On -------------------------------------------------------
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));



	// ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	//// Add step lines using the original and the reversed data
 //   StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0xf7f612);//linecolor change
 //   // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	//layer0->setXData(DoubleArray(dataX, nSize));


    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
	if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);


    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	// if (dataY2) delete[] dataY2;
	delete c;
}


void CMainFormView::DrawControlViewer2(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     1         };
	//double dataX[] =      { 0,  100, 110, 120, 130, 4000,  4050,  5000      };
	size_t targetIndex = 2;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositionsHEAD2.size()) {
		selectedData  = m_listOfPositionsHEAD2[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;

	int i=0;
	for (const auto& data : selectedData )
	{
		dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
	}

	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3 );
	}
	else
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);

    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));
    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
	if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);


    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	// if (dataY2) delete[] dataY2;

	delete c;
}


void CMainFormView::DrawControlViewer3(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     1         };
	//double dataX[] =      { 0,  100, 110, 120, 130, 4000,  4050,  5000      };
	size_t targetIndex = 1;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositions.size()) {
		selectedData  = m_listOfPositions[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();
	//if(nSize == 0)  nSize = 2;

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;

	int i=0;
	//if(nSize > 0)
	{
		for (const auto& data : selectedData )
		{
			dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
		}
	}

	//size_t targetIndex2 = 1;  // 가져올 인덱스 지정
	//std::vector<RecordedFirstTabData> selectedData2;
	//if (targetIndex2 < m_listOfFirstTabPositions.size()) {
	//	selectedData2  = m_listOfFirstTabPositions[targetIndex2];
	//}
	//int nSize2 = selectedData2.size();
	////if(nSize == 0)  nSize = 2;

	//double* dataY2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//i=0;
	////if(nSize > 0)
	//{
	//	for (const auto& data : selectedData2 )
	//	{
	//		dataY2[i] = data.ioState; i++;
	//	}
	//}
	//else
	//{
		
		/*dataY[0] =      0;      dataY[1] =      0;     dataY[2] =      0;
		dataY_Fill[0] = 1;      dataY_Fill[1] = 1;     dataY_Fill[2] = 1;
		dataX[0] =      0;      dataX[1] =      2000;  dataX[2] =      3000;*/
	//}
	
	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	else
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	
	/*ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY2, nSize2)).add(6.5);
    StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0x210def);
	layer0_1->setXData(DoubleArray(dataX, nSize2));
*/
    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));
    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
    if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);

    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	// if (dataY2) delete[] dataY2;

	delete c;
}


void CMainFormView::DrawControlViewer4(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     1         };
	//double dataX[] =      { 0,  100, 110, 120, 130, 4000,  4050,  5000      };
	size_t targetIndex = 1;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositionsHEAD2.size()) {
		selectedData  = m_listOfPositionsHEAD2[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();
	//if(nSize == 0)  nSize = 2;

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;

	int i=0;
	//if(nSize > 0)
	{
		for (const auto& data : selectedData )
		{
			dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
		}
	}

	//size_t targetIndex2 = 1;  // 가져올 인덱스 지정
	//std::vector<RecordedFirstTabData> selectedData2;
	//if (targetIndex2 < m_listOfFirstTabPositionsHEAD2.size()) {
	//	selectedData2  = m_listOfFirstTabPositionsHEAD2[targetIndex2];
	//}
	//int nSize2 = selectedData2.size();
	////if(nSize == 0)  nSize = 2;

	//double* dataY2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataY_Fill2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataX2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//i=0;
	////if(nSize > 0)
	//{
	//	for (const auto& data : selectedData2 )
	//	{
	//		dataY2[i] = data.ioState; dataX2[i] = data.position; dataY_Fill2[i] = 1; i++;
	//	}
	//}
	//else
	//{
		
		/*dataY[0] =      0;      dataY[1] =      0;     dataY[2] =      0;
		dataY_Fill[0] = 1;      dataY_Fill[1] = 1;     dataY_Fill[2] = 1;
		dataX[0] =      0;      dataX[1] =      2000;  dataX[2] =      3000;*/
	//}
	
	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3 );
	}
	else
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	

	/*ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY2, nSize2)).add(6.5);
    StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0x210def);
	layer0_1->setXData(DoubleArray(dataX2, nSize2));*/

    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));
    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
    if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);

    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	/*if (dataY2) delete[] dataY2;
	if (dataY_Fill2) delete[] dataY_Fill2;
	if (dataX2) delete[] dataX2;*/


	delete c;
}


void CMainFormView::DrawControlViewer5(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     1         };
	//double dataX[] =      { 0,  100, 110, 120, 130, 4000,  4050,  5000      };
	size_t targetIndex = 0;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositions.size()) {
		selectedData  = m_listOfPositions[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();
	//if(nSize == 0)  nSize = 2;

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;
	int i=0;
	//if(nSize > 0)
	{
		for (const auto& data : selectedData )
		{
			dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
		}
	}

	//size_t targetIndex2 = 0;  // 가져올 인덱스 지정
	//std::vector<RecordedFirstTabData> selectedData2;
	//if (targetIndex2 < m_listOfFirstTabPositions.size()) {
	//	selectedData2  = m_listOfFirstTabPositions[targetIndex2];
	//}
	//int nSize2 = selectedData2.size();
	////if(nSize == 0)  nSize = 2;

	//double* dataY2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataY_Fill2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataX2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//i=0;
	////if(nSize > 0)
	//{
	//	for (const auto& data : selectedData2 )
	//	{
	//		dataY2[i] = data.ioState; dataX2[i] = data.position; dataY_Fill2[i] = 1; i++;
	//	}
	//}
	//else
	//{
		
		/*dataY[0] =      0;      dataY[1] =      0;     dataY[2] =      0;
		dataY_Fill[0] = 1;      dataY_Fill[1] = 1;     dataY_Fill[2] = 1;
		dataX[0] =      0;      dataX[1] =      2000;  dataX[2] =      3000;*/
	//}
	
	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	else
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
/*
	ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY2, nSize2)).add(6.5);
    StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0x210def);
	layer0_1->setXData(DoubleArray(dataX2, nSize2));
	*/
    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));
    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
    if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);

    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	/*if (dataY2) delete[] dataY2;
	if (dataY_Fill2) delete[] dataY_Fill2;
	if (dataX2) delete[] dataX2;*/

	delete c;
}


void CMainFormView::DrawControlViewer6(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	//double dataY[] =      { 0,  0,   1,   0,   0,   1,     0,     0         };
	//double dataY_Fill[] = { 1,  1,   1,   1,   1,   1,     1,     1         };
	//double dataX[] =      { 0,  100, 110, 120, 130, 4000,  4050,  5000      };
	size_t targetIndex = 0;  // 가져올 인덱스 지정
	std::vector<RecordedData> selectedData;
	if (targetIndex < m_listOfPositionsHEAD2.size()) {
		selectedData  = m_listOfPositionsHEAD2[targetIndex];
	} else
	{
		RecordedData tmpData;
		tmpData.position = 0;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
		tmpData.position = 1;
		tmpData.ioState = TRUE;
		selectedData.push_back(tmpData);
		tmpData.position = 1000;
		tmpData.ioState = FALSE;
		selectedData.push_back(tmpData);
	}
	int nSize = selectedData.size();
	//if(nSize == 0)  nSize = 2;

	double* dataY = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataY_Fill = (nSize > 0) ? new double[nSize] : nullptr;
	double* dataX = (nSize > 0) ? new double[nSize] : nullptr;

	int i=0;
	//if(nSize > 0)
	{
		for (const auto& data : selectedData )
		{
			dataY[i] = data.ioState; dataX[i] = data.position; dataY_Fill[i] = 1; i++;
		}
	}

	//size_t targetIndex2 = 0;  // 가져올 인덱스 지정
	//std::vector<RecordedFirstTabData> selectedData2;
	//if (targetIndex2 < m_listOfFirstTabPositionsHEAD2.size()) {
	//	selectedData2  = m_listOfFirstTabPositionsHEAD2[targetIndex2];
	//}
	//int nSize2 = selectedData2.size();
	////if(nSize == 0)  nSize = 2;

	//double* dataY2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataY_Fill2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//double* dataX2 = (nSize2 > 0) ? new double[nSize2] : nullptr;
	//i=0;
	////if(nSize > 0)
	//{
	//	for (const auto& data : selectedData2 )
	//	{
	//		dataY2[i] = data.ioState; dataX2[i] = data.position; dataY_Fill2[i] = 1; i++;
	//	}
	//}

	//else
	//{
		
		/*dataY[0] =      0;      dataY[1] =      0;     dataY[2] =      0;
		dataY_Fill[0] = 1;      dataY_Fill[1] = 1;     dataY_Fill[2] = 1;
		dataX[0] =      0;      dataX[1] =      2000;  dataX[2] =      3000;*/
	//}
	
	 const char *labels[] = {"", "ENCODER LEN", "", "<*font,color=00aa22*>ON<*/font*> / <*font,color=cc2200*>OFF<*/font*> """, "", "LASER ON", ""};
	
	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_CONTROL_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	
	int nWidth = r.right;
	int nHeight = r.bottom;
	int nEdgeMargin = 0;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);
	TextBox *title = NULL;
	if(m_strHEAD1Name == "Anode")
	{
		strTemp = "CATHODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xC3C3C3 );
	}
	else
	{
		strTemp = "ANODE";
		title = c->addTitle(Chart::TopCenter,  LPSTR(LPCTSTR(strTemp)), "arialbd.ttf",  10, 0xda7948);
	}
	
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1,Chart::Transparent)->setGridColor(
        Chart::Transparent, 0x888888, Chart::Transparent, c->dashLineColor(0xcccccc,Chart::DotLine));

	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);
	c->yAxis()->setColors(Chart::TextColor);
	
	// Set the y axis labels
    c->yAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    // Set y-axis label style to 8pts Arial Bold
    c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0xeee308);

	/*ArrayMath shiftedLine0_1 = ArrayMath(DoubleArray(dataY2, nSize2)).add(6.5);
    StepLineLayer *layer0_1 = c->addStepLineLayer(shiftedLine0_1, 0x210def);
	layer0_1->setXData(DoubleArray(dataX2, nSize2));
	*/
    // Shift the data by 4.5, so instead of 0 - 1, it is now 4.5 to 5.5, or fluctuate around the y = 5 (Logic Line label) position.
    ArrayMath shiftedLine0 = ArrayMath(DoubleArray(dataY, nSize)).add(4.5);

	// Add step lines using the original and the reversed data
    StepLineLayer *layer0 = c->addStepLineLayer(shiftedLine0, 0xf7f612);//linecolor change
    // layer0->setXData(DoubleArray(dataX, sizeof(dataX)/sizeof(dataX[0])));
	layer0->setXData(DoubleArray(dataX, nSize));
    // To perform ON/OFF filling, we draw the logic line, and its reverse, and fill the region in between
    
	// Shift the data by 2.5, so instead of 0 - 1, it is now 2.5 to 3.5, or fluctuate around the y = 3 (ON/OFF Filing label) position.
    ArrayMath shiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).add(2.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine1 = ArrayMath(DoubleArray(dataY, nSize)).mul(-1).add(3.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer1 = c->addStepLineLayer(shiftedLine1, Chart::Transparent);
    layer1->addDataSet(reverseShiftedLine1, Chart::Transparent);
    layer1->setXData(DoubleArray(dataX, nSize));

    // Fill the region between the two step lines with green (00aa22) or red (cc2200), depending on whether the original or the reserve is higher.
    c->addInterLineLayer(layer1->getLine(0), layer1->getLine(1), 0x00aa22, 0xcc2200);

   
    // The ON Only filling is the same as ON/OFF filling, except the OFF filling color is transparent
    // Shift the data by 0.5, so instead of 0 - 1, it is now 0.5 to 1.5, or fluctuate around the y = 1 (ON Only Filing label) position.
    ArrayMath shiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).add(0.5);
    // Reverse the data, so the 0 becomes 1 and 1 becomes 0, and shift it as well.
    ArrayMath reverseShiftedLine2 = ArrayMath(DoubleArray(dataY_Fill,nSize)).mul(-1).add(1.5);

    // Add step lines using the original and the reversed data
    StepLineLayer *layer2 = c->addStepLineLayer(shiftedLine2, Chart::Transparent);
    layer2->addDataSet(reverseShiftedLine2, Chart::Transparent);
    layer2->setXData(DoubleArray(dataX, nSize ));

	//layer2->setAlignment(Chart::Center);
	layer2->addCustomDataLabel(0, 13, "End", "arialbd.ttf",0xffffff);
	
	//TextBox *t = c->addText(nWidth/2, nHeight-57, " 9999 mm ", "arialbi.ttf", 5, 0xffffff);
    //t->setBackground(0x008800, Chart::Transparent, Chart::softLighting());
   // t->setRoundedCorners(5);

    // Set the x axis to Transparent, with labels
    c->xAxis()->setColors(Chart::Transparent, 0xffffff);

	// Fill the region between the two step lines with green (00aa22) or transparent, depending on whether the original or the reserve is higher.
    if(m_strHEAD1Name == "Anode")
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xC3C3C3, Chart::Transparent);
	else
		c->addInterLineLayer(layer2->getLine(0), layer2->getLine(1), 0xda7948, Chart::Transparent);

    // Adjust the plot area size, such that the bounding box (inclusive of axes) is 10 pixels from the left edge, 10 pixels  below the title, 30 pixels from the
    // right edge, and 10 pixels above the bottom edge.
    c->packPlotArea(10, title->getHeight() + 10, c->getWidth() - 30, c->getHeight() - 10);


	viewer->setChart(c);
	
	viewer->ShowWindow(TRUE);

	if (dataY) delete[] dataY;
	if (dataY_Fill) delete[] dataY_Fill;
	if (dataX) delete[] dataX;
	/*if (dataY2) delete[] dataY2;
	if (dataY_Fill2) delete[] dataY_Fill2;
	if (dataX2) delete[] dataX2;*/
	delete c;
}

void CMainFormView::DrawScannerHead1(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	dResultX = 1.0;
	dResultY = 2.0;

	// 스캐너 누적 경로 확인용
	/*double dataX2[] = {0, 20, 30, 40, 50, 80, 100, 120, 130, 140, 150, 180, 200};
    double dataY2[] = {30,30, 30, 30, 30, 30,  30, 30,   30,  30,  30,  30,  30};*/
	//double dataX2[100];
	//double dataY2[100];
	/*pTransUnit->SetValueWithField(pDsp->GetPosX());
	dResultX = pTransUnit->GetValue(MM);
	pTransUnit->SetValueWithField(pDsp->GetPosY());
	dResultY = pTransUnit->GetValue(MM);*/
	//SetDlgItemText(IDC_SCANNER_POS, strTemp);

	double xPos,yPos;
#ifndef _SIMUL_

	//for(int i=0; i < 12; i++)
	{
		xPos = pDsp->nGetPosX(RTC_CARD_NUM_1);
		yPos = pDsp->nGetPosY(RTC_CARD_NUM_1);
		pTransUnit->SetValueWithField(xPos);
		dResultX = pTransUnit->GetValue(MM);
		pTransUnit->SetValueWithField(yPos);
		dResultY = pTransUnit->GetValue(MM);

		//dataX2[i] = dResultX;
		//dataY2[i] = dResultY;
	}
#else
	///For Test
	pTransUnit->SetValue(dResultX, MM);
	dResultX = pTransUnit->GetField();
	pTransUnit->SetValue(dResultY, MM);
	dResultY = pTransUnit->GetField();
	//dDoubleCuttingStartPos = pTransUnit->GetMM(nLineWidth, FIELD);
	pTransUnit->SetValueWithField(dResultX);
	dResultX = pTransUnit->GetValue(MM);
	pTransUnit->SetValueWithField(dResultY);
	dResultY = pTransUnit->GetValue(MM);
	//xPos = dResultX;
	//yPos = dResultY;
#endif
	strTemp.Format("Pos:%d(%.3f) , %d(%.3f)", pDsp->GetPosX(), dResultX, pDsp->GetPosY(), dResultY);
	//xPos = 0;
	//yPos = 0;

	double dataX0[] = {dResultX};
	double dataY0[] = {dResultY};

	

	RECT rect;
	GetClientRect( &rect);

	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_MARK_WND1);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	int nWidth = r.right-r.left;
	int nHeight = r.bottom-r.top;
	int nEdgeMargin = 5;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);

	//c->setPlotArea(55, 62, rect.right - 1, rect.bottom - 1, c->linearGradientColor(0, 55, 0, 335, 0x313e50,
	//   0x313e50), -1, 0xc5c5c5, 0xc5c5c5);
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1, -1, 0xA0A0A0, 0xA0A0A0 )
		->set4QBgColor(0x202020, 0x202020, 0x202020, 0x202020, 0x000000);

	c->setClipping();

	c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

	c->xAxis()->setWidth(1);
	c->yAxis()->setWidth(1);

	LegendBox *legendBox = c->addLegend( nWidth- 2 , 5, true, "arialbd.ttf", 8);
	legendBox->setAlignment(Chart::TopRight);
	legendBox->setBackground(0x40dddddd);

	// Add a titles to axes
	c->xAxis()->setTitle("Axis X");
	c->yAxis()->setTitle("Axis Y");

	// Set axes width to 2 pixels
	c->xAxis()->setWidth(2);
	c->yAxis()->setWidth(2);

	c->xAxis()->setColors(0x3333FF);
	c->yAxis()->setColors(0x3333FF);
	c->xAxis()->setTickDensity(50, 10);
	c->yAxis()->setTickDensity(50, 10);

//2025.03.04 Line Layer Test---------------------------------------------------------
	//LineLayer *layer1 = c->addLineLayer(DoubleArray(dataY2,
 //       sizeof(dataY2)/sizeof(dataY2[0])), 0xFF0000, "Scanner Pos");

 //   layer1->setXData(DoubleArray(dataX2, sizeof(dataX2)/sizeof(dataX2[0])));

 //   // Set the line width to 3 pixels
 //   layer1->setLineWidth(2);

 //   // Use 9 pixel square symbols for the data points
 //   layer1->getDataSet(0)->setDataSymbol(Chart::SquareSymbol, 9);
//-----------------------------------------------------------------------------------

	char buffer[256];
	sprintf(buffer, "[ %.3f,%.3f ]", dataX0[0],dataY0[0]);

	c->addScatterLayer(DoubleArray(dataX0, sizeof(dataX0) / sizeof(dataX0[0])), 
		DoubleArray(dataY0, sizeof(dataY0) / sizeof(dataY0[0])), buffer, 
		Chart::CircleShape, 11, 0xff3333);

	if (m_maxX == m_minX)
	{
		// The axis scale has not yet been set up. So this is the first time the chart is
		// drawn and it is drawn with no zooming. We can use auto-scaling to determine the
		// axis-scales, then remember them for future use. 

		// Explicitly auto-scale axes so we can get the axis scales
		c->layout();

		// Save the axis scales for future use
		m_minX = -(dMmSize/dScale);
		m_maxX = (dMmSize/dScale);
		m_minY = -(dMmSize/dScale);
		m_maxY = (dMmSize/dScale);
	}
	else
	{
		// Compute the zoomed-in axis scales using the overall axis scales and ViewPort size
		double xScaleMin = m_minX + (m_maxX - m_minX) * viewer->getViewPortLeft();
		double xScaleMax = m_minX + (m_maxX - m_minX) * (viewer->getViewPortLeft() + 
			viewer->getViewPortWidth());
		double yScaleMin = m_maxY - (m_maxY - m_minY) * (viewer->getViewPortTop() + 
			viewer->getViewPortHeight());
		double yScaleMax = m_maxY - (m_maxY - m_minY) * viewer->getViewPortTop();
		// *** use the following formula if you are using a log scale axis ***
		// double xScaleMin = minX * pow(maxX / minX, viewer->getViewPortLeft());
		// double xScaleMax = minX * pow(maxX / minX, viewer->getViewPortLeft() + 
		//     viewer->getViewPortWidth());
		// double yScaleMin = maxY * pow(minY / maxY, viewer->getViewPortTop() + 
		//    viewer->getViewPortHeight);
		// double yScaleMax = maxY * pow(minY / maxY, viewer->getViewPortTop());

		// Set the axis scales
		c->xAxis()->setLinearScale(xScaleMin, xScaleMax);
		c->xAxis()->setRounding(false, false);
		c->yAxis()->setLinearScale(yScaleMin, yScaleMax);
		c->yAxis()->setRounding(false, false);
	}


	viewer->setChart(c);
	//viewer->setImageMap(c->getHTMLImageMap("clickable", "",
	//    "title='[{dataSetName}] PositionX = {x} mm, PositionY = {value} mm'"));

	viewer->ShowWindow(TRUE);
	delete c;

}


void CMainFormView::DrawScannerHead2(CChartViewer *viewer)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dScale = pInitialTable->GetFieldScale();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDsp *pDsp = CDsp::GetInstance();
	CString strTemp;
	double dResultX,dResultY;

	dResultX = 1.0;
	dResultY = 2.0;

	/*pTransUnit->SetValueWithField(pDsp->GetPosX());
	dResultX = pTransUnit->GetValue(MM);
	pTransUnit->SetValueWithField(pDsp->GetPosY());
	dResultY = pTransUnit->GetValue(MM);*/
	//SetDlgItemText(IDC_SCANNER_POS, strTemp);

	double xPos,yPos;
#ifndef _SIMUL_
	xPos = pDsp->nGetPosX(RTC_CARD_NUM_2);
	yPos = pDsp->nGetPosY(RTC_CARD_NUM_2);
	pTransUnit->SetValueWithField(xPos);
	dResultX = pTransUnit->GetValue(MM);
	pTransUnit->SetValueWithField(yPos);
	dResultY = pTransUnit->GetValue(MM);
#else
	///For Test
	pTransUnit->SetValue(dResultX, MM);
	dResultX = pTransUnit->GetField();
	pTransUnit->SetValue(dResultY, MM);
	dResultY = pTransUnit->GetField();
	//dDoubleCuttingStartPos = pTransUnit->GetMM(nLineWidth, FIELD);
	pTransUnit->SetValueWithField(dResultX);
	dResultX = pTransUnit->GetValue(MM);
	pTransUnit->SetValueWithField(dResultY);
	dResultY = pTransUnit->GetValue(MM);
	//xPos = dResultX;
	//yPos = dResultY;
#endif
	//strTemp.Format("Pos:%d(%.3f) , %d(%.3f)", pDsp->GetPosX(), dResultX, pDsp->GetPosY(), dResultY);
	double dataX0[] = {dResultX};
	double dataY0[] = {dResultY};

	RECT rect;
	GetClientRect( &rect);

	CRect r;
	CWnd *pCtrl = GetDlgItem(IDC_MARK_WND2);  
	if(NULL != pCtrl){  // 주소를 제대로 얻었는지 체크한다.
		pCtrl->GetWindowRect(r);  // '확인'버튼의 '윈도우 영역 좌표'를 구함
		ScreenToClient(r);   // r변수에 저장된 좌표를 '클라이언트 영역 좌표'로 변환 함
	}
	int nWidth = r.right-r.left;
	int nHeight = r.bottom-r.top;
	int nEdgeMargin = 5;

	XYChart *c = new XYChart(r.right-r.left + nEdgeMargin, r.bottom-r.top + nEdgeMargin,  0x202020, 0x202020, 1);

	//c->setPlotArea(55, 62, rect.right - 1, rect.bottom - 1, c->linearGradientColor(0, 55, 0, 335, 0x313e50,
	//   0x313e50), -1, 0xc5c5c5, 0xc5c5c5);
	c->setPlotArea(nEdgeMargin/2, nEdgeMargin/2, nWidth, nHeight, -1, -1, -1, 0xA0A0A0, 0xA0A0A0 )
		->set4QBgColor(0x202020, 0x202020, 0x202020, 0x202020, 0x000000);

	c->setClipping();

	c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

	c->xAxis()->setWidth(1);
	c->yAxis()->setWidth(1);

	LegendBox *legendBox = c->addLegend( nWidth- 2 , 5, true, "arialbd.ttf", 8);
	legendBox->setAlignment(Chart::TopRight);
	legendBox->setBackground(0x40dddddd);

	// Add a titles to axes
	c->xAxis()->setTitle("Axis X");
	c->yAxis()->setTitle("Axis Y");

	// Set axes width to 2 pixels
	c->xAxis()->setWidth(2);
	c->yAxis()->setWidth(2);

	c->xAxis()->setColors(0x3333FF);
	c->yAxis()->setColors(0x3333FF);
	c->xAxis()->setTickDensity(50, 10);
	c->yAxis()->setTickDensity(50, 10);

	char buffer[256];
	sprintf(buffer, "[ %.3f,%.3f ]", dataX0[0],dataY0[0]);


	c->addScatterLayer(DoubleArray(dataX0, sizeof(dataX0) / sizeof(dataX0[0])), 
		DoubleArray(dataY0, sizeof(dataY0) / sizeof(dataY0[0])), buffer, 
		Chart::CircleShape, 11, 0xff3333);

	if (m_maxX == m_minX)
	{
		// The axis scale has not yet been set up. So this is the first time the chart is
		// drawn and it is drawn with no zooming. We can use auto-scaling to determine the
		// axis-scales, then remember them for future use. 

		// Explicitly auto-scale axes so we can get the axis scales
		c->layout();

		// Save the axis scales for future use
		m_minX = -(dMmSize/dScale);
		m_maxX = (dMmSize/dScale);
		m_minY = -(dMmSize/dScale);
		m_maxY = (dMmSize/dScale);
	}
	else
	{
		// Compute the zoomed-in axis scales using the overall axis scales and ViewPort size
		double xScaleMin = m_minX + (m_maxX - m_minX) * viewer->getViewPortLeft();
		double xScaleMax = m_minX + (m_maxX - m_minX) * (viewer->getViewPortLeft() + 
			viewer->getViewPortWidth());
		double yScaleMin = m_maxY - (m_maxY - m_minY) * (viewer->getViewPortTop() + 
			viewer->getViewPortHeight());
		double yScaleMax = m_maxY - (m_maxY - m_minY) * viewer->getViewPortTop();
		// *** use the following formula if you are using a log scale axis ***
		// double xScaleMin = minX * pow(maxX / minX, viewer->getViewPortLeft());
		// double xScaleMax = minX * pow(maxX / minX, viewer->getViewPortLeft() + 
		//     viewer->getViewPortWidth());
		// double yScaleMin = maxY * pow(minY / maxY, viewer->getViewPortTop() + 
		//    viewer->getViewPortHeight);
		// double yScaleMax = maxY * pow(minY / maxY, viewer->getViewPortTop());

		// Set the axis scales
		c->xAxis()->setLinearScale(xScaleMin, xScaleMax);
		c->xAxis()->setRounding(false, false);
		c->yAxis()->setLinearScale(yScaleMin, yScaleMax);
		c->yAxis()->setRounding(false, false);
	}


	viewer->setChart(c);
	//viewer->setImageMap(c->getHTMLImageMap("clickable", "",
	//   "title='[{dataSetName}] PositionX = {x} mm, PositionY = {value} mm'"));

	if(viewer->m_hWnd!= NULL)
		viewer->ShowWindow(TRUE);
	delete c;

}


//void CMainFormView::OnBnClickedButtonDelete()
//{
//	//int nRowCnt = m_SpreadEncHEAD1.GetRow();;
//	//m_SpreadEncHEAD1.DeleteRows(1, nRowCnt);
//
//}


//void CMainFormView::OnBnClickedButtonReset()
//{
//	CString strLog;
//	strLog = "AAAAAAAAAAAAAAAAA";
//	UpdateLog(strLog);
//	
//	CCttextctrl* pCcText	= NULL;
//	pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD1_BUSY); 
//	pCcText->SetForeColor(RGB(255,0,0));
//
//	m_SpreadEncHEAD1.Reset();
//	m_SpreadEncHEAD2.Reset();
//	InitEncDisplay(RTC_CARD_NUM_1);
//	InitEncDisplay(RTC_CARD_NUM_2);
//
//
//}


void CMainFormView::InitEncDisplay(int nHeadNo)
{
	int nMaxRow = 20;
	int nMaxCol = 20;

	int nCurrentIndex = 0;
	int i = 0;
	int nUnitColWidth	= 8;
	int nUnitRowWidth	= 45;

	if(nHeadNo == RTC_CARD_NUM_1)
	{
		m_SpreadEncHEAD1.SetReDraw(FALSE);

		m_SpreadEncHEAD1.SetColWidth(1,10);
		m_SpreadEncHEAD1.SetCol(1);
		m_SpreadEncHEAD1.SetRow(0);
		m_SpreadEncHEAD1.SetText(_T("시간"));

		m_SpreadEncHEAD1.SetColWidth(2,10);
		m_SpreadEncHEAD1.SetCol(2);
		m_SpreadEncHEAD1.SetRow(0);
		m_SpreadEncHEAD1.SetText(_T("패턴길이(mm)"));
		//m_SpreadTapPosInfo.SetBackColor(RGB(23, 150, 253));
		m_SpreadEncHEAD1.SetBackColor(clBlack);
		m_SpreadEncHEAD1.SetForeColor(clWhite);

		m_SpreadEncHEAD1.SetColWidth(3,10);
		m_SpreadEncHEAD1.SetCol(3);
		m_SpreadEncHEAD1.SetRow(0);
		m_SpreadEncHEAD1.SetText(_T("오차"));
		//m_SpreadTapPosInfo.SetBackColor(RGB(23, 150, 253));
		m_SpreadEncHEAD1.SetBackColor(clBlack);
		m_SpreadEncHEAD1.SetForeColor(clWhite);

		m_SpreadEncHEAD1.SetMaxRows(nMaxRow);
		m_SpreadEncHEAD1.SetReDraw(TRUE);
	}
	else
	{

		m_SpreadEncHEAD2.SetReDraw(FALSE);
		m_SpreadEncHEAD2.SetColWidth(1,10);
		m_SpreadEncHEAD2.SetCol(1);
		m_SpreadEncHEAD2.SetRow(0);
		m_SpreadEncHEAD2.SetText(_T("시간"));

		m_SpreadEncHEAD2.SetColWidth(2,10);
		m_SpreadEncHEAD2.SetCol(2);
		m_SpreadEncHEAD2.SetRow(0);
		m_SpreadEncHEAD2.SetText(_T("패턴길이(mm)"));
		//m_SpreadTapPosInfo.SetBackColor(RGB(23, 150, 253));
		m_SpreadEncHEAD2.SetBackColor(clBlack);
		m_SpreadEncHEAD2.SetForeColor(clWhite);

		m_SpreadEncHEAD2.SetColWidth(3,10);
		m_SpreadEncHEAD2.SetCol(3);
		m_SpreadEncHEAD2.SetRow(0);
		m_SpreadEncHEAD2.SetText(_T("오차"));
		//m_SpreadTapPosInfo.SetBackColor(RGB(23, 150, 253));
		m_SpreadEncHEAD2.SetBackColor(clBlack);
		m_SpreadEncHEAD2.SetForeColor(clWhite);

		m_SpreadEncHEAD2.SetMaxRows(nMaxRow);
		m_SpreadEncHEAD1.SetReDraw(TRUE);
	}

}


void CMainFormView::OnTimer(UINT_PTR nIDEvent)
{
	LONG HEAD1EncoderX,HEAD1EncoderY,HEAD2EncoderX,HEAD2EncoderY, HEAD1EncoderTemp,HEAD2EncoderTemp;
	HEAD1EncoderX=0;HEAD1EncoderY=0;HEAD2EncoderX=0;HEAD2EncoderY=0; HEAD1EncoderTemp=0;HEAD2EncoderTemp=0;
	CString encoderValue;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	UINT uBusy, uPos;

	if(nIDEvent == TM_ENC_CHECK)
	{
		unsigned short status = 0;
		unsigned short value = 0;
		status = pDsp->n_GetIoStatus(RTC_CARD_NUM_1);

		value = status & (unsigned short)((double)pow(2.0, RTC_SIG_O_ACTUAL_FIRST_TAB));
		value = value >> RTC_SIG_O_ACTUAL_FIRST_TAB;
		if(value == 1 && m_bEncCheckedFlag == FALSE)
		{
			m_previousIoState = -1;
			// 기존값 비교해서 반대값 넣어주기
			updateIoState(TRUE);
			updateIoState(FALSE);

			m_bEncCheckedFlag = TRUE;
			m_bEncCheckedNonFlag = FALSE;
			UpdateEncInfo(RTC_CARD_NUM_1);
			OnBnClickedButtonAdd();
			RefreshIOViewer();
		}
		else if(value == 0 && m_bEncCheckedNonFlag == FALSE)
		{
			m_bEncCheckedFlag = FALSE;
			m_bEncCheckedNonFlag = TRUE;
			UpdateEncInfo(RTC_CARD_NUM_1);
		}

		if(pDsp->GetBoardCount() > 1)
		{
			status = pDsp->n_GetIoStatus(RTC_CARD_NUM_2);
			value = status & (unsigned short)((double)pow(2.0, RTC_SIG_O_ACTUAL_FIRST_TAB));
			value = value >> RTC_SIG_O_ACTUAL_FIRST_TAB;

			if(value == 1 && m_bEncCheckedFlag2 == FALSE)
			{
				m_previousIoStateHEAD2 = -1;
				// 기존값 비교해서 반대값 넣어주기
				updateIoStateHEAD2(TRUE);
				updateIoStateHEAD2(FALSE);

				m_bEncCheckedFlag2 = TRUE;
				m_bEncCheckedNonFlag2 = FALSE;
				UpdateEncInfo(RTC_CARD_NUM_2);
				LogAddData();
				//RefreshIOViewerHEAD2();
			}
			//else if(value == 0)
			else if(value == 0 && m_bEncCheckedNonFlag2 == FALSE)
			{
				m_bEncCheckedFlag2 = FALSE;
				m_bEncCheckedNonFlag2 = TRUE;
				UpdateEncInfo(RTC_CARD_NUM_2);
			}
		}
		
		pDsp->GetEncodeHEAD1(HEAD1EncoderX,HEAD1EncoderY);
		pDsp->GetEncodeHEAD2(HEAD2EncoderX,HEAD2EncoderY);

		//Y축 엔코더가 위치제어용으로 사용중
		double fieldKX;
		if(pFieldParameter->GetKX() < 0)
		{
			fieldKX = -pFieldParameter->GetKX();
		} else
		{
			fieldKX = pFieldParameter->GetKX();		
		}
		m_encoderPosition =  HEAD1EncoderY / fieldKX;
		m_encoderPositionHEAD2 =  HEAD2EncoderY / fieldKX;

		encoderValue.Format("H1_0 %.3f mm", HEAD1EncoderY / fieldKX);
		SetDlgItemText(IDC_CTHEAD1_ECN_CNT,encoderValue);

		encoderValue.Format("H2_0 %.3f mm", HEAD2EncoderY / fieldKX);
		SetDlgItemText(IDC_CTHEAD2_ECN_CNT,encoderValue);

	



	}
	else if(nIDEvent == TM_SCANNER_CHECK)
	{
		KillTimer(TM_SCANNER_CHECK);
		DrawScannerHead1(&m_ScannerHEAD1Vewer);
		if (m_pDrawThread1 == NULL)
			m_pDrawThread1 = ::AfxBeginThread(DrawThreaFunc1, this);

		//if (m_pDrawThread2 == NULL)
		//	m_pDrawThread2 = ::AfxBeginThread(DrawThreaFunc2, this);

	}

	else if(nIDEvent == TM_STATUS_BUSY)
	{
		CCttextctrl* pCcText	= NULL;
		CString strData;
		UINT statusword_raw, temperature;
		double temperature_C;
		

		if(pDsp->GetMarkStatusHEAD1())
		{
			pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD1_BUSY ); 
			pCcText->SetForeColor(RGB(255,0,0));
			//SetTimer(TM_STATUS_BUSY, TM_CHECK_RTC_PERIOD_1, NULL);
		
			//LedOnOff(IDC_PIC_HEAD1_BUSY, LED_GREEN_ON);
		}
		else
		{
			pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD1_BUSY ); 
			pCcText->SetForeColor(RGB(255,255,255));
			//GetDlgItem(IDC_CTPUSH_AUTO)->EnableWindow(TRUE);
			
			//LedOnOff(IDC_PIC_HEAD1_BUSY, LED_GREEN_OFF);
		}

		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0514); 
		Sleep(10);
		statusword_raw = n_get_value(RTC_CARD_NUM_1, 1);
		temperature = statusword_raw & 0xFFFF;
		temperature_C = temperature / 160.0; 
		strData.Format("%0.2f", temperature_C);
		SetDlgItemText(IDC_CTHEAD1_SCANNER_TEMP_X, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0514); 
		Sleep(10);
		statusword_raw = n_get_value(RTC_CARD_NUM_1, 2);
		temperature = statusword_raw & 0xFFFF;
		temperature_C = temperature / 160.0; 
		strData.Format("%0.2f", temperature_C);
		SetDlgItemText(IDC_CTHEAD1_SCANNER_TEMP_Y, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0515); 
		Sleep(10);
		statusword_raw = n_get_value(RTC_CARD_NUM_1, 1);
		temperature = statusword_raw & 0xFFFF;
		temperature_C = temperature / 160.0; 
		strData.Format("%0.2f", temperature_C);
		SetDlgItemText(IDC_CTHEAD1_BOARD_TEMP_X, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0515); 
		Sleep(10);
		statusword_raw = n_get_value(RTC_CARD_NUM_1, 2);
		temperature = statusword_raw & 0xFFFF;
		temperature_C = temperature / 160.0; 
		strData.Format("%0.2f", temperature_C);
		SetDlgItemText(IDC_CTHEAD1_BOARD_TEMP_Y, strData);

		if(pDsp->GetBoardCount() > 1)
		{
			if(pDsp->GetMarkStatusHEAD2())
			{
				pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD2_BUSY ); 
				pCcText->SetForeColor(RGB(255,0,0));
				//SetTimer(TM_STATUS_BUSY, TM_CHECK_RTC_PERIOD_1, NULL);
				//TC.Clear();

				//LedOnOff(IDC_PIC_HEAD2_BUSY, LED_GREEN_ON);
			}
			else
			{
				pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD2_BUSY ); 
				pCcText->SetForeColor(RGB(255,255,255));
				//GetDlgItem(IDC_CTPUSH_AUTO)->EnableWindow(TRUE);
			
				//LedOnOff(IDC_PIC_HEAD2_BUSY, LED_GREEN_OFF);
			}

			n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0514); 
			Sleep(10);
			statusword_raw = n_get_value(RTC_CARD_NUM_2, 1);
			temperature = statusword_raw & 0xFFFF;
			temperature_C = temperature / 160.0; 
			strData.Format("%0.2f", temperature_C);
			SetDlgItemText(IDC_CTHEAD2_SCANNER_TEMP_X, strData);

			n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0514); 
			Sleep(10);
			statusword_raw = n_get_value(RTC_CARD_NUM_2, 2);
			temperature = statusword_raw & 0xFFFF;
			temperature_C = temperature / 160.0; 
			strData.Format("%0.2f", temperature_C);
			SetDlgItemText(IDC_CTHEAD2_SCANNER_TEMP_Y, strData);

			n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0515); 
			Sleep(10);
			statusword_raw = n_get_value(RTC_CARD_NUM_2, 1);
			temperature = statusword_raw & 0xFFFF;
			temperature_C = temperature / 160.0; 
			strData.Format("%0.2f", temperature_C);
			SetDlgItemText(IDC_CTHEAD2_BOARD_TEMP_X, strData);

			n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0515); 
			Sleep(10);
			statusword_raw = n_get_value(RTC_CARD_NUM_2, 2);
			temperature = statusword_raw & 0xFFFF;
			temperature_C = temperature / 160.0; 
			strData.Format("%0.2f", temperature_C);
			SetDlgItemText(IDC_CTHEAD2_BOARD_TEMP_Y, strData);
		}
	}
	else if(nIDEvent == TM_AGING_TEST)
	{
		m_encoderPosition++;
		SetDlgItemInt(IDC_CTHEAD1_ECN_CNT, m_encoderPosition);
	}

	CProjectBaseView::OnTimer(nIDEvent);
}


void CMainFormView::UpdateEncInfo(int nCardNo)
{
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	long encoder0_0, encoder1_0,encoder0_1,encoder1_1 ;
	if(nCardNo == RTC_CARD_NUM_1)
	{
		pDsp->ReadEncodeHEAD1(encoder0_0, encoder1_0,encoder0_1,encoder1_1);
		//encoderValue.Format("%d,%d,%d,%d diff: %f", encoder0_0, encoder1_0,encoder0_1,encoder1_1, abs(encoder1_0-encoder1_1) / pFieldParameter->GetKX()); 
		int nCurIndex = m_SpreadEncHEAD1.GetRow();
		CString strTemp;
		if(nCurIndex > 20) {
			m_SpreadEncHEAD1.Reset();
			InitEncDisplay(RTC_CARD_NUM_1);
			m_SpreadEncHEAD1.SetReDraw(TRUE);
			nCurIndex = m_SpreadEncHEAD1.GetRow();
		}

		nCurIndex++;

		m_SpreadEncHEAD1.SetColWidth(1,10);
		m_SpreadEncHEAD1.SetCol(1);
		m_SpreadEncHEAD1.SetRow(nCurIndex);
		CTime t = CTime::GetCurrentTime(); 
		strTemp.Format("%d시 %d분 %d초", t.GetHour(), t.GetMinute(), t.GetSecond()); 
		m_SpreadEncHEAD1.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD1.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD1.SetBackColor(clGray);

		m_SpreadEncHEAD1.SetColWidth(2,10);
		m_SpreadEncHEAD1.SetCol(2);
		m_SpreadEncHEAD1.SetRow(nCurIndex);
		strTemp.Format(_T("%.3f mm"), encoder1_1 / -pFieldParameter->GetKX());
		m_SpreadEncHEAD1.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD1.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD1.SetBackColor(clGray);

		m_SpreadEncHEAD1.SetColWidth(2,10);
		m_SpreadEncHEAD1.SetCol(3);
		m_SpreadEncHEAD1.SetRow(nCurIndex);
		strTemp.Format(_T("%.3f mm"), abs(encoder1_0-encoder1_1) / -pFieldParameter->GetKX());
		m_SpreadEncHEAD1.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD1.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD1.SetBackColor(clGray);

		m_SpreadEncHEAD1.SetForeColor(CustomColor::colorBackGraund);
		m_SpreadEncHEAD1.SetTypeHAlign(0);
		m_SpreadEncHEAD1.SetTypeVAlign(2);

		m_SpreadEncHEAD1.SetReDraw(TRUE);
	}
	else
	{
		pDsp->ReadEncodeHEAD2(encoder0_0, encoder1_0,encoder0_1,encoder1_1);

		int nCurIndex = m_SpreadEncHEAD2.GetRow();
		CString strTemp;
		if(nCurIndex > 20) {
			m_SpreadEncHEAD2.Reset();
			InitEncDisplay(RTC_CARD_NUM_1);
			m_SpreadEncHEAD2.SetReDraw(TRUE);
			nCurIndex = m_SpreadEncHEAD2.GetRow();
		}

		nCurIndex++;

		m_SpreadEncHEAD2.SetColWidth(1,10);
		m_SpreadEncHEAD2.SetCol(1);
		m_SpreadEncHEAD2.SetRow(nCurIndex);
		CTime t = CTime::GetCurrentTime(); 
		strTemp.Format("%d시 %d분 %d초", t.GetHour(), t.GetMinute(), t.GetSecond()); 
		m_SpreadEncHEAD2.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD2.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD2.SetBackColor(clGray);

		m_SpreadEncHEAD2.SetColWidth(2,10);
		m_SpreadEncHEAD2.SetCol(2);
		m_SpreadEncHEAD2.SetRow(nCurIndex);
		strTemp.Format(_T("%.3f mm"), encoder1_1 / -pFieldParameter->GetKX());
		m_SpreadEncHEAD2.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD2.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD2.SetBackColor(clGray);

		m_SpreadEncHEAD2.SetColWidth(2,10);
		m_SpreadEncHEAD2.SetCol(3);
		m_SpreadEncHEAD2.SetRow(nCurIndex);
		strTemp.Format(_T("%.3f mm"), abs(encoder1_0-encoder1_1) / -pFieldParameter->GetKX());
		m_SpreadEncHEAD2.SetText(strTemp);
		if(nCurIndex%2)
			m_SpreadEncHEAD2.SetBackColor(clWhite);
		else
			m_SpreadEncHEAD2.SetBackColor(clGray);

		m_SpreadEncHEAD2.SetForeColor(CustomColor::colorBackGraund);
		m_SpreadEncHEAD2.SetTypeHAlign(0);
		m_SpreadEncHEAD2.SetTypeVAlign(2);

		m_SpreadEncHEAD2.SetReDraw(TRUE);
	}
}



void CMainFormView::OnViewPortChanged()
{
	//DrawScannerHead1(&m_ScannerHEAD1Vewer);
}


void CMainFormView::OnViewPortChanged2()
{
	//DrawScannerHead2(&m_ScannerHEAD2Vewer);
}


void CMainFormView::Display()
{
	
}


void CMainFormView::OnStnClickedMarkImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainFormView::OnStnClickedScannerViewer2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainFormView::OnStnClickedMarkImage2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainFormView::OnStnClickedScannerViewer1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainFormView::OnBnClickedButtonAdd4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void CMainFormView::OnBnClickedButtonInit4()
//{
//	CCttextctrl* pCcText	= NULL;
//	pCcText = (CCttextctrl*)GetDlgItem(	IDC_CTHEAD1_BUSY); 
//	pCcText->SetForeColor(RGB(255,255,255));
//}


BOOL CMainFormView::OnEraseBkgnd(CDC* pDC)
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


void CMainFormView::OnClose()
{
	m_listOfPositions.clear();
	m_listOfPositions.shrink_to_fit();


	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	StopMarkThread();

	CProjectBaseView::OnClose();
}
	
void CMainFormView::StopMarkThread()
{
	m_DrawThreadAlive1 = FALSE;
	m_DrawThreadAlive2 = FALSE;
	//DWORD dwState1 = WaitForSingleObject(m_pDrawThread1, 1000);
	//DWORD dwState2 = WaitForSingleObject(m_pDrawThread2, 1000);

	DWORD dwState1 = WaitForSingleObject(m_pDrawThread1, INFINITE);
	DWORD dwState2 = WaitForSingleObject(m_pDrawThread2, INFINITE);
	
	
	/*if(dwState1 == WAIT_TIMEOUT)
	{
		DWORD dwExitCode;
		GetExitCodeThread(m_pDrawThread1, &dwExitCode);

		if(dwExitCode == STILL_ACTIVE) 
			TerminateThread(m_pDrawThread1, 0);
		m_pDrawThread1 = NULL;
	}
	else
	{
		TerminateThread(m_pDrawThread1, 0);
	}


	if(dwState2 == WAIT_TIMEOUT)
	{
		DWORD dwExitCode;
		GetExitCodeThread(m_pDrawThread2, &dwExitCode);

		if(dwExitCode == STILL_ACTIVE) 
			TerminateThread(m_pDrawThread2, 0);
		m_pDrawThread2 = NULL;
	}
	else
	{
		TerminateThread(m_pDrawThread2, 0);
	}
	*/
	


}




void CMainFormView::OnStnClickedControlViewer1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




//void CMainFormView::OnBnClickedButtonIoTest()
//{	
//	m_dEncLaserOnPos = 0;
//	CString strTemp;
//	GetDlgItemText(IDC_CTHEAD1_ECN_CNT, strTemp);
//	m_dEncLaserOnPos = atof(strTemp);
//
//
//
//	if(IsDlgButtonChecked(IDC_CHECK_IO))
//		updateIoState(TRUE);
//	else
//		updateIoState(FALSE);
//
//	/*if(IsDlgButtonChecked(IDC_CHECK_IO))
//		updateFirstTabIoState(TRUE);
//	else
//		updateFirstTabIoState(FALSE);*/
//
//	//SetTimer(TM_AGING_TEST, 10, NULL);
//
//	/*RecordedData stData;
//	stData.position = 0;
//	stData.ioState = 1;
//	m_recordedPositions.push_back(stData);
//
//	stData.position = 10;
//	stData.ioState = 1;
//	m_recordedPositions.push_back(stData);
//
//	stData.position = 20;
//	stData.ioState = 1;
//	m_recordedPositions.push_back(stData);
//
//	stData.position = 30;
//	stData.ioState = 1;
//	m_recordedPositions.push_back(stData);*/
//
//	return;
//
//	
//}
//
//// I/O 상태 업데이트 - FIRST_TAB
//void CMainFormView::updateFirstTabIoState(bool newState)
//{
//	m_FirstTabioState = newState;
//
//	RecordedFirstTabData stData;
//	stData.position = m_encoderPosition;
//	stData.ioState = newState;
//
//	// I/O 값이 변할 때만 기록
//	if (m_FirstTabioState != m_previousFirstTabIoState) 
//	{
//		m_recordedFirstTabPositions.push_back(stData);
//	}
//
//	// 현재 상태를 이전 상태로 업데이트
//	m_previousFirstTabIoState = m_FirstTabioState;
//}


// I/O 상태 업데이트 (외부 입력값 받아옴)
void CMainFormView::updateIoState(bool newState)
{
	m_ioState = newState;

	RecordedData stData;
	stData.position = m_encoderPosition;
	stData.ioState = newState;

	// I/O 값이 변할 때만 기록
	if (m_ioState != m_previousIoState) 
	{
		m_recordedPositions.push_back(stData);
	}

	// 현재 상태를 이전 상태로 업데이트
	m_previousIoState = m_ioState;
}
//
//// I/O 상태 업데이트 - FIRST_TAB
//void CMainFormView::updateFirstTabIoStateHEAD2(bool newState)
//{
//	m_FirstTabioStateHEAD2 = newState;
//
//	RecordedFirstTabData stData;
//	stData.position = m_encoderPositionHEAD2;
//	stData.ioState = newState;
//
//	// I/O 값이 변할 때만 기록
//	if (m_FirstTabioStateHEAD2 != m_previousFirstTabIoStateHEAD2) 
//	{
//		m_recordedFirstTabPositionsHEAD2.push_back(stData);
//	}
//
//	// 현재 상태를 이전 상태로 업데이트
//	m_previousFirstTabIoStateHEAD2 = m_FirstTabioStateHEAD2;
//}
//
//
//// I/O 상태 업데이트 (외부 입력값 받아옴)
void CMainFormView::updateIoStateHEAD2(bool newState)
{
	m_ioStateHEAD2 = newState;

	RecordedData stData;
	stData.position = m_encoderPositionHEAD2;
	stData.ioState = newState;

	// I/O 값이 변할 때만 기록
	if (m_ioStateHEAD2 != m_previousIoStateHEAD2) 
	{
		m_recordedPositionsHEAD2.push_back(stData);
	}

	// 현재 상태를 이전 상태로 업데이트
	m_previousIoStateHEAD2 = m_ioStateHEAD2;
}


// 기록된 위치 및 I/O 상태 출력
void CMainFormView::printRecordedPositions()
{
	for (const auto& data : m_recordedPositions) {
		//std::cout << "  " << data << std::endl;
	}
}

//void CMainFormView::OnEnChangeSetedEncPos()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CProjectBaseView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void CMainFormView::RefreshIOViewer(void)
{
	if(m_NotchControlVewer1.m_hWnd != NULL)
			DrawControlViewer1(&m_NotchControlVewer1);


	if(m_NotchControlVewer3.m_hWnd != NULL)
			DrawControlViewer3(&m_NotchControlVewer3);


	if(m_NotchControlVewer5.m_hWnd != NULL)
			DrawControlViewer5(&m_NotchControlVewer5);

}

void CMainFormView::RefreshIOViewerHEAD2(void)
{

	if(m_NotchControlVewer2.m_hWnd != NULL)
			DrawControlViewer2(&m_NotchControlVewer2);


	if(m_NotchControlVewer4.m_hWnd != NULL)
			DrawControlViewer4(&m_NotchControlVewer4);


	if(m_NotchControlVewer6.m_hWnd != NULL)
			DrawControlViewer6(&m_NotchControlVewer6);
}


BEGIN_EVENTSINK_MAP(CMainFormView, CProjectBaseView)
//	ON_EVENT(CMainFormView, IDC_CTHEAD1_XOFFSET, DISPID_CLICK, CMainFormView::ClickCthead1Xoffset, VTS_NONE)
//	ON_EVENT(CMainFormView, IDC_CTHEAD1_YOFFSET, DISPID_CLICK, CMainFormView::ClickCthead1Yoffset, VTS_NONE)
//	ON_EVENT(CMainFormView, IDC_CTHEAD2_XOFFSET, DISPID_CLICK, CMainFormView::ClickCthead2Xoffset, VTS_NONE)
//	ON_EVENT(CMainFormView, IDC_CTHEAD2_YOFFSET, DISPID_CLICK, CMainFormView::ClickCthead2Yoffset, VTS_NONE)
END_EVENTSINK_MAP()


//void CMainFormView::ClickCthead1Xoffset()
//{
//	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
//
//	IniUtil _iniUtil;
//	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
//	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
//	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
//
//	SingleScannerParameter HEAD1Param;
//	HEAD1Param.clear();
//	_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
//
//	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
//	double dMmSize, dFieldSize;
//	dMmSize = FIELD_FARAMETER.MmSize;
//	dFieldSize = FIELD_FARAMETER.FieldSize;
//	CNumberKeyPad testdlg;
//
//	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetMasterX() / (double)dFieldSize * (double)dMmSize);
//
//	if(testdlg.DoModal()==IDOK)
//	{
//		CString strGetText = _T("");
//		double dOffsetValueX = testdlg.GetResultDouble();
//
//
//		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
//		strGetText.Format("%.2f",dOffsetValueX);
//
//		SetDlgItemText(IDC_CTHEAD1_XOFFSET,strGetText);
//
//		pFieldParameter->SetMasterX(dOffsetValueX * dFieldSize / dMmSize);
//
//		HEAD1Param.xOffset = dOffsetValueX;
//		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
//	}
//}


//void CMainFormView::ClickCthead1Yoffset()
//{
//	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
//	IniUtil _iniUtil;
//	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
//	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
//	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
//
//	SingleScannerParameter HEAD1Param;
//	HEAD1Param.clear();
//	_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
//
//	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
//	double dMmSize, dFieldSize;
//	dMmSize = FIELD_FARAMETER.MmSize;
//	dFieldSize = FIELD_FARAMETER.FieldSize;
//	CNumberKeyPad testdlg;
//
//	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetMasterY() / (double)dFieldSize * (double)dMmSize);
//
//
//	if(testdlg.DoModal()==IDOK)
//	{
//		CString strGetText = _T("");
//		double dOffsetValueY = testdlg.GetResultDouble();
//
//		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
//		strGetText.Format("%.2f",dOffsetValueY);
//
//		SetDlgItemText(IDC_CTHEAD1_YOFFSET,strGetText);
//
//		pFieldParameter->SetMasterY(dOffsetValueY * dFieldSize / dMmSize);
//
//		HEAD1Param.yOffset = dOffsetValueY;
//		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
//
//	}
//}


//void CMainFormView::ClickCthead2Xoffset()
//{
//	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
//	IniUtil _iniUtil;
//	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
//	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
//	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
//
//	SingleScannerParameter HEAD2Param;
//	HEAD2Param.clear();
//	_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);
//
//	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
//	double dMmSize, dFieldSize;
//	dMmSize = FIELD_FARAMETER.MmSize;
//	dFieldSize = FIELD_FARAMETER.FieldSize;
//	CNumberKeyPad testdlg;
//
//	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetSlaveX() / (double)dFieldSize * (double)dMmSize);
//
//	if(testdlg.DoModal()==IDOK)
//	{
//		CString strGetText = _T("");
//		double dOffsetValueX = testdlg.GetResultDouble();
//
//		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
//		strGetText.Format("%.2f",dOffsetValueX);
//
//		SetDlgItemText(IDC_CTHEAD2_XOFFSET,strGetText);
//
//		pFieldParameter->SetSlaveX(dOffsetValueX * dFieldSize / dMmSize);
//
//		HEAD2Param.xOffset = dOffsetValueX;
//		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD2Param);
//	}
//}


//void CMainFormView::ClickCthead2Yoffset()
//{
//	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
//	IniUtil _iniUtil;
//	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
//	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
//	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
//
//	SingleScannerParameter HEAD2Param;
//	HEAD2Param.clear();
//	_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);
//
//	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
//	double dMmSize, dFieldSize;
//	dMmSize = FIELD_FARAMETER.MmSize;
//	dFieldSize = FIELD_FARAMETER.FieldSize;
//	CNumberKeyPad testdlg;
//
//	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetSlaveY() / (double)dFieldSize * (double)dMmSize);
//
//	if(testdlg.DoModal()==IDOK)
//	{
//		CString strGetText = _T("");
//		double dOffsetValueY = testdlg.GetResultDouble();
//
//		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
//		strGetText.Format("%.2f",dOffsetValueY);
//
//		SetDlgItemText(IDC_CTHEAD2_YOFFSET,strGetText);
//
//		pFieldParameter->SetSlaveY(dOffsetValueY * dFieldSize / dMmSize);
//
//		HEAD2Param.yOffset = dOffsetValueY;
//		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD2Param);
//	}
//}
void CMainFormView::CalculateScaleFactor()
{
    // 💡 기준 해상도를 1920x1080으로 설정
    const int BASE_WIDTH = 1920;
    const int BASE_HEIGHT = 1080;

    // 💡 현재 컴퓨터의 실제 해상도를 가져옴
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 💡 가로/세로 비율 계산 (ex: 1280/1920, 1080/1080)
    m_fScaleX = static_cast<float>(screenWidth) / BASE_WIDTH;
    m_fScaleY = static_cast<float>(screenHeight) / BASE_HEIGHT;
}

void CMainFormView::ResizeControls()
{
    if (m_originalRects.empty())
        return;

    for (int i = 0; i < GetControlCount(); i++)
    {
        CWnd* pWnd = GetDlgItem(i);
        if (pWnd)
        {
            CRect newRect = m_originalRects[i];

            // 📏 X, Y 비율에 맞게 위치 및 크기 조정
            newRect.left = static_cast<int>(newRect.left * m_fScaleX);
            newRect.top = static_cast<int>(newRect.top * m_fScaleY);
            newRect.right = static_cast<int>(newRect.right * m_fScaleX);
            newRect.bottom = static_cast<int>(newRect.bottom * m_fScaleY);

            pWnd->MoveWindow(&newRect);
        }
    }

    // 🔹 다이얼로그 크기 조정
    CRect newDlgRect = m_originalDlgRect;
    newDlgRect.right = static_cast<int>(newDlgRect.right * m_fScaleX);
    newDlgRect.bottom = static_cast<int>(newDlgRect.bottom * m_fScaleY);
    SetWindowPos(NULL, 0, 0, newDlgRect.Width(), newDlgRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
}

int CMainFormView::GetControlCount()
{
    int count = 0;
    CWnd* pWnd = GetWindow(GW_CHILD); // 첫 번째 자식 컨트롤 가져오기

    while (pWnd)
    {
        count++;
        pWnd = pWnd->GetNextWindow(GW_HWNDNEXT); // 다음 컨트롤로 이동
    }

    return count;
}