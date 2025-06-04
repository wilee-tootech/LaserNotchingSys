// FilePath.cpp: implementation of the CFilePath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "FilePath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFilePath* CFilePath::m_pFilePath = 0;
CFilePath* CFilePath::GetInstance()
{
	if (m_pFilePath == 0) {
		m_pFilePath = new CFilePath;
	}
	return m_pFilePath;
}

CFilePath::CFilePath()
{
	m_strScribe = _T("");
	m_strDevice = _T("");
	m_strMark = _T("");
}

CFilePath::~CFilePath()
{

}

void CFilePath::SetScribeFilePath(CString strScribe)
{
	m_strScribe = strScribe;
}

CString CFilePath::GetScribeFilePath()
{
	return m_strScribe;
}

void CFilePath::SetDeviceFilePath(CString strDevice)
{
	m_strDevice = strDevice;
}

CString CFilePath::GetDeviceFilePath()
{
	return m_strDevice;
}

void CFilePath::SetMarkFilePath(CString strMark)
{
	m_strMark = strMark;
}

CString CFilePath::GetMarkFilePath()
{
	return m_strMark;
}
