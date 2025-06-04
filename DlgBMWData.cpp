// DlgBMWData.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgBMWData.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "MainFrm.h"


// CDlgBMWData 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgBMWData, CDialogEx)

CDlgBMWData::CDlgBMWData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBMWData::IDD, pParent)
{

}

CDlgBMWData::~CDlgBMWData()
{
}

void CDlgBMWData::DoDataExchange(CDataExchange* pDX)
{



	//DDX_Text(pDX,IDC_CTTEXT_GRAPHITEHEIGHT,m_bmwData.dGraphiteHeight);   //DDX_TEXT를 쓰니까 소수점이 안들어가는것같다.
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBMWData, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDlgBMWData::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CDlgBMWData::OnBnClickedOk2)
END_MESSAGE_MAP()


// CDlgBMWData 메시지 처리기입니다.



BEGIN_EVENTSINK_MAP(CDlgBMWData, CDialogEx)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_GRAPHITEHEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextGraphiteheight, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_ENDSEGMENT_HEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextEndsegmentHeight, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_ENDSEGMENT_LENGTH, DISPID_CLICK, CDlgBMWData::ClickCttextEndsegmentLength, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_FLAG_COUNT, DISPID_CLICK, CDlgBMWData::ClickCttextFlagCount, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_INSERTSEGMENT_LENGTH, DISPID_CLICK, CDlgBMWData::ClickCttextInsertsegmentLength, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_INSERTSEGMENT_DEEPHEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextInsertsegmentDeepheight, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_INSERTSEGMENT_HEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextInsertsegmentHeight, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_FLAG_HEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextFlagHeight, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_FLAG_WAITLENGTH, DISPID_CLICK, CDlgBMWData::ClickCttextFlagWaitlength, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_FLAG_DEEPLENGTH, DISPID_CLICK, CDlgBMWData::ClickCttextFlagDeeplength, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_FLAG_INOUTLEGNTH, DISPID_CLICK, CDlgBMWData::ClickCttextFlagInoutlegnth, VTS_NONE)
	ON_EVENT(CDlgBMWData, IDC_CTTEXT_TOTAL_HEIGHT, DISPID_CLICK, CDlgBMWData::ClickCttextTotalHeight, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgBMWData::ClickCttextGraphiteheight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dGraphiteHeight);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Graphite Height: %0.2lf -> %0.2lf", m_bmwData.dGraphiteHeight,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dGraphiteHeight = newData;
		SetDlgItemText(IDC_CTTEXT_GRAPHITEHEIGHT,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


BOOL CDlgBMWData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	m_bmwData = pFieldParameter->GetBMWData();
	//UpdateData(false);
	SetTextControls();
	SetStaticTextControl();

	SetWindowText(_T("Pattern Data"));
	return true;
}


void CDlgBMWData::SetTextControls()
{
	CString dataStr;

	dataStr.Format("%0.2lf",m_bmwData.dGraphiteHeight);
	SetDlgItemText(IDC_CTTEXT_GRAPHITEHEIGHT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dEndSegmentHeight);
	SetDlgItemText(IDC_CTTEXT_ENDSEGMENT_HEIGHT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dEndSegmentLength);
	SetDlgItemText(IDC_CTTEXT_ENDSEGMENT_LENGTH,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dTabCount);
	SetDlgItemText(IDC_CTTEXT_FLAG_COUNT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dInsertSegmentLength);
	SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_LENGTH,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dInsertSegmentDeepHeight);
	SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_DEEPHEIGHT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dInsertSegmentHeight);
	SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_HEIGHT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dFlagHeight);
	SetDlgItemText(IDC_CTTEXT_FLAG_HEIGHT,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dFlagWaitLength);
	SetDlgItemText(IDC_CTTEXT_FLAG_WAITLENGTH,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dFlagDeepLength);
	SetDlgItemText(IDC_CTTEXT_FLAG_DEEPLENGTH,dataStr);

	
	dataStr.Format("%0.2lf",m_bmwData.dFlagInoutLength);
	SetDlgItemText(IDC_CTTEXT_FLAG_INOUTLEGNTH,dataStr);
}

void CDlgBMWData::SetStaticTextControl()
{
	CString dataStr;

	dataStr.Format("%0.2lf",m_bmwData.dFlagWaitLength + m_bmwData.dFlagInoutLength * 2); // FlagOneLength
	SetDlgItemText(IDC_CTTEXT_FLAG_ONELENGTH,dataStr);

	dataStr.Format("%0.2lf",m_bmwData.dFlagWaitLength + m_bmwData.dFlagInoutLength * 2 + m_bmwData.dFlagDeepLength); // FlagOneLength
	SetDlgItemText(IDC_CTTEXT_FLAG_TOTALLENGTH,dataStr);


	dataStr.Format("%0.2lf",m_bmwData.dInsertSegmentHeight + m_bmwData.dFlagHeight); // FlagOneLength
	SetDlgItemText(IDC_CTTEXT_TOTAL_HEIGHT,dataStr);
	


}


