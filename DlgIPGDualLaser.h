#pragma once

#include "NX_SOCKET\SocketManager.h"
#include "../DIALOGEX/UserDialogEx.h"
#include <string>
#include "afxwin.h"
#include "LanSocket.h"
#include "BtnST.h"
#include "FieldParameter.h"
#include "windef.h"

#define TIMER_GET_STATUS_ID_HEAD1              0x0001
#define TIMER_GET_STATUS_ID_HEAD2              0x0002
#define TIMER_DLG_INIT                         0x0003

#define TIMER_IPG_CONNECT_CHECK_HEAD1          0x0004
#define TIMER_IPG_CONNECT_CHECK_HEAD2          0x0005

#define TIMER_IPG_RECONNECT_CHECK_HEAD1        0x0006
#define TIMER_IPG_RECONNECT_CHECK_HEAD2        0x0007


#define TIMER_GET_STATUS_INTERVAL_HEAD1      500 //500ms 에 한번씩 요청
#define TIMER_GET_STATUS_INTERVAL_HEAD2      500 //500ms 에 한번씩 요청




/*typedef struct _LASERSTATUS_
{
	
		bool   bHEAD1_STATUS_POWER_SUPPLY;
		bool   bHEAD1_STATUS_LASER_READY;
		bool   bHEAD1_STATUS_EMISSION;
		bool   bHEAD1_STATUS_GUIDE_LASER;
		bool   bHEAD1_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION;
		bool   bHEAD1_STATUS_HKK_PS_HOT_STOP;
		bool   bHEAD1_STATUS_EXTEMAL_EMISSION_OFF_DURING_EMISSION;
		bool   bHEAD1_WARNINGS_LASER_TEMPERATURE_TOO_HIGH;
		bool   bHEAD1_WARNINGS_LASER_TEMPERATURE_TOO_LOW;
		bool   bHEAD1_WARNINGS_PRR_LOW;
		bool   bHEAD1_WARNINGS_PRR_HIGH;
		bool   bHEAD1_WARNINGS_SERVICE;
		bool   bHEAD1_WARNINGS_WRONG_MODE;
		bool   bHEAD1_WARNINGS_GUIDE_LASER;
		bool   bHEAD1_WARNINGS_FAN_SPEED;
		bool   bHEAD1_ALARM_SYSTEM;
		bool   bHEAD1_ALARM_VOLATGE;
		bool   bHEAD1_ALARM_LASER_TEMPERTURE;
		bool   bHEAD1_ALARM_CRITICAL_ALARM;
		bool   bHEAD1_ALARM_BACK_REFLECTION;
		bool   bHEAD1_ALARM_SAFTY;
		bool   bHEAD1_ALARM_GUIDE_LASER;
		bool   bHEAD1_HK_POWER_SUPPLY_TOO_LOW;


		//2023.08.29 LASER PULSE RATE, LASER ACTIVE POWER 추가. LaserParameter 항목으로 되어있지만 상태로 포함하여 사용.
		double dHEAD2_LASER_PULSE_RATE;
		double dHEAD2_LASER_ACTIVE_POWER;


		void clear()
		{
			


		}
	
} LASERSTATUS;*/
class DataProcessor
{
public:
	static bool ProcessData(const BYTE* data,int size);
	
};

// 소켓통신에 필요한 구조체 역할 ( 클래스와 구조체의 형태는 유사 )
// 레이저 상태 정보를 담아서 소켓통신으로 보내기위해 필요

// GetAirCooledLaserStatus
class SkamLaserStatus
{
public:
	unsigned short Version; //Version of the structure (= 1) // 0

	unsigned short InstalledStatus; // 2

	unsigned short ModeIndex; // 6
	float Frequency; // 8
	float AveragePower; // 12
	float Power; // 16

