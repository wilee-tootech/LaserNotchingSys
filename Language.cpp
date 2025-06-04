// Language.cpp: implementation of the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLanguage::CLanguage()
{
	m_iLanguage = -1;
}

CLanguage::~CLanguage()
{
}

CLanguage* CLanguage::m_pLanguage = 0;
CLanguage* CLanguage::GetInstance()
{
	if (m_pLanguage == 0) {
		m_pLanguage = new CLanguage;
	}
	return m_pLanguage;
}

void CLanguage::SetLanguage(int language)
{
	m_iLanguage = language;
}

int CLanguage::GetString(int BaseString)
{
 	if (m_iLanguage == -1)
		return -1;
	
	return BaseString+m_iLanguage;
}
