 // TabStandardPara.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TabStandardPara.h"
#include "LoadString.h"
#include "FieldParameter.h"
#include "PointerContainer.h"
#include "PointerManager.h"
#include "InitialTable.h"
#include "RS232.h"
#include "TimeChecker.h"
#include "DlgFiber.h"
#include "Dsp.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "./Control/ctpush.h"
#include "./Control/cttextctrl.h"

/*
#if	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#if	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#endif

#if	_RTC4eth_
#include ".\Include\Rtc4eth\RTC4ethexpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4impl.h"
//#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif

#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__; 
#endif

#define WM_RECEIVE_COM      WM_USER + 4 

#define SPI_LATCH_HIGH	0x00000100//8
#define SPI_LATCH_LOW	0xFFFFFEFF
/////////////////////////////////////////////////////////////////////////////
// CTabStandardPara dialog


CTabStandardPara::CTabStandardPara(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabStandardPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabStandardPara)
	m_iFPS = 0;
	m_iJumpDelay = 0;
	m_iJumpStep = 0;
	m_iLaserOnDelay = 0;
	m_iLaserOffDelay = 0;
	m_iMarkDelay = 0;
	m_iMarkStep = 0;
	m_iStepPeriod = 0;
	m_iStrokeDelay = 0;
	m_iFrequency = 0;
	m_iPulseWidth = 0;
	m_iLampPower = 0;
	m_dLaserPower = 0.0;
	m_iPulseCount = 0;
	m_pCommunicate =  NULL;
	m_iPst = 0;
	//}}AFX_DATA_INIT
	m_PowerMeasermentComport=-1;

	//-----------------------------NEW Parameter-----------------------------------
	m_iJumpSpeed = 0;
	m_iJumpPower = 0;
	m_iStartSpeed = 0;
	m_iStartPower = 0;
	m_iStartExtSpeed = 0;
	m_iStartExtPower = 0;
	m_iStartChangeDelay = 0;
	m_iEndSpeed = 0;
	m_iEndPower = 0;
	m_iEndExtPower = 0;
	m_iEndExtSpeed = 0;
	m_iEndChangeDelay = 0;
	m_iLineSpeed = 0;
	m_iLinePower = 0;
	m_iLineOffsetPower = 0;
	m_iFlagJumpSpeed = 13000;
	//---------------- New Position Control Data-----------------------------
	m_iScaleM5 = 0;
	m_iScaleM4 = 0;
	m_iScaleM3 = 0;
	m_iScaleM2 = 0;
	m_iScaleM1 = 0;
	m_iScale0 = 0;
	m_iScale1 = 0;
	m_iScale2 = 0;
	m_iScale3 = 0;
	m_iScale4 = 0;
	m_iScale5 = 0;

	m_iNonflagExtSpeed = 0;
	m_iNonflagLineExtSpeed = 0;
	m_iNonflagExtLen = 0;
	m_iNonFlagLineExtLen = 0;
	m_iFlagExtLen = 0;
}


void CTabStandardPara::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabStandardPara)
	DDX_Text(pDX, IDC_FPS_DELAY, m_iFPS);
	DDX_Text(pDX, IDC_CTTEXT_JUMPDELAY, m_iJumpDelay);
	DDX_Text(pDX, IDC_JUMP_STEP, m_iJumpStep);
	DDV_MinMaxInt(pDX, m_iJumpStep, 0, 50000);
	DDX_Text(pDX, IDC_CTTEXT_LASERONDELAY, m_iLaserOnDelay);
	DDX_Text(pDX, IDC_CTTEXT_LASEROFFDELAY, m_iLaserOffDelay);
	DDX_Text(pDX, IDC_CTTEXT_MARKDELAY, m_iMarkDelay);
	DDX_Text(pDX, IDC_MARK_STEP, m_iMarkStep);
	DDV_MinMaxInt(pDX, m_iMarkStep, 0, 50000);
	DDX_Text(pDX, IDC_STEP_PERIOD, m_iStepPeriod);
	DDX_Text(pDX, IDC_CTTEXT_POLYGONDELAY, m_iStrokeDelay);
	DDX_Text(pDX, IDC_QSW_FREQ, m_iFrequency);
	DDX_Text(pDX, IDC_PULSE_WIDTH, m_iPulseWidth);
	DDX_Text(pDX, IDC_LAMP_POWER, m_iLampPower);
	DDX_Text(pDX, IDC_LASER_POWER, m_dLaserPower);
	DDX_Text(pDX, IDC_PULSE_COUNT, m_iPulseCount);
	DDX_Text(pDX, IDC_EDIT_PST, m_iPst);
	//}}AFX_DATA_MAP
	//-------------------------NEW Parameter------------------------------
	DDX_Text(pDX, IDC_CTTEXT_FLAGMARKSPEED, m_iStartSpeed);
	DDX_Text(pDX, IDC_CTTEXT_FLAG_POWER, m_iStartPower);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGLINE_SPEED, m_iStartExtSpeed);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGLINE_POWER, m_iStartExtPower);
	DDX_Text(pDX, IDC_Start_Change_Delay, m_iStartChangeDelay);
	DDX_Text(pDX, IDC_CTTEXT_FLAGEXT_SPEED, m_iEndSpeed);
	DDX_Text(pDX, IDC_CTTEXT_FLAGEXT_POWER, m_iEndPower);
	DDX_Text(pDX, IDC_End_Ext_Speed, m_iEndExtSpeed);
	DDX_Text(pDX, IDC_End_Ext_Power, m_iEndExtPower);
	DDX_Text(pDX, IDC_End_Change_Delay, m_iEndChangeDelay);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGINOUT_SPEED, m_iLineSpeed);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGINOUT_POWER, m_iLinePower);
	DDX_Text(pDX, IDC_Line_Offset_Power, m_iLineOffsetPower);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAG_JUMPSPEED, m_iJumpSpeed);
	DDX_Text(pDX, IDC_Jump_Power, m_iJumpPower);
	

	

	//------------------------ New Position Control Data -------------------
	DDX_Text(pDX, IDC_Scale_m5, m_iScaleM5);
	DDX_Text(pDX, IDC_Scale_m4, m_iScaleM4);
	DDX_Text(pDX, IDC_Scale_m3, m_iScaleM3);
	DDX_Text(pDX, IDC_Scale_m2, m_iScaleM2);
	DDX_Text(pDX, IDC_Scale_m1, m_iScaleM1);
	DDX_Text(pDX, IDC_Scale_0, m_iScale0);
	DDX_Text(pDX, IDC_Scale_1, m_iScale1);
	DDX_Text(pDX, IDC_Scale_2, m_iScale2);
	DDX_Text(pDX, IDC_Scale_3, m_iScale3);
	DDX_Text(pDX, IDC_Scale_4, m_iScale4);
	DDX_Text(pDX, IDC_Scale_5, m_iScale5);
	DDX_Text(pDX, IDC_CTTEXT_FLAG_JUMPSPEED,m_iFlagJumpSpeed);

	DDX_Text(pDX, IDC_CTTEXT_NONFLAGINOUTEXT_SPEED,m_iNonflagExtSpeed);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGLINEEXT_SPEED,m_iNonflagLineExtSpeed);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGINOUTEXT_LENGTH,m_iNonflagExtLen);
	DDX_Text(pDX, IDC_CTTEXT_NONFLAGLINEEXT_LENGTH,m_iNonFlagLineExtLen);
	DDX_Text(pDX, IDC_CTTEXT_FLAGEXT_LENGTH, m_iFlagExtLen);


	DDX_Control(pDX, IDC_SLIDER_SCALEM4, m_SliderScaleM4);
	DDX_Control(pDX, IDC_SLIDER_SCALEM3, m_SliderScaleM3);
	DDX_Control(pDX, IDC_SLIDER_SCALEM2, m_SliderScaleM2);
	DDX_Control(pDX, IDC_SLIDER_SCALEM1, m_SliderScaleM1);
	DDX_Control(pDX, IDC_SLIDER_SCALE0, m_SliderScale0);
	DDX_Control(pDX, IDC_SLIDER_SCALE1, m_SliderScale1);
	DDX_Control(pDX, IDC_SLIDER_SCALE2, m_SliderScale2);
	DDX_Control(pDX, IDC_SLIDER_SCALE3, m_SliderScale3);
	DDX_Control(pDX, IDC_SLIDER_SCALE4, m_SliderScale4);
	DDX_Control(pDX, IDC_Scale_m4, m_EdScaleM4);
	DDX_Control(pDX, IDC_Scale_m3, m_EdScaleM3);
	DDX_Control(pDX, IDC_Scale_m2, m_EdScaleM2);
	DDX_Control(pDX, IDC_Scale_m1, m_EdScaleM1);
	DDX_Control(pDX, IDC_Scale_0, m_EdScale0);
	DDX_Control(pDX, IDC_Scale_1, m_EdScale1);
	DDX_Control(pDX, IDC_Scale_2, m_EdScale2);
	DDX_Control(pDX, IDC_Scale_3, m_EdScale3);
	DDX_Control(pDX, IDC_Scale_4, m_EdScale4);

}


BEGIN_MESSAGE_MAP(CTabStandardPara, CDialog)
	//{{AFX_MSG_MAP(CTabStandardPara)
	ON_BN_CLICKED(IDC_STANDARDPARA_3, OnParaEdit)
	ON_BN_CLICKED(IDC_SET_POWER, OnSetPower)
	ON_MESSAGE(WM_RECEIVE_COM, OnReceive_Com)
	ON_EN_KILLFOCUS(IDC_LASER_POWER, OnKillfocusLaserPower)
	ON_EN_KILLFOCUS(IDC_LAMP_POWER, OnKillfocusLampPower)
	ON_EN_CHANGE(IDC_LAMP_POWER, OnChangeLampPower)
	ON_BN_CLICKED(IDC_SET_FREQ, OnSetFreq)
	ON_BN_CLICKED(IDC_BTN_CHECK_SPPED, OnBtnCheckSpped)
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_Scale_m4, &CTabStandardPara::OnEnChangeScalem4)
	ON_EN_CHANGE(IDC_Scale_m3, &CTabStandardPara::OnEnChangeScalem3)
	ON_EN_CHANGE(IDC_Scale_m2, &CTabStandardPara::OnEnChangeScalem2)
	ON_EN_CHANGE(IDC_Scale_m1, &CTabStandardPara::OnEnChangeScalem1)
	ON_EN_CHANGE(IDC_Scale_0, &CTabStandardPara::OnEnChangeScale0)
	ON_EN_CHANGE(IDC_Scale_1, &CTabStandardPara::OnEnChangeScale1)
	ON_EN_CHANGE(IDC_Scale_2, &CTabStandardPara::OnEnChangeScale2)
	ON_EN_CHANGE(IDC_Scale_3, &CTabStandardPara::OnEnChangeScale3)
	ON_EN_CHANGE(IDC_Scale_4, &CTabStandardPara::OnEnChangeScale4)

	
	ON_EN_CHANGE(IDC_FLAG_JUMP_SPEED, &CTabStandardPara::OnEnChangeFlagJumpSpeed)

	

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabStandardPara message handlers

BOOL CTabStandardPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//CLoadString LoadString;
	//LoadString.LoadString(this, IDS_STANDARDPARA_1, IDC_STANDARDPARA_1, IDC_STANDARDPARA_3, FALSE, FALSE);
	
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	//// 2007.10.02  
	//if (pInitialTable->GetLaser() == LASER_FIBER)
	//{
	//	SetDlgItemText(IDC_STATIC_PW, "%");
	//	GetDlgItem(IDC_STATIC_FPS)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_FPS_DELAY)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_STATIC_FPS_US)->ShowWindow(SW_HIDE);

	//	GetDlgItem(IDC_STATIC_LP)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_LAMP_POWER)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_STATIC_LP_P)->ShowWindow(SW_HIDE);

	//	GetDlgItem(IDC_SET_FREQ)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_PULSE_WIDTH)->EnableWindow(true);	
	//}

	//// 2007.10.02  
	//if (pInitialTable->GetLaser() == LASER_ROFIN)
	//{
	//	SetDlgItemText(IDC_STATIC_PW, "W");
	//	GetDlgItem(IDC_STATIC_FPS)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_FPS_DELAY)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_STATIC_FPS_US)->ShowWindow(SW_SHOW);

	//	GetDlgItem(IDC_STATIC_LP)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_LAMP_POWER)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_STATIC_LP_P)->ShowWindow(SW_SHOW);

	//	GetDlgItem(IDC_SET_FREQ)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_PULSE_WIDTH)->EnableWindow(true);
	//}

	//if (pInitialTable->GetLaser() == LASER_LASERVALL/* || pInitialTable->GetLaser() == LASER_FIBER*/)
	//{
	//	SetDlgItemText(IDC_DUTY, "ns");
	//	(GetDlgItem(IDC_POWER))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_LASER_POWER))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_STATIC_PW))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_SET_POWER))->ShowWindow(FALSE);
	//}

	//if (pInitialTable->GetLaser() == LASER_SPIFIBER)
	//{
	//	SetDlgItemText(IDC_DUTY, "ns");
	//	SetDlgItemText(IDC_STATIC_PW, "V");
	//	SetDlgItemText(IDC_POWER, "Laser Power(0~10)");
	//	(GetDlgItem(IDC_STATIC_PW))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_LASER_POWER))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_SET_POWER))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_POWER))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_STATIC_PST))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_EDIT_PST))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_STATIC_PST_MS))->ShowWindow(TRUE);
	//}

	//if (pInitialTable->GetLaser() == LASER_NOUSE)
	//{
	//	SetDlgItemText(IDC_DUTY, "us");
	//	//SetDlgItemText(IDC_STATIC_PW, "V");
	//	SetDlgItemText(IDC_STATIC_PW, "");
	//	SetDlgItemText(IDC_POWER, "Laser Power(0~10)");
	//	(GetDlgItem(IDC_STATIC_PW))->ShowWindow(TRUE);
	//	(GetDlgItem(IDC_LASER_POWER))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_SET_POWER))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_POWER))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_STATIC_PST))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_EDIT_PST))->ShowWindow(FALSE);
	//	(GetDlgItem(IDC_STATIC_PST_MS))->ShowWindow(FALSE);
	//}
	m_SliderScaleM4.SetRange(0,20);
	m_SliderScaleM4.SetPos(m_iScaleM4);
	m_SliderScaleM4.SetLineSize(1);
	m_SliderScaleM4.SetPageSize(2);
	int iPosM4 = m_SliderScaleM4.GetPos();
	CString sPosM4;
	sPosM4.Format(_T("%d"), iPosM4);
	m_EdScaleM4.SetWindowTextA(sPosM4);

	m_SliderScaleM3.SetRange(0,20);
	m_SliderScaleM3.SetPos(m_iScaleM3);
	m_SliderScaleM3.SetLineSize(1);
	m_SliderScaleM3.SetPageSize(2);
	int iPosM3 = m_SliderScaleM3.GetPos();
	CString sPosM3;
	sPosM3.Format(_T("%d"), iPosM3);
	m_EdScaleM3.SetWindowTextA(sPosM3);

	m_SliderScaleM2.SetRange(0,20);
	m_SliderScaleM2.SetPos(m_iScaleM2);
	m_SliderScaleM2.SetLineSize(1);
	m_SliderScaleM2.SetPageSize(2);
	int iPosM2 = m_SliderScaleM2.GetPos();
	CString sPosM2;
	sPosM2.Format(_T("%d"), iPosM2);
	m_EdScaleM2.SetWindowTextA(sPosM2);

	m_SliderScaleM1.SetRange(0,20);
	m_SliderScaleM1.SetPos(m_iScaleM1);
	m_SliderScaleM1.SetLineSize(1);
	m_SliderScaleM1.SetPageSize(2);
	int iPosM1 = m_SliderScaleM1.GetPos();
	CString sPosM1;
	sPosM1.Format(_T("%d"), iPosM1);
	m_EdScaleM1.SetWindowTextA(sPosM1);

	m_SliderScale0.SetRange(0,20);
	m_SliderScale0.SetPos(m_iScale0);
	m_SliderScale0.SetLineSize(1);
	m_SliderScale0.SetPageSize(2);
	int iPos0 = m_SliderScale0.GetPos();
	CString sPos0;
	sPos0.Format(_T("%d"), iPos0);
	m_EdScale0.SetWindowTextA(sPos0);

	m_SliderScale1.SetRange(0,20);
	m_SliderScale1.SetPos(m_iScale1);
	m_SliderScale1.SetLineSize(1);
	m_SliderScale1.SetPageSize(2);
	int iPos1 = m_SliderScale1.GetPos();
	CString sPos1;
	sPos1.Format(_T("%d"), iPos1);
	m_EdScale1.SetWindowTextA(sPos1);

	m_SliderScale2.SetRange(0,20);
	m_SliderScale2.SetPos(m_iScale2);
	m_SliderScale2.SetLineSize(1);
	m_SliderScale2.SetPageSize(2);
	int iPos2 = m_SliderScale2.GetPos();
	CString sPos2;
	sPos2.Format(_T("%d"), iPos2);
	m_EdScale2.SetWindowTextA(sPos2);

	m_SliderScale3.SetRange(0,20);
	m_SliderScale3.SetPos(m_iScale3);
	m_SliderScale3.SetLineSize(1);
	m_SliderScale3.SetPageSize(2);
	int iPos3 = m_SliderScale3.GetPos();
	CString sPos3;
	sPos3.Format(_T("%d"), iPos3);
	m_EdScale3.SetWindowTextA(sPos3);

	m_SliderScale4.SetRange(0,20);
	m_SliderScale4.SetPos(m_iScale4);
	m_SliderScale4.SetLineSize(1);
	m_SliderScale4.SetPageSize(2);
	int iPos4 = m_SliderScale4.GetPos();
	CString sPos4;
	sPos4.Format(_T("%d"), iPos4);
	m_EdScale4.SetWindowTextA(sPos4);




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabStandardPara::OnParaEdit() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_JUMP_DELAY)->EnableWindow(true);
	GetDlgItem(IDC_STROKE_DELAY)->EnableWindow(true);
	GetDlgItem(IDC_LASER_ON_DELAY)->EnableWindow(true);
	GetDlgItem(IDC_LASER_OFF_DELAY)->EnableWindow(true);
}

