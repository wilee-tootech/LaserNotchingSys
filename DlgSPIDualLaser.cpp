// DlgSPIDualLaser.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgSPIDualLaser.h"
#include "afxdialogex.h"
#include "Control\ctcheck.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "NX_KEYPAD\AlphaKeyPad.h"
#include "MainFrm.h"
#include "UserCheck.h"
#include "WriteLog.h"
#include "Control\ctpush.h"
#include "define.h"
#include "PointerContainer.h"
#include "./Include/EXTERN/FileMgr.h"




void CSPILaserTruePulseNanoEthernet::OnReceive(int nErrorCode)
{
	TCHAR buff[MAX_BUFFER+1];
	//memset(buff,NULL,MAX_BUFFER+1);
	int size = this->Receive(buff, MAX_BUFFER);

	switch (size) {
	case 0:
		{
			m_bIsOverReadbuff = FALSE;
			Close();
			m_bIsConnect = FALSE;
		}
		break;

	case SOCKET_ERROR:
		{
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				AfxMessageBox ("Error occurred");
				m_bIsOverReadbuff = FALSE;
				Close();
				m_bIsConnect = FALSE;
			}
		}
		break;

	default:
		{
			buff[size] = '\0';

			if (m_bIsOverReadbuff) {
				CString strTmp = _T("");
				strTmp.Format("%s", m_strReadData);
				m_strReadData.Format("%s%s", strTmp, buff);
			} else {
				memset(m_byteBuffer,NULL,MAX_BUFFER+1);
				memcpy(m_byteBuffer,buff,size);
				m_strReadData.Format("%s", buff);
			}
			m_bIsConnect = TRUE;

			//m_HEAD1LaserLog.AddString(_T("HEAD1 Laser Connect Success"));
			//pMainFrm->AddLogData("HEAD1 Laser Connect Success...");


			if (MAX_BUFFER == size) {
				m_bIsOverReadbuff = TRUE;
			} else {
				m_bIsOverReadbuff = FALSE;
				//2022.12.07 TEST

				if(m_strOwner == "LaserHEAD2")
					m_pOwner->SendMessage(WM_SOCK_RECEIVE,WPARAM(m_nPortNum), LPARAM(HEAD2_SOCKET) );
				else
					m_pOwner->SendMessage(WM_SOCK_RECEIVE,WPARAM(m_nPortNum), LPARAM(HEAD1_SOCKET) );

				//m_pOwner->SendMessage(WM_SOCK_RECEIVE,WPARAM(m_nPortNum));
				//m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.


			}
		}
	}

	if (m_bMode == MODE_CLIENT)
		CSocket::OnReceive(nErrorCode);
	else
		CAsyncSocket::OnReceive(nErrorCode);
}

char* CSPILaserTruePulseNanoEthernet::ReadData()
{
	if (m_bMode == MODE_SERVER) {
		//return LPSTR(LPCTSTR(m_pAcceptSock->m_strReadData));
		return (char*)m_byteBuffer;
	}
	else if (m_bMode == MODE_CLIENT) {
		//return LPSTR(LPCTSTR(this->m_strReadData));
		return (char*)m_byteBuffer;
	}
	else {
		return NULL;
	}


	return NULL;
}

UINT CSPILaserTruePulseNanoEthernet::WriteData(BYTE *SendString, DWORD Stringlength)
{
	char chSendMsg[1024] = {_T(""),};
	int nCheck = -1;

	//int nBufLen = strlen((LPSTR)SendString);
	memcpy(chSendMsg, SendString, (sizeof(char) * Stringlength) + 1);

	if (m_bMode == MODE_CLIENT) {
		nCheck = this->Send(SendString, Stringlength);
	}

	if (m_bMode == MODE_SERVER) {
		if (m_pAcceptSock != NULL) {
			nCheck = m_pAcceptSock->Send(SendString, strlen(chSendMsg));
		}
		else
			return -1;
	}
	return nCheck;
}

int CSPILaserTruePulseNanoEthernet::GetPortNum()
{
	return m_nPortNum;
}


CString CSPILaserTruePulseNanoEthernet::GetIPAddress()
{
	return m_strIPAddress;
}


// CDlgSPIDualLaser 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgSPIDualLaser, CDialogEx)

CDlgSPIDualLaser::CDlgSPIDualLaser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSPIDualLaser::IDD, pParent)
{
	//m_HEAD2LaserIP = _T("169.254.168.203");
	/*
	m_HEAD1LaserIP = _T("169.254.190.203");
	m_HEAD1LaserPort = 58174;

	m_HEAD2LaserIP = _T("169.254.168.203");
	m_HEAD2LaserPort = 58174;
	*/

	 m_HEAD1LaserIP = _T("127.0.0.1");
	 m_HEAD1LaserPort = 5100;

	 m_HEAD2LaserIP = _T("192.168.0.50");
	 m_HEAD2LaserPort = 5200;


	 bHEAD1Connect = FALSE;
	 bHEAD2Connect = FALSE;

	 bHEAD1DataRcvFlag = FALSE;
	 bHEAD2DataRcvFlag = FALSE;
	
	m_pSPILaserHEAD1 = new CSPILaserTruePulseNanoEthernet("LaserHEAD1",this);

	m_pSPILaserHEAD2 = new CSPILaserTruePulseNanoEthernet("LaserHEAD2",this);

	isGuideBeamHEAD2 = false;
	isGuideBeamHEAD1 = false;

	
	
	
}

CDlgSPIDualLaser::~CDlgSPIDualLaser()
{
}

void CDlgSPIDualLaser::UINT32ToByteArray(UINT32 intData,BYTE* byteArr)
{
	byteArr[0] = ((intData & 0xff000000) >> 24); 
	byteArr[1] = ((intData & 0x00ff0000) >> 16);
	byteArr[2] = ((intData & 0x0000ff00) >> 8);
	byteArr[3] = (intData & 0x000000ff);
}

void CDlgSPIDualLaser::UINT16ToByteArray(UINT16 intData,BYTE* byteArr)
{
	byteArr[0] = ((intData & 0x0000ff00) >> 8);
	byteArr[1] = (intData & 0x000000ff);
}

UINT32 CDlgSPIDualLaser::ByteArrayToUINT32(BYTE* byteArr)
{
	UINT32 value = 0;


	int a = byteArr[0];
	int b = byteArr[1];
	int c = byteArr[2];
	int d = byteArr[3];

	UINT32 uppestByte = byteArr[0] << 24;
	UINT32 upperByte = byteArr[1] << 16;
	UINT32 lowerByte = byteArr[2] << 8;
	UINT32 lowertByte = byteArr[3];
	value = uppestByte + upperByte + lowerByte + lowertByte;
	return value;
}

UINT16 CDlgSPIDualLaser::ByteArrayToUINT16(BYTE* byteArr)
{
	UINT16 value = 0;
	
	UINT16 upperByte = byteArr[0] << 8;
	UINT16 lowertByte = byteArr[1];
	value = upperByte + lowertByte;
	return value;

}

void CDlgSPIDualLaser::SetCheckSum(BYTE* packet, const int arrayLength)
{
	for(int i=0;i<arrayLength - 1; ++i)
	{
		packet[arrayLength - 1] += packet[i];
	}
}


int CDlgSPIDualLaser::SetRs232BaudRate(UINT32 baudrate,CCommunicate* pSocket)
{

	int nCheck = -1;
	const int arrayLength = 10;
	BYTE packetArr[arrayLength];
	BYTE baudrateArr[4];

	UINT32ToByteArray(baudrate,baudrateArr);


	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = sizeof(baudrate) + 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetRS232BaudRate;
	packetArr[4] = baudrateArr[0];
	packetArr[5] = baudrateArr[1];
	packetArr[6] = baudrateArr[2];
	packetArr[7] = baudrateArr[3];
	packetArr[8] = SPI_PACKET_STOP_BYTE;
	packetArr[9] = 0;


	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
    return nCheck;
}


