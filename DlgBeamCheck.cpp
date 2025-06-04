// DlgBeamCheck.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgBeamCheck.h"
#include "Dsp.h"
#include "afxdialogex.h"


// CDlgBeamCheck 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgBeamCheck, CDialogEx)

CDlgBeamCheck::CDlgBeamCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBeamCheck::IDD, pParent)
{

}

CDlgBeamCheck::~CDlgBeamCheck()
{
}

void CDlgBeamCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBeamCheck, CDialogEx)
END_MESSAGE_MAP()


// CDlgBeamCheck 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(CDlgBeamCheck, CDialogEx)
	ON_EVENT(CDlgBeamCheck, IDC_CTPUSHCTRL_ON, DISPID_CLICK, CDlgBeamCheck::ClickCtpushctrlOn, VTS_NONE)
	ON_EVENT(CDlgBeamCheck, IDC_CTPUSHCTRL_OFF, DISPID_CLICK, CDlgBeamCheck::ClickCtpushctrlOff, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgBeamCheck::ClickCtpushctrlOn()
{
	CDsp *pDsp = pDsp->GetInstance();

	CString strCurrent,strDelay;
	double dCurrent;

	GetDlgItemText(IDC_EDIT_POWER, strCurrent);
	dCurrent = atof(strCurrent);
	
	
	//dVoltage = dCurrent / 10.0;
	pDsp->SetAnalogOutPut1(dCurrent);

	GetDlgItemText(IDC_EDIT_SHOTTIME, strDelay);
	pDsp->LaserSignalOn();
	SetDelayTime(atoi(strDelay));
	pDsp->LaserSignalOff();
}


void CDlgBeamCheck::ClickCtpushctrlOff()
{
	CDsp *pDsp = pDsp->GetInstance();
	pDsp->LaserSignalOff();
	
}


void CDlgBeamCheck::SetDelayTime(unsigned int iSecond)
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
