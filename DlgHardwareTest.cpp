// DlgHardwareTest.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgHardwareTest.h"
#include "TransUnit.h"
#include "ConcreteIterator.h"
#include "PointerManager.h"
#include "InitialTable.h"
#include "FieldParameter.h"
#include "MainFrm.h" 
#include "Dsp.h"

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

/////////////////////////////////////////////////////////////////////////////
// CDlgHardwareTest dialog


CDlgHardwareTest::CDlgHardwareTest(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgHardwareTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHardwareTest)
	m_scannerX = 0;
	m_scannerY = 0;
	m_fq = 20;
	m_pw = 50;
	//}}AFX_DATA_INIT
}


void CDlgHardwareTest::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHardwareTest)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_SCANNER_X_MOVE, m_scannerX);
	DDV_MinMaxInt(pDX, m_scannerX, -100, 100);
	DDX_Text(pDX, IDC_EDIT_SCANNER_Y_MOVE, m_scannerY);
	DDV_MinMaxInt(pDX, m_scannerY, -100, 100);
	DDX_Text(pDX, IDC_QSW_FQ, m_fq);
	DDX_Text(pDX, IDC_QSW_PW, m_pw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHardwareTest, CUserDialogEx)
	//{{AFX_MSG_MAP(CDlgHardwareTest)
	ON_BN_CLICKED(IDC_STARTPOINT, OnStartingPoint)
	ON_BN_CLICKED(IDC_LASER_ON, OnLaserOn)
	ON_BN_CLICKED(IDC_LASER_OFF, OnLaserOff)
	ON_BN_CLICKED(IDC_SCANNERMOVE, OnScannermove)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgHardwareTest::OnBnClickedOk)
	ON_BN_CLICKED(65535, &CDlgHardwareTest::OnBnClicked65535)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHardwareTest message handlers

void CDlgHardwareTest::OnStartingPoint() 
{
	// TODO: Add your control notification handler code here
//	stop_execution();
//	home_position(0,0);
//	goto_xy(0,0);
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		n_goto_xy(RTC_CARD_NUM_2,0, 0);
	}
	else
	{
		n_goto_xy(RTC_CARD_NUM_1,0, 0);
	}


}

void CDlgHardwareTest::OnLaserOn() 
{
	CDsp *pDsp = CDsp::GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CString strTemp;
	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	int nTimer = GetDlgItemInt(IDC_SET_TIMER);
	//if(nTimer > 0)
	{
		//TimedLaserOn();
		//return;
	}

	// TODO: Add your control notification handler code here
	int m_qsw_fq = GetDlgItemInt(IDC_QSW_FQ);
	
	if(m_qsw_fq < 20)
	{
		AfxMessageBox("20 이상의 정수를 입력하세요.");
		return;
	}

	int m_qsw_pw = GetDlgItemInt(IDC_QSW_PW);

	if(m_qsw_pw < 1)
	{
		AfxMessageBox("0 보다 큰 정수를 입력하세요.");
		return;
	}

	//enable_laser();	

	//SetParaMeter(0);

	
	
//	mark_abs(0,0);

//	while(!get_list_space()) ;
	//set_end_of_list();

#ifdef _RTC_Test_		
	enable_laser();
	CParameter *pParameter = iterator->GetCurrentItem();
	double dCurrent = pParameter->GetLaserPowerSet();
	if(pDsp->GetInitialStatus())
	{
		write_8bit_port((unsigned short)(dCurrent));
		write_8bit_port_list((unsigned short)(dCurrent));


		//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
		pDsp->OutputIOList(RTCIO_O_MO, true);
		pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
	}
#endif


	Sleep(50);
	//laser_signal_on();
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		n_enable_laser(RTC_CARD_NUM_2);
		SetParaMeter(RTC_CARD_NUM_2,0);
		n_jump_abs(RTC_CARD_NUM_2, 0,0);
		n_goto_xy(RTC_CARD_NUM_2, 0, 0);
		n_laser_signal_on(RTC_CARD_NUM_2);
	}
	else
	{
		n_enable_laser(RTC_CARD_NUM_1);
		SetParaMeter(RTC_CARD_NUM_1,0);
		n_jump_abs(RTC_CARD_NUM_1, 0,0);
		n_goto_xy(RTC_CARD_NUM_1, 0, 0);
		n_laser_signal_on(RTC_CARD_NUM_1);
	}
}

