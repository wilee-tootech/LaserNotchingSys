// HanaLaser.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "HanaLaser.h"
#include "RS232.h"
#include "Defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AddStr(n) strcat(Msg , n ) 
/////////////////////////////////////////////////////////////////////////////
// CHanaLaser dialog


CHanaLaser::CHanaLaser(CWnd *pWnd)
{
	//{{AFX_DATA_INIT(CHanaLaser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetMsgNull();
	m_iBreak = 0;

	/* 다이로그에서 직접 초기화 대신 넘겨짐 */
	m_pCommunicate = new CRS232("Laser Control", pWnd);
	/* 변수 초기화 필요 */
	m_bIsConnect = FALSE;
	m_bIsShutterOn = FALSE;
	m_iCurrent = 0;	// Current는 파일 로딩으로 읽어들였다고 가정


	if (m_pCommunicate->StartCommunicate() < 0)
		return;

	m_strNowUsedTime = "";
	m_bIsConnect = TRUE;
}

CHanaLaser::~CHanaLaser()
{
	m_bIsConnect = FALSE;

	if(m_pCommunicate != NULL)  ///황 050419 잘 안되는것 같아 다시 죽임 
	{
		m_pCommunicate->StopCommunicate(); 
		delete m_pCommunicate;
	}
	if(m_pDLG)
	{
	}

}

int CHanaLaser::SetQsFrequency(char *frequency, int mode)
{
	
	int nCommandData = (int)(atof(frequency)*10);
	int nSendCode = SET_ACT_FREQUENCY;
	if( nCommandData < 30 )
		nCommandData = 30;

	BYTE sSend[5]="";
	WORD wData = (WORD)nCommandData;
		
	*(Msg) = 0x02;
	*(Msg+1) = (BYTE)nSendCode;
	*(Msg+2) = (BYTE)LOBYTE(wData);
	*(Msg+3) = (BYTE)HIBYTE(wData);
	*(Msg+4) = 0x03;
	
	return SendMsgWait();
}

char *CHanaLaser::GetLampCurrent()
{
	static char Msg1[22]={0,};
/////////////////////////////////사용하지 않음 
	/*
	char *tmp;
	
	*(Msg+0) = 'L';
	*(Msg+1) = 'C';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	if( !SendMsgWait() ) return NULL;
	tmp = GetMsgFromComm();
	tmp+=2;
	int i =0;
	int j= 0;
	
	while ( tmp )
	{
		if( *tmp <='9' && *tmp >='0')
		{
			Msg1[i] = *tmp;
			i++;
		}
		tmp ++;
		j++;
		if( j >20 ) break;
	}
	Msg1[i] = NULL;*/

	
	return Msg1;
}

char *CHanaLaser::GetStatus()
{
	char *Report=NULL;
	memset((char *)Report,0x00,80);
	ReadReportData();
	return Report;
}

char *CHanaLaser::GetInterLockMessage()
{

	////비트 데이터 라고 함 
	*(Msg+0) = (char)0x02;
	*(Msg+1) = (char)0x20;
	*(Msg+2) = (char)0xff;
	*(Msg+3) = (char)0xff;
	*(Msg+4) = (char)0x03;
	SendMsgWait();

   
	return 	GetMsgFromComm();
}

BOOL    CHanaLaser::SetMaxFrequency(UINT MaxFrq)
{
	//	MaxFrq = MaxFrq ; // double형인 Current 저장 (부모의 변수임)
	int wData = (double)MaxFrq * 10;
	Msg[0] = 0x02;

	Msg[1] = 0x03;
	Msg[2] = (BYTE)LOBYTE((int)wData);;
	Msg[3] = (BYTE)HIBYTE((int)wData);;
	Msg[4] = 0x03;



	SendMsgWait();
	return 	true;
}
char*   CHanaLaser::GetMaxFrequency()
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x14;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	return GetMsgFromComm();
}

BOOL    CHanaLaser::SetElapsedHour(UINT  nHour)
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x18;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	if(GetMsgFromComm() == 0x00)
	{
		return false;
	}
	return 	true;
}
char*    CHanaLaser::GetElapsedHour()
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x14;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	return GetMsgFromComm();
}

BOOL    CHanaLaser::SetElapsedMinute(UINT nMin)
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x06;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	if(GetMsgFromComm() == 0x00)
	{
		return false;
	}
	return 	true;
}
char*    CHanaLaser::GetElapsedMinute()
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x19;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	return GetMsgFromComm();
}