void CTabStandardPara::OnSetPower() 
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	if (pInitialTable->GetLaser() == LASER_FIBER)
	{
		/* 연결되지 않았으면 측정 못함 */
		CPointerManager *pPointerManager = pPointerManager->GetInstance();
		CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();

		if (IDYES == AfxMessageBox("파워를 설정하시겠습니까?", MB_YESNO))
		{
			GetDlgItem(IDC_LASER_POWER)->EnableWindow(false);
			GetDlgItem(IDC_QSW_FREQ)->EnableWindow(false);
			GetDlgItem(IDC_SET_FREQ)->EnableWindow(false);
			GetDlgItem(IDC_SET_POWER)->EnableWindow(false);
			int val = GetDlgItemInt(IDC_LASER_POWER);
			fiber->SendPowerSet(val);
			GetDlgItem(IDC_SET_POWER)->EnableWindow(true);
			GetDlgItem(IDC_SET_FREQ)->EnableWindow(true);
			GetDlgItem(IDC_QSW_FREQ)->EnableWindow(true);
			GetDlgItem(IDC_LASER_POWER)->EnableWindow(true);
		}
	}

	// 2007.10.02  
	if (pInitialTable->GetLaser() == LASER_ROFIN)
	{
		double m_InIpower = pInitialTable->GetNormalLimitPower(); 
		double CalValue_1;
		double CalValue_2;
		double LowValue, NormalValue, MaxValue;
		LowValue = 0; NormalValue = 0; MaxValue = 0;
		LowValue = pInitialTable->GetLowLimitPower(); 
		NormalValue = pInitialTable->GetNormalLimitPower();
		MaxValue = pInitialTable->GetMaxLimitPower();

		UpdateData(TRUE);
		double bValue1,bValue2;

		bValue1 = LowValue;
		bValue2 = NormalValue - ((MaxValue - NormalValue)/150)*100;  

		if(NormalValue > 0 && MaxValue > 0)
		{
			CalValue_1 = ((NormalValue - LowValue)/100.)*m_iLampPower + bValue1;
			CalValue_2 = ((MaxValue - NormalValue)/150.)*m_iLampPower + bValue2;
		}
		else
		{
			AfxMessageBox(IDS_STRING1056);
			return;
		}
		
		if(m_iLampPower < 100)
			m_dLaserPower = CalValue_1;
		else
			m_dLaserPower = CalValue_2;

		CString strPower;
		strPower.Format("%.2f", m_dLaserPower);
		SetDlgItemText(IDC_LASER_POWER, strPower);
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->SetSetedPowerValue(m_dLaserPower);
	}

	if (pInitialTable->GetLaser() == LASER_SPIFIBER)
	{
		CString strVal = "";
		GetDlgItemText(IDC_LASER_POWER, strVal);

		//psc ---------------------------------------------------------
		if(pInitialTable->GetKindOfRtcBoard() == 1)
		{
			
		}
		//-------------------------------------------------------------
		else if(pInitialTable->GetKindOfRtcBoard() == 0)
		{
			/* Laser Power Setting By USE RTC */
			//write_da_1((1023 * atof(strVal)) / 10.0);
		}
	}
}

