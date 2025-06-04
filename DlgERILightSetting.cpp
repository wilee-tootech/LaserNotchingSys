// DlgERILightSetting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgERILightSetting.h"
#include "afxdialogex.h"
#include "NX_LIGHT\IlluminationLVS.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "Include\EXTERN\cttextctrl.h"
#include "MathUtil.h"






// CDlgERILightSetting 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgERILightSetting, CDialogEx)



CDlgERILightSetting::CDlgERILightSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgERILightSetting::IDD, pParent)
{
	m_nLightIntensity = 1000;
	m_gLightMgr->GetContents(0)->GetBrightValueFromRS232(0);
}

CDlgERILightSetting::~CDlgERILightSetting()
{
}

void CDlgERILightSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
}


BEGIN_MESSAGE_MAP(CDlgERILightSetting, CDialogEx)
	
	ON_BN_CLICKED(IDC_LIGHT0_APPLY, &CDlgERILightSetting::OnBnClickedLight0Apply)
	ON_BN_CLICKED(IDC_LIGHT1_APPLY, &CDlgERILightSetting::OnBnClickedLight1Apply)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgERILightSetting::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CDlgERILightSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgERILightSetting 메시지 처리기입니다.


BOOL CDlgERILightSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	//cominfo.clear();
	//cominfo.nPortNum = 3; //2021.09.27 포트번호지정
	//cominfo.nDataBit = 8;
	//cominfo.nBaudRate = 19200;
	//cominfo.nStopBit = 1;
	//cominfo.nParity = 0;	


	//if(m_gLightMgr) delete m_gLightMgr;
	//m_gLightMgr = new CLightMgr(true);

	//m_gLightMgr->AddContents(new CIlluminationLVS(4, cominfo, CIlluminationLVS::LVS_PT));
	//m_gLightMgr->GetContents(0)->SetBrightValue(0,100);

	SetTimer(TIMER_CHECK_IS_RECIVE_MESSAGE_CHANGED,1,NULL);

	return TRUE;
}




void CDlgERILightSetting::OnBnClickedLight0Apply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	m_gLightMgr->GetContents(0)->SetLightOn(0,true);
	m_gLightMgr->GetContents(0)->SetLightOn(1,true);
	int channel0brightness	= (long)GetDlgItemInt(IDC_LIGHT0_BRIGHTNESS);

	m_gLightMgr->GetContents(0)->SetBrightValue(0,channel0brightness);
	m_gLightMgr->GetContents(0)->SetBrightValue(1,channel0brightness);
}


void CDlgERILightSetting::OnBnClickedLight1Apply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_gLightMgr->GetContents(0)->SetLightOn(1,true);
	int channel1brightness= (long)GetDlgItemInt(IDC_LIGHT1_BRIGHTNESS);

	m_gLightMgr->GetContents(0)->SetBrightValue(1,channel1brightness);
}
BEGIN_EVENTSINK_MAP(CDlgERILightSetting, CDialogEx)
	ON_EVENT(CDlgERILightSetting, IDC_CTPUSH_LOAD_LIGHTINFO, DISPID_CLICK, CDlgERILightSetting::ClickCtpushLoadLightinfo, VTS_NONE)
	ON_EVENT(CDlgERILightSetting, IDC_CTPUSH_SAVE_LIGHTINFO, DISPID_CLICK, CDlgERILightSetting::ClickCtpushSaveLightinfo, VTS_NONE)
	ON_EVENT(CDlgERILightSetting, IDC_CTPUSH_GETDATA_TEST, DISPID_CLICK, CDlgERILightSetting::ClickCtpushGetdataTest, VTS_NONE)
	ON_EVENT(CDlgERILightSetting, IDC_CTTEXT_LIGHT_INTENSITY, DISPID_CLICK, CDlgERILightSetting::ClickCttextLightIntensity, VTS_NONE)
	ON_EVENT(CDlgERILightSetting, IDC_CTPUSH_LOAD_LIGHTI_ON, DISPID_CLICK, CDlgERILightSetting::ClickCtpushLoadLightiOn, VTS_NONE)
	ON_EVENT(CDlgERILightSetting, IDC_CTPUSH_LOAD_LIGHTI_OFF, DISPID_CLICK, CDlgERILightSetting::ClickCtpushLoadLightiOff, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgERILightSetting::ClickCtpushLoadLightinfo()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_gLightMgr->GetContents(0)->LoadLightInfo();
}


void CDlgERILightSetting::ClickCtpushSaveLightinfo()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_gLightMgr->GetContents(0)->SaveLightInfo();
}


void CDlgERILightSetting::ClickCtpushGetdataTest()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_gLightMgr->GetContents(0)->SendTempData();
}


void CDlgERILightSetting::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	static int datacount = 0;
	switch (nIDEvent)
	{

	case TIMER_CHECK_IS_RECIVE_MESSAGE_CHANGED:
		{
			std::string reciveStr = m_gLightMgr->GetContents(0)->GetReciveData();
			if(!reciveStr.empty())
			{
				ParseReciveData(reciveStr);
			}
	
		}
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgERILightSetting::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	int indexnum = GetDlgItemInt(IDC_TEST_SEND_INDEX_NUM);

	CString sendString;
	GetDlgItemText(IDC_TEST_SEND_EDITBOX,sendString);

	std::string standardString = sendString;

	
	if(m_gLightMgr->GetContents(indexnum) != NULL)
	{
		m_gLightMgr->GetContents(indexnum)->SendCustomData(standardString);
	}


}