BOOL    CHanaLaser::SetLowFrequencyLimit(UINT LimitFrq)
{
	int wData = (double)LimitFrq * 10;
	Msg[0] = 0x02;

	Msg[1] = 0x07;
	Msg[2] = (BYTE)LOBYTE((int)wData);;
	Msg[3] = (BYTE)HIBYTE((int)wData);;
	Msg[4] = 0x03;



	SendMsgWait();
	return 	true;
	

}
char*    CHanaLaser::GetLowFrequencyLimit()
{
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x1a;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	return GetMsgFromComm();
}

int CHanaLaser::SendMsgWait(void)
{
	int result;
	
	result = SendDataToPort();
	
	if( result )
	{
		if( !WaitForResponse(1000) ) return NULL;
		if ( *(m_pCommunicate->ReadData()) == NULL ) return NULL; // RS232 buff에 직접 접근하는 대신 이용
	}
	
	return result;
}

char *CHanaLaser::GetMsgFromComm()
{
	int i=0;
	static char R_Msg[22];
	memset( (char *)R_Msg, 0x00, 20);
	
	do
	{

		if( R_Msg[i] = *(m_pCommunicate->ReadData()+i)/*rs.m_buff[i]*/ ){
			i++;
			continue;
		}
		else break;

		
	} while (i < 22);
	


/*
	switch(R_Msg[1]) 
	{
	case 0x06:
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
	case 0x4c:
		memset((char *)R_Msg, 0x00, 20);
		R_Msg[0] = 0x01;
			break;
	case 0x50:
		memset((char *)R_Msg, 0x00, 20);
		R_Msg[0] = 0x00;
		break;
	default :
		break;
     	
	}*/

	return R_Msg;
	
}

/* 실제 Data를 포트에 써주는 놈. SendMsg와 동일*/
BOOL CHanaLaser::SendDataToPort()
{
	int writecount;

	writecount = m_pCommunicate->WriteData((BYTE *)Msg , 5);
	
	if (writecount <= 0)
	{
//		AfxMessageBox("Fail to Write",MB_OK);
		return FALSE;
	}

	SetMsgNull();

	return TRUE;
}

