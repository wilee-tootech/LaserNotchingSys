// Dsp.h: interface for the CDsp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSP_H__C0CE2793_8646_41D7_AC26_73FAEC363EA1__INCLUDED_)
#define AFX_DSP_H__C0CE2793_8646_41D7_AC26_73FAEC363EA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#include <AFXTEMPL.H>
#include "Parameter.h"
#include "Vector.h"
#include "define.h"
#include "DualScannerParameter.h"

#ifdef	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#ifdef	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#pragma comment( lib, "RTC4DLL.lib") 
#endif


#ifdef	_RTC4eth_
//#include ".\Include\Rtc4eth\RTC4ethexpl.h"
//#include ".\Include\Rtc4eth\RTC4ethimpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#include ".\Include\Rtc4eth\RTC4ethimpl.h"
//#include ".\Include\Rtc4eth\RTC4ethexpl.h"

#pragma comment( lib, "RTC4ethDLL.lib") 
#endif

#ifdef _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4impl.h"
#pragma comment( lib, "SCANalone4.lib") 
//#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif

#ifdef	_RTC5_
#include ".\Include\Rtc5\RTC5impl.h"
#pragma comment( lib, "RTC5DLL.lib") 
#endif

#ifdef	_RTC6_
#include ".\Include\Rtc6\RTC6impl.h"
#pragma comment( lib, "RTC6DLL.lib") 
#endif

/******************************** KOEM I/O Define ****************************/

//#ifdef	_RTC_Test_
//#define RTC_SIG_I_LASER_ON		0x05
//#define RTC_SIG_I_FIRST_TAB		0x06
//#define RTC_SIG_I_EMG_STOP		0x07
//#define RTC_SIG_I_NG_TAG		0x08
//#else 
#define RTC_SIG_I_LASER_ON		   0x00
#define RTC_SIG_I_FIRST_TAB		   0x01
#define RTC_SIG_I_EMG_STOP		   0x02
#define RTC_SIG_I_SKIP_MODE		   0x03
#define RTC_SIG_I_AUTO_CHANGE      0x04
#define RTC_SIG_I_DOOR_INTERLOCK	0x06
#define RTC_SIG_I_SCRAP_SENSOR	   	0x07
#define RTC_SIG_I_NOTCHING_SENSOR1	   0x08
#define RTC_SIG_I_NOTCHING_SENSOR2	   0x09

#define RTC_SIG_I_NG_TAPE			0x02
#define RTC_SIG_I_ACCPOS			0x03
#define RTC_SIG_I_ONE_PATTERN		0x04
#define RTC_SIG_I_PLC_MODE			0x05	// 제어 못하도록 막는용도
#define RTC_SIG_I_ZIG_CLEAN			0x06
#define RTC_SIG_I_NOTCHING_SENSOR_A	0x0A
#define RTC_SIG_I_NOTCHING_SENSOR_B	0x0B


#define RTC_SIG_I_MASK0_SKIP_MODE	1
#define RTC_SIG_I_MASK1_SKIP_MODE	14
//#endif


//#define RTC_SIG_O_READY  		0x00
//#define RTC_SIG_O_PROGRESS		0x01
//#define RTC_SIG_O_ALARM			0x02
//#define RTC_SIG_O_DEVICE_OK 	0x03

#define RTC_SIG_O_READY  		0x00

#ifdef	_RTC_Test_
#define RTC_SIG_O_ALARM			0x01 // 테스트 장비 IPG LASER BEAM 새는것 용으로 사용
#define RTC_SIG_O_PROGRESS		0x02
#define RTC_SIG_O_ALARM			0x05
#else
#define RTC_SIG_O_STANDBY		0x01 // 테스트 장비 IPG LASER BEAM 새는것 용으로 사용
#define RTC_SIG_O_ALARM		    0x01 // 

#define RTC_SIG_O_PROGRESS		0x02
#endif