	unsigned int MainStatus; // 20
	unsigned int Alarms; // 24
	unsigned int SystemAlarms; // 28
	unsigned int ExtendedAlarms; // 32
	unsigned int Warnings; // 36
	unsigned int Status; // 40
	unsigned int ExtendedStatus; // 44

	float MeasFrequency; // 48
	float PulseDuration; // 52

	float MeasPower; // 56
	float PulseEnergy; // 60
	float PeakPower; // 64

	float AnalogPowerControl; // 68
	float BackReflection; // 72

	float LaserTemperature; // 76
	float DewPointTemperature; // 80
	float Humidity; //84

	unsigned short UserResidual; //88
	unsigned short Reserved;    //90
	
	// 0으로 초기화
	void claer()
	{
	Version=0; //Version of the structure (= 1) // 0

	InstalledStatus=0; // 2

	ModeIndex=0; // 6
	Frequency=0.0; // 8
	AveragePower=0.0; // 12
	Power=0.0; // 16

	MainStatus=0; // 20
	Alarms=0; // 24
	SystemAlarms=0; // 28
	ExtendedAlarms=0; // 32
	Warnings=0; // 36
	Status=0; // 40
	ExtendedStatus=0; // 44

	MeasFrequency=0.0; // 48
	PulseDuration=0.0; // 52

	MeasPower=0.0; // 56
	PulseEnergy=0.0; // 60
	PeakPower=0.0; // 64

	AnalogPowerControl=0.0; // 68
	BackReflection=0.0; // 72

	LaserTemperature=0.0; // 76
	DewPointTemperature=0.0; // 80
	Humidity=0.0; //84

	UserResidual=0; //88
	Reserved=0;    //9
	}
};

class HPPLLaserStatus
{
public:
	unsigned short Version; //Version of the structure (= 1) // 0

	unsigned short InstalledStatus; // 2

	unsigned short ModeIndex; // 6
	float Frequency; // 8
	float AveragePower; // 12
	float Power; // 16

	unsigned int MainStatus; // 20
	unsigned int Alarms; // 24
	unsigned int SystemAlarms; // 28
	unsigned int ExtendedAlarms; // 32
	unsigned int Warnings; // 36
	unsigned int Status; // 40
	unsigned int ExtendedStatus; // 44

	float MeasFrequency; // 48
	float PulseDuration; // 52

	float MeasPower; // 56
	float PulseEnergy; // 60
	float PeakPower; // 64

	float AnalogPowerControl; // 68
	float BackReflection; // 72

	float LaserTemperature; // 76
	float DewPointTemperature; // 80
	float Humidity; //84

	unsigned short UserResidual; //88
	unsigned short Reserved;    //90
	
	// 0으로 초기화
	void claer()
	{
	Version=0; //Version of the structure (= 1) // 0

	InstalledStatus=0; // 2

	ModeIndex=0; // 6
	Frequency=0.0; // 8
	AveragePower=0.0; // 12
	Power=0.0; // 16

	MainStatus=0; // 20
	Alarms=0; // 24
	SystemAlarms=0; // 28
	ExtendedAlarms=0; // 32
	Warnings=0; // 36
	Status=0; // 40
	ExtendedStatus=0; // 44

	MeasFrequency=0.0; // 48
	PulseDuration=0.0; // 52

	MeasPower=0.0; // 56
	PulseEnergy=0.0; // 60
	PeakPower=0.0; // 64

	AnalogPowerControl=0.0; // 68
	BackReflection=0.0; // 72

	LaserTemperature=0.0; // 76
	DewPointTemperature=0.0; // 80
	Humidity=0.0; //84

	UserResidual=0; //88
	Reserved=0;    //9
	}
};
/*struct SkamLaserStatus
{
	//enum LasersState
	//{
		unsigned short Version; //Version of the structure (= 1) // 0

		unsigned short InstalledStatus; // 2

		unsigned short ModeIndex; // 6
		float Frequency; // 8
		float AveragePower; // 12
		float Power; // 16

		unsigned int MainStatus; // 20
		unsigned int Alarms; // 24
		unsigned int SystemAlarms; // 28
		unsigned int ExtendedAlarms; // 32
		unsigned int Warnings; // 36
		unsigned int Status; // 40
		unsigned int ExtendedStatus; // 44

		float MeasFrequency; // 48
		float PulseDuration; // 52

		float MeasPower; // 56
		float PulseEnergy; // 60
		float PeakPower; // 64

		float AnalogPowerControl; // 68
		float BackReflection; // 72

		float LaserTemperature; // 76
		float DewPointTemperature; // 80
		float Humidity; //84

		unsigned short UserResidual; //88
		unsigned short Reserved;    //90


	//}statusType;
	/*enum LasersState
	{
		UserResidual,
	}statusType;
};
*/
class CIPGLaserPulseNanoEthernet : public CLanSocket
{
private:
	BYTE m_byteBuffer[MAX_BUFFER+1];
	
	
public:
	
