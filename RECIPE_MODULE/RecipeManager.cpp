#include "stdafx.h"
#include "RecipeManager.h"

#include "RecipeDefine.h"

#include <fstream>
#include <sstream>

CRecipeManager* RecipeMgr = NULL;
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
	//if (0 < GetPrivateProfileStringW(Section, Setting, sstr.str().c_str(), buffer, sizeof(buffer), iniFileName)){				
	if (0 < GetPrivateProfileString(Section, Setting, sstr.str().c_str(), buffer, sizeof(buffer), iniFileName)){				
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
	std::stringstream sstr;
#endif
	sstr << value;		
	//WritePrivateProfileStringW(Section, Setting, sstr.str().c_str(), iniFileName);
	WritePrivateProfileString(Section, Setting, sstr.str().c_str(), iniFileName);
}


CRecipeManager::CRecipeManager(void)
{

}

CRecipeManager::~CRecipeManager(void)
{
}


void CRecipeManager::SaveLogPath()
{	
	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("LogPath.ini") );

	if( PathFileExists( szPath ) == FALSE  ){
		std::wofstream Stream( szPath, std::ios::ate | std::ios::app );
		Stream.close();
	}

	TCHAR* Section;

	Section = _T("Log Path");

	TCHAR buffer[1024] = {0, };

	WritePrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[0], m_StRecipePath.m_strEquimentPath				, szPath);
	WritePrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[1], m_StRecipePath.m_strSystemPath				, szPath);
	WritePrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[2], m_StRecipePath.m_strMESLogPath				, szPath);
}
void CRecipeManager::OpenLogPath()
{
	TCHAR szPath[MAX_PATH] = {0, };

	//_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("Recipe.ini"));
	_stprintf( szPath, _T("%s%s"), RecipePath.GetProjectPath(), _T("LogPath.ini"));
	

	TCHAR* Section;

	Section = _T("Log Path");

	TCHAR buffer[1024] = {0, };

	GetPrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[0]	,_T("C:\\"),	buffer, sizeof(buffer),	szPath);
	m_StRecipePath.m_strEquimentPath.	Format(_T("%s"),	buffer); 

	GetPrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[1]	,_T("C:\\"),	buffer, sizeof(buffer),	szPath);
	m_StRecipePath.m_strSystemPath.	Format(_T("%s"),	buffer); 

	GetPrivateProfileString( Section, m_strRecipePathDisp.RECIPE_PATH_DISP_NAME[2]	,_T("C:\\"),	buffer, sizeof(buffer),	szPath);
	m_StRecipePath.m_strMESLogPath.	Format(_T("%s"),	buffer); 

}

//////////////////////////////////////////////////////////////////////////


//{{
BOOL CRecipeManager::GetSheetTextCompare(CFpspread8* a_pSpread, int a_Col, int a_Row, TCHAR* a_szText)
{
	if(!a_szText) return FALSE;

	VARIANT var;
	BSTR	bstr= NULL;
	CString strData;

	a_pSpread->GetText(a_Col,a_Row,&var);
	V_VT(&var) = VT_BSTR;
	strData.Format(_T("%s"),(LPCTSTR)(bstr_t)var.bstrVal);

	SysFreeString(bstr);
	VariantClear(&var);

	if(strData.Compare(a_szText) == 0)
		return TRUE;

	return FALSE;
}

//}}


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CRecipeManager::OpenMotionBodyValue()
{


	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("\\02_Recipe.ini"));

	TCHAR* Section;

	Section = _T("Motion_Body");

	m_stRecipeMotionBody.m_fCondinate_Offset_X		= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[0], 0.0,		szPath);	
	m_stRecipeMotionBody.m_fCondinate_Offset_Y		= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[1], 0.0,		szPath);	

	m_stRecipeMotionBody.m_fAlignAccuracy_X			= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[2], 0.0,		szPath);	
	m_stRecipeMotionBody.m_fAlignAccuracy_Y			= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[3], 0.0,		szPath);

	m_stRecipeMotionBody.m_nAlignRetryCount			= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[4],  0,		szPath);

	m_stRecipeMotionBody.m_fSmartZMatch				= GetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[5], 0.0,		szPath);

}

