// TabSetting.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TabSetting.h"
#include "FieldParameter.h"
#include "TransUnit.h"

#include "PointerContainer.h"
#include "MathUtil.h"
#include "InitialTable.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabSetting dialog


CTabSetting::CTabSetting(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CTabSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabSetting)
	m_dFieldAngle = 0.0;
	m_dMasterX = 0;
	m_dMasterY = 0;
	m_dSlaveX = 0;
	m_dSlaveY = 0;
	m_iSimulationSpeed = 0;
	//}}AFX_DATA_INIT
}


void CTabSetting::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSetting)
	DDX_Text(pDX, IDC_FIELD_ANGLE, m_dFieldAngle);
	DDX_Text(pDX, IDC_MASTER_X, m_dMasterX);
	DDX_Text(pDX, IDC_MASTER_Y, m_dMasterY);
	DDX_Text(pDX, IDC_SLAVE_X, m_dSlaveX);
	DDX_Text(pDX, IDC_SLAVE_Y, m_dSlaveY);
	DDX_Text(pDX, IDC_SIMULATION_SPEED, m_iSimulationSpeed);

	DDX_Control(pDX, IDC_SETTING_6, m_btnStart);
	DDX_Control(pDX, IDC_SETTING_7, m_btnStop);

	

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabSetting, CUserDialogEx)
	//{{AFX_MSG_MAP(CTabSetting)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SETTING_6, OnSetting6)
	ON_BN_CLICKED(IDC_SETTING_7, OnSetting7)
	ON_WM_CTLCOLOR()
	ON_WM_NCCREATE()
	ON_WM_CLOSE()
	ON_WM_CAPTURECHANGED()
	ON_EN_KILLFOCUS(IDC_SLAVE_X, OnKillfocusSlaveX)
	ON_EN_KILLFOCUS(IDC_SLAVE_Y, OnKillfocusSlaveY)
	ON_EN_KILLFOCUS(IDC_MASTER_X, OnKillfocusMasterX)
	ON_EN_KILLFOCUS(IDC_MASTER_Y, OnKillfocusMasterY)
	ON_BN_CLICKED(IDC_BTN_MEASURE, OnBtnMeasure)
	ON_BN_CLICKED(IDC_BTN_MEASURE_STOP, OnBtnMeasureStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSetting message handlers

BOOL CTabSetting::OnInitDialog() 
{
	CUserDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	LoadString.LoadString(this, IDS_SETTING_1, IDC_SETTING_1, IDC_SETTING_7, FALSE, FALSE);
	
/*	m_btnStart.SetFont("Courier New",16,600);
	m_btnStart.SetShade(SHS_HARDBUMP);
	m_btnStart.SetTextColor(RGB(0,0,100));
	
	m_btnStop.SetFont("Courier New",16,600);
	m_btnStop.SetShade(SHS_HARDBUMP);
	m_btnStop.SetTextColor(RGB(0,0,100));
	*/

	LoadValue();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString strCompany = _T("");
	strCompany = pInitialTable->GetCompanyCode();
	
	if(strCompany == _T("AMKOR") || strCompany == _T("amkor"))
	{
	GetDlgItem(IDC_FIELD_ANGLE)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	m_pDxfLoadThread = NULL;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabSetting::OnDestroy() 
{
	CUserDialogEx::OnDestroy();
	
	// TODO: Add your message handler code here

	
	//CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	//CDlgMark *m_pDlgMark = m_pDlgMark->GetInstance();
}

void CTabSetting::LoadValue()
{/*
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize;
	double dFieldSize;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	m_dFieldAngle = pFieldParameter->GetFieldAngle();
	int iUnit = pFieldParameter->GetUnit();
	pTransUnit->SetValue(pFieldParameter->GetMasterX(), FIELD);
	m_dMasterX = pTransUnit->GetValue(iUnit);
	pTransUnit->SetValue(pFieldParameter->GetMasterY(), FIELD);
	m_dMasterY = pTransUnit->GetValue(iUnit);
	pTransUnit->SetValue(pFieldParameter->GetSlaveX(), FIELD);
	m_dSlaveX = pTransUnit->GetValue(iUnit);
	pTransUnit->SetValue(pFieldParameter->GetSlaveY(), FIELD);
	m_dSlaveY = pTransUnit->GetValue(iUnit);
	m_iSimulationSpeed = pFieldParameter->GetSimulationSpeed();	
	*/

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize;
	double dFieldSize;
	CMathUtil mathUtil;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	m_dFieldAngle = pFieldParameter->GetFieldAngle();
	/*int iUnit = pFieldParameter->GetUnit();
	pTransUnit->SetValue(pFieldParameter->GetMasterX(), FIELD);
 	//m_dMasterX = pTransUnit->GetValue(iUnit);
	m_dMasterX = mathUtil.Round(pTransUnit->GetValue(iUnit), 2);
	//m_dMasterX = floor(10.*(pTransUnit->GetValue(iUnit)))/10.;
	
	pTransUnit->SetValue(pFieldParameter->GetMasterY(), FIELD);
	//m_dMasterY = floor(10.*(pTransUnit->GetValue(iUnit)))/10.;
	m_dMasterY = mathUtil.Round(pTransUnit->GetValue(iUnit), 2);
	//m_dMasterY = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(pFieldParameter->GetSlaveX(), FIELD);
	//m_dSlaveX = floor(10.*(pTransUnit->GetValue(iUnit)))/10.;
	m_dSlaveX = mathUtil.Round(pTransUnit->GetValue(iUnit), 2);
	//m_dSlaveX = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(pFieldParameter->GetSlaveY(), FIELD);
	//m_dSlaveY = floor(10.*(pTransUnit->GetValue(iUnit)))/10.;
	m_dSlaveY = mathUtil.Round(pTransUnit->GetValue(iUnit), 2);
	//m_dSlaveY = pTransUnit->GetValue(iUnit);
	*/
	m_iSimulationSpeed = (float)pFieldParameter->GetSimulationSpeed();
	
	UpdateData(false);
	
	//strOffsetX.Format("%.3f", mathUtil.Round(pTransUnit->GetValue(iUnit), 4));
	
}

void CTabSetting::OnSetting6() 
{
	// TODO: Add your control notification handler code here
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();



}

void CTabSetting::OnSetting7() 
{
	// TODO: Add your control notification handler code here
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
    int m_iUnit = pFieldParameter->GetUnit();
	
	CString m_strTmp;
	GetDlgItemText(IDC_SLAVE_X, m_strTmp);
	m_dSlaveX = atof(m_strTmp);
	GetDlgItemText(IDC_SLAVE_Y, m_strTmp);
	m_dSlaveY = atof(m_strTmp);
	GetDlgItemText(IDC_MASTER_X, m_strTmp);
	m_dMasterX = atof(m_strTmp);
	GetDlgItemText(IDC_MASTER_Y, m_strTmp);
	m_dMasterY = atof(m_strTmp);
	UpdateData(false);

	pTransUnit->SetValue(m_dMasterX, m_iUnit);
	pFieldParameter->SetMasterX(pTransUnit->GetField());

	pTransUnit->SetValue(m_dMasterY, m_iUnit);
	pFieldParameter->SetMasterY(pTransUnit->GetField());
	
	pTransUnit->SetValue(m_dSlaveX, m_iUnit);
	pFieldParameter->SetSlaveX(pTransUnit->GetField());
	
	pTransUnit->SetValue(m_dSlaveY, m_iUnit);
	pFieldParameter->SetSlaveY(pTransUnit->GetField());
	


	/*
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();

	m_pDlgMark->m_ctMarkPreview.SetIsSimulation(FALSE);	
	m_pDlgMark->m_ctMarkPreview.Stop();  
	m_pDlgMark->m_ctMarkPreview.Invalidate();	
	*/
}

HBRUSH CTabSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CUserDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	CBrush m_brush;
	

	/*if(pWnd->GetDlgCtrlID()==IDC_EDIT1)
	{
		GetBrush();
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SelectObject(&m_bredtBrush);
		hbr=(HBRUSH)m_bredtBrush;
	}
	*/
/*	
	if (nCtlColor == CTLCOLOR_STATIC)  
	{
	    pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,100));
		
        HBRUSH B = CreateSolidBrush(RGB(213,196,247)); // ¹è°æ»ö Èò»ö 
        return (HBRUSH) B;
	}
	else if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX)  
    {
        pDC->SetBkMode(TRANSPARENT);
        HBRUSH B = CreateSolidBrush(RGB(213,196,247)); // ¹è°æ»ö Èò»ö 
        return (HBRUSH) B;
    } 
	*/
	return hbr;
}

BOOL CTabSetting::OnNcCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (!CUserDialogEx::OnNcCreate(lpCreateStruct))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}





void CTabSetting::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnClose();
}

