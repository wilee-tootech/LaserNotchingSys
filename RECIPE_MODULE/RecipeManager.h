#ifndef _RECIPE_MANAGER_H_
#define _RECIPE_MANAGER_H_

#pragma once

#include <NX_KEYPAD/AlphaKeyPad.h>
#include <NX_RECIPE_PATH/RecipePathManager.h>

#include "../Include/EXTERN/fpspread8.h"

#include "RecipeDefine.h"

#define RECIPE_DIRECTORY_NAME			"\\Config\\"

#define  RECIPE_LASER_COUNT					10

enum 
{
	RECIPE_SPREAD_NO		= 1	,
	RECIPE_SPREAD_ITEM			,
	RECIPE_SPREAD_UNIT			,
	RECIPE_SPREAD_VALUE			,
	RECIPE_SPREAD_UPLOAD		,
	//
	RECIPE_SPREAD_EXPLANATION	,

};

typedef struct DEF_RECIPE_PATH
{
	CString m_strEquimentPath;
	CString m_strSystemPath;
	CString m_strMESLogPath;
	

	DEF_RECIPE_PATH(void)
	{
		Clear();
	}

	void Clear()
	{
		m_strEquimentPath						= _T("");
		m_strSystemPath							= _T("");
		m_strMESLogPath							= _T("");
		
	}

}RECIPE_PATH;

//////////////////////////////////////////////////////////////////////////

//Recipe Body
typedef struct DEF_RECIPE_MOTION_BODY
{

#define DEF_RECIPE_MOTION_BODY_COUNT 6

	double	m_fMaxLimit;
	double	m_fMinLimit;

	double m_fCondinate_Offset_X; //전체 Offset X
	double m_fCondinate_Offset_Y; //전체 Offset Y

	double m_fAlignAccuracy_X;	  //Align 정밀도 X
	double m_fAlignAccuracy_Y;	  //Align 정밀도 Y

	int	   m_nAlignRetryCount;    //Algin Retry 회수
	int	   m_nAlignCurrentCount;  //Align Retry 현재 횟수 (저장되지않는값)

	double m_fSmartZMatch;		  //Smart Z Match (Limit) Safety Lock 

	double m_fSmartZPosition;    //(저장되지않는값)
	//

	int		m_nBodyRecipeItemCnt;
	TCHAR*	RECIPE_MOTION_BODY_NAME[DEF_RECIPE_MOTION_BODY_COUNT];
	TCHAR*	RECIPE_MOTION_BODY_UNIT_NAME[DEF_RECIPE_MOTION_BODY_COUNT];
	TCHAR*	RECIPE_MOTION_BODY_EXPLANATION[DEF_RECIPE_MOTION_BODY_COUNT];

	DEF_RECIPE_MOTION_BODY(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fMaxLimit						= 10.0;
		m_fMinLimit						= -10.0;

		m_fCondinate_Offset_X			= 0.0;
		m_fCondinate_Offset_Y			= 0.0;

		m_fAlignAccuracy_X				= 0.0;
		m_fAlignAccuracy_Y				= 0.0;

		m_fSmartZMatch					= 0.0;

		m_nAlignRetryCount				= 0;
		m_nAlignCurrentCount			= 0;

		m_fSmartZPosition				= 0.0;
		//

		m_nBodyRecipeItemCnt			=	DEF_RECIPE_MOTION_BODY_COUNT;


		RECIPE_MOTION_BODY_NAME[0]					= _T("ALL OFFSET X");
		RECIPE_MOTION_BODY_UNIT_NAME[0]				= _T("mm");
		RECIPE_MOTION_BODY_EXPLANATION[0]			= _T("X축 방향으로 전체 이동(mm) 설정합니다.");


		RECIPE_MOTION_BODY_NAME[1]					= _T("PCB OFFSET Y");
		RECIPE_MOTION_BODY_UNIT_NAME[1]				= _T("mm");
		RECIPE_MOTION_BODY_EXPLANATION[1]			= _T("Y축 방향으로 전체 이동(mm) 설정합니다.");

		RECIPE_MOTION_BODY_NAME[2]					= _T("ALIGN ACCURACY X");
		RECIPE_MOTION_BODY_UNIT_NAME[2]				= _T("mm");
		RECIPE_MOTION_BODY_EXPLANATION[2]			= _T("ALING X축 정밀도(mm)를 설정합니다.");

		RECIPE_MOTION_BODY_NAME[3]					= _T("ALIGN ACCURACY Y");
		RECIPE_MOTION_BODY_UNIT_NAME[3]				= _T("mm");
		RECIPE_MOTION_BODY_EXPLANATION[3]			= _T("ALING Y축 정밀도(mm)를 설정합니다.");

		RECIPE_MOTION_BODY_NAME[4]					= _T("ALIGN RETRAY COUNT");
		RECIPE_MOTION_BODY_UNIT_NAME[4]				= _T("Cnt");
		RECIPE_MOTION_BODY_EXPLANATION[4]			= _T("ALING 재시도 횟수를 설정합니다.");

		RECIPE_MOTION_BODY_NAME[5]					= _T("SMART Z(TATGET) LIMIT");
		RECIPE_MOTION_BODY_UNIT_NAME[5]				= _T("mm");
		RECIPE_MOTION_BODY_EXPLANATION[5]			= _T("자동 높이 보정 값에 설정된 값을 벗어나지 못하도록 제한을 걸어둡니다.");
	}

}RECIPE_MOTION_BODY;

