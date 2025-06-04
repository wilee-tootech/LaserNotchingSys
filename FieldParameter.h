// FieldParameter.h: interface for the CFieldParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDPARAMETER_H__FCEA0894_F121_4F38_82CB_866BA8CD59B2__INCLUDED_)
#define AFX_FIELDPARAMETER_H__FCEA0894_F121_4F38_82CB_866BA8CD59B2__INCLUDED_

#include "DRect.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* 변수들의 Get() Set()만 담당하는 놈 */
/* 각 변수들은 Project 파일 (*.mrk) 을 통틀어 딱 한 개씩만 존재함 */
/* 이 놈들 중에는 파일에 저장되는 놈도 있고 항상 같은 변수로 초기화 되는 놈들도 존재 */


enum RunMode 
{
	Nonstop = 0, 
	OneStop = 1, 
	TwoStop = 2, 
	NonstopOneCut = 3
};


enum Pattern 
{
	T = 0, 
	S = 1,
	B = 2, 
	POUCH = 3, // 241218 MJY
	POUCH_TEST = 4 // 241218 MJY
};

typedef struct 
{
	double dWidth;
	double dHeight;
	double dExpendDist;
	double dStartExtOffset;
	double dEndExtOffset;
	double dLT_Radius;
	double dLB_Radius;
	double dRT_Radius;
	double dRB_Radius;
	double dLeftTabAngle;
	double dLeftCtrlPoint1;
	double dLeftCtrlPoint2;
	double dRightTabAngle;
	double dRightCtrlPoint1;
	double dRightCtrlPoint2;
	bool   bYFlip;
	int    nCuttingMode;
	double dYoffset;
	double dOffsetCutWidth;

	//------- 추가 파라메터 ------
	double dSloopWidth;
	double dSloopWidth_L;
	double dSloopWidth_R;
	double dBaseCutWidth;

	double dSloopSegment_LT;
	double dSloopSegment_RT;
	double dSloopSegment_LB;
	double dSloopSegment_RB;


	double dExtend_Xwidth_L;
	double dExtend_Xwidth_R;


	double dExtend_Yheight_L;
	double dExtend_Yheight_R;

	//------------------------- T사 파라메터 ---------------------
	
	double dNonflagStartWidth,dNonflagStartHeight,dNonflagEndWidth,dNonflagEndHeight;
	double dFoilExtention,dHEAD2Width,dBuriedHeight,dNotchRoot,dNublessHeight;
	double dTabWidth,dTabHeight,dTabCount,dT1Count,dTnCount,dTaLength,dTabPitch,dBuriedRegion,dNublessRegion,dFlagStartWidth;
	double dTabAngle;
	double dFlagVariableStartLength,dFlagVariableEndLength,dFlagVariableTotalLength;
	double dVariableTabWidth[100];//2023.12.22 For SDI

	double dPitchWidth1,dPitchWidth2,dPitchWidth3,dPitchWidth4,dPitchWidth5,dPitchWidth6; // 240426 jyh SDI UI Pitch 파라미터
	double dCuttingCnt1,dCuttingCnt2, dCuttingCnt3,dCuttingCnt4,dCuttingCnt5,dCuttingCnt6; // 240430 jyh 커팅 개수

	
	//-------------------------------------------------------------

	CString m_strFilename;

	double dMarkingFieldSize;

	double dNochingOutPosLeng;

	void clear()
	{
		
		dWidth = 0.0;
		dHeight = 0.0;
		dExpendDist = 0.0;
		dStartExtOffset = 0.0;
		dEndExtOffset = 0.0;
		dLT_Radius = 0.0;
		dLB_Radius = 0.0;
		dRT_Radius = 0.0;
		dRB_Radius = 0.0;
		dLeftTabAngle = 0.0;
		dLeftCtrlPoint1 = 0.0;
		dLeftCtrlPoint2 = 0.0;
		dRightTabAngle = 0.0;
		dRightCtrlPoint1 = 0.0;
		dRightCtrlPoint2 = 0.0;
		bYFlip = FALSE;
		nCuttingMode = 0;
		dYoffset = 0.0;
		dOffsetCutWidth = 0.0;

		//------ 추가 파라메터 --------//
		
		dSloopWidth = 0.0;
		dSloopWidth_L = 0.0;
		dSloopWidth_R = 0.0;
		dBaseCutWidth = 0.0;

		dSloopSegment_LT = 0.0;
		dSloopSegment_RT = 0.0;
		dSloopSegment_LB = 0.0;
		dSloopSegment_RB = 0.0;


		dExtend_Xwidth_L = 0.0;
		dExtend_Xwidth_R = 0.0;

		dExtend_Yheight_L = 0.0;
		dExtend_Yheight_R = 0.0;

		//---------------------------T사 추가파라메터----------------------
		dNonflagStartWidth = 40;//m_stNotchPatternData.dUnflagStart;
		dNonflagStartHeight = 1.2;
		dNublessRegion = 0;//m_stNotchPatternData.dNublessRegion;
		dNublessHeight = 3.25;
		dNotchRoot = 2.5;
		dTabWidth = 4;//m_stNotchPatternData.dTabWidth;
		dTabCount = 10;//m_stNotchPatternData.dTabCount;
		dT1Count = 10;
		dTnCount = 1;
		dTaLength = 1;
		dTabPitch = 1.0;
		dTabHeight = 5;//m_stNotchPatternData.dFlagLength;
		dBuriedRegion = 40;//m_stNotchPatternData.dBuriedRegion;
		dBuriedHeight = 1.2;
		dNonflagEndWidth = 40;//m_stNotchPatternData.dUnflagEnd;
		dNonflagEndHeight = 3.25;
		dTabAngle = 12.5;//m_stNotchPatternData.dFlagDegrees;
		dFoilExtention = 0;
		dHEAD2Width = 0;
		dFlagStartWidth = 0;


		dFlagVariableStartLength = 2;
		dFlagVariableEndLength = 4;
		dFlagVariableTotalLength = 2000;

		dPitchWidth1 = 0; // 240426 JYH SDI UI 
		dPitchWidth2 = 0;
		dPitchWidth3 = 0;
		dPitchWidth4 = 0;
		dPitchWidth5 = 0;
		dPitchWidth6 = 0; 
		dCuttingCnt1 = 0; // 240430 jyh
		dCuttingCnt2 = 0; 
		dCuttingCnt3 = 0;
		dCuttingCnt4 = 0;
		dCuttingCnt5 = 0;
		dCuttingCnt6 = 0;

		memset(dVariableTabWidth,NULL,sizeof(dVariableTabWidth));
		//------------------------------------------------------------------
		m_strFilename = _T("");

		
		dMarkingFieldSize = 0;

		dNochingOutPosLeng = 0;
	}

} _NOTCH_PATTERN_DATA;