LRESULT CTabStandardPara::OnReceive_Com(WPARAM wParam, LPARAM lParam)
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	char buffer[10] = "";
	
	int nRcvSize = (INT)lParam;
	if( nRcvSize <= 0 )
		return FALSE;
	CString strData = "";
	if(int(wParam) == m_PowerMeasermentComport)
	{
		strData = strRcvData2Char(nRcvSize);
		CString tempStr("S\n");
		strcpy(buffer, (LPCTSTR)strData);
		m_dLaserPower = atof(strData);
		UpdateData(FALSE);
		m_pCommunicate->StopCommunicate(); 
		m_pCommunicate->SetIsConnect(FALSE);
		m_pCommunicate = NULL;
		
		
	}
	return TRUE;
}

CString CTabStandardPara::strRcvData2Char(int nRcvSize)
{
	CString strData = "";
	//--- 수신 갯수만큼..
	char* buf = NULL;
	for( int i=0; i< nRcvSize; i++ )
	{
		 buf = m_pCommunicate->ReadData();
	}	 
	strData +=buf;
	strData.TrimRight(); 
	//--- 맨 뒤에는 줄바꿈..Edit Box의 다음줄에 출력하기위해 
	strData += _T( "\r\n" );
	//--- 변환된 문자열 넘김.
	return strData;
}

