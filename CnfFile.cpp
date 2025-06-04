// CnfFile.cpp: implementation of the CCnfFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mk.h"
#include "CnfFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCnfFile::CCnfFile()
{

}

CCnfFile::~CCnfFile()
{

}

BOOL CCnfFile::Open(CString fileName)
{
	FILE *file;
	file = fopen(fileName, "rt");
	if (file == NULL)
		return FALSE;
	fscanf(file,"%d %d\n", &m_maxField, &m_maxMmSize);
	fclose(file);
	m_fileName = fileName;
	return TRUE;
}

BOOL CCnfFile::SaveFile()
{
	FILE *file;
	file = fopen(m_fileName, "wt");
	if (file == NULL)
		return FALSE;
	fprintf(file,"%d %d\n", m_maxField, m_maxMmSize);
	fclose(file);
	return TRUE;
}

BOOL CCnfFile::SaveFile(int maxField, int maxMmSize)
{
	FILE *file;
	file = fopen(m_fileName, "wt");
	if (file == NULL)
		return FALSE;
	fprintf(file,"%d %d\n", maxField, maxMmSize);
	fclose(file);
	return TRUE;
}