#define MAX_SPREAD_ROW 25
typedef struct 
{
	double dTotalWidth;
	double dTotalHeight;
	double dTabCount;
	
	double dNotchingWidth[MAX_SPREAD_ROW];
	double dNotchingGabWidth[MAX_SPREAD_ROW];
	double dNotchingWidthOffset[MAX_SPREAD_ROW];
	double dNotchingRealWidth[MAX_SPREAD_ROW];
	double dNotchingAccWidth[MAX_SPREAD_ROW];
	double dNotchingAccOffset[MAX_SPREAD_ROW];

	double dNotchingWidthDiff;

	double dCuttingWidth;
	double dCuttingHeight;

	double dCuttingOffset; // 세라믹높이 만큼 더 쳐야함 // + 0.7고정 + 1.5만큼 위에서 더 치고내려오게

	double dArcDegree;

	// 선단부 아크 좌표
	double dArcInXPos;
	double dArcInYPos;

	// 종단부 아크 좌표
	double dArcOutXPos;
	double dArcOutYPos;

	double dPatternShift;
	void setDefault()
	{
		dTotalWidth = 0.0;			// 전체 넓이
		dTotalHeight = 0.0;			// 전체 높이
		dTabCount = 0;				// 탭 개수
		for (size_t i = 0; i < MAX_SPREAD_ROW; i++)
		{
			dNotchingWidth[i] = 0.0;
			dNotchingWidthOffset[i] = 0.0;
			dNotchingRealWidth[i] = 0.0;
			dNotchingAccWidth[i] = 0.0;
			dNotchingAccOffset[i] = 0.0;
			dNotchingGabWidth[i] = 0.0;
		}

		dNotchingWidthDiff = 0.00;  //  노칭길이 변동폭.

		dCuttingWidth = 0.0;		// 컷팅 길이
		dCuttingHeight = 0.0;		// 컷팅 높이

		dCuttingOffset = 0.0;		// 컷팅 옾셋

		dArcInXPos = 0.0;			// 아크 들어가는 X 좌표
		dArcInYPos = 0.0;			// 아크 들어가는 Y 좌표
		dArcOutXPos = 0.0;			// 아크 나가는 x 좌표
		dArcOutYPos = 0.0;			// 아크 나가는 Y 좌표

		dPatternShift = 0.0;
	}
} _POCKET_TMP_DATA_;