int CDlgSPIDualLaser::GetRS232BaudRate(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetRS232BaudRate;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::SetLaserInterfaceControlMode(UCHAR mode,CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 7;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(mode);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetLaserInterfaceControlMode;
	packetArr[4] = mode;
	packetArr[5] = SPI_PACKET_STOP_BYTE;
	packetArr[6] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;

	
}


int CDlgSPIDualLaser::GetLaserInterfaceControlMode(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserInterfaceControlMode;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}




int CDlgSPIDualLaser::SetLaserControlSignals(UINT16 state,CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE stateArr[2];
	UINT16ToByteArray(state,stateArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(state);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetLaserControlSignals;
	packetArr[4] = stateArr[0];
	packetArr[5] = stateArr[1];
	packetArr[6] = SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::GetLaserControlSignals(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserControlSignals;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	
	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::SetAnalogueCurrentSetPoint(UINT16 point,UINT16 value,CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 10;
	BYTE packetArr[arrayLength] = {0};

	BYTE pointArr[2];
	BYTE valueArr[2];
	UINT16ToByteArray(point,pointArr);
	UINT16ToByteArray(value,valueArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(point) + sizeof(value);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetAnalogueCurrentSetPoint;
	packetArr[4] = pointArr[0];
	packetArr[5] = pointArr[1];
	packetArr[6] = valueArr[0];
	packetArr[7] = valueArr[1];
	packetArr[8] =	SPI_PACKET_STOP_BYTE;
	packetArr[9] = 0;

	SetCheckSum(packetArr,arrayLength);
	
	//socket.WriteData(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
	
}

int CDlgSPIDualLaser::GetAnalogueSignals(UINT16 point,CCommunicate* pSocket)
{


	
	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE pointArr[2];
	UINT16ToByteArray(point,pointArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(point) ;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetAnalogueSignals;
	packetArr[4] = pointArr[0];
	packetArr[5] = pointArr[1];
	packetArr[6] =	SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	
	SetCheckSum(packetArr,arrayLength);

	
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;

}


int CDlgSPIDualLaser::SetPulseWaveform(UINT16 pulseWaveform,CCommunicate* pSocket)
{
	

	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE pulseWaveformArr[2];
	UINT16ToByteArray(pulseWaveform,pulseWaveformArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(pulseWaveform) ;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetPulseWaveform;
	packetArr[4] = pulseWaveformArr[0];
	packetArr[5] = pulseWaveformArr[1];
	packetArr[6] =	SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::GetPulseWaveform(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetPulseWaveform;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);

	//socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::SetPulseRate(UINT32 rate,CCommunicate* pSocket)
{

	int nCheck = -1;
	const int arrayLength = 10;
	BYTE packetArr[arrayLength] = {};

	BYTE rateArr[sizeof(rate)];

	UINT32ToByteArray(rate,rateArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(rate);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetPulseRate;
	packetArr[4] = rateArr[0];
	packetArr[5] = rateArr[1];
	packetArr[6] = rateArr[2];
	packetArr[7] = rateArr[3];
	packetArr[8] =	SPI_PACKET_STOP_BYTE;
	packetArr[9] = 0;

	SetCheckSum(packetArr,arrayLength);

	//socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::GetPulseRate(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetPulseRate;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;

	SetCheckSum(packetArr,arrayLength);
	

	//socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::SetPulseBurstLength(UINT32 burstLength,CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 10;
	BYTE packetArr[arrayLength] = {};

	BYTE burstArr[4];

	UINT32ToByteArray(burstLength,burstArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(burstLength);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetPulseBurstLength;
	packetArr[4] = burstArr[0];
	packetArr[5] = burstArr[1];
	packetArr[6] = burstArr[2];
	packetArr[7] = burstArr[3];
	packetArr[8] =	SPI_PACKET_STOP_BYTE;
	packetArr[9] = 0;


	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;

}

int CDlgSPIDualLaser::GetPulseBurstLength(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetPulseBrustLength;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;

	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;

}

int CDlgSPIDualLaser::SetPumpDutyFactor(UINT16 dutyFactor,CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE dutyFactorArr[sizeof(dutyFactor)];

	UINT16ToByteArray(dutyFactor,dutyFactorArr);
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(dutyFactor);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetPumpDutyFactor;
	packetArr[4] = dutyFactorArr[0];
	packetArr[5] = dutyFactorArr[1];
	packetArr[6] =	SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
	
}


int CDlgSPIDualLaser::GetPumpDutyFactor(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetPumpDutyFactor;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	

	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::SetAllPulseGeneratorParameters(UINT16 waveform,UINT32 rate, UINT32 burstLength, UINT16 dutyFactor,CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 18;
	BYTE packetArr[arrayLength] = {};

	BYTE waveformArr[2];
	BYTE rateArr[4];
	BYTE burstLengthArr[4];
	BYTE dutyFactorArr[2];

	UINT16ToByteArray(waveform,waveformArr);
	UINT32ToByteArray(rate,rateArr);
	UINT32ToByteArray(burstLength,burstLengthArr);
	UINT16ToByteArray(dutyFactor,dutyFactorArr);




	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(waveform) + sizeof(rate) + sizeof(burstLength) + sizeof(dutyFactor);
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetAllPulseGeneratorParameters;
	packetArr[4] = waveformArr[0];
	packetArr[5] = waveformArr[1];
	packetArr[6] = rateArr[0];
	packetArr[7] = rateArr[1];
	packetArr[8] = rateArr[2];
	packetArr[9] = rateArr[3];
	packetArr[10] = burstLengthArr[0];
	packetArr[11] = burstLengthArr[1];
	packetArr[12] = burstLengthArr[2];
	packetArr[13] = burstLengthArr[3];
	packetArr[14] = dutyFactorArr[0];
	packetArr[15] = dutyFactorArr[1];
	packetArr[16] =	SPI_PACKET_STOP_BYTE;
	packetArr[17] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);

	return nCheck;
	
}




int CDlgSPIDualLaser::GetAllPulseGeneratorParameters(UINT16 waveform,CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE waveformArr[sizeof(waveform)];
	UINT16ToByteArray(waveform,waveformArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(waveform) ;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetAllPulseGeneratorParameters;
	packetArr[4] = waveformArr[0];
	packetArr[5] = waveformArr[1];
	packetArr[6] = SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::RestartPulseGenerator(UINT16 waveform,CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 8;
	BYTE packetArr[arrayLength] = {};

	BYTE waveformArr[sizeof(waveform)];
	UINT16ToByteArray(waveform,waveformArr);

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2 + sizeof(waveform) ;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::RestartPulseGenerator;
	packetArr[4] = waveformArr[0];
	packetArr[5] = waveformArr[1];
	packetArr[6] = SPI_PACKET_STOP_BYTE;
	packetArr[7] = 0;

	SetCheckSum(packetArr,arrayLength);


	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::QueryStatusLinesAndAlarms(CCommunicate* pSocket)
{
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	int nCheck = -1;

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryStatusLinesAndAlarms;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::QueryLaserTemperatures(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};


	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryLaserTemperatures;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;

	SetCheckSum(packetArr,arrayLength);
	
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::QueryLaserCurrents(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryLaserCurrents;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;

}

int  CDlgSPIDualLaser::QueryPowerSupplyVoltages(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryPowerSupplyVoltages;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
	
}

int CDlgSPIDualLaser::QueryHardwareInterface(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};


	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryHardwareInterface;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);


	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::QueryOperatingHours(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryOperatingHours;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
	
}


int CDlgSPIDualLaser::QueryExternalPulseTriggerRepetitionRate(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};

	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryExternalPulseTriggerRepetitionRate;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	

	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::QueryExtendedLaserCurrents(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::QueryExtendedLaserCurrents;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}


int CDlgSPIDualLaser::SetLaserIntoDiagnosisState(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::SetLaserIntoDiagnosisState;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::GetLaserSerialNumber(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserSerialNumber;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;

	SetCheckSum(packetArr,arrayLength);

	nCheck = pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::GetLaserPartNumber(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserPartNumber;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);

	pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::GetLaserFirmwareDetails(CCommunicate* pSocket)
{
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserFirmwareDetails;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);

	pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}

int CDlgSPIDualLaser::GetLaserDescription(CCommunicate* pSocket)
{
	
	int nCheck = -1;
	const int arrayLength = 6;
	BYTE packetArr[arrayLength] = {};
	packetArr[0] = SPI_PACKET_START_BYTE;
	packetArr[1] = 2;
	packetArr[2] = SPI_COMMAND_START_BYTE;
	packetArr[3] = SPILaserCommandByte::GetLaserDescription;
	packetArr[4] =	SPI_PACKET_STOP_BYTE;
	packetArr[5] = 0;
	
	SetCheckSum(packetArr,arrayLength);
	pSocket->WriteData(packetArr,arrayLength);
	return nCheck;
}



void CDlgSPIDualLaser::ParseHEAD2Data(BYTE* pData,SPIData& spiData)
{
	CDsp *pDsp = CDsp::GetInstance();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//////////////////테스트용.. 나중에 지우세요 
	int ndatasize = 0;

	ndatasize = sizeof(pData);
	ndatasize = MAX_BUFFER;

	int nonNullDataSize = 0;

	for (int i = 0; i < MAX_BUFFER; i++) {
		if (pData[i] != NULL) {
			nonNullDataSize++;
		}
	}


	CString str(reinterpret_cast<const char*>(pData), nonNullDataSize);
	m_HEAD2LaserLog.AddString(str);

	//bHEAD1DataRcvFlag = TRUE;

	//BYTE arr[100] = {};

	//for(int i=0;i<30;++i)
	//{
		//arr[i] = pData[i];
	//}
	//////////////////

	BOOL bitFlag = FALSE;

	if(pData[SPI_RECEIVE_PACKET_RESPONSE_VALUE_POS] != 0x09)
	{
		return;
	}
	
	CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_RX);
	p->SetChecked(TRUE);

	switch(pData[SPI_RECEIVE_PACKET_LASER_COMMAND_POS])
	{
		case SPILaserCommandByte::SetRS232BaudRate:
			break;

		case SPILaserCommandByte::QueryStatusLinesAndAlarms:
			{
				UINT32 status = ByteArrayToUINT16(&pData[5]);
				
				//2022.11.23 추가
				UINT32 status2 = ByteArrayToUINT16(&pData[6]);
				int nAlarmCode = status2;

				CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_POWER_SUPPLY_FAULT);
				if(nAlarmCode == ALARM_CODE_LASER_POWER_SUPPLY) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT);	
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_FAN_FAULT);
				if(nAlarmCode == ALARM_CODE_LASER_FAN) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_FAN_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_FAN_FAULT);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_EMERGENCY_STOP);
				if(nAlarmCode == ALARM_CODE_LASER_EMERGENCY_STOP) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_EMERGENCY_STOP_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_EMERGENCY_STOP_FAULT);	
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_TASK_ACTIVE);
				p->SetChecked(status >> 11 & 1);

				if( (status >> 11 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_TASK_ACTIVE = 1;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_TASK_ACTIVE = 1;
				


				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_CW);
				p->SetChecked(status >> 10 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ON);
				p->SetChecked(status >> 9 & 1);
				if( (status >> 9 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ON = 1;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ON = 0;


				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ENABLE);
				p->SetChecked(status >> 8 & 1);
				if( (status >> 8 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ENBLED= 1;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ENBLED = 0;


				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ON);
				p->SetChecked(status >> 7 & 1);
				if( (status >> 7 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ON= 1;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ON = 0;

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_EMISSION);
				p->SetChecked(status >> 6 & 1);
				if( (status >> 6 & 1 ) == 1)
				{
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_EMISSION= 1;
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_EMISSIONS_GATE = 1;
				}
				else
				{
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_EMISSION = 0;
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_EMISSIONS_GATE = 0;
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_DISABLE);
				bitFlag = (status >> 5) & 1;
				p->SetChecked(!bitFlag);
				if( (status >> 5 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_DISABLED= 0;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_DISABLED = 1;

				//p->SetChecked(status >> 5 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_SYSTEM);
				bitFlag = (status >> 4) & 1;

				if( (status >> 4 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_SYSTEM_FAULT= 0;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_SYSTEM_FAULT = 1;

				p->SetChecked(!bitFlag);
				if(bitFlag!= 1)
				{
					//CPointerContainer::GetInformationView()->
					//CInformationView* a = CPointerContainer::GetInformationView();
					//a->OnStopMark();
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_SYSTEM_FAULT_ALARM);

				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_SYSTEM_FAULT_ALARM);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_BEAM_DELIVERY_TEMP);
				bitFlag = (status >> 3) & 1;
				p->SetChecked(!bitFlag);
				
				//p->SetChecked(status >> 3 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_BODY_TEMP);
				bitFlag = (status >> 2) & 1;
				p->SetChecked(!bitFlag);

				if(bitFlag!= 1)
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_TEMP_ALARM);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_TEMP_ALARM);
				}
				//p->SetChecked(status >> 2 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_ALARM);
				bitFlag = (status >> 1) & 1;
				p->SetChecked(!bitFlag);
				if( (status >> 1 & 1 ) == 1)
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ALARM= 0;
				else
					m_LaserHEAD2StatusToSend.bHEAD2_LASER_ALARM = 1;
				//p->SetChecked(status >> 1 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_MONITOR);
				bitFlag = status  & 1;
				//p->SetChecked(status  & 1);
				p->SetChecked(!bitFlag);
			}
			break;


		case SPILaserCommandByte::GetAnalogueSignals:
			{
				int active = ByteArrayToUINT16(&pData[7]);
				spiData.activeCurrent = active;
				double tempActiveCurrent =  m_spiDataHEAD2.activeCurrent / 10.0;
				m_LaserHEAD2StatusToSend.dHEAD2_LASER_ACTIVE_POWER = tempActiveCurrent;
			}

			break;

		case SPILaserCommandByte::GetPulseWaveform:
			{
				int pulseWaveform = ByteArrayToUINT16(&pData[5]);
				spiData.waveForm = pulseWaveform;
			}
			break;
		case SPILaserCommandByte::GetLaserInterfaceControlMode:
			{
				UCHAR ctrlMode = pData[5];
				spiData.laserControlMode = ctrlMode;
			}

			break;

		case SPILaserCommandByte::GetPulseRate:
			{
				UINT32 pulseRate = ByteArrayToUINT32(&pData[5]);
				spiData.pulseRate = pulseRate;
				m_LaserHEAD2StatusToSend.dHEAD2_LASER_PULSE_RATE = pulseRate;
			}

		case SPILaserCommandByte::GetLaserControlSignals:
			{
				BYTE laserSignals = pData[5];
				spiData.laserControlSignals = laserSignals;

				/*if(m_spiDataHEAD2.laserControlSignals == 0)
				{
					CctPush* HEAD2GuideButton = (CctPush*)GetDlgItem(IDC_CTPUSH_GUIDE_BEAM);
					HEAD2GuideButton->SetForeColor(0);
				}

				else
				{
					CctPush* HEAD2GuideButton = (CctPush*)GetDlgItem(IDC_CTPUSH_GUIDE_BEAM);
					HEAD2GuideButton->SetForeColor(0xFF0000);
				}*/

			}

			break;


		case SPILaserCommandByte::QueryLaserTemperatures:
			{
				UINT16 laserTemperature = ByteArrayToUINT16(&pData[5]);
				double dRealTemp = (35800.0 - laserTemperature)/100.0;
				dRealTemp = 85 - dRealTemp;
				spiData.laserTemperature = dRealTemp;
				//spiData.laserTemperature = laserTemperature;
				CString strTemp;
				strTemp.Format("Laser Temperature: %04.2f", dRealTemp);
				SetDlgItemText(IDC_CTTEXTCTRL_LASERTEMP_HEAD2, strTemp);
				m_LaserHEAD2StatusToSend.dHEAD2_LASER_BEAM_DELIVERLY_TEMP = atof(strTemp);

				laserTemperature = ByteArrayToUINT16(&pData[7]);
				dRealTemp = (35800.0 - laserTemperature)/100.0;
				dRealTemp = 85 - dRealTemp;
				spiData.laserTemperature = dRealTemp;
				strTemp.Format("BDO Temperature: %.2f", dRealTemp);
				SetDlgItemText(IDC_CTTEXTCTRL_BDOTEMP_HEAD2, strTemp);
				m_LaserHEAD2StatusToSend.dHEAD2_LASER_BODY_TEMP = atof(strTemp);


			}

			break;

		case SPILaserCommandByte::QueryPowerSupplyVoltages:
			{
				UINT16 PSU_Voltages = ByteArrayToUINT16(&pData[5]);
				UINT16 PSU_Voltages2 = ByteArrayToUINT16(&pData[7]);
				
				double dRealVoltages = PSU_Voltages / 1000.0;
				spiData.logicPowerSupply = dRealVoltages;
				CString strTemp;
				strTemp.Format("Logic PSU Voltages: %.3f", dRealVoltages);
				SetDlgItemText(IDC_CTTEXTCTRL_PSU_VOLTAGE_HEAD2, strTemp);

				dRealVoltages = PSU_Voltages2 / 1000.0;
				//spiData.diodePowerSupply = dRealVoltages;
				m_LaserHEAD2StatusToSend.dHEAD2_LASER_ACTIVE_MV = dRealVoltages;
				
				strTemp.Format("Amp PSU Voltages: %.3f", dRealVoltages);
				SetDlgItemText(IDC_CTTEXTCTRL_AMP_PSU_VOLTAGE_HEAD2, strTemp);

			}

			break;

		case SPILaserCommandByte::QueryExtendedLaserCurrents:
			{
				UINT16 PreAmpCurrent = ByteArrayToUINT16(&pData[5]);
				UINT16 MainAmpCurrent = ByteArrayToUINT16(&pData[7]);

				CString strTemp;
				strTemp.Format("PreAmp Current: %d(mA)", PreAmpCurrent);
				SetDlgItemText(IDC_CTTEXTCTRL_PRE_AMP_HEAD2, strTemp);

				strTemp.Format("Main Cuttent: %d(mA)", MainAmpCurrent);
				SetDlgItemText(IDC_CTTEXTCTRL_MAIN_AMP_HEAD2, strTemp);
			}

			break;
			
	}

	
	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetLaserStatusHEAD2(m_LaserHEAD2StatusToSend);

	p->SetChecked(FALSE);

}

void CDlgSPIDualLaser::ParseHEAD1Data(BYTE* pData,SPIData& spiData)
{
	CDsp *pDsp = CDsp::GetInstance();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	int ndatasize = 0;

	ndatasize = sizeof(pData);
	ndatasize = MAX_BUFFER;

	int nonNullDataSize = 0;

	for (int i = 0; i < MAX_BUFFER; i++) {
		if (pData[i] != NULL) {
			nonNullDataSize++;
		}
	}


	CString str(reinterpret_cast<const char*>(pData), nonNullDataSize);
	m_HEAD1LaserLog.AddString(str);

	if(pData[SPI_RECEIVE_PACKET_RESPONSE_VALUE_POS] != 0x09)
	{
		return;
	}
	
	CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_RX);
	p->SetChecked(TRUE);
	
	BOOL bitFlag = FALSE;

	switch(pData[SPI_RECEIVE_PACKET_LASER_COMMAND_POS])
	{
		case SPILaserCommandByte::SetRS232BaudRate:
			break;

		case SPILaserCommandByte::QueryStatusLinesAndAlarms:
			{
				UINT32 status = ByteArrayToUINT16(&pData[5]);
				//2022.11.23 추가
				UINT32 status2 = ByteArrayToUINT16(&pData[6]);
				int nAlarmCode = status2;

				CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_POWER_SUPPLY_FAULT);
				if(nAlarmCode == ALARM_CODE_LASER_POWER_SUPPLY) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_FAN_FAULT);
				if(nAlarmCode == ALARM_CODE_LASER_FAN) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_FAN_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_FAN_FAULT);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_EMERGENCY_STOP);
				if(nAlarmCode == ALARM_CODE_LASER_EMERGENCY_STOP) 
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_EMERGENCY_STOP_FAULT);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_EMERGENCY_STOP_FAULT);
				}

				/*CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_POWER_SUPPLY_FAULT);
				bitFlag = (status >> 15) & 1;
				p->SetChecked(!bitFlag);
				if(bitFlag!= 1)
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT_ALARM);			
				}
				else
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);

				CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_FAN_FAULT);
				bitFlag = (status >> 15) & 1;
				p->SetChecked(!bitFlag);
				if(bitFlag!= 1)
				{
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_POWER_SUPPLY_FAULT_ALARM);			
				}
				else
					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_TASK_ACTIVE);
				p->SetChecked(status >> 11 & 1);
				if( (status >> 11 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_TASK_ACTIVE = 1;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_TASK_ACTIVE = 1;
				

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_CW);
				p->SetChecked(status >> 10 & 1);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ON);
				p->SetChecked(status >> 9 & 1);
				if( (status >> 9 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ON = 1;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ON = 0;


				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ENABLE);
				p->SetChecked(status >> 8 & 1);
				if( (status >> 8 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ENBLED= 1;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ENBLED = 0;

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ON);
				p->SetChecked(status >> 7 & 1);
				if( (status >> 7 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ON= 1;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ON = 0;

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_EMISSION);
				p->SetChecked(status >> 6 & 1);
				if( (status >> 6 & 1 ) == 1)
				{
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_EMISSION= 1;
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_EMISSIONS_GATE = 1;
				}
				else
				{
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_EMISSION = 0;
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_EMISSIONS_GATE = 0;
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_DISABLE);
				bitFlag = (status >> 5) & 1;
				if( (status >> 5 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_DISABLED= 0;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_DISABLED = 1;
				p->SetChecked(!bitFlag);
				
				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_SYSTEM);
				bitFlag = (status >> 4) & 1;
				if( (status >> 4 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_SYSTEM_FAULT= 0;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_SYSTEM_FAULT = 1;
				p->SetChecked(!bitFlag);
				if(bitFlag!= 1)
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_SYSTEM_FAULT_ALARM);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_SYSTEM_FAULT_ALARM);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_BEAM_DELIVERY_TEMP);
				bitFlag = (status >> 3) & 1;
				p->SetChecked(!bitFlag);

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_BODY_TEMP);
				bitFlag = (status >> 2) & 1;
				p->SetChecked(!bitFlag);

				if(bitFlag!= 1)
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
					pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_TEMP_ALARM);			
				}
				else
				{
					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
					pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_TEMP_ALARM);
				}

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_ALARM);
				bitFlag = (status >> 1) & 1;
				p->SetChecked(!bitFlag);
				if( (status >> 1 & 1 ) == 1)
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ALARM= 0;
				else
					m_LaserHEAD1StatusToSend.bHEAD1_LASER_ALARM = 1;

				p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_MONITOR);
				bitFlag = status  & 1;
				p->SetChecked(!bitFlag);

			}
			break;


		case SPILaserCommandByte::GetAnalogueSignals:
			{
				int active = ByteArrayToUINT16(&pData[7]);
				spiData.activeCurrent = active;
				double tempActiveCurrent =  m_spiDataHEAD1.activeCurrent / 10.0;
				m_LaserHEAD1StatusToSend.dHEAD1_LASER_ACTIVE_POWER = tempActiveCurrent;
			}

			break;

		case SPILaserCommandByte::GetPulseWaveform:
			{
				int pulseWaveform = ByteArrayToUINT16(&pData[5]);
				spiData.waveForm = pulseWaveform;
			}
			break;
		case SPILaserCommandByte::GetLaserInterfaceControlMode:
			{
				UCHAR ctrlMode = pData[5];
				spiData.laserControlMode = ctrlMode;
			}

			break;

		case SPILaserCommandByte::GetPulseRate:
			{
				UINT32 pulseRate = ByteArrayToUINT32(&pData[5]);
				spiData.pulseRate = pulseRate;
				m_LaserHEAD1StatusToSend.dHEAD1_LASER_PULSE_RATE = pulseRate;
			}

		case SPILaserCommandByte::GetLaserControlSignals:
			{
				BYTE laserSignals = pData[5];
				spiData.laserControlSignals = laserSignals;

				/*if(m_spiDataHEAD2.laserControlSignals == 0)
				{
					CctPush* HEAD2GuideButton = (CctPush*)GetDlgItem(IDC_CTPUSH_GUIDE_BEAM);
					HEAD2GuideButton->SetForeColor(0);
				}

				else
				{
					CctPush* HEAD2GuideButton = (CctPush*)GetDlgItem(IDC_CTPUSH_GUIDE_BEAM);
					HEAD2GuideButton->SetForeColor(0xFF0000);
				}*/

			}

			break;


		case SPILaserCommandByte::QueryLaserTemperatures:
			{
				UINT16 laserTemperature = ByteArrayToUINT16(&pData[5]);
				double dRealTemp = (35800.0 - laserTemperature)/100.0;
				dRealTemp = 85 - dRealTemp;
				spiData.laserTemperature = dRealTemp;
				CString strTemp;
				strTemp.Format("Laser Temperature: %.2f", dRealTemp);
				SetDlgItemText(IDC_CTTEXTCTRL_LASERTEMP_HEAD1, strTemp);
				m_LaserHEAD1StatusToSend.dbHEAD1_LASER_BEAM_DELIVERLY_TEMP = dRealTemp;

				laserTemperature = ByteArrayToUINT16(&pData[7]);
				dRealTemp = (35800.0 - laserTemperature)/100.0;
				dRealTemp = 85 - dRealTemp;
				spiData.laserTemperature = dRealTemp;
				strTemp.Format("BDO Temperature: %.2f", dRealTemp);
				SetDlgItemText(IDC_CTTEXTCTRL_BDOTEMP_HEAD1, strTemp);
				m_LaserHEAD1StatusToSend.dHEAD1_LASER_BODY_TEMP = dRealTemp;
			}

			break;
		
		case SPILaserCommandByte::QueryPowerSupplyVoltages:
			{
				UINT16 PSU_Voltages = ByteArrayToUINT16(&pData[5]);
				UINT16 PSU_Voltages2 = ByteArrayToUINT16(&pData[7]);
				
				double dRealVoltages = PSU_Voltages / 1000.0;
				spiData.logicPowerSupply = dRealVoltages;
				CString strTemp;
				strTemp.Format("Logic PSU Voltages: %.3f", dRealVoltages);
				SetDlgItemText(IDC_CTTEXTCTRL_PSU_VOLTAGE_HEAD1, strTemp);

				dRealVoltages = PSU_Voltages2 / 1000.0;
				//spiData.diodePowerSupply = dRealVoltages;
				m_LaserHEAD1StatusToSend.dHEAD1_LASER_ACTIVE_MV = dRealVoltages;
				
				strTemp.Format("Amp PSU Voltages: %.3f", dRealVoltages);
				SetDlgItemText(IDC_CTTEXTCTRL_AMP_PSU_VOLTAGE_HEAD1, strTemp);
			}

			break;

		case SPILaserCommandByte::QueryExtendedLaserCurrents:
			{
				UINT16 PreAmpCurrent = ByteArrayToUINT16(&pData[5]);
				UINT16 MainAmpCurrent = ByteArrayToUINT16(&pData[7]);

				CString strTemp;
				strTemp.Format("PreAmp Current: %d(mA)", PreAmpCurrent);
				SetDlgItemText(IDC_CTTEXTCTRL_PRE_AMP_HEAD1, strTemp);

				strTemp.Format("Main Cuttent: %d(mA)", MainAmpCurrent);
				SetDlgItemText(IDC_CTTEXTCTRL_MAIN_AMP_HEAD1, strTemp);

				//m_LaserHEAD1StatusToSend
			}

			break;
			
	}

	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetLaserStatusHEAD1(m_LaserHEAD1StatusToSend);
	p->SetChecked(FALSE);
}

void	CDlgSPIDualLaser::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;

	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Sleep(1);
		}
	}
}