int CHanaLaser::WaitForResponse(unsigned int wait)
{
	DWORD dwTick= GetTickCount();
	MSG msg;
	
	while (GetTickCount() - dwTick < wait)
	{
		if (PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (isReceived==1){
			isReceived= 0;
			return 1;
		}
		Sleep(5);
		if (m_iBreak == 1) break;
	}
	
    return 0;
}

void CHanaLaser::SetMsgNull(void) //이것은 Private 인게 좋겠다.
{
	int i=MSG_SIZE-1;
	
	do
	{
		Msg[i--]=0x00;
	} while (i>=0);
}

 
UINT CHanaLaser::ShutterOn() 
{
// CString message;
//memset((BYTE*)message,0x00,6);
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x03;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
//	message = GetMsgFromComm();
	
	return 1;//(UINT)message[2];
}

UINT CHanaLaser::ShutterOff() 
{
// CString message;
//	memset((BYTE*)message,0x00,6);
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x04;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
//	message = GetMsgFromComm();
	
	return 1;//(UINT)message[2];
}

UINT	CHanaLaser::RemoteOn()
{
/*CString message;*/
//	memset((BYTE*)message,0x00,6);
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x0b;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
//	message = GetMsgFromComm();
	
	return 1;//(UINT)message[2];
}
UINT	CHanaLaser::GetNowFrequency()
{
//CString message;
//	memset((BYTE*)message,0x00,6);
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x0b;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
//	message = GetMsgFromComm();
	
	return 1;//1(UINT)message[2];
	
}
UINT	CHanaLaser::RemoteOff()
{
//CString message;
//emset((BYTE*)message,0x00,6);
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x0c;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
//	message = GetMsgFromComm();
	
	return 1;//(UINT)atoi(message[2]);
}
UINT	CHanaLaser::QSW_On()
{
// CString message;

	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x05;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
// 	message = GetMsgFromComm();
	
	return 1;//(UINT)message[2];
}
UINT	CHanaLaser::QSW_Off()
{
// 	CString message;
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x06;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
// 	message = GetMsgFromComm();
	
	return 1;// (UINT)message[2];
}
UINT	CHanaLaser::LaserOn()
{
// 	CString message;
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x01;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
// 	message = GetMsgFromComm();
	
	return 1;//(UINT)message[2];
} 
UINT	CHanaLaser::LaserOff()
{
// 	CString message;
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x02;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();
	
// 	message = GetMsgFromComm();
	
	return 1;// (UINT)message[2];
} 
UINT CHanaLaser::CurrentControl(double dCurrent) 
{
	m_dCurrent = dCurrent ; // double형인 Current 저장 (부모의 변수임)
	int wData = (double)dCurrent * 10;

	Msg[0] = 0x02;

	Msg[1] = 0x02;
	Msg[2] = (BYTE)LOBYTE((int)wData);;
	Msg[3] = (BYTE)HIBYTE((int)wData);;
	Msg[4] = 0x03;

	return SendMsgWait();
}

char *CHanaLaser::GetReceivedCurrent()
{

return ReadCurrent();
}

void CHanaLaser::SetMsgEnd(void)
{
	///////////하나레저에서는 사용 하지 않음 
/*
	int i;

	for(i = 1; i < 17; i++)
	{
		if( ( *(Msg+i) == NULL ) ) break;
	}
	*(Msg+i) = 0x0d;*/

}

BOOL CHanaLaser::GetIsConnect()
{
	return m_bIsConnect;
}

void CHanaLaser::SetIsReceived(int iReceived)
{
	isReceived = iReceived;
}

void CHanaLaser::SetIsBreak(int iBreak)
{
	m_iBreak = iBreak;
}

int CHanaLaser::SetLaserPower(char *power) // 4자 까지 
{
/*
	*(Msg) = 0x02;
	*(Msg+1) = 0x02;
	*(Msg+2) = (BYTE)LOBYTE(power);
	*(Msg+3) = (BYTE)HIBYTE(power);
	*(Msg+4) = 0x03;*/

	//AddStr(power);
	//SetMsgEnd();

	/*
	memset(sSend, 0, 5);
	sSend[0] = 0x02;
	sSend[1] = (BYTE)nCode;
	sSend[2] = (BYTE)LOBYTE(wData);
	sSend[3] = (BYTE)HIBYTE(wData);
	sSend[4] = 0x03;
	
	*/
	return SendMsgWait();
}

char *CHanaLaser::GetLaserPower()
{
	char *test = NULL;
	*(Msg) = 0x02;
	*(Msg+1) = 0x12;
	*(Msg+2) = 0xff;
	*(Msg+3) = 0xff;
	*(Msg+4) = 0x03;
	SendMsgWait();
  
	return test;// /**/GetMsgFromComm();	
}

double CHanaLaser::GetCurrent()
{
//	GetReceivedCurrent();
	return m_dCurrent;
}


BOOL CHanaLaser::SendData(int nCode, int nData)
{
	BYTE sSend[5]="";
	int nReceiveCode, nReceiveData, nStartByte;
	WORD wData = (WORD)nData;
	
	*(Msg) = 0x02;
	*(Msg+1) = (BYTE)nCode;
	*(Msg+2) = (BYTE)LOBYTE(wData);
	*(Msg+3) = (BYTE)HIBYTE(wData);
	*(Msg+4) = 0x03;
	SendMsgWait();
	//m_port.SendData(sSend, 5);

	
	char* sRXBuf = NULL;
	long nIter = 0;
	
	memset(sRXBuf, 0, 135);
	

	sRXBuf = GetMsgFromComm();
	
	nStartByte = (int)sRXBuf[0];
	nReceiveCode = (int)sRXBuf[1];
	nReceiveData = (int)sRXBuf[2]+(int)(sRXBuf[3]*256);
	
	BOOL bFault = TRUE;
	
	switch(nCode) 
	{
	case SET_MAX_CURRENT:
	case SET_ACT_CURRENT:
	case SET_MAX_FREQUENCY:
	case SET_ACT_FREQUENCY:
	case ON_OFF_COMMAND:
		break;
	case SET_PERIODIC_MONITOR_ON_OFF:
		if( nReceiveCode != SET_OK )
			bFault = TRUE;
		break;
	case CHECK_COM_CODE:
		if(nStartByte != 0x02)
		{
//				m_port.Close();
//				m_port.Open(nPortNum, 9600);
//				Sleep(300);
//				bFault = FALSE;
			

		}
		break;
	default:
		break;
	}
	
	if(!bFault)
		return FALSE;
	return TRUE;

}

BOOL CHanaLaser::ReadReportData() //사용 대기 아직 사용안함 
{

	*(Msg) = 0x02;
	*(Msg+1) = 0x40;
	*(Msg+2) = 0x01;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;

	SendMsgWait();

//	GetMsgFromCommAllData();


	return TRUE;
}
UINT	CHanaLaser::Internal_F()
{
/*	CString message;*/
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x07;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();

/*	message = GetMsgFromComm();*/
	
	return 1;//(UINT)message[2];
}
UINT	CHanaLaser::External_F()
{
/*	CString message;*/
	*(Msg+0) = 0x02;
	*(Msg+1) = 0x30;
	*(Msg+2) = 0x08;
	*(Msg+3) = 0x00;
	*(Msg+4) = 0x03;
	SendMsgWait();

/*
	message = GetMsgFromComm();
	*/

	return 1;//1(UINT)message[2];
}

void CHanaLaser::SetViewDlg(CDialog *pdlg)
{
 m_pDLG = pdlg;
}
CDialog *CHanaLaser::GetViewDlg()
{
 return m_pDLG;
}

void CHanaLaser::Save_Data_to_Memory()
{
//	*(Msg+0) = 0x02;
//	*(Msg+1) = 0x30;
//	*(Msg+2) = 0x08;
//	*(Msg+3) = 0x00;
//	*(Msg+4) = 0x03;
//	SendMsgWait();
}

char* CHanaLaser::ReadCurrent()
{
	char* hyy;
		CString message;
		Msg[0] = 0x02;
	Msg[1] = 0x11;
	Msg[2] = 0xff;
	Msg[3] = 0xff;
	Msg[4] = 0x03;
     SendMsgWait();
 	 hyy = GetMsgFromComm();
     return hyy;
}
CString CHanaLaser::GetMsgFromCommAllData()
{
	int i = 0;
	int j = 0;
	static char R_Msg[85];
	char PartData[17][5];
//	memset( (char *)R_Msg, 0x00, 80);
// strcpy(R_Msg,(char*)rcvBuf);

	

//PartData[1][1]  Laser Power
//PartData[2][1]  Arrary temp
//PartData[3][1]  Fet Voltage
////PartData[4][1]   Fet TEMP
 ////PartData[5][1]  falult data
////PartData[6][1]  Swithch data
////PartData[7][1]  Max xurrent
////PartData[8][1]  ACT Currernt
CString unit1= PartData[8][2] ;
CString unit2 = PartData[8][3];
//m_dCurrent = ((int)atoi(unit1) + (int)atoi(unit2)*256)/10;




////PartData[9][1] Max Frqency
////PartData[10][1] act Frqency
////PartData[11][1] elap hour
////PartData[12][1]  elap min
////PartData[13][1] fault override
////PartData[14][1] FPS data
////PartData[15][1] Low Frquency  Limit


/*
	switch(R_Msg[1]) 
	{
	case 0x06:
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
	case 0x4c:
		memset((char *)R_Msg, 0x00, 20);
		R_Msg[0] = 0x01;
			break;
	case 0x50:
		memset((char *)R_Msg, 0x00, 20);
		R_Msg[0] = 0x00;
		break;
	default :
		break;
     	
	}*/

	return (char *)rcvBuf;
	
}
void CHanaLaser::SetDelayTime(unsigned int iSecond)
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
BOOL    CHanaLaser::SetMaxCurrent(UINT MaxCurrnet)
{
		MaxCurrnet = MaxCurrnet ; // double형인 Current 저장 (부모의 변수임)
	int wData = (double)MaxCurrnet * 10;

	Msg[0] = 0x02;

	Msg[1] = 0x01;
	Msg[2] = (BYTE)LOBYTE((int)wData);
	Msg[3] = (BYTE)HIBYTE((int)wData);
	Msg[4] = 0x03;

	 SendMsgWait();
	 return true;
}

void CHanaLaser::SetCurrentVal(double current)
{
	m_dCurrent = current;
}
CString CHanaLaser::GetLaserUsedTime()
{
	return m_strNowUsedTime;
}
void CHanaLaser::SetLaserUsedTime(CString nowTime)
{
 m_strNowUsedTime = nowTime;
}