typedef struct 
{
	BOOL   bFlip;
	int	   nCuttingMode;
	double dTotalWidth;
	double dCuttingTotalWidth;
	double dNochingWidth;
	double dNochingHeight;
	double dCuttingHeight;
	double dCuttingTabWidth1;
	double dCuttingTabWidth2;
	double dCuttingTabWidth3;
	double dCuttingTabWidth4;
	double dCuttingTabWidth5;
	double dCuttingTabWidth6;
	double dCuttingCount1;
	double dCuttingCount2;
	double dCuttingCount3;
	double dCuttingCount4;
	double dCuttingCount5;
	double dCuttingCount6;
	double dCuttingAngle;
	double dNochingAngle;
	double dNochingOutPosWidth;//외곽부 

	

	void setDefault()
	{
		bFlip=1;
		nCuttingMode=2;
		dCuttingTotalWidth=3660.00;
		dNochingWidth=1071.00;
		dNochingHeight=4.5;
		dCuttingHeight=4;
		dCuttingTabWidth1=2.00;
		dCuttingTabWidth2=2.20;
		dCuttingTabWidth3=2.40;
		dCuttingTabWidth4=2.60;
		dCuttingTabWidth5=2.80;
		dCuttingTabWidth6=3.00;
		dCuttingCount1=244.00;
		dCuttingCount2=244.00;
		dCuttingCount3=244.00;
		dCuttingCount4=244.00;
		dCuttingCount5=244.00;
		dCuttingCount6=244.00;
		dCuttingAngle=-10;
		dNochingAngle=0;
		dNochingOutPosWidth=500;
	}
} _SDI_NOTCH_PATTERN_DATA;


typedef struct _BMW_DATA_
{
	double dGraphiteHeight;
	double dTotalHeight;

	double dInsertSegmentHeight;
	double dInsertSegmentDeepHeight;
	double dInsertSegmentLength;

	double dEndSegmentHeight;
	double dEndSegmentLength;

	double dFlagWaitLength;
	double dFlagInoutLength;
	double dFlagDeepLength;
	double dFlagTotalLegnth;
	double dFlagHeight;
	double dTabCount;

		

	double dMaxField;
	double dMaxMm;


	
	void SetFieldSizeAndMmSize(double maxField, double maxMm)
	{
		dMaxField = maxField;
		dMaxMm = maxMm;
	}

	void SetDefaultValue()
	{
		dGraphiteHeight = 0;
		dTotalHeight = 0;
		
		dInsertSegmentHeight = 0;
		dInsertSegmentDeepHeight = 0;
		dInsertSegmentLength = 0;
		
		dEndSegmentHeight = 0;
		dEndSegmentLength = 0;
		
		dFlagWaitLength = 0;
		dFlagInoutLength = 0;
		dFlagDeepLength = 0;
		dFlagTotalLegnth = -10;
		dTabCount = 0;
		dFlagHeight = 0;

		dMaxField = 0;
		dMaxMm = 0;
	}

	double FieldValue(double realValue)
	{
		if(dMaxMm == 0)
		{
			return 0;
		}

		return realValue * dMaxField / dMaxMm;
	}

	double FieldValueToMM(double fieldValue)

	{
		if(dMaxField == 0)
		{
			return 0;
		}

		return fieldValue / dMaxField * dMaxMm;
	}

} BPATTERNDATA;


typedef struct _LG_DATA_
{
	struct LGFLAG
	{
		double flagHeight;
		double flagTotalLength; 
		double flagCount;
		double flagAngle;
	};



	double unflagLength; 

	LGFLAG flagData[15];


} LGDATA;


