// DlgRTC.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgRTC.h"
#include "afxdialogex.h"
#include "Dsp.h"
#include <math.h>
#include "MainFrm.h"
#include "DlgHardwareTest.h"



#define TIMER_SCANING		    1
#define MAX_IN_CNT			    16
#define MAX_OUT_CNT			    16
#define MAX_OUT_CNT_USE			4

// CDlgRTC 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRTC, CUserDialogEx)

CDlgRTC::CDlgRTC(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgRTC::IDD, pParent)
{

}

CDlgRTC::~CDlgRTC()
{
}

void CDlgRTC::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	
}


BEGIN_MESSAGE_MAP(CDlgRTC, CUserDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRTC::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_TEST, &CDlgRTC::OnBnClickedButtonScannerTest)
	ON_BN_CLICKED(IDC_CHECK0, &CDlgRTC::OnBnClickedCheck0)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgRTC::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgRTC::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgRTC::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgRTC::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CDlgRTC::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CDlgRTC::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CDlgRTC::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CDlgRTC::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CDlgRTC::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CDlgRTC::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CDlgRTC::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK12, &CDlgRTC::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_CHECK13, &CDlgRTC::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK14, &CDlgRTC::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK15, &CDlgRTC::OnBnClickedCheck15)
END_MESSAGE_MAP()


// CDlgRTC 메시지 처리기입니다.


void CDlgRTC::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUserDialogEx::OnOK();
}


BOOL CDlgRTC::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();

	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetTimer(TIMER_SCANING, 500, NULL);

	((CButton*)GetDlgItem(IDC_RADIO_HEAD2))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgRTC::OnTimer(UINT_PTR nIDEvent)
{
	CDsp *pRTC = CDsp::GetInstance();
	//unsigned short status = pRTC->ReadIoPort();
    unsigned short status = 0;
	unsigned short value = 0;
		 
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
		value = 0;
	}
	else
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
		value = 0;
	}


	if(nIDEvent == TIMER_SCANING)
	{
		for(int i = 0; i < MAX_IN_CNT; i++)
		{
			//status = pRTC->ReadIoPort();
			//status = pRTC->n_ReadIoPort();
			if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
				status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
			else
				status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
			
			value = status & (unsigned short)((double)pow(2.0, i));
			value = value >> i;

			if(i == 0) DisplayIO(IDC_PIC_LT_IN_00, value);
			else if(i == 1) DisplayIO(IDC_PIC_LT_IN_01, value);
			else if(i == 2) DisplayIO(IDC_PIC_LT_IN_02, value);
			else if(i == 3) DisplayIO(IDC_PIC_LT_IN_03, value);
			else if(i == 4) DisplayIO(IDC_PIC_LT_IN_04, value);
			else if(i == 5) DisplayIO(IDC_PIC_LT_IN_05, value);
			else if(i == 6) DisplayIO(IDC_PIC_LT_IN_06, value);
			else if(i == 7) DisplayIO(IDC_PIC_LT_IN_07, value);
			else if(i == 8) DisplayIO(IDC_PIC_LT_IN_08, value);
			else if(i == 9) DisplayIO(IDC_PIC_LT_IN_09, value);
			else if(i == 10) DisplayIO(IDC_PIC_LT_IN_10, value);
			else if(i == 11) DisplayIO(IDC_PIC_LT_IN_11, value);
			else if(i == 12) DisplayIO(IDC_PIC_LT_IN_12, value);
			else if(i == 13) DisplayIO(IDC_PIC_LT_IN_13, value);
			else if(i == 14) DisplayIO(IDC_PIC_LT_IN_14, value);
			else if(i == 15) DisplayIO(IDC_PIC_LT_IN_15, value);
		}


		for(int i = 0; i < MAX_OUT_CNT; i++)
		{
			//status = pRTC->GetIoStatus();
			if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
				status = pRTC->n_GetIoStatus(RTC_CARD_NUM_2);
			else
				status = pRTC->n_GetIoStatus(RTC_CARD_NUM_1);

			value = status & (unsigned short)((double)pow(2.0, i));
			value = value >> i;

			if(i == 0) DisplayIO(IDC_PIC_LT_OUT_00, value);
			else if(i == 1) DisplayIO(IDC_PIC_LT_OUT_01, value);
			else if(i == 2) DisplayIO(IDC_PIC_LT_OUT_02, value);
			else if(i == 3) DisplayIO(IDC_PIC_LT_OUT_03, value);
			else if(i == 4) DisplayIO(IDC_PIC_LT_OUT_04, value);
			else if(i == 5) DisplayIO(IDC_PIC_LT_OUT_05, value);
			else if(i == 6) DisplayIO(IDC_PIC_LT_OUT_06, value);
			else if(i == 7) DisplayIO(IDC_PIC_LT_OUT_07, value);
			else if(i == 8) DisplayIO(IDC_PIC_LT_OUT_08, value);
			else if(i == 9) DisplayIO(IDC_PIC_LT_OUT_09, value);
			else if(i == 10) DisplayIO(IDC_PIC_LT_OUT_10, value);
			else if(i == 11) DisplayIO(IDC_PIC_LT_OUT_11, value);
			else if(i == 12) DisplayIO(IDC_PIC_LT_OUT_12, value);
			else if(i == 13) DisplayIO(IDC_PIC_LT_OUT_13, value);
			else if(i == 14) DisplayIO(IDC_PIC_LT_OUT_14, value);
			else if(i == 15) DisplayIO(IDC_PIC_LT_OUT_15, value);
			

		}
	}

	CUserDialogEx::OnTimer(nIDEvent);
}