#define RTC_SIG_O_FIRST_TAB 	0x03
#define RTC_SIG_O_ACTUAL_FIRST_TAB 	0x0F

#define RTC_SIG_O_INTER_LOCK	0x04
#define RTC_SIG_O_EMISSION_ENABLE	0x05
#define RTC_SIG_O_REMOTE_KEY_SWITCH		0x06
#define RTC_SIG_O_REMOTE_START_BUTTON	0x07

//--------------------------------------------------------------------------------

#ifdef	_RTC4eth_
#define RTCIO_O_LASER_ENABLE		0
#define RTCIO_O_GUIDEBEAM_ENABLE	1
#define RTCIO_O_LATCH           	3
#define RTCIO_O_MO              	4
#define RTCIO_O_EMERGENCY           5
#define RTCIO_O_LASER_SHUTTER		5
#define RTCIO_O_IPG_GATE			8
#endif


#ifdef	_RTC_Test_
#define RTCIO_O_MO					0
#define RTCIO_O_GUIDEBEAM_ENABLE	1
#define RTCIO_O_LATCH           	3
#define RTCIO_O_LASER_ENABLE        4
#define RTCIO_O_EMERGENCY           5
#define RTCIO_O_LASER_SHUTTER		5
#define RTCIO_O_IPG_GATE			8
#endif

#define LATCH_DELAY					100

#define PARA_INDEX_UNFLAG				0
#define PARA_INDEX_FLAG					1
#define PARA_INDEX_UNFLAG_INOUT			2
#define PARA_INDEX_FLAG_EXT				3
#define PARA_INDEX_UNFLAG_INOUT_EXT		4
#define PARA_INDEX_UNFLAG_EXT			5
#define PARA_INDEX_DUMMY				6
#define PARA_INDEX_SIMUL				7



#define SIMULATION_ENCODER_OFF			0
#define SIMULATION_ENCODER_X			1
#define SIMULATION_ENCODER_Y			2	
#define SIMULATION_ENCODER_XY			3


//------ Variable Mode -------/
#define NORMAL_MARK_MODE 0
#define TIMED_MARK_MODE  1
#define SPEED_MARK_MODE  2

#define LASER_PULSE_UNIT               64.0
#define PI	3.1415926535


typedef struct 
{

	BOOL bBusy1;
	BOOL bBusy2;
	BOOL bLoad1;
	BOOL bLoad2;
	BOOL bReady1;
	BOOL bReady2;
	BOOL bUsed1;
	BOOL bUsed2;
	
	void clear()
	{
		bBusy1 = bBusy2 = bLoad1 = bLoad2 = bReady1 = bReady2 = bUsed1 = bUsed2 = 0;
	}

} TListExeStat;

typedef struct 
{

	UINT m_unGalvoXStat;
	long m_lGalvoXPos;
	UINT m_unGalvoYStat;
	long m_lGalvoYPos;

} TGalvoInfo;

typedef struct 
{
	BOOL bPosAckX;
	BOOL bPosAckY;
	BOOL bTempStat;
	BOOL bPwrStat;

} THeadInfo;


const UINT GET_GAlVANO_X = 7;
const UINT GET_GAlVANO_Y = 8;

const UINT unResetCompletely( UINT_MAX );


class CDsp  
{
public:
	THeadInfo    m_tHeadInfo;
	TListExeStat m_tListExeStat;
	int GetPosY();
	int GetPosX();
	void GetHeadStat();
	//void OutputIO(unsigned int bit, BOOL value);
	BOOL LoadCorrectionFile(double iMasterX, double iMasterY, double iSlaveX, double iSlaveY, double FieldAngle);
	void Set_Angle(double dAngle);
	void ListCountPlus();
	void SetListCount(int listCount);
	int GetListCount();
	void SetGotoXY(long x, long y);
	void SetParameterDataList();	
	void SetParameterNumber(int number);	
// 2007.06.25  
	void LaserOff();
	void LaserOn();
	int  GetBoardCount();


