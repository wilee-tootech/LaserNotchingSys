#include "stdafx.h"
#include "SetupManager.h"

#include "../EXTERN/FileMgr.h"

#include "../MOTION/AjinMotionDefine.h"

#include <fstream>
#include <sstream>

CSetupManager* SetupMgr = NULL;
#pragma warning(disable  : 4996)


template<typename T> T __stdcall GetIniValue(const TCHAR* Section, const TCHAR* Setting, T Default, const TCHAR* iniFileName)
{		
	T v = Default;
	TCHAR buffer[1024] = {0, };
#ifdef _UNICODE
	std::wstringstream sstr;
#else 
	std::stringstream sstr;	
#endif
	sstr << Default;
	buffer[0] = 0;
	if (0 < GetPrivateProfileStringW(Section, Setting, sstr.str().c_str(), buffer, sizeof(buffer), iniFileName)){				
#ifdef _UNICODE
		std::wstringstream sstr(buffer);
#else 
		std::stringstream sstr(buffer);
#endif
		sstr >> v;
		return v;
	}
	return Default;		
}	
template<typename T> void __stdcall SetIniValue(const TCHAR* Section, const TCHAR* Setting, T value, const TCHAR* iniFileName)
{
#ifdef _UNICODE
	std::wstringstream sstr;
#else 
	sstd::stringstream sstr;
#endif
	sstr << value;		
	WritePrivateProfileStringW(Section, Setting, sstr.str().c_str(), iniFileName);
}

CSetupManager::CSetupManager(void)
{
	ReadLaserParam(_T("LOSYNLASER"), _T("LosynLaserParam.ini"));
}