	CIPGLaserPulseNanoEthernet(CString owner, CWnd* pWnd) : CLanSocket( owner, pWnd)
	{
		
	}
	

	
	
	virtual void OnReceive(int nErrorCode);
	virtual char* ReadData();
	virtual UINT WriteData(BYTE *SendString, DWORD Stringlength);

	int GetPortNum();
	CString GetIPAddress();
	int GetRevSize();
	int nRevSize;
	

};

// CDlgIPGDualLaser 대화 상자입니다.

class CDlgIPGDualLaser : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgIPGDualLaser)

public:
		// 소켓 프로토콜 파트
	CCommunicate* m_pLaserHEAD2;
	CCommunicate* m_pLaserHEAD1;

	CString m_strSiteName;

	SkamLaserStatus st_SkamLaserStatusOfHEAD1;
	SkamLaserStatus st_SkamLaserStatusOfHEAD2;

	int SetHEAD2PatternData(SkamLaserStatus KOEM_PATTERN_DATA);
	int SetHEAD1PatternData(SkamLaserStatus koemPatternData);

	SkamLaserStatus GetHEAD2PatternDataOfKoem(void);
	SkamLaserStatus GetHEAD1PatternDataOfKoem(void);
	void SetDelayTime(unsigned int iSecond);
	HBITMAP m_mLedGray;
	HBITMAP m_mLedGreen;
	void LedOnOff(UINT uid,int flag);
	CDlgIPGDualLaser(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgIPGDualLaser();

	BOOL bHEAD1Connect;
	BOOL bHEAD2Connect;

	BOOL bHEAD1DataRcvFlag;
	BOOL bHEAD2DataRcvFlag;

	BOOL bDlgInitFlag;

	int  nErrorID;
	
	void SendIPGHEAD2DataFromMRK(IPGData data);
	void SendIPGHEAD1DataFromMRK(IPGData data);
	void SendPowerSet(int val);
	void SendFreqSet(int val);

	//SkamLaserStatus* st_SkamLaserStatusOfHEAD1;
	//SkamLaserStatus* st_SkamLaserStatusOfHEAD2;
	unsigned short CRC16(unsigned char *data, int dataSize);
	void HEAD1classification();
	void HEAD2classification();

	void UINT32ToByteArray(UINT32 intData,BYTE* byteArr);
	void UINT32ToByteArrayLittleEndian(UINT32 intData,BYTE* byteArr);
	void UINT16ToByteArray(UINT16 intData,BYTE* byteArr);
	void UINT16ToByteArrayLittleEndian(UINT16 intData,BYTE* byteArr);


	void floatToByteArray32(float floatData, BYTE* byteArr);
	float byteArrayToFloat32(const BYTE* byteArr);
	void floatToByteArray16(float floatData, BYTE* byteArr);
	float byteArrayToFloat16(const BYTE* byteArr);

	void intToByteArray16(int intData, BYTE* byteArr);
	int byteArrayToint16(const BYTE* byteArr);

	void intToByteArray32(int intData, BYTE* byteArr);
	int byteArrayToint32(const BYTE* byteArr);
	int SetLaserControlbits(UINT16 state, CCommunicate* pSocket);





	UINT32 ByteArrayToUINT32(BYTE* byteArr);
	UINT16 ByteArrayToUINT16(BYTE* byteArr);
	void SetCheckSum(BYTE* packet, const int arrayLength);

	
	int SetPulseRate(UINT32 rate, CCommunicate* pSocket);
	int SetPower(UINT32 rate, CCommunicate* pSocket);
	
	int SetGuideLaser(UINT16 on_off, CCommunicate* pSocket);
	int SetEmission(UINT16 on_off, CCommunicate* pSocket);
	int SetPSMode(UINT16 on_off, CCommunicate* pSocket);
	int Setmodulation(UINT16 on_off, CCommunicate* pSocket);
	int Reset(CCommunicate* pSocket);

	int GetAirCooledLaserStatus(CCommunicate* pSocket);

	void ParseHEAD2Data(BYTE* pData, int nSize);
	void ParseHEAD1Data(BYTE* pData, int nSize);
	void CDlgIPGDualLaser::Bitcheck(BYTE* data,int size);

	void ShowLaserDlg();

	

	CListBox m_HEAD2LaserLog;
	CListBox m_HEAD1LaserLog;

	IPGData GetIPGDataHEAD2();
	IPGData GetIPGDataHEAD1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_IPG_LASER_DUAL };

