// Parameter.h: interface for the CParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETER_H__DA2F71C1_197C_48C6_8C78_3CCC98F42507__INCLUDED_)
#define AFX_PARAMETER_H__DA2F71C1_197C_48C6_8C78_3CCC98F42507__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParameter // List를 형성하고 Iterator에 의해 검색당할 것임.
{
public:
	int GetPowerSetTime();
	void SetPowerSetTime(int iPst);
	int GetPulseCount();
	void SetLaserPowerSet(double m_dPower);
	double GetLaserPowerSet();
	int GetLampPower();
	CParameter();
		CParameter(int iIndex, TCHAR cName[], double iMarkStep, double iJumpStep, int iStepPeriod, int iMarkDelay, int iJumpDelay, int iStrokeDelay,
		      int iFrequency, int iPulseWidth, int iLampPower,int iLaserOnDelay, int iLaserOffDelay,  int iFPS, int iBmpSize,
			  int iDwellTime, int iLineMoveDelayTime, double m_dLaserPower, int iPulseCount, int iPst, int iJumpSpeed, int iJumpPower, int iStartSpeed,
			  int iStartPower, int iStartExtSpeed, int iStartExtPower, int iStartChangeDelay, int iEndSpeed, int iEndPower, int iEndExtSpeed, int iEndExtPower,
			  int iEndChangeDelay, int iLineSpeed, int iLinePower, int iLineOffsetPower, double iScaleM5, double iScaleM4, double iScaleM3, double iScaleM2,
			  double iScaleM1, double iScale0, double iScale1, double iScale2, double iScale3, double iScale4, double iScale5, double iFlagJumpSpeed,
			  int iNonflagExtSpeed, int iNonflagLineExtSpeed, int iNonflagExtLen, int iNonFlagLineExtLen, int iFlagExtLen);

	void SetRTCParameter();

	virtual ~CParameter();

	/* 파일 저장 로딩을 위함 */
	int  GetIndex();
	double  GetMarkStep();
	double  GetJumpStep();
	double  GetFlagJumpStep();
	double GetFlagJumpSpeed();
	int  GetStepPeriod();
	int  GetMarkDelay();
	int  GetJumpDelay();
	int  GetStrokeDelay();
	int  GetFrequency();
	int  GetPulseWidth();
	int  GetLaserOnDelay();
	int  GetLaserOffDelay();
	int  GetFPS();
	int  GetBmpSize();
	int  GetDwellTime();
	int  GetLineMoveDelayTime();
	char *GetName();
	char *GetScrPathName();

	//-------------------------------------NEW Parameter----------------------------------

	int GetJumpSpeed();
	
	int GetJumpPower();
	int GetFlagSpeed();
	int GetFlagPower();
	int GetUnflagLineSpeed();
	int GetUnflagPower();
	int GetStartChangeDelay();
	int GetFlagExtSpeed();
	int GetFlagExtPower();
	int GetEndExtSpeed();
	int GetEndExtPower();
	int GetEndChangeDelay();
	int GetUnflagInoutSpeed();
	int GetUnflagInoutPower();
	int GetLineOffsetPower();
	double GetChangeLineSpeed(int iIndex);
	double GetScaleM5();
	double GetScaleM4();
	double GetScaleM3();
	double GetScaleM2();
	double GetScaleM1();
	double GetScale0();
	double GetScale1();
	double GetScale2();
	double GetScale3();
	double GetScale4();
	double GetScale5();
	int GetUnFlagInoutExtSpeed();
	int GetNonFlagLineExtSpeed();
	int GetNonFlagExtLen();
	int GetNonFlagLineExtLen();
	int GetFlagExtLen();

	void GetPositionDataArray(float dataArray[]);
	void SetPositionDataArray(float dataArray[]);
	void GetPositionScaleArray(float dataArray[]);
	void SetPositionScaleArray(float dataArray[]);

	
	void UnSerialize(char *pstrSerial);
	char *Serialize(DWORD &dwLength);

	enum VariableParameterID
	{
		ID_INDEX = 10000,
		ID_MARK_STEP = 10001,
		ID_JUMP_STEP = 10002,
		ID_STEP_PERIOD = 10003,
		ID_MARK_DELAY = 10004,
		ID_JUMP_DELAY = 10005,
		ID_STROKE_DELAY = 10006,
		ID_FREQUENCY = 10007,
		ID_PULSE_WIDTH = 10008,
		ID_LAMP_POWER  = 10009,
		ID_LASERON_DELAY = 10010,
		ID_LASEROFF_DELAY = 10011,
		ID_FPS = 10012,
		ID_BMPSIZE = 10013,
		ID_DWELLTIME = 10014,
		ID_LINEMOVEDELAYTIME = 10015,
		ID_NAME = 10016,
		ID_PATHNAME = 10017,
		ID_LASER_POWER = 10018,
		ID_PULSE_COUNT = 10019,
		ID_POWER_SET_TIME = 10020,
		ID_FILE_NAME     = 10021,

		//----------------------------------------------NEW Parameter----------------------------------------------------------------
		ID_START_SPEED = 10022,
		ID_START_POWER = 10023,
		ID_START_EXT_SPEED = 10024,
		ID_START_EXT_POWER = 10025,
		ID_START_CHANGE_DELAY = 10026,
		ID_END_SPEED = 10027,
		ID_END_POWER = 10028,
		ID_END_EXT_SPEED = 10029,
		ID_END_EXT_POWER = 10030,
		ID_END_CHANGE_DELAY = 10031,
		ID_LINE_SPEED = 10032,
		ID_LINE_POWER = 10033,
		ID_LINE_OFFSET_POWER = 10034,
		ID_JUMP_SPEED = 10035,
		ID_JUMP_POWER = 10036,
		// ----------------------------- New Position Data -------------
		ID_SCALE_M5 = 10047,
		ID_SCALE_M4 = 10037,
		ID_SCALE_M3 = 10038,
		ID_SCALE_M2 = 10039,
		ID_SCALE_M1 = 10040,
		ID_SCALE_0 = 10041,
		ID_SCALE_1 = 10042,
		ID_SCALE_2 = 10043,
		ID_SCALE_3 = 10044,
		ID_SCALE_4 = 10045,
		ID_SCALE_5 = 10046,

		// 2021.07.06 ReplaySyndrome ------------ PowerControlByPosition
		ID_POSITIONDATA_1 = 10101,
		ID_POSITIONDATA_2 = 10102,
		ID_POSITIONDATA_3 = 10103,
		ID_POSITIONDATA_4 = 10104,
		ID_POSITIONDATA_5 = 10105,
		ID_POSITIONDATA_6 = 10106,
		ID_POSITIONDATA_7 = 10107,
		ID_POSITIONDATA_8 = 10108,

		ID_POSITION_SCALE_1 = 10111,
		ID_POSITION_SCALE_2 = 10112,
		ID_POSITION_SCALE_3 = 10113,
		ID_POSITION_SCALE_4 = 10114,
		ID_POSITION_SCALE_5 = 10115,
		ID_POSITION_SCALE_6 = 10116,
		ID_POSITION_SCALE_7 = 10117,
		ID_POSITION_SCALE_8 = 10118,

		ID_FLAG_JUMP_SPEED = 10119,
		ID_NONFLAG_EXT_SPEED = 10120,
		ID_NONFLAG_LINE_EXT_SPEED = 10121,
		ID_NONFLAG_EXT_LEN = 10122,
		ID_NONFLAG_LINE_EXT_LEN = 10123,
		ID_FLAG_EXT_LEN = 10124

	};

private:
	int m_iIndex;
	double m_dMarkStep;
	double m_dJumpStep;
	int m_iStepPeriod;
	int m_iMarkDelay;
	int m_iJumpDelay;
	int m_iStrokeDelay;
	int m_iFrequency;
	int m_iPulseWidth;
	int m_iLampPower;
	int m_iLaserOnDelay;
	int m_iLaserOffDelay;
	int m_iFPS;
	int m_iBmpSize;
	int m_iDwellTime;
	int m_iLineMoveDelayTime;
	TCHAR m_ScrPath[100];
	TCHAR m_cName[20];
	double m_dSetLaserPower;
	int m_iPulseCount;
	int m_iPst;
	TCHAR m_Filename[100];
	//----------------- NEW Parameter ---------------------------------------

	int m_iJumpSpeed;
	int m_iJumpPower;
	int m_iStartSpeed;
	int m_iStartPower;
	int m_iStartExtSpeed;
	int m_iStartExtPower;
	int m_iStartChangeDelay;
	int m_iEndSpeed;
	int m_iEndPower;
	int m_iEndExtSpeed;
	int m_iEndExtPower;
	int m_iEndChangeDelay;
	int m_iLineSpeed;
	int m_iLinePower;
	int m_iLineOffsetPower;
	int m_iChangeLineSpeed;
	int m_iLineSpeedIndex;
	int m_iFlagJumpSpeed;
	//--------------- New Position Control Data -----------------------
	double		m_iScaleM5;
	double		m_iScaleM4;
	double		m_iScaleM3;
	double		m_iScaleM2;
	double		m_iScaleM1;
	double		m_iScale0;
	double		m_iScale1;
	double		m_iScale2;
	double		m_iScale3;
	double		m_iScale4;
	double		m_iScale5;

	int		m_iNonflagExtSpeed;
	int		m_iNonflagLineExtSpeed;
	int		m_iNonflagExtLen;
	int		m_iNonFlagLineExtLen;
	int		m_iFlagExtLen;


public:
	void SetFilename(CString strFilename);
	void SetChangLineSpeed(int dTapPosition);

	// 2021.07.06 ReplaySyndrome
	float m_fPositionArray[8];
	float m_fPositionScaleArray[8];
};

#endif // !defined(AFX_PARAMETER_H__DA2F71C1_197C_48C6_8C78_3CCC98F42507__INCLUDED_)