void CDlgERILightSetting::ClickCttextLightIntensity()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad keypadDlg;

	//keypadDlg.SetRange(0,1024,m_nLightIntensity);
	keypadDlg.SetRange(0,100,m_nLightIntensity);

	if(keypadDlg.DoModal() == IDOK)
	{
		CString strGetText = _T("");
		m_nLightIntensity = keypadDlg.GetResultInteger() * 255/ 100; 
		//m_nLightIntensity = keypadDlg.GetResultInteger();

		strGetText.Format("Light Intensity: %d ", keypadDlg.GetResultInteger());
		strGetText += '%'; //%는 안넣어진다.

		SetDlgItemText(IDC_CTTEXT_LIGHT_INTENSITY,strGetText);
		m_gLightMgr->GetContents(0)->SetBrightValue(0,  m_nLightIntensity);
		m_gLightMgr->GetContents(0)->GetBrightValueFromRS232(0);
		m_gLightMgr->GetContents(0)->SaveLightInfo();

		/* 2022.10.17 ch 2 추가 */
		m_gLightMgr->GetContents(0)->SetBrightValue(1,  m_nLightIntensity);
		m_gLightMgr->GetContents(0)->GetBrightValueFromRS232(1);
		m_gLightMgr->GetContents(0)->SaveLightInfo();


	}

	
	
	

}

void CDlgERILightSetting::SetDlgLightCttextBackcolor(int redIntensity)
{



	CCttextctrl* cttextLignt0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_LIGHT0));
	cttextLignt0->SetBackColor(redIntensity);


	CCttextctrl* cttextLignt1 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_LIGHT1));
	cttextLignt1->SetBackColor(redIntensity);

	CCttextctrl* cttextLignt2 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_LIGHT2));
	cttextLignt2->SetBackColor(redIntensity);

	CCttextctrl* cttextLignt3 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_LIGHT3));
	cttextLignt3->SetBackColor(redIntensity);


}

bool CDlgERILightSetting::ParseReciveData(std::string str)
{

	char tokenBuffer[100]; // 적당히크게
	char tokenBuffer2[100]; // 적당히크게
	char tokenBuffer3[100]; // 적당히크게
	strcpy(tokenBuffer,str.c_str());
	char* token = strtok(tokenBuffer," ");


	CString showString;
	int index = -100;
	int channel = -100;
	int brightness  = -100;
	int OnOff = -1;
	if(!strcmp(token,"getbrightness")) //true일때 0 반환
	{

		std::string parseString;
		sscanf(str.c_str(),"%s %d %d %d",tokenBuffer,&index,&channel,&brightness);
		double dLightIntensity = (double)brightness / 255.0 * 100.0;
		//double dLightIntensity = (double)brightness;
		
		/*if(m_nLightIntensity != 0 || m_nLightIntensity != 100)
		{
			dLightIntensity += 1;
		}*/
		
		dLightIntensity = CMathUtil::Round(dLightIntensity,0);

		showString.Format("Light Intensity: %d ",(int)dLightIntensity); 
		showString += '%';
		SetDlgItemText(IDC_CTTEXT_LIGHT_INTENSITY,showString);
		showString.Empty();
		SetDlgLightCttextBackcolor(brightness);
		showString += str.data();
		sumString += str.data();
		SetDlgItemText(IDC_CTPUSH_GETDATA_TEST,showString);

		return true;
	}
	else if(!strcmp(token,"getonoff")) //true일때 0 반환
	{
		std::string parseString;
		//sscanf(str.c_str(),"%s %d %d",tokenBuffer,&index,&OnOff);
		sscanf(str.c_str(),"%s %d %d\n",tokenBuffer,&index,&OnOff);
		
		if(OnOff != 1)
			SetDlgLightCttextBackcolor(0);	
		else
			m_gLightMgr->GetContents(0)->LoadLightInfo();
	
	}


	return false;
}



void CDlgERILightSetting::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CDlgERILightSetting::ClickCtpushLoadLightiOn()
{
	m_gLightMgr->GetContents(0)->SetLightOn(0,true);
	//m_gLightMgr->GetContents(0)->SetBrightValue(0,  m_nLightIntensity);
	//SetDelayTime(500);
	//m_gLightMgr->GetContents(0)->SetLightOn(1,true);
	//SetDelayTime(500);
	//m_gLightMgr->GetContents(0)->SetBrightValue(0,  m_nLightIntensity);
	//m_gLightMgr->GetContents(0)->GetLightInfo(0);
	SetDelayTime(500);
	m_gLightMgr->GetContents(0)->SaveLightInfo();
	
	SetDelayTime(500);
	m_gLightMgr->GetContents(0)->GetLightInfo(1);
		
}


void CDlgERILightSetting::ClickCtpushLoadLightiOff()
{
	m_gLightMgr->GetContents(0)->SetLightOn(0,false);
	SetDelayTime(500);
	//m_gLightMgr->GetContents(0)->SetBrightValue(0,  m_nLightIntensity);
	

	//m_gLightMgr->GetContents(0)->SetLightOn(1,false);
	//m_gLightMgr->GetContents(0)->SetBrightValue(0,  m_nLightIntensity);
	//SetDelayTime(500);
	//m_gLightMgr->GetContents(0)->GetLightInfo(0);

	//SetDelayTime(500);
	

	SetDelayTime(500);
	m_gLightMgr->GetContents(0)->SaveLightInfo();
	SetDelayTime(500);
	m_gLightMgr->GetContents(0)->GetLightInfo(1);
}



void CDlgERILightSetting::SetDelayTime(unsigned int iSecond)
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