void CRecipeManager::SaveMotionBodyValue()
{	
	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("\\02_Recipe.ini") );

	if( PathFileExists( szPath ) == FALSE  ){
		std::wofstream Stream( szPath, std::ios::ate | std::ios::app );
		Stream.close();
	}


	TCHAR* Section;

	Section = _T("Motion_Body");

	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[0], m_stRecipeMotionBody.m_fCondinate_Offset_X		,	 szPath);	
	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[1], m_stRecipeMotionBody.m_fCondinate_Offset_Y		,	 szPath);

	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[2], m_stRecipeMotionBody.m_fAlignAccuracy_X			,	 szPath);
	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[3], m_stRecipeMotionBody.m_fAlignAccuracy_Y			,	 szPath);

	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[4], m_stRecipeMotionBody.m_nAlignRetryCount			,	 szPath);

	SetIniValue( Section, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[5], m_stRecipeMotionBody.m_fSmartZMatch				,	 szPath);
}

void CRecipeManager::InitRecipeMotionBody_Save(CFpspread8* a_pSpread)
{
	if(!a_pSpread) return;

	VARIANT var;
	CString strValue;

	BOOL bCompare = FALSE;
	int n_MaxRow = a_pSpread->GetMaxRows() + 1;

	int nRowCont = 3;

	for(int i = 3 ; i < n_MaxRow; i++)
	{
		for( int nItem = 0; nItem < m_stRecipeMotionBody.m_nBodyRecipeItemCnt; nItem++ )
		{
			bCompare = GetSheetTextCompare(a_pSpread, 2, i, m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[nItem]);
			if(bCompare)
			{
				switch (nItem)
				{
				case 0:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_fCondinate_Offset_X = _tstof(strValue);
					break;

				case 1:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_fCondinate_Offset_Y	= _tstof(strValue);
					break;

				case 2:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_fAlignAccuracy_X	= _tstof(strValue);
					break;

				case 3:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_fAlignAccuracy_Y	= _tstof(strValue);
					break;

				case 4:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_nAlignRetryCount	= _tstoi(strValue);
					break;

				case 5:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeMotionBody.m_fSmartZMatch	= _tstof(strValue);
					break;
				}
			}
		}
	}

	VariantClear(&var);

	SaveMotionBodyValue();
}

