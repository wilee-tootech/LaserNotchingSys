#include "stdafx.h"
#include "RunMgr.h"


#include "../InitialTable.h"
#include "../FieldParameter.h"
#include "../Dsp.h"
#include "../MathUtil.h"
#include "../TransUnit.h"
#include "../PointerContainer.h"
#include "../PointerManager.h"
#include "../WriteLog.h"
#include "../Defines.h"
#include "../RECIPE_MODULE/RecipeManager.h"
#include "../MainFormView.h"

#include <cmath>
#include <iostream>
#include <vector>

CRunMgr *RunMgr = NULL;
#define TM_INTER_LOCK_CHECK 1001

CRunMgr::CRunMgr(void)
{
	m_eRunMode			= RUN_MODE::STOP;	//장비상태
	m_eSelectManualMode = SELECT_MANUAL_MODE::SELECT_MANUAL_MODE_NONE;

	m_bInitComplete		= FALSE;			//초기화 여부
	m_bStartInitialize	= FALSE;
	m_bEndInitalize		= FALSE;

	m_nChattering		= 0;

	m_pGatheringTimeCheck = new CTimeCounter;

	//////////////////////////////////////////////////////////////////////////

	//Body 
	m_nBodyMoveWorkPosStep			= 0;


	//Feeder
	m_nLaserSupplyStep				= 0;

	//////////////////////////////////////////////////////////////////////////

	m_bJobEnd						= FALSE;

	//////////////////////////////////////////////////////////////////////////

	m_hThread = NULL;
	m_hHEAD2Thread = NULL;
}

CRunMgr::~CRunMgr(void)
{
	n_write_io_port(RTC_CARD_NUM_1, 0);

	if(m_pGatheringTimeCheck)
	{
		delete m_pGatheringTimeCheck;
		m_pGatheringTimeCheck = NULL;
	}
}

void __stdcall CRunMgr::ButtonSwitch(BUTTON_SW a_eMode)
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	switch (a_eMode)
	{
	case BUTTON_RESET:
		{
			if(pMainFrm)
				pMainFrm->PostMessage(WM_POPUP_MSG_ALL_CLOSE);

			ModeChange(STOP);
			break;
		}
	case BUTTON_STOP:
		if( m_eRunMode != JAM)
		{
			ModeChange(STOP);
		}
		break;

	case BUTTON_START:

#ifndef _SIMUL

		if(!m_bInitComplete) 
		{
			//ModeChange(JAM,ERROR_MACHINE_STATUS_IS_NOT_INIT);
			//return;
		}
#endif

		if(m_eRunMode == STOP)
		{
			ModeChange(READY);
		}
		break;

	}

	m_nChattering = 0;
}

void __stdcall CRunMgr::CheckDigital()
{
	//	if(!Digital) return;
	//버튼 챕터링 
	//{{
	// 	if(m_nChattering > 8)
	// 	{
	// 		if		(X_INTERFACE_LASER_START ) ButtonSwitch(BUTTON_START	);
	// 		else if (X_INTERFACE_LASER_STOP  ) ButtonSwitch(BUTTON_STOP		);
	// 
	// 	}
	// 	else if(X_INTERFACE_LASER_START || X_INTERFACE_LASER_STOP)
	// 	{
	// 		if(m_nChattering < 9) m_nChattering++;
	// 	}
	//}}

	if(m_eRunMode==RUN_MODE::JAM) return;

#ifndef _SIMUL
	//Start NG 처리
	//{{
	//{
	//	Y_MC_ON = OFF;
	//m_bInitComplete = FALSE;
	//ModeChange(JAM, ERROR_EMERGENCY_HAS_BEEN_DETECTED);
	//return;
	//}
	// 
	// 	if(!X_MC_ON)
	// 	{
	// 		m_bInitComplete = FALSE;
	// 		ModeChange(JAM, ERROR_MC_ON);
	// 	}

	// 	if(!X_MAIN_VACUUM)
	// 	{
	// 		m_bInitComplete = FALSE;
	// 		ModeChange(JAM, ERROR_MAIN_VACUUM_CHK);
	// 		return;
	// 	}

	//}}
#endif // !_SIMULATION_

}

void __stdcall CRunMgr::CheckMotion()
{
}

void __stdcall CRunMgr::ModeChange(RUN_MODE a_eRunMode, int a_nErrorNo, SELECT_MANUAL_MODE a_eSelectManualMode)
{
	int i = 0;

	switch(a_eRunMode)
	{
	case JAM:
		{
			if(m_eRunMode == JAM) return;

			m_stMain.m_nMainStep = START_ACTION;

			CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
			if(pMainFrm)
				pMainFrm->PostMessage(WM_SHOW_ERROR, a_nErrorNo);

		}
		break;
	case INIT:
		m_bInitComplete			= FALSE;
		m_bStartInitialize		= TRUE;
		m_bEndInitalize			= TRUE;
		m_bInitComplete			= TRUE;
		m_stMain.m_nMainStep	= START_ACTION;
		break;

	case READY:
		if(!m_bInitComplete)
		{
			ModeChange(JAM, ERROR_MACHINE_STATUS_IS_NOT_INIT);
			return;
		}
		m_stMain.m_nMainStep = START_ACTION;	
		break;
	case AUTO:
		m_stMain.m_nMainStep = START_ACTION;	
		break;

	case STOP:
		m_bThreadAlive = FALSE;
		m_stMain.m_nMainStep = START_ACTION;
		break;
	case MAX_RUNMODE:		
		break;
	}

	m_eRunMode = a_eRunMode;
}

void __stdcall CRunMgr::Execute()
{
	static BOOL bRun = FALSE;
	if(bRun) return;
	bRun = TRUE;

	//	if(Digital)
	{

		//Digital->Scan();
		//CheckDigital();

	}

	//if(!MotionMgr) return;
	//MotionMgr->GetAllMotionsStatus();

	switch(m_eRunMode)
	{
	case INIT:

		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			SetJobClear();
			Initialize();
			ModeChange(STOP);
		}
		break;
	case READY:
		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			Ready();
			ModeChange(AUTO);
		}
		break;
	case AUTO:
		break;
	case STOP:
		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			Stop();
			ModeChange(STOP);
		}
		break;
	case MAX_RUNMODE:		
		break;
	}
	m_stMain.m_nMainStep = FINISH_ACTION;

	bRun = FALSE;

}

void __stdcall CRunMgr::Execute2()
{
	static BOOL bRun = FALSE;
	if(bRun) return;
	bRun = TRUE;

	//	if(Digital)
	{

		//Digital->Scan();
		//CheckDigital();

	}

	//if(!MotionMgr) return;
	//MotionMgr->GetAllMotionsStatus();

	switch(m_eRunMode)
	{
	case INIT:

		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			SetJobClear();
			Initialize();
			ModeChange(STOP);
		}
		break;
	case READY:
		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			Ready();
			ModeChange(AUTO);
		}
		break;
	case AUTO:
		break;
	case STOP:
		if(m_stMain.m_nMainStep == START_ACTION && m_eRunMode != RUN_MODE::JAM)
		{
			Stop();
			ModeChange(STOP);
		}
		break;
	case MAX_RUNMODE:		
		break;
	}
	m_stMain.m_nMainStep = FINISH_ACTION;

	bRun = FALSE;

}

/* IF COND 10,11 사용시 참고 */
//   10(11번째 포트) - 1025 ,  64510   (0x401, 0xFBFE)        0000 0100 0000 0001        1111 1011 1111 1110
//   11(12번째 포트) - 2049 ,  63486   (0x801, 0xF7FE)        0000 1000 0000 0001        1111 0111 1111 1110



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////         241105_1550 LDY 파우치장비 테스트           /////////////////////////////////////////////////////////////////////////////
DWORD WINAPI CRunMgr::ExecutePatternSDI_Pouch_Head1(LPVOID lparam)
{
	IniUtil _iniutil;

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString paramPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PARAM);
	_iniutil.LoadParameterIni(_T("HEAD1"), paramPath, HEAD1ScannerParameter);

	// 2025.01.31 jjsjong 다시 한번 확인
	double dMmSize, dFieldSize;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	double dEncoderOffset = FIELD_FARAMETER.CycleOffset;
	double dEncoderOffset2 = FIELD_FARAMETER.CycleOffset2;

	CTransUnit *pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	pTransUnit->SetMaxValue(dFieldSize, dMmSize);
	pFieldParameter->SetSize(dMmSize, dFieldSize);
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	pFieldParameter->SetScannerStartPosX(FIELD_FARAMETER.ScannerStartPosX);
	pFieldParameter->SetScannerStartPosY(FIELD_FARAMETER.ScannerStartPosY);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter *> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetApp()->GetMainWnd();
	double dScale = pInitialTable->GetFieldScale();
	CRunMgr *pDlg = (CRunMgr *)lparam;
	CWriteLog *log = NULL;
	CDsp *pDsp = CDsp::GetInstance();

	// pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_STANDBY, FALSE);
	pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, TRUE);

	pFieldParameter->SetKxKy(FIELD_FARAMETER.KX, FIELD_FARAMETER.KY);

	TListExeStat stStat;
	stStat.clear();
	CMathUtil mathUtil;

	double m_dMaxField;
	double m_dMaxMM;
	m_dMaxField = dFieldSize;
	m_dMaxMM = dMmSize;

	CString ModeValue = _T("");
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"), _T("Mode"), sitePath, ModeValue);
	_POCKET_TMP_DATA_ stPocketData;

	stPocketData = pFieldParameter->GetPocketPatternParameterData();

#ifdef _SIMUL_
	return 0;
#endif

#ifdef _RTC6_
	// Scanahead: calculate delays automatically. excelliscan
	//(const UINT CardNo, const UINT Mode, const UINT HeadNo, const UINT TableNo, const UINT PreViewTime, const UINT Vmax, const double Amax);
#ifndef _SIMUL_
	LONG CornerScale = (LONG)HEAD1ScannerParameter.polygonDelay;
	LONG EndScale = (LONG)HEAD1ScannerParameter.markDelay;
	LONG AccScale = (LONG)HEAD1ScannerParameter.jumpDelay;
	UINT uPrevTime = 0, uVmax = 0, uAmax = 0;

	select_rtc(RTC_CARD_NUM_1);
	n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax); // place anywhere after load_correction_file
	n_activate_scanahead_autodelays(RTC_CARD_NUM_1, 1);
	n_set_scanahead_line_params(RTC_CARD_NUM_1, CornerScale, EndScale, AccScale);
	n_set_scanahead_laser_shifts(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay * dScale * 64), (long)(HEAD1ScannerParameter.laserOffDelay * dScale * 64)); // fine tuning LaserON and LaserOFF. 1 bit = 1/64
#endif
#endif

	double dScaleFactorX = 0.0, dScaleFactorY = 0.0;;

	if (pFieldParameter->GetKX() != 0)
		dScaleFactorX = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKX();
	if (pFieldParameter->GetKY() != 0)
		dScaleFactorY = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKY();

	double dTabHeightField = (stPocketData.dCuttingHeight + stPocketData.dCuttingOffset) * m_dMaxField / m_dMaxMM;

	// 2025.01.31 jjsjong 추가,
	double dStartExtLenField = HEAD1ScannerParameter.startExtLen * m_dMaxField / m_dMaxMM;

	double cs = cos(PI * pFieldParameter->GetFieldAngle() / 180);
	double sn = sin(PI * pFieldParameter->GetFieldAngle() / 180);

	pDsp->SetFlipHead1(TRUE);
	pDsp->SetMatrixHEAD1(cs, sn);

	pDlg->m_nEncoderSumCount = 0;
	double nEncoderScaleX = pFieldParameter->GetKX();
	double nEncoderScaleY = pFieldParameter->GetKY();
	if (nEncoderScaleX < 0)
		nEncoderScaleX = -nEncoderScaleX;

	pDsp->EnableLaserHEAD1();
	pDsp->StopExcutionHEAD1();

	UINT uStartPos = 0;
	// UINT uJumpPos = 0;
	UINT u2ndJumpPos = 0;
	UINT uEndPos = 0;
	// UINT uFlagPos = 0;
	// UINT uJumpNGPos = 0;
	// UINT uIOPos = 0;
	UINT uOncPattern = 0;
	// NG 태그 관련 Pos
	UINT uNGPos = 0;

	pDsp->SetFirstStart(TRUE);

	double dNotchingWidth[MAX_SPREAD_ROW] = {0.0}; // 노칭길이 배열
	double dBefTotalWidth = 0.0;
	int nFlagCount = stPocketData.dTabCount;

	for (size_t i = 0; i < nFlagCount && i < MAX_SPREAD_ROW; i++)
	{
		dNotchingWidth[i] = stPocketData.dNotchingRealWidth[i] - dBefTotalWidth;
		dBefTotalWidth += dNotchingWidth[i] + stPocketData.dCuttingWidth;
	}

	/////////////////////////////////////////////////////////////// LIST 1 START //////////////////////////////////////////////////////////////////
	pDsp->SetStartListHEAD1(1); // 1번 리스트 시작

	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	pDsp->ClearFlyOverflowHEAD1(15);

#ifdef _RTC6_
#ifndef _SIMUL_
	n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay * dScale * 64), (long)(HEAD1ScannerParameter.laserOffDelay * dScale * 64)); // fine tuning LaserON and LaserOFF. 1 bit = 1/64
#endif
#endif
	uStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	// 2025.01.31 jjsjong 스케일 통일
	double dNotchingKX = pFieldParameter->GetKX();
	if (dNotchingKX < 0)
	{
		dNotchingKX = -dNotchingKX;
	}

	pDsp->EnableLaserHEAD1();

	// 엔코더 리셋
	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	double dStartCutPosX = pFieldParameter->GetScannerStartPosX();
	double dStartCutPosY = pFieldParameter->GetScannerStartPosY();
	pDsp->N_Jump_Abs(RTC_CARD_NUM_1, dStartCutPosX, dStartCutPosY, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, dStartCutPosX, 0, MM);

	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagPower);

	pDsp->SetFlyXHEAD1(dScaleFactorX);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	pDsp->nListJumpRel(RTC_CARD_NUM_1, 13); // 상대적으로 아래 n번째꺼 실행
	////////////////////////////////////////////// 2ndJumpPos Start ////////////////////////////////////////////////////////////
	u2ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, dEncoderOffset2, 0, MM); // 250218 test bef

	pDsp->SetFlyXHEAD1(dScaleFactorX);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM); // Laser On Trigger

	double nNexSumCount = 0;
	////////////////////////////////////////////// 2ndJumpPos End //////////////////////////////////////////////////////////////
	nNexSumCount += (dNotchingWidth[0] + HEAD1ScannerParameter.dNGSensorLeng - stPocketData.dArcInYPos);

	// 들어와서 레이저 안쏨
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);

	// 0x08 : 가속 및 감속 구간의 I/O - dAccOffset( 1회 탭옵셋 ) 적용
	// 0x40 : 지그 클리닝시 의 I/O( 가감속 I/O 와 함께 체크 ) - dAccOffset2 ( 연동 탭옵셋 ) 적용
	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x08, 0);
	pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccOffset[0] * dNotchingKX, 0)), 1);

	// pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x48, 0);
	// pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(dAccOffset2[0] * dNotchingKX, 0)), 1);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x08, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	/////// ARC IN START
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagPower);
	// pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 1, 0, MM); // Test
	n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
	/////// ARC IN END

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

	if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize, 0);
	}
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dTabHeightField + dStartExtLenField);

	nNexSumCount += stPocketData.dArcInYPos;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	nNexSumCount += stPocketData.dCuttingWidth + HEAD1ScannerParameter.dCuttingOffset;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	for (int i = 0; i < nFlagCount; i++)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);

		/////// ARC OUT START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagExtSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -dStartExtLenField);
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -(dTabHeightField - (stPocketData.dArcOutXPos * dFieldSize / dMmSize)));
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcOutXPos * dFieldSize / dMmSize), (stPocketData.dArcOutYPos * dFieldSize / dMmSize), -90);

		if (i != nFlagCount - 1)
		{
			pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
			pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagPower);
		}
		/////// ARC OUT END

		if (i == nFlagCount - 1)
		{
			nNexSumCount += stPocketData.dArcOutXPos;

			nNexSumCount += HEAD1ScannerParameter.notchOffset;
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -HEAD1ScannerParameter.cycleOffset, 0, MM);
			nNexSumCount -= HEAD1ScannerParameter.notchOffset;
			break;
		}
		else
		{
			nNexSumCount += (dNotchingWidth[i + 1] - stPocketData.dArcOutXPos);
			if (i == 0)
			{
				nNexSumCount += dEncoderOffset;
			}
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);

			// 0x08 : 가속 및 감속 구간의 I/O - dAccOffset( 1회 탭옵셋 ) 적용
			// 0x40 : 지그 클리닝시 의 I/O( 가감속 I/O 와 함께 체크 ) - dAccOffset2 ( 연동 탭옵셋 ) 적용
			pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x08, 0);
			pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccOffset[i + 1] * dNotchingKX, 0)), 1);

			// pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x48, 0);
			// pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(dAccOffset2[i + 1] * dNotchingKX, 0)), 1);

			pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x08, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
		}

		/////// ARC IN START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
		pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagPower);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90);
		/////// ARC IN END

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

		// 2025.01.24 jjsjong
		if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
		{
			pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize, 0);
		}
		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dTabHeightField + dStartExtLenField);

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		if (i == nFlagCount - 2)
		{
			nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos; // + HEAD1ScannerParameter.dCuttingOffset;
		}
		else
		{
			nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos;
		}

		nNexSumCount += HEAD1ScannerParameter.flagOffset;

		pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
		pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

		nNexSumCount -= HEAD1ScannerParameter.flagOffset;
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	uEndPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, HEAD1ScannerParameter.cycleOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	// 11번째 IO CHECK H↑ L↓ Low Edge
#ifndef _RTC_Test_
	if (ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x401, 0); // 1번 및 10번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
	else if (ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
#endif
#ifdef _RTC_Test_
	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x101, 0); // 0번 및 8번 I/O 들어올때까지 대기
	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
#endif

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	// 가감속 패턴 쉬프트용 리셋
	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, dEncoderOffset2, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	double nTempEnc = HEAD1ScannerParameter.dPlcOffset; // 연속운전 및 지그클리닝 이후 가속부에 패턴 쉬프트를 위한 Offset
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nTempEnc * dNotchingKX, 0);
	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x08, 0); // 가감속( 0x08 )이 들어와 있으면
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x10, 0);  // 0x10 : 1회운전 I/O // 4번
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos); // <-- 1회운전 I/O 들어올 시 무시

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////// 1회 운전 로직 ///////////////////////////////////////////////////
	uOncPattern = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, dEncoderOffset2, 0, MM); // 250218 test bef

	pDsp->SetFlyXHEAD1(dScaleFactorX);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM); // Laser On Trigger

	nNexSumCount = 0;
	////////////////////////////////////////////// 2ndJumpPos End //////////////////////////////////////////////////////////////
	nNexSumCount += (dNotchingWidth[0] + HEAD1ScannerParameter.dNGSensorLeng - stPocketData.dArcInYPos + HEAD1ScannerParameter.dPatternShift);

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	// nNexSumCount += dAccOffset[0];

	// 탭 하나 가공하기 위해 추가
	/////// ARC IN START
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagPower);
	n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90); // 192.86
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
	/////// ARC IN END
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

	if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize, 0);
	}
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dTabHeightField + dStartExtLenField);

	nNexSumCount += stPocketData.dArcInYPos;
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	nNexSumCount += stPocketData.dCuttingWidth;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	// i를 이어작업 시 가변되도록 변경해야함
	for (int i = 0; i < nFlagCount; i++)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);

		/////// ARC OUT START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagExtSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -dStartExtLenField);
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -(dTabHeightField - (stPocketData.dArcOutXPos * dFieldSize / dMmSize)));
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcOutXPos * dFieldSize / dMmSize), (stPocketData.dArcOutYPos * dFieldSize / dMmSize), -90);

		if (i != nFlagCount - 1)
		{
			pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
			pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagPower);
		}
		/////// ARC OUT END

		if (i == nFlagCount - 1)
		{
			nNexSumCount += stPocketData.dArcOutXPos;

			nNexSumCount += HEAD1ScannerParameter.notchOffset;
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -HEAD1ScannerParameter.cycleOffset, 0, MM);
			nNexSumCount -= HEAD1ScannerParameter.notchOffset;
			break;
		}
		else
		{
			nNexSumCount += (dNotchingWidth[i + 1] - stPocketData.dArcOutXPos - stPocketData.dNotchingAccWidth[i + 1]);
			if (i == 0)
			{
				nNexSumCount += dEncoderOffset;
			}
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			nNexSumCount += stPocketData.dNotchingAccWidth[i + 1];
		}

		/////// ARC IN START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		pDsp->nSetFrequency(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
		pDsp->nWriteDA1List(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagPower);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90);
		/////// ARC IN END

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

		// 2025.01.24 jjsjong
		if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
		{
			pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize, 0);
		}
		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dTabHeightField + dStartExtLenField);

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

		nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos;
		nNexSumCount += HEAD1ScannerParameter.flagOffset;

		pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
		pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

		nNexSumCount -= HEAD1ScannerParameter.flagOffset;
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, HEAD1ScannerParameter.cycleOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

#ifndef _RTC_Test_
	if (ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x401, 0); // 1번 및 10번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
	else if (ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
#endif
#ifdef _RTC_Test_
	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x101, 0xFEE6); // 0번 및 8번 I/O 들어올때까지 대기
	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);			   // 상대적으로 아래 n번째꺼 실행
#endif

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x10, 0);  // 0x10 : 1회운전 I/O
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos); // <-- 1회운전 I/O 들어올 시 무시

	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x10, 0);	  // 0x10 : 1회운전 I/O
	n_list_jump_pos(RTC_CARD_NUM_1, uOncPattern); // <-- 1회운전 I/O 들어올 시 실행

	///////////////////////////////////////////////// NG Tape /////////////////////////////////////////////////////
	uNGPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);
	// n_write_io_port_list(RTC_CARD_NUM_1, 65);

	nNexSumCount = 0;

	pDsp->SetFlyYHEAD1(1.0);
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, -15, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dStartCutPosY, MM);
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dStartCutPosY, MM);

	nNexSumCount += HEAD1ScannerParameter.dMinFlagLeng;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif

	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	// 11번째 IO CHECK H↑ L↓ Low Edge
	if (ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x401, 0); // 1번 및 10번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
	else if (ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);		  // 상대적으로 아래 n번째꺼 실행
	}
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x10, 0);
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos);
	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x10, 0);
	n_list_jump_pos(RTC_CARD_NUM_1, uOncPattern);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pDsp->SetEndOfListHEAD1();
	pDsp->SetFirstStart(FALSE);

	pDsp->EnableLaserHEAD1();

	stStat = pDsp->ReadStatusHEAD1();

	BOOL bRestartProgramCheck = FALSE;

	if (bRestartProgramCheck == FALSE)
	{
		while (stStat.bBusy1 == FALSE && stStat.bBusy2 == FALSE)
		{
			n_execute_list(RTC_CARD_NUM_1, 1);
			pDlg->m_bThreadAlive = TRUE;
			stStat = pDsp->ReadStatusHEAD1();
			Sleep(10);
		}
		bRestartProgramCheck = TRUE;
	}

	BOOL bLaserOnCheck = TRUE;
	BOOL bLaserOnCheckBef = TRUE;

	BOOL bNGCheck = TRUE;
	BOOL bNGCheck_BEF = TRUE;

	BOOL bMainInfo = TRUE;
	BOOL bMainInfo_Bef = TRUE;

	BOOL bAccCheck = TRUE;
	BOOL bAccCheck_Bef = TRUE;

	BOOL bZigCheck = TRUE;
	BOOL bZigCheck_Bef = TRUE;

	long nEncX = 0.0, nEncY = 0.0;
	long nNgWaitX = 0.0, nNGWaitY = 0.0;
	double dTapePos = 0.0;
	CString strTmpData;

	while (pDlg->m_bThreadAlive)
	{
		CString strTime;
		CString strDate;
		SYSTEMTIME stime;
		::GetSystemTime(&stime);

		stime.wHour += 9;
		if (stime.wHour > 23)
		{
			stime.wDay++;
		}
		stime.wHour = stime.wHour % 24;
		strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
		strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
		if (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ACCPOS) == TRUE)
		{
			bAccCheck_Bef = TRUE;
			if (bAccCheck != bAccCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s ::[OnePattern : %s]ACC IO In / Enc : %0.2f", strDate, strTime, pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ONE_PATTERN) ? "TRUE" : "FALSE", nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		}
		else
		{
			bAccCheck_Bef = FALSE;
			if (bAccCheck != bAccCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s :: [OnePattern : %s]ACC IO Out / Enc : %0.2f", strDate, strTime, pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ONE_PATTERN) ? "TRUE" : "FALSE", nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		}
		bAccCheck = bAccCheck_Bef;

		if (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ZIG_CLEAN) == TRUE)
		{
			bZigCheck_Bef = TRUE;
			if (bZigCheck != bZigCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s :: Zig Cleaning IO In / Enc : %0.2f", strDate, strTime, nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		}
		else
		{
			bZigCheck_Bef = FALSE;
			if (bZigCheck != bZigCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s :: Zig Cleaning IO Out / Enc : %0.2f", strDate, strTime, nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		}
		bZigCheck = bZigCheck_Bef;

		if ((pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_A) == TRUE) || (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_B) == TRUE))
		{
			// 10번 혹은 11번 IO 가 들어오면
			bMainInfo_Bef = TRUE;
			if (bMainInfo != bMainInfo_Bef)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
			}
		}
		else
		{
			bMainInfo_Bef = FALSE;
			if (bMainInfo != bMainInfo_Bef)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
			}
		}
		bMainInfo = bMainInfo_Bef;

		if (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_LASER_ON) == TRUE)
		{
			bLaserOnCheckBef = TRUE;
			if (bLaserOnCheck != bLaserOnCheckBef)
			{
				pDsp->EnableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		}
		else
		{
			bLaserOnCheckBef = FALSE;
			if (bLaserOnCheck != bLaserOnCheckBef)
			{
				pDsp->DisableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, FALSE);
		}
		bLaserOnCheck = bLaserOnCheckBef;

		UINT uBusy, uPos;
		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos);

		// 연결테이프 로직
		if (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NG_TAPE) == TRUE) // 임시로 2번
		{
			bNGCheck_BEF = TRUE;
			if (bNGCheck != bNGCheck_BEF)
			{
				// 센서길이 대기
				pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
				double dPreEnc = nNGWaitY / pFieldParameter->GetKX();
				// CString strNGLog;
				// strNGLog.Format("[NG TEST] dPreEnc : %0.2f", dPreEnc);

				dTapePos = dPreEnc + HEAD1ScannerParameter.ngLength;

				if (dTapePos >= stPocketData.dTotalWidth)
				{
					double dRemainLength = stPocketData.dTotalWidth - dPreEnc;

					// 엔코더 리셋위치까지 대기
					while (1)
					{
						pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
						Sleep(10);

						if (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_LASER_ON) == TRUE)
						{
							bLaserOnCheckBef = TRUE;
							if (bLaserOnCheck != bLaserOnCheckBef)
							{
								pDsp->EnableLaserHEAD1();
							}
						}
						else
						{
							bLaserOnCheckBef = FALSE;
							if (bLaserOnCheck != bLaserOnCheckBef)
							{
								pDsp->DisableLaserHEAD1();
							}
						}
						bLaserOnCheck = bLaserOnCheckBef;

						if (dRemainLength < (nNGWaitY / pFieldParameter->GetKX() - dPreEnc) || nNGWaitY / pFieldParameter->GetKX() < 20)
							break; // 엔코더 리셋위치까지 대기
					}
				}

				while (1)
				{
					pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
					Sleep(10);

					if (dTapePos >= stPocketData.dTotalWidth)
					{
						dTapePos -= stPocketData.dTotalWidth;
					}
					if (dTapePos - (HEAD1ScannerParameter.dMinFlagLeng / 2) <= nNGWaitY / pFieldParameter->GetKX()) // 무지부 위치 테이프 고려안됨
						break;
				}
				n_stop_execution(RTC_CARD_NUM_1);
				n_execute_list_pos(RTC_CARD_NUM_1, 1, uNGPos);
			}
		}
		else
		{
			bNGCheck_BEF = FALSE;
			if (bNGCheck != bNGCheck_BEF)
			{
			}
		}
		bNGCheck = bNGCheck_BEF;
		Sleep(10);
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