private: 


	
	SkamLaserStatus m_stPatternDataOfHEAD2;
	SkamLaserStatus m_stPatternDataOfHEAD1;

	IPGData m_IPGDataHEAD2;
	IPGData m_IPGDataHEAD1;

	CString m_HEAD2LaserIP;
	int m_HEAD2LaserPort;
	CString m_HEAD1LaserIP;
	int m_HEAD1LaserPort;




	bool isGuideBeamHEAD2;
	bool isGuideBeamHEAD1;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBtnFreqSet();
	afx_msg void OnBtnPwrSet();
public:

	CButtonST	m_btnOk;
	CButtonST	m_btnCancel;

	afx_msg LRESULT OnSockReceiveFromIPG(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedConntect();
	virtual BOOL OnInitDialog();

	
	DECLARE_EVENTSINK_MAP()
	//HEAD1
//	void ClickCtpushHEAD1GuideBeam();
	void ClickCtpushHEAD1Retset();
	void ClickCtpushHEAD1Emission();
//	void ClickCtpushHEAD1modulation();
//	void ClickCttextHEAD1Prf();
//	void ClickCttextHEAD1Power();
	//HEAD2
	void ClickCtpushHEAD2GuideBeam();
	void ClickCtpushHEAD2Retset();
	void ClickCtpushHEAD2Emission();
	void ClickCtpushHEAD2modulation();
	void ClickCttextHEAD2Prf();
	void ClickCttextHEAD2Power();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	void OnDblclickCtpushHEAD2Reset();
//	void OnDblclickCtpushHEAD2Enable();
	void OnClickCtpushHEAD2Modulation();
	void OnClickCtpushHEAD2GuideBeam();
	void OnClickCttextHEAD2Prf();
	void ClickCttextHEAD1Prf();
	void ClickCttextHEAD1Active();
	void ClickCttextHEAD2Active();
	void ClickCtpushHEAD1Modulation();
	void ClickCtpushHEAD2Reset();
	void ClickCtpushHEAD2Enable();
	void ClickCtpushHEAD1GuideBeam();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnLbnSelchangeSpiHead1LaserLog();
	void ClickCtpushHead1PowerSupply();
	void ClickCtpushHead1Enable2();
	void ClickCtpushHead1PowerSupply2();
	void ClickCtpushHead1Modulation2();
	void ClickCtpushHead1GuideBeam3();
};
