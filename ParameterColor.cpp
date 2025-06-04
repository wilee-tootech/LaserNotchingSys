// ParameterColor.cpp: implementation of the CParameterColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "ParameterColor.h"
#include "InitialTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParameterColor::CParameterColor()
{   // 기본 설정 값 
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	COLORREF *crPara = pInitialTable->GetParaCol();
	m_crParameterColor[0] = crPara[0];//RGB(255,0,0);
	m_crParameterColor[1] = crPara[1];//RGB(0,255,0);
	m_crParameterColor[2] = crPara[2];//RGB(0,0,255);
	m_crParameterColor[3] = crPara[3];//RGB(0,255,255);
	m_crParameterColor[4] = crPara[4];//RGB(255,255,0);
	m_crParameterColor[5] = crPara[5];//RGB(255,0,255);
	m_crParameterColor[6] = crPara[6];//RGB(0,0,0);
	m_crParameterColor[7] = crPara[7];//RGB(255,0,0);
	m_crParameterColor[8] = crPara[8];//RGB(255,0,0);
	m_crParameterColor[9] = crPara[9];//RGB(255,0,0);
	m_crParameterColor[10] = crPara[10];//RGB(255,0,0);
	m_crParameterColor[11] = crPara[11];//RGB(255,0,0);
	m_crParameterColor[12] = crPara[12];//RGB(255,0,0);
	m_crParameterColor[13] = crPara[13];//RGB(255,0,0);
	m_crParameterColor[14] = crPara[14];//RGB(255,0,0);
	m_crParameterColor[15] = crPara[15];//RGB(255,0,0);
	m_crParameterColor[16] = crPara[16];//RGB(255,0,0);
	m_crParameterColor[17] = crPara[17];//RGB(255,0,0);
	m_crParameterColor[18] = crPara[18];//RGB(255,0,0);
	m_crParameterColor[19] = crPara[19];//RGB(255,0,0);
	m_crParameterColor[20] = crPara[20];//RGB(255,0,0);
	
}


CParameterColor::~CParameterColor()
{

}

void CParameterColor::SetParaCol(DWORD dwIndex, COLORREF col)
{
	ASSERT( dwIndex < MAX_PARAMETER );
	m_crParameterColor[dwIndex] = col;
}

COLORREF CParameterColor::GetParaCol(DWORD dwIndex)
{
	ASSERT( dwIndex < MAX_PARAMETER );
	return m_crParameterColor[dwIndex];
}

CParameterColor &CParameterColor::Instance() 
{ // 유일한 객체 반환 
	static CParameterColor pcParaCol;
	return pcParaCol;
}