typedef struct _LASERSTATUS_
{
	
		bool   bHEAD1_LASER_ON;
		bool   bHEAD1_LASER_ENBLED;
		bool   bHEAD1_LASER_DISABLED;
		bool   bHEAD1_LASER_EMISSIONS_GATE;
		bool   bHEAD1_LASER_EMISSION;
		bool   bHEAD1_LASER_TASK_ACTIVE;
		bool   bHEAD1_LASER_ALARM;
		bool   bHEAD1_LASER_SYSTEM_FAULT;
		bool   bHEAD1_INTERLOCK;
		bool   bHEAD1_LASER_READY;
		double dHEAD1_LASER_BODY_TEMP;
		double dbHEAD1_LASER_BEAM_DELIVERLY_TEMP;
		double dHEAD1_LASER_ACTIVE_MV;
		//2023.08.29 LASER PULSE RATE, LASER ACTIVE POWER 추가. LaserParameter 항목으로 되어있지만 상태로 포함하여 사용.
		double dHEAD1_LASER_PULSE_RATE;
		double dHEAD1_LASER_ACTIVE_POWER;

		bool   bHEAD2_LASER_ON;
		bool   bHEAD2_LASER_ENBLED;
		bool   bHEAD2_LASER_DISABLED;
		bool   bHEAD2_LASER_EMISSIONS_GATE;
		bool   bHEAD2_LASER_EMISSION;
		bool   bHEAD2_LASER_TASK_ACTIVE;
		bool   bHEAD2_LASER_ALARM;
		bool   bHEAD2_LASER_SYSTEM_FAULT;
		bool   bHEAD2_INTERLOCK;
		bool   bHEAD2_LASER_READY;
		double dHEAD2_LASER_BODY_TEMP;
		double dHEAD2_LASER_BEAM_DELIVERLY_TEMP;
		double dHEAD2_LASER_ACTIVE_MV;
		//2023.08.29 LASER PULSE RATE, LASER ACTIVE POWER 추가. LaserParameter 항목으로 되어있지만 상태로 포함하여 사용.
		double dHEAD2_LASER_PULSE_RATE;
		double dHEAD2_LASER_ACTIVE_POWER;


		void clear()
		{
			bHEAD1_LASER_ON = 0;
			bHEAD1_LASER_ENBLED= 0;
			bHEAD1_LASER_DISABLED= 0;
			bHEAD1_LASER_EMISSIONS_GATE= 0;
			bHEAD1_LASER_EMISSION= 0;
			bHEAD1_LASER_TASK_ACTIVE= 0;
			bHEAD1_LASER_ALARM= 0;
			bHEAD1_LASER_SYSTEM_FAULT= 0;
			bHEAD1_INTERLOCK= 0;
			bHEAD1_LASER_READY= 0;
			dHEAD1_LASER_BODY_TEMP= 0;
			dbHEAD1_LASER_BEAM_DELIVERLY_TEMP= 0;
			dHEAD1_LASER_ACTIVE_MV= 0;
			dHEAD1_LASER_PULSE_RATE=0;
			dHEAD1_LASER_ACTIVE_POWER=0;

			bHEAD2_LASER_ON= 0;
			bHEAD2_LASER_ENBLED= 0;
			bHEAD2_LASER_DISABLED= 0;
			bHEAD2_LASER_EMISSIONS_GATE= 0;
			bHEAD2_LASER_EMISSION= 0;
			bHEAD2_LASER_TASK_ACTIVE= 0;
			bHEAD2_LASER_ALARM= 0;
			bHEAD2_LASER_SYSTEM_FAULT= 0;
			bHEAD2_INTERLOCK= 0;
			bHEAD2_LASER_READY= 0;
			dHEAD2_LASER_BODY_TEMP= 0;
			dHEAD2_LASER_BEAM_DELIVERLY_TEMP= 0;
			dHEAD2_LASER_ACTIVE_MV= 0;

			dHEAD2_LASER_PULSE_RATE=0;
			dHEAD2_LASER_ACTIVE_POWER=0;


		}
	
} LASERSTATUS;

typedef struct FieldParameter
{
	double FieldSize;
	double MmSize;
	double Unit;
	double KX;
	double KY;
	double KX2;
	double KY2;
	double KX_Notch;
	double KY_Notch;
	double KX2_Notch;
	double KY2_Notch;
	double MaxCuttingSize;
	double RollSpeed;
	double SampleSize;
	double RealSize;
	double RFieldSize;
	double MarkingField;
	double CycleOffset;
	double CycleOffset2;
	double ScannerStartPosX;
	double ScannerStartPosY;
	int ModeValue;
	double nPattern;
	double Cutting_set_head1;
	double Cutting_act_head1;
	double Cutting_set_head2;
	double Cutting_act_head2;
	double Notching_set_head1;
	double Notching_act_head1;
	double Notching_set_head2;
	double Notching_act_head2;
} FieldParameter;
		

