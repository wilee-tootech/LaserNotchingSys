// Communicate.cpp: implementation of the CCommunicate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Communicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommunicate::CCommunicate()
{
	m_bIsConnect = FALSE;
}

CCommunicate::~CCommunicate()
{

}

BOOL CCommunicate::GetIsConnect()
{
	return m_bIsConnect;
}

void CCommunicate::SetIsConnect(BOOL bIsConnect)
{
	m_bIsConnect = bIsConnect;
}