void CTabSetting::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialogEx::OnCaptureChanged(pWnd);
}

void CTabSetting::ApplyVaule()
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
    int m_iUnit = pFieldParameter->GetUnit();
	
	CString m_strTmp;
	GetDlgItemText(IDC_SLAVE_X, m_strTmp);
	m_dSlaveX = atof(m_strTmp);
	GetDlgItemText(IDC_SLAVE_Y, m_strTmp);
	m_dSlaveY = atof(m_strTmp);
	GetDlgItemText(IDC_MASTER_X, m_strTmp);
	m_dMasterX = atof(m_strTmp);
	GetDlgItemText(IDC_MASTER_Y, m_strTmp);
	m_dMasterY = atof(m_strTmp);
	UpdateData(false);



	pTransUnit->SetValue(m_dMasterX, m_iUnit);
	pFieldParameter->SetMasterX(pTransUnit->GetField());

	pTransUnit->SetValue(m_dMasterY, m_iUnit);
	pFieldParameter->SetMasterY(pTransUnit->GetField());
	
	pTransUnit->SetValue(m_dSlaveX, m_iUnit);
	pFieldParameter->SetSlaveX(pTransUnit->GetField());
	
	pTransUnit->SetValue(m_dSlaveY, m_iUnit);
	pFieldParameter->SetSlaveY(pTransUnit->GetField());
	

	
	/*
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();

	m_pDlgMark->m_ctMarkPreview.SetIsSimulation(FALSE);	
	m_pDlgMark->m_ctMarkPreview.Stop();  
	m_pDlgMark->m_ctMarkPreview.Invalidate();	
	*/
}