void CDlgHardwareTest::OnLaserOff() 
{
	CDsp *pDsp = CDsp::GetInstance();
	// TODO: Add your control notification handler code here
	/*
	stop_execution();
	laser_signal_off();
	home_position(0,0);
	*/
	//goto_xy(0, 0);
	
	

	//laser_signal_off();
	//disable_laser();

	//goto_xy(0, 0);

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		n_stop_execution(RTC_CARD_NUM_2);
		n_laser_signal_off(RTC_CARD_NUM_2);
		n_disable_laser(RTC_CARD_NUM_2);
		n_goto_xy(RTC_CARD_NUM_2,0, 0);
		n_laser_signal_on(RTC_CARD_NUM_2);

		//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 
		pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, FALSE);
	
	}
	else
	{
		n_stop_execution(RTC_CARD_NUM_1);
		n_laser_signal_off(RTC_CARD_NUM_1);
		n_disable_laser(RTC_CARD_NUM_1);
		n_goto_xy(RTC_CARD_NUM_1,0, 0);
		n_laser_signal_on(RTC_CARD_NUM_1);

		//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 
		pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, FALSE);
	}

}

BOOL CDlgHardwareTest::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();

	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(pInitialTable->GetLaser() == LASER_LASERVALL)
	{
		SetDlgItemText(IDC_DUTY, "ns");
	}
	else
	{
		SetDlgItemText(IDC_DUTY, "%");
	}

	((CButton*)GetDlgItem(IDC_RADIO_HEAD2))->SetCheck(TRUE);

	UpdateData(FALSE);

	SetTimer(1, 100, NULL);
	return TRUE;
}

BOOL CDlgHardwareTest::SetParaMeter(int nCardNo, int index)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	
	int m_qsw_fq = GetDlgItemInt(IDC_QSW_FQ);
	int m_qsw_pw = GetDlgItemInt(IDC_QSW_PW);

	set_firstpulse_killer_list(pParameter->GetFPS() * 8); 

	//write_8bit_port_list((unsigned short)(uSetPower));

	int nQswFrequence = 1000 / m_qsw_fq / 2;
	int nQswPulseDuty = (1000 / (double)m_qsw_fq) * ((double)m_qsw_pw / 100);
	n_set_laser_timing(nCardNo,nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 0);
	
	n_set_laser_delays(nCardNo,pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());
	n_set_scanner_delays(nCardNo,pParameter->GetJumpDelay()/10,pParameter->GetMarkDelay()/10,pParameter->GetStrokeDelay()/10);

	double JumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();
	double MarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 

	n_set_mark_speed(nCardNo,MarkSpeed);
	n_set_jump_speed(nCardNo,JumpSpeed);	

	return TRUE;
}

void CDlgHardwareTest::OnScannermove() 
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CDsp *pDsp = CDsp::GetInstance();

	int nMaxmm = pInitialTable->GetMMSize();
	int nMaxfield = pInitialTable->GetFieldSize();
	int moveX = 0, moveY = 0;

	if(IsDlgButtonChecked(IDC_CHECK_FLY))
	{
		CString strTemp;
		double dScaleFactorX,dScaleFactorY;
		dScaleFactorX = 0.0;dScaleFactorY = 0.0;

		if( pFieldParameter->GetKX() != 0)
			dScaleFactorX = (nMaxfield / nMaxmm) / pFieldParameter->GetKX();
		if( pFieldParameter->GetKY() != 0)
			dScaleFactorY = (nMaxfield / nMaxmm) / pFieldParameter->GetKY();

		if(pDsp->GetSimulate_Encoder() > 0){
			pDsp->SetFlyX(dScaleFactorX/1000);
			pDsp->SetFlyY(dScaleFactorY/1000);
		}
		else{
			pDsp->SetFlyX(dScaleFactorX);
			pDsp->SetFlyY(dScaleFactorY);
		}
	}

	// TODO: Add your control notification handler code here
	

	

	int m_scannerMoveX = GetDlgItemInt(IDC_EDIT_SCANNER_X_MOVE);
	int m_scannerMoveY = GetDlgItemInt(IDC_EDIT_SCANNER_Y_MOVE);

	moveX = ((nMaxfield/nMaxmm)*m_scannerMoveX);
	moveY = ((nMaxfield/nMaxmm)*m_scannerMoveY);

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		n_goto_xy(RTC_CARD_NUM_2,moveX, moveY);
	}
	else
	{
		n_goto_xy(RTC_CARD_NUM_1,moveX, moveY);
	}

	
}



