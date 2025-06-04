#pragma once


// CDlgSPIDualLaser 대화 상자입니다.
#include "NX_SOCKET\SocketManager.h"
#include <string>
#include "afxwin.h"
#include "LanSocket.h"
#include "BtnST.h"
#include "FieldParameter.h"


#define TIMER_SPI_CONNECT_TO_LASER 1
#define TIMER_SPI_CHECK_DATA 2
#define TIMER_SPI_QUERY_STATUS 3

#define TIMER_SPI_CONNECT_CHECK_HEAD1   4
#define TIMER_SPI_CONNECT_CHECK_HEAD2 5

#define TIMER_SPI_INTERVAL				 700 //2초에 한번씩
#define TIMER_SPI_QUERY_DELAY			 10 //2초에 한번씩
#define TIMER_HEAD1_LASERON_IO			 20
#define TIMER_HEAD2_LASERON_IO         30


#define TIMER_HEAD1_AUTO_LASER_READY        31
#define TIMER_HEAD2_AUTO_LASER_READY      32

#define TIMER_UPDATE_LASER_POWER            33

#define TIMER_SPI_CONNECT_CHEECK_INTERVAL	10000 




class CSPILaserTruePulseNanoEthernet : public CLanSocket
{
private:
	BYTE m_byteBuffer[MAX_BUFFER];
	
public:
	SPIData m_spiData;

	
	

public:
	
	CSPILaserTruePulseNanoEthernet(CString owner, CWnd* pWnd) : CLanSocket( owner, pWnd)
	{

	}
	
	
	virtual void OnReceive(int nErrorCode);
	virtual char* ReadData();
	virtual UINT WriteData(BYTE *SendString, DWORD Stringlength);

	int GetPortNum();
	CString GetIPAddress();
	


};



class CDlgSPIDualLaser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSPIDualLaser)
public:
	_LASERSTATUS_ m_LaserHEAD2StatusToSend;
	_LASERSTATUS_ m_LaserHEAD1StatusToSend;

	BOOL bHEAD1Connect;
	BOOL bHEAD2Connect;

	BOOL bHEAD1DataRcvFlag;
	BOOL bHEAD2DataRcvFlag;


private: 
	CCommunicate* m_pSPILaserHEAD2;
	CCommunicate* m_pSPILaserHEAD1;

	SPIData m_spiDataHEAD2;
	SPIData m_spiDataHEAD1;

	
	
	
	CString m_HEAD2LaserIP;
	int m_HEAD2LaserPort;
	CString m_HEAD1LaserIP;
	int m_HEAD1LaserPort;


	bool isGuideBeamHEAD2;
	bool isGuideBeamHEAD1;
	