	void SetLaserErrorToHandler();
	ULONG m_temp,m_temp2;
//	void SetHandlerSignal();
	void SetChipNumber(int iNumber);
	CDsp();
	virtual ~CDsp();
	int	 GetMarkStatus();// 커팅 상태 가져오기
	int  GetMarkStatusHEAD2();
	int  GetMarkStatusHEAD1();
	BOOL InitDsp(); // Dsp 초기화 시키기
	void DestoryDsp();
	void StopAutoMarking();
	void StartAutoMarking();
	void StartManualMarking();
	void SetOffsetData(int iMasterX, int iMasterY, int iSlaveX, int iSlaveY); // Field 값이기 때문에 X, Y는 integer이어야 마땅함.
	void SetOffsetData(int iMasterX, int iMasterY);
	void SetScaleData(int iMasterXScale, int iMasterYScale, int iSlaveXScale, int iSlaveYScale); // X, Y의 Scale을 결정? 기존에 사용되다가 지금은 안됨
	void SetScaleData(int iMasterXScale, int iMasterYScale);
	void SetCalibrationData(CPoint (*MasterCalData)[MAX_CAL_DATA], CPoint (*SlavecalData)[MAX_CAL_DATA], short sNumberOfX, short sNumberOfY); // Master, Slave 두번 setting
	void SetCalibrationData(CPoint (*MasterCalData)[MAX_CAL_DATA], short sNumberOfX, short sNumberOfY); // Master, Slave 두번 setting
	void SetBinNumber(); // 빈 갯수 셋팅
//	void SetBinData(int *binData); // 빈 데이터 셋팅
	void SetBinData();
	void SetParameterData(); // 구조체 자체 받아서 파라미터 데이터 셋팅
	void SetObjectNumber(); // m_iNumberOfObj를 Dsp 메모리 번지에 Setting하기- void CDsp::SetObjNum(int objnum)
	void SetImageParameter(int iIntervalSize, int iDwellTime, int iLineMoveDelayTime); // Image의 경우 커팅시 필요한 파라미터가 추가됨
	// 마지막 파라미터인 markingType은 결정되어서 오기
	// 실제 커팅 데이타 정보를 셋팅, 맨 마지막 markingType은 TEXT, HPGL 여부가 아닌 VECTOR/PIXEL AND Dual Head에서의 MARKING/NOMARKING 여부에 따라 결정
	void SetVectorObjectData(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex);
	void SetPixelObjectData(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex);
//	void SetObjInfo(int iType, int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition);
	void SetVectorObjInfo(int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition);
	void SetPixelObjInfo(int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition);
	void SetFieldValue(double maxField,double maxMM);
	void SetDspFileName(char *fileName); // Dsp.out 파일 이름 다운시키기
	CString GetVersion(); // 특정번지 읽어서 return만 시킴. Dsp Pgm의 버전 읽기용

	// 레이저 컨트롤을 Dsp에서 담당할 경우 Only On/Off만 받음 // 주소 셋팅은 이곳에서 직접
	// 실제 사용된 기억은 X
	void ShutterOn();
	void ShutterOff();
//	void SetMasterChipOffset(CList<Vector, Vector> *ltMasterOffset);
//	void SetSlaveChipOffset(CList<Vector, Vector> *ltSlaveOffset);
	void SetMasterChipOffset(Vector *ltMasterOffset, int iNumberOfVector);
	void SetSlaveChipOffset(Vector *ltSlaveOffset, int iNumberOfVector);

	static CDsp *GetInstance();

	

	// Version 
	UINT GetDllVer();
	UINT GetHexVer();
	UINT GetRtcVer();
	UINT GetSerialNum();

private:
	int  m_nListSize;
	int  m_nBoardIdx;
	
	CHAR m_caCfgPath[MAX_PATH];

	BOOL m_bInit;
	// Version 
	UINT m_unDllVer;
	UINT m_unHexVer;
	UINT m_unRtcVer;
	UINT m_unSerialNum;