CSetupManager::~CSetupManager(void)
{
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CommSetting CSetupManager::ReadCommSet(CString a_strSection, CString a_strFileName)
{
	CFileMgr* FileMgr = new CFileMgr;

	CommSetting a_CommSetting;

	CString strPath = FileMgr->GetNowExePath();

	strPath += SETUP_DIRECTORY_NAME;

	strPath += a_strFileName;

	a_CommSetting.nPortNum	=  _ttoi(FileMgr->ReadString(a_strSection, _T("_PortNumber"), strPath));
	a_CommSetting.nBaudRate =  _ttoi(FileMgr->ReadString(a_strSection, _T("_BaudRate"), strPath));
	a_CommSetting.nDataBit	=  _ttoi(FileMgr->ReadString(a_strSection, _T("_DataBit"), strPath));
	a_CommSetting.nStopBit	=  _ttoi(FileMgr->ReadString(a_strSection, _T("_StopBit"), strPath));
	a_CommSetting.nParity	=  _ttoi(FileMgr->ReadString(a_strSection, _T("_Parity"), strPath));

	delete FileMgr;

	return a_CommSetting;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CSetupManager::ReadLaserParam(CString a_strSection, CString a_strFileName)
{
	CFileMgr* FileMgr = new CFileMgr;

	CommSetting a_CommSetting;

	CString strPath = FileMgr->GetNowExePath();

	strPath += SETUP_DIRECTORY_NAME;

	strPath += a_strFileName;

	m_stRecipeLaserParam.m_strDeviceName	=  FileMgr->ReadString(a_strSection, _T("_DeviceName"), strPath);
	m_stRecipeLaserParam.m_nDeviceID		=  _ttoi(FileMgr->ReadString(a_strSection, _T("_DeviceID")	, strPath));
	m_stRecipeLaserParam.m_fMinCurrent		=  _ttof(FileMgr->ReadString(a_strSection, _T("_MinCurrent"), strPath));
	m_stRecipeLaserParam.m_fMaxCurrent		=  _ttof(FileMgr->ReadString(a_strSection, _T("_MaxCurrent"), strPath));
	m_stRecipeLaserParam.m_fMaxPower		=  _ttof(FileMgr->ReadString(a_strSection, _T("_MaxPower")	, strPath));

	delete FileMgr;
}

//////////////////////////////////////////////////////////////////////////


BOOL CSetupManager::GetSheetTextCompare(CFpspread8* a_pSpread, int a_Col, int a_Row, CString a_StrCompare)
{
	VARIANT var;
	BSTR	bstr= NULL;
	CString strData;

	a_pSpread->GetText(a_Col,a_Row,&var);
	V_VT(&var) = VT_BSTR;
	strData.Format(_T("%s"),(LPCTSTR)(bstr_t)var.bstrVal);

	SysFreeString(bstr);
	VariantClear(&var);

	if(strData.Compare(a_StrCompare) == 0)
		return TRUE;

	return FALSE;
}

CString CSetupManager::GetRecipepath()
{
	CFileMgr* FileMgr = new CFileMgr;

	//현재 실행 중인 폴더의 경로를 가져온다.
	CString strPath = FileMgr->GetNowExePath();

	strPath += SETUP_DIRECTORY_NAME;

	delete FileMgr;

	return strPath;
}

//////////////////////////////////////////////////////////////////////////

//Setup Motion Position

void CSetupManager::OpenPosition_Body_Select(BOOL a_bDisp, CFpspread8* a_pSpread, UINT a_Select)
{
	CFileMgr* FileMgr = new CFileMgr;
	//현재 실행 중인 폴더의 경로를 가져온다.
	CString strPath;
	strPath.Format(_T("%s\\00_Position.ini"), SetupMgr->RecipePath.GetRecipeFilePath());

	//파일 유무 확인
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//파일이 없을 경우 파일 생성.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection(TEXT(""));

	strSection = _T("Setup Motion Body Axis");

	enum
	{
		DISP_SETUP_MOTION_BODY_AXIS_X								=  0,
		DISP_SETUP_MOTION_BODY_AXIS_Y								=  1,
		DISP_SETUP_MOTION_BODY_AXIS_Z								=  2,
	};

	int nCount = 0;

	switch (a_Select)
	{

	case DISP_SETUP_MOTION_BODY_AXIS_X:
		m_stSetupAxisDisp_X.m_fBodySafetyPos_X		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nCount++], strPath);
		m_stSetupAxisDisp_X.m_fBodyWorkPos_X		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nCount++], strPath);
		break;

	case DISP_SETUP_MOTION_BODY_AXIS_Y:
		m_stSetupAxisDisp_Y.m_fBodySafetyPos_Y		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nCount++], strPath);
		m_stSetupAxisDisp_Y.m_fBodyWorkPos_Y		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nCount++], strPath);
		break;

	case DISP_SETUP_MOTION_BODY_AXIS_Z:
		m_stSetupAxisDisp_Z.m_fBodySafetyPos_Z		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nCount++], strPath);
		m_stSetupAxisDisp_Z.m_fBodyWorkPos_Z		= FileMgr->ReadDouble(strSection, m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nCount++], strPath);
		break;

	default:
		break;
	} 

	if(FileMgr)
	{
		delete FileMgr;
		FileMgr = NULL;
	}

	if(a_bDisp)
		OpenPosition_Body_Disp_Select(a_pSpread, a_Select);
}

void CSetupManager::SavePosition_Body(void)
{
	CFileMgr* FileMgr = new CFileMgr;
	//현재 실행 중인 폴더의 경로를 가져온다.
	CString strPath;
	strPath.Format(_T("%s\\00_Position.ini"), SetupMgr->RecipePath.GetRecipeFilePath());

	//파일 유무 확인
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//파일이 없을 경우 파일 생성.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection(TEXT(""));

	strSection = _T("Setup Motion Body Axis");

	int nCount = 0;

	//X
	nCount = 0;

	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_X.m_fBodySafetyPos_X					, m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nCount++], strPath);
	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_X.m_fBodyWorkPos_X					, m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nCount++], strPath);

	//Y
	nCount = 0;

	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_Y.m_fBodySafetyPos_Y					, m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nCount++], strPath);
	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_Y.m_fBodyWorkPos_Y					, m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nCount++], strPath);

	//Z
	nCount = 0;

	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_Z.m_fBodySafetyPos_Z					, m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nCount++], strPath);
	FileMgr->WriteDouble	(strSection,m_stSetupAxisDisp_Z.m_fBodyWorkPos_Z					, m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nCount++], strPath);

	if(FileMgr)
	{
		delete FileMgr;
		FileMgr = NULL;
	}
}