DWORD WINAPI CRunMgr::ExecutePatternSDI_Pouch_Head1_Manual(LPVOID lparam)
{
	IniUtil _iniutil;

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance(); 
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString paramPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PARAM);
	_iniutil.LoadParameterIni( _T("HEAD1"), paramPath, HEAD1ScannerParameter);

	//2025.01.31 jjsjong 다시 한번 확인
	double dMmSize, dFieldSize;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	double dEncoderOffset = FIELD_FARAMETER.CycleOffset;
	double dEncoderOffset2 = FIELD_FARAMETER.CycleOffset2;

	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	pTransUnit->SetMaxValue(dFieldSize, dMmSize);
	pFieldParameter->SetSize(dMmSize, dFieldSize);
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	pFieldParameter->SetScannerStartPosX(FIELD_FARAMETER.ScannerStartPosX);
	pFieldParameter->SetScannerStartPosY(FIELD_FARAMETER.ScannerStartPosY);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	double dScale = pInitialTable->GetFieldScale();
	CRunMgr *pDlg = (CRunMgr*)lparam;
	CWriteLog *log= NULL;
	CDsp *pDsp = CDsp::GetInstance();

	pFieldParameter->SetKxKy(FIELD_FARAMETER.KX, FIELD_FARAMETER.KY);

	TListExeStat stStat; stStat.clear();
	CMathUtil mathUtil;

	double cs,sn;
	double m_dMaxField;
	double m_dMaxMM;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;
	CString strTemp;

	CString ModeValue = _T("");
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("Mode"), sitePath, ModeValue);
	_POCKET_TMP_DATA_ stPocketData;

	stPocketData = pFieldParameter->GetPocketPatternParameterData();

#ifdef _SIMUL_
	return 0;
#endif

	double dFlagOffsetStart = HEAD1ScannerParameter.flagOffset; 
	double dFlagOffsetEnd = atof(strTemp);

	LONG CornerScale = 500;
	LONG EndScale = 500;
	LONG AccScale = 50;
	UINT uMode, uPrevTime,uVmax,uAmax;
	uPrevTime=0;uVmax=0;uAmax=0;
	
	CornerScale = (LONG)HEAD1ScannerParameter.polygonDelay;
	EndScale = (LONG)HEAD1ScannerParameter.markDelay;
	AccScale = (LONG)HEAD1ScannerParameter.jumpDelay;

#ifdef _RTC6_	
	//Scanahead: calculate delays automatically. excelliscan
	//(const UINT CardNo, const UINT Mode, const UINT HeadNo, const UINT TableNo, const UINT PreViewTime, const UINT Vmax, const double Amax);
#ifndef _SIMUL_
	select_rtc(RTC_CARD_NUM_1);
	n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	n_activate_scanahead_autodelays(RTC_CARD_NUM_1, 1);
	n_set_scanahead_line_params(RTC_CARD_NUM_1,CornerScale, EndScale, AccScale );
	n_set_scanahead_laser_shifts(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif

	UINT iListNumber = 1;
	CString strTmp;
	LONG firstPosX,firstPosY, encoderX, encoderY;
	BOOL bFirstRunFlag=  TRUE;	BOOL FirstAutoFlag = TRUE;
	BOOL bLastMarkFlag = FALSE;


	double dScaleFactorX,dScaleFactorY;
	dScaleFactorX = 0.0;dScaleFactorY = 0.0;

	if( pFieldParameter->GetKX() != 0)
		dScaleFactorX = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKX();
	if( pFieldParameter->GetKY() != 0)
		dScaleFactorY = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKY();

	double dStartCutPosX = 0; 
	double  dStartCutPosY = 0;

	dStartCutPosX = pFieldParameter->GetScannerStartPosX();
	dStartCutPosY = pFieldParameter->GetScannerStartPosY();

	dStartCutPosX = dStartCutPosX * m_dMaxField / m_dMaxMM;
	int iStepindex = STEP_UNFLAG_START;
	int iStartSpeed = pParameter->GetUnflagLineSpeed();

	double dTabHeight = stPocketData.dCuttingHeight + stPocketData.dCuttingOffset;
	double dTabHeightField = dTabHeight * m_dMaxField / m_dMaxMM;

	//2025.01.31 jjsjong 추가, 
	double dStartExtLenField = 0;
	dStartExtLenField = HEAD1ScannerParameter.startExtLen * m_dMaxField / m_dMaxMM;


	int nTabIndex = 0;
	double nTabLengthSumTemp = 0;
	double nTempCountCheck = 0;


	nTabIndex = 0;
	double iRealdistence = 0, iScnSpeed = 0, iRollSpeed = 0;
	iScnSpeed = pParameter->GetUnflagLineSpeed();
	iRollSpeed = pFieldParameter->GetRollSpeed();

	int i = 0, iFieldWidth = 0;
	iFieldWidth = pFieldParameter->GetMarkingField();
	BOOL bSimulOn = pFieldParameter->GetSimulationFlag();

	cs = cos(PI * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(PI * pFieldParameter->GetFieldAngle() / 180);

	pDsp->SetFlipHead1(TRUE);
	pDsp->SetMatrixHEAD1(cs,sn);
	int nTapIndexCount = 0;
	double nEncoderScaleX = 40.0;
	double nEncoderScaleY = 40.0;
	int nSpeedIndexTest = 0;
	double nNexSumCount = 0; 
	double nStartPos = 0; 
	double dFlagEncSum = 0;

	pDlg->m_nEncoderSumCount = nStartPos;
	nEncoderScaleX = pFieldParameter->GetKX();
	nEncoderScaleY = pFieldParameter->GetKY();
	if(nEncoderScaleX < 0) nEncoderScaleX = -nEncoderScaleX;
	int iXoffset, iYoffset;
	firstPosX = 0;
	firstPosY = -dTabHeight;
	pDsp->EnableLaserHEAD1();
	iStepindex = 0;


	UINT Minvalue,Maxvalue;
	Minvalue = 0;
	Maxvalue = 4095;

	int nFlagStartOffsetx;
	nFlagStartOffsetx = 100 * m_dMaxField / m_dMaxMM;

	double dFlagOffset = 0;

	double dRollSpeed = pFieldParameter->GetRollSpeed();
	double dUnflagScannerSpeed = pParameter->GetUnflagLineSpeed();
	pDsp->StopExcutionHEAD1();

	UINT uStartPos = 0;
	UINT uJumpPos = 0;
	UINT u2ndJumpPos = 0;
	UINT uEndPos = 0;
	UINT uFlagPos = 0;
	UINT uJumpNGPos = 0;
	UINT uIOPos = 0;

	UINT uOncPattern = 0;

	// NG 태그 관련 Pos
	UINT uNGPos = 0;


#ifndef _RTC_Test_				
	const double dFlagSafeAreaLength = 125; 
#else
	const double dFlagSafeAreaLength = m_dMaxMM;
#endif
	bool bIsShotFlag = false;

	firstPosX = 0;


	pDsp->SetFirstStart(TRUE);
	pDlg->m_nEncoderSumCount = 0;

	const double dMaxValidPos = 0;
	const double dAddAmount = 0;
	double dTempValue = 0;
	double dOverflowField = m_dMaxMM / 2 *  m_dMaxField / m_dMaxMM; 
	double dFlagDistanceField = 0;
	LONG HEAD1EncoderY,HEAD1EncoderX;
	HEAD1EncoderX=0;HEAD1EncoderY=0;

	CString strLogData;

	double dNotchingWidth[MAX_SPREAD_ROW] = {0.0}; // 노칭길이 배열
	double dBefTotalWidth = 0; 

	double dTabCount = stPocketData.dTabCount;
	for (size_t i = 0; i < dTabCount && i < MAX_SPREAD_ROW; i++)
	{
		dNotchingWidth[i] = stPocketData.dNotchingRealWidth[i] - dBefTotalWidth;
		dBefTotalWidth += dNotchingWidth[i] + stPocketData.dCuttingWidth;
	}

	/////////////////////////////////////////////////////////////// LIST 1 START //////////////////////////////////////////////////////////////////
	pDsp->SetStartListHEAD1(1);

	//n_write_io_port_list(RTC_CARD_NUM_1, 69);

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter);

	pDsp->ClearFlyOverflowHEAD1(15);

#ifdef _RTC6_
#ifndef _SIMUL_
	n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif

	int nFlagCountReal = 0;	
	nFlagCountReal = dTabCount; 

	uStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	double dTempEncX = 0.0;
	double dSensorLeng = HEAD1ScannerParameter.dNGSensorLeng;

	i = 0;
	uJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);// 처음

	uIOPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	//2025.01.31 jjsjong 스케일 통일
	double dNotchingKX = pFieldParameter->GetKX();
	if(dNotchingKX < 0) 
	{
		dNotchingKX = -dNotchingKX;
	}

	dStartCutPosX = pFieldParameter->GetScannerStartPosX();
	dStartCutPosY = pFieldParameter->GetScannerStartPosY();

	pDsp->EnableLaserHEAD1(); 

	long dTmpX, dTmpY;


	BOOL bLaserOn;
	bLaserOn = pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_LASER_ON);

	int posX, posY;

	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->N_Jump_Abs(RTC_CARD_NUM_1, dStartCutPosX , dStartCutPosY, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, dStartCutPosX, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);


//2025.05.10 Manual Test 

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90); // 192.86	
	//double angleStep = (PI / 2) / 30; 
	//double angle, x, y;
	//for (int i = 1; i <= 30; ++i)
	//{
	//	angle = (1.5 * PI) + i * angleStep;
	//	x = 4 * (cos(angle) - cos(angle - angleStep));
	//	y = 4 * (sin(angle) - sin(angle - angleStep));
	//	//pDsp->N_Mark_Rel(RTC_CARD_NUM_1, x, y, MM);
	//}
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
	/////// ARC IN END
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

	if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize , 0);
	}
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField + dStartExtLenField);

	pDsp->SetEndOfListHEAD1();
	pDsp->SetFirstStart(FALSE);

	pDsp->EnableLaserHEAD1();

	int nIOTestFor_ABTytpe;
	if (ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B")) // 정노칭
		nIOTestFor_ABTytpe = RTC_SIG_I_NOTCHING_SENSOR_A;
	else
		nIOTestFor_ABTytpe = RTC_SIG_I_NOTCHING_SENSOR_B; // 역노칭

	
		n_execute_list(RTC_CARD_NUM_1, 1); 
			


return 0;

	pDsp->nListJumpRel(RTC_CARD_NUM_1, 12); // 상대적으로 아래 n번째꺼 실행
	////////////////////////////////////////////// 2ndJumpPos Start ////////////////////////////////////////////////////////////
	n_write_io_port_list(RTC_CARD_NUM_1, 69); // 1
	u2ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, dEncoderOffset2, 0, MM); // 250218 test bef
	//pDsp->N_Mark_Abs(RTC_CARD_NUM_1, HEAD1ScannerParameter.dCuttingOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM); // Laser On Trigger

	nNexSumCount = 0;
	////////////////////////////////////////////// 2ndJumpPos End //////////////////////////////////////////////////////////////

	//nNexSumCount += (dNotchingWidth[0] - stPocketData.dArcInYPos); // 센서길이를 while문에서 기다렷다고 생각 // test

	nNexSumCount += (dNotchingWidth[0] + dSensorLeng - stPocketData.dArcInYPos);

	// 들어와서 레이저 안쏨
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);

	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x08, 0x40);
	pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccWidth[0] * dNotchingKX, 0)), 1);

	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x48, 0);
	pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccOffset[0] * dNotchingKX, 0)), 1);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x08, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	
	pDsp->SetFlyXHEAD1(dScaleFactorX);  
	UINT uListCheck = 0;
	uListCheck = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	// 탭 하나 가공하기 위해 추가
	/////// ARC IN START
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90); // 192.86	
	//double angleStep = (PI / 2) / 30; 
	//double angle, x, y;
	//for (int i = 1; i <= 30; ++i)
	//{
	//	angle = (1.5 * PI) + i * angleStep;
	//	x = 4 * (cos(angle) - cos(angle - angleStep));
	//	y = 4 * (sin(angle) - sin(angle - angleStep));
	//	//pDsp->N_Mark_Rel(RTC_CARD_NUM_1, x, y, MM);
	//}
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
	/////// ARC IN END
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

	if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize , 0);
	}
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField + dStartExtLenField);

	nNexSumCount += stPocketData.dArcInYPos;
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	nNexSumCount += stPocketData.dCuttingWidth;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	int nFlagCount = 0; 
	nFlagCount = stPocketData.dTabCount;

	double dFirstNotchingWidth = dNotchingWidth[0];



	// i를 이어작업 시 가변되도록 변경해야함
	for(int i = 0; i < nFlagCount; i++)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);

		/////// ARC OUT START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagExtSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -dStartExtLenField);
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -(dTabHeightField - (stPocketData.dArcOutXPos * dFieldSize / dMmSize)));
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcOutXPos * dFieldSize / dMmSize), (stPocketData.dArcOutYPos * dFieldSize / dMmSize), -90);
		//angleStep = (PI / 2) / 30; 

		//for (int i = 1; i <= 30; ++i)
		//{
		//	angle = i * angleStep;
		//	x = 4 * (cos(angle) - cos(angle - angleStep));
		//	y = 4 * (sin(angle) - sin(angle - angleStep));
		//	//pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -x, -y, MM);
		//}

		if(i != nFlagCount - 1)
		{
			pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
			pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);
		}
		/////// ARC OUT END

		if(i == nFlagCount - 1)
		{
			//2025.02.15 jjsjong 더할 필요 없음.
			nNexSumCount += stPocketData.dArcOutXPos;

			nNexSumCount += HEAD1ScannerParameter.notchOffset;
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -HEAD1ScannerParameter.cycleOffset, 0, MM);
			nNexSumCount -= HEAD1ScannerParameter.notchOffset;
			break;
		}
		else
		{
			nNexSumCount += (dNotchingWidth[i+1] - stPocketData.dArcOutXPos);
			if( i == 0 ) 
			{
				nNexSumCount += dEncoderOffset; 
			}
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x08, 0x40);
			pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccWidth[i + 1] * dNotchingKX, 0)), 1); // 임시

			pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x48, 0);
			pDsp->WaitForEncoderHEAD1((pDlg->m_nEncoderSumCount - (int)mathUtil.Round(stPocketData.dNotchingAccOffset[i + 1] * dNotchingKX, 0)), 1); // 임시 

			pDsp->nIf_not_Cond(RTC_CARD_NUM_1, 0x08, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
		}

		/////// ARC IN START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90);	
		//for (int i = 1; i <= 30; ++i)
		//{
		//	angle = (1.5 * PI) + i * angleStep;
		//	x = 4 * (cos(angle) - cos(angle - angleStep));
		//	y = 4 * (sin(angle) - sin(angle - angleStep));
		//	//pDsp->N_Mark_Rel(RTC_CARD_NUM_1, x, y, MM);
		//}
		/////// ARC IN END

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

		//2025.01.24 jjsjong
		if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
		{
			pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize , 0);
		}
		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField + dStartExtLenField);

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		 if(i == nFlagCount - 2)
		 {
		 	nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos; // + HEAD1ScannerParameter.dCuttingOffset;
		 }
		 else
		{
			nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos;
		}

		nNexSumCount += HEAD1ScannerParameter.flagOffset; 

		pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
		pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
		nNexSumCount -= HEAD1ScannerParameter.flagOffset;
	}


#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	uEndPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, HEAD1ScannerParameter.cycleOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////// TEST ///////////////////////////////////////////////////
	/*nNexSumCount += 500;
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	n_write_io_port_list(RTC_CARD_NUM_1, 69);*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//11번째 IO CHECK H↑ L↓ Low Edge
	 if(ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	 {
	 	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x401 , 0); // 1번 및 10번 I/O 들어올때까지 대기
	 	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	// 	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 10번 I/O 꺼질 때까지 대기
	// 	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행

		//

	 } 
	 else if(ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	 {
	 	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
	 	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	// 	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 11번 I/O 꺼질 때까지 대기
	// 	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	 }
	//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x101, 0xFEE6); // 1번 및 11번 I/O 들어올때까지 대기
	//pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 11번 I/O 꺼질 때까지 대기
	//pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x10 , 0);
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos); 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////// 1회 운전 로직 ///////////////////////////////////////////////////
	n_write_io_port_list(RTC_CARD_NUM_1, 69); // 1
	uOncPattern = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0);
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, dEncoderOffset2, 0, MM); // 250218 test bef
	//pDsp->N_Mark_Abs(RTC_CARD_NUM_1, HEAD1ScannerParameter.dCuttingOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM); // Laser On Trigger

	nNexSumCount = 0;
	////////////////////////////////////////////// 2ndJumpPos End //////////////////////////////////////////////////////////////
	nNexSumCount += (dNotchingWidth[0] + dSensorLeng - stPocketData.dArcInYPos - stPocketData.dNotchingAccWidth[0]); // 센서길이를 while문에서 기다렷다고 생각 // test

	// 들어와서 레이저 안쏨
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	nNexSumCount += stPocketData.dNotchingAccWidth[0];

	pDsp->SetFlyXHEAD1(dScaleFactorX);  

	// 탭 하나 가공하기 위해 추가
	/////// ARC IN START
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90); // 192.86	
	//for (int i = 1; i <= 30; ++i)
	//{
	//	angle = (1.5 * PI) + i * angleStep;
	//	x = 4 * (cos(angle) - cos(angle - angleStep));
	//	y = 4 * (sin(angle) - sin(angle - angleStep));
	//	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, x, y, MM);
	//}
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
	/////// ARC IN END
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

	if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize , 0);
	}
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField + dStartExtLenField);

	nNexSumCount += stPocketData.dArcInYPos;
	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);

	nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dNotchingAccWidth[0];

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	nFlagCount = stPocketData.dTabCount;



	// i를 이어작업 시 가변되도록 변경해야함
	for(int i = 0; i < nFlagCount; i++)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);

		/////// ARC OUT START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagExtSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -dStartExtLenField);
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, -(dTabHeightField - (stPocketData.dArcOutXPos * dFieldSize / dMmSize)));
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcOutXPos * dFieldSize / dMmSize), (stPocketData.dArcOutYPos * dFieldSize / dMmSize), -90);
		/*for (int i = 1; i <= 30; ++i)
		{
			angle = i * angleStep;
			x = 4 * (cos(angle) - cos(angle - angleStep));
			y = 4 * (sin(angle) - sin(angle - angleStep));
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -x, -y, MM);
		}*/
		if(i != nFlagCount - 1)
		{
			pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth);
			pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);
		}
		/////// ARC OUT END

		if(i == nFlagCount - 1)
		{
			//2025.02.15 jjsjong 더할 필요 없음.
			nNexSumCount += stPocketData.dArcOutXPos;

			nNexSumCount += HEAD1ScannerParameter.notchOffset;
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -HEAD1ScannerParameter.cycleOffset, 0, MM);
			nNexSumCount -= HEAD1ScannerParameter.notchOffset;
			break;
		}
		else
		{
			nNexSumCount += (dNotchingWidth[i+1] - stPocketData.dArcOutXPos - stPocketData.dNotchingAccWidth[i + 1]);
			if( i == 0 ) 
			{
				nNexSumCount += dEncoderOffset;
			}
			pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
			pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
			nNexSumCount += stPocketData.dNotchingAccWidth[i + 1];
		}

		/////// ARC IN START
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.markSpeed, HEAD1ScannerParameter);
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth);
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
		n_arc_rel(RTC_CARD_NUM_1, (stPocketData.dArcInXPos * dFieldSize / dMmSize), (stPocketData.dArcInYPos * dFieldSize / dMmSize), -90);	
		//double angleStep = (PI / 2) / 30; 
		//double angle, x, y;
		//for (int i = 1; i <= 30; ++i)
		//{
		//	angle = (1.5 * PI) + i * angleStep;
		//	x = 4 * (cos(angle) - cos(angle - angleStep));
		//	y = 4 * (sin(angle) - sin(angle - angleStep));
		//	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, x, y, MM);
		//}
		/////// ARC IN END

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, 0, dTabHeightField - (stPocketData.dArcInYPos * dFieldSize / dMmSize));

		//2025.01.24 jjsjong
		if (ModeValue == _T("Anode_A") || ModeValue == _T("Anode_B"))
		{
			pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagLineSpeed, HEAD1ScannerParameter);
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1, (stPocketData.dCuttingWidth + HEAD1ScannerParameter.flagLineExt) * dFieldSize / dMmSize , 0);
		}
		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField + dStartExtLenField);

		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed, HEAD1ScannerParameter);
		// nNexSumCount += dAccOffset[i + 1];

		if(i == nFlagCount - 2)
		{
			nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos; // + HEAD1ScannerParameter.dCuttingOffset;
		}
		 else
		{
			nNexSumCount += stPocketData.dCuttingWidth + stPocketData.dArcInYPos;
		}

		nNexSumCount += HEAD1ScannerParameter.flagOffset; 

		pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
		pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

		nNexSumCount -= HEAD1ScannerParameter.flagOffset;
	}