class CFieldParameter  
{
public:
	double GetHEAD1LaserPower();
	void SetHead1LaserPower(double power);
	double GetHEAD2LaserPower();
	void SetHead2LaserPower(double power);
	CString GetFileName();
	void SetFileName(CString m_strFileName);
	void WeekcodeIndex(int weekcodepara);
	CString GetWeekCodeString(int m_iday, int m_itime);
	void SetWeekCodeString(CString strWeekCode);
	BOOL GetSemiteqAutoText();
	void SetSemiteqAutoText(BOOL m_flag);
	CString GetAmkorPenFileName();
	void SetAmkorPenFileName(CString m_strPenName);
	BOOL GetMaxTextWarning();
	void SetMaxTextLimitWarning(BOOL m_flag);
	BOOL GetLaserWarning();
	void SetLaserWarning(BOOL m_warning);
	void SetUpdateText(CString m_strText);
	CString GetUpdateText();
	BOOL GetChangeText();
	void SetChangeText(BOOL m_flag);
	BOOL GetGroupSameAngle();
	void SetGroupSameAngle(BOOL m_flag);
	BOOL GetDBAccessFlag();
	void SetDBAccessFlag(BOOL m_DBFlag);
	void SetGroupObjRect(CRect m_rect);
	BOOL GetGroupFlag();
	void SetGroupFlag(BOOL m_flag);
	CRect GetGroupObjRect();
	void SetGuideCheck(int index , BOOL cflag);
	BOOL GetGuideCheck(int index);
	CPoint GetZeroArea(int index);
	void SetZeroArea(CPoint m_area, int index);
	CString GetAmkPreBuf(int index);
	void SetAmkPreBuf(int index, CString m_data);
	BOOL GetSelectAllFlag();
	void SetSelectAllFlag(BOOL m_selectFlag);
	double GetSetedPowerValue();
	void SetSetedPowerValue(double m_SedtedPower);
	void SetDeviceType(int m_DeviceType);
	int  GetDeviceType();
	CString GetSemFileTextFromDB(/*CString strSem*/int strSEQ);
	void SetSemTextFromDB(CString strText,int strSEQ);
	void ClearSemTextBuffer();
	CString GetAmkorPrjFileName();
	void SetAmkorPrjFileName(CString m_FileName);
	void SetAmkorRscFileName(CString m_FileName);
	CString GetAmkorRscFileName();
	BOOL GetSimulationFlag();
	void SetSimulationFlag(BOOL m_bsimulation);
	void SetGuideLineSet(CDRect m_Guide, int index);
	CDRect GetGuideLineValue(int index);

	void SetWeekDay(int m_iday);
	int  GetWeekDay();
	void SetWeekTime(int m_iweektime);
	int  GetWeekTime();

	CFieldParameter();
	virtual ~CFieldParameter();

	int	 GetUnit();
	int  GetLensSize();
	int  GetDelayTime();
	double	 GetMasterX();
	double  GetMasterY();
	double  GetSlaveX();
	double  GetSlaveY();
	int	 GetRunMode();
	int	 GetPatternMode();
	void SetSize(double mmSize, double fieldSize); // User가 셋팅한 Field & mm Size를 가져다가 setting
	void GetSize(double *mmSize, double *fieldSize);
	void SetFieldAngle(double fieldAngle);

	void SetLensSize(int lensSize); // SetLensSize시에는 ctdFile의 이름도 변화할 필요성이 있다.
	void SetDelayTime(int delayTime);
	void SetUnit(int iUnit);
	void SetMasterX(double iMasterX);
	void SetMasterY(double iMasterY);
	void SetSlaveX(double iSlaveX);
	void SetSlaveY(double iSlaveY);
	void SetRunMode(int runMode);
	void SetPatternMode(int patternMode);
	UINT OpenFile();
	UINT SaveFile();
	double GetFieldAngle();
	/* 설정된 카운트 */
	void SetSetCount(int iSetCount);
	int  GetSetCount();
	/* 커팅된 카운트 */
	void InitialCount(); // Count를 0으로 초기화
	void IncreaseCount(int interval); // Count interval만큼씩 증가시키기
	int	 GetMarkedCount();
	void SetSimulationSpeed(int iSimulationSpeed);
	int  GetSimulationSpeed();
	CString m_strUpdateText;
	CString m_strWeekCode;
	CString m_strAmicWeekCode;// 
	CString m_strSplitWeekCode;// 2007.01.12   split
	CString m_strIssueWeekCode;// 2007.01.12   issue
	CString m_strLotCountCode;// 2007.03.13   lot count
	static CFieldParameter* GetInstance();
	CString m_strLotCountFormat;	
	

private:
	static CFieldParameter* m_pFieldParameter;
	int		m_iUnit;
	double	m_dMMSize;
	double	m_dFieldSize;
	int		m_iLensSize;
	int		m_iDelayTime; // 커팅 전 delay Time 설정