	int m_iCommandAddress; // 접근 메모리
	int m_iCount; // 데이터 갯수
	int m_iData; // 실제 데이터
	int m_iNumberOfObj; // 오브젝트 갯수
	int m_iVectorDataPosition; // 데이터 번지
	int m_iNumberOfParameter; // 파라미터 갯수
	int m_iNumberOfBinData; // 빈 갯수
	static CDsp *m_pDsp; // 유일한 instance
	BOOL m_bInitialStatus;
	BOOL m_bAnalogPowerSet;
	
	int m_iListConunt;	// 내린 리스트 갯수
	int m_iEncoderPos;

//2017.04.04 jjsjong RTC5 Convertion
	int m_nCardNo;
	
	double m_dPreFlyY;
	double m_dPreFlyX;

	int n_Simulate_Encode;
	int n_ScannerVariableMode; // Scanner Variable Mode

	double m_dSpeedScale;
	double m_dtimed_marktime;
	double m_dApplySpeed;
	int m_iChangeLineSpeedIndex;
	double m_dSettedCurrMarkSpeed;
	
	UINT m_unErroNo;

	BOOL m_bFirstStart;
	BOOL m_bFirstStartHEAD1;
	BOOL m_b1stFlagStep;
	BOOL m_bFlipHead1;
	BOOL m_bFlipHead2;
	
	double m_maxFieldHEAD2;
	double m_maxMMHEAD2;
	double m_maxFieldHEAD1;
	double m_maxMMHEAD1;


private:
	friend class CDlgDspTest;

//	void SetBinItem(int *binNumber);
	void SetBinItem(CString binNumber);
	// Error
	UINT GetErr();

	//Board Initialize
	BOOL LoadProgFile();
	BOOL LoadCorrectFile();	
	void SelCorrectTable();


	
public:
	void SetFlipHead1(BOOL bFlag);
	void SetFlipHead2(BOOL bFlag);


	void SetFirstStart(BOOL  bFlag);
	void SetFirstStartHEAD1(BOOL  bFlag);

	void SetDelay(unsigned int iSecond);
	void OutputIO(unsigned int bit, bool value);
	void nOutputIO(int nCardNo,unsigned int bit, bool value);
	void OutputIOList(unsigned int bit, bool value);
	
	void GetEncode(long & x, long & y);
	void GetEncodeHEAD2(long & x, long & y);
	void GetEncodeHEAD1(long & x, long & y);

	void ReadEncodeHEAD1(long &encoder0_0, long &encoder1_0,long &encoder0_1,long &encoder1_1);
	void ReadEncodeHEAD2(long &encoder0_0, long &encoder1_0,long &encoder0_1,long &encoder1_1);
	
	
	
	

	void ResetRTC(void);
	void SetSimulate_Encoder(int nMode);
	int GetSimulate_Encoder(void);
	void SetControlMode(unsigned int mode);
	bool GetInitialStatus(void);
	void StopExecution(void);
	void Disable_Laser(void);
	void Enable_Laser(void);
	void SetReady(void);
	void SetParameterDataList_Change(void);
	void SetParameterDataList_Change_ByDistance(double dBaseDistance, double dApplyDistance);
	void Set_Matrix(double cs, double sn);

	void SetMatrixHEAD2(double cs, double sn);
	void SetMatrixHEAD1(double cs,double sn);

	void SetGotoXYHEAD2(double x,double y);  
	void SetGotoXYHEAD1(double x,double y);    

	void EnableLaserHEAD2();
	void EnableLaserHEAD1();

	void DisableLaserHEAD2();
	void DisableLaserHEAD1();



	void StopExcutionHEAD2();
	void StopExcutionHEAD1();

	void WriteIOHEAD2(unsigned int bit, int value);
	void WriteIOHEAD1(unsigned int bit, int value);

	void SetStartListHEAD2(UINT listNo);
	void SetStartListHEAD1(UINT listNo);