#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, HEAD1ScannerParameter.cycleOffset, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	if(ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x401 , 0); // 1번 및 10번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	//	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 10번 I/O 꺼질 때까지 대기
	//	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	} 
	else if(ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	//	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 11번 I/O 꺼질 때까지 대기
	//	pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x10 , 0); // 
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos);
	
	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x10 , 0);
	n_list_jump_pos(RTC_CARD_NUM_1, uOncPattern);

	//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x101, 0xFEE6); // 1번 및 11번 I/O 들어올때까지 대기
	//pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	////pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 11번 I/O 꺼질 때까지 대기
	////pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x10, 0);
	//n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos);
	//pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x10 , 0);
	//n_list_jump_pos(RTC_CARD_NUM_1, uOncPattern);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////// TEST ///////////////////////////////////////////////////
	// nNexSumCount += 500;
	// pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	// pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////// NG Tape /////////////////////////////////////////////////////
	n_write_io_port_list(RTC_CARD_NUM_1, 69);
	uNGPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);
	n_write_io_port_list(RTC_CARD_NUM_1, 69);

	nNexSumCount = 0;

	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, -2, 0, MM);
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	pDsp->N_Mark_Rel( RTC_CARD_NUM_1,  0, dStartCutPosY, MM);
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0, dStartCutPosY, MM);

	nNexSumCount += HEAD1ScannerParameter.dMinFlagLeng;

	pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif

	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, 0, 0, MM);
	//nNexSumCount += 500;
	//pDlg->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);
	//pDsp->WaitForEncoderHEAD1(pDlg->m_nEncoderSumCount, 1);

	//11번째 IO CHECK H↑ L↓ Low Edge
	if(ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x401 , 0); // 1번 및 10번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
		//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 10번 I/O 꺼질 때까지 대기
		//pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	} 
	else if(ModeValue == _T("Cathode_A") || ModeValue == _T("Anode_A"))
	{
		pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x801, 0); // 1번 및 11번 I/O 들어올때까지 대기
		pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
		//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x01 , 0xFFE6); // 11번 I/O 꺼질 때까지 대기
		//pDsp->nListJumpRel(RTC_CARD_NUM_1, -1); // 상대적으로 아래 n번째꺼 실행
	}
	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dEncoderOffset2, 0, MM);

	pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x10 , 0); 
	n_list_jump_pos(RTC_CARD_NUM_1, u2ndJumpPos);
	pDsp->nIf_Cond(RTC_CARD_NUM_1, 0x10 , 0);
	n_list_jump_pos(RTC_CARD_NUM_1, uOncPattern);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pDsp->SetEndOfListHEAD1();
	pDsp->SetFirstStart(FALSE);

	UINT uBusy, uPos;

	pDsp->EnableLaserHEAD1();

	stStat = pDsp->ReadStatusHEAD1();

	BOOL bRestartProgramCheck = FALSE; 

	//int nIOTestFor_ABTytpe;
	if (ModeValue == _T("Cathode_B") || ModeValue == _T("Anode_B")) // 정노칭
		nIOTestFor_ABTytpe = RTC_SIG_I_NOTCHING_SENSOR_A;
	else
		nIOTestFor_ABTytpe = RTC_SIG_I_NOTCHING_SENSOR_B; // 역노칭

	if(bRestartProgramCheck == FALSE)
	{
		while(stStat.bBusy1 == FALSE && stStat.bBusy2 == FALSE)
		{
			n_execute_list(RTC_CARD_NUM_1, 1); 
			pDlg->m_bThreadAlive = TRUE;
			stStat = pDsp->ReadStatusHEAD1();
			Sleep(10);
		}
		bRestartProgramCheck = TRUE;
	}

	long nEncX, nEncY;
	long nTmpEncY;

	BOOL bRestartCheck = TRUE;
	BOOL bRestartCheck_BEF = TRUE;


	double dSecondEncResetPosWidth;
	dSecondEncResetPosWidth = stPocketData.dTotalWidth - (stPocketData.dNotchingWidth[0] + stPocketData.dCuttingWidth);

	double dEncoderPreValue;

	BOOL bLaserOnCheck = TRUE;
	BOOL bLaserOnCheckBef = TRUE;

	BOOL bNGCheck = TRUE;
	BOOL bNGCheck_BEF = TRUE;

	long nNgWaitX, nNGWaitY;

	double dNGSensorLength;
	dNGSensorLength = HEAD1ScannerParameter.ngLength;

	double dTapePos;

	CString strNGLog, strLog;

	BOOL bMainInfo, bMainInfo_Bef;
	bMainInfo = bMainInfo_Bef = TRUE;

	double dVisionWidth, dVisionOffset;

	BOOL bAccCheck, bAccCheck_Bef;
	bAccCheck = bAccCheck_Bef = TRUE;

	CString strTmpData;

	while( pDlg->m_bThreadAlive )
	{
		CString strTime;
		CString strDate;
		SYSTEMTIME stime;
		::GetSystemTime(&stime);

		stime.wHour += 9;
		if (stime.wHour > 23)
		{
			stime.wDay++;
		}
		stime.wHour = stime.wHour % 24;
		strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
		strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
		if(pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ACCPOS)== TRUE)
		{
			bAccCheck_Bef = TRUE;
			if(bAccCheck != bAccCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s ::[OnePattern : %s]ACC IO In / Enc : %0.2f",strDate,strTime, pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ONE_PATTERN) ? "TRUE" : "FALSE", nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		} else
		{
			bAccCheck_Bef = FALSE;
			if(bAccCheck != bAccCheck_Bef)
			{
				pDsp->GetEncodeHEAD1(nEncX, nEncY);
				strTmpData.Format("%s-%s :: [OnePattern : %s]ACC IO Out / Enc : %0.2f",strDate,strTime, pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_ONE_PATTERN) ? "TRUE" : "FALSE", nEncY / -FIELD_FARAMETER.KX);
				pMainFrm->m_pDoc->m_pMainFormView->m_LogList.AddItem(strTmpData);
			}
		}
		bAccCheck = bAccCheck_Bef;


		if((pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_A) == TRUE) || (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_B) == TRUE))
		{
			// 10번 혹은 11번 IO 가 들어오면
			bMainInfo_Bef = TRUE;
			if(bMainInfo != bMainInfo_Bef)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
			}
		} else
		{
			bMainInfo_Bef = FALSE;
			if(bMainInfo != bMainInfo_Bef)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
			}
		}
		bMainInfo = bMainInfo_Bef;
		
		if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_LASER_ON)== TRUE)
		{
			bLaserOnCheckBef = TRUE;
			if(bLaserOnCheck != bLaserOnCheckBef)
			{
				pDsp->EnableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		}
		else
		{   
			bLaserOnCheckBef = FALSE;
			if(bLaserOnCheck != bLaserOnCheckBef)
			{
				pDsp->DisableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, FALSE);
		}
		bLaserOnCheck = bLaserOnCheckBef;
		// TEST 250410_1356 LDY - 첫 탭 위치 보정용 테스트
		// 1. MES 를 통해 전체극판길이를 받아서 처리
		// 현재 도면상 극판길이 : stPocketData.dTotalWidth;
		// MES에서 받은 극판길이를 따로 저장해서 위 TotalWidth를 빼면 +- 값 확인가능
		// 그 길이를 바탕으로 점프타이밍 변경
		
		
		// 2. 엔코더 대기 중 리셋을 시켜 첫 노칭길이가 길어지도록 수정
//#ifdef _RTC_Test_
//		if(pDsp->nGetInputValue(RTC_CARD_NUM_1, 0x08) == TRUE)
//#else
//		if((pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_A) == TRUE) || (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_B) == TRUE))
//#endif
//		{
//			bMainInfo_Bef = TRUE;
//			if(bMainInfo != bMainInfo_Bef)
//			{
//				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
//			}
//			_iniutil.LoadRealWidthIni(dVisionWidth);
//			dVisionOffset = dVisionWidth - stPocketData.dTotalWidth + HEAD1ScannerParameter.dPlcOffset; // PLC 옵셋 적용해야함
//			while(TRUE)
//			{
//#ifdef _RTC_Test_
//				if(pDsp->nGetInputValue(RTC_CARD_NUM_1, 0x08) == FALSE)
//#else
//				if((pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_A) == FALSE) && (pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_NOTCHING_SENSOR_B) == FALSE))
//#endif
//				{
//					bMainInfo_Bef = FALSE;
//					if(bMainInfo != bMainInfo_Bef)
//					{
//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
//					}
//					Sleep(1);
//					break;
//				}
//			}
//			bMainInfo = bMainInfo_Bef;
//			// 한번만 체크해야함 - 어차피 밑에 While 문 타면 더 못타긴함 
//			pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
//			double dRestartPosLeng = nNGWaitY / pFieldParameter->GetKX();
//			while(TRUE) // 센서길이만큼 대기 + 옵셋값만큼 더 대기( +- 둘다 가능 )
//			{
//				Sleep(1);
//				pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
//				if(pDsp->nGetInputValue(RTC_CARD_NUM_1, 0x04) == TRUE)
//				{
//					// 1회운전
//					if(dRestartPosLeng + HEAD1ScannerParameter.dNGSensorLeng + dVisionOffset < nNGWaitY / pFieldParameter->GetKX())
//						break;
//				} else
//				{
//					// 연속운전
//					if(dRestartPosLeng + HEAD1ScannerParameter.dNGSensorLeng + dVisionOffset + HEAD1ScannerParameter.dPatternShift < nNGWaitY / pFieldParameter->GetKX())
//						break;
//				}
//			}
//			//n_stop_execution(RTC_CARD_NUM_1);
//			//Sleep(1);
//			//// IO 상태에 따라 1회운전로직 / 연속운전로직 변경
//			//if(pDsp->nGetInputValue(RTC_CARD_NUM_1, 0x04) == TRUE)
//			//{
//			//	// 1회운전
//			//	n_execute_list_pos(RTC_CARD_NUM_1, 1, uOncPattern);
//			//} else
//			//{
//			//	// 연속운전
//			//	n_execute_list_pos(RTC_CARD_NUM_1, 1, u2ndJumpPos);
//			//}
//		}

		strLog = " ";
		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos);

		// 연결테이프 로직
		if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_NG_TAPE) == TRUE) // 임시로 2번
		{
			bNGCheck_BEF = TRUE;
			if(bNGCheck != bNGCheck_BEF)
			{
				// 센서길이 대기
				pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY); 
				double dPreEnc = nNGWaitY / pFieldParameter->GetKX();
				strNGLog.Format("[NG TEST] dPreEnc : %0.2f", dPreEnc);

				dTapePos = dPreEnc + dNGSensorLength;

				if(dTapePos >= stPocketData.dTotalWidth)
				{
					double dRemainLength = stPocketData.dTotalWidth - dPreEnc;

					// 엔코더 리셋위치까지 대기
					while(1)
					{
						pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
						Sleep(10);

						if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_LASER_ON)== TRUE)
						{
							bLaserOnCheckBef = TRUE;
							if(bLaserOnCheck != bLaserOnCheckBef)
							{
								pDsp->EnableLaserHEAD1();
							}
						}
						else
						{   
							bLaserOnCheckBef = FALSE;
							if(bLaserOnCheck != bLaserOnCheckBef)
							{
								pDsp->DisableLaserHEAD1();
							}
						}
						bLaserOnCheck = bLaserOnCheckBef;

						if(dRemainLength < (nNGWaitY / pFieldParameter->GetKX() - dPreEnc) || nNGWaitY / pFieldParameter->GetKX() < 20)
							break; // 엔코더 리셋위치까지 대기	
					}
				}

				while(1)
				{
					pDsp->GetEncodeHEAD1(nNgWaitX, nNGWaitY);
					Sleep(10);

					if(dTapePos >= stPocketData.dTotalWidth)
					{
						dTapePos -= stPocketData.dTotalWidth;
					}
					if(dTapePos - (HEAD1ScannerParameter.dMinFlagLeng / 2) <= nNGWaitY / pFieldParameter->GetKX()) // 무지부 위치 테이프 고려안됨
						break;	
				}
				n_stop_execution(RTC_CARD_NUM_1);
				n_execute_list_pos(RTC_CARD_NUM_1, 1, uNGPos);
			}

		} else
		{
			bNGCheck_BEF = FALSE;
			if(bNGCheck != bNGCheck_BEF)
			{
			}
		}
		bNGCheck = bNGCheck_BEF;
		Sleep(10);
	}
	return 0;	
}

DWORD WINAPI CRunMgr::ExecutePatternSDI_Head2(LPVOID lparam)
{
	CRunMgr* pRunMgr = (CRunMgr*)lparam;
	IniUtil _iniUtil;

	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	_iniUtil.LoadParameterIni( _T("HEAD2"), ParamPath, HEAD2ScannerParameter);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	double dScale = pInitialTable->GetFieldScale();
	CWriteLog *log= NULL;
	CDsp *pDsp = CDsp::GetInstance();

	TListExeStat stStat; stStat.clear();
	CMathUtil mathUtil;
	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();

	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;
	pDsp->SetFieldValue(dFieldSize, dMmSize);

	// pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	double cs,sn;
	double m_dMaxField;
	double m_dMaxMM;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CString strTemp;
	//_NOTCH_PATTERN_DATA m_stNotchPatternData = pFieldParameter->GetHEAD1PatternDataOfKoem();

	_SDI_NOTCH_PATTERN_DATA m_stNotchPatternData;
	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, m_stNotchPatternData);

	//2023.11.15 Excelli Test --------------------------------------------------------------------------------------------
	//pDlg->GetDlgItemText(IDC_OFFSET2,strTemp);
	double dFlagOffsetStart = HEAD2ScannerParameter.flagOffset; //  240503 jyh
	double dFlagOffsetEnd = atof(strTemp);

	LONG CornerScale = 500; // polyline: 100%: max precision, 0% min execution time 
	LONG EndScale = 500;// mark, jump: 100%: max precision, 0% min execution time
	LONG AccScale = 50;// 100%: laser is on during acceleration and deceleration
	UINT uMode, uPrevTime,uVmax,uAmax;
	uPrevTime=0;uVmax=0;uAmax=0;

	CornerScale = (LONG)HEAD2ScannerParameter.polygonDelay;
	EndScale = (LONG)HEAD2ScannerParameter.markDelay;
	AccScale = (LONG)HEAD2ScannerParameter.jumpDelay;

#ifdef _RTC6_	
	//Scanahead: calculate delays automatically. excelliscan
	//(const UINT CardNo, const UINT Mode, const UINT HeadNo, const UINT TableNo, const UINT PreViewTime, const UINT Vmax, const double Amax);
#ifndef _SIMUL_
	select_rtc(RTC_CARD_NUM_2);
	n_set_scanahead_params(RTC_CARD_NUM_2, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	n_activate_scanahead_autodelays(RTC_CARD_NUM_2, 1);
	n_set_scanahead_line_params(RTC_CARD_NUM_2,CornerScale, EndScale, AccScale );
	n_set_scanahead_laser_shifts(RTC_CARD_NUM_2, (long)(HEAD2ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD2ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif

	UINT iListNumber = 1;
	CString strTmp;

	//2022.11.25 Flip Test
	//m_stNotchPatternData.bYFlip = FALSE;

	LONG firstPosX,firstPosY, encoderX, encoderY;
	BOOL bFirstRunFlag=  TRUE;	BOOL FirstAutoFlag = TRUE;
	BOOL bLastMarkFlag = FALSE;


	double dScaleFactorX,dScaleFactorY;
	dScaleFactorX = 0.0;dScaleFactorY = 0.0;

	pFieldParameter->SetKxKy2(FIELD_FARAMETER.KX2, FIELD_FARAMETER.KY2);

	if( FIELD_FARAMETER.KX2 != 0)
		dScaleFactorX = (m_dMaxField / m_dMaxMM) / FIELD_FARAMETER.KX2;
	if( FIELD_FARAMETER.KY2 != 0)
		dScaleFactorY = (m_dMaxField / m_dMaxMM) / FIELD_FARAMETER.KY2;

	double dStartCutPosX = 0; // Ä¿ÆÃ ½ÃÀÛ Æ÷Áö¼Ç
	dStartCutPosX = dStartCutPosX * m_dMaxField / m_dMaxMM;
	//BaseLine Data 
	double dNonflagStartWidth,dNonflagStartHeight,dNonflagEndWidth,dNonflagEndHeight;
	double dTotalWidth,dFoilExtention,dHEAD2Width,dBuriedHeight,dNotchRoot,dNublessHeight;
	double dTabWidth,dTabHeight,dTabCount,dBuriedRegion,dNublessRegion,dPitchLength;
	double dTabAngle, dFlagStartWidth, dChangeOffset;


	int iStepindex = STEP_UNFLAG_START;
	int iStartSpeed = pParameter->GetUnflagLineSpeed();


	dNonflagStartHeight  = 0; //= m_stNotchPatternData.dNonflagStartHeight; // o  Check
	dNublessRegion = 0; // = m_stNotchPatternData.dNublessRegion; // x
	dNublessHeight = 0; // = m_stNotchPatternData.dNublessHeight; // x
	dNotchRoot = 0; // = m_stNotchPatternData.dNotchRoot; // o
	dTabWidth = 0; // = m_stNotchPatternData.dTabWidth; // x
	dTabCount = 0; // = m_stNotchPatternData.dTabCount; // ?
	dTabHeight = m_stNotchPatternData.dCuttingHeight + HEAD2ScannerParameter.dCuttingOffset; // ㅇ
	dBuriedRegion = m_stNotchPatternData.dNochingWidth; // ㅇ
	dBuriedHeight = m_stNotchPatternData.dNochingHeight; // ㅇ
	dNonflagEndWidth = 0; // = m_stNotchPatternData.dNonflagEndWidth; // ㄴ
	dNonflagEndHeight = 0; // = m_stNotchPatternData.dNonflagEndHeight; // ㄴ
	dTabAngle = m_stNotchPatternData.dCuttingAngle; // ㅇ
	dFoilExtention = 0; // = m_stNotchPatternData.dFoilExtention; // ? 
	dHEAD2Width = 0; // = m_stNotchPatternData.dHEAD2Width; // ?
	dTotalWidth = m_stNotchPatternData.dTotalWidth; //dHEAD1Width + dFoilExtention;
	dFlagStartWidth = 0; // = m_stNotchPatternData.dFlagStartWidth; // ?
	dChangeOffset = FIELD_FARAMETER.CycleOffset;


	dNonflagStartHeight = dNonflagStartHeight - dHEAD2Width;
	dNublessHeight = dNublessHeight - dHEAD2Width;
	dNotchRoot = dHEAD2Width - dNotchRoot; 
	dBuriedHeight = m_stNotchPatternData.dCuttingHeight - dBuriedHeight;
	dNonflagEndHeight = dNonflagEndHeight - dHEAD2Width;


	double  dNonflagStartHeightField, dNonflagEndWidthField, dNonflagEndHeightField;
	double dTotalWidthField, dFoilExtentionField, dHEAD1WidthField, dBuriedHeightField, dNotchRootField, dNublessHeightField;
	double dTabWidthField, dTabHeightField, dBuriedRegionField, dNublessRegionField, dPitchLengthField;
	double dFlagStartWidthField, dChangeOffsetField;

	dNonflagStartHeightField = dNonflagStartHeight * m_dMaxField / m_dMaxMM;
	dNonflagEndWidthField = dNonflagEndWidth * m_dMaxField / m_dMaxMM;
	dNonflagEndHeightField = dNonflagEndHeight * m_dMaxField / m_dMaxMM;
	dTotalWidthField = dTotalWidth * m_dMaxField / m_dMaxMM;
	dFoilExtentionField = dFoilExtention * m_dMaxField / m_dMaxMM;
	dHEAD1WidthField = dHEAD2Width * m_dMaxField / m_dMaxMM;
	dBuriedHeightField = dBuriedHeight * m_dMaxField / m_dMaxMM;
	dNotchRootField = dNotchRoot * m_dMaxField / m_dMaxMM;
	dNublessHeightField = dNublessHeight * m_dMaxField / m_dMaxMM;
	dTabWidthField = dTabWidth * m_dMaxField / m_dMaxMM;
	dTabHeightField = dTabHeight * m_dMaxField / m_dMaxMM;
	dBuriedRegionField = dBuriedRegion * m_dMaxField / m_dMaxMM;
	dNublessRegionField = dNublessRegion * m_dMaxField / m_dMaxMM;
	dFlagStartWidthField = dFlagStartWidth * m_dMaxField / m_dMaxMM;
	dChangeOffsetField = dChangeOffset * m_dMaxField / m_dMaxMM;

	dNonflagEndWidthField = dNonflagEndWidthField - dStartCutPosX;
	dNublessRegionField = dNublessRegionField - dFlagStartWidthField;

	double dUnflagStartSloopX, dTabAngleX,dTabAngleTemp;
	double dBuriedSloopX;
	dUnflagStartSloopX = 0;dTabAngleX=0;dBuriedSloopX=0;dTabAngleTemp=0;


	//2023.07.10 Samsung Pattern Test
	double dStartTabWidth = m_stNotchPatternData.dCuttingTabWidth1;
	double dFinalTabWidth = m_stNotchPatternData.dCuttingTabWidth6;
	double dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;
	dTabCount = (dTotalLength * 2)/(dStartTabWidth + dFinalTabWidth);
	double dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount - 1.0);
	//double dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount );
	double dSimulatedTotalLength = dTabCount * (dStartTabWidth + dFinalTabWidth) / 2.0;

	double dTabWidth1,dTabWidth2,dTabWidth3,dTabWidth4,dTabWidth5,dTabWidth6;
	double dStartTabWidthArray[10];
	double dStartTabWidthArraySum[10];
	double dSecondTabWidth = 0;

	double dPatternCorePos; // 코어부 길이 >> 노칭 - 외곽
	double dPatternOutPos;
	dPatternOutPos = m_stNotchPatternData.dNochingOutPosWidth;
	dPatternCorePos = dBuriedRegion - dPatternOutPos;

	// CDlgDualScannerParameter* pDlgParam = CDlgDualScannerParameter::GetInstance();
	// CString strAcLeng;
	// pDlgParam->GetDlgItemText(IDC_CTTEXT_ACSENSOR_LENG2, strAcLeng);
	double dACSensorLength;
	dACSensorLength = HEAD2ScannerParameter.dACSensorLeng;;

	for(int i = 0; i < 10; i++)
	{
		dStartTabWidthArray[i] = 0;
		dStartTabWidthArraySum[i] = 0;
	}

	int nGroupCnt = 6;
	double dTabLengthDivided ;
	// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
	{
		//dTabCount = nGroupCnt; //SDI 고정 6구간
		dSimulatedTotalLength = dTabCount * (dStartTabWidth + dFinalTabWidth) / 2.0;
		dTabWidth = dFinalTabWidth;
		dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount - 1.0);
		dTabLengthDivided = dTotalLength / nGroupCnt; //Flag 구간을 그룹으로 나눔.

		//2023.08.03 For 삼성SDI 샘플 ===============================================================================

		// 재선언 수정
		dTabWidth1 = 0;dTabWidth2=0;dTabWidth3=0;dTabWidth4=0;dTabWidth5=0;dTabWidth6=0;
		dTabWidth1 = m_stNotchPatternData.dCuttingTabWidth1; // 240503 jyh
		dTabWidth2 = m_stNotchPatternData.dCuttingTabWidth2;
		dTabWidth3 = m_stNotchPatternData.dCuttingTabWidth3;
		dTabWidth4 = m_stNotchPatternData.dCuttingTabWidth4;
		dTabWidth5 = m_stNotchPatternData.dCuttingTabWidth5;
		dTabWidth6 = m_stNotchPatternData.dCuttingTabWidth6;

		dStartTabWidthArray[0] = dTabWidth1;
		dStartTabWidthArray[1] = dTabWidth2;
		dStartTabWidthArray[2] = dTabWidth3;
		dStartTabWidthArray[3] = dTabWidth4;
		dStartTabWidthArray[4] = dTabWidth5;
		dStartTabWidthArray[5] = dTabWidth6;
		dStartTabWidthArray[6] = dTabWidth6;
		dStartTabWidthArray[7] = dTabWidth6;
		dStartTabWidthArray[8] = dTabWidth6;
		dStartTabWidthArray[9] = dTabWidth6;

		dStartTabWidthArraySum[0] = dStartTabWidthArray[0] * m_stNotchPatternData.dCuttingCount1;//247;
		for(int i = 1; i < 10; i++)
		{
			if(i == 1)
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount2;//285;
			} else if( i == 2 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount3;//285;
			} else if( i == 3 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount4;//285;
			} else if( i == 4 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount5;//285;
			} else
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount6;//285;
			}
		}

		if(dTabWidth1 > 0 || dTabWidth2 > 0 || dTabWidth3 > 0 || dTabWidth4 > 0 || dTabWidth5 > 0 || dTabWidth6 > 0 )
			dFlagAllowance = 0;
	}

	int nTabIndex = 0;
	double nTabLengthSumTemp = 0;
	double nTempCountCheck = 0;

	nTabIndex = 0;

	//=============================================================================================================
	double dRadian = 0;

	if(dTabAngle != 0)
	{

		dRadian = ( dTabAngle  / 180.0f) * M_PI;
		dUnflagStartSloopX = ((dTabHeight - dNonflagStartHeight)*tan(dRadian));
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dBuriedSloopX = ((dTabHeight - dBuriedHeight)*tan(dRadian));


		dUnflagStartSloopX = dUnflagStartSloopX * m_dMaxField / m_dMaxMM;
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
		dBuriedSloopX = dBuriedSloopX * m_dMaxField / m_dMaxMM;
	}
	//--------------------------------------------------------------------------------------

	double iRealdistence = 0, iScnSpeed = 0, iRollSpeed = 0;
	iScnSpeed = pParameter->GetUnflagLineSpeed();
	iRollSpeed = pFieldParameter->GetRollSpeed();

	int i = 0, iFieldWidth = 0;
	iFieldWidth = pFieldParameter->GetMarkingField();
	BOOL bSimulOn = pFieldParameter->GetSimulationFlag();


	cs = cos(PI * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(PI * pFieldParameter->GetFieldAngle() / 180);

	if(m_stNotchPatternData.bFlip)
		pDsp->SetFlipHead2(TRUE);
	else
		pDsp->SetFlipHead2(FALSE);

	pDsp->SetMatrixHEAD2(cs,sn);

	int nTapIndexCount = 0;
	double nEncoderScaleX = 40.0;
	double nEncoderScaleY = 40.0;
	int nSpeedIndexTest = 0;
	double nNexSumCount = 0;
	double nStartPos = 0;
	double dFlagEncSum = 0;

	pRunMgr->m_nEncoderSumCount = nStartPos;
	nEncoderScaleX = FIELD_FARAMETER.KX2;
	nEncoderScaleY = FIELD_FARAMETER.KY2;
	if(nEncoderScaleX < 0) nEncoderScaleX = -nEncoderScaleX;
	int iXoffset, iYoffset;
	firstPosX = 0;
	firstPosY = -dTabHeight;
	pDsp->EnableLaserHEAD2();
	iStepindex = 0;


	UINT Minvalue,Maxvalue;
	Minvalue = 0;
	Maxvalue = 4095;

	//2021.07.07 TestDebug
	int nFlagStartOffsetx;
	nFlagStartOffsetx = 100 * m_dMaxField / m_dMaxMM;


	double dFlagOffset = 0;


	double dRollSpeed = pFieldParameter->GetRollSpeed();
	//double dMarkArea = 250; // mm
	double dUnflagScannerSpeed = pParameter->GetUnflagLineSpeed();
	//double dCuttingTIme = dMarkArea / (dUnflagScannerSpeed - dRollSpeed);
	//double maxCutMM =  dCuttingTIme* dRollSpeed;
	pDsp->StopExcutionHEAD2();



#ifndef _RTC_Test_				
	const double dFlagSafeAreaLength = 125;  //mm´ÜÀ§
#else
	const double dFlagSafeAreaLength = m_dMaxMM;//250;  //mm´ÜÀ§

#endif


	bool bIsShotFlag = false;

	//firstPosX = 125 *  m_dMaxField / m_dMaxMM;
	firstPosX = 0;


	pDsp->SetFirstStart(TRUE);
	pRunMgr->m_nEncoderSumCount = 0;
	dChangeOffset = HEAD2ScannerParameter.cycleOffset;//pFieldParameter->GetCycleOffset();

	const double dMaxValidPos = 0;
	const double dAddAmount = 0;
	double dTempValue = 0;
	double dOverflowField = m_dMaxMM / 2 *  m_dMaxField / m_dMaxMM;
	double dFlagDistanceField = 0;
	LONG HEAD2EncoderY,HEAD2EncoderX;
	HEAD2EncoderX=0;HEAD2EncoderY=0;
	//----------------------------2024.06.13 이어작업 기능추가 테스트 --------------------------------------------


	CString strHEAD2Encoder; //, strHead2Encoder;
	strTemp.Format("H2_0 %.3f mm", HEAD2EncoderY / FIELD_FARAMETER.KX2);

	double dHEAD1Enc, dHEAD2Enc;

	_iniUtil.LoadEncIni(dHEAD1Enc, dHEAD2Enc);


	double HEAD2TmpEncY;
	if( dHEAD2Enc > 0 )
	{
		HEAD2TmpEncY = dHEAD2Enc * FIELD_FARAMETER.KX2;
	} else
	{
		pDsp->GetEncodeHEAD2(HEAD2EncoderX,HEAD2EncoderY);
		HEAD2TmpEncY = HEAD2EncoderY;
	}


	// pDsp->GetEncodeHEAD2(HEAD2EncoderX,HEAD2EncoderY);
	//Y축 엔코더가 위치제어용으로 사용중
	strTemp.Format("H2_0 %.3f mm", HEAD2TmpEncY / FIELD_FARAMETER.KX2);

	double dSumCountPrev = HEAD2TmpEncY / FIELD_FARAMETER.KX2;
	double dSumCountTemp = 0;

	if(dSumCountPrev > m_stNotchPatternData.dNochingWidth)
	{
		dSumCountPrev =  dSumCountPrev - m_stNotchPatternData.dNochingWidth; // 
	}  else 
	{
		// pDlg->SetDlgItemText(IDC_SAVED_HEAD2ENC, _T("0.0"));
#ifdef _RTC5_
		n_init_fly_2d(RTC_CARD_NUM_2,0,0);
#else
		n_init_fly_2d(RTC_CARD_NUM_2,0,0,0);
#endif
	}
	if(_ttoi(strHEAD2Encoder) > 0 )
	{
		dSumCountTemp -= (dFlagOffsetStart + FIELD_FARAMETER.CycleOffset2);
	}


	while(1)
	{
		if(dSumCountTemp >= dStartTabWidthArraySum[nTabIndex] )
		{
			nTabIndex++;
			dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

		}
		else if( (dSumCountTemp + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
		{
			dStartTabWidth = dStartTabWidthArray[nTabIndex];
			dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
		}
		else
		{
			dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
		}
		dSumCountTemp += (dStartTabWidth + dSecondTabWidth);
		if(dSumCountTemp >= dSumCountPrev)
			break;
	}
	if(dStartTabWidth == 0)
		dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];

	dTempValue = dStartTabWidth + dSecondTabWidth - (dSumCountTemp - dSumCountPrev);

	// 리셋햇을때
	if(dSumCountPrev == 0 )
	{
		dStartTabWidth = dStartTabWidthArray[nTabIndex];
	} else
	{
		dStartTabWidth = dSumCountTemp - dSumCountPrev;
	}

	//=============================================================================================================
	pDsp->SetGotoXYHEAD2(0,   dTabHeightField);


	pDsp->SetStartListHEAD2(1);
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter);

#ifdef _RTC_Test_				
	double dCurrent = pParameter->GetLaserPowerSet();
	if(pDsp->GetInitialStatus())
	{
		write_8bit_port((unsigned short)(dCurrent));
		write_8bit_port_list((unsigned short)(dCurrent));

		pDsp->OutputIOList(RTCIO_O_MO, true);
		pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
	}
#endif

	pDsp->ClearFlyOverflowHEAD2(15);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);