//Disp
void CSetupManager::OpenPosition_Body_Disp_Select(CFpspread8* a_pSpread, UINT a_Select)
{
	if(!a_pSpread) return;

	int nCount = 0;
	int nItem  = 0;

	VARIANT var;
	BSTR	bStr = NULL;
	CString	strValue;

	V_VT(&var) = VT_BSTR;

	a_pSpread->SetCol(SETUP_SPREAD_ITEM); a_pSpread->SetRow(3); a_pSpread->SetForeColor(clRed);
	//}}
	//

	enum
	{
		DISP_SETUP_MOTION_BODY_AXIS_X								=  0,
		DISP_SETUP_MOTION_BODY_AXIS_Y								=  1,
		DISP_SETUP_MOTION_BODY_AXIS_Z								=  2,
	};

	switch (a_Select)
	{

	case DISP_SETUP_MOTION_BODY_AXIS_X	:
		nCount = 3;
		strValue = _T(" ACTUAL X POS");											bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_X.SETUP_BODY_DISP_X_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);

		nItem  = 0;																								 					 
		nCount = 3;																								 					 
		strValue = _T("mm");													bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = _T("mm");													bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);

		strValue = m_stSetupAxisDisp_X.SETUP_BODY_DISP_UNIT_X_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = m_stSetupAxisDisp_X.SETUP_BODY_DISP_UNIT_X_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);

		nCount = 4;
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_X.m_fBodySafetyPos_X);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_X.m_fBodyWorkPos_X);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);

		break;

	case DISP_SETUP_MOTION_BODY_AXIS_Y	:
		nCount = 3;
		strValue = _T(" ACTUAL Y POS");											bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_Y.SETUP_BODY_DISP_Y_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);

		nItem  = 0;																								 					 
		nCount = 3;																								 					 
		strValue = _T("mm");													bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = _T("mm");													bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);

		strValue = m_stSetupAxisDisp_Y.SETUP_BODY_DISP_UNIT_Y_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = m_stSetupAxisDisp_Y.SETUP_BODY_DISP_UNIT_Y_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);

		nCount = 4;
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_Y.m_fBodySafetyPos_Y);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_Y.m_fBodyWorkPos_Y);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);

		break;

	case DISP_SETUP_MOTION_BODY_AXIS_Z	:
		nCount = 3;
		strValue = _T(" ACTUAL Z POS");											bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);
		strValue = m_stSetupAxisDisp_Z.SETUP_BODY_DISP_Z_NAME[nItem++];			bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_ITEM,nCount++,var);

		nItem  = 0;																								 					 
		nCount = 3;																								 					 
		strValue = _T("mm");													bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = m_stSetupAxisDisp_Z.SETUP_BODY_DISP_UNIT_Z_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);
		strValue = m_stSetupAxisDisp_Z.SETUP_BODY_DISP_UNIT_Z_NAME[nItem++];	bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_UNIT,nCount++,var);SysFreeString(bStr);

		nCount = 4;
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_Z.m_fBodySafetyPos_Z);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);
		strValue.Format(_T("%.3f"),m_stSetupAxisDisp_Z.m_fBodyWorkPos_Z);		bStr = strValue.AllocSysString(); V_BSTR(&var) = bStr; a_pSpread->SetText(SETUP_SPREAD_VALUE, nCount++,var);

		break;

	default:
		break;
	}

	SysFreeString(bStr);
	VariantClear(&var);	
}