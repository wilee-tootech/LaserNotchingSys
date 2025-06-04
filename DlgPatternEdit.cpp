// DlgPatternEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgPatternEdit.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "MainFrm.h"
#include "InitialTable.h"
#include "Include\EXTERN\cttextctrl.h"\




// CDlgPatternEdit 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgPatternEdit, CUserDialogEx)

CDlgPatternEdit::CDlgPatternEdit(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgPatternEdit::IDD, pParent)
{
	m_stPatternDataOfHEAD2.clear();
	m_stPatternDataOfHEAD1.clear();
}

CDlgPatternEdit::~CDlgPatternEdit()
{
}

void CDlgPatternEdit::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);

	DDX_Text(pDX,IDC_CTTEXT_NONTAB_LENGTH_HEAD2,m_stPatternDataOfHEAD2.dBuriedRegion);
	DDX_Text(pDX,IDC_CTTEXT_TAB_COUNT_HEAD2,m_stPatternDataOfHEAD2.dTabCount);
	DDX_Text(pDX,IDC_CTTEXT_T1_COUNT_HEAD2,m_stPatternDataOfHEAD2.dT1Count);
	DDX_Text(pDX,IDC_CTTEXT_TN_COUNT_HEAD2,m_stPatternDataOfHEAD2.dTnCount);
	DDX_Text(pDX,IDC_CTTEXT_TA_LENGTH_HEAD2,m_stPatternDataOfHEAD2.dTaLength);
	DDX_Text(pDX,IDC_CTTEXT_TAB_WIDTH_HEAD2,m_stPatternDataOfHEAD2.dTabWidth);
	DDX_Text(pDX,IDC_CTTEXT_TAB_PITCH_HEAD2,m_stPatternDataOfHEAD2.dTabPitch);
	DDX_Text(pDX,IDC_CTTEXT_TAB_L_ANGLE_HEAD2,m_stPatternDataOfHEAD2.dLeftTabAngle);
	DDX_Text(pDX,IDC_CTTEXT_TAB_R_ANGLE_HEAD2,m_stPatternDataOfHEAD2.dRightTabAngle);
	//DDX_Text(pDX,IDC_CTTEXT_TAB_LENGTH_HEAD2,m_stPatternDataOfHEAD1.d
	DDX_Text(pDX,IDC_CTTEXT_TAB_HEIGHT_HEAD2,m_stPatternDataOfHEAD2.dTabHeight);


	DDX_Text(pDX,IDC_CTTEXT_NONTAB_LENGTH_HEAD1,m_stPatternDataOfHEAD1.dBuriedRegion);
	DDX_Text(pDX,IDC_CTTEXT_TAB_COUNT_HEAD1,m_stPatternDataOfHEAD1.dTabCount);
	DDX_Text(pDX,IDC_CTTEXT_T1_COUNT_HEAD1,m_stPatternDataOfHEAD1.dT1Count);
	DDX_Text(pDX,IDC_CTTEXT_TN_COUNT_HEAD1,m_stPatternDataOfHEAD1.dTnCount);
	DDX_Text(pDX,IDC_CTTEXT_TA_LENGTH_HEAD1,m_stPatternDataOfHEAD1.dTaLength);
	DDX_Text(pDX,IDC_CTTEXT_TAB_WIDTH_HEAD1,m_stPatternDataOfHEAD1.dTabWidth);
	DDX_Text(pDX,IDC_CTTEXT_TAB_PITCH_HEAD1,m_stPatternDataOfHEAD1.dTabPitch);
	DDX_Text(pDX,IDC_CTTEXT_TAB_L_ANGLE_HEAD1,m_stPatternDataOfHEAD1.dLeftTabAngle);
	DDX_Text(pDX,IDC_CTTEXT_TAB_R_ANGLE_HEAD1,m_stPatternDataOfHEAD1.dRightTabAngle);
	//DDX_Text(pDX,IDC_CTTEXT_TAB_LENGTH_HEAD2,m_stPatternDataOfHEAD1.d
	DDX_Text(pDX,IDC_CTTEXT_TAB_HEIGHT_HEAD1,m_stPatternDataOfHEAD1.dTabHeight);


}