void CDlgRTC::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(TIMER_SCANING);

	CUserDialogEx::OnClose();
}


void CDlgRTC::DisplayIO(int nID, int bStatus)
{
	CStatic *pIcon = (CStatic*)GetDlgItem(nID);



	switch(bStatus)
	{
		//case LED_GRAY:		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));			break;
		//case LED_GREEN_ON:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));		break;
		//case LED_GREEN_OFF:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_OFF)));		break;
		case 1:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));;		break;
		case 0:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_OFF)));		break;
		//case LED_YELLOW:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_YELLOW_ON)));		break;

	}
}


void CDlgRTC::OnBnClickedButtonScannerTest()
{
	CDlgHardwareTest hardwareTest;

	hardwareTest.DoModal();
}


void CDlgRTC::OutPut(int nPortNum)
{
	CDsp *pRTC = CDsp::GetInstance();
	

	unsigned short status = 0;
	unsigned short value = 0;

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
		value = 0;
		status = n_get_io_status(RTC_CARD_NUM_2);
	}
	else
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
		value = 0;
		status = n_get_io_status(RTC_CARD_NUM_1);

	}

	//unsigned short status = pRTC->ReadIoPort();
	//unsigned short value = 0;

	//status = pRTC->GetIoStatus();

	

	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;


	//pRTC->OutputIO(0, value);

	
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		if(value)
			pRTC->nOutputIO(RTC_CARD_NUM_2,nPortNum, FALSE);
		else
			pRTC->nOutputIO(RTC_CARD_NUM_2,nPortNum, TRUE);
	}
	else
	{
		if(value)
			pRTC->nOutputIO(RTC_CARD_NUM_1,nPortNum, FALSE);
		else
			pRTC->nOutputIO(RTC_CARD_NUM_1,nPortNum, TRUE);
	}

	/*
		if(value)
		pRTC->OutputIO(nPortNum, FALSE);
	else
		pRTC->OutputIO(nPortNum, TRUE);
		*/
}



void CDlgRTC::OnBnClickedCheck0()
{
	OutPut(0);
}


void CDlgRTC::OnBnClickedCheck1()
{
	OutPut(1);
}


void CDlgRTC::OnBnClickedCheck2()
{
	OutPut(2);
}


void CDlgRTC::OnBnClickedCheck3()
{
	OutPut(3);
}


void CDlgRTC::OnBnClickedCheck4()
{
	OutPut(4);
}


void CDlgRTC::OnBnClickedCheck5()
{
	OutPut(5);
}


void CDlgRTC::OnBnClickedCheck6()
{
	OutPut(6);
}


void CDlgRTC::OnBnClickedCheck7()
{
	OutPut(7);
}


void CDlgRTC::OnBnClickedCheck8()
{
	OutPut(8);
}


void CDlgRTC::OnBnClickedCheck9()
{
	OutPut(9);
}


void CDlgRTC::OnBnClickedCheck10()
{
	OutPut(10);
}


void CDlgRTC::OnBnClickedCheck11()
{
	OutPut(11);
}


void CDlgRTC::OnBnClickedCheck12()
{
	OutPut(12);
}


void CDlgRTC::OnBnClickedCheck13()
{
	OutPut(13);
}


void CDlgRTC::OnBnClickedCheck14()
{
	OutPut(14);
}


void CDlgRTC::OnBnClickedCheck15()
{
	OutPut(15);
}