void CDlgBMWData::ClickCttextEndsegmentHeight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dEndSegmentHeight);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("EndSegment Height: %0.2lf -> %0.2lf", m_bmwData.dEndSegmentHeight,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dEndSegmentHeight = newData;
		SetDlgItemText(IDC_CTTEXT_ENDSEGMENT_HEIGHT,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextEndsegmentLength()
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dEndSegmentLength);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("EndSegment Length: %0.2lf -> %0.2lf", m_bmwData.dEndSegmentLength,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dEndSegmentLength = newData;
		SetDlgItemText(IDC_CTTEXT_ENDSEGMENT_LENGTH,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextFlagCount()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dTabCount);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Flag Count: %d -> %d", (int)m_bmwData.dTabCount,(int)newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%d",(int)newData);
		m_bmwData.dTabCount = newData;
		SetDlgItemText(IDC_CTTEXT_FLAG_COUNT,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextInsertsegmentLength()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dInsertSegmentLength);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Insert Segment Length: %0.2lf -> %0.2lf", m_bmwData.dInsertSegmentLength,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dInsertSegmentLength = newData;
		SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_LENGTH,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextInsertsegmentDeepheight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dInsertSegmentDeepHeight);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Insert Segment Deep Height: %0.2lf -> %0.2lf", m_bmwData.dInsertSegmentDeepHeight,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dInsertSegmentDeepHeight = newData;
		SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_DEEPHEIGHT,writeStr);
		//UpdateData(false);
	}

	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextInsertsegmentHeight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dInsertSegmentHeight);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Insert Segment Height: %0.2lf -> %0.2lf", m_bmwData.dInsertSegmentHeight,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dInsertSegmentHeight = newData;
		SetDlgItemText(IDC_CTTEXT_INSERTSEGMENT_HEIGHT,writeStr);

		//UpdateData(false);
	}

	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextFlagHeight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dFlagHeight);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Flag Height: %0.2lf -> %0.2lf", m_bmwData.dFlagHeight,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dFlagHeight = newData;
		SetDlgItemText(IDC_CTTEXT_FLAG_HEIGHT,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextFlagWaitlength()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dFlagWaitLength);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Flag Wait Length: %0.2lf -> %0.2lf", m_bmwData.dFlagWaitLength,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dFlagWaitLength = newData;
		SetDlgItemText(IDC_CTTEXT_FLAG_WAITLENGTH,writeStr);
		//UpdateData(false);
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextFlagDeeplength()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dFlagDeepLength);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Flag Deep Length: %0.2lf -> %0.2lf", m_bmwData.dFlagDeepLength,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dFlagDeepLength = newData;
		SetDlgItemText(IDC_CTTEXT_FLAG_DEEPLENGTH,writeStr);
		//UpdateData(false)
	}
	SetStaticTextControl();
}


void CDlgBMWData::ClickCttextFlagInoutlegnth()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,m_bmwData.dFlagInoutLength);

	if(numberpadDlg.DoModal()==IDOK)
	{		
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		CString writeStr;
		writeStr.Format("Flag Inout Length: %0.2lf -> %0.2lf", m_bmwData.dFlagInoutLength,newData);
		pMainFrm->AddLogData(writeStr);
		writeStr.Format("%0.2lf",newData);
		m_bmwData.dFlagInoutLength = newData;
		SetDlgItemText(IDC_CTTEXT_FLAG_INOUTLEGNTH,writeStr);
		//UpdateData(false)
	}
	SetStaticTextControl();
}


void CDlgBMWData::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
	CString writeStr;
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	pMainFrm->AddLogData("--------------------------------------------------B_DATA--------------------------------------------------");

	writeStr.Format("Graphite Height: %0.2lf ", m_bmwData.dGraphiteHeight);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("EndSegment Height: %0.2lf", m_bmwData.dEndSegmentHeight);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("EndSegment Length: %0.2lf", m_bmwData.dEndSegmentLength);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Flag Count: %d", (int)m_bmwData.dTabCount);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Insert Segment Length: %0.2lf", m_bmwData.dInsertSegmentLength);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Insert Segment Deep Height: %0.2lf", m_bmwData.dInsertSegmentDeepHeight);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Insert Segment Height: %0.2lf", m_bmwData.dInsertSegmentHeight);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Flag Height: %0.2lf", m_bmwData.dFlagHeight);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Flag Wait Length: %0.2lf", m_bmwData.dFlagWaitLength);
	pMainFrm->AddLogData(writeStr);

	writeStr.Format("Flag Deep Length: %0.2lf", m_bmwData.dFlagDeepLength);
	pMainFrm->AddLogData(writeStr);


	writeStr.Format("Flag Inout Length: %0.2lf", m_bmwData.dFlagInoutLength);
	pMainFrm->AddLogData(writeStr);

	pMainFrm->AddLogData("--------------------------------------------------B_DATA--------------------------------------------------");

	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetBMWData(m_bmwData);

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->UpdateSplitterWindow();

	CDialogEx::OnOK();
}


void CDlgBMWData::ClickCttextTotalHeight()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//CNumberKeyPad numberpadDlg;
	//CString strConvert;

	//numberpadDlg.SetRange(0.0,100.0,m_bmwData.dTotalHeight);

	//if(numberpadDlg.DoModal()==IDOK)
	//{		
	//	double newData = numberpadDlg.GetResultDouble();

	//	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	//	CString writeStr;
	//	writeStr.Format("Insert Total Height: %0.2lf -> %0.2lf", m_bmwData.dTotalHeight,newData);
	//	pMainFrm->AddLogData(writeStr);
	//	writeStr.Format("%0.2lf",newData);
	//	m_bmwData.dInsertSegmentHeight = newData;
	//	SetDlgItemText(IDC_CTTEXT_TOTAL_HEIGHT,writeStr);

	//	//UpdateData(false);
	//}

	//SetStaticTextControl();
}


void CDlgBMWData::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