BEGIN_MESSAGE_MAP(CDlgPatternEdit, CUserDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPatternEdit::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgPatternEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgPatternEdit 메시지 처리기입니다.


void CDlgPatternEdit::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgPatternEdit::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	UpdateData(TRUE);// 컨트롤값->변수

	
	pFieldParameter->SetHEAD2PatternData(m_stPatternDataOfHEAD2);
	pFieldParameter->SetHEAD1PatternData(m_stPatternDataOfHEAD1);
	pFieldParameter->SetUnitShapePreview(true);

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->UpdateSplitterWindow();

	//CDialogEx::OnOK();
}


BOOL CDlgPatternEdit::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	m_stPatternDataOfHEAD2 = pFieldParameter->GetHEAD2PatternDataOfKoem();
	m_stPatternDataOfHEAD1 = pFieldParameter->GetHEAD1PatternDataOfKoem();

	
	if(pInitialTable->GetHead1Name() == "Anode")
	{
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW1_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW2_1)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW1_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_PATTERN_VIEW2_1)->ShowWindow(SW_HIDE);		
	}



	UpdateData(FALSE);//변수->컨트롤

	UpdateTabData();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BEGIN_EVENTSINK_MAP(CDlgPatternEdit, CUserDialogEx)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_COUNT_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabCountHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_NONTAB_LENGTH_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextNontabLengthHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_T1_COUNT_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextT1CountHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TN_COUNT_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTnCountHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TA_LENGTH_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTaLengthHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_WIDTH_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabWidthHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_PITCH_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabPitchHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_L_ANGLE_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabAngleHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_HEIGHT_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabHeightHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_NONTAB_LENGTH_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextNontabLengthHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_COUNT_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabCountHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_T1_COUNT_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextT1CountHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TN_COUNT_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTnCountHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TA_LENGTH_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTaLengthHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_WIDTH_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabWidthHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_PITCH_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabPitchHEAD1, VTS_NONE)
//	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_L_ANGLE_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabAngleHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_HEIGHT_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabHeightHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_R_ANGLE_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabRAngleHEAD2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_R_ANGLE_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabRAngleHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_L_ANGLE_HEAD1, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabLAngleHEAD1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit, IDC_CTTEXT_TAB_LENGTH_HEAD2, DISPID_CLICK, CDlgPatternEdit::ClickCttextTabLengthHEAD2, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgPatternEdit::ClickCttextTabCountHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,1500.0,m_stPatternDataOfHEAD2.dTabCount);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TabCount %lf -> %lf"),m_stPatternDataOfHEAD2.dTabCount ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTabCount = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_COUNT_HEAD2,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextNontabLengthHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dBuriedRegion);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 BuriedRegion %lf -> %lf"),m_stPatternDataOfHEAD2.dBuriedRegion ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dBuriedRegion = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_NONTAB_LENGTH_HEAD2,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextT1CountHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dT1Count);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 T1Count %lf -> %lf"),m_stPatternDataOfHEAD2.dT1Count ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dT1Count = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_T1_COUNT_HEAD2,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTnCountHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dTnCount);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TnCount %lf -> %lf"),m_stPatternDataOfHEAD2.dTnCount ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTnCount = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TN_COUNT_HEAD2,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTaLengthHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dTaLength);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TaLength %lf -> %lf"),m_stPatternDataOfHEAD2.dTaLength ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTaLength = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TA_LENGTH_HEAD2,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextTabWidthHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dTabWidth);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TabWidth %lf -> %lf"),m_stPatternDataOfHEAD2.dTabWidth ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTabWidth = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_WIDTH_HEAD2,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTabPitchHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dTabPitch);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TabPitch %lf -> %lf"),m_stPatternDataOfHEAD2.dTabPitch ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTabPitch = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_PITCH_HEAD2,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTabAngleHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-45.0,45.0,m_stPatternDataOfHEAD2.dLeftTabAngle);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 LeftTabAngle %lf -> %lf"),m_stPatternDataOfHEAD2.dLeftTabAngle ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dLeftTabAngle = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_L_ANGLE_HEAD2,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextTabHeightHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD2.dTabHeight);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 TabHeight %lf -> %lf"),m_stPatternDataOfHEAD2.dTabHeight ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dTabHeight = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_HEIGHT_HEAD2,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextNontabLengthHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dBuriedRegion);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 BuriedRegion %lf -> %lf"),m_stPatternDataOfHEAD1.dBuriedRegion ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dBuriedRegion = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_NONTAB_LENGTH_HEAD1,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextTabCountHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,1500.0,m_stPatternDataOfHEAD1.dTabCount);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TabCount %lf -> %lf"),m_stPatternDataOfHEAD1.dTabCount ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTabCount = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_COUNT_HEAD1,strGetValue);
	}
}



