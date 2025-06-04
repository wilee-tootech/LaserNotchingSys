// PointerContainer.cpp: implementation of the CPointerContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PointerContainer.h"

#include "MKObjectApproacher.h"
#include "MKFile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMKObjectApproacher   *CPointerContainer::m_pApproacher=0;
CMKFile   *CPointerContainer::m_pFile=0;

CommandManager   *CPointerContainer::m_pCmdMng=0;

CBeamEditor6View *CPointerContainer::m_pView=0;

//CPatternEditVeiw *CPointerContainer::m_pMainFormView=0;

CMainFormView *CPointerContainer::m_pMainFormView=0;



CGraphView *CPointerContainer::m_pGraphView=0;

CInformationView *CPointerContainer::m_pInfoView=0;






CPointerContainer::CPointerContainer()
{
}

CPointerContainer::~CPointerContainer()
{

}




CMKObjectApproacher *CPointerContainer::GetApproacher()
{
	return m_pApproacher;
}
void CPointerContainer::SetApproacher(CMKObjectApproacher *pApproacher)
{
	ASSERT ( FALSE == IsBadReadPtr( pApproacher, sizeof(CMKObjectApproacher) ) );
	
	m_pApproacher = pApproacher;

}
	
CMKFile *CPointerContainer::GetMKFile()
{
	return m_pFile;
}
void CPointerContainer::SetMKFile(CMKFile *pMKFile)
{
	ASSERT ( FALSE == IsBadReadPtr( pMKFile, sizeof(CMKFile) ) );

	m_pFile = pMKFile;

}



CBeamEditor6View *CPointerContainer::GetView()
{
	return m_pView;
}

void CPointerContainer::SetView(CBeamEditor6View *pView)
{

	m_pView = pView;
}

CInformationView *CPointerContainer::GetInformationView()
{
	return m_pInfoView;
}
void CPointerContainer::SetInformationView(CInformationView *pView)
{
	ASSERT(pView != NULL);

	m_pInfoView = pView;
}

CGraphView *CPointerContainer::GetGraphView()
{
	return m_pGraphView;
}
void CPointerContainer::SetGraphView(CGraphView *pView)
{
	ASSERT(pView != NULL);

	m_pGraphView = pView;
}


CMainFormView *CPointerContainer::GetCMainFormView()
{
	return m_pMainFormView;
}


void CPointerContainer::SetCMainFormView(CMainFormView *pView)
{
	ASSERT(pView != NULL);

	m_pMainFormView = pView;
}