void CDlgSPIDualLaser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);


	DDX_Control(pDX, IDC_SPI_HEAD2_LASER_LOG, m_HEAD2LaserLog);
	DDX_Control(pDX, IDC_SPI_HEAD1_LASER_LOG, m_HEAD1LaserLog);

	DDX_Text(pDX, IDC_CTTEXT_HEAD2_IP,m_HEAD2LaserIP);
	DDX_Text(pDX, IDC_CTTEXT_HEAD2_PORT,m_HEAD2LaserPort);

	DDX_Text(pDX, IDC_CTTEXT_HEAD1_IP,m_HEAD1LaserIP);
	DDX_Text(pDX, IDC_CTTEXT_HEAD1_PORT,m_HEAD1LaserPort);


	double tempActiveCurrent =  m_spiDataHEAD2.activeCurrent / 10.0;
	DDX_Text(pDX, IDC_CTTEXT_HEAD2_ACTIVE, tempActiveCurrent);
	DDX_Text(pDX, IDC_CTTEXT_HEAD2_WAVE_FORM, m_spiDataHEAD2.waveForm);
	DDX_Text(pDX, IDC_CTTEXT_HEAD2_CTRLMODE, m_spiDataHEAD2.laserControlMode);
	DDX_Text(pDX, IDC_CTTEXT_HEAD2_PRF, m_spiDataHEAD2.pulseRate);


	tempActiveCurrent =  m_spiDataHEAD1.activeCurrent / 10.0;
	DDX_Text(pDX, IDC_CTTEXT_HEAD1_ACTIVE, tempActiveCurrent);
	DDX_Text(pDX, IDC_CTTEXT_HEAD1_WAVE_FORM, m_spiDataHEAD1.waveForm);
	DDX_Text(pDX, IDC_CTTEXT_HEAD1_CTRLMODE, m_spiDataHEAD1.laserControlMode);
	DDX_Text(pDX, IDC_CTTEXT_HEAD1_PRF, m_spiDataHEAD1.pulseRate);


	// ActiveCurrent에 관하여
	// 레이저 파라미터들은 이곳에서 화면에 보여주는 세팅만 하고 실제로 변수에는 저장되지 않습니다.(UpdateData(TRUE))는 사용하지 않습니다.
	// True Pulse Nano의 파워(Active)값은 밀리퍼센트(1000)단위여서 퍼센트(100)단위로 바꾸기 위해 10.0으로 나누어줍니다.
	// 실제 레이저 파워(Active)를 세팅하는 곳에는 입력 값에 10을 곱해서 통신을 합니다.



}