void CRecipeManager::InitRecipeMotionBody_Open(CFpspread8* a_pSpread, UINT a_Select)
{
	if(!a_pSpread) return;

	OpenMotionBodyValue();

	int nCount = 0;
	int nItem  = 0;

	VARIANT var;
	BSTR	bStr = NULL;
	CString	strValue;

	V_VT(&var) = VT_BSTR;

	enum
	{
		DISP_RECIPE_BODY  = 0,
	};

	switch (a_Select)
	{
	case DISP_RECIPE_BODY:
		nCount = 3;
		for (int nItem = 0; nItem < m_stRecipeMotionBody.m_nBodyRecipeItemCnt; nItem++, nCount++)
		{
			strValue = m_stRecipeMotionBody.RECIPE_MOTION_BODY_NAME[nItem];			bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_ITEM,nCount,var);
			strValue = m_stRecipeMotionBody.RECIPE_MOTION_BODY_UNIT_NAME[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_UNIT,nCount,var);SysFreeString(bStr);


			switch (nItem)
			{
			case 0:
				strValue.Format(_T("%.3f"),m_stRecipeMotionBody.m_fCondinate_Offset_X		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 1:
				strValue.Format(_T("%.3f"),m_stRecipeMotionBody.m_fCondinate_Offset_Y		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 2:
				strValue.Format(_T("%.3f"),m_stRecipeMotionBody.m_fAlignAccuracy_X		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 3:
				strValue.Format(_T("%.3f"),m_stRecipeMotionBody.m_fAlignAccuracy_Y		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 4:
				strValue.Format(_T("%d"),m_stRecipeMotionBody.m_nAlignRetryCount		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 5:
				strValue.Format(_T("%.3f"),m_stRecipeMotionBody.m_fSmartZMatch			); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;
			}
		}
	}


}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CRecipeManager::OpenMotionOptionValue()
{


	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s%s"), RecipePath.GetRecipeFilePath(), _T("\\02_Recipe.ini"));

	TCHAR* Section;

	Section = _T("Motion_Option");

	m_stRecipeMotionOption.m_bLaserUse		= GetIniValue( Section, m_stRecipeMotionOption.RECIPE_MOTION_OPTION_NAME[0],		TRUE,		szPath);	

}

void CRecipeManager::SaveMotionOptionValue()
{	
	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s%s"), RecipePath.GetRecipeFilePath(), _T("\\02_Recipe.ini") );

	if( PathFileExists( szPath ) == FALSE  ){
		std::wofstream Stream( szPath, std::ios::ate | std::ios::app );
		Stream.close();
	}


	TCHAR* Section;

	Section = _T("Motion_Option");

	SetIniValue( Section, m_stRecipeMotionOption.RECIPE_MOTION_OPTION_NAME[0], m_stRecipeMotionOption.m_bLaserUse,						 szPath);	

}

//

void CRecipeManager::InitRecipeMotionOption_Save(CFpspread8* a_pSpread)
{
	if(!a_pSpread) return;

	VARIANT var;
	CString strValue;

	BOOL bCompare = FALSE;
	int n_MaxRow = a_pSpread->GetMaxRows() + 1;

	int nRowCont = 3;

	for(int i = 3 ; i < n_MaxRow; i++)
	{
		for( int nItem = 0; nItem < m_stRecipeMotionOption.m_nOptionRecipeItemCnt; nItem++ )
		{
			bCompare = GetSheetTextCompare(a_pSpread, 2, i, m_stRecipeMotionOption.RECIPE_MOTION_OPTION_NAME[nItem]);
			if(bCompare)
			{
				switch (nItem)
				{
				case 0:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 

					if(strValue.Compare(_T("USE")) == 0)
					{
						strValue = _T("1");
					}

					else
					{
						strValue = _T("0");
					}

					m_stRecipeMotionOption.m_bLaserUse	= _tstoi(strValue);
					break;

				}
			}
		}
	}

	VariantClear(&var);

	SaveMotionOptionValue();
}

void CRecipeManager::InitRecipeMotionOption_Open(CFpspread8* a_pSpread, UINT a_Select)
{
	if(!a_pSpread) return;

	OpenMotionOptionValue();

	int nCount = 0;
	int nItem  = 0;

	VARIANT var;
	BSTR	bStr = NULL;
	CString	strValue;

	V_VT(&var) = VT_BSTR;

	enum
	{
		DISP_RECIPE_OPTION  = 0,
	};

	switch (a_Select)
	{
	case DISP_RECIPE_OPTION:
		nCount = 3;
		for (int nItem = 0; nItem < m_stRecipeMotionOption.m_nOptionRecipeItemCnt; nItem++, nCount++)
		{
			strValue = m_stRecipeMotionOption.RECIPE_MOTION_OPTION_NAME[nItem];			bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_ITEM,nCount,var);
			strValue = m_stRecipeMotionOption.RECIPE_MOTION_OPTION_UNIT_NAME[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_UNIT,nCount,var);SysFreeString(bStr);


			switch (nItem)
			{
			case 0:
				strValue.Format(_T("%d"),m_stRecipeMotionOption.m_bLaserUse		); 

				if(strValue.Compare(_T("1")) == 0)
				{
					strValue = _T("USE");
				}

				else
				{
					strValue = _T("NOT_USE");
				}

				bStr = strValue.AllocSysString(); 

				V_BSTR(&var) = bStr; 

				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);

				a_pSpread->SetCol(RECIPE_SPREAD_VALUE);
				a_pSpread->SetRow(nCount);

				a_pSpread->SetTypeHAlign(2);
				a_pSpread->SetTypeVAlign(2);

				break;

			}
		}
	}


}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CRecipeManager::OpenIlluminationBodyValue()
{


	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s%s"), RecipePath.GetRecipeFilePath(), _T("\\03_Illumination.ini"));

	TCHAR* Section;

	Section = _T("ILLUMINATION_BODY");

	m_stRecipeIllminationBody.m_lCoaxisCamLigntValue_Basic			= GetIniValue( Section, m_stRecipeIllminationBody.ILLUMINATION_ITEM_NAME[0],		50,		szPath);		
}

void CRecipeManager::SaveIlluminationBodyValue()
{	
	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("\\03_Illumination.ini") );

	if( PathFileExists( szPath ) == FALSE  ){
		std::wofstream Stream( szPath, std::ios::ate | std::ios::app );
		Stream.close();
	}


	TCHAR* Section;

	Section = _T("ILLUMINATION_BODY");

	SetIniValue( Section, m_stRecipeIllminationBody.ILLUMINATION_ITEM_NAME[0], m_stRecipeIllminationBody.m_lCoaxisCamLigntValue_Basic,					 szPath);
}

void CRecipeManager::InitRecipeIlluminationBody_Save(CFpspread8* a_pSpread)
{
	if(!a_pSpread) return;

	VARIANT var;
	CString strValue;

	BOOL bCompare = FALSE;
	int n_MaxRow = a_pSpread->GetMaxRows() + 1;

	int nRowCont = 3;

	for(int i = 3 ; i < n_MaxRow; i++)
	{
		for( int nItem = 0; nItem < m_stRecipeIllminationBody.m_nIlluminationItemCnt; nItem++ )
		{
			bCompare = GetSheetTextCompare(a_pSpread, 2, i, m_stRecipeIllminationBody.ILLUMINATION_ITEM_NAME[nItem]);
			if(bCompare)
			{
				switch (nItem)
				{
				case 0:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeIllminationBody.m_lCoaxisCamLigntValue_Basic		= _tstoi(strValue);
					break;
				}
			}
		}
	}

	VariantClear(&var);

	SaveIlluminationBodyValue();
}

void CRecipeManager::InitRecipeIlluminationBody_Open(CFpspread8* a_pSpread, UINT a_Select)
{
	if(!a_pSpread) return;

	OpenIlluminationBodyValue();

	int nCount = 0;
	int nItem  = 0;

	VARIANT var;
	BSTR	bStr = NULL;
	CString	strValue;

	V_VT(&var) = VT_BSTR;

	enum
	{
		DISP_RECIPE_STAGE  = 0,
	};

	switch (a_Select)
	{
	case DISP_RECIPE_STAGE:
		nCount = 3;
		for (int nItem = 0; nItem < m_stRecipeIllminationBody.m_nIlluminationItemCnt; nItem++, nCount++)
		{
			strValue = m_stRecipeIllminationBody.ILLUMINATION_ITEM_NAME[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_ITEM,nCount,var);
			strValue = m_stRecipeIllminationBody.ILLUMINATION_ITEM_UNIT[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_UNIT,nCount,var);SysFreeString(bStr);


			switch (nItem)
			{
			case 0:
				strValue.Format(_T("%d"),m_stRecipeIllminationBody.m_lCoaxisCamLigntValue_Basic		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;
			}
		}
	}


}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CRecipeManager::OpenVisionBodyValue()
{


	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("\\04_Vision.ini"));

	TCHAR* Section;

	Section = _T("VISION_BODY");

	m_stRecipeVisionBody.m_fVisionCal_X					= GetIniValue( Section, m_stRecipeVisionBody.VISION_ITEM_NAME[0],		0.0,		szPath);	
	m_stRecipeVisionBody.m_fVisionCal_Y					= GetIniValue( Section, m_stRecipeVisionBody.VISION_ITEM_NAME[1],		0.0,		szPath);	
}

void CRecipeManager::SaveVisionBodyValue()
{	
	TCHAR szPath[MAX_PATH] = {0, };

	_stprintf( szPath, _T("%s\\%s"), RecipePath.GetRecipeFilePath(), _T("\\04_Vision.ini") );

	if( PathFileExists( szPath ) == FALSE  ){
		std::wofstream Stream( szPath, std::ios::ate | std::ios::app );
		Stream.close();
	}

	TCHAR* Section;

	Section = _T("VISION");

	SetIniValue( Section, m_stRecipeVisionBody.VISION_ITEM_NAME[0], m_stRecipeVisionBody.m_fVisionCal_X,					 szPath);	
	SetIniValue( Section, m_stRecipeVisionBody.VISION_ITEM_NAME[1], m_stRecipeVisionBody.m_fVisionCal_Y,					 szPath);
}

void CRecipeManager::InitRecipeVisionBody_Save(CFpspread8* a_pSpread)
{
	if(!a_pSpread) return;

	VARIANT var;
	CString strValue;

	BOOL bCompare = FALSE;
	int n_MaxRow = a_pSpread->GetMaxRows() + 1;

	int nRowCont = 3;

	for(int i = 3 ; i < n_MaxRow; i++)
	{
		for( int nItem = 0; nItem < m_stRecipeVisionBody.m_nVisionItemCnt; nItem++ )
		{
			bCompare = GetSheetTextCompare(a_pSpread, 2, i, m_stRecipeVisionBody.VISION_ITEM_NAME[nItem]);
			if(bCompare)
			{
				switch (nItem)
				{
				case 0:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeVisionBody.m_fVisionCal_X	= _tstof(strValue);
					break;

				case 1:
					a_pSpread->GetText(RECIPE_MERGE_COLS_CNT, nRowCont+nItem,&var); 
					strValue = (CString)var.bstrVal; 
					m_stRecipeVisionBody.m_fVisionCal_Y	= _tstof(strValue);
					break;
				}
			}
		}
	}

	VariantClear(&var);

	SaveVisionBodyValue();
}

void CRecipeManager::InitRecipeVisionBody_Open(CFpspread8* a_pSpread, UINT a_Select)
{
	if(!a_pSpread) return;

	OpenVisionBodyValue();

	int nCount = 0;
	int nItem  = 0;

	VARIANT var;
	BSTR	bStr = NULL;
	CString	strValue;

	V_VT(&var) = VT_BSTR;

	enum
	{
		DISP_RECIPE_STAGE  = 0,
	};

	switch (a_Select)
	{
	case DISP_RECIPE_STAGE:
		nCount = 3;
		for (int nItem = 0; nItem < m_stRecipeVisionBody.m_nVisionItemCnt; nItem++, nCount++)
		{
			strValue = m_stRecipeVisionBody.VISION_ITEM_NAME[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_ITEM,nCount,var);
			strValue = m_stRecipeVisionBody.VISION_ITEM_UNIT[nItem];	bStr = strValue.AllocSysString();	V_BSTR(&var) = bStr;	a_pSpread->SetText(RECIPE_SPREAD_UNIT,nCount,var);SysFreeString(bStr);


			switch (nItem)
			{
			case 0:
				strValue.Format(_T("%.5f"),m_stRecipeVisionBody.m_fVisionCal_X		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;

			case 1:
				strValue.Format(_T("%.5f"),m_stRecipeVisionBody.m_fVisionCal_Y		); 
				bStr = strValue.AllocSysString(); 
				V_BSTR(&var) = bStr; 
				a_pSpread->SetText(RECIPE_SPREAD_VALUE, nCount,var);
				break;
			}
		}
	}


}
//////////////////////////////////////////////////////////////////////////