	double  m_dKX;
	double  m_dKY;
	double  m_dKX2;
	double  m_dKY2;

	double	m_dKX_Notch;
	double	m_dKY_Notch;
	double	m_dKX2_Notch;
	double	m_dKY2_Notch;


	double  m_dSavedEncooderCountHead1;//2024.06.28 프로그램 껏다 실행시 이어작업 하기위해 추가.
	double  m_dSavedEncooderCountHead2;

	double  m_dMaxCuttingSize;
	double  m_dRollSpeed;
	double m_dSampleSize;
	double m_dRealSize;
	double m_dRFieldSize;
	double m_dMarkingField;
	double m_dCycleOffset;
	double m_dCycleOffset2;
	double m_dScannerStartPosX;
	double m_dScannerStartPosY;
	int ModeValue;

	double  m_dSpeedScale;
	BOOL    m_bEncoderReverse;
	int     m_iSimulationMode;
	double	m_iMasterX;	/* 항상 Field로 저장하고 있기 때문에 int임 */
	double	m_iMasterY;
	double	m_iSlaveX;
	double	m_iSlaveY;
	double  m_dSetedPowerValue; 
	int		m_iSetCount;
	int		m_iMarkedCount;
	int		m_iSimulationSpeed;
	BOOL    m_bSimulationFlag;
	double	m_dFieldAngle;
	CString	m_strFileName;
	CString m_AmkorRscFileName;
	CString m_AmkorPrjFileName;
	CString m_SemFileTextFromDB;
	CString m_SemTextArray[100];
	CString m_returnedTextBuffer[100];
	CString m_AmkPreSelBuffer[8];
	int m_dDeviceType;
	BOOL m_SelectAllFlag;
	CPoint m_ZeroArea[100];
	CDRect m_GuideLineBuf[10];
	BOOL   m_GuideCheckBuf[10];
	CRect m_objRect;
	BOOL   m_bGroupFlag;
	BOOL m_DBAccessFlag;
	BOOL m_GroupSameAngle;
	BOOL m_bChangeText;
	BOOL m_bSemiteqAutoText;
	//CString m_strUpdateText;
	BOOL m_bLaserWarningDetect;	
	BOOL m_bMaxTextWarning;
	CString m_strAmkorPenFile;
	int  m_iweekday;
	int  m_iweekTime;
	CString m_strLotNoAC; // 2007.06.15  
	CString m_strPartNo;
	CString m_strLotNo;
	CString m_strRunNo;
	CString m_strBinCode;	
	CString m_strDevcieCode;
	CString m_strTapFileName;
	CString m_strPatternView;

	BOOL m_bAutoHAlign;
	BOOL m_bAutoVAlign;

	BOOL m_bLaserPower;
	BOOL m_bScannerPower;
	BOOL m_bLaserEnable;

	BOOL m_bSkipModeSignalHEAD2;
	BOOL m_bSkipModeSignalHEAD1;

	BOOL m_bAutoMarkFlag;
	BOOL m_bDownloadFlag;
	
	// 2018.10.04 jjsjong For KOEM
	double m_dSloopOfWidth;
	double m_dSloopOfWidthLeft;
	double m_dSloopOfWidthRight;
	double m_dSloopSegmentLeft;
	double m_dSloopSegmentRight;
	double m_dExtandLine_widthX_Left;
	double m_dExtandLine_widthX_Right;
	double m_dExtandLine_heightY_Left;
	double m_dExtandLine_heightY_Right;

	double m_dAdjustVector;
	double m_dMultiSpeed[250];

	

	bool   m_bPreviewMode;
	bool   m_bUnitShapePreviewMode;
	bool   m_bSavePatternImage;

	long   m_lEncoderPosition;
	bool   m_bHighLowFlag;


	// 2021.08.27 김준혁 모드 FieldParameter에서 선택하도록 수정
	int m_nRunMode;
	int m_bPatternViewType;
	int m_nPatternMode;