void CDlgPatternEdit::ClickCttextTabRAngleHEAD2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-45.0,45.0,m_stPatternDataOfHEAD2.dRightTabAngle);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 RightTabAngle %lf -> %lf"),m_stPatternDataOfHEAD2.dRightTabAngle ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD2.dRightTabAngle = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_R_ANGLE_HEAD2,strGetValue);
	}
}



void CDlgPatternEdit::ClickCttextTabRAngleHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-45.0,45.0,m_stPatternDataOfHEAD1.dRightTabAngle);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 RightTabAngle %lf -> %lf"),m_stPatternDataOfHEAD1.dRightTabAngle ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dRightTabAngle = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_R_ANGLE_HEAD1,strGetValue);
	}
}

void CDlgPatternEdit::ClickCttextT1CountHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dT1Count);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 T1Count %lf -> %lf"),m_stPatternDataOfHEAD1.dT1Count ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dT1Count = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_T1_COUNT_HEAD1,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTnCountHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dTnCount);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TnCount %lf -> %lf"),m_stPatternDataOfHEAD1.dTnCount ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTnCount = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%d",(int)numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TN_COUNT_HEAD1,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTaLengthHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dTaLength);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TaLength %lf -> %lf"),m_stPatternDataOfHEAD1.dTaLength ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTaLength = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TA_LENGTH_HEAD1,strGetValue);
	}
}


void CDlgPatternEdit::ClickCttextTabWidthHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dTabWidth);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TabWidth %lf -> %lf"),m_stPatternDataOfHEAD1.dTabWidth ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTabWidth = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_WIDTH_HEAD1,strGetValue);

		UpdateTabData();
	}
}


void CDlgPatternEdit::ClickCttextTabPitchHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dTabPitch);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TabPitch %lf -> %lf"),m_stPatternDataOfHEAD1.dTabPitch ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTabPitch = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_PITCH_HEAD1,strGetValue);

		UpdateTabData();
	}
}



void CDlgPatternEdit::ClickCttextTabHeightHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,2000.0,m_stPatternDataOfHEAD1.dTabHeight);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 TabHeight %lf -> %lf"),m_stPatternDataOfHEAD1.dTabHeight ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dTabHeight = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_HEIGHT_HEAD1,strGetValue);
	}
}




void CDlgPatternEdit::ClickCttextTabLAngleHEAD1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-45.0,45.0,m_stPatternDataOfHEAD1.dLeftTabAngle);

	if(numberdlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 LeftTabAngle %lf -> %lf"),m_stPatternDataOfHEAD1.dLeftTabAngle ,numberdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		m_stPatternDataOfHEAD1.dLeftTabAngle = numberdlg.GetResultDouble();
		CString strGetValue;
		strGetValue.Format("%.2f",numberdlg.GetResultDouble());
		SetDlgItemText(IDC_CTTEXT_TAB_L_ANGLE_HEAD1,strGetValue);
	}
}


void CDlgPatternEdit::UpdateTabData(void)
{
	CString dataStr;
	dataStr.Format("%d",(int)m_stPatternDataOfHEAD2.dT1Count * (int)m_stPatternDataOfHEAD2.dTnCount);
	SetDlgItemText(IDC_CTTEXT_TAB_COUNT_HEAD2,dataStr);
	//m_stPatternDataOfHEAD1.dTnCount * m_stPatternDataOfHEAD1.dTnCount

	dataStr.Format("%d",(int)m_stPatternDataOfHEAD1.dT1Count * (int)m_stPatternDataOfHEAD1.dTnCount);
	SetDlgItemText(IDC_CTTEXT_TAB_COUNT_HEAD1,dataStr);

	dataStr.Format("%.2f",m_stPatternDataOfHEAD2.dTabWidth + m_stPatternDataOfHEAD2.dTabPitch);
	SetDlgItemText(IDC_CTTEXT_TAB_LENGTH_HEAD2,dataStr);
	//m_stPatternDataOfHEAD1.dTnCount * m_stPatternDataOfHEAD1.dTnCount

	dataStr.Format("%.2f",m_stPatternDataOfHEAD1.dTabWidth + m_stPatternDataOfHEAD1.dTabPitch);
	SetDlgItemText(IDC_CTTEXT_TAB_LENGTH_HEAD1,dataStr);

	UpdateData(TRUE);// 컨트롤값->변수
}


void CDlgPatternEdit::ClickCttextTabLengthHEAD2()
{
	
}