	void ClearFlyOverflowHEAD2(UINT mode = 15); // mode 15 => clear XY Overflow
	void ClearFlyOverflowHEAD1(UINT mode = 15);   // mode 15 => clear XY Overflow

	void SetFlyLimitsHEAD2(double xMin, double xMax, double yMin, double yMax);
	void SetFlyLimitsHEAD1(double xMin, double xMax, double yMin, double yMax);

	void SetFlyXHEAD2(double scaleX);
	void SetFlyXHEAD1(double scaleX);

	//(const UINT CardNo, const double ScaleX, const double ScaleY, const LONG EncX, const LONG EncY);
	void Activivate_Fly_2d_Encoder(UINT CardNo, double ScaleX, double ScaleY, LONG EncX, LONG EncY);
	
	void SetFlyYHEAD2(double scaleY);
	void SetFlyYHEAD1(double scaleY);

	void JumpAbsHEAD2(double x,double y); //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.
	void JumpAbsHEAD1(double x, double y);  //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.

	void MarkAbsHEAD2(double x, double y); //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.
	void MarkAbsHEAD1(double x, double y);	 //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.

	void FlyReturnHEAD2(double x,double y); //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.
	void FlyreturnHEAD1(double x,double y);	  //실제 사이즈 (mm) 단위로 입력하세요 함수 내에서 필드 사이즈로 변경됩니다.

	void OutputIOListHEAD2(unsigned int bit,bool value);
	void OutputIOListHEAD1(unsigned int bit,bool value);

	void WaitForEncoderHEAD2(long value, int encoderNo);
	void WaitForEncoderHEAD1(long value, int encoderNo);

	void WaitForEncoderModeHEAD2(long value, int encoderNo, int mode);
	void WaitForEncoderModeHEAD1(long value, int encoderNo, int mode);

	void SetEndOfListHEAD2();
	void SetEndOfListHEAD1();

	UINT GetMarkingInfoHEAD2();
	UINT GetMarkingInfoHEAD1();


	TListExeStat ReadStatusHEAD2();
	TListExeStat ReadStatusHEAD1();


	TListExeStat ReadStatus();
	TListExeStat NReadStatus(UINT headNo);

	void FlyReturn(long x, long y);
	void N_Fly_Return(UINT cardNo, long x,long y);
	void N_Fly_Return(UINT cardNo, double x,double y, int unit);
	
	void SetFlyY(double y);
	void SetFlyX(double x);


	void Mark_Abs(int x, int y);
	void N_Mark_Abs(UINT cardNo,int x, int y);
	void N_Mark_Abs(UINT cardNo,double x, double y, int unit);

	void N_Mark_Rel(UINT cardNo,int x, int y);
	void N_Mark_Rel(UINT cardNo,double x, double y, int unit);

	void N_Jump_Rel(UINT cardNo,int x, int y);
	void N_Jump_Rel(UINT cardNo,double x, double y, int unit);

	void Jump_Abs(int x, int y);

	void N_Jump_Abs(UINT cardNo, int x,int y);
	void N_Jump_Abs(UINT cardNo, double x,double y, int unit);

	void Timed_Mark_Abs(int x, int y, double time);
	void Timed_Mark_Abs(double x, double y, double time, int unit);

	void Timed_Jump_Abs(int x, int y, double time);
	void Timed_Jump_Abs(double x, double y, double time, int unit);
	
	void N_Timed_Mark_Abs(UINT cardNo,int x, int y, double time);
	void N_Timed_Mark_Abs(UINT cardNo,double x, double y, double time, int unit);

	void Timed_Mark_Rel(int x, int y, double time);
	void Timed_Jump_Rel(int x, int y, double time);

	void N_Timed_Mark_Rel(UINT cardNo,int x, int y, double time);
	void N_Timed_Mark_Rel(UINT cardNo,double x, double y, double time, int unit);

