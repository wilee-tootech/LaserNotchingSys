// ParameterColor.h: interface for the CParameterColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERCOLOR_H__D199AD37_A2EE_44F4_B226_02BCD018E25E__INCLUDED_)
#define AFX_PARAMETERCOLOR_H__D199AD37_A2EE_44F4_B226_02BCD018E25E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"

class CParameterColor  
{
public:
	CParameterColor();
	virtual ~CParameterColor();
	COLORREF m_crParameterColor[MAX_PARAMETER];
	
	void SetParaCol(DWORD dwIndex, COLORREF col);
	COLORREF GetParaCol(DWORD dwIndex);
	static CParameterColor &Instance();

};

#endif // !defined(AFX_PARAMETERCOLOR_H__D199AD37_A2EE_44F4_B226_02BCD018E25E__INCLUDED_)
