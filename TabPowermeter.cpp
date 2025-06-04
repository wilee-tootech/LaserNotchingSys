 // TabPowermeter.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "TabPowermeter.h"
#include "PointerManager.h"
#include "RS232.h"
#include "Dsp.h"
#include "Marking.h"
#include "InitialTable.h" /* Loading InitialTable */
#include "FieldParameter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabPowermeter dialog


CTabPowermeter::CTabPowermeter(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CTabPowermeter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabPowermeter)
	m_dSetPower = 10.0;
	m_dMeasuredPower = 0.0;
	m_iPowerCount = 0;
	m_dTotalof3Power = 0.0;
	m_pCommunicate = NULL;
	m_dAperture = 0.0;
	m_dPower = 0.0;
	m_dCurrent = 0.0;
	m_strDate = _T("");
	//}}AFX_DATA_INIT
//	m_pControl = new CQuantronix(pParent);

	m_dCurrentAmpare;
}


void CTabPowermeter::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabPowermeter)
	DDX_Text(pDX, IDC_SETED_POWER, m_dSetPower);
	DDX_Text(pDX, IDC_CURRENT_POWER, m_dMeasuredPower);
	DDX_Text(pDX, IDC_SAVED_APERTURE, m_dAperture);
	DDX_Text(pDX, IDC_SAVED_POWER, m_dPower);
	DDX_Text(pDX, IDC_SAVED_CURRENT, m_dCurrent);
	DDX_Text(pDX, IDC_SAVED_DATE, m_strDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabPowermeter, CUserDialogEx)
	//{{AFX_MSG_MAP(CTabPowermeter)
	ON_MESSAGE(WM_RECEIVE_COM, OnReceive_Com)
	ON_BN_CLICKED(IDC_POWERMETER_5, OnAdjustPower)
	ON_BN_CLICKED(IDC_POWERMETER_7, OnRecordingMode)
	ON_EN_UPDATE(IDC_CURRENT_POWER, OnUpdateCurrentPower)
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabPowermeter message handlers

BOOL CTabPowermeter::OnInitDialog() 
{
	CUserDialogEx::OnInitDialog();
	//------------------------------------------------------------------
	
  //------------------------------------------------------------------
	
	// TODO: Add extra initialization here
	/* Load String */
	CLoadString LoadString;
	LoadString.LoadString(this, IDS_POWERMETER_1, IDC_POWERMETER_1, IDC_POWERMETER_7, FALSE, FALSE);

	/* Load Value */
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	if (pPointerManager->GetLaserControl() != NULL)
		LoadValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabPowermeter::LoadValue()
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	
	if (pPointerManager->GetLaserControl() != NULL) {
		m_dAperture = pPointerManager->GetLaserControl()->GetAperture();
		m_dCurrent = pPointerManager->GetLaserControl()->GetCurrent();
		m_dPower = pPointerManager->GetLaserControl()->GetMeasuredPower();
		m_strDate = pPointerManager->GetLaserControl()->GetDate();
		m_dSetPower = pPointerManager->GetLaserControl()->GetSetPower();
		m_dMeasuredPower = pPointerManager->GetLaserControl()->GetMeasuredPower();
		double tmp;
		tmp = pPointerManager->GetLaserControl()->GetCurrent(); 
	}		
	UpdateData(FALSE);
}

void CTabPowermeter::SetValue()
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();

	UpdateData(TRUE);
	pPointerManager->GetLaserControl()->SetMeasuredPower(m_dMeasuredPower);
}


void CTabPowermeter::CreateLaserControl()
{
	/*m_pControl = new CQuantronix();
	m_pControl->InitLaser(1,"9600,0,8,1");
	m_pControl->ControlEnable(true);
	m_pControl->SetExternalPRF(true); 

	if(m_pControl->StartupComplete() == TRUE)
	{
		double Template =0;
		Template = m_pControl->GetCurrent(); 	
	}*/
}
/* 보정과 Laser Control이 관련 있는 이유는 Current를 보정해주는 신호를 보내줘야하기 때문 */
void CTabPowermeter::OnAdjustPower() 
{
	// TODO: Add your control notification handler code here
	CPointerManager *pPointerManager = pPointerManager->GetInstance();

	/* 통신이 닫혀 있으면 Open 시키기 */
	if (m_pCommunicate == NULL || m_pCommunicate->GetIsConnect() == FALSE) {
		m_pCommunicate = new CRS232("Power Adjustment", this);
		if (m_pCommunicate->StartCommunicate() < 0)
			return;
	}	
 
	/* Open 성공했으면 Connect는 TRUE */
	m_pCommunicate->SetIsConnect(TRUE);
	

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	pPointerManager->GetLaserControl()->PowerAdjustment(m_pCommunicate, TRUE);
}

/* 걍 Util */
void CTabPowermeter::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

CString CTabPowermeter::strRcvData2Char(int nRcvSize)
{
	CString strData;
	//--- 수신 갯수만큼..
	for( int i=0; i< nRcvSize; i++ )
	{
		strData += rcvBuf[i];
	}
	//--- 맨 뒤에는 줄바꿈..Edit Box의 다음줄에 출력하기위해 
	strData += _T( "\r\n" );
	//--- 변환된 문자열 넘김.
	return strData;
}

LRESULT CTabPowermeter::OnReceive_Com(WPARAM wParam,LPARAM lParam)
{

	return TRUE;
}

double CTabPowermeter::GetAjustValue(double dCurrent , double dSetting, double dEdge)
{
	double fAdjust = 0;
	
	if (dSetting - dCurrent > dSetting * dEdge*2)
		fAdjust = 1;
	else if (dCurrent - dSetting > dSetting * dEdge*2)
		fAdjust = -1;
	else if (dSetting - dCurrent > dSetting * dEdge)
		fAdjust = 0.5;
	else if (dCurrent - dSetting > dSetting * dEdge)
		fAdjust = -0.5;
	else if (dSetting - dCurrent > dSetting * dEdge/2)
		fAdjust = 0.2;
	else if (dCurrent - dSetting > dSetting * dEdge/2)
		fAdjust = -0.2;
	else
		;

	return fAdjust;
}


void CTabPowermeter::OnRecordingMode() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SAVED_APERTURE)->EnableWindow(TRUE);
	/* 보류 */
//	GetDlgItem(IDC_SAVED_POWER)  ->EnableWindow(TRUE);
//	GetDlgItem(IDC_SAVED_CURRENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_DATE)  ->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_APERTURE)->SetFocus();		
	
}

/* 파워 측정이 끝난 후에는 자동적으로 변수 셋팅 */
void CTabPowermeter::OnUpdateCurrentPower() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CTabPageSSL::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	
	if (pPointerManager->GetLaserControl() != NULL) {
		CString strTemp;
		GetDlgItem(IDC_CURRENT_POWER)->GetWindowText(strTemp);
		GetDlgItem(IDC_SAVED_POWER)->SetWindowText(strTemp);
	}
}

void CTabPowermeter::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CUserDialogEx::OnActivate(nState, pWndOther, bMinimized);
	

	
}
