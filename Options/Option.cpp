// Option.cpp: implementation of the COption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Options.h"
#include "Option.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COption::COption()
{
	m_iMm = 1048576;
	m_iField = 208;
	m_cpDspFileName = "hkdsp.out";
	m_cpUnit = "MM";
	m_bShutter = FALSE;
	m_bUseChipSelect = FALSE;
	m_bUseTwoPart = FALSE;
	m_bUseLoadingImage = TRUE;
	m_bUseNetwork = FALSE;
	m_bUseHKImage = TRUE;
	m_bUseDefaultFile = FALSE;
	m_fFieldAngle = 0;
}

COption::~COption()
{

}

BOOL COption::LoadFile(char *cpFileName)
{
	FILE *initialFile;
	char cLine[20];
	char cIndex[20];
	char cVariable[20];
	int result;
	int i=0;
	int j=0;
	
	initialFile = fopen(cpFileName, "rt");
	if (initialFile == NULL) {
		return FALSE;
	}

	do {
		result = fscanf(initialFile, "%s\n", cLine); // Release mode관련 범인ㅡㅡ;;
		if( cLine[0] != NULL) 
		{
			for( i=0; cLine[i] ==' '; i++) ; 

			if( cLine[i] == ';')continue;
		}
				
		for ( i=0; cLine[i] != NULL; i++) {
			cIndex[i] = cLine[i];
			if (cLine[i] == '=') {
				cIndex[i] = '\0';
				for (int j = 0; cLine[++i] != NULL; j++) {
					cVariable[j] = cLine[i];
				}
				cVariable[j] = '\0';
				break;
			}
		}
		SetVariable(cIndex, cVariable);
	} while (result != -1);

	fclose(initialFile);
	
	return TRUE;
}

void COption::SetVariable(CString Index, CString Variable)
{
	if (strcmp(Index, "DEFAULTFILE") == 0) {
		m_bUseDefaultFile = atoi(Variable);
	}
	else if (strcmp(Index, "DSPFILE") == 0) {
		m_cpDspFileName = (char *)(LPCTSTR)Variable;
	}
	else if (strcmp(Index, "NETWORK") == 0) {
		m_bUseNetwork = atoi(Variable);
	}
	else if (strcmp(Index, "HKIMAGE") == 0) {
		m_bUseHKImage = atoi(Variable);
	}
	else if (strcmp(Index, "LOADINGIMAGE") == 0) {
		m_bUseLoadingImage = atoi(Variable);
	}
	else if (strcmp(Index, "UNIT") == 0) {
		m_cpUnit = (char *)(LPCTSTR)Variable;
	}
	else if (strcmp(Index, "LASER") == 0) {
		m_cpLaserControl = (char *)(LPCTSTR)Variable;
	}
	else if (strcmp(Index, "FIELD") == 0) {
		m_iField = atoi(Variable);
	}
	else if (strcmp(Index, "MM") == 0) {
		m_iMm = atoi(Variable);
	}
	else if (strcmp(Index, "FIELDANGLE") == 0) {
		m_fFieldAngle = float(atof(Variable));
	}
	else if (strcmp(Index, "PARTNUMBER") == 0) {
		m_bUseTwoPart = atoi(Variable);
	}
	else if (strcmp(Index, "USECHIPSELECT") == 0) {
		m_bUseChipSelect = atoi(Variable);
	}
}