BEGIN_MESSAGE_MAP(CDlgSPIDualLaser, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SPI_LASER_TEST_BBUTTON, &CDlgSPIDualLaser::OnBnClickedSpiLaserTestBbutton)
	ON_BN_CLICKED(IDC_CHECK_GUIDEBEAM_HEAD2, &CDlgSPIDualLaser::OnBnClickedCheckGuidebeamHEAD2)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SOCK_RECEIVE, &CDlgSPIDualLaser::OnSockReceiveFromSPI)
	ON_BN_CLICKED(IDOK2, &CDlgSPIDualLaser::OnBnClickedOk2)
	ON_BN_CLICKED(ID_CONNTECT, &CDlgSPIDualLaser::OnBnClickedConntect)
	ON_BN_CLICKED(IDOK3, &CDlgSPIDualLaser::OnBnClickedOk3)
END_MESSAGE_MAP()


// CDlgSPIDualLaser 메시지 처리기입니다.


void CDlgSPIDualLaser::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	CWriteLog *log = NULL;
	LASERSTATUS  HEAD2LaserStatus,HEAD1LaserStatus;
	SPIData HEAD1SPIData; 
	SPIData HEAD2SPIData; 
	CString strSetValue;

#ifdef	_RTC_Test_		
	return;
#endif

