#ifndef _RUN_MGR_H_
#define _RUN_MGR_H_

#include "RunningDefine.h"
#include "../Include/EXTERN/TimeCounter.h"
#include "../MainFrm.h"




//Class 등록
//{{
//class CRunningTray;

//}}

class CRunMgr
{
public:
	CRunMgr(void);
	~CRunMgr(void);


private:
	

	RUN_MODE			m_eRunMode;								//장비상태
	SELECT_MANUAL_MODE	m_eSelectManualMode;

	BOOL				m_bInitComplete;						//초기화 여부
	BOOL				m_bStartInitialize;
	BOOL				m_bEndInitalize;

	DEF_RUN				m_stMain;								//메인시퀀스 관리
	DEF_RUN				m_stSubSeqMgr;							//메인시퀀스 관리
	//CRunningBase*		m_pRunningModule[SEQ_MODULE_ID_MAX];	//각 모듈 시퀀스 관리

	CTimeCounter		m_MainErrorTimeCheck;
	CTimeCounter		m_SubErrorTimeCheck;
	CTimeCounter*		m_pGatheringTimeCheck;

	BOOL				m_bJobEnd;
	//////////////////////////////////////////////////////////////////////////

	//Body
	int m_nBodyMoveWorkPosStep;


	//Laser
	int m_nLaserSupplyStep;

	//////////////////////////////////////////////////////////////////////////

	BOOL m_bCheckLaserParam;


	//////////////////////////////////////////////////////////////////////////
	

protected:

public:
	BOOL m_bListCheck;
	double m_PLCTotalLength;
	UINT_PTR m_nTimerID;
    HWND m_hWnd;

	IniUtil _iniUtil;

	CFileMgr FileMgr;
	int m_nChattering;

	//2025.01.14 jjsjong 추가
	int m_nEncoderSumCount;
	UINT m_uJumpPos;
	UINT m_uJumpPos2;
	UINT m_u2ndFlagPos;
	double m_dNGNochingLength;

	BOOL m_bThreadAlive;
	BOOL m_bThreadAlive2;
	HANDLE  m_hThread;
	HANDLE  m_hHEAD2Thread;

	BOOL m_StopBtnClicked;

	BOOL m_bReStartProgramHEAD1;
	BOOL m_bReStartProgramHEAD2;

	//CRunningModuleInterface m_Interface;

	BOOL					m_bStatusClearCheck;

	int						m_nCheckLaserEncoder;
	int						n_nLaserEncoder;

private:
	void __stdcall CheckDigital(void);
	void __stdcall CheckMotion(void);
	void __stdcall MainSeqCheckError	(DEF_RUN* Run, int a_nTime, int a_nErrNo);
	void __stdcall SubSeqCheckError	(DEF_RUN* Run, int a_nTime, int a_nErrNo);

    BOOL __stdcall StartManualMode(SELECT_MANUAL_MODE a_eSelectManualMode);
    BOOL __stdcall RunManulMode(SELECT_MANUAL_MODE a_eSelectManualMode);


protected:
	void __stdcall Initialize();
	void __stdcall Ready();
	void __stdcall Ready2();
	void __stdcall Stop();
	

	BOOL __stdcall GetModuleStop();
public:
	void StartTimer(HWND hWnd); 
	void StopTimer();   
	void __stdcall Execute();
	void __stdcall Execute2();

	static DWORD WINAPI ExecutePatternSDI_Head1(LPVOID lparam);
	static DWORD WINAPI ExecutePatternSDI_Head2(LPVOID lparam);

	static DWORD WINAPI ExecutePatternSDI_Pouch_Head1(LPVOID lparam);

	static DWORD WINAPI ExecutePatternSDI_Pouch_Head1_Manual(LPVOID lparam);
	
	void __stdcall ModeChange(RUN_MODE a_eRunMode, int a_nErrorNo = 0 , SELECT_MANUAL_MODE a_eSelectManualMode = SELECT_MANUAL_MODE_NONE);
	void __stdcall ButtonSwitch(BUTTON_SW a_eMode);


public:
	RUN_MODE __stdcall GetRunMode		(void);
	BOOL	 __stdcall GetInitialized	(void) { return m_bInitComplete;	};

	void SetDelayTime(unsigned int iSecond);

	BOOL SetJobClear(void);
	void SetRunstatusClear(BOOL bStatus);
	BOOL GetRunstatusClear(void);

	void SetStatusClearVariable(BOOL bStatus);
	BOOL GetStatusClearVariable(void);

	void OffsetApply();

public:

	void	 __stdcall SetLaserParamCheck_NG(BOOL a_bStatus) { m_bCheckLaserParam = a_bStatus;};
	BOOL     __stdcall GetLaserParamCheck(void) { return m_bCheckLaserParam;};

};


extern CRunMgr* RunMgr;
#endif // !_RUN_MGR_H_