public:
	

	HBITMAP m_mLedGray;
	HBITMAP m_mLedGreen;

	CButtonST	m_btnOk;
	CButtonST	m_btnCancel;



	CDlgSPIDualLaser(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSPIDualLaser();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SPI_LASER_DUAL };

	

	void SetSPILaserData();
	void ShowLaserDlg();
	void LedOnOff(UINT uid, int flag);

	SPIData GetSPIDataHEAD2();
	SPIData GetSPIDataHEAD1();

	void SendSPIHEAD2DataFromMRK(SPIData data);
	void SendSPIHEAD1DataFromMRK(SPIData data);


	//////////////////////////////Laser Protocol True Pulse Nano 2030 ///////////////////



	void UINT32ToByteArray(UINT32 intData,BYTE* byteArr);
	void UINT16ToByteArray(UINT16 intData,BYTE* byteArr);
	UINT32 ByteArrayToUINT32(BYTE* byteArr);
	UINT16 ByteArrayToUINT16(BYTE* byteArr);
	void SetCheckSum(BYTE* packet, const int arrayLength);


	// 4.3 Interface Control Command Reference
	int SetRs232BaudRate(UINT32 baudrate, CCommunicate* pSocket);
	int GetRS232BaudRate( CCommunicate* pSocket);

	int SetLaserInterfaceControlMode(UCHAR mode, CCommunicate* pSocket);
	int GetLaserInterfaceControlMode( CCommunicate* pSocket);

	int SetLaserControlSignals(UINT16 state, CCommunicate* pSocket);
	int GetLaserControlSignals(CCommunicate* pSocket);

	int SetAnalogueCurrentSetPoint(UINT16 point,UINT16 value, CCommunicate* pSocket);

	int GetAnalogueSignals(UINT16 point, CCommunicate* pSocket);
	
	// 4.4 Pulse Generator Command Reference
	int SetPulseWaveform(UINT16 pulseWaveform, CCommunicate* pSocket);
	int GetPulseWaveform(CCommunicate* pSocket);


	int SetPulseRate(UINT32 rate, CCommunicate* pSocket);
	int GetPulseRate( CCommunicate* pSocket);

	
	int SetPulseBurstLength(UINT32 burstLength, CCommunicate* pSocket);
	int GetPulseBurstLength( CCommunicate* pSocket);

	int SetPumpDutyFactor(UINT16 dutyFactor, CCommunicate* pSocket);
	int GetPumpDutyFactor(CCommunicate* pSocket);


	int SetAllPulseGeneratorParameters(UINT16 waveform,UINT32 rate, UINT32 burstLength, UINT16 dutyFactor, CCommunicate* pSocket);
	int GetAllPulseGeneratorParameters(UINT16 waveform, CCommunicate* pSocket);

	int RestartPulseGenerator(UINT16 waveform, CCommunicate* pSocket);

	// 4.5 Monitoring Command Reference 

	int QueryStatusLinesAndAlarms( CCommunicate* pSocket);
	int QueryLaserTemperatures(CCommunicate* pSocket);
	int QueryLaserCurrents(CCommunicate* pSocket);
	int QueryPowerSupplyVoltages(CCommunicate* pSocket);
	int QueryHardwareInterface(CCommunicate* pSocket);
	int QueryOperatingHours(CCommunicate* pSocket);
	int QueryExternalPulseTriggerRepetitionRate(CCommunicate* pSocket);
	int QueryExtendedLaserCurrents(CCommunicate* pSocket);



	// 4.6 Diagnostics Command Reference
	int SetLaserIntoDiagnosisState(CCommunicate* pSocket);
	int GetLaserSerialNumber(CCommunicate* pSocket);
	int GetLaserPartNumber(CCommunicate* pSocket);
	int GetLaserFirmwareDetails(CCommunicate* pSocket);
	int GetLaserDescription(CCommunicate* pSocket);


	//////////////////////////////Laser Protocol True Pulse Nano 2030 ///////////////////

	void ParseHEAD2Data(BYTE* pData,SPIData& spiData);
	void ParseHEAD1Data(BYTE* pData,SPIData& spiData);


	void	SetDelayTime(unsigned int iSecond);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CListBox m_HEAD2LaserLog;
	CListBox m_HEAD1LaserLog;
	afx_msg void OnBnClickedSpiLaserTestBbutton();
	DECLARE_EVENTSINK_MAP()
	void ClickCttextHEAD2Ctrlmode();
	void ClickCttextHEAD2WaveForm();
	void ClickCttextHEAD2Prf();
	void ClickCttextHEAD2Active();
	void ClickCtcheckHEAD2Isconnected();
	void ClickCttextHEAD2Ip();
	void ClickCttextHEAD2Port();
	
	void ClickCtpushGuideBeam();
	void ClickCtpushHEAD2Enable();
	void ClickCtpushHEAD2Trigger();
	afx_msg void OnBnClickedCheckGuidebeamHEAD2();





	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT OnSockReceiveFromSPI(WPARAM wParam, LPARAM lParam);
public:
	void ClickCtpushHEAD1Enable();
	void ClickCtpushHEAD1Trigger();
	void ClickCtpushHEAD1GuideBeam();
	void ClickCttextHEAD1Ctrlmode();
	void ClickCttextHEAD1WaveForm();
	void ClickCttextHEAD1Prf();
	void ClickCttextHEAD1Active();
	void ClickCtpushHEAD2Standby();
	virtual BOOL OnInitDialog();
	void ClickCtpushHEAD1Standby();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedConntect();
	afx_msg void OnBnClickedOk3();
};