#ifdef _RTC6_
#ifndef _SIMUL_
	n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_2, (long)(HEAD2ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD2ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif

	int nFlagCountReal = 0;	
	nFlagCountReal = dTabCount; 

	double dTmpSumCountPrev = dSumCountPrev;

	pDsp->SetFlyYHEAD2(1.0); pDsp->SetFlyYHEAD2(0.0);
	pDsp->SetFlyXHEAD2(1.0); pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyXHEAD2(dScaleFactorX);

	nNexSumCount = 0;

	BOOL bMarkCheck = (dStartTabWidth > dTempValue);

	// 현재 스캐너위치
	if(dStartTabWidth > dTempValue) // 여기가 문제 같음
	{
		nNexSumCount += dStartTabWidth - dStartTabWidthArray[nTabIndex]; 

	} else
	{
		nNexSumCount += dStartTabWidth;
	}

	// 재시작시 X

	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth - dTmpSumCountPrev;

	dStartTabWidth = dStartTabWidthArray[nTabIndex]; 
	nTempCountCheck = nNexSumCount;

	if(bMarkCheck == TRUE)
	{
		//pDsp->N_Jump_Abs(RTC_CARD_NUM_2, (nNexSumCount * m_dMaxField / m_dMaxMM) ,   dTabHeightField);
		//pDsp->N_Mark_Rel( RTC_CARD_NUM_2, dTabAngleX ,   -dTabHeightField);
		//nNexSumCount += dStartTabWidth;
	} else
	{
		//nNexSumCount += dSecondTabWidth;
	}

	pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);


	nTempCountCheck = nNexSumCount;

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); // 2.4

	UINT uStartPos = 0;
	UINT uJumpPos = 0;
	UINT u2ndFlagPos = 0;
	UINT uEndPos = 0;
	UINT u2ndJumpPos = 0;
	UINT u3ndJumpPos = 0;
	UINT u3ndFlagStartPos = 0; // 3포지션에서 플래그 시작부
	UINT u4ndJumpPos = 0;
	UINT u5ndJumpPos = 0;
	UINT u6ndJumpPos = 0;
	UINT n6ndFlagPos = 0;
	UINT u7ndJumpPos = 0;

	nTempCountCheck = nNexSumCount;

	uStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);


	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);

	BOOL bZigZagCut = FALSE;
	BOOL bLastFlag = FALSE;

	if(m_stNotchPatternData.nCuttingMode == 2)
		bZigZagCut = TRUE;

	if(bZigZagCut == FALSE)
	{
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 247
				{
					nTabIndex++;
					nTabLengthSumTemp=0;
					nTapIndexCount=0;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
				{
					nTabIndex=0;
					nTabLengthSumTemp=0;
					nTapIndexCount=0;
					break;
				}

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD2(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_2, (long)(HEAD2ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD2ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD2(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		//else
		//{
		//	for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
		//	{
		//		pDsp->SetFlyXHEAD2(dScaleFactorX);
		//		{
		//			pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//			pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//		}

		//		//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//		nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

		//		nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//	}

		//}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{

		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;
		BOOL bBreakFlag=FALSE;
		BOOL bLastFlag = FALSE;


		pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);

		int i = 0;
		// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------

				//2024.06.26 엔코더 리셋 안하고 이어할때
				if(dSumCountPrev > 0)
				{
					if(nNexSumCount >= (dStartTabWidthArraySum[nTabIndex] + m_stNotchPatternData.dNochingWidth))
					{
						//if(nTabIndex < 6)
						nTabIndex++;

						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

					}
					else if( (nNexSumCount + dStartTabWidthArray[nTabIndex]) >= (dStartTabWidthArraySum[nTabIndex] + m_stNotchPatternData.dNochingWidth) )
					{
						dStartTabWidth = dStartTabWidthArray[nTabIndex];
						dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
					}
					else
					{
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
					}
				}
				else

				{
					if(nNexSumCount >= dStartTabWidthArraySum[nTabIndex] )
					{
						nTabIndex++;

						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];

					}
					else if( (nNexSumCount + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
					{
						dStartTabWidth = dStartTabWidthArray[nTabIndex];
						dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
					}
					else
					{
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
					}
				}

				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				//if(i % 2 == 0)
				dFlagDistanceField = dStartTabWidth;
				dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
				pDsp->SetFlyXHEAD2(dScaleFactorX);

				// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				{
					//스캐너로 Flag Width조정
					//if(i % 2 == 0 && nTapIndexCount <  284)

					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX ,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset2;

					//if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						//	nNexSumCount += (dStartTabWidth  + dNonFlagOffset);
					}
					//else
					{
						// 음양극 모두 첫패턴 3번째 플래그는 보정 없음
						nNexSumCount += dStartTabWidth ;
					}

					nTabLengthSumTemp += dStartTabWidth;
					dTempEncX = nNexSumCount;


					//// log->WriteString(CWriteLog::MakeFormatString("Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX));
				}
				//				else
				//				{
				//
				//					//엔코더로 Flag Width조정
				//					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
				//#ifndef _SIMUL_
				//					n_list_nop(RTC_CARD_NUM_2);
				//#endif
				//					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
				//					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				//					pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
				//
				//					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
				//					//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				//				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dSecondTabWidth;
				nNexSumCount += dSecondTabWidth;
				nTapIndexCount++;
				i++;


				// pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);

				//2024.06.18 Nonflag i/o 미리 보내기
				if(nNexSumCount >= dTotalLength - 50 )
				{
					//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
				}


				if(nNexSumCount >= dTotalLength)
				{
					bBreakFlag = TRUE;
					// nNexSumCount += HEAD2ScannerParameter.cycleOffset;
				}

				if( (nNexSumCount + dStartTabWidth) >= dTotalLength)
				{
					// 음극은 종단부 한번 더 긋기없음, 양극은 있음
					if(pInitialTable->GetHead1Name() == "Cathode")
					{
						// 1호기
						pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   -dTabHeightField); // 기존

						// pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   -dTabHeightField);
						pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

						bBreakFlag = TRUE;
						nNexSumCount += dStartTabWidth;

					} else
					{
						// 2호기
						bBreakFlag = TRUE;
						// nNexSumCount+=dChangeOffset;
					}

					//pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					//pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);


					//bBreakFlag = TRUE;
					//nNexSumCount+= (dStartTabWidth+ dChangeOffset);

				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD2ScannerParameter.cycleOffset;
					dFlagEncSum = nNexSumCount;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


				if(bBreakFlag == TRUE)
				{
					break;
				}

			}

		}
		//		else
		//		{
		//			int i = 0;
		//			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
		//			{	
		//				pDsp->SetFlyXHEAD2(dScaleFactorX);
		//				//스캐너로 Flag Width조정
		//				//if(i % 2 == 0)
		//				{
		//					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
		//					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
		//
		//					{
		//						//스캐너로 Flag Width조정
		//						if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
		//						{
		//							if(i % 2 == 0)
		//							{
		//								pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//								pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
		//								pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//								//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//							}
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//						}
		//						else
		//						{
		//							//엔코더로 Flag Width조정
		//							pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//#ifndef _SIMUL_
		//							n_list_nop(RTC_CARD_NUM_2);
		//#endif
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//							pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//							pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//							//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//						}
		//					}
		//				}
		//
		//				//-----------------------------------------------------------------------------------------------------------
		//
		//				i++;
		//				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
		//
		//				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//				//if(i == (int)nFlagCountReal-1)
		//				//	nNexSumCount+=dChangeOffset;
		//
		//				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);
		//
		//				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//
		//				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//			}
		//		}
	}

	//pDsp->SetEndOfListHEAD2();
	nTempCountCheck = nNexSumCount;
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 0;


	//pDsp->SetStartListHEAD2(2);
	/////////////////////////////////////////////////////////////NonFlag Start///////////////////////////////////////////////////////////////////////////////////
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
	uJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);


	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);
	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);



	double dScaleFactorXNotching = 0;
	if( FIELD_FARAMETER.KX2 != 0)
		dScaleFactorXNotching = (m_dMaxField / m_dMaxMM) / FIELD_FARAMETER.KX2;


	// pDsp->SetFlyXHEAD2(dScaleFactorXNotching); // 24.10.23_17:54 여기서 리셋 후 노칭 엔코더 스케일로 먹어야함
	pDsp->SetFlyXHEAD2(dScaleFactorX); 

	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);

	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter);




	// 241002_1010 ldy - 노칭 입사각
	dTabAngleTemp = dTabAngleX;
	double dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;

	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}
	// ldy end
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagPower);

	pDsp->N_Mark_Abs(RTC_CARD_NUM_2, dTabAngleX, dBuriedHeightField);


	// 앞은 음양극 모두 노칭오프셋
	double dNonFlagOffset = 0;
	dNonFlagOffset = HEAD2ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	if(dNonFlagOffset > 0)
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagLineSpeed,HEAD2ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_2, dNonFlagOffset, 0);
	}

	dTabAngleX = dTabAngleTemp;

	nNexSumCount += (dBuriedRegion); // 노칭오프셋 2번빼는파트 제거

	double dNotchingKX2 = FIELD_FARAMETER.KX2;
	if(dNotchingKX2 < 0) 
	{
		dNotchingKX2 = -dNotchingKX2;
	}

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX2, 0); // 여기서만 따로 적용되면 될듯?
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount, 1); 


	if(dNonFlagOffset > 0)
	{
		pDsp->N_Mark_Rel(RTC_CARD_NUM_2, dNonFlagOffset , 0);
		pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter );
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_2, -dTabAngleX ,dTabHeightField);

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif

	//2024.01.25 AnalogPowr Use 

	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);


	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);


	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth; 
	nNexSumCount += (dStartTabWidth + dFlagOffsetStart);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); 

	///////////////////////////////////////////////////////////// NonFlag END ///////////////////////////////////////////////////////////////////////////////////
	//----------------------------------------- Flag 한번더 Start---------------------------------------------------------------------------



	u2ndFlagPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);
	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	BOOL bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;

	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);


	if(bZigZagCut == FALSE)
	{
		//pDsp->SetFlyXHEAD2(dScaleFactorX);
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1)
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD2(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_2, (long)(HEAD2ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD2ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD2(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		//else
		//{
		//	for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
		//	{
		//		pDsp->SetFlyXHEAD2(dScaleFactorX);
		//		{
		//			pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//			pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//		}

		//		//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//		nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

		//		nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//	}

		//}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;       
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD2(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;


					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset2;

					//--------------  양극과 틀린부분 --------------------
					//if(nTapIndexCount == 0 && nTabIndex == 0)
					//{
					//nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					//} else
					{
						nNexSumCount += dStartTabWidth;
					}
					//----------------------------------------------------
					nTempCountCheck+=(dStartTabWidth );
				}
				//				else
				//				{
				//					//엔코더로 Flag Width조정
				//					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
				//#ifndef _SIMUL_
				//					n_list_nop(RTC_CARD_NUM_2);
				//#endif
				//					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
				//					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				//					pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
				//
				//					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
				//					//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				//				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck+=dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;

				//if(nTabLengthSumTemp >= dTotalLength) //마지막에는 플래그를 한개 적게 커팅해야함.
				//if( nTabIndex == 6-1 && nTabLengthSumTemp >= (dTotalLength - dStartTabWidthArray[5]) )
				if(  nTempCountCheck >= dTotalLength  )
				{
					// nNexSumCount+=dChangeOffset;
					// nTempCountCheck+=dChangeOffset;
					bBreakFlag=TRUE;

					TRACE("HEAD2 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nTempCountCheck, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
				}

				//2024.06.18 Nonflag i/o 미리 보내기
				if(nTempCountCheck >= dTotalLength - 50 )
				{
					//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
				}

				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					//pDsp->N_Jump_Rel( RTC_CARD_NUM_2, 0 ,   -dTabHeightField);
					//pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   0);
					//pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

					// 2번째 패턴부터는 음양극 공통으로 한번더 긋고 종단부옵셋으로 조절함( 탭 너비 고려 O )
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);


					bBreakFlag = TRUE;
					nNexSumCount+= dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
					TRACE("HEAD2 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nTempCountCheck, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD2ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD2ScannerParameter.cycleOffset;

					dFlagEncSum = nTempCountCheck;
				}
				//nNexSumCount += dStartTabWidth;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		//		else
		//		{
		//			int i = 0;
		//			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
		//			{	
		//				pDsp->SetFlyXHEAD2(dScaleFactorX);
		//				//스캐너로 Flag Width조정
		//				//if(i % 2 == 0)
		//				{
		//					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
		//					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
		//
		//					{
		//						//스캐너로 Flag Width조정
		//						if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
		//						{
		//							if(i % 2 == 0)
		//							{
		//								pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//								pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
		//								pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//								//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//							}
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//						}
		//						else
		//						{
		//							//엔코더로 Flag Width조정
		//							pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//#ifndef _SIMUL_
		//							n_list_nop(RTC_CARD_NUM_2);
		//#endif
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//							pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//							pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//							//pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//						}
		//					}
		//				}
		//
		//				//-----------------------------------------------------------------------------------------------------------
		//
		//				i++;
		//				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
		//
		//				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//				if(i == (int)nFlagCountReal-1)
		//					nNexSumCount+=dChangeOffset;
		//
		//				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);
		//
		//				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//
		//				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//				//n_store_encoder(RTC_CARD_NUM_2, 0);
		//				//n_store_encoder(RTC_CARD_NUM_2, 1);
		//
		//			}
		//		}
	}
	uEndPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);

	//----------------------------------------- Flag 한번더 End---------------------------------------------------------------------------
	//pDsp->nListJumpPos(RTC_CARD_NUM_2, uStartPos);
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif
	pDsp->nListJumpPos(RTC_CARD_NUM_2, uJumpPos);

	nTempCountCheck = nNexSumCount;
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 0;

	//------------------------------------------------------- NG Flag start-------------------------------------------------------------------------------
	u2ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2); 

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);



	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);

	int nCount = 0;
	double dNGTabWidth = 3;
	double dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD2(dScaleFactorX);
		pDsp->N_Mark_Abs( RTC_CARD_NUM_2, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount >= HEAD2ScannerParameter.dMinFlagLeng)
			break;
	}
	//------------------------------------------------------- NG Flag end-------------------------------------------------------------------------------
	//------------------------------------------------------- Core + @ start -------------------------------------------------------------------------------
	// 여기서 SetEndOFListHEAD1() 전에 2번째 NonFlag 만들어서 NG 체크
	u3ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2); // 2번째 노칭시작

	nNexSumCount = 0;

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);
	pDsp->SetFlyXHEAD2(dScaleFactorX);

	//2024.01.25 AnalogPowr Use 
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter);

	// 241002_1010 ldy - 노칭 입사각
	dTabAngleTemp = 0;
	dTabAngleTemp = dTabAngleX;
	dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;



	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}

	// ldy end
	pDsp->N_Mark_Abs(RTC_CARD_NUM_2, dTabAngleX, dBuriedHeightField);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagLineSpeed,HEAD2ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagPower);


	// 음극은 노칭부 엔코더 옵셋으로 조절
	dNonFlagOffset = 0;
	dNonFlagOffset = HEAD2ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	pDsp->N_Mark_Rel(RTC_CARD_NUM_2, dNonFlagOffset, 0);
	dTabAngleX = dTabAngleTemp;


	double dNgLength = 0;
	dNgLength = HEAD2ScannerParameter.ngLength;

	pRunMgr->m_dNGNochingLength = dNgLength + dPatternCorePos;
	nNexSumCount += (pRunMgr->m_dNGNochingLength); // 길이를 받아야함 - 멤버변수로 밑에서 하고오기?

	dNotchingKX2 = FIELD_FARAMETER.KX2;
	if(dNotchingKX2 < 0) 
	{
		dNotchingKX2 = -dNotchingKX2;
	}

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX2, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); 


	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth;

	//--------------------------------------------------------------------------------------------------------------------------------------
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter);

	if(pInitialTable->GetHead1Name() != "Cathode")
	{
		pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_2, -dTabAngleX ,dTabHeightField);

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif
	u3ndFlagStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2); 

	pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter); 

	//20220818 jjsjong
	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);



	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth; 
	nNexSumCount += (dStartTabWidth +  dFlagOffsetStart);
	double dNgoffset = 0.0;
	CString sNgoffset = "";

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round((nNexSumCount + dNgoffset) * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); 

	//-------------------------------------------------------CORE + @ end-------------------------------------------------------------------------------
	//-------------------------------------------------------2nd Flag - NG start-------------------------------------------------------------------------------
	// 점프 전 노칭 로직 완성 - 위 노칭 로직 길이만 수정해서 가져오기

	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;

	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
	if(bZigZagCut == FALSE)
	{
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285 ->  240509 jyh
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD1(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD2(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		//else
		//{
		//	for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
		//	{
		//		pDsp->SetFlyXHEAD2(dScaleFactorX);
		//		{
		//			pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//			pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//		}

		//		//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//		nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

		//		nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//	}

		//}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD2(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset2;

					//--------------  양극과 틀린부분 --------------------
					// 음극일경우 3번째 플래그 보정 없음 - 탭너비 고려 X
					// 양극일경우 3번째 플래그 보정 있음 - 탭너비 고려 O
					/*if(pInitialTable->GetHead1Name() == "Cathode")
					{
					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
					nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
					nNexSumCount += dStartTabWidth;
					}
					} else
					{
					nNexSumCount += dStartTabWidth ;
					}*/

					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
						nNexSumCount += dStartTabWidth;
					}					
					nTempCountCheck+=dStartTabWidth;
				}
				//				else
				//				{
				//
				//					//엔코더로 Flag Width조정
				//					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
				//#ifndef _SIMUL_
				//					n_list_nop(RTC_CARD_NUM_2);
				//#endif
				//					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
				//					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				//					pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
				//
				//					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
				//				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------

				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;
				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck += dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;
				if(  nTempCountCheck >= dTotalLength  )
				{
					bBreakFlag=TRUE;
				}

				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

					bBreakFlag = TRUE;
					nNexSumCount+=dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD2ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD2ScannerParameter.cycleOffset;
					dFlagEncSum = nTempCountCheck;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		//		else
		//		{
		//			int i = 0;
		//			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
		//			{	
		//				pDsp->SetFlyXHEAD2(dScaleFactorX);
		//				//스캐너로 Flag Width조정
		//				//if(i % 2 == 0)
		//				{
		//					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
		//					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
		//
		//					{
		//						//스캐너로 Flag Width조정
		//						if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
		//						{
		//							if(i % 2 == 0)
		//							{
		//								pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//								pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
		//								pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//							}
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//						}
		//						else
		//						{
		//							//엔코더로 Flag Width조정
		//							pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//#ifndef _SIMUL_
		//							n_list_nop(RTC_CARD_NUM_2);
		//#endif
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//							pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//							pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//						}
		//					}
		//				}
		//
		//				//-----------------------------------------------------------------------------------------------------------
		//
		//				i++;
		//				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
		//
		//				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//				if(i == (int)nFlagCountReal-1)
		//					nNexSumCount+=dChangeOffset;
		//
		//				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);
		//
		//				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//
		//				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//			}
		//		}
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif
	//-------------------------------------------------------2nd Flag - NG end-------------------------------------------------------------------------------
	pDsp->nListJumpPos(RTC_CARD_NUM_2, uJumpPos);
	//------------------------------------------------------- NG Wait Flag start-------------------------------------------------------------------------------
	u4ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);

	nNexSumCount = 0;

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);



	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round( nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);

	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter);

	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD2(dScaleFactorX);
		// while문으로 무한대기하고 밑에서 조건문으로 스톱시킬것
		pDsp->N_Mark_Abs( RTC_CARD_NUM_2, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_2, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount > HEAD2ScannerParameter.dNGSensorLeng)
			break;
	}
	pDsp->nListJumpPos(RTC_CARD_NUM_2, u2ndJumpPos);
	//------------------------------------------------------- NG Wait Flag end-------------------------------------------------------------------------------
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 0;
	//------------------------------------------------------- A/C Event Start -------------------------------------------------------------------------------
	u5ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);

	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);

	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD2(dScaleFactorX);
		pDsp->N_Mark_Abs( RTC_CARD_NUM_2, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_2, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount >= 1500) // 임시테스트
			break;
	}
	//------------------------------------------------------- NG Flag end-------------------------------------------------------------------------------
	//-------------------------------------------------------CORE + @ start -------------------------------------------------------------------------------
	// 여기서 SetEndOFListHEAD1() 전에 2번째 NonFlag 만들어서 NG 체크
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
	u6ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2); // 2번째 노칭시작

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);

	nNexSumCount = 0;

	dScaleFactorXNotching = 0; // 241023_1729 LDY 논플래그 스케일 같이 먹도록
	if( FIELD_FARAMETER.KX2 != 0)
		dScaleFactorXNotching = (m_dMaxField / m_dMaxMM) / FIELD_FARAMETER.KX2;

	pDsp->SetFlyXHEAD2(dScaleFactorXNotching);

	// pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);

	//2024.01.25 AnalogPowr Use 
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter);

	// 241002_1010 ldy - 노칭 입사각
	dTabAngleTemp = 0;
	dTabAngleTemp = dTabAngleX;
	dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;

	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}
	// ldy end

	pDsp->N_Mark_Abs(RTC_CARD_NUM_2, dTabAngleX, dBuriedHeightField);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagLineSpeed,HEAD2ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagFreq, HEAD2ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.nonflagPower);


	// 음극은 노칭부 엔코더 옵셋으로 조절
	dNonFlagOffset = 0;
	dNonFlagOffset = HEAD2ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	pDsp->N_Mark_Rel(RTC_CARD_NUM_2, dNonFlagOffset, 0);
	dTabAngleX = dTabAngleTemp;


	dNgLength = 0;
	dNgLength = HEAD2ScannerParameter.ngLength;

	pRunMgr->m_dNGNochingLength = dNgLength + dPatternCorePos;
	nNexSumCount += (pRunMgr->m_dNGNochingLength); // 길이를 받아야함 - 멤버변수로 밑에서 하고오기?

	dNotchingKX2 = FIELD_FARAMETER.KX2;
	if(dNotchingKX2 < 0) 
	{
		dNotchingKX2 = -dNotchingKX2;
	}

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX2, 0);


	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); 


	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth;
	if (dNonFlagOffset > 0)
	{
		pDsp->N_Mark_Rel(RTC_CARD_NUM_2, dNonFlagOffset , 0);  // 241023_ 1729 LDY 기존으로 수정
		pDsp->nSetScannerParameter(RTC_CARD_NUM_2, HEAD2ScannerParameter.nonflagInoutSpeed,HEAD2ScannerParameter);
	}

	if(pInitialTable->GetHead1Name() != "Cathode")
	{
		pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagFreq, HEAD2ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagPower);
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_2, -dTabAngleX ,dTabHeightField);


	//--------------------------------------------------------------------------------------------------------------------------------	
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif
	n6ndFlagPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2ScannerParameter.flagSpeed,HEAD2ScannerParameter); 

	//20220818 jjsjong
	dStartTabWidth = dTabWidth1;
	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);
	nNexSumCount += (dStartTabWidth +  dFlagOffsetStart);
	dNgoffset = 0.0;
	sNgoffset = "";

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round((nNexSumCount + dNgoffset) * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1); 

	//-------------------------------------------------------CORE + @ end-------------------------------------------------------------------------------
	//-------------------------------------------------------3nd Flag - A/C start-------------------------------------------------------------------------------
	// 점프 전 노칭 로직 완성 - 위 노칭 로직 길이만 수정해서 가져오기
	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;

	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
	//pDsp->NOutputIOList(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
	if(bZigZagCut == FALSE)
	{
		//pDsp->SetFlyXHEAD1(dScaleFactorX);
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285 ->  240509 jyh
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD1(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD2(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		//else
		//{
		//	for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
		//	{
		//		pDsp->SetFlyXHEAD2(dScaleFactorX);
		//		{
		//			pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//			pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//		}

		//		//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//		nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

		//		nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//	}

		//}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD2(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset2;

					//--------------  양극과 틀린부분 --------------------
					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
						nNexSumCount += dStartTabWidth;
					}
					//----------------------------------------------------
					nTempCountCheck+=dStartTabWidth;
				}
				//				else
				//				{
				//
				//					//엔코더로 Flag Width조정
				//					pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
				//#ifndef _SIMUL_
				//					n_list_nop(RTC_CARD_NUM_2);
				//#endif
				//					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
				//					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				//					pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
				//
				//					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
				//					//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				//				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;
				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck += dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;

				//if(nTabLengthSumTemp >= dTotalLength) //마지막에는 플래그를 한개 적게 커팅해야함.
				//if( nTabIndex == 6-1 && nTabLengthSumTemp >= (dTotalLength - dStartTabWidthArray[5]) )
				if(  nTempCountCheck >= dTotalLength  )
				{
					// nNexSumCount+=dChangeOffset;
					bBreakFlag=TRUE;

					//TRACE("HEAD1 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
					//// log->WriteString(CWriteLog::MakeFormatString("Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX));
				}


				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					// 2번째 패턴부터는 음양극 공통으로 한번더 긋고 종단부옵셋으로 조절함( 탭 너비 고려 O )
					pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);

					bBreakFlag = TRUE;
					nNexSumCount+=dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD2ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD2ScannerParameter.cycleOffset;
					dFlagEncSum = nTempCountCheck;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		//		else
		//		{
		//			int i = 0;
		//			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
		//			{	
		//				pDsp->SetFlyXHEAD2(dScaleFactorX);
		//				//스캐너로 Flag Width조정
		//				//if(i % 2 == 0)
		//				{
		//					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
		//					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
		//
		//					{
		//						//스캐너로 Flag Width조정
		//						if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
		//						{
		//							if(i % 2 == 0)
		//							{
		//								pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//								pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dFlagDistanceField,   0);
		//								pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//							}
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//						}
		//						else
		//						{
		//							//엔코더로 Flag Width조정
		//							pDsp->N_Mark_Abs( RTC_CARD_NUM_2, dTabAngleX + dAddAmount,   dNotchRootField);
		//#ifndef _SIMUL_
		//							n_list_nop(RTC_CARD_NUM_2);
		//#endif
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//							pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//							pDsp->N_Mark_Rel( RTC_CARD_NUM_2, -dTabAngleX ,   dTabHeightField);
		//							//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//						}
		//					}
		//				}
		//
		//				//-----------------------------------------------------------------------------------------------------------
		//
		//				i++;
		//				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
		//
		//				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//				if(i == (int)nFlagCountReal-1)
		//					nNexSumCount+=dChangeOffset;
		//
		//				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);
		//
		//				pDsp->N_Fly_Return( RTC_CARD_NUM_2,dAddAmount,   dTabHeightField);
		//
		//				pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		//
		//			}
		//		}
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_2, 0);
	n_store_encoder(RTC_CARD_NUM_2, 1);