void CTabStandardPara::OnKillfocusLaserPower() 
{
	UpdateData(TRUE);
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	pFieldParameter->SetSetedPowerValue(m_dLaserPower); 	
}

void CTabStandardPara::OnKillfocusLampPower() 
{
	OnSetPower(); 	
}

void CTabStandardPara::OnChangeLampPower() 
{
	OnSetPower(); 
	
}

void CTabStandardPara::OnSetFreq() 
{
	// TODO: Add your control notification handler code here
	// 2011.04.08 syhun START - Laser control 통합.
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if (pInitialTable->GetLaser() == LASER_ROFIN || pInitialTable->GetLaser() == LASER_FIBER)
	{
		CPointerManager *pPointerManager = pPointerManager->GetInstance();
		CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();
		
		if (IDYES == AfxMessageBox("주파수를 설정하시겠습니까?", MB_YESNO))
		{
			GetDlgItem(IDC_LASER_POWER)->EnableWindow(false);
			GetDlgItem(IDC_QSW_FREQ)->EnableWindow(false);
			GetDlgItem(IDC_SET_FREQ)->EnableWindow(false);
			GetDlgItem(IDC_SET_POWER)->EnableWindow(false);
			int val = GetDlgItemInt(IDC_QSW_FREQ);
			fiber->SendFreqSet(val);
			GetDlgItem(IDC_SET_POWER)->EnableWindow(true);
			GetDlgItem(IDC_SET_FREQ)->EnableWindow(true);
			GetDlgItem(IDC_QSW_FREQ)->EnableWindow(true);
			GetDlgItem(IDC_LASER_POWER)->EnableWindow(true);
		}
	}
	// syhun END.
}

