// Ctd.cpp: implementation of the CCtd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Ctd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtd::CCtd()
{
	m_pFile = NULL;
}

CCtd::~CCtd()
{
	if (m_pFile != NULL) {
		delete m_pFile;
		m_pFile = NULL;
	}
}

////////////////////////////////////////
// 화일 이름을 받아 CArchive 객체를 생성후 반환
BOOL CCtd::SaveCtd(CString fileName, CPoint (*point)[MAX_CAL_DATA])
{
	int i, j;
	CString fileType;
	CPoint fieldSize, mmSize;

	if(m_pFile != NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
	m_pFile = new CFile(fileName, CFile::modeCreate|CFile::modeWrite);

	if (m_pFile == NULL)
	{
		return FALSE;
	}

	// 아카이브 객체를 만든다
	CArchive Archive(m_pFile, CArchive::store);

	m_fileName = fileName;
	if (Archive.IsStoring())
	{
		// TODO: add storing code here
		fileType = "ctd 1.0"; // file version
		Archive << fileType;
		for(i=0;i<MAX_CAL_DATA;i++)
		{
			for(j=0;j<MAX_CAL_DATA;j++)
			{
				Archive << point[i][j];
			}
		}
		Archive.Close();
		m_pFile->Close();
		return TRUE;
	}
	Archive.Close();
	m_pFile->Close();
	return FALSE;
}

BOOL CCtd::SaveCtd(CString fileName, CPoint (*baseData)[MAX_CAL_DATA], CPoint (*point)[MAX_CAL_DATA])
{
	int i, j;
	CString fileType;
	CPoint fieldSize, mmSize, tempoint;

	if(m_pFile != NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
	m_pFile = new CFile(fileName, CFile::modeCreate|CFile::modeWrite);

	if (m_pFile == NULL)
	{
		return FALSE;
	}

	// 아카이브 객체를 만든다
	CArchive Archive(m_pFile, CArchive::store);

	m_fileName = fileName;
	if (Archive.IsStoring())
	{
		// TODO: add storing code here
		fileType = "ctd 1.0"; // file version
		Archive << fileType;
		for(i=0;i<MAX_CAL_DATA;i++)
		{
			for(j=0;j<MAX_CAL_DATA;j++)
			{
				tempoint = baseData[i][j] + point[i][j];
				Archive << tempoint;// point[i][j];
			}
		}
		Archive.Close();
		m_pFile->Close();
		return TRUE;
	}
	Archive.Close();
	m_pFile->Close();
	return FALSE;
}

BOOL CCtd::OpenCtd(CString fileName, CPoint (*point)[MAX_CAL_DATA])
{
	// TODO: add storing code here
	int i, j;
	CString fileType;

	if(m_pFile != NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
	m_pFile = new CFile(fileName, CFile::modeRead);

	if (m_pFile == NULL)
	{
		return FALSE;
	}

	// 아카이브 객체를 만든다
	CArchive Archive(m_pFile, CArchive::load);
	m_fileName = fileName;
	if (Archive.IsLoading())
	{
		Archive >> fileType;
		if (fileType.Left(3) != "ctd")
		{
			Archive.Close();
			m_pFile->Close();
			return FALSE;
		}

		for(i=0;i<MAX_CAL_DATA;i++)
		{
			for(j=0;j<MAX_CAL_DATA;j++)
			{
				Archive >> point[i][j];
			}
		}
		Archive.Close();
		m_pFile->Close();
		return TRUE;
	}
	Archive.Close();
	m_pFile->Close();
	return FALSE;
}