//////////////////////////////////////////////////////////////////////////

//Recipe Option
typedef struct DEF_RECIPE_MOTION_OPTION
{

#define DEF_RECIPE_MOTION_OPTION_COUNT 1

	double	m_fMinLimit;
	double	m_fMaxLimit;

	int		m_nOptionRecipeItemCnt;

	BOOL	m_bLaserUse;

	TCHAR*	RECIPE_MOTION_OPTION_NAME[DEF_RECIPE_MOTION_OPTION_COUNT];
	TCHAR*	RECIPE_MOTION_OPTION_UNIT_NAME[DEF_RECIPE_MOTION_OPTION_COUNT];
	TCHAR*	RECIPE_MOTION_OPTION_EXPLANATION[DEF_RECIPE_MOTION_OPTION_COUNT];

	//
	BOOL	m_bRunstatusClear;

	DEF_RECIPE_MOTION_OPTION(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fMinLimit									=	-5.0;
		m_fMaxLimit									=	 5.0;

		m_nOptionRecipeItemCnt						=	DEF_RECIPE_MOTION_OPTION_COUNT;

		m_bLaserUse									=   TRUE;

		RECIPE_MOTION_OPTION_NAME[0]				= _T("LASER USE");
		RECIPE_MOTION_OPTION_UNIT_NAME[0]			= _T("NOT USE/USE");
		RECIPE_MOTION_OPTION_EXPLANATION[0]			= _T("MANUAL 동작 또는 AUTO RUN 동작 중에 LASER 사용여부를 설정합니다.");

		//
		m_bRunstatusClear					= 0;
	}

}RECIPE_MOTION_OPTION;
//

//////////////////////////////////////////////////////////////////////////
//ILLUMINATION

typedef struct DEF_RECIPE_ILLUMINATION_BODY
{

#define DEF_RECIPE_ILLUMINATION_BODY_COUNT 1

	long m_lCoaxisCamLigntValue_Basic;

	int    m_nIlluminationItemCnt;
	TCHAR* ILLUMINATION_ITEM_NAME[DEF_RECIPE_ILLUMINATION_BODY_COUNT];
	TCHAR* ILLUMINATION_ITEM_UNIT[DEF_RECIPE_ILLUMINATION_BODY_COUNT];
	TCHAR* ILLUMINATION_ITEM_EXPLANATION[DEF_RECIPE_ILLUMINATION_BODY_COUNT];

	DEF_RECIPE_ILLUMINATION_BODY(void)
	{
		Clear();
	}

	void Clear()
	{
		m_lCoaxisCamLigntValue_Basic		= 0;

		//

		m_nIlluminationItemCnt				= DEF_RECIPE_ILLUMINATION_BODY_COUNT;

		ILLUMINATION_ITEM_NAME[0]			= _T("Coaxis Cam Light(Nomal)");

		ILLUMINATION_ITEM_UNIT[0]			= _T("brightness");

		ILLUMINATION_ITEM_EXPLANATION[0]	= _T("Coaxis Cam(Nomal) 조명의 밝기를 설정합니다.");

	}

}RECIPE_ILLUMINATION_BODY;