#endif
	//-------------------------------------------------------3nd Flag - AC end-------------------------------------------------------------------------------
	pDsp->nListJumpPos(RTC_CARD_NUM_2, uJumpPos);
	//------------------------------------------------------- A/C Event End ---------------------------------------------------------------------------------
	//------------------------------------------------------- A/C Wait Flag start-------------------------------------------------------------------------------
	u7ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_2);

	nNexSumCount = 0;

	pDsp->SetFlyXHEAD2(1.0); 
	pDsp->SetFlyXHEAD2(0.0);
	pDsp->SetFlyYHEAD2(1.0); 
	pDsp->SetFlyYHEAD2(0.0);


	pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);



	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD2(dScaleFactorX);
		// while문으로 무한대기하고 밑에서 조건문으로 스톱시킬것
		pDsp->N_Mark_Abs( RTC_CARD_NUM_2, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_2, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_2, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_2, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD2(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount > dACSensorLength) // AC태그위치까지 대기
			break;
	}
	pDsp->nListJumpPos(RTC_CARD_NUM_2, u5ndJumpPos);
	//------------------------------------------------------- A/C Wait Flag end-------------------------------------------------------------------------------

	pDsp->SetEndOfListHEAD2();
	pDsp->SetFirstStart(FALSE);

#ifndef _SIMUL_
	//n_execute_list(RTC_CARD_NUM_2,1);
#endif

	/*strTemp.Format("FlagEncSum: %.3f, Cycle Offset: %.3f, FlagStart: %.3f, FlagEnd: %.3f", dFlagEncSum, dChangeOffset, dFlagOffsetStart, dFlagOffsetEnd);
	pDlg->SetDlgItemText(IDC_CTTEXT_PARA_INFO, strTemp);*/

	UINT nListNumber = 1;

	UINT uErrorbit = -1;

	BOOL bErrorCheck = FALSE;

	BOOL bEnabledLaser = TRUE;
	BOOL bEnabledFlag = TRUE;

	LONG HEAD2_EncoderY,HEAD2_EncoderX;
	HEAD2_EncoderX=0;HEAD2_EncoderY=0;
	UINT uBusy, uPos;
#ifdef _SIMUL_
	//return 0;
#endif

	double dEncoderPos = HEAD2_EncoderY / FIELD_FARAMETER.KX2;//500;

	BOOL bNGLasor = TRUE;
	BOOL bNGFlag = TRUE;

	BOOL bNgFlagTmp = TRUE;
	BOOL bNgNonFlagTmp = TRUE;


	// pDsp->EnableLaserHEAD1();
#ifndef _SIMUL_
	n_execute_list(RTC_CARD_NUM_2,1); // ldy _ 240930_1612
#endif

	//m_bHEAD2ListSucc = TRUE;  // 리스트 다운로드 체크변수 24.10.16 11:10

#ifdef _SIMUL_
	return 0;
#endif

	// 여기서 현재 엔코더값 기록 후 쭉 더하기
	// 파라미터값 확인하기!
	long nNgX,nNgY;

	int nNgTriger = -1;

	int bNGCheck = -1; // -1 : 대기  /  0 : 논플래그  /  1 : 플래그 


	BOOL bNGFlagCheck = FALSE;

	BOOL bACCheck_prev = TRUE;
	BOOL bACCheck = TRUE;

	while( pRunMgr->m_bThreadAlive2 ) 
	{
		//CDsp *pDsp = CDsp::GetInstance();
		//pDsp->GetEncodeHEAD1(encoderX, encoderY);

#ifndef _TestMC_

		if(pDsp->nGetInputValue(RTC_CARD_NUM_2,RTC_SIG_I_LASER_ON)== TRUE)
		{
			bEnabledLaser = TRUE;
			if(bEnabledFlag != bEnabledLaser)
			{
				pDsp->EnableLaserHEAD2();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
		}
		else
		{   
			bEnabledLaser = FALSE;
			if(bEnabledFlag != bEnabledLaser)
			{
				pDsp->DisableLaserHEAD2();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, FALSE);

		}
		bEnabledFlag = bEnabledLaser;

#endif
		stStat = pDsp->ReadStatusHEAD2();

#ifndef _SIMUL_
		uErrorbit = n_get_marking_info(RTC_CARD_NUM_2);

		UINT nGetMarkingInfo = uErrorbit;//get_marking_info();
		UINT nXUnderFlowCheckBit  = 0x0003;
		UINT nXOverFlowCheckBit  = 0x0030;
		UINT nYUnderFlowCheckBit  = 0x000C;
		UINT nYOverFlowCheckBit  = 0x00C0;

		if((nGetMarkingInfo & nXUnderFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("XUnderlow");
			}
		}
		if((nGetMarkingInfo & nXOverFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("XOverFlow");
			}
		}
		if((nGetMarkingInfo & nYUnderFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("YUnderFlow");
			}
		}
		if((nGetMarkingInfo & nYOverFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("YOverFlow");
			}
		}

#endif

		dNgLength = 0;
		dNgLength = HEAD2ScannerParameter.ngLength; // 알파값
		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		if (uPos > uJumpPos && uPos < u2ndFlagPos)
		{
			// nonFlag
			bNGCheck = 0;
		}		
		else
		{
			// Flag
			bNGCheck = 1;
		}


		// 외곽부 + 코어부 = 노칭길이
		dPatternOutPos = 0; // 외곽부 길이 - 추가완료 
		dPatternOutPos = m_stNotchPatternData.dNochingOutPosWidth;

		dPatternCorePos = 0; // 코어부 길이 >> 노칭 - 외곽
		dPatternCorePos = dBuriedRegion - dPatternOutPos;

		double dMinWinderLeng;	// 최소권취길이 >> 1150mm
		double dFirstTabArea;	// 첫탭구간 값 >> 950mm
		double dSensorLeng;		// 센서인식길이 - 200mm 고정

		// test
		dFirstTabArea = HEAD2ScannerParameter.dMinFlagLeng; // 최소권취길이
		dSensorLeng = HEAD2ScannerParameter.dNGSensorLeng; // NG태그 센서부터 현 가공위치의 길이

		dMinWinderLeng = dFirstTabArea + dSensorLeng;

		double dPrePatternLeng;
		CString strLogData;

		// 변수 2개 추가 - NON / Flag 
		// if(pDlg->IsDlgButtonChecked(IDC_CHECKBOX_ENABLE_NGTAG)) //NGTAG 체크박스 체크시
		// {
		// 	if(pDsp->nGetInputValue(RTC_CARD_NUM_2,RTC_SIG_I_FIRST_TAB) == TRUE) // NG 신호시 - 1
		// 	{
		// 		// 현재 가공이 어딘지 알아야함.
		// 		// NG 태그센서 길이부터 가공위치까지 
		// 		pDsp->GetEncodeHEAD2(nNgX, nNgY);
		// 
		// 		bNGLasor = TRUE;
		// 		if(bNGFlag != bNGLasor)
		// 		{
		// 			log->WriteString2("HEAD2 NG Tag On", "");
		// 
		// 			dPrePatternLeng = (nNgY / -pFieldParameter->GetKY2()); 
		// 			double dNgTagPredictSensorLeng; // NG 태그 위치 ( 예측 )
		// 			dNgTagPredictSensorLeng = dPrePatternLeng + dSensorLeng; // 현재 가공위치( 현재 엔코더값 + NG태그 센서부터 현 가공위치의 길이 ) // 115
		// 
		// 			strLogData.Format("dPrePatternLeng : %0.1f", dPrePatternLeng);
		// 			log->WriteString2("HEAD2 NG Tag On", "");
		// 
		// 			// NG태그 위치 찾아서( 센서길이 + 현재 엔코더 위치 )
		// 			dTotalLength; // 패턴길이
		// 			dBuriedRegion; // 노칭길이
		// 			double dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 한패턴 길이 ( 플래그 + 논플래그 )
		// 
		// 			if( dNgTagPredictSensorLeng > dOneCyclePatternLeng  ) // 전체 패턴( 논플 + 플래그 )보다 NG태그위치가 멀다면 - 프로그램 시작 후 2번째 패턴 이후( 프로그램 재시작시 첫 플래그 패턴 대비 위함 )
		// 			{
		// 				// 다음 패턴의 논플래그 혹은 플래그 판단하기 위함
		// 				if( dNgTagPredictSensorLeng > dOneCyclePatternLeng + dBuriedRegion ) // 한패턴 + 논플래그 길이 보다 크다면
		// 				{
		// 					// NG태그 플래그 위치 -> NG위치에서 앞으로 1000mm 했을때 코어부인지 외곽부인지
		// 					if( (dNgTagPredictSensorLeng - dOneCyclePatternLeng - 1000) > dPatternOutPos ) // dPatternOutPos : 노칭 외곽부
		// 					{
		// 						log->WriteString2("HEAD2 NG Tag Pos = 1000mm CorePos -> NO.5 ", "");
		// 						// 코어부라면
		// 						// NG태그 앞 1000mm 기준 코어부에 위치
		// 						double dBetweenSensorToFlagEndLength;
		// 						dBetweenSensorToFlagEndLength = dOneCyclePatternLeng - dPrePatternLeng; // NG 센서 신호 시 가공부부터 종단부까지의 길이.( 전체 패턴길이 - 현재 엔코더 길이 )
		// 
		// 						while(1)
		// 						{
		// 
		// 							// 엔코더 리셋 위치까지 대기
		// 							pDsp->GetEncodeHEAD2(nNgX, nNgY);
		// 							Sleep(1);
		// 							pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
		// 							if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
		// 							{
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		// 								pDlg->SetDelayTime(10);
		// 							}		
		// 							else
		// 							{
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		// 								pDlg->SetDelayTime(10);
		// 							}
		// 
		// 							if(( nNgY / -pFieldParameter->GetKY2()) <= dPatternOutPos)
		// 								break;
		// 						}
		// 						pDsp->GetEncodeHEAD2(nNgX, nNgY);
		// 
		// 						// NG 센서까지의 남은거리만큼 대기
		// 						while( ( nNgY / -pFieldParameter->GetKY2() ) <= ( dSensorLeng - dBetweenSensorToFlagEndLength ) )
		// 						{
		// 							pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
		// 							if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
		// 							{
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		// 								pDlg->SetDelayTime(10);
		// 							}		
		// 							else
		// 							{
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
		// 								pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		// 								pDlg->SetDelayTime(10);
		// 							}
		// 							pDsp->GetEncodeHEAD2(nNgX, nNgY);
		// 							Sleep(1);
		// 						}
		// 
		// 						n_stop_execution(RTC_CARD_NUM_2); // 리스트 스톱
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
		// 						n_execute_list_pos(RTC_CARD_NUM_2, 1, u2ndJumpPos); // 첫탭구간 가공
		// 
		// 					} else
		// 					{
		// 						log->WriteString2("HEAD2 NG Tag Pos = 1000mm OutPos -> NO.4 ", "");
		// 						// 외곽부라면
		// 						// NG태그 앞 1000mm 기준 외곽부에 위치
		// 						n_stop_execution(RTC_CARD_NUM_2);
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
		// 						n_execute_list_pos(RTC_CARD_NUM_2, 1, u4ndJumpPos); 
		// 					}
		// 				} else
		// 				{
		// 					log->WriteString2("HEAD2 NG Tag Pos = NonFlag -> NO.2, NO.3 ", "");
		// 					// NG 태그 논플래그 위치 한다면
		// 					// 코어부 + 외곽부 같은 조건
		// 					// 3mm로 쭉 가공하다가 NG태그위치왔을때 1000mm + 첫탭가공
		// 					n_stop_execution(RTC_CARD_NUM_2);
		// 					pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
		// 					n_execute_list_pos(RTC_CARD_NUM_2, 1, u4ndJumpPos);
		// 				}
		// 			}else
		// 			{
		// 				log->WriteString2("HEAD2 NG Tag Pos = Flag -> NO.1 ", "");
		// 				// 한패턴보다 NG태그위치가 가까우면 -> 즉, 첫패턴의 플래그에 위치할 경우
		// 				// NG태그 위치까지 대기 후 1000mm + 첫탭가공
		// 				while( ( nNgY / -pFieldParameter->GetKY2()) <= dNgTagPredictSensorLeng )
		// 				{
		// 					pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
		// 					if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
		// 					{
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		// 						pDlg->SetDelayTime(10);
		// 					}		
		// 					else
		// 					{
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
		// 						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		// 						pDlg->SetDelayTime(10);
		// 					}
		// 					pDsp->GetEncodeHEAD2(nNgX, nNgY);
		// 					Sleep(1);
		// 				}
		// 				n_stop_execution(RTC_CARD_NUM_2); // 리스트 스톱
		// 				// 첫탭길이만큼 진행 이후
		// 				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
		// 				n_execute_list_pos(RTC_CARD_NUM_2, 1, u2ndJumpPos); // 1000mm 플래그 채워주고 첫탭가공
		// 			}
		// 		}
		// 	} 
		// 	else
		// 	{
		// 		bNGLasor = FALSE;
		// 		if(bNGFlag != bNGLasor)
		// 		{
		// 		}
		// 	}
		// 	bNGFlag = bNGLasor;
		// }

		double dACPrePatternLeng;
		dACSensorLength = HEAD2ScannerParameter.dACSensorLeng;// 임시 테스트
		double dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 전체길이

		if(pDsp->nGetInputValue(RTC_CARD_NUM_2, RTC_SIG_I_AUTO_CHANGE) == TRUE) // mjy
		{
			pDsp->GetEncodeHEAD2(nNgX, nNgY);
			dACPrePatternLeng = 0;

			bACCheck_prev = TRUE;
			if(bACCheck != bACCheck_prev)
			{
				dACPrePatternLeng = (nNgY / -FIELD_FARAMETER.KX2);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);

				double dBetweenACSensorToFlagEndLength;
				dBetweenACSensorToFlagEndLength = dOneCyclePatternLeng - dACPrePatternLeng; 

				while(1)
				{
					// 엔코더 리셋 위치까지 대기
					pDsp->GetEncodeHEAD2(nNgX, nNgY);
					Sleep(1);
					pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
					if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
					{
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
						pRunMgr->SetDelayTime(10);
					}		
					else
					{
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
						pRunMgr->SetDelayTime(10);
					}

					if(( nNgY / -FIELD_FARAMETER.KX2) <= dPatternOutPos)
						break;
				}
				pDsp->GetEncodeHEAD2(nNgX, nNgY);

				// NG 센서까지의 남은거리만큼 대기
				while( ( nNgY / -FIELD_FARAMETER.KX2 ) <= ( dACSensorLength - dBetweenACSensorToFlagEndLength ) )
				{
					pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
					if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
					{
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
						pRunMgr->SetDelayTime(10);
					}		
					else
					{
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
						pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
						pRunMgr->SetDelayTime(10);
					}
					pDsp->GetEncodeHEAD2(nNgX, nNgY);
					Sleep(1);
				}
				n_stop_execution(RTC_CARD_NUM_2); 
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);
				n_execute_list_pos(RTC_CARD_NUM_2, 1, u5ndJumpPos);
			}
		} else
		{
			bACCheck_prev = FALSE;
			if(bACCheck != bACCheck_prev)
			{
			}
		}
		bACCheck = bACCheck_prev;

		pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
		if (!((uPos > uJumpPos - 15 && uPos < u2ndFlagPos + 15) || (u6ndJumpPos - 15 < uPos && uPos < n6ndFlagPos  + 15) || (uPos < u3ndFlagStartPos + 15 && uPos > u3ndJumpPos - 15)))
		{
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, 6, FALSE);
		}
		else
		{
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_FIRST_TAB, TRUE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		}
		CFileMgr pFileMgr;

		double dTriggerWidth; // 리셋 전 거리
		dTriggerWidth = pFileMgr.ReadDouble(_T("HEAD2"), _T("TriggerWidth"), _T(".\\DustCollectorTrigger.ini"));
		dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;
		dBuriedRegion = m_stNotchPatternData.dNochingWidth;
		dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 패턴 전체길이 ( 노칭 + 커팅 )
		pDsp->GetEncodeHEAD2(nNgX, nNgY);

		pDsp->nGetstatus(RTC_CARD_NUM_2, uBusy, uPos );
		if(uPos >= nStartPos && uPos < uJumpPos )
		{
			// 첫 패턴
			if( (nNgY / -FIELD_FARAMETER.KX2) > dTotalLength - dTriggerWidth  && (nNgY / -FIELD_FARAMETER.KX2) < dTotalLength)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, 6, TRUE);
			}
		} else
		{
			if( (nNgY / -FIELD_FARAMETER.KX2) > dOneCyclePatternLeng - dTriggerWidth  && (nNgY / -FIELD_FARAMETER.KX2) < dOneCyclePatternLeng)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_2, 6, TRUE);
			}
		}
		pRunMgr->m_bReStartProgramHEAD2 = FALSE; // 재시작
		Sleep(10);
	}
	return 0;	
}

DWORD WINAPI CRunMgr::ExecutePatternSDI_Head1(LPVOID lparam)
{
	CRunMgr* pRunMgr = (CRunMgr*)lparam;
	IniUtil _iniUtil;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	_iniUtil.LoadParameterIni( _T("HEAD1"), ParamPath, HEAD1ScannerParameter);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	double dScale = pInitialTable->GetFieldScale();
	CWriteLog *log= NULL;
	CDsp *pDsp = CDsp::GetInstance();

	TListExeStat stStat; stStat.clear();
	CMathUtil mathUtil;
	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();

	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	// pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	double cs,sn;
	double m_dMaxField;
	double m_dMaxMM;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CString strTemp;
	//_NOTCH_PATTERN_DATA m_stNotchPatternData = pFieldParameter->GetHEAD1PatternDataOfKoem();

	_SDI_NOTCH_PATTERN_DATA m_stNotchPatternData;
	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, m_stNotchPatternData);

	//2023.11.15 Excelli Test --------------------------------------------------------------------------------------------
	double dFlagOffsetEnd = HEAD1ScannerParameter.cycleOffset;
	double dFlagOffsetStart = HEAD1ScannerParameter.flagOffset; // 240503 jyh

	LONG CornerScale = 500;  
	LONG EndScale = 500;
	LONG AccScale = 50;
	UINT uMode, uPrevTime,uVmax,uAmax;
	uPrevTime=0;uVmax=0;uAmax=0;

	CornerScale = (LONG)HEAD1ScannerParameter.polygonDelay;
	EndScale = (LONG)HEAD1ScannerParameter.markDelay;
	AccScale = (LONG)HEAD1ScannerParameter.jumpDelay;

#ifdef _RTC6_	
	//Scanahead: calculate delays automatically. excelliscan
	//(const UINT CardNo, const UINT Mode, const UINT HeadNo, const UINT TableNo, const UINT PreViewTime, const UINT Vmax, const double Amax);
