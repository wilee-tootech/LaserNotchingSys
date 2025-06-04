// FiberLaser.cpp: implementation of the CFiberLaser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "FiberLaser.h"
#include "RS232.h"
#include "LanSocket.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define AddStr(n) strcat(Msg , n ) 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFiberLaser::CFiberLaser(CWnd *pWnd)
{
	SetMsgNull();
	m_iBreak = 0;

	/* 다이로그에서 직접 초기화 대신 넘겨짐 */
	//m_pCommunicate = new CRS232("Laser Control", pWnd);
	//2019.01.04 jjsjong LaserControl Socket으로 변경
	m_pCommunicate = new CLanSocket("Laser Control", pWnd);
	if (m_pCommunicate->InitCommnicate() != -1) {
		//m_pCommunicate->StartCommunicate();
		m_bIsConnect = FALSE;

	}
	else
	{
		m_bIsConnect = TRUE;
	}

	/* 변수 초기화 필요 */
	m_bIsShutterOn = FALSE;
	m_iCurrent = 0;	// Current는 파일 로딩으로 읽어들였다고 가정

	// 통신 시작
	//if (m_pCommunicate->StartCommunicate() < 0)
	//	return;
	
	
}

CFiberLaser::~CFiberLaser()
{
	m_bIsConnect = FALSE;

	if(m_pCommunicate != NULL)
	{
		m_pCommunicate->StopCommunicate(); // 통신 종료
		delete m_pCommunicate;
	}
}

BOOL CFiberLaser::SetConfigComPort(int Boaud, int Parity, int stopbit)
{
	
	CString strport;
	*(Msg+0) = 'C';
	*(Msg+1) = 'F';
	//strcat(Msg, Boaud);
	*(Msg+2) = Boaud;
	*(Msg+3) = 8;
	*(Msg+4) = Parity;
	*(Msg+5) = stopbit;
	*(Msg+6) = 'H';
	*(Msg+7) = 0x0d;

	SetMsgEnd();
	SendMsgWait();


	static char Msg1[22]={0,};
	char *tmp;
	
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
	Msg1[i] = NULL;

	//if(Msg1 == "c") return FALSE;
	return TRUE;
}

int CFiberLaser::SetQsFrequency(char *frequency, int mode)
{
	char temp[10]={0,};

	AddStr("QF");
	AddStr(frequency);
	AddStr(" ");
	//itoa(mode, temp, 10);
	AddStr(temp);

	SetMsgEnd();
	
	return SendMsgWait();
}

char *CFiberLaser::GetTemperature()
{
	static char Msg1[22]={0,};
	
	*(Msg+0) = 'T';
	*(Msg+1) = 'P';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	if( !SendMsgWait() ) return NULL;
//	GetMsgFromComm();
/*	tmp = GetMsgFromComm();
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
	Msg1[i] = NULL;
	*/
	return m_Temp;
}


char *CFiberLaser::GetLampCurrent()
{
	static char Msg1[22]={0,};
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
	Msg1[i] = NULL;
	
	return Msg1;
}

char *CFiberLaser::GetStatus()
{
	*(Msg+0) = 'S';
	*(Msg+1) = 'S';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	*(Msg+4) = NULL;
	SendMsgWait();
	
	return NULL;//GetMsgFromComm();
}

char *CFiberLaser::GetInterLockMessage()
{
	*(Msg+0) = 'I';
	*(Msg+1) = 'L';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	SendMsgWait();
	
	return NULL;//GetMsgFromComm();
}

int CFiberLaser::SendMsgWait(void)
{
	int result;
	
	result = SendDataToPort();
	
	/*if( result )
	{
		if( !WaitForResponse(500) ) return NULL;
		Sleep(10);
		if ( *(m_pCommunicate->ReadData()) == NULL ) return NULL; // RS232 buff에 직접 접근하는 대신 이용
	}
	*/
	return result;
}

char *CFiberLaser::GetMsgFromComm()
{

	int i =0;
	int j= 0;
	static char R_Msg[22];
	memset( (char *)R_Msg, 0x00, 20);
	char *tmp;
	if( !WaitForResponse(500) ) return NULL;
	
	do
	{
		
		if( R_Msg[i] = *(m_pCommunicate->ReadData()+i)/*rs.m_buff[i]*/ ){
			i++;
			continue;
		}
		else break;

		
	} while (i < 19);

	tmp = R_Msg;
//--------------------------------------------------------------------------------
	i=0;
	if(tmp[0] == 'L' && tmp[1] == 'C')
	{
		tmp+=2;
		
		while ( tmp )
		{
			if( *tmp <='9' && *tmp >='0')
			{
				R_Msg[i] = *tmp;
				i++;
			}
			tmp ++;
			j++;
			if( j >20 ) break;
		}
		R_Msg[i] = NULL;
		m_Current = R_Msg;
	}
	else if(tmp[0] == 'T' && tmp[1] == 'P')
	{
		while ( tmp )
		{
			if( *tmp <='9' && *tmp >='0')
			{
				R_Msg[i] = *tmp;
				i++;
			}
			tmp ++;
			j++;
			if( j >20 ) break;
		}
		R_Msg[i] = NULL;
		m_Temp = R_Msg;
	}
	
	
//--------------------------------------------------------------------------------
	return R_Msg;
	
}