void CTabStandardPara::OnBtnCheckSpped() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double fSpeed;
	CString strSpeed;
	
	fSpeed = ((double)m_iMarkStep * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
				/ ((double)m_iStepPeriod / 1000000.)) / 10;
	strSpeed.Format("%.3f mm/sec",fSpeed);

	double fSpeedRTC;

	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	fSpeedRTC = fSpeed /(((double)dMmSize / (double) dFieldSize)* 1000) ; // RTC기준 속도단위변환시



	SetDlgItemText(IDC_ST_CHECK_SPPED, strSpeed);
}
BEGIN_EVENTSINK_MAP(CTabStandardPara, CTabPageSSL)

END_EVENTSINK_MAP()

void CTabStandardPara::OnEnChangeScalem4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScaleM4.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScaleM4.SetPos(iPosM4);
}

void CTabStandardPara::OnEnChangeScalem3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM3;
	m_EdScaleM3.GetWindowTextA(sPosM3);
	int iPosM3 = 20 - _ttoi(sPosM3);

	m_SliderScaleM3.SetPos(iPosM3);
}

void CTabStandardPara::OnEnChangeScalem2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScaleM2.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScaleM2.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScalem1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScaleM1.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScaleM1.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScale0()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScale0.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScale0.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScale1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScale1.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScale1.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScale2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScale2.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScale2.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScale3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScale3.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScale3.SetPos(iPosM4);
}
void CTabStandardPara::OnEnChangeScale4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString sPosM4;
	m_EdScale4.GetWindowTextA(sPosM4);
	int iPosM4 = 20 - _ttoi(sPosM4);

	m_SliderScale4.SetPos(iPosM4);
}




void CTabStandardPara::OnEnChangeFlagJumpSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CTabPageSSL::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString sFlagJumpSpeed;

	m_EFlagJumpSpeed.GetWindowTextA(sFlagJumpSpeed);



}










HBRUSH CTabStandardPara::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CTabPageSSL::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}