	BOOL  m_bPatternOfKoem;
	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD1;
	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD2;
	
	
	_SDI_NOTCH_PATTERN_DATA m_stSDIPatternDataHEAD1;
	_SDI_NOTCH_PATTERN_DATA m_stSDIPatternDataHEAD2;

	BPATTERNDATA m_BMWPatternData;
	LASERSTATUS m_LaserStatusHEAD2;
	LASERSTATUS m_LaserStatusHEAD1;

	_POCKET_TMP_DATA_ m_stPatternDataOfPocketAnode; // 양극임시테스트용 24105_1626 LDY
	_POCKET_TMP_DATA_ m_stPatternDataOfPocketCathode; // 파우치 UI 테스트 241217 MJY

	_POCKET_TMP_DATA_ m_stParameterData; // 파우치 UI 테스트 241217 MJY
	_POCKET_TMP_DATA_ m_stPatternDataOfPocketAnodeModeB; // 파우치 UI 테스트 241217 MJY
	_POCKET_TMP_DATA_ m_stPatternDataOfPocketCathodeModeA; // 파우치 UI 테스트 241217 MJY
	_POCKET_TMP_DATA_ m_stPatternDataOfPocketCathodeModeB; // 파우치 UI 테스트 241217 MJY

	FieldParameter m_fieldSettingParameter;
	

	_LG_DATA_ m_LGData;

public:
	void SetSkipModeHEAD2(BOOL bFlag);
	BOOL GetSkipModeHEAD2();
	void SetSkipModeHEAD1(BOOL bFlag);
	BOOL GetSkipModeHEAD1();

	BOOL GetLaserEnableSig();
	void SetLaserEnableSig(BOOL bFlag);
	BOOL GetScannerPowerSig();
	void SetScannerPowerSig(BOOL bFlag);
	BOOL GetLaserPowerSig();
	void SetLaserPowerSig(BOOL bFlag);
	CString GetYMD();
	CString GetDeviceCode();
	CString GetBinCode();
	void SetDeviceCode(CString strData);	
	void SetBinCode(CString strData);	
	BOOL GetAutoVAlignment();
	void SetAutoVAlignment(BOOL m_flag);
	BOOL GetAutoHAlignment();
	void SetAutoHAlignment(BOOL m_flag);

	void SetPatternView(CString strData);	
	CString GetPatternView();

	// 2007.03.13   - lot count
	void SetLotCountCodeString(int count, CString format);
	CString GetLotCountcode();

	// 2007.01.12   - issue (Amic)
	void SetIssueWeekCodeString(CString m_strWeekcode);
	CString GetIssueWeekcode();

	// 2007.01.12   - split
	void SetSplitWeekCodeString(CString m_strWeekcode);
	CString GetSplitWeekcode();

	CString GetAutoDisplaceLotNo(CString strIndex);
	CString GetRunNo();
	void SetRunNo(CString strData);
	CString GetLotNo();
	CString GetLotNoAC();
	void SetLotNo(CString strData);
	void SetLotNoAC(CString strData);
	CString GetPartNo();
	void SetPartNo(CString m_strData);
		//20060407 
	int m_weekcodeselectpara;
	
	void SetSloopWidth(double dSloopWidth);
	double GetSloopWidth();
	void SetPreviewMode(bool bPreview);
	bool GetPreViewMode(void);
	void SetPatternOfKoem(bool bKoemPattern);
	bool GetPatternOfKoem(void);
	int SetHEAD2PatternData(_NOTCH_PATTERN_DATA KOEM_PATTERN_DATA);
	int SetHEAD1PatternData(_NOTCH_PATTERN_DATA koemPatternData);
	
	_NOTCH_PATTERN_DATA GetHEAD2PatternDataOfKoem(void);
	_NOTCH_PATTERN_DATA GetHEAD1PatternDataOfKoem(void);

	int SetSDIPatternDataHEAD1(_SDI_NOTCH_PATTERN_DATA PatternData);
	int SetSDIPatternDataHEAD2(_SDI_NOTCH_PATTERN_DATA PatternData);
	_SDI_NOTCH_PATTERN_DATA GetSDIPatternDataHEAD1(void);
	_SDI_NOTCH_PATTERN_DATA GetSDIPatternDataHEAD2(void);

	_POCKET_TMP_DATA_ GetPocketPatternParameterData(void);
	int SetPocketPatternParameterData(_POCKET_TMP_DATA_ tmpPocketData);