//////////////////////////////////////////////////////////////////////////
//VIsion
typedef struct DEF_RECIPE_VISION_BODY
{

#define DEF_RECIPE_VISION_BODY_COUNT 2

	double m_fVisionCal_X;
	double m_fVisionCal_Y;

	int    m_nVisionItemCnt;

	TCHAR* VISION_ITEM_NAME[DEF_RECIPE_VISION_BODY_COUNT];
	TCHAR* VISION_ITEM_UNIT[DEF_RECIPE_VISION_BODY_COUNT];
	TCHAR* VISION_ITEM_EXPLANATION[DEF_RECIPE_VISION_BODY_COUNT];

	DEF_RECIPE_VISION_BODY(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fVisionCal_X				= 0.0;
		m_fVisionCal_Y				= 0.0;

		m_nVisionItemCnt			= DEF_RECIPE_VISION_BODY_COUNT;

		VISION_ITEM_NAME[0]			= _T("Vision Calibration X");
		VISION_ITEM_NAME[1]			= _T("Vision Calibration Y");

		VISION_ITEM_UNIT[0]			= _T("Pixel");
		VISION_ITEM_UNIT[1]			= _T("Pixel");

		VISION_ITEM_EXPLANATION[0]	= _T("Coaxis Cam Calibration X 방향을 설정합니다.");
		VISION_ITEM_EXPLANATION[1]	= _T("Coaxis Cam Calibration Y 방향을 설정합니다.");
	}

}RECIPE_VISION_BODY;

//VIsion etc
typedef struct DEF_RECIPE_VISION_ETC
{

	double m_fMatchScoreAlign;
	double m_fMatchAngleAlign;


	DEF_RECIPE_VISION_ETC(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fMatchScoreAlign = 0.0;
		m_fMatchAngleAlign = 0.0;
	}

}RECIPE_VISION_ETC;

//////////////////////////////////////////////////////////////////////////

class CRecipeManager
{
public:
	CRecipePathManager RecipePath;

public:
	CRecipeManager(void);
	~CRecipeManager(void);

	void Save();
	void Open();

	void SaveLogPath();
	void OpenLogPath();

	//
	CString GetRecipepath();

	//
	BOOL GetSheetTextCompare(CFpspread8* a_pSpread, int a_Col, int a_Row, TCHAR* a_szText);

	//Motion Body
	void OpenMotionBodyValue();
	void SaveMotionBodyValue();
	void InitRecipeMotionBody_Save(CFpspread8* a_pSpread);
	void InitRecipeMotionBody_Open(CFpspread8* a_pSpread, UINT a_Select);

	//Motion Option
	void OpenMotionOptionValue();
	void SaveMotionOptionValue();
	void InitRecipeMotionOption_Save(CFpspread8* a_pSpread);
	void InitRecipeMotionOption_Open(CFpspread8* a_pSpread, UINT a_Select);

	//////////////////////////////////////////////////////////////////////////

	//Illumination
	void OpenIlluminationBodyValue();
	void SaveIlluminationBodyValue();
	void InitRecipeIlluminationBody_Save(CFpspread8* a_pSpread);
	void InitRecipeIlluminationBody_Open(CFpspread8* a_pSpread, UINT a_Select);

	//Vision
	void OpenVisionBodyValue();
	void SaveVisionBodyValue();
	void InitRecipeVisionBody_Save(CFpspread8* a_pSpread);
	void InitRecipeVisionBody_Open(CFpspread8* a_pSpread, UINT a_Select);


public:
	RECIPE_PATH					m_StRecipePath;
	RECIPE_PATH_DISP			m_strRecipePathDisp;

	RECIPE_MOTION_BODY			m_stRecipeMotionBody;
	RECIPE_MOTION_OPTION		m_stRecipeMotionOption;

	//
	RECIPE_ILLUMINATION_BODY	m_stRecipeIllminationBody;
	RECIPE_VISION_BODY			m_stRecipeVisionBody;

	//
	RECIPE_VISION_ETC			m_stRecipeVisionEtc;
};


#endif

extern CRecipeManager* RecipeMgr;