#ifdef _TestMC_			
	return;
#endif


	switch(nIDEvent)
	{
	case TIMER_UPDATE_LASER_POWER:
		
		HEAD2LaserStatus.clear(); HEAD1LaserStatus.clear();
		HEAD2LaserStatus = pFieldParameter->GetLaserStatusHEAD2();
		HEAD1LaserStatus = pFieldParameter->GetLaserStatusHEAD1();

		
		HEAD1SPIData = GetSPIDataHEAD1();
		//HEAD1SPIData.activeCurrent = atoi(strSetValue)* 10 ;

		HEAD2SPIData = GetSPIDataHEAD2();
		//HEAD2SPIData.activeCurrent = atoi(strSetValue)* 10 ;


		if(m_pSPILaserHEAD2->GetIsConnect())
		{
			SetAnalogueCurrentSetPoint(0,HEAD2SPIData.activeCurrent,m_pSPILaserHEAD2);
			//SetPulseWaveform(HEAD1SPIData.waveForm,m_pSPILaserHEAD2);
			SetPulseRate(HEAD2SPIData.pulseRate,m_pSPILaserHEAD2);
		}

		if(m_pSPILaserHEAD1->GetIsConnect())
		{
			SetAnalogueCurrentSetPoint(0,HEAD1SPIData.activeCurrent,m_pSPILaserHEAD2);
		//SetPulseWaveform(HEAD2SPIData.waveForm,m_pSPILaserHEAD2);
			SetPulseRate(HEAD1SPIData.pulseRate,m_pSPILaserHEAD2);
		}


		

		


		break;
	
	case TIMER_HEAD1_AUTO_LASER_READY:
		KillTimer(TIMER_HEAD1_AUTO_LASER_READY);
		SetLaserControlSignals(0,m_pSPILaserHEAD1);
		SetDelayTime(50);
		SetLaserControlSignals(1,m_pSPILaserHEAD1);
		SetDelayTime(50);
		RestartPulseGenerator(m_spiDataHEAD1.waveForm,m_pSPILaserHEAD1);
		//SetLaserControlSignals(0,m_pSPILaserHEAD1);
		isGuideBeamHEAD1 = false;
		break;

	case TIMER_HEAD2_AUTO_LASER_READY:
		KillTimer(TIMER_HEAD2_AUTO_LASER_READY);
		SetLaserControlSignals(0,m_pSPILaserHEAD2);
		SetDelayTime(50);
		SetLaserControlSignals(1,m_pSPILaserHEAD2);
		SetDelayTime(50);
		RestartPulseGenerator(m_spiDataHEAD2.waveForm,m_pSPILaserHEAD2);

		//SetLaserControlSignals(0,m_pSPILaserHEAD2);
		isGuideBeamHEAD2 = false;
		break;

	case TIMER_SPI_CONNECT_CHECK_HEAD1:
		
		if(m_pSPILaserHEAD1->GetIsConnect())
		{
			bHEAD1Connect = TRUE;
			pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_COM_DISCONECT);
			SetTimer(TIMER_HEAD1_LASERON_IO,1000,NULL);
			//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);

		}
		else
		{
			bHEAD1Connect = FALSE;
			//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
			//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);

//			CInformationView* a = CPointerContainer::GetInformationView();
//			a->OnStopMark();

			pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_COM_DISCONECT);
			SetTimer(TIMER_HEAD1_LASERON_IO,10000,NULL);
		}
		break;

	case TIMER_SPI_CONNECT_CHECK_HEAD2:

		if(m_pSPILaserHEAD2->GetIsConnect())
		{
			bHEAD2Connect = TRUE;
			pMainFrm->PostMessage(WM_HIDE_ERROR,ERROR_LASER_COM_DISCONECT);
			SetTimer(TIMER_HEAD2_LASERON_IO,1000,NULL);
			//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
		}
		else
		{

			//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
// 			CInformationView* a = CPointerContainer::GetInformationView();
// 			a->OnStopMark();
			

			pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_COM_DISCONECT);
			bHEAD2Connect = FALSE;
			

#ifndef _SIMUL_
			SetTimer(TIMER_HEAD2_LASERON_IO,10000,NULL);