	FieldParameter GetFieldParameterData(void);
	int SetFieldParameterData(FieldParameter FieldData);

	BPATTERNDATA GetBMWData();
	void SetBMWData(BPATTERNDATA data);

	LASERSTATUS  GetLaserStatusHEAD2();
	void SetLaserStatusHEAD2(LASERSTATUS status);

	LASERSTATUS  GetLaserStatusHEAD1();
	void SetLaserStatusHEAD1(LASERSTATUS status);


	void SetUnitShapePreview(bool bUnisSahpeView);
	bool GetUnitSahpePreview(void);
	void SetSloopWidthOfLeft(double dSloopWidthLeft);
	double GetSloopWidthOfLeft(void);
	void SetSloopWidthOfRight(double dSloopWidthRight);
	double GetSloopWidthOfRight(void);
	void SetPatternFileName(CString strFilename);
	CString GetPatternFileName(void);
	bool GetPatternFlipY(void);
	void SetPatternFlipY(bool bYFlip);
	void SetTapPositionFilename(CString strfilename);
	CString GetTapFilename(void);
	void SetSloopSegment(double dLeftSegmentLT, double dLeftSegmentLB, double dRightSegmentRT,double dRightSegmentRB);
	void GetSloopSegment(double & dLeftSegmentLT, double & dLeftSegmentLB, double & dRightSegmentRT,double & dRightSegmentRB);
	void SetAdjustVector(double dVector);
	double GetAdjustVector(void);
	
	void SetExtendLine_Xwidth(double dLeftWidth, double dRightWidth);
	void GetExtendLine_Xwidth(double & dLeftWidth, double & dRightWidth);

	void SetExtendLine_Yheight(double dLeftHeight, double dRightHeight);
	void GetExtendLine_Yheight(double & dLeftHeight, double & dRightHeight);


	void SavePatternImage(bool bFlag);
	bool GetPatternSaveFlag(void);
	void SetKxKy(double kx, double ky);
	void SetKxKy_Notch(double kx, double ky);
	double GetKX(void);
	double GetKY(void);
	double GetKX_Notch(void);
	double GetKY_Notch(void);
	void SetKxKy2(double kx, double ky);
	void SetKxKy2_Notch(double kx, double ky);
	double GetKX2(void);
	double GetKY2(void);
	double GetKX2_Notch(void);
	double GetKY2_Notch(void);




	void  SaveEncoderCountToFile(double dHead1_Cnt, double dHead2_Cnt);
	void  GetSavedEncoderCountFromFile(double *dHead1_Cnt, double *dHead2_Cnt);
	


	void SetSimulationMode(int nMode);
	int GetSimulationMode(void);
	void SetEncoderReverse(bool bFlag);
	bool GetEncoderReverse();
	void SetSpeedScale(double dScale);
	double GetSpeedScale(void);
	void SetEncoderPositionIoCheckView(long lEncoderPosition, bool bSig1HighLowFlag);
	void GetEncoderPositionIoCheckView(long & lEncoderPosition, bool & bHighLowFlag);
	void SetAutoMarkFlag(bool bAutoMarkFlag);
	bool GetAutoMarkFlag(void);
	void SetMaxCuttingSize(double dMaxCuttingSize);
	double GetMaxCuttingSize();
	void SetRollSpeed(double dRollSpeed);
	double GetRollSpeed(void);
	void SetMarkingField(double dMarkingField);
	double GetMarkingField(void);
	void SetCycleOffset(double dCycleOffset);
	double GetCycleOffset(void);
	void SetCycleOffset2(double dCycleOffset);
	double GetCycleOffset2(void);


	void SetScannerStartPosX(double dScannerStartX);
	double GetScannerStartPosX(void);
	void SetScannerStartPosY(double dScannerStartY);
	double GetScannerStartPosY(void);
	
	void Setmultispeed(int nIndex, double dSpeed);
	int GetMultispeed(int nIndex);
	void SetDownloadFlag(bool bDouwnloadFlag);
	bool GetDownloadFlag(void);
	void SetSampleSize(double dSampleSize);
	double GetSampleSize(void);
	void SetRealSize(double dRealSize);
	double GetRealSize(void);
	void SetRFieldSize(double dRFieldSize);
	double GetRFieldSize(void);
};

#endif // !defined(AFX_FIELDPARAMETER_H__FCEA0894_F121_4F38_82CB_866BA8CD59B2__INCLUDED_)
