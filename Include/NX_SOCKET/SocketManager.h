// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SocketComm.h"

#define WM_UPDATE_CONNECTION	WM_APP+0x1234

const int SOCK_TCP	= 0;
const int SOCK_UDP  = 1;

#define MAX_CONNECTION		10


#ifdef NX_SOCKET_EXPORTS
#define DLL_SOCKET_EXPORTS __declspec(dllexport)
#else
#define DLL_SOCKET_EXPORTS __declspec(dllimport)
#endif
struct IPGData
{
	UINT32 IPG_pulseRate; // PulseMode 1000~1000000
	UINT32 IPG_pulsePower;
	/*bool isReceiveRs232BaudRate;

	UCHAR laserControlMode;
	bool isReceiveLaserControlMode;

	UINT16 laserControlSignals;
	bool isReceiveLaserControlSignals;

	UINT16 analogueCurrentSetPoint; // 0 = active, 1 = simmer


	UINT16 analogurCurrentMaxValue;

	bool isReceiveAllPulseGenerate;

	


	UINT16 PRF0;
	bool isReceivePRF0;*/


	 // PulseMode 1000~1000000
					  // CWMode 0~99
	                  // CW-M Mode 100~100000

	

	/*UINT32 burstLength;

	int activeCurrent;
	bool isReceiveActiveCurrent;
	


	UINT16 dutyFactor; // CW Mode..... maybe not use
	

	UINT16 statusLineAndAlarm;

	double laserTemperature;


	double beamDeliveryTemperature;


	UINT16 preAmplifierDiodeCurrent;


	UINT16 powerAmplifierDiodeCurrent;

	UINT16 logicPowerSupply;


	UINT16 diodePowerSupply;

	UINT16 digitalOutputSignals;


	UINT16 digitalInputSignals;

	UINT16 activeAnalogueInput;


	UINT16 simmerAnalogueInput;

	UINT32 operateHours;

	UINT32 externalPulseTriggerRepetationRate;


	UINT32 laserSerialNumber;
	bool isReceiveLaserSerialNumber;

	//CString laserPartNumber;
	bool isReceivelaserPartNumber;*/

	IPGData()
	{
		IPG_pulsePower=10;
		/*rs232BaudRate  = 0 ;
		isReceiveRs232BaudRate = false;

		laserControlMode = 0 ;
		isReceiveLaserControlMode = false;


		laserControlSignals = 0 ;
		analogueCurrentSetPoint = 0 ; // 0 = active, 1 
		analogurCurrentMaxValue = 0 ;

		isReceiveAllPulseGenerate = false;

		activeCurrent = 0;
		isReceiveActiveCurrent = false;

		
		PRF0 = 0 ;*/
		IPG_pulseRate = 250 ; // PulseMode 1000~1000000
		// CWMode 0~99
		// CW-M Mode 100~100000

		/*burstLength = 0 ;
		dutyFactor = 0 ; // CW Mode..... maybe not use

		statusLineAndAlarm = 0 ;

		laserTemperature = 0 ;
		beamDeliveryTemperature = 0 ;

		preAmplifierDiodeCurrent = 0 ;
		powerAmplifierDiodeCurrent = 0 ;

		logicPowerSupply = 0 ;
		diodePowerSupply = 0 ;

		digitalOutputSignals = 0 ;
		digitalInputSignals = 0 ;

		activeAnalogueInput = 0 ;
		simmerAnalogueInput = 0 ;

		operateHours = 0 ;

		externalPulseTriggerRepetationRate = 0 ;


		laserSerialNumber = 0 ;
		isReceiveLaserSerialNumber = false;

		//laserPartNumber = _T("");
		isReceivelaserPartNumber = false;*/
	}

};


struct SPIData
{
	UINT32 rs232BaudRate;
	bool isReceiveRs232BaudRate;

	UCHAR laserControlMode;
	bool isReceiveLaserControlMode;

	UINT16 laserControlSignals;
	bool isReceiveLaserControlSignals;

	UINT16 analogueCurrentSetPoint; // 0 = active, 1 = simmer


	UINT16 analogurCurrentMaxValue;

	bool isReceiveAllPulseGenerate;

	int waveForm;
	


	UINT16 PRF0;
	bool isReceivePRF0;


	UINT32 pulseRate; // PulseMode 1000~1000000
					  // CWMode 0~99
	                  // CW-M Mode 100~100000

	

	UINT32 burstLength;

	int activeCurrent;
	bool isReceiveActiveCurrent;
	


	UINT16 dutyFactor; // CW Mode..... maybe not use
	

	UINT16 statusLineAndAlarm;

	double laserTemperature;


	double beamDeliveryTemperature;


	UINT16 preAmplifierDiodeCurrent;


	UINT16 powerAmplifierDiodeCurrent;

	UINT16 logicPowerSupply;


	UINT16 diodePowerSupply;

	UINT16 digitalOutputSignals;


	UINT16 digitalInputSignals;

	UINT16 activeAnalogueInput;


	UINT16 simmerAnalogueInput;

	UINT32 operateHours;

	UINT32 externalPulseTriggerRepetationRate;


	UINT32 laserSerialNumber;
	bool isReceiveLaserSerialNumber;

	//CString laserPartNumber;
	bool isReceivelaserPartNumber;

	SPIData()
	{

		rs232BaudRate  = 0 ;
		isReceiveRs232BaudRate = false;

		laserControlMode = 0 ;
		isReceiveLaserControlMode = false;


		laserControlSignals = 0 ;
		analogueCurrentSetPoint = 0 ; // 0 = active, 1 
		analogurCurrentMaxValue = 0 ;

		isReceiveAllPulseGenerate = false;

		activeCurrent = 0;
		isReceiveActiveCurrent = false;

		waveForm = 0 ;
		PRF0 = 0 ;
		pulseRate = 0 ; // PulseMode 1000~1000000
		// CWMode 0~99
		// CW-M Mode 100~100000

		burstLength = 0 ;
		dutyFactor = 0 ; // CW Mode..... maybe not use

		statusLineAndAlarm = 0 ;

		laserTemperature = 0 ;
		beamDeliveryTemperature = 0 ;

		preAmplifierDiodeCurrent = 0 ;
		powerAmplifierDiodeCurrent = 0 ;

		logicPowerSupply = 0 ;
		diodePowerSupply = 0 ;

		digitalOutputSignals = 0 ;
		digitalInputSignals = 0 ;

		activeAnalogueInput = 0 ;
		simmerAnalogueInput = 0 ;

		operateHours = 0 ;

		externalPulseTriggerRepetationRate = 0 ;


		laserSerialNumber = 0 ;
		isReceiveLaserSerialNumber = false;

		//laserPartNumber = _T("");
		isReceivelaserPartNumber = false;





	}

};


class DLL_SOCKET_EXPORTS CSocketManager : public CSocketComm  
//class CSocketManager : public CSocketComm  
{
public:
	CSocketManager();
	virtual ~CSocketManager();

	void SetMessageWindow(CListBox* pMsgCtrl);
	void AppendMessage(LPCTSTR strText );

	SPIData m_spiData;

	bool m_isConnected;
public:

	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);

	virtual void OnEvent(UINT uEvent, LPVOID lpvData);

	


	void ShowLog(CString log);
protected:
	void DisplayData(const LPBYTE lpData, DWORD dwCount, const SockAddrIn& sfrom);
	CListBox* m_pMsgCtrl;
};

extern DLL_SOCKET_EXPORTS CSocketManager* SocketManager;
extern DLL_SOCKET_EXPORTS CSocketManager* SocketCurrServer;
#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