/* 실제 Data를 포트에 써주는 놈. SendMsg와 동일*/
BOOL CFiberLaser::SendDataToPort(CString msg)
{
	int writecount;
	char buf[1024];
	CString CR = "";
	CR.Format("%c", 0x0D);
	msg += CR;
	msg += "\0";
	strcpy(buf, msg);

	writecount = m_pCommunicate->WriteData((BYTE *)buf, msg.GetLength());
	
	if (writecount <= 0)
	{
//		AfxMessageBox("Fail to Write",MB_OK);
		return FALSE;
	}

	//SetMsgNull();

	return TRUE;
}

/* 실제 Data를 포트에 써주는 놈. SendMsg와 동일*/
BOOL CFiberLaser::SendDataToPort()
{
	int writecount;

	writecount = m_pCommunicate->WriteData((BYTE *)Msg , strlen(Msg)); // 실제 보내는 함수
	
	if (writecount <= 0)
	{
		return FALSE;
	}

	SetMsgNull();

	return TRUE;
}

int CFiberLaser::WaitForResponse(unsigned int wait)
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

void CFiberLaser::SetMsgNull(void) //이것은 Private 인게 좋겠다.
{
	int i=MSG_SIZE-1;
	
	do
	{
		Msg[i--]=0x00;
	} while (i>=0);
}

/* 지금은 사용되지 않음 */ 
UINT CFiberLaser::ShutterOn() 
{
	strcpy(Msg, "SM01");
	SetMsgEnd();
	return SendDataToPort();
}

UINT CFiberLaser::ShutterOff() 
{
	strcpy(Msg, "SM00");
	SetMsgEnd();
	return SendDataToPort();
}

UINT CFiberLaser::CurrentControl(double dCurrent) 
{
//	dCurrent = (0xFF / 100.0) * dCurrent;	
	// 환산하면 100이 0xFE로 되므로
//	if (dCurrent == 0xFE) dCurrent = 0xFF;
	
	Msg[0] = 'P';
	Msg[1] = (BYTE)dCurrent;
	
/*
	m_dCurrent = dCurrent / 10; // double형인 Current 저장 (부모의 변수임)
	char* current;

	//SetMsgNull();
	CString tempCurrent;
	Msg[0] = 'L';
	Msg[1] = 'C';
	tempCurrent.Format("%d", int(dCurrent));
	current = (char *) (LPCTSTR) tempCurrent;
	strcat(Msg, current);
*/	
	SetMsgEnd();

	return SendMsgWait();
}

char *CFiberLaser::GetReceivedCurrent()
{
	static char Msg1[22] = {0,};

	int i =0;
	int j= 0;
	
	*(Msg+0) = 'L';
	*(Msg+1) = 'C';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	if( !SendMsgWait() ) return NULL;
	m_Current = NULL;
	//GetMsgFromComm();

	
	
/*
	if(tmp[0] == 'L' && tmp[1] == 'C')
	{
	tmp+=2;
	
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
	}
	Msg1[i] = NULL;
	*/
	return m_Current ;
}

void CFiberLaser::SetMsgEnd(void)
{
	int i;

	for(i = 1; i < 17; i++)
	{
		if( ( *(Msg+i) == NULL ) ) break;
	}
//	*(Msg+i) = 0x0d;
}

BOOL CFiberLaser::GetIsConnect()
{
	m_bIsConnect = m_pCommunicate->GetIsConnect();
	return m_bIsConnect;
}

void CFiberLaser::SetIsReceived(int iReceived)
{
	isReceived = iReceived;
}

void CFiberLaser::SetIsBreak(int iBreak)
{
	m_iBreak = iBreak;
}

int CFiberLaser::SetLaserPower(char *power) // 4자 까지 
{
	*(Msg) = 'L';
	*(Msg+1) = 'P';
	AddStr(power);
	SetMsgEnd();

	return SendMsgWait();
}

char *CFiberLaser::GetLaserPower()
{
	*(Msg) = 'L';
	*(Msg+1) = 'P';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	SendMsgWait();

	return GetMsgFromComm();	
}

double CFiberLaser::GetCurrent()
{
	return m_dCurrent;
}


void CFiberLaser::SetShutter(BOOL m_shutter)
{
	m_bIsShutterOn  = m_shutter;
}

BOOL CFiberLaser::GetShutter()
{
	return m_bIsShutterOn;
}

int CFiberLaser::StartCommunicate(void)
{
	//m_pCommunicate->InitCommnicate();
	if (m_pCommunicate->InitCommnicate() != -1)
	{
		m_pCommunicate->StartCommunicate();
	}
	
	return 0;
}