	void N_Timed_Jump_Rel(UINT cardNo,int x, int y, double time);
	void N_Timed_Jump_Rel(UINT cardNo,double x, double y, double time, int unit);

	void N_Timed_Jump_Abs(UINT cardNo,int x, int y, double time);
	void N_Timed_Jump_Abs(UINT cardNo,double x, double y, double time, int unit);

	void SetGotoXYHEAD2(double x,double y, int unit);  
	void SetGotoXYHEAD1(double x,double y, int unit);    


	void LaserSignalOn(void);
	void LaserSignalOff(void);
	void SetAnalogOutPut1(double dVoltage);
	void SetAnalogOutPut2(double dVoltage);

	void SetAnalogPowerUse(bool bUseAnalog);
	bool GetAnalogPowerUse(void);
	unsigned short ReadIoPort(void);
	unsigned short n_ReadIoPort(int nCardNo);
	bool GetIoStatus(unsigned short bit);
	bool n_GetIoStatus(UINT cardNo, unsigned short bit);
	bool GetInputValue(int nBit);
	bool nGetInputValue(UINT cardNo,int nBit);

	unsigned short GetIoStatus(void);
	unsigned short n_GetIoStatus(UINT cardNo);

	void SetSpeedScale(double dScale);
	double GetSpeedScale(void);
	double Get_timed_Markabs(void);
	void SetVariableMode(int nVariableMode);
	void activate_fly_xy(double dScaleX, double dScaleY);
	void SetChangeLineSpeedIndex(int iLineSpeedIndex);
	void ClearOverflow(void);
	void Set1stFlagStep(bool bFlag);
	bool Get1stFlagStep(void);
	double GetFlagMarkSpeedDiff(int index);
	double GetNonFlagMarkSpeedDiff(int index);
	double GetNonFlagLineMarkSpeedDiff(int index);
	void SetMarkSpeed(double dMarkSpeed);
	double GetSettedMarkSpeed();




	void nSetRTCJumpSpeed(UINT cardNo,double jumpSpeed);
	void nSetRTCMarkSpeed(UINT cardNo,double markSpeed);
	void nSetScannerParameter(UINT cardNo, double scannerSpeed, SingleScannerParameter scannerParameter);
	void nSetFrequency(UINT cardNo, double dFreq, double dPulseWidth);

	void WriteDA1(double voltage);
	void WriteDA2(double voltage);


	void nWriteDA1List(UINT cardNo,double voltage);
	void nWriteDA2List(UINT cardNo,double voltage);

	void NOutputIOList(UINT headNo, unsigned int bit, bool value);


	UINT nGetListSpace(UINT CardNo);
	UINT nGetInputPointer(UINT CardNo);
	void nSetInputPointer(UINT CardNo, UINT Pos);
	void nSetStartLisPos(UINT CardNo, UINT listNo,UINT Pos);

	void nListRepeat(UINT CardNo);
	void nListUntil(UINT CardNo, UINT Number);

	void nListContinue(UINT CardNo);
	void nListJumpRel(UINT CardNo, long Pos);
	void nListJumpPos(UINT CardNo, long Pos);
	void nIf_Cond(const UINT CardNo, const UINT Mask1, const UINT Mask0);
	void nIf_not_Cond(const UINT CardNo, const UINT Mask1, const UINT Mask0);

	UINT nGetMarkingInfo(UINT CardNo);

	void nExecuteList(UINT CardNo , UINT ListNo);
	void nGetstatus(UINT CardNo, UINT &Status, UINT &Pos);

	void nSaveAndRestartTimer(UINT CardNo);
	double nGetTime(UINT CardNo);

	UINT nGetListSize(UINT CardNo);

	int nGetPosY(UINT CardNo);
	int nGetPosX(UINT CardNo);

	void nPauseList(UINT CardNo);
	void nRestartList(UINT CardNo);

	


};

#endif // !defined(AFX_DSP_H__C0CE2793_8646_41D7_AC26_73FAEC363EA1__INCLUDED_)