void CTabSetting::OnKillfocusSlaveX() 
{
	//ApplyVaule();
	
}

void CTabSetting::OnKillfocusSlaveY() 
{
//ApplyVaule();	
}

void CTabSetting::OnKillfocusMasterX() 
{
//ApplyVaule();	
}

void CTabSetting::OnKillfocusMasterY() 
{
//ApplyVaule();	
}

BOOL CTabSetting::PreTranslateMessage(MSG *pMsg)	
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)	
	{
		 return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg) ;
}

void CTabSetting::OnBtnMeasure() 
{
	CDsp *pDsp = CDsp::GetInstance();
	//CMarking *pMarking = pMarking->GetInstance();
	pDsp->SetParameterData();
	int x = GetDlgItemInt(IDC_EDIT_POWER_X), y = GetDlgItemInt(IDC_EDIT_POWER_Y);
	pDsp->SetGotoXY(x, y);
	//pDsp->PMUShutterOn();
}

void CTabSetting::OnBtnMeasureStop() 
{
	// TODO: Add your control notification handler code here
	CDsp *pDsp = CDsp::GetInstance();
	//pDsp->PMUShutterOff();

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrm != NULL)
		pMainFrm->InitRTC();
}
BEGIN_EVENTSINK_MAP(CTabSetting, CDialogEx)
	ON_EVENT(CTabSetting, IDC_CTPUSHCTRL1, DISPID_CLICK, CTabSetting::ClickCtpushctrl1, VTS_NONE)
END_EVENTSINK_MAP()


void CTabSetting::ClickCtpushctrl1()
{
	AfxMessageBox("TEST SETTIN");
}