void CDlgHardwareTest::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUserDialogEx::OnOK();
}


void CDlgHardwareTest::OnBnClicked65535()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgHardwareTest::TimedLaserOn(void)
{
	int nTimer = GetDlgItemInt(IDC_SET_TIMER);
	CDsp *pDsp = CDsp::GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CString strTemp;
	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	double cs,sn;
	double m_dMaxField;
	double m_dMaxMM;
	bool bMarkFlag = TRUE;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;

	double dTimedValue = 0;
	double dDistance = 100;//100mm
	dTimedValue = dDistance / pFieldParameter->GetRollSpeed();
	int nCardNo = RTC_CARD_NUM_1;

	

	

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
		nCardNo = RTC_CARD_NUM_2;
	else
		nCardNo = RTC_CARD_NUM_1;

	pDsp->nOutputIO(nCardNo, RTC_SIG_O_PROGRESS, TRUE);

	//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 

	
	SingleScannerParameter HEAD2Parameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
	pDsp->nSetScannerParameter(nCardNo,HEAD2Parameter.flagSpeed,HEAD2Parameter);
	//pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2Parameter.flagExtSpeed,HEAD2Parameter);
	n_goto_xy(nCardNo,0,0);

	n_set_start_list(nCardNo,1);

#ifdef _RTC_Test_		
		enable_laser();
		CParameter *pParameter = iterator->GetCurrentItem();
		double dCurrent = pParameter->GetLaserPowerSet();
		if(pDsp->GetInitialStatus())
		{
			write_8bit_port((unsigned short)(dCurrent));
			write_8bit_port_list((unsigned short)(dCurrent));


			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			pDsp->OutputIOList(RTCIO_O_MO, true);
			pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
		}
#endif

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		pDsp->SetFlyXHEAD2(1.0); pDsp->SetFlyYHEAD2(0.0);
	}
	else
	{
		pDsp->SetFlyXHEAD1(1.0); pDsp->SetFlyYHEAD1(0.0);
	}
	
	n_save_and_restart_timer(nCardNo);
	
	//if(nTimer > 0)
		n_timed_mark_abs(nCardNo,0,0, nTimer * 1000 /*1000000*/);
	//else
		//laser_signal_on();
		//laser_signal_on_list();
		//n_laser_signal_on_list(nCardNo);
	//n_timed_mark_abs(nCardNo,0,0, 1000000);//1초동안 레이져 출사. 이동거리 확인용
	//laser_on_list(100000);// 1초간 출사
	//laser_on_list(dTimedValue * 100000);// 1초간 출사

	n_save_and_restart_timer(nCardNo);
	int nFlagMannualCutEncoderSumCount = 0;
	int nNextSumCount = 0;


	double dManualCutWidth = 10;


	n_set_end_of_list(nCardNo);
	n_execute_list(nCardNo,1);

	Sleep(100);

	 UINT Busy, Pos;
	 CString str;
 //   //  Wait for no list busy
    do
    {
        n_get_status(nCardNo, &Busy, &Pos );
		//Sleep(1);
		//str.Format("busy:%d_Pos:%d", Busy, Pos);
		//SetDlgItemText(IDC_STATIC_MON, str);
		Sleep(10);
    }
    while ( Busy );
	
	strTemp.Format("%.3f", n_get_time(nCardNo));
	SetDlgItemText(IDC_MARK_TIME, strTemp);
}


void CDlgHardwareTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		double dMmSize, dFieldSize;
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->GetSize(&dMmSize, &dFieldSize);
		CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
		
		CDsp *pDsp = CDsp::GetInstance();
		CString strTemp;
		double dResultX,dResultY;

		//dDoubleCuttingStartPos = pTransUnit->GetMM(nLineWidth, FIELD);
		pTransUnit->SetValueWithField(pDsp->GetPosX());
		dResultX = pTransUnit->GetValue(MM);
		pTransUnit->SetValueWithField(pDsp->GetPosY());
		dResultY = pTransUnit->GetValue(MM);

		strTemp.Format("Pos:%d(%.3f) , %d(%.3f)", pDsp->GetPosX(), dResultX, pDsp->GetPosY(), dResultY);
		SetDlgItemText(IDC_SCANNER_POS, strTemp);
	}

	CUserDialogEx::OnTimer(nIDEvent);
}
