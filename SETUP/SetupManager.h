#ifndef _SETUP_MANAGER_H_
#define _SETUP_MANAGER_H_

#pragma once

#include "../NX_KEYPAD/NX_KEYPAD/AlphaKeyPad.h"
#include "../NX_RECIPE_PATH/RecipePathManager.h"

#include "NX_COMM/CommDefine.h"

#include "SetupDefine.h"

#include "../Include/EXTERN/fpspread8.h"

#define SETUP_DIRECTORY_NAME			"\\Config\\"

enum 
{
	SETUP_SPREAD_NO		= 1	,
	SETUP_SPREAD_ITEM		,
	SETUP_SPREAD_UNIT		,
	SETUP_SPREAD_VALUE		,
	SETUP_SPREAD_UPLOAD		,
};

typedef struct DEF_RECIPE_LASER_PARAM
{
	CString m_strDeviceName;
	int		m_nDeviceID;
	double	m_fMinCurrent;
	double	m_fMaxCurrent;
	double	m_fMaxPower;

	DEF_RECIPE_LASER_PARAM(void)
	{
		Clear();
	}

	void Clear()
	{
		m_strDeviceName	= _T("");
		m_nDeviceID		= 0;
		m_fMinCurrent	= 0.0;
		m_fMaxCurrent	= 0.0;
		m_fMaxPower		= 0.0;
	}

}RECIPE_LASER_PARAM;

//{{

//Motion
//Axis X
typedef struct DEF_SETUP_AXIS_X_DISP
{
#define  DEF_SETUP_VARIABLE_CNT_AXIS_X	2

	double	m_fLimitMin;
	double	m_fLimitMax;

	double	m_fBodySafetyPos_X;
	double  m_fBodyWorkPos_X;

	int		m_nBodyItemCnt_X;
	TCHAR* SETUP_BODY_DISP_X_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_X];
	TCHAR* SETUP_BODY_DISP_UNIT_X_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_X];

	DEF_SETUP_AXIS_X_DISP(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fLimitMin			=	0.0;
		m_fLimitMax			=	1000.0;

		m_fBodySafetyPos_X	=	0.0;
		m_fBodyWorkPos_X	=	0.0;

		m_nBodyItemCnt_X	=	DEF_SETUP_VARIABLE_CNT_AXIS_X;

		SETUP_BODY_DISP_X_NAME[0] = _T("BODY SAFETY X POS");
		SETUP_BODY_DISP_X_NAME[1] = _T("BODY WORK X POS");

		SETUP_BODY_DISP_UNIT_X_NAME[0]	= _T("mm");
		SETUP_BODY_DISP_UNIT_X_NAME[1]	= _T("mm");
	}

}SETUP_AXIS_X_DISP;

//Axis Y
typedef struct DEF_SETUP_AXIS_Y_DISP
{
#define  DEF_SETUP_VARIABLE_CNT_AXIS_Y	2

	double	m_fLimitMin;
	double	m_fLimitMax;

	double	m_fBodySafetyPos_Y;
	double  m_fBodyWorkPos_Y;

	int		m_nBodyItemCnt_Y;
	TCHAR* SETUP_BODY_DISP_Y_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_Y];
	TCHAR* SETUP_BODY_DISP_UNIT_Y_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_Y];

	DEF_SETUP_AXIS_Y_DISP(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fLimitMin			=	0.0;
		m_fLimitMax			=	1000.0;

		m_fBodySafetyPos_Y	=	0.0;
		m_fBodyWorkPos_Y	=	0.0;

		m_nBodyItemCnt_Y	=	DEF_SETUP_VARIABLE_CNT_AXIS_Y;

		SETUP_BODY_DISP_Y_NAME[0] = _T("BODY SAFETY Y POS");
		SETUP_BODY_DISP_Y_NAME[1] = _T("BODY WORK Y POS");

		SETUP_BODY_DISP_UNIT_Y_NAME[0]	= _T("mm");
		SETUP_BODY_DISP_UNIT_Y_NAME[1]	= _T("mm");
	}

}SETUP_AXIS_Y_DISP;

//Axis Z
typedef struct DEF_SETUP_AXIS_Z_DISP
{
#define  DEF_SETUP_VARIABLE_CNT_AXIS_Z	2

	double	m_fLimitMin;
	double	m_fLimitMax;

	double	m_fBodySafetyPos_Z;
	double  m_fBodyWorkPos_Z;

	int		m_nBodyItemCnt_Z;

	TCHAR* SETUP_BODY_DISP_Z_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_Z];
	TCHAR* SETUP_BODY_DISP_UNIT_Z_NAME[DEF_SETUP_VARIABLE_CNT_AXIS_Z];

	DEF_SETUP_AXIS_Z_DISP(void)
	{
		Clear();
	}

	void Clear()
	{
		m_fLimitMin				=	0.0;
		m_fLimitMax				=	1000.0;

		m_fBodySafetyPos_Z		=	0.0;
		m_fBodyWorkPos_Z		=	0.0;

		m_nBodyItemCnt_Z		=	DEF_SETUP_VARIABLE_CNT_AXIS_Z;

		SETUP_BODY_DISP_Z_NAME[0] = _T("BODY SAFETY Z POS");
		SETUP_BODY_DISP_Z_NAME[1] = _T("BODY WORK Z POS");

		SETUP_BODY_DISP_UNIT_Z_NAME[0]	= _T("mm");
		SETUP_BODY_DISP_UNIT_Z_NAME[1]	= _T("mm");
	}

}SETUP_AXIS_Z_DISP;


class CSetupManager
{
public:
	CSetupManager(void);
	~CSetupManager(void);

	//Comm Setting
	CommSetting ReadCommSet(CString a_strSection, CString a_strFileName);
	void ReadLaserParam(CString a_strSection, CString a_strFileName);

	//
	CString GetRecipepath();

public:
	CRecipePathManager			RecipePath;
	RECIPE_LASER_PARAM			m_stRecipeLaserParam;
	//
	SETUP_AXIS_X_DISP			m_stSetupAxisDisp_X;
	SETUP_AXIS_Y_DISP			m_stSetupAxisDisp_Y;
	SETUP_AXIS_Z_DISP			m_stSetupAxisDisp_Z;

public:
	BOOL GetSheetTextCompare(CFpspread8* a_pSpread, int a_Col, int a_Row, CString a_StrCompare);

	//
	void OpenPosition_Body_Select(BOOL a_Disp, CFpspread8* a_pSpread, UINT a_Select);

	//
	void SavePosition_Body(void);

private:
	
	//Disp
	void OpenPosition_Body_Disp_Select(CFpspread8* a_pSpread, UINT a_Select);

};

#endif

extern CSetupManager* SetupMgr;