#ifndef _SIMUL_
	select_rtc(RTC_CARD_NUM_1);
	n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	n_activate_scanahead_autodelays(RTC_CARD_NUM_1, 1);
	n_set_scanahead_line_params(RTC_CARD_NUM_1,CornerScale, EndScale, AccScale );
	n_set_scanahead_laser_shifts(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif

	UINT iListNumber = 1;
	CString strTmp;

	//2022.11.25 Flip Test
	LONG firstPosX,firstPosY, encoderX, encoderY;
	BOOL bFirstRunFlag=  TRUE;	BOOL FirstAutoFlag = TRUE;
	BOOL bLastMarkFlag = FALSE;

	pFieldParameter->SetKxKy(FIELD_FARAMETER.KX, FIELD_FARAMETER.KY);

	double dScaleFactorX,dScaleFactorY;
	dScaleFactorX = 0.0;dScaleFactorY = 0.0;

	if( pFieldParameter->GetKX() != 0)
		dScaleFactorX = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKX();
	if( pFieldParameter->GetKY() != 0)
		dScaleFactorY = (m_dMaxField / m_dMaxMM) / -pFieldParameter->GetKY();

	double dStartCutPosX = 0; // Ä¿ÆÃ ½ÃÀÛ Æ÷Áö¼Ç
	dStartCutPosX = dStartCutPosX * m_dMaxField / m_dMaxMM;
	//BaseLine Data 
	double dNonflagStartHeight,dNonflagEndWidth,dNonflagEndHeight;
	double dTotalWidth,dFoilExtention,dHEAD1Width,dBuriedHeight,dNotchRoot,dNublessHeight;
	double dTabWidth,dTabHeight,dTabCount,dBuriedRegion,dNublessRegion,dPitchLength;
	double dTabAngle, dFlagStartWidth, dChangeOffset;


	int iStepindex = STEP_UNFLAG_START;
	int iStartSpeed = pParameter->GetUnflagLineSpeed();

	dNonflagStartHeight  = 0; //= m_stNotchPatternData.dNonflagStartHeight; // o  Check
	dNublessRegion = 0; // = m_stNotchPatternData.dNublessRegion; // x
	dNublessHeight = 0; // = m_stNotchPatternData.dNublessHeight; // x
	dNotchRoot = 0; // = m_stNotchPatternData.dNotchRoot; // o
	dTabWidth = 0; // = m_stNotchPatternData.dTabWidth; // x
	dTabCount = 0; // = m_stNotchPatternData.dTabCount; // ?
	dTabHeight = m_stNotchPatternData.dCuttingHeight + HEAD1ScannerParameter.dCuttingOffset; // ㅇ
	dBuriedRegion = m_stNotchPatternData.dNochingWidth; // ㅇ
	dBuriedHeight = m_stNotchPatternData.dNochingHeight; // ㅇ
	dNonflagEndWidth = 0; // = m_stNotchPatternData.dNonflagEndWidth; // ㄴ
	dNonflagEndHeight = 0; // = m_stNotchPatternData.dNonflagEndHeight; // ㄴ
	dTabAngle = m_stNotchPatternData.dCuttingAngle; // ㅇ
	dFoilExtention = 0; // = m_stNotchPatternData.dFoilExtention; // ? 
	dHEAD1Width = 0; // = m_stNotchPatternData.dHEAD2Width; // ?
	dTotalWidth = m_stNotchPatternData.dTotalWidth; //dHEAD1Width + dFoilExtention;
	dFlagStartWidth = 0; // = m_stNotchPatternData.dFlagStartWidth; // ?
	dChangeOffset = FIELD_FARAMETER.CycleOffset;


	dNonflagStartHeight = dNonflagStartHeight - dHEAD1Width;
	dNublessHeight = dNublessHeight - dHEAD1Width;
	dNotchRoot = dHEAD1Width - dNotchRoot; 
	dBuriedHeight = m_stNotchPatternData.dCuttingHeight - dBuriedHeight;
	dNonflagEndHeight = dNonflagEndHeight - dHEAD1Width;


	double  dNonflagStartHeightField, dNonflagEndWidthField, dNonflagEndHeightField;
	double dTotalWidthField, dFoilExtentionField, dHEAD1WidthField, dBuriedHeightField, dNotchRootField, dNublessHeightField;
	double dTabWidthField, dTabHeightField, dBuriedRegionField, dNublessRegionField, dPitchLengthField;
	double dFlagStartWidthField, dChangeOffsetField;

	dNonflagStartHeightField = dNonflagStartHeight * m_dMaxField / m_dMaxMM;
	dNonflagEndWidthField = dNonflagEndWidth * m_dMaxField / m_dMaxMM;
	dNonflagEndHeightField = dNonflagEndHeight * m_dMaxField / m_dMaxMM;
	dTotalWidthField = dTotalWidth * m_dMaxField / m_dMaxMM;
	dFoilExtentionField = dFoilExtention * m_dMaxField / m_dMaxMM;
	dHEAD1WidthField = dHEAD1Width * m_dMaxField / m_dMaxMM;
	dBuriedHeightField = dBuriedHeight * m_dMaxField / m_dMaxMM;
	dNotchRootField = dNotchRoot * m_dMaxField / m_dMaxMM;
	dNublessHeightField = dNublessHeight * m_dMaxField / m_dMaxMM;
	dTabWidthField = dTabWidth * m_dMaxField / m_dMaxMM;
	dTabHeightField = dTabHeight * m_dMaxField / m_dMaxMM;
	dBuriedRegionField = dBuriedRegion * m_dMaxField / m_dMaxMM;
	dNublessRegionField = dNublessRegion * m_dMaxField / m_dMaxMM;
	dFlagStartWidthField = dFlagStartWidth * m_dMaxField / m_dMaxMM;
	dChangeOffsetField = dChangeOffset * m_dMaxField / m_dMaxMM;

	dNonflagEndWidthField = dNonflagEndWidthField - dStartCutPosX;
	dNublessRegionField = dNublessRegionField - dFlagStartWidthField;

	double dUnflagStartSloopX, dTabAngleX;
	double dBuriedSloopX;
	dUnflagStartSloopX = 0;dTabAngleX=0;dBuriedSloopX=0;


	//2023.07.10 Samsung Pattern Test
	double dStartTabWidth = m_stNotchPatternData.dCuttingTabWidth1;
	double dFinalTabWidth = m_stNotchPatternData.dCuttingTabWidth6;
	double dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;
	dTabCount = (dTotalLength * 2)/(dStartTabWidth + dFinalTabWidth);
	double dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount - 1.0);
	//double dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount );
	double dSimulatedTotalLength = dTabCount * (dStartTabWidth + dFinalTabWidth) / 2.0;

	double dTabWidth1,dTabWidth2,dTabWidth3,dTabWidth4,dTabWidth5,dTabWidth6;
	double dStartTabWidthArray[10];
	double dStartTabWidthArraySum[10];
	double dSecondTabWidth = 0;

	double dPatternCorePos;
	double dPatternOutPos;
	dPatternOutPos = m_stNotchPatternData.dNochingOutPosWidth;
	dPatternCorePos = dBuriedRegion - dPatternOutPos;

	double dACSensorLength;
	dACSensorLength = HEAD1ScannerParameter.dACSensorLeng;


	for(int i = 0; i < 10; i++)
	{
		dStartTabWidthArray[i] = 0;
		dStartTabWidthArraySum[i] = 0;
	}

	int nGroupCnt = 6;
	double dTabLengthDivided ;
	//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
	{
		//dTabCount = nGroupCnt; //SDI 고정 6구간
		dSimulatedTotalLength = dTabCount * (dStartTabWidth + dFinalTabWidth) / 2.0;
		dTabWidth = dFinalTabWidth;
		dFlagAllowance = (dFinalTabWidth - dStartTabWidth) / (dTabCount - 1.0);

		//2023.08.03 For 삼성SDI 샘플 ===============================================================================
		dTabWidth1 = 0;dTabWidth2=0;dTabWidth3=0;dTabWidth4=0;dTabWidth5=0;dTabWidth6=0;
		dTabWidth1 = m_stNotchPatternData.dCuttingTabWidth1; // 240503 jyh
		dTabWidth2 = m_stNotchPatternData.dCuttingTabWidth2;
		dTabWidth3 = m_stNotchPatternData.dCuttingTabWidth3;
		dTabWidth4 = m_stNotchPatternData.dCuttingTabWidth4;
		dTabWidth5 = m_stNotchPatternData.dCuttingTabWidth5;
		dTabWidth6 = m_stNotchPatternData.dCuttingTabWidth6;

		dStartTabWidthArray[0] = dTabWidth1;
		dStartTabWidthArray[1] = dTabWidth2;
		dStartTabWidthArray[2] = dTabWidth3;
		dStartTabWidthArray[3] = dTabWidth4;
		dStartTabWidthArray[4] = dTabWidth5;
		dStartTabWidthArray[5] = dTabWidth6;
		dStartTabWidthArray[6] = dTabWidth6;
		dStartTabWidthArray[7] = dTabWidth6;
		dStartTabWidthArray[8] = dTabWidth6;
		dStartTabWidthArray[9] = dTabWidth6;


		dStartTabWidthArraySum[0] = dStartTabWidthArray[0] * m_stNotchPatternData.dCuttingCount1;

		for(int i = 1; i < 10; i++)
		{
			if(i == 1)
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount2;
			} else if( i == 2 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount3;
			} else if( i == 3 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount4;
			} else if( i == 4 )
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount5;
			} else
			{
				dStartTabWidthArraySum[i] = dStartTabWidthArraySum[i-1] + dStartTabWidthArray[i] *  m_stNotchPatternData.dCuttingCount6;
			}

		}

		if(dTabWidth1 > 0 || dTabWidth2 > 0 || dTabWidth3 > 0 || dTabWidth4 > 0 || dTabWidth5 > 0 || dTabWidth6 > 0 )
			dFlagAllowance = 0;
	}

	int nTabIndex = 0;
	double nTabLengthSumTemp = 0;
	double nTempCountCheck = 0;

	nTabIndex = 0;



	//=============================================================================================================
	double dRadian = 0;

	if(dTabAngle != 0)
	{

		dRadian = ( dTabAngle  / 180.0f) * M_PI;

		dUnflagStartSloopX = ((dTabHeight - dNonflagStartHeight)*tan(dRadian));
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dBuriedSloopX = ((dTabHeight - dBuriedHeight)*tan(dRadian));


		dUnflagStartSloopX = dUnflagStartSloopX * m_dMaxField / m_dMaxMM;
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
		dBuriedSloopX = dBuriedSloopX * m_dMaxField / m_dMaxMM;
	}
	//--------------------------------------------------------------------------------------

	double iRealdistence = 0, iScnSpeed = 0, iRollSpeed = 0;
	iScnSpeed = pParameter->GetUnflagLineSpeed();
	iRollSpeed = pFieldParameter->GetRollSpeed();

	int i = 0, iFieldWidth = 0;
	iFieldWidth = pFieldParameter->GetMarkingField();
	BOOL bSimulOn = pFieldParameter->GetSimulationFlag();


	cs = cos(PI * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(PI * pFieldParameter->GetFieldAngle() / 180);

	if(m_stNotchPatternData.bFlip)
		pDsp->SetFlipHead1(TRUE);
	else
		pDsp->SetFlipHead1(FALSE);

	pDsp->SetMatrixHEAD1(cs,sn);

	int nTapIndexCount = 0;
	double nEncoderScaleX = 40.0;
	double nEncoderScaleY = 40.0;
	int nSpeedIndexTest = 0;
	double nNexSumCount = 0;
	double nStartPos = 0;
	double dFlagEncSum = 0;

	pRunMgr->m_nEncoderSumCount = nStartPos;
	nEncoderScaleX = -pFieldParameter->GetKX();
	if(nEncoderScaleX < 0) nEncoderScaleX = -nEncoderScaleX;
	nEncoderScaleY = pFieldParameter->GetKY();

	int iXoffset, iYoffset;
	firstPosX = 0;
	firstPosY = -dTabHeight;
	pDsp->EnableLaserHEAD1();
	iStepindex = 0;


	UINT Minvalue,Maxvalue;
	Minvalue = 0;
	Maxvalue = 4095;

	//2021.07.07 TestDebug
	int nFlagStartOffsetx;
	nFlagStartOffsetx = 100 * m_dMaxField / m_dMaxMM;


	double dFlagOffset = 0;


	double dRollSpeed = pFieldParameter->GetRollSpeed();
	double dUnflagScannerSpeed = pParameter->GetUnflagLineSpeed();
	pDsp->StopExcutionHEAD1();



#ifndef _RTC_Test_				
	const double dFlagSafeAreaLength = 125;
#else
	const double dFlagSafeAreaLength = m_dMaxMM;

#endif


	bool bIsShotFlag = false;

	firstPosX = 0;


	pDsp->SetFirstStart(TRUE);
	pRunMgr->m_nEncoderSumCount = 0;
	dChangeOffset = HEAD1ScannerParameter.cycleOffset;

	const double dMaxValidPos = 0;
	const double dAddAmount = 0;
	double dTempValue = 0;
	double dOverflowField = m_dMaxMM / 2 *  m_dMaxField / m_dMaxMM;  
	double dFlagDistanceField = 0;
	LONG HEAD1EncoderY,HEAD1EncoderX;
	HEAD1EncoderX=0;HEAD1EncoderY=0;
	//----------------------------2024.06.13 이어작업 기능추가 테스트 --------------------------------------------
	CString strHEAD1Encoder; //, strHEAD1Encoder;

	double dHEAD1Enc, dHEAD2Enc;

	_iniUtil.LoadEncIni(dHEAD1Enc, dHEAD2Enc);

	double HEAD1TmpEncY;
	if( dHEAD1Enc > 0 )
	{
		HEAD1TmpEncY = dHEAD1Enc * -pFieldParameter->GetKX();
	} else
	{
		pDsp->GetEncodeHEAD1(HEAD1EncoderX,HEAD1EncoderY);
		HEAD1TmpEncY = HEAD1EncoderY;
	}




	double dRestartTotalLeng;
	dRestartTotalLeng = 0; // test

	//Y축 엔코더가 위치제어용으로 사용중
	strTemp.Format("H1_0 %.3f mm", HEAD1TmpEncY / -pFieldParameter->GetKX());

	double dSumCountPrev = HEAD1TmpEncY / -pFieldParameter->GetKX();
	double dSumCountTemp = 0;

	if(dSumCountPrev > m_stNotchPatternData.dNochingWidth)
	{
		dRestartTotalLeng = dSumCountPrev =  dSumCountPrev - m_stNotchPatternData.dNochingWidth;
	} else 
	{
		//pDlg->SetDlgItemText(IDC_SAVED_HEAD1ENC, _T("0.0"));

#ifdef _RTC5_
		n_init_fly_2d(RTC_CARD_NUM_1,0,0);
#else
		n_init_fly_2d(RTC_CARD_NUM_1,0,0,0);
#endif
	}

	if(HEAD1TmpEncY > 0 )
	{
		dSumCountTemp -= (dFlagOffsetStart + FIELD_FARAMETER.CycleOffset);
	}

	while(1)
	{
		if(dSumCountTemp >= dStartTabWidthArraySum[nTabIndex] )
		{
			nTabIndex++;
			dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

		}
		else if( (dSumCountTemp + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
		{
			dStartTabWidth = dStartTabWidthArray[nTabIndex];
			dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
		}
		else
		{
			dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
		}

		dSumCountTemp += (dStartTabWidth + dSecondTabWidth);
		if(dSumCountTemp >= dSumCountPrev)
			break;
	}
	if(dStartTabWidth == 0)
		dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];


	//if(nTabIndex > 0)
	//{
	//	dTempValue = fmod(dSumCountPrev, dStartTabWidth + dSecondTabWidth);
	//	//dTempValue = fmod(dSumCountPrev-dStartTabWidthArraySum[nTabIndex-1], dStartTabWidth + dSecondTabWidth);
	//	//dStartTabWidth = dTempValue;
	//	dStartTabWidth = dSumCountTemp - dSumCountPrev;
	//}
	//else
	//{
	//	dTempValue = fmod(dSumCountPrev, dStartTabWidth + dSecondTabWidth);
	//	//dStartTabWidth = (dStartTabWidth + dSecondTabWidth) - dTempValue;
	//	//dStartTabWidth = dTempValue;
	//	dStartTabWidth = dSumCountTemp - dSumCountPrev;
	//}

	dTempValue = dStartTabWidth + dSecondTabWidth - (dSumCountTemp - dSumCountPrev);

	// 리셋햇을때
	if(dSumCountPrev == 0 )
	{
		dStartTabWidth = dStartTabWidthArray[nTabIndex];
	} else
	{
		dStartTabWidth = dSumCountTemp - dSumCountPrev;
	}

	//=============================================================================================================

	pDsp->SetGotoXYHEAD1(0,   dTabHeightField); // test


	pDsp->SetStartListHEAD1(1);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter);

#ifdef _RTC_Test_				
	double dCurrent = pParameter->GetLaserPowerSet();
	if(pDsp->GetInitialStatus())
	{
		write_8bit_port((unsigned short)(dCurrent));
		write_8bit_port_list((unsigned short)(dCurrent));


		pDsp->OutputIOList(RTCIO_O_MO, true);
		pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
	}
#endif

	pDsp->ClearFlyOverflowHEAD1(15);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);

#ifdef _RTC6_
#ifndef _SIMUL_
	n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif
#endif


	int nFlagCountReal = 0;	
	nFlagCountReal = dTabCount; 

	double dTmpSumCountPrev = dSumCountPrev;
	double dNexSumCountBef = 0.0; // test

	pDsp->SetFlyYHEAD1(1.0); pDsp->SetFlyYHEAD1(0.0);
	pDsp->SetFlyXHEAD1(1.0); pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyXHEAD1(dScaleFactorX);

	nNexSumCount = 0;

	BOOL bMarkCheck = (dStartTabWidth > dTempValue);

	if(dStartTabWidth > dTempValue)
	{
		nNexSumCount += dStartTabWidth - dStartTabWidthArray[nTabIndex]; 
	}else
	{
		nNexSumCount += dStartTabWidth;
	}

	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth - dTmpSumCountPrev; // 추가
	dStartTabWidth = dStartTabWidthArray[nTabIndex]; 
	nTempCountCheck = nNexSumCount;

	pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

	nNexSumCount += dSecondTabWidth;
	nTempCountCheck = nNexSumCount;

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1); // 2.4

	UINT uStartPos = 0; // 1. 처음 시작부  
	UINT uJumpPos = 0; // 2. NonFlag Start
	UINT u2ndFlagPos = 0; // Flag 한번더 Start
	UINT uEndPos = 0; // x
	UINT u2ndJumpPos = 0; // NG Flag start
	UINT u3ndJumpPos = 0; // CORE + @ start 
	UINT u3ndFlagStartPos = 0; // 3포지션에서 플래그 시작부
	UINT u4ndJumpPos = 0; // NG Wait Flag start  1000mm를 3mm 탭으로 매꿈
	UINT u5ndJumpPos = 0; // A/C 이벤트 진행 - 노칭 전 2~300mm 탭으로 매꿈
	UINT u6ndJumpPos = 0; // A/C 이벤트 노칭 
	UINT n6ndFlagPos = 0;
	UINT u7ndJumpPos = 0; 

	nTempCountCheck = nNexSumCount;

	uStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);


	BOOL bZigZagCut = FALSE;
	BOOL bLastFlag = FALSE;

	if(m_stNotchPatternData.nCuttingMode == 2)
		bZigZagCut = TRUE;


	if(bZigZagCut == FALSE)
	{
		if(1)
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285
				{
					nTabIndex++;
					nTabLengthSumTemp=0;
					nTapIndexCount=0;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
				{
					nTabIndex=0;
					nTabLengthSumTemp=0;
					nTapIndexCount=0;
					break;
				}

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				pDsp->SetFlyXHEAD1(dScaleFactorX);


				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		else
		{
			for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
			{
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
			}

		}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{

		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;
		BOOL bBreakFlag=FALSE;
		BOOL bLastFlag = FALSE;


		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);

		int i = 0;
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		if(1)
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//2024.06.26 엔코더 리셋 안하고 이어할때
				if(dSumCountPrev > 0)
				{
					if(nNexSumCount >= (dStartTabWidthArraySum[nTabIndex] + m_stNotchPatternData.dNochingWidth))
					{
						//if(nTabIndex < 6)
						nTabIndex++;
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

					}
					else if( (nNexSumCount + dStartTabWidthArray[nTabIndex]) >= (dStartTabWidthArraySum[nTabIndex] + m_stNotchPatternData.dNochingWidth) )
					{
						dStartTabWidth = dStartTabWidthArray[nTabIndex];
						dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
					}
					else
					{
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
					}
				}
				else
				{
					if(nNexSumCount >= dStartTabWidthArraySum[nTabIndex] )
					{
						//if(nTabIndex < 6)
						nTabIndex++;
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

					}
					else if( (nNexSumCount + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
					{
						dStartTabWidth = dStartTabWidthArray[nTabIndex];
						dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
					}
					else
					{
						dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	
					}
				}

				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				//if(i % 2 == 0)
				dFlagDistanceField = dStartTabWidth;
				dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
				pDsp->SetFlyXHEAD1(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				if(1)
				{
					//스캐너로 Flag Width조정
					//if(i % 2 == 0 && nTapIndexCount <  284)

					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					dTempEncX = nNexSumCount;
					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset;//pFieldParameter->GetCycleOffset();

					nNexSumCount += dStartTabWidth;

				}
				else
				{

					//엔코더로 Flag Width조정
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
					n_list_nop(RTC_CARD_NUM_1);
#endif
					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
					pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
					//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;

				//if( bLastFlag == FALSE )
				{
					nNexSumCount += dSecondTabWidth + i * dFlagAllowance;

					nTapIndexCount++;
					i++;
				}


				if(nNexSumCount >= dTotalLength)
				{
					bBreakFlag = TRUE;
				}

				if( (nNexSumCount + dStartTabWidth) >=  dTotalLength )
				{
					// 음극은 종단부 한번 더 긋기없음, 양극은 있음
					if(pInitialTable->GetHead1Name() == "Anode")
					{
						// 1호기
						bBreakFlag = TRUE;
						// nNexSumCount+=dChangeOffset;
					} else
					{
						// 2호기
						pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
						pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

						bBreakFlag = TRUE;
						nNexSumCount+=dStartTabWidth;
					}
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD1ScannerParameter.cycleOffset;
					dFlagEncSum = nNexSumCount;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		else
		{
			int i = 0;
			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
			{	
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				//스캐너로 Flag Width조정
				//if(i % 2 == 0)
				{
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					{
						//스캐너로 Flag Width조정
						//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
						if(1)
						{
							if(i % 2 == 0)
							{
								pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
								pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
								pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
							}
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
						}
						else
						{
							//엔코더로 Flag Width조정
							pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
							n_list_nop(RTC_CARD_NUM_1);
#endif
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
							pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

							pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
							//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
						}
					}
				}

				//-----------------------------------------------------------------------------------------------------------

				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//if(i == (int)nFlagCountReal-1)
				//	nNexSumCount+=dChangeOffset;

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);

				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

			}
		}
	}

	//pDsp->SetEndOfListHEAD1();
	nTempCountCheck = nNexSumCount;
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 0;


	//pDsp->SetStartListHEAD1(2);
	// HEAD1
	/////////////////////////////////////////////////////////////NonFlag Start///////////////////////////////////////////////////////////////////////////////////

	// 여기서 스케일값 따로 적용 되도록 수정해야함

	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
	uJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);

	//2024.01.25 AnalogPowr Use 
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);

	// 241002_1010 ldy - 노칭 입사각
	double dTabAngleTemp = 0;
	dTabAngleTemp = dTabAngleX;
	double dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;

	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}

	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);


	// ldy end
	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, dTabAngleX, dBuriedHeightField);

	// 음극은 노칭부 엔코더 옵셋으로 조절
	double dNonFlagOffset = 0;
	dNonFlagOffset = HEAD1ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	if (dNonFlagOffset > 0)
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagLineSpeed,HEAD1ScannerParameter);
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset, 0);
	}

	dTabAngleX = dTabAngleTemp;


	// 2번빼는거 제거
	nNexSumCount += (dBuriedRegion); // 241023_ 1729 LDY 기존으로 수정
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * pFieldParameter->GetKX(), 0);


	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount, 1); 

	if (dNonFlagOffset > 0)
	{
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset , 0);  // 241023_ 1729 LDY 기존으로 수정
	}

	if (dNonFlagOffset > 0)
	{
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);
	}

	if(pInitialTable->GetHead1Name() != "Cathode")
	{
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	}


	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dTabAngleX ,dTabHeightField);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);

	dStartTabWidth = dTabWidth1;
	dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;

	//--------------------------------------------------------------------------------------------------------------------------------	
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif

	//20220818 jjsjong
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);


	double dAddFlagAmountField = dTabWidthField;

	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth;
	nNexSumCount += (dStartTabWidth +  dFlagOffsetStart);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount, 0); 

	/////////////////////////////////////////////////////////////NonFlag End///////////////////////////////
	//pDsp->nListJumpPos(RTC_CARD_NUM_1, uStartPos);
	//----------------------------------------- Flag 한번더 Start---------------------------------------------------------------------------
	pRunMgr->m_u2ndFlagPos = u2ndFlagPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);
	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	BOOL bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;



	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
	if(bZigZagCut == FALSE)
	{
		//pDsp->SetFlyXHEAD1(dScaleFactorX);
		//if(IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		if(1)
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285 ->  240509 jyh
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD1(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		else
		{
			for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
			{
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
			}

		}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		if(1)
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD1(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				if(1)
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					//if(i != 0)
					{
						pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
						pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
						pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
					}

					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset;;

					//--------------  양극과 틀린부분 --------------------
					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
						nNexSumCount += dStartTabWidth;
					}
					//----------------------------------------------------
					nTempCountCheck+=dStartTabWidth;
				}
				else
				{

					//엔코더로 Flag Width조정
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
					n_list_nop(RTC_CARD_NUM_1);
#endif
					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
					pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
					//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;
				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck += dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;

				//if(nTabLengthSumTemp >= dTotalLength) //마지막에는 플래그를 한개 적게 커팅해야함.
				//if( nTabIndex == 6-1 && nTabLengthSumTemp >= (dTotalLength - dStartTabWidthArray[5]) )
				if(  nTempCountCheck >= dTotalLength  )
				{
					// nNexSumCount+=dChangeOffset;
					bBreakFlag=TRUE;

					//TRACE("HEAD1 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
					//log->WriteString(CWriteLog::MakeFormatString("Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX));
				}


				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					// 2번째 패턴부터는 음양극 공통으로 한번더 긋고 종단부옵셋으로 조절함( 탭 너비 고려 O )
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					bBreakFlag = TRUE;
					nNexSumCount+=dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD1ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD1ScannerParameter.cycleOffset;
					dFlagEncSum = nTempCountCheck;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		else
		{
			int i = 0;
			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
			{	
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				//스캐너로 Flag Width조정
				//if(i % 2 == 0)
				{
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					{
						//스캐너로 Flag Width조정
						//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
						if(1)
						{
							if(i % 2 == 0)
							{
								pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
								pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
								pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
							}
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
						}
						else
						{
							//엔코더로 Flag Width조정
							pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
							n_list_nop(RTC_CARD_NUM_1);
#endif
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
							pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

							pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
							//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
						}
					}
				}

				//-----------------------------------------------------------------------------------------------------------

				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				if(i == (int)nFlagCountReal-1)
					nNexSumCount+=dChangeOffset;

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);

				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

			}
		}
	}


	//----------------------------------------- Flag 한번더 End---------------------------------------------------------------------------
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	pDsp->nListJumpPos(RTC_CARD_NUM_1, uJumpPos);

	nTempCountCheck = nNexSumCount;
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 3;

	//------------------------------------------------------- NG Flag start-------------------------------------------------------------------------------
	u2ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); 

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);

	//dScaleFactorXNotching = 0; // 241023_1729 LDY 논플래그 스케일 같이 먹도록
	//if( pFieldParameter->GetKX_Notch() != 0)
	//	dScaleFactorXNotching = (m_dMaxField / m_dMaxMM) / pFieldParameter->GetKX_Notch();

	//pDsp->SetFlyXHEAD1(dScaleFactorXNotching);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	int nCount = 0;
	double dNGTabWidth = 3;
	double dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->N_Mark_Abs( RTC_CARD_NUM_1, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_1, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount >= HEAD1ScannerParameter.dMinFlagLeng) // 센서길이가 아닌 다른 조건이 필요해보임
			break;
	}
	//------------------------------------------------------- NG Flag end-------------------------------------------------------------------------------
	//-------------------------------------------------------CORE + @ start -------------------------------------------------------------------------------
	// 여기서 SetEndOFListHEAD1() 전에 2번째 NonFlag 만들어서 NG 체크
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
	u3ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); // 2번째 노칭시작

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);

	nNexSumCount = 0;

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);

	//2024.01.25 AnalogPowr Use 
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);

	// 241002_1010 ldy - 노칭 입사각
	dTabAngleTemp = 0;
	dTabAngleTemp = dTabAngleX;
	dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;

	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}
	// ldy end

	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, dTabAngleX, dBuriedHeightField);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagLineSpeed,HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);


	// 음극은 노칭부 엔코더 옵셋으로 조절
	dNonFlagOffset = 0;
	dNonFlagOffset = HEAD1ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset, 0);
	dTabAngleX = dTabAngleTemp;


	double dNgLength = 0;
	dNgLength = HEAD1ScannerParameter.ngLength;

	pRunMgr->m_dNGNochingLength = dNgLength + dPatternCorePos;
	nNexSumCount += (pRunMgr->m_dNGNochingLength); // 길이를 받아야함 - 멤버변수로 밑에서 하고오기?

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * pFieldParameter->GetKX(), 0);


	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1); 


	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth;
	if (dNonFlagOffset > 0)
	{
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset , 0);  // 241023_ 1729 LDY 기존으로 수정
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);
	}

	if(pInitialTable->GetHead1Name() != "Cathode")
	{
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dTabAngleX ,dTabHeightField);


	//--------------------------------------------------------------------------------------------------------------------------------	
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	u3ndFlagStartPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); // 3번 째 점프 포즈에서 플래그 시작부

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter); 

	//20220818 jjsjong
	dStartTabWidth = dTabWidth1;
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);
	nNexSumCount += (dStartTabWidth +  dFlagOffsetStart);
	double dNgoffset = 0.0;
	CString sNgoffset = "";

	//pDlg->GetDlgItemText(IDC_TEXT_NG_OFFSET, sNgoffset);
	dNgoffset = atof(sNgoffset);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round((nNexSumCount + dNgoffset) * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1); 

	//-------------------------------------------------------CORE + @ end-------------------------------------------------------------------------------
	//-------------------------------------------------------2nd Flag - NG start-------------------------------------------------------------------------------
	// 점프 전 노칭 로직 완성 - 위 노칭 로직 길이만 수정해서 가져오기
	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;

	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
	if(bZigZagCut == FALSE)
	{
		//pDsp->SetFlyXHEAD1(dScaleFactorX);
		//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		if(1)
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285 ->  240509 jyh
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD1(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);


			}
		}
		else
		{
			for(int i=1 ; i<(int)nFlagCountReal-1   ; ++i) // ÇÑ¹ø¿¡ ÇÃ·¡±×¸¦ ¸î°³ µþÁö
			{
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
			}

		}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		//if(IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		if(1)
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD1(dScaleFactorX);

				//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				if(1)
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset;

					//--------------  양극과 틀린부분 --------------------
					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
						nNexSumCount += dStartTabWidth;
					}
					//----------------------------------------------------
					nTempCountCheck+=dStartTabWidth;
				}
				else
				{

					//엔코더로 Flag Width조정
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
					n_list_nop(RTC_CARD_NUM_1);
#endif
					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
					pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
					pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
					//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;
				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck += dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;

				//if(nTabLengthSumTemp >= dTotalLength) //마지막에는 플래그를 한개 적게 커팅해야함.
				//if( nTabIndex == 6-1 && nTabLengthSumTemp >= (dTotalLength - dStartTabWidthArray[5]) )
				if(  nTempCountCheck >= dTotalLength  )
				{
					// nNexSumCount+=dChangeOffset;
					bBreakFlag=TRUE;

					//TRACE("HEAD1 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
					//log->WriteString(CWriteLog::MakeFormatString("Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX));
				}


				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					// 2번째 패턴부터는 음양극 공통으로 한번더 긋고 종단부옵셋으로 조절함( 탭 너비 고려 O )
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					bBreakFlag = TRUE;
					nNexSumCount+=dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD1ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD1ScannerParameter.cycleOffset;
					dFlagEncSum = nTempCountCheck;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		else
		{
			int i = 0;
			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
			{	
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				//스캐너로 Flag Width조정
				//if(i % 2 == 0)
				{
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					{
						//스캐너로 Flag Width조정
						//if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
						if(1)
						{
							if(i % 2 == 0)
							{
								pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
								pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
								pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
							}
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
						}
						else
						{
							//엔코더로 Flag Width조정
							pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
#ifndef _SIMUL_
							n_list_nop(RTC_CARD_NUM_1);
#endif
							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
							pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
							pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

							pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
							//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
						}
					}
				}

				//-----------------------------------------------------------------------------------------------------------

				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				if(i == (int)nFlagCountReal-1)
					nNexSumCount+=dChangeOffset;

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);

				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

			}
		}
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	//-------------------------------------------------------2nd Flag - NG end-------------------------------------------------------------------------------
	pDsp->nListJumpPos(RTC_CARD_NUM_1, uJumpPos);
	//------------------------------------------------------- NG Wait Flag start-------------------------------------------------------------------------------
	u4ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	nNexSumCount = 3;

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);


	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
	pDsp->SetFlyXHEAD1(dScaleFactorX);


	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		// while문으로 무한대기하고 밑에서 조건문으로 스톱시킬것
		pDsp->N_Mark_Abs( RTC_CARD_NUM_1, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_1, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount > HEAD1ScannerParameter.dNGSensorLeng)
			break;
	}
	pDsp->nListJumpPos(RTC_CARD_NUM_1, u2ndJumpPos);
	//------------------------------------------------------- NG Wait Flag end-------------------------------------------------------------------------------
	pRunMgr->m_nEncoderSumCount = 0;
	nNexSumCount = 0;
	//------------------------------------------------------- A/C Event Start -------------------------------------------------------------------------------
	u5ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); 

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);

	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);



	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);
		pDsp->N_Mark_Abs( RTC_CARD_NUM_1, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_1, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount >= 1500) // 임시테스트
			break;
	}
	//------------------------------------------------------- NG Flag end-------------------------------------------------------------------------------
	//-------------------------------------------------------CORE + @ start -------------------------------------------------------------------------------
	// 여기서 SetEndOFListHEAD1() 전에 2번째 NonFlag 만들어서 NG 체크
	u6ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); // 2번째 노칭시작

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);

	nNexSumCount = 0;

	double dScaleFactorXNotching = 0; // 241023_1729 LDY 논플래그 스케일 같이 먹도록
	if( pFieldParameter->GetKX_Notch() != 0)
		dScaleFactorXNotching = (m_dMaxField / m_dMaxMM) / pFieldParameter->GetKX_Notch();

	pDsp->SetFlyXHEAD1(dScaleFactorX);

	// pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

	//2024.01.25 AnalogPowr Use 
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);

	// 241002_1010 ldy - 노칭 입사각
	dTabAngleTemp = 0;
	dTabAngleTemp = dTabAngleX;
	dNotchingStartAngle = m_stNotchPatternData.dNochingAngle;

	dRadian = 0;

	if(dNotchingStartAngle != 0)
	{
		dRadian = ( dNotchingStartAngle  / 180.0f) * M_PI;
		dTabAngleX = ((dTabHeight - dNotchRoot)*tan(dRadian));
		dTabAngleX = dTabAngleX * m_dMaxField / m_dMaxMM;
	} else
	{
		// 2024.01.27. NonFlag시작 0도
		dTabAngleX = 0; // 강제로 0 을 줌 - 파라미터로 빼기
	}
	// ldy end

	pDsp->N_Mark_Abs(RTC_CARD_NUM_1, dTabAngleX, dBuriedHeightField);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagLineSpeed,HEAD1ScannerParameter);
	pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagFreq, HEAD1ScannerParameter.pulsewidth );
	pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.nonflagPower);


	// 음극은 노칭부 엔코더 옵셋으로 조절
	dNonFlagOffset = 0;
	dNonFlagOffset = HEAD1ScannerParameter.notchOffset * m_dMaxField / m_dMaxMM;

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset, 0);
	dTabAngleX = dTabAngleTemp;


	dNgLength = 0;
	dNgLength = HEAD1ScannerParameter.ngLength;

	pRunMgr->m_dNGNochingLength = dNgLength + dPatternCorePos;
	nNexSumCount += (pRunMgr->m_dNGNochingLength); // 길이를 받아야함 - 멤버변수로 밑에서 하고오기?

	double dNotchingKX = pFieldParameter->GetKX_Notch();
	if(dNotchingKX < 0) 
	{
		dNotchingKX = -dNotchingKX;
	}

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * dNotchingKX, 0);


	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1); 


	dStartTabWidth = dTabWidth1;
	nTempCountCheck = dStartTabWidth;
	if (dNonFlagOffset > 0)
	{
		pDsp->N_Mark_Rel(RTC_CARD_NUM_1, dNonFlagOffset , 0);  // 241023_ 1729 LDY 기존으로 수정
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1, HEAD1ScannerParameter.nonflagInoutSpeed,HEAD1ScannerParameter);
	}

	if(pInitialTable->GetHead1Name() != "Cathode")
	{
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagFreq, HEAD1ScannerParameter.pulsewidth );
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagPower);
	}

	pDsp->N_Mark_Rel(RTC_CARD_NUM_1, -dTabAngleX ,dTabHeightField);


	//--------------------------------------------------------------------------------------------------------------------------------	
#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	n6ndFlagPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1); // 3번 째 점프 포즈에서 플래그 시작부

	// pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	// pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);

	pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1ScannerParameter.flagSpeed,HEAD1ScannerParameter); 

	//20220818 jjsjong
	dStartTabWidth = dTabWidth1;
	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);
	nNexSumCount += (dStartTabWidth +  dFlagOffsetStart);
	dNgoffset = 0.0;
	sNgoffset = "";

	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round((nNexSumCount + dNgoffset) * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1); 

	//-------------------------------------------------------CORE + @ end-------------------------------------------------------------------------------
	//-------------------------------------------------------3nd Flag - A/C start-------------------------------------------------------------------------------
	// 점프 전 노칭 로직 완성 - 위 노칭 로직 길이만 수정해서 가져오기
	nTabIndex=0;
	nTabLengthSumTemp=0;
	nTapIndexCount=0;
	bBreakFlag=FALSE;
	bLastFlag = FALSE;
	dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;

	// pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
	// pDsp->NOutputIOList(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
	if(bZigZagCut == FALSE)
	{
		//pDsp->SetFlyXHEAD1(dScaleFactorX);
		// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			while(1)
			{			
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTapIndexCount == m_stNotchPatternData.dCuttingCount1) // 285 ->  240509 jyh
				{
					nTabIndex++;
					//nTabLengthSumTemp=0;
					nTapIndexCount=0;
					bLastFlag = FALSE;
				}
				nTapIndexCount++;

				if(nTabIndex == 6) 
					break;

				if(nTabIndex == 0)
					dStartTabWidth = dTabWidth1;
				else if(nTabIndex == 1)
					dStartTabWidth = dTabWidth2;
				else if(nTabIndex == 2)
					dStartTabWidth = dTabWidth3;
				else if(nTabIndex == 3)
					dStartTabWidth = dTabWidth4;
				else if(nTabIndex == 4)
					dStartTabWidth = dTabWidth5;
				else if(nTabIndex == 5)
					dStartTabWidth = dTabWidth6;
				//---------------------------------------------------------------------------------------------------------------
				//pDsp->SetFlyXHEAD1(dScaleFactorX);

				//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(HEAD1ScannerParameter.laserOnDelay*dScale*64), (long)(HEAD1ScannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
				pDsp->SetFlyXHEAD1(dScaleFactorX);
				{
					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				}

				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------------
				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
			}
		}
		nNexSumCount+=dChangeOffset;
		pRunMgr->m_nEncoderSumCount = (int)(nNexSumCount * nEncoderScaleX); 
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
	}
	else // For ZigZag Cut   
	{
		double dFlagDistanceField = 0;
		double dTempEncX = 0.0;
		dSecondTabWidth = 0;

		dFlagDistanceField = dStartTabWidth * m_dMaxField / m_dMaxMM;


		int i = 0;
		// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCH))
		{
			//엔코더로 TabPitch 적용----------------------------------------------------------------------------------------
			while(1)
			{		
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				if(nTempCountCheck >= dStartTabWidthArraySum[nTabIndex] )
				{
					if(nTabIndex < 6)
						nTabIndex++;
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];			

				}
				else if( (nTempCountCheck + dStartTabWidthArray[nTabIndex]) >= dStartTabWidthArraySum[nTabIndex] )
				{
					dStartTabWidth = dStartTabWidthArray[nTabIndex];
					dSecondTabWidth =  dStartTabWidthArray[nTabIndex+1];
				}
				else
				{
					dSecondTabWidth = dStartTabWidth = dStartTabWidthArray[nTabIndex];	

				}
				//---------------------------------------------------------------------------------------------------------------
				//스캐너로 Flag Width조정
				pDsp->SetFlyXHEAD1(dScaleFactorX);

				// if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
				{
					//스캐너로 Flag Width조정
					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;

					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
					dTempEncX = nNexSumCount;

					double dNonFlagOffset = 0;
					dNonFlagOffset = FIELD_FARAMETER.CycleOffset;

					//--------------  양극과 틀린부분 --------------------
					if(nTapIndexCount == 0 && nTabIndex == 0)
					{
						nNexSumCount += (dStartTabWidth +  dNonFlagOffset);
					} else
					{
						nNexSumCount += dStartTabWidth;
					}
					//----------------------------------------------------
					nTempCountCheck+=dStartTabWidth;
				}
				//				else
				//				{
				//
				//					//엔코더로 Flag Width조정
				//					pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
				//#ifndef _SIMUL_
				//					n_list_nop(RTC_CARD_NUM_1);
				//#endif
				//					nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
				//					nNexSumCount += dStartTabWidth + i * dFlagAllowance;
				//					pDlg->pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				//					pDsp->WaitForEncoderHEAD1(pDlg->pRunMgr->m_nEncoderSumCount,1);
				//
				//					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
				//					//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
				//				}

				//-----------------------------------------------------------------------------------------------------------
				nTapIndexCount++;
				i++;
				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
				//nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;

				nTabLengthSumTemp += dSecondTabWidth + i * dFlagAllowance;
				nNexSumCount += dSecondTabWidth + i * dFlagAllowance;
				nTempCountCheck += dSecondTabWidth + i * dFlagAllowance;

				nTapIndexCount++;
				i++;

				//if(nTabLengthSumTemp >= dTotalLength) //마지막에는 플래그를 한개 적게 커팅해야함.
				//if( nTabIndex == 6-1 && nTabLengthSumTemp >= (dTotalLength - dStartTabWidthArray[5]) )
				if(  nTempCountCheck >= dTotalLength  )
				{
					// nNexSumCount+=dChangeOffset;
					bBreakFlag=TRUE;

					//TRACE("HEAD1 Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX);
					//// log->WriteString(CWriteLog::MakeFormatString("Flag EncX:%.3f, nTabIndex:%d, nTapIndexCount:%d,  SX:%.3f, diff:%.3f \n", nNexSumCount, nTabIndex, nTapIndexCount, dStartTabWidth , nNexSumCount -  dTempEncX));
				}


				if( (nTempCountCheck + dStartTabWidth) >= dTotalLength)
				{
					// 2번째 패턴부터는 음양극 공통으로 한번더 긋고 종단부옵셋으로 조절함( 탭 너비 고려 O )
					pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField + dTabAngleX,   -dTabHeightField);
					pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);

					bBreakFlag = TRUE;
					nNexSumCount+=dStartTabWidth;
					nTempCountCheck+=dStartTabWidth;
				}

				if(bBreakFlag == TRUE)
				{
					nNexSumCount+=HEAD1ScannerParameter.cycleOffset;
					nTempCountCheck+=HEAD1ScannerParameter.cycleOffset;
					dFlagEncSum = nTempCountCheck;
				}

				pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);

				pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);

				if(bBreakFlag == TRUE)
				{
					break;
				}
			}

		}
		//		else
		//		{
		//			int i = 0;
		//			for(i=0 ; i<(int)nFlagCountReal -1   ; ++i)
		//			{	
		//				pDsp->SetFlyXHEAD1(dScaleFactorX);
		//				//스캐너로 Flag Width조정
		//				//if(i % 2 == 0)
		//				{
		//					dFlagDistanceField = dStartTabWidth + i * dFlagAllowance;
		//					dFlagDistanceField = dFlagDistanceField * m_dMaxField / m_dMaxMM;
		//
		//					{
		//						//스캐너로 Flag Width조정
		//						if(pDlg->IsDlgButtonChecked(IDC_CHECK_S_PITCHBY_SCANNER))
		//						{
		//							if(i % 2 == 0)
		//							{
		//								pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
		//								pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dFlagDistanceField,   0);
		//								pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
		//								//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//							}
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//						}
		//						else
		//						{
		//							//엔코더로 Flag Width조정
		//							pDsp->N_Mark_Abs( RTC_CARD_NUM_1, dTabAngleX + dAddAmount,   dNotchRootField);
		//#ifndef _SIMUL_
		//							n_list_nop(RTC_CARD_NUM_1);
		//#endif
		//							nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//							pDlg->pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		//							pDsp->WaitForEncoderHEAD1(pDlg->pRunMgr->m_nEncoderSumCount,1);
		//
		//							pDsp->N_Mark_Rel( RTC_CARD_NUM_1, -dTabAngleX ,   dTabHeightField);
		//							//pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//						}
		//					}
		//				}
		//
		//				//-----------------------------------------------------------------------------------------------------------
		//
		//				i++;
		//				//---------------------------------------- 2023.08.03 6구간 TabWidth For SDI Sample ------------------------
		//				nTabLengthSumTemp += dStartTabWidth + i * dFlagAllowance;
		//
		//				nNexSumCount += dStartTabWidth + i * dFlagAllowance;
		//				if(i == (int)nFlagCountReal-1)
		//					nNexSumCount+=dChangeOffset;
		//
		//				pDlg->pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 3);
		//
		//				pDsp->N_Fly_Return( RTC_CARD_NUM_1,dAddAmount,   dTabHeightField);
		//
		//				pDsp->WaitForEncoderHEAD1(pDlg->pRunMgr->m_nEncoderSumCount,1);
		//
		//			}
		//		}
	}

#ifndef _SIMUL_
	n_store_encoder(RTC_CARD_NUM_1, 0);
	n_store_encoder(RTC_CARD_NUM_1, 1);
#endif
	//-------------------------------------------------------3nd Flag - AC end-------------------------------------------------------------------------------
	pDsp->nListJumpPos(RTC_CARD_NUM_1, uJumpPos);
	//------------------------------------------------------- A/C Event End ---------------------------------------------------------------------------------
	//------------------------------------------------------- A/C Wait Flag start-------------------------------------------------------------------------------
	u7ndJumpPos = pDsp->nGetInputPointer(RTC_CARD_NUM_1);

	nNexSumCount = 0;

	pDsp->SetFlyXHEAD1(1.0); 
	pDsp->SetFlyXHEAD1(0.0);
	pDsp->SetFlyYHEAD1(1.0); 
	pDsp->SetFlyYHEAD1(0.0);


	pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);
	pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
	pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);



	nCount = 0;
	dNGTabWidth = 3;
	dNGTabWidthField = dNGTabWidth * m_dMaxField / m_dMaxMM;
	while(1)
	{
		pDsp->SetFlyXHEAD1(dScaleFactorX);
		// while문으로 무한대기하고 밑에서 조건문으로 스톱시킬것
		pDsp->N_Mark_Abs( RTC_CARD_NUM_1, 0 + 0,   dNotchRootField);
		pDsp->N_Jump_Rel( RTC_CARD_NUM_1, dNGTabWidthField,   0);
		pDsp->N_Mark_Rel( RTC_CARD_NUM_1, 0 ,   dTabHeightField);

		pDsp->N_Fly_Return(RTC_CARD_NUM_1, 0 ,dTabHeightField);

		nNexSumCount += dNGTabWidth;
		nNexSumCount += dNGTabWidth;

		pRunMgr->m_nEncoderSumCount = (int)mathUtil.Round(nNexSumCount * nEncoderScaleX, 0);
		pDsp->WaitForEncoderHEAD1(pRunMgr->m_nEncoderSumCount,1);
		if(nNexSumCount > dACSensorLength) // AC태그위치까지 대기
			break;
	}
	pDsp->nListJumpPos(RTC_CARD_NUM_1, u5ndJumpPos);
	//------------------------------------------------------- A/C Wait Flag end-------------------------------------------------------------------------------


	pDsp->SetEndOfListHEAD1();
	pDsp->SetFirstStart(FALSE);
	if(pDsp->GetBoardCount() == 1)
	{
		//if(m_stNotchPatternData.dFoilExtention == 0)
		{
			//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
			//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_DATA_NOT_FOUND);
			return 0;
		}
		//else if(iStartSpeed == 0)
		{
			//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_PARAMETER_NOT_FOUND);
			return 0;
		}
		//else
		{
			//pMainFrm->PostMessage(WM_SHOW_STATE,STATE_READY);
		}
	}
	UINT nListNumber = 1;

	UINT uErrorbit = -1;

	BOOL bErrorCheck = FALSE;

	BOOL bEnabledLaser = TRUE;
	BOOL bEnabledFlag = TRUE;

	LONG HEAD1_EncoderY,HEAD1_EncoderX;
	HEAD1_EncoderX=0;HEAD1_EncoderY=0;
	UINT uBusy, uPos;
#ifdef _SIMUL_
	//return 0;
#endif

	double dEncoderPos = HEAD1_EncoderY / -pFieldParameter->GetKX();//500;

	BOOL bNGLasor = TRUE;
	BOOL bNGFlag = TRUE;

	BOOL bNgFlagTmp = TRUE;
	BOOL bNgNonFlagTmp = TRUE;


#ifndef _SIMUL_
	n_execute_list(RTC_CARD_NUM_1,1); // ldy _ 240930_1612


#endif

#ifdef _SIMUL_
	return 0;