#endif
		}
		break;


	case TIMER_HEAD1_LASERON_IO:
		{
			//SetTimer(TIMER_SPI_CONNECT_CHECK_HEAD1, TIMER_SPI_CONNECT_CHEECK_INTERVAL, NULL);
			
			CString strHEAD2LaserPort;
			strHEAD2LaserPort.Format(_T("%d"),m_HEAD2LaserPort);
			SetDlgItemText(IDC_CTTEXT_HEAD2_IP, m_HEAD2LaserIP );
			SetDlgItemText(IDC_CTTEXT_HEAD2_PORT, strHEAD2LaserPort);
			if(pDsp->GetBoardCount() > 1)
			{
				if(bHEAD1Connect == FALSE)
				{
					//if(m_pSPILaserHEAD1->InitCommnicate() != -1)
					{
						if(m_pSPILaserHEAD1->StartCommunicate() != 0) // 통신 시작에 실패하면 0을 리턴한다. 명시적으로 보여주자
						{
							KillTimer(TIMER_HEAD1_LASERON_IO);
							//AfxMessageBox(_T("HEAD1 Laser Connect Success"));
							SetTimer(TIMER_SPI_CHECK_DATA,TIMER_SPI_INTERVAL,NULL);
							m_HEAD1LaserLog.AddString(_T("HEAD1 Laser Connect Success"));
							pMainFrm->AddLogData("HEAD1 Laser Connect Success...");
							bHEAD1Connect = TRUE;
							SetTimer(TIMER_SPI_CONNECT_CHECK_HEAD1, TIMER_SPI_CONNECT_CHEECK_INTERVAL, NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);

							SetTimer(TIMER_HEAD1_AUTO_LASER_READY,1000,NULL);
							

						}
						else
						{
							if(m_HEAD1LaserLog.GetCount() > 10)
								m_HEAD1LaserLog.ResetContent();

							m_HEAD1LaserLog.AddString(_T("HEAD1 Laser ReConnect..."));
							pMainFrm->AddLogData("HEAD1 Laser ReConnect...");
							bHEAD1Connect = FALSE;
							SetTimer(TIMER_HEAD1_LASERON_IO,10000,NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
//							CInformationView* a = CPointerContainer::GetInformationView();
//							a->OnStopMark();
						}
						//SetDelayTime(2000);
					}
					//else
					//{
						//AfxMessageBox(_T("HEAD1 Laser Connect Fail!!\nPlease Check Laser IP or Port Number"));
					//}
				}

			}
			break;
		}
	case TIMER_HEAD2_LASERON_IO:
		{
#ifdef	_RTC_Test_		
			return;
#endif
			
			if(pDsp->GetBoardCount() > 0)
			{
				if(bHEAD2Connect == FALSE)
				{
					//if(m_pSPILaserHEAD2->InitCommnicate() != -1)
					{
						//SetDelayTime(3000);
						if(m_pSPILaserHEAD2->StartCommunicate() != 0) // 통신 시작에 실패하면 0을 리턴한다. 명시적으로 보여주자
						{
							//AfxMessageBox(_T("HEAD2 Laser Connect Success"));
							KillTimer(TIMER_HEAD2_LASERON_IO);
							//SetTimer(TIMER_SPI_QUERY_STATUS,1000,NULL);
							SetTimer(TIMER_SPI_CHECK_DATA,TIMER_SPI_INTERVAL,NULL);
							m_HEAD2LaserLog.AddString(_T("HEAD2 Laser Connect Success"));
							//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);

							bHEAD2Connect = TRUE;
							SetTimer(TIMER_SPI_CONNECT_CHECK_HEAD2, TIMER_SPI_CONNECT_CHEECK_INTERVAL, NULL);
							SetTimer(TIMER_HEAD2_AUTO_LASER_READY,1000,NULL);

							pMainFrm->AddLogData("HEAD2 Laser Connect Success...");
							

						}
						else
						{
							if(m_HEAD2LaserLog.GetCount() > 10)
								m_HEAD2LaserLog.ResetContent();

							m_HEAD2LaserLog.AddString(_T("HEAD2 Laser ReConnect..."));
							SetTimer(TIMER_HEAD2_LASERON_IO,10000,NULL);

							pMainFrm->AddLogData("HEAD2 Laser ReConnect...");
							//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
							//SetTimer(TIMER_HEAD2_LASERON_IO,2000,NULL);
							bHEAD2Connect = FALSE;
//							CInformationView* a = CPointerContainer::GetInformationView();
//#ifndef _TestMC_			
//							a->OnStopMark();
//#endif
						}
					}
				}

				//else
				//{
				//	AfxMessageBox(_T("HEAD2 Laser Connect Fail!!\nPlease Check Laser IP or Port Number"));

				//}

			}

			break;
		}
	case TIMER_SPI_CONNECT_TO_LASER:
#ifdef	_RTC_Test_		
			return;
#endif
		KillTimer(TIMER_SPI_CONNECT_TO_LASER);
		{
			
			CString strHEAD2LaserPort;
			strHEAD2LaserPort.Format(_T("%d"),m_HEAD2LaserPort);
			SetDlgItemText(IDC_CTTEXT_HEAD2_IP, m_HEAD2LaserIP );
			SetDlgItemText(IDC_CTTEXT_HEAD2_PORT, strHEAD2LaserPort);
			if(pDsp->GetBoardCount() > 1)
			{
				if(bHEAD1Connect == FALSE)
				{
					//if(m_pSPILaserHEAD1->InitCommnicate() != -1)
					{
						if(m_pSPILaserHEAD1->StartCommunicate() != 0) // 통신 시작에 실패하면 0을 리턴한다. 명시적으로 보여주자
						{
							//AfxMessageBox(_T("HEAD1 Laser Connect Success"));
							SetTimer(TIMER_SPI_CHECK_DATA,TIMER_SPI_INTERVAL,NULL);
							m_HEAD1LaserLog.AddString(_T("HEAD1 Laser Connect Success"));
							pMainFrm->AddLogData("HEAD1 Laser Connect Success...");
							bHEAD1Connect = TRUE;
							SetTimer(TIMER_SPI_CONNECT_CHECK_HEAD1, TIMER_SPI_CONNECT_CHEECK_INTERVAL, NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
							SetTimer(TIMER_HEAD1_AUTO_LASER_READY,1000,NULL);
						}
						else
						{
							if(m_HEAD1LaserLog.GetCount() > 10)
								m_HEAD1LaserLog.ResetContent();

							m_HEAD1LaserLog.AddString(_T("HEAD1 Laser ReConnect..."));
							pMainFrm->AddLogData("HEAD1 Laser ReConnect...");
							bHEAD1Connect = FALSE;
							SetTimer(TIMER_HEAD1_LASERON_IO,10000,NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
// 							CInformationView* a = CPointerContainer::GetInformationView();
// 							a->OnStopMark();
						}
						SetDelayTime(2000);
					}
					//else
					//{
					//	AfxMessageBox(_T("HEAD1 Laser Connect Fail!!\nPlease Check Laser IP or Port Number"));
					//}
				}

			}

			if(pDsp->GetBoardCount() > 0)
			{
				if(bHEAD2Connect == FALSE)
				{
					//if(m_pSPILaserHEAD2->InitCommnicate() != -1)
					{

						if(m_pSPILaserHEAD2->StartCommunicate() != 0) // 통신 시작에 실패하면 0을 리턴한다. 명시적으로 보여주자
						{
							//AfxMessageBox(_T("HEAD2 Laser Connect Success"));
							m_HEAD2LaserLog.AddString(_T("HEAD2 Laser Connect Success"));
							pMainFrm->AddLogData("HEAD2 Laser Connect Success...");
							SetTimer(TIMER_SPI_CHECK_DATA,TIMER_SPI_INTERVAL,NULL);
							//SetTimer(TIMER_SPI_QUERY_STATUS,1000,NULL);
							bHEAD2Connect = TRUE;
							SetTimer(TIMER_SPI_CONNECT_CHECK_HEAD2, TIMER_SPI_CONNECT_CHEECK_INTERVAL, NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
							SetTimer(TIMER_HEAD2_AUTO_LASER_READY,1000,NULL);
						}
						else
						{
							if(m_HEAD2LaserLog.GetCount() > 10)
								m_HEAD2LaserLog.ResetContent();

							m_HEAD2LaserLog.AddString(_T("HEAD2 Laser ReConnect..."));
							pMainFrm->AddLogData("HEAD2 Laser ReConnect...");
							bHEAD2Connect = FALSE;
							SetTimer(TIMER_HEAD2_LASERON_IO,10000,NULL);
							//pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);

						}
						SetDelayTime(3000);
					}

					//else
					//{
					//	AfxMessageBox(_T("HEAD2 Laser Connect Fail!!\nPlease Check Laser IP or Port Number"));

					//}
				}

			}

			
			
			 
			/*if(isSuccess && m_HEAD2SocketManager.WatchComm())
			{
				AfxMessageBox(_T("Connect Success : "));
				m_HEAD2SocketManager.m_isConnected = isSuccess;

				m_HEAD2SocketManager.GetLaserPartNumber();
				
				m_HEAD2SocketManager.GetLaserSerialNumber();

				m_HEAD2SocketManager.QueryStatusLinesAndAlarms();
				
				m_HEAD2SocketManager.SetLaserControlSignals(1);

				m_HEAD2SocketManager.SetAnalogueCurrentSetPoint(0,1000);

				m_HEAD2SocketManager.SetAllPulseGeneratorParameters(0,300000,0,1000);

				m_HEAD2SocketManager.RestartPulseGenerator(0);


				m_HEAD2SocketManager.SetLaserInterfaceControlMode('0');
				SetTimer(TIMER_SPI_CHECK_DATA,500,NULL);
				
			}
			else 
			{
				AfxMessageBox(_T("HEAD2 Laser Connect Fail : ") + m_HEAD2LaserIP + _T(" ") + m_HEAD2LaserPort);
			}*/

			//isSuccess = m_HEAD1Socketmanager.ConnectTo(m_HEAD1LaserIP,m_HEAD1LaserPort ,AF_INET, SOCK_STREAM);

			
		}

		

		break;

	case TIMER_SPI_QUERY_STATUS:
		QueryStatusLinesAndAlarms(m_pSPILaserHEAD2);
		//2022.11.23
		QueryStatusLinesAndAlarms(m_pSPILaserHEAD1);
		break;


	case TIMER_SPI_CHECK_DATA:

		KillTimer(TIMER_SPI_CHECK_DATA);
		
		//HEAD1======================================================================================
		if(m_pSPILaserHEAD1->GetIsConnect())
		{
			CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_TX);
			p->SetChecked(TRUE);
			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryStatusLinesAndAlarms(m_pSPILaserHEAD1);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetAnalogueSignals(0,m_pSPILaserHEAD1);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetPulseWaveform(m_pSPILaserHEAD1);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetLaserInterfaceControlMode(m_pSPILaserHEAD1);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetPulseRate(m_pSPILaserHEAD1);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetLaserControlSignals(m_pSPILaserHEAD1);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryLaserTemperatures(m_pSPILaserHEAD1);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryPowerSupplyVoltages(m_pSPILaserHEAD1);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryExtendedLaserCurrents(m_pSPILaserHEAD1);
			p->SetChecked(TRUE);

		}
		//HEAD2------------------------------------------------------------------------------------
		if(m_pSPILaserHEAD2->GetIsConnect())
		{
			CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_TX);
			 // 레이저 상태는 계속 체크하장
			p->SetChecked(TRUE);
			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryStatusLinesAndAlarms(m_pSPILaserHEAD2);
			
			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetAnalogueSignals(0,m_pSPILaserHEAD2);
			p->SetChecked(FALSE);


			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetPulseWaveform(m_pSPILaserHEAD2);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetLaserInterfaceControlMode(m_pSPILaserHEAD2);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetPulseRate(m_pSPILaserHEAD2);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			GetLaserControlSignals(m_pSPILaserHEAD2);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryLaserTemperatures(m_pSPILaserHEAD2);
			p->SetChecked(TRUE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryPowerSupplyVoltages(m_pSPILaserHEAD2);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryExtendedLaserCurrents(m_pSPILaserHEAD2);
			p->SetChecked(FALSE);

			SetDelayTime(TIMER_SPI_QUERY_DELAY);
			QueryExtendedLaserCurrents(m_pSPILaserHEAD2);
			p->SetChecked(TRUE);


			
		}
		//HEAD2------------------------------------------------------------------------------------
		SetTimer(TIMER_SPI_CHECK_DATA,TIMER_SPI_INTERVAL,NULL);
		//HEAD1======================================================================================
		
		UpdateData(FALSE);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


int CDlgSPIDualLaser::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


#ifndef _SIMUL_
	SetTimer(TIMER_SPI_CONNECT_TO_LASER,2000,NULL);
#endif

	return 0;
}


void CDlgSPIDualLaser::OnBnClickedSpiLaserTestBbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	

	//m_HEAD2SocketManager.m_spiData.burstLength = 3;
}


void CDlgSPIDualLaser::SetSPILaserData()
{

	////HEAD2------------------------------------------------------------------------------------
	//int status = m_HEAD2SocketManager.m_spiData.statusLineAndAlarm;

	//CctCheck* p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_TASK_ACTIVE);
	//p->SetChecked(status >> 11 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_CW);
	//p->SetChecked(status >> 10 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ON);
	//p->SetChecked(status >> 9 & 1);

	//
	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ENABLE);
	//p->SetChecked(status >> 8 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_ON);
	//p->SetChecked(status >> 7 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_EMISSION);
	//p->SetChecked(status >> 6 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_DISABLE);
	//p->SetChecked(status >> 5 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_SYSTEM);
	//p->SetChecked(status >> 4 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_BEAM_DELIVERY_TEMP);
	//p->SetChecked(status >> 3 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_LASER_BODY_TEMP);
	//p->SetChecked(status >> 2 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_ALARM);
	//p->SetChecked(status >> 1 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_MONITOR);
	//p->SetChecked(status  & 1);


	//CString fotmatStr;

	//fotmatStr.Format(_T("%d"),m_HEAD2SocketManager.m_spiData.laserControlMode);
	//SetDlgItemText(IDC_CTTEXT_HEAD2_CTRLMODE,fotmatStr);


	//fotmatStr.Format(_T("%d"),m_HEAD2SocketManager.m_spiData.waveForm);
	//SetDlgItemText(IDC_CTTEXT_HEAD2_WAVE_FORM,fotmatStr);
	//
	//
	//fotmatStr.Format(_T("%d"),m_HEAD2SocketManager.m_spiData.pulseRate);
	//SetDlgItemText(IDC_CTTEXT_HEAD2_PRF,fotmatStr);

	//fotmatStr.Format(_T("%d"),m_HEAD2SocketManager.m_spiData.activeCurrent);
	//SetDlgItemText(IDC_CTTEXT_HEAD2_ACTIVE,fotmatStr);
	////HEAD2------------------------------------------------------------------------------------


	////HEAD1**************************************************************************************
	//status = m_HEAD1Socketmanager.m_spiData.statusLineAndAlarm;

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_TASK_ACTIVE);
	//p->SetChecked(status >> 11 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_CW);
	//p->SetChecked(status >> 10 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ON);
	//p->SetChecked(status >> 9 & 1);

	//
	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ENABLE);
	//p->SetChecked(status >> 8 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_ON);
	//p->SetChecked(status >> 7 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_EMISSION);
	//p->SetChecked(status >> 6 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_DISABLE);
	//p->SetChecked(status >> 5 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_SYSTEM);
	//p->SetChecked(status >> 4 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_BEAM_DELIVERY_TEMP);
	//p->SetChecked(status >> 3 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_LASER_BODY_TEMP);
	//p->SetChecked(status >> 2 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_ALARM);
	//p->SetChecked(status >> 1 & 1);

	//p = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD1_MONITOR);
	//p->SetChecked(status  & 1);



	//fotmatStr.Format(_T("%d"),m_spiDataHEAD2.laserControlMode);
	//SetDlgItemText(IDC_CTTEXT_HEAD1_CTRLMODE,fotmatStr);


	//fotmatStr.Format(_T("%d"),m_HEAD1Socketmanager.m_spiData.waveForm);
	//SetDlgItemText(IDC_CTTEXT_HEAD1_WAVE_FORM,fotmatStr);
	//
	//
	//fotmatStr.Format(_T("%d"),m_HEAD1Socketmanager.m_spiData.pulseRate);
	//SetDlgItemText(IDC_CTTEXT_HEAD1_PRF,fotmatStr);

	//fotmatStr.Format(_T("%d"),m_HEAD1Socketmanager.m_spiData.activeCurrent);
	//SetDlgItemText(IDC_CTTEXT_HEAD1_ACTIVE,fotmatStr);
	////HEAD1**************************************************************************************
}