#endif

	// 여기서 현재 엔코더값 기록 후 쭉 더하기
	// 파라미터값 확인하기!
	long nNgX,nNgY;

	int nNgTriger = -1;

	int bNGCheck = -1; // -1 : 대기  /  0 : 논플래그  /  1 : 플래그 

	BOOL bACCheck = TRUE;
	BOOL bACCheck_prev = TRUE;


	BOOL bNGFlagCheck = FALSE;
	CString strLogData;

	int nTriger1, nTriger2;
	nTriger1 = nTriger2 = 0;

	double dNgTagPredictSensorLeng; // NG 태그 위치 ( 예측 )

	//return 0;

	BOOL bTrigger = FALSE;

	while( pRunMgr->m_bThreadAlive ) 
	{
#ifndef _TestMC_
		if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_LASER_ON)== TRUE)
		{
			bEnabledLaser = TRUE;
			if(bEnabledFlag != bEnabledLaser)
			{
				pDsp->EnableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		}
		else
		{   
			bEnabledLaser = FALSE;
			if(bEnabledFlag != bEnabledLaser)
			{
				pDsp->DisableLaserHEAD1();
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, FALSE);

		}
		bEnabledFlag = bEnabledLaser;
#endif
		stStat = pDsp->ReadStatusHEAD1();

#ifndef _SIMUL_
		uErrorbit = n_get_marking_info(RTC_CARD_NUM_1);

		UINT nGetMarkingInfo = uErrorbit;//get_marking_info();
		UINT nXUnderFlowCheckBit  = 0x0003;
		UINT nXOverFlowCheckBit  = 0x0030;
		UINT nYUnderFlowCheckBit  = 0x000C;
		UINT nYOverFlowCheckBit  = 0x00C0;

		if((nGetMarkingInfo & nXUnderFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("XUnderlow");
			}
		}
		if((nGetMarkingInfo & nXOverFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);
				bErrorCheck = TRUE;
				TRACE("XOverFlow");
			}
		}
		if((nGetMarkingInfo & nYUnderFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("YUnderFlow");
			}
		}
		if((nGetMarkingInfo & nYOverFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
				pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				TRACE("YOverFlow");
			}
		}
#endif
		dNgLength = 0;
		dNgLength = HEAD1ScannerParameter.ngLength; // 알파값

		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		if (uPos > uJumpPos && uPos < u2ndFlagPos)
		{
			// nonFlag
			bNGCheck = 0;
		}		
		else
		{
			bNGCheck = 1;
		}

		// 외곽부 + 코어부 = 노칭길이
		dPatternOutPos = 0; // 외곽부 길이 - 추가완료 
		dPatternOutPos = m_stNotchPatternData.dNochingOutPosWidth;

		dPatternCorePos = 0; // 코어부 길이 >> 노칭 - 외곽
		dPatternCorePos = dBuriedRegion - dPatternOutPos;

		double dMinWinderLeng;	// 최소권취길이 >> 1150mm
		double dFirstTabArea;	// 첫탭구간 값 >> 950mm
		double dSensorLeng;		// 센서인식길이 - 200mm 고정
		double dPrePatternTrigger;

		// test
		dFirstTabArea = HEAD1ScannerParameter.dMinFlagLeng; // 최소권취길이
		dSensorLeng = HEAD1ScannerParameter.dNGSensorLeng; // NG태그 센서부터 현 가공위치의 길이

		dMinWinderLeng = dFirstTabArea + dSensorLeng;

		double dPrePatternLeng;

		// 변수 2개 추가 - NON / Flag 
		//if(pDlg->IsDlgButtonChecked(IDC_CHECKBOX_ENABLE_NGTAG))//NGTAG 체크박스 체크시 - 현재 사용 안함
		//{
		//	if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_FIRST_TAB) == TRUE) // NG 신호시 - 1
		//	{
		//		bNGLasor = TRUE;
		//		if(bNGFlag != bNGLasor)
		//		{
		//			pDsp->GetEncodeHEAD1(nNgX, nNgY);
		//			dPrePatternLeng = (nNgY / -pFieldParameter->GetKY());
		//			dPrePatternTrigger = 0;
		//			dPrePatternTrigger = dPrePatternLeng;
		//
		//			if((pDlg->m_StopBtnClicked == TRUE && pDlg->m_bAutoCheck == TRUE) || pDlg->m_bReStartProgramHEAD1 == TRUE )
		//			{
		//				strLogData.Format("m_dExistHEAD1Enc : %0.1f", pDlg->m_dExistHEAD1Enc);
		//				dPrePatternLeng += pDlg->m_dExistHEAD1Enc;
		//			}
		//
		//			dNgTagPredictSensorLeng = dPrePatternLeng + dSensorLeng; 
		//
		//			strLogData.Format("dPrePatternLeng : %0.1f", dPrePatternLeng); 
		//
		//			double dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 한패턴 길이 ( 플래그 + 논플래그 )
		//
		//			if( dNgTagPredictSensorLeng > dOneCyclePatternLeng  ) // 전체 패턴( 논플 + 플래그 )보다 NG태그위치가 멀다면 - 프로그램 시작 후 2번째 패턴 이후( 프로그램 재시작시 첫 플래그 패턴 대비 위함 )
		//			{
		//				// 다음 패턴의 논플래그 혹은 플래그 판단하기 위함
		//				if( dNgTagPredictSensorLeng > dOneCyclePatternLeng + dBuriedRegion ) // 한패턴 + 논플래그 길이 보다 크다면
		//				{
		//					// NG태그 플래그 위치 -> NG위치에서 앞으로 1000mm 했을때 코어부인지 외곽부인지
		//					if( (dNgTagPredictSensorLeng - dOneCyclePatternLeng - HEAD1ScannerParameter.dMinFlagLeng) > dPatternOutPos ) // dPatternOutPos : 노칭 외곽부
		//					{
		//						// 코어부라면
		//						// NG태그 앞 1000mm 기준 코어부에 위치
		//						double dBetweenSensorToFlagEndLength;
		//						dBetweenSensorToFlagEndLength = dOneCyclePatternLeng - dPrePatternLeng; // NG 센서 신호 시 가공부부터 종단부까지의 길이.( 전체 패턴길이 - 현재 엔코더 길이 )
		//
		//						while(1)
		//						{
		//							// 엔코더 리셋 위치까지 대기
		//							pDsp->GetEncodeHEAD1(nNgX, nNgY);
		//							Sleep(1);
		//
		//							pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		//							if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 20) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 20) || (uPos < u3ndFlagStartPos + 20 && uPos > u3ndJumpPos)))
		//							{
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		//							}		
		//							else
		//							{
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		//							}
		//
		//							if(( nNgY / -pFieldParameter->GetKY()) <= dPatternOutPos)
		//								break;
		//						}
		//
		//						pDsp->GetEncodeHEAD1(nNgX, nNgY);
		//
		//						// NG 센서까지의 남은거리만큼 대기
		//						while( ( nNgY / -pFieldParameter->GetKY() ) <= ( dSensorLeng - dBetweenSensorToFlagEndLength ) )
		//						{
		//							pDsp->GetEncodeHEAD1(nNgX, nNgY);
		//							Sleep(1);
		//
		//							pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		//							if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 20) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 20) || (uPos < u3ndFlagStartPos + 20 && uPos > u3ndJumpPos)))
		//							{
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		//							}		
		//							else
		//							{
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
		//								pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		//							}
		//						}
		//
		//						n_stop_execution(RTC_CARD_NUM_1); // 리스트 스톱
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		//						n_execute_list_pos(RTC_CARD_NUM_1, 1, u2ndJumpPos); // 첫탭구간 가공
		//					} else
		//					{
		//						// 외곽부라면
		//						// NG태그 앞 1000mm 기준 외곽부에 위치
		//						n_stop_execution(RTC_CARD_NUM_1);
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		//						n_execute_list_pos(RTC_CARD_NUM_1, 1, u4ndJumpPos); 
		//					}
		//				} else
		//				{
		//					// NG 태그 논플래그 위치 한다면
		//					// 코어부 + 외곽부 같은 조건
		//					// 3mm로 쭉 가공하다가 NG태그위치왔을때 1000mm + 첫탭가공
		//					n_stop_execution(RTC_CARD_NUM_1);
		//					pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		//					n_execute_list_pos(RTC_CARD_NUM_1, 1, u4ndJumpPos);
		//				}
		//			}else
		//			{
		//				// 한패턴보다 NG태그위치가 가까우면 -> 즉, 첫패턴의 플래그에 위치할 경우
		//				// NG태그 위치까지 대기 후 1000mm + 첫탭가공
		//				while( ( nNgY / -pFieldParameter->GetKY()) <= ( dPrePatternTrigger + dSensorLeng ) )
		//				{
		//					pDsp->GetEncodeHEAD1(nNgX, nNgY);
		//					Sleep(1);
		//
		//					pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		//					if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 20) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 20) || (uPos < u3ndFlagStartPos + 20 && uPos > u3ndJumpPos)))
		//					{
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
		//					}		
		//					else
		//					{
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
		//						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
		//					}
		//				}
		//				n_stop_execution(RTC_CARD_NUM_1); // 리스트 스톱
		//				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
		//				n_execute_list_pos(RTC_CARD_NUM_1, 1, u2ndJumpPos); // 1000mm 플래그 채워주고 첫탭가공
		//			}
		//		}
		//	} 
		//	else
		//	{
		//		bNGLasor = FALSE;
		//		if(bNGFlag != bNGLasor)
		//		{
		//			log->WriteString2("RTC_SIG_I_FIRST_TAB == FALSE","");
		//		}
		//	}
		//	bNGFlag = bNGLasor;
		//}

		double dACPrePatternLeng;
		dACSensorLength = HEAD1ScannerParameter.dACSensorLeng;; // 임시 테스트
		double dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 전체길이

		CString strLogData;

		if(pDsp->nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_AUTO_CHANGE) == TRUE)
		{
			pDsp->GetEncodeHEAD1(nNgX, nNgY);
			dACPrePatternLeng = 0;

			bACCheck_prev = TRUE;
			if(bACCheck != bACCheck_prev)
			{
				dACPrePatternLeng = (nNgY / -pFieldParameter->GetKY());

				double dBetweenACSensorToFlagEndLength;
				dBetweenACSensorToFlagEndLength = dOneCyclePatternLeng - dACPrePatternLeng; 
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);


				while(1)
				{
					// 엔코더 리셋 위치까지 대기
					pDsp->GetEncodeHEAD1(nNgX, nNgY);
					Sleep(1);
					pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
					if (!((uPos > uJumpPos - 15 && uPos < u2ndFlagPos + 15) || (u6ndJumpPos - 15 < uPos && uPos < n6ndFlagPos  + 15) || (uPos < u3ndFlagStartPos + 15 && uPos > u3ndJumpPos - 15)))
					{
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
						pRunMgr->SetDelayTime(10);
					}		
					else
					{
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
						pRunMgr->SetDelayTime(10);
					}

					if(( nNgY / -pFieldParameter->GetKY()) <= dPatternOutPos)
						break;
				}
				pDsp->GetEncodeHEAD1(nNgX, nNgY);

				// NG 센서까지의 남은거리만큼 대기
				while( ( nNgY / -pFieldParameter->GetKY() ) <= ( dACSensorLength - dBetweenACSensorToFlagEndLength ) )
				{
					pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
					if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
					{
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
						pRunMgr->SetDelayTime(10);
					}		
					else
					{
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
						pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
						pRunMgr->SetDelayTime(10);
					}
					pDsp->GetEncodeHEAD1(nNgX, nNgY);
					Sleep(1);
				}
				n_stop_execution(RTC_CARD_NUM_1); 
				pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);
				n_execute_list_pos(RTC_CARD_NUM_1, 1, u5ndJumpPos);
			}
		} else
		{
			bACCheck_prev = FALSE;
			if(bACCheck != bACCheck_prev)
			{
			}
		}
		bACCheck = bACCheck_prev;

		// 논플래그 기준 딜레이타임 10 동안 캐치를 못함 -> 조건 좀더 넉넉히 + 반대로
		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		if (!((uPos > uJumpPos && uPos < u2ndFlagPos + 10) || (u6ndJumpPos < uPos && uPos < n6ndFlagPos  + 10) || (uPos < u3ndFlagStartPos + 10 && uPos > u3ndJumpPos)))
		{
			if(nTriger1 == 0 )
			{
				nTriger1 = 1;
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, 6, FALSE);
			pRunMgr->SetDelayTime(10);

		}		
		else
		{
			if(nTriger1 == 1)
			{
				nTriger1 = 0;
			}
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_FIRST_TAB, TRUE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ACTUAL_FIRST_TAB, TRUE);
			pRunMgr->m_StopBtnClicked = FALSE;
			pRunMgr->SetDelayTime(10);
		}
		pRunMgr->m_bReStartProgramHEAD1 = FALSE;

		CFileMgr pFileMgr;

		double dTriggerWidth; // 리셋 전 거리
		dTriggerWidth = pFileMgr.ReadDouble(_T("HEAD1"), _T("TriggerWidth"), _T(".\\DustCollectorTrigger.ini"));
		dTotalLength = m_stNotchPatternData.dCuttingTotalWidth;
		dBuriedRegion = m_stNotchPatternData.dNochingWidth;
		dOneCyclePatternLeng = dTotalLength + dBuriedRegion; // 패턴 전체길이 ( 노칭 + 커팅 )
		pDsp->GetEncodeHEAD1(nNgX, nNgY);

		pDsp->nGetstatus(RTC_CARD_NUM_1, uBusy, uPos );
		if(uPos >= nStartPos && uPos < uJumpPos )
		{

			// 첫 패턴
			if( (nNgY / -FIELD_FARAMETER.KX) > dTotalLength - dTriggerWidth  && (nNgY / -FIELD_FARAMETER.KX) < dTotalLength)
			{

				pDsp->nOutputIO(RTC_CARD_NUM_1, 6, TRUE);
			}
		} else
		{
			if( (nNgY / -FIELD_FARAMETER.KX) > dOneCyclePatternLeng - dTriggerWidth  && (nNgY / -FIELD_FARAMETER.KX) < dOneCyclePatternLeng)
			{
				pDsp->nOutputIO(RTC_CARD_NUM_1, 6, TRUE);
			}
		}
		Sleep(10);
	}
	return 0;
}



void __stdcall CRunMgr::Initialize()
{
	enum 
	{
		SEQ_INIT_PRECHECK				= 1		,
		SEQ_INIT_MODULE_START			= 10	,
		SEQ_INIT_MODULE_START_COMPLETE			,
		SEQ_INIT_MODULE_RUN				= 20	,
		SEQ_INIT_MODULE_RUN_COMPLETE			,
		SEQ_INIT_COMPLETE				= 30	,
	};

	int i = 0;

	switch(m_stMain.m_nMainStep)
	{
	case SEQ_INIT_PRECHECK:
		{
			CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
			pMainFrm->PostMessage(WM_SHOW_ALARM,ALARM_INIT);

			//Module Interface Init
			//			m_Interface.InitStatusClear();	

			SetJobClear();
			m_stMain.m_nMainStep = SEQ_INIT_MODULE_START;
		}
		break;

	case SEQ_INIT_MODULE_START:

		m_stMain.m_nMainStep++;
		break;

	case SEQ_INIT_MODULE_START_COMPLETE:
		m_bStartInitialize = TRUE;



		if(!m_bStartInitialize)
			ModeChange(JAM, m_stMain.m_nMainStep);

		m_stMain.m_nMainStep = SEQ_INIT_MODULE_RUN;
		break;

	case SEQ_INIT_MODULE_RUN:
		m_bEndInitalize = TRUE;



		if(!m_bEndInitalize) break;

		m_stMain.m_nMainStep = SEQ_INIT_MODULE_RUN_COMPLETE;
		break;

	case SEQ_INIT_MODULE_RUN_COMPLETE:
		m_stMain.m_nMainStep = SEQ_INIT_COMPLETE;
		break;

	case SEQ_INIT_COMPLETE:
		{
			m_bInitComplete = TRUE;
			CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
			pMainFrm->PostMessage(WM_HIDE_ALARM,ALARM_INIT);
			m_stMain.m_nMainStep = FINISH_ACTION;
		}
		break;		
	}

	MainSeqCheckError(&m_stMain,TIMEOUT_RUNMGR_INIT, ERROR_MSG_RUNMGR_INIT);
}

void __stdcall CRunMgr::Ready()
{

	DWORD dwThreadID;
	DWORD dwHEAD2ThreadID;

	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter* pFieldParamater = pFieldParamater->GetInstance();
	int nPatternmode = pFieldParamater->GetPatternMode();

	IniUtil _iniUtil;
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	OffsetApply();

	if(FIELD_FARAMETER.nPattern == Pattern::POUCH)
	{
		m_hThread = CreateThread(NULL,0,ExecutePatternSDI_Pouch_Head1,this,0,&dwThreadID);
	}
	else if(FIELD_FARAMETER.nPattern == Pattern::POUCH_TEST)
	{
		m_hThread = CreateThread(NULL,0,ExecutePatternSDI_Pouch_Head1_Manual,this,0,&dwThreadID);
	}
	else if(FIELD_FARAMETER.nPattern == Pattern::S)
	{
		m_bThreadAlive = TRUE;
		if(pDsp->GetBoardCount() == 1)
		{
			m_hThread = CreateThread(NULL,0,ExecutePatternSDI_Head1,this,0,&dwThreadID);
		}
		else
		{
			m_bThreadAlive = TRUE;
			m_bThreadAlive2 = TRUE;
			m_hThread = CreateThread(NULL,0,ExecutePatternSDI_Head1,this,0,&dwThreadID);

			SetDelayTime(1000);

			m_hHEAD2Thread = CreateThread(NULL,0,ExecutePatternSDI_Head2,this,0,&dwHEAD2ThreadID);
		}
	}
}

void __stdcall CRunMgr::Ready2()
{
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter* pFieldParamater = pFieldParamater->GetInstance();
	int nPatternmode = pFieldParamater->GetPatternMode();

	IniUtil _iniUtil;
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	if(FIELD_FARAMETER.nPattern == Pattern::POUCH)
	{
		//ExecutePatternSDI_Pouch_Head1();
	}
	else if(FIELD_FARAMETER.nPattern == Pattern::S)
	{
		m_bThreadAlive2 = TRUE;
		//ExecutePatternSDI_Head2();
	}
}

#define _SIMUL_
void __stdcall CRunMgr::Stop()
{
	CFieldParameter* pFieldParamater = pFieldParamater->GetInstance();
	int nPatternmode = pFieldParamater->GetPatternMode();
	CDsp *pDsp = CDsp::GetInstance();

	IniUtil _iniUtil;
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);


	if(FIELD_FARAMETER.nPattern == Pattern::POUCH)
	{
		//ExecutePatternSDI_Pouch_Head1();
		//m_bThreadAlive = FALSE;
#ifndef _SIMUL_
		n_write_io_port(RTC_CARD_NUM_1, 64);
#endif
		pDsp->OutputIO(RTC_SIG_O_REMOTE_KEY_SWITCH, TRUE);

		pDsp->OutputIO(RTC_SIG_O_READY, FALSE);
		//pDsp->OutputIO(RTC_SIG_O_STANDBY, TRUE);
		pDsp->StopExecution();

	}
	else if(FIELD_FARAMETER.nPattern == Pattern::S)
	{
		m_bThreadAlive = FALSE;
		m_bThreadAlive2 = FALSE;
		pDsp->StopExecution();

		DWORD dwState = WaitForSingleObject(m_hThread, 1000);
		DWORD dwHEAD1State = WaitForSingleObject(m_hHEAD2Thread , 1000);
		if(dwState == WAIT_TIMEOUT)
		{
			DWORD dwExitCode;
			GetExitCodeThread(m_hThread, &dwExitCode);

			if(dwExitCode == STILL_ACTIVE) 
				TerminateThread(m_hThread, 0);

			CloseHandle(m_hThread);

			m_bThreadAlive = FALSE;
			m_hThread = NULL;
		}
		else
		{
			TerminateThread(m_hThread, 0);
			m_bThreadAlive = FALSE;
			m_hThread = NULL;
		}

		if(m_hHEAD2Thread!= NULL)
		{
			if(dwHEAD1State == WAIT_TIMEOUT)
			{
				DWORD dwExitCode;
				GetExitCodeThread(m_hHEAD2Thread, &dwExitCode);

				if(dwExitCode == STILL_ACTIVE) 
					TerminateThread(m_hHEAD2Thread, 0);

				CloseHandle(m_hHEAD2Thread);

				m_bThreadAlive2 = FALSE;
				m_hHEAD2Thread = NULL;
			}

			else
			{
				TerminateThread(m_hHEAD2Thread, 0);
				CloseHandle(m_hHEAD2Thread);

				m_bThreadAlive2 = FALSE;
				m_hHEAD2Thread = NULL;
			}
		}
		//ExecutePatternSDI_Head1();
		long dEncHEAD1X, dEncHEAD1Y, dEncHEAD2X, dEncHEAD2Y;
		dEncHEAD1X = dEncHEAD1Y = dEncHEAD2X = dEncHEAD2Y = 0;
		IniUtil _iniutil;
		FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
		CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
		_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

		pDsp->GetEncodeHEAD1(dEncHEAD1X,dEncHEAD1Y);
		pDsp->GetEncodeHEAD2(dEncHEAD2X,dEncHEAD2Y);
		double dHEAD1 = dEncHEAD1Y / -FIELD_FARAMETER.KX;
		double dHEAD2 = dEncHEAD2Y / -FIELD_FARAMETER.KX;
		_iniUtil.SaveEncIni(dHEAD1, dHEAD2);
	}
}


void __stdcall CRunMgr::MainSeqCheckError	(DEF_RUN* Run, int a_nTime, int a_nErrNo)
{
	if(Run->m_nMainStep == FINISH_ACTION) return;
	if(Run->m_nMainStep != Run->m_nPreset)
	{
		Run->m_nPreset = Run->m_nMainStep;
		m_MainErrorTimeCheck.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
	}
	else if(m_MainErrorTimeCheck.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) >= a_nTime)
	{
		RunMgr->ModeChange(JAM, Run->m_nMainStep + a_nErrNo);
	}
}

void __stdcall CRunMgr::SubSeqCheckError	(DEF_RUN* Run, int a_nTime, int a_nErrNo)
{
	if(Run->m_nSubStep == FINISH_ACTION) return;
	if(Run->m_nSubStep != Run->m_nSubPreset)
	{
		Run->m_nSubPreset = Run->m_nSubStep;
		m_SubErrorTimeCheck.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
	}
	else if(m_SubErrorTimeCheck.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) >= a_nTime)
	{
		RunMgr->ModeChange(JAM, Run->m_nSubStep + a_nErrNo);
	}
}

RUN_MODE __stdcall CRunMgr::GetRunMode()
{
	return m_eRunMode;	
}


BOOL __stdcall CRunMgr::StartManualMode(SELECT_MANUAL_MODE a_eSelectManualMode)
{
	BOOL bStartOK = FALSE;

	return bStartOK;
}

BOOL __stdcall CRunMgr::RunManulMode(SELECT_MANUAL_MODE m_eSelectManualMode)
{
	BOOL bManualComplete = FALSE;

	return bManualComplete;
}

BOOL CRunMgr::GetModuleStop()
{
	BOOL bRtn = TRUE;


	return bRtn;
}

BOOL CRunMgr::SetJobClear()
{
	int nIndex = 0;


	return TRUE;
}



void CRunMgr::SetRunstatusClear(BOOL bStatus)
{
	//RecipeMgr->m_stRecipeMotionOption.m_bRunstatusClear = bStatus;
}
BOOL CRunMgr::GetRunstatusClear()
{
	//return RecipeMgr->m_stRecipeMotionOption.m_bRunstatusClear;
	return true;
}
void CRunMgr::SetStatusClearVariable(BOOL bStatus)
{
	m_bStatusClearCheck = bStatus;
}
BOOL CRunMgr::GetStatusClearVariable()
{
	return m_bStatusClearCheck;
}

void CRunMgr::SetDelayTime(unsigned int iSecond)
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
		Sleep(1);
	}
}

void CRunMgr::StartTimer(HWND hWnd) {
	m_hWnd = hWnd;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	if (m_hWnd) {
		m_nTimerID = ::SetTimer(m_hWnd, TM_INTER_LOCK_CHECK, 100, NULL);
		if(strSiteName == "SDI_POUCH")
		{
			m_nTimerID = ::SetTimer(m_hWnd, TM_START_PROGRAM, 100, NULL);
			m_nTimerID = ::SetTimer(m_hWnd, TM_LASER_CHECK, 100, NULL);
		}
	}
}


void CRunMgr::OffsetApply()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	IniUtil _iniUtil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

	SingleScannerParameter HEAD1Param, HEAD2Param;
	HEAD1Param.clear();
	HEAD2Param.clear();
	_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
	_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);

	CDsp *pDsp = CDsp::GetInstance();

	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
	int m_iUnit = pFieldParameter->GetUnit();

	pTransUnit->SetValue(HEAD1Param.xOffset, m_iUnit);
	pFieldParameter->SetMasterX(pTransUnit->GetField());

	pTransUnit->SetValue(HEAD1Param.yOffset, m_iUnit);
	pFieldParameter->SetMasterY(pTransUnit->GetField());

	pTransUnit->SetValue(HEAD2Param.xOffset, m_iUnit);
	pFieldParameter->SetSlaveX(pTransUnit->GetField());

	pTransUnit->SetValue(HEAD2Param.yOffset, m_iUnit);
	pFieldParameter->SetSlaveY(pTransUnit->GetField());

	pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
		(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );
}