void CDlgSPIDualLaser::ShowLaserDlg()
{
	//CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	//if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	//{
	//	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//	//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
	//	pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
	//	return;
	//}

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	pMainFrm->OnShowLaserControl();
}


void CDlgSPIDualLaser::LedOnOff(UINT uid, int flag)
{
	CStatic *pIcon = (CStatic*)GetDlgItem(uid);

	switch(flag)
	{
		case LED_GRAY:		pIcon->SetBitmap(m_mLedGray);		break;
		case LED_GREEN_ON:	pIcon->SetBitmap(m_mLedGreen);		break;
	}

}



SPIData CDlgSPIDualLaser::GetSPIDataHEAD2()
{
	return m_spiDataHEAD2;
}

SPIData CDlgSPIDualLaser::GetSPIDataHEAD1()
{
	return m_spiDataHEAD1;
}

void CDlgSPIDualLaser::SendSPIHEAD2DataFromMRK(SPIData data)
{
	if(m_pSPILaserHEAD2!=NULL)
	{
		if(m_pSPILaserHEAD2->GetIsConnect())
		{
			SetAnalogueCurrentSetPoint(0,data.activeCurrent,m_pSPILaserHEAD2);
			SetPulseWaveform(data.waveForm,m_pSPILaserHEAD2);
			SetPulseRate(data.pulseRate,m_pSPILaserHEAD2);

			CString laserLogStr;

			laserLogStr.Format(_T("Set HEAD2 Laser Power : %lf"),data.activeCurrent/10.0);
			m_HEAD2LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD2 WaveForm : %d"),data.waveForm);
			m_HEAD2LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD2 Pulse Rate : %d"),data.pulseRate);
			m_HEAD2LaserLog.AddString(laserLogStr);

			CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
			strLogEvent.Format("--------------------Set HEAD2 Laser--------------------");
			strLogEvent.Format("Set Laser Power : %.1f",data.activeCurrent/10.0 );
			strLogEvent.Format("Set WaveForm : %d",data.waveForm );
			strLogEvent.Format("Set Pulse Rate : %d",data.pulseRate );
			strLogEvent.Format("----------------------------------------------------------");

		}
	}
}
void CDlgSPIDualLaser::SendSPIHEAD1DataFromMRK(SPIData data)
{
	//2022.10.20
	if(m_pSPILaserHEAD1!=NULL)
	{
		if(m_pSPILaserHEAD1->GetIsConnect())
		{
			SetAnalogueCurrentSetPoint(0,data.activeCurrent,m_pSPILaserHEAD1);
			SetPulseWaveform(data.waveForm,m_pSPILaserHEAD1);
			SetPulseRate(data.pulseRate,m_pSPILaserHEAD1);

			CString laserLogStr;

			laserLogStr.Format(_T("Set HEAD1 Laser Power : %lf"),data.activeCurrent/10.0);
			m_HEAD1LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD1 WaveForm : %d"),data.waveForm);
			m_HEAD1LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD1 Pulse Rate : %d"),data.pulseRate);
			m_HEAD1LaserLog.AddString(laserLogStr);

			CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
			strLogEvent.Format("--------------------Set HEAD1 Laser--------------------");
			strLogEvent.Format("Set Laser Power : %.1f",data.activeCurrent/10.0 );
			strLogEvent.Format("Set WaveForm : %d",data.waveForm );
			strLogEvent.Format("Set Pulse Rate : %d",data.pulseRate );
			strLogEvent.Format("----------------------------------------------------------");
		}
	}
}



BEGIN_EVENTSINK_MAP(CDlgSPIDualLaser, CDialogEx)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_CTRLMODE, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2Ctrlmode, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_WAVE_FORM, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2WaveForm, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_PRF, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2Prf, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_ACTIVE, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2Active, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTCHECK_HEAD2_ISCONNECTED, DISPID_CLICK, CDlgSPIDualLaser::ClickCtcheckHEAD2Isconnected, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_IP, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2Ip, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD2_PORT, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD2Port, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_GUIDE_BEAM, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushGuideBeam, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD2_ENABLE, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD2Enable, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD2_TRIGGER, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD2Trigger, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD1_ENABLE, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD1Enable, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD1_TRIGGER, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD1Trigger, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD1_GUIDE_BEAM, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD1GuideBeam, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD1_CTRLMODE, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD1Ctrlmode, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD1_WAVE_FORM, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD1WaveForm, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD1_PRF, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD1Prf, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTTEXT_HEAD1_ACTIVE, DISPID_CLICK, CDlgSPIDualLaser::ClickCttextHEAD1Active, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD2_STANDBY, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD2Standby, VTS_NONE)
	ON_EVENT(CDlgSPIDualLaser, IDC_CTPUSH_HEAD1_STANDBY, DISPID_CLICK, CDlgSPIDualLaser::ClickCtpushHEAD1Standby, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgSPIDualLaser::ClickCttextHEAD2Ctrlmode()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,7,m_spiDataHEAD2.laserControlMode);
	if(keypadDlg.DoModal()==IDOK)
	{

		//double mode = keypadDlg.GetResultDouble();

		
		int ctrlMode = keypadDlg.GetResultInteger();;
		SetLaserInterfaceControlMode(ctrlMode,m_pSPILaserHEAD2);

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD2 ControlMode %d -> %d"),m_spiDataHEAD2.laserControlMode, ctrlMode );

		//m_HEAD2SocketManager.m_spiData.isReceiveLaserControlMode = false;
		//m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);
		

	}
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD2WaveForm()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,63,m_spiDataHEAD2.waveForm);

	if(keypadDlg.DoModal()==IDOK)
	{

		int waveFormNum = keypadDlg.GetResultInteger();
		SetPulseWaveform(waveFormNum,m_pSPILaserHEAD2);


		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD2 WaveFormNum %d -> %d"),m_spiDataHEAD2.waveForm, waveFormNum );

		////m_HEAD2SocketManager.m_spiData.waveForm = waveFormNum;
		//m_HEAD2SocketManager.SetAllPulseGeneratorParameters(waveFormNum,m_HEAD2SocketManager.m_spiData.pulseRate,
		//m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		//m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;
		//m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);
	}
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD2Prf()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,1000000,m_spiDataHEAD2.pulseRate);

	if(keypadDlg.DoModal()==IDOK)
	{

		int pulseRate = keypadDlg.GetResultInteger();;
		SetPulseRate(pulseRate,m_pSPILaserHEAD2);


		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD2 PulseRate %lf -> %lf"),m_spiDataHEAD2.pulseRate, pulseRate );


		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}



	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD2Active()
{

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0.0,100.0,m_spiDataHEAD2.activeCurrent / 10.0);

	if(keypadDlg.DoModal()==IDOK)
	{
		/*int activeCurrent = keypadDlg.GetResultInteger();;
		m_HEAD2SocketManager.SetAnalogueCurrentSetPoint(0,activeCurrent);
		m_HEAD2SocketManager.m_spiData.isReceiveActiveCurrent = false;*/

		int activeCurrent = keypadDlg.GetResultDouble() * 10.0;

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD2 ActiveCurrent %lf -> %lf"),m_spiDataHEAD2.activeCurrent / 10.0, activeCurrent );

		SetAnalogueCurrentSetPoint(0,activeCurrent,m_pSPILaserHEAD2);
	}


	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtcheckHEAD2Isconnected()
{

	

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//if(!m_HEAD2SocketManager.m_isConnected)
	//{
	//	/*m_HEAD2LaserIP = _T("192.168.0.180");
	//	CString portNum  = _T("2000");*/
	//	UpdateData(FALSE);
	//	m_HEAD2SocketManager.CloseComm();
	//	m_HEAD2SocketManager.StopComm();
	//	

	//	
	//	bool isSuccess = false;//m_HEAD2SocketManager.ConnectTo(m_HEAD2LaserIP,m_HEAD2LaserPort ,AF_INET, SOCK_STREAM);

	//	

	//	if(isSuccess && m_HEAD2SocketManager.WatchComm())
	//	{
	//		SetTimer(TIMER_SPI_CHECK_DATA,500,NULL);
	//		m_HEAD2SocketManager.m_isConnected = isSuccess;
	//	}
	//	
	//}



	//if(m_HEAD2SocketManager.m_isConnected)
	//{
	//	CctCheck* checkIsConnected = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_ISCONNECTED);
	//	checkIsConnected->SetChecked(TRUE);
	//}

	//else
	//{
	//	CctCheck* checkIsConnected = (CctCheck*)GetDlgItem(IDC_CTCHECK_HEAD2_ISCONNECTED);
	//	checkIsConnected->SetChecked(FALSE);

	//}

}


void CDlgSPIDualLaser::ClickCttextHEAD2Ip()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAlphaKeyPad dlgAlpha;
	dlgAlpha.SetStrOldData(m_HEAD2LaserIP);
	if(dlgAlpha.DoModal()== IDOK)
	{
		m_HEAD2LaserIP = dlgAlpha.GetStrNewData();
		SetDlgItemText(IDC_CTTEXT_HEAD2_IP,m_HEAD2LaserIP);
	}
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD2Port()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	/*CAlphaKeyPad dlgAlpha;
	dlgAlpha.SetStrOldData(m_HEAD2LaserPort);
	if(dlgAlpha.DoModal()== IDOK)
	{
		m_HEAD2LaserPort = dlgAlpha.GetStrNewData();
		SetDlgItemText(IDC_CTTEXT_HEAD2_PORT,m_HEAD2LaserPort);
	}
*/
}


void CDlgSPIDualLaser::ClickCtpushGuideBeam()
{
	//// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//CctPush* guidebeamButton = (CctPush*)(GetDlgItem(IDC_CTPUSH_GUIDE_BEAM));

	if(!isGuideBeamHEAD2) // 가이드빔이 꺼져있다면
	{
		SetLaserControlSignals(2,m_pSPILaserHEAD2);
		isGuideBeamHEAD2 = true;
	}

	else // 가이드빔이 켜져있다면
	{
		SetLaserControlSignals(0,m_pSPILaserHEAD2);
		SetDelayTime(50);
		SetLaserControlSignals(1,m_pSPILaserHEAD2);
		SetDelayTime(50);
		RestartPulseGenerator(m_spiDataHEAD2.waveForm,m_pSPILaserHEAD2);

		//SetLaserControlSignals(0,m_pSPILaserHEAD2);
		isGuideBeamHEAD2 = false;
	}
	

	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtpushHEAD2Enable()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetLaserControlSignals(1,m_pSPILaserHEAD2);
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtpushHEAD2Trigger()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	RestartPulseGenerator(m_spiDataHEAD2.waveForm,m_pSPILaserHEAD2);
	ShowLaserDlg();
}


void CDlgSPIDualLaser::OnBnClickedCheckGuidebeamHEAD2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

//	if((CButton*)GetDlgItem(IDC_CHECK_GUIDEBEAM_HEAD2))->GetCheck() == TRUE)


	if(IsDlgButtonChecked(IDC_CHECK_GUIDEBEAM_HEAD2))
	{
		SetLaserControlSignals(2,m_pSPILaserHEAD2);
	}

	else
	{
		SetLaserControlSignals(0,m_pSPILaserHEAD2);
	}

	ShowLaserDlg();


	
}


void CDlgSPIDualLaser::OnDestroy()
{

	if(m_pSPILaserHEAD2->GetIsConnect())
	{
		SetLaserControlSignals(0,m_pSPILaserHEAD2);
		SetAnalogueCurrentSetPoint(0,0,m_pSPILaserHEAD2);
	}


	if(m_pSPILaserHEAD1->GetIsConnect())
	{
		SetLaserControlSignals(0,m_pSPILaserHEAD1);
		SetAnalogueCurrentSetPoint(0,0,m_pSPILaserHEAD1);
	}
	

	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


afx_msg LRESULT CDlgSPIDualLaser::OnSockReceiveFromSPI(WPARAM wParam, LPARAM lParam)
{
	//if((int)wParam == ((CSPILaserTruePulseNanoEthernet*)m_pSPILaserHEAD2)->GetPortNum())

	

	if((int)wParam == ((CSPILaserTruePulseNanoEthernet*)m_pSPILaserHEAD2)->GetPortNum() && (int)lParam == HEAD2_SOCKET  )
	{
		ParseHEAD2Data((BYTE*)m_pSPILaserHEAD2->ReadData(),m_spiDataHEAD2);
	}
	//else if((int)wParam == ((CSPILaserTruePulseNanoEthernet*)m_pSPILaserHEAD1)->GetPortNum())
	else if((int)wParam == ((CSPILaserTruePulseNanoEthernet*)m_pSPILaserHEAD1)->GetPortNum() && (int)lParam == HEAD1_SOCKET)
	{
		//int a = 10;
		ParseHEAD1Data((BYTE*)m_pSPILaserHEAD1->ReadData(),m_spiDataHEAD1);
	}

	else
	{
		//int b = 20;
	}

	return 0;
}


void CDlgSPIDualLaser::ClickCtpushHEAD1Enable()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetLaserControlSignals(1,m_pSPILaserHEAD1);
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtpushHEAD1Trigger()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//RestartPulseGenerator(32768,m_pSPILaserHEAD1); // 32768 == 현재 WaveForm으로 RestartPulseGenerator 를 실행합니다. 메뉴얼 86page
	RestartPulseGenerator(m_spiDataHEAD1.waveForm,m_pSPILaserHEAD1);
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtpushHEAD1GuideBeam()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(!isGuideBeamHEAD1) // 가이드빔이 꺼져있다면
	{
		SetLaserControlSignals(2,m_pSPILaserHEAD1);
		isGuideBeamHEAD1 = true;
	}

	else // 가이드빔이 켜져있다면
	{
		SetLaserControlSignals(0,m_pSPILaserHEAD1);
		SetDelayTime(50);
		SetLaserControlSignals(1,m_pSPILaserHEAD1);
		SetDelayTime(50);
		RestartPulseGenerator(m_spiDataHEAD1.waveForm,m_pSPILaserHEAD1);
		//SetLaserControlSignals(0,m_pSPILaserHEAD1);
		isGuideBeamHEAD1 = false;
	}
	
	

	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD1Ctrlmode()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,7,m_spiDataHEAD1.laserControlMode);
	if(keypadDlg.DoModal()==IDOK)
	{

		//double mode = keypadDlg.GetResultDouble();

		
		int ctrlMode = keypadDlg.GetResultInteger();;
		SetLaserInterfaceControlMode(ctrlMode,m_pSPILaserHEAD1);

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD1 ControlMode %d -> %d"),m_spiDataHEAD1.laserControlMode, ctrlMode );

		
		//m_HEAD2SocketManager.m_spiData.isReceiveLaserControlMode = false;
		//m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);
		

	}
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD1WaveForm()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,63,m_spiDataHEAD1.waveForm);

	if(keypadDlg.DoModal()==IDOK)
	{

		int waveFormNum = keypadDlg.GetResultInteger();
		SetPulseWaveform(waveFormNum,m_pSPILaserHEAD1);

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD1 WaveFormNum %d -> %d"),m_spiDataHEAD1.waveForm, waveFormNum );


		////m_HEAD2SocketManager.m_spiData.waveForm = waveFormNum;
		//m_HEAD2SocketManager.SetAllPulseGeneratorParameters(waveFormNum,m_HEAD2SocketManager.m_spiData.pulseRate,
		//m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		//m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;
		//m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);
	}
	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD1Prf()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0,1000000,m_spiDataHEAD1.pulseRate);

	if(keypadDlg.DoModal()==IDOK)
	{

		int pulseRate = keypadDlg.GetResultInteger();;
		SetPulseRate(pulseRate,m_pSPILaserHEAD1);

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD1 PulseRate %d -> %d"),m_spiDataHEAD2.pulseRate, pulseRate );


		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}



	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCttextHEAD1Active()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0.0,100.0,m_spiDataHEAD1.activeCurrent / 10.0);

	if(keypadDlg.DoModal()==IDOK)
	{

		/*int activeCurrent = keypadDlg.GetResultInteger();;
		m_HEAD2SocketManager.SetAnalogueCurrentSetPoint(0,activeCurrent);

		m_HEAD2SocketManager.m_spiData.isReceiveActiveCurrent = false;*/

		int activeCurrent = keypadDlg.GetResultDouble() * 10.0;
		SetAnalogueCurrentSetPoint(0,activeCurrent,m_pSPILaserHEAD1);

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Set HEAD1 ActiveCurrent %lf -> %lf"),m_spiDataHEAD1.activeCurrent / 10.0, activeCurrent );

	}


	ShowLaserDlg();
}


void CDlgSPIDualLaser::ClickCtpushHEAD2Standby()
{
	//2022.11.23 test
	/*CDsp *pDsp = CDsp::GetInstance();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
	pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_TEMP_ALARM);

	return;*/
	SetLaserControlSignals(0,m_pSPILaserHEAD2);
	ShowLaserDlg();
}


BOOL CDlgSPIDualLaser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_mLedGray		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GRAY));
	m_mLedGreen		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GREEN));


	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	m_LaserHEAD1StatusToSend.clear();
	m_LaserHEAD2StatusToSend.clear();

	pFieldParameter->SetLaserStatusHEAD1(m_LaserHEAD1StatusToSend);
	pFieldParameter->SetLaserStatusHEAD2(m_LaserHEAD2StatusToSend);


	if(m_pSPILaserHEAD1->InitCommnicate() != -1)
	{
		if(m_pSPILaserHEAD1->StartCommunicate() != 0) 
			bHEAD1Connect = FALSE;
	}

	if(m_pSPILaserHEAD2->InitCommnicate()!= -1)
	{
		if(m_pSPILaserHEAD2->StartCommunicate() != 0) 
			bHEAD2Connect = FALSE;
	}


	//SetTimer(TIMER_UPDATE_LASER_POWER, 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgSPIDualLaser::ClickCtpushHEAD1Standby()
{
	SetLaserControlSignals(0,m_pSPILaserHEAD1);
	ShowLaserDlg();
}


void CDlgSPIDualLaser::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgSPIDualLaser::OnBnClickedConntect()
{
	//CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_LASER_COM_DISCONECT);	
	//SetTimer(TIMER_HEAD1_LASERON_IO,2000,NULL);
}


void CDlgSPIDualLaser::OnBnClickedOk3()
{
	//SetTimer(TIMER_HEAD2_LASERON_IO,2000,NULL);
}
