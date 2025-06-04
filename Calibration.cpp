// Calibration.cpp: implementation of the CCalibration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Calibration.h"
#include "Ctd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalibration::CCalibration()
{
	// 여기서 초기화도 해주는 거지
	for(int i=0; i< MAX_CAL_DATA; i++)
	{
		for(int j=0; j< MAX_CAL_DATA; j++)
		{
			m_calData[i][j].x = 0;
			m_calData[i][j].y = 0;
		}
	}
}

CCalibration::~CCalibration()
{

}

LRESULT CCalibration::OpenCalFile(CString calFile)
{
	CFileFind filefind;
	if (filefind.FindFile(calFile) == FALSE)
	{
		return FALSE;
	}

	CCtd ctd;
	if (FALSE == ctd.OpenCtd(calFile, m_calData))
	{
		AfxMessageBox(IDS_MESSAGE53, MB_OK);
		return FALSE;
	}

	return TRUE;
}

void CCalibration::GetCalData(CPoint (*calData)[MAX_CAL_DATA])
{
//	calData = m_calData;
	for (int i = 0; i < MAX_CAL_DATA; i++) {
		for (int j = 0; j < MAX_CAL_DATA; j++) {
			(*(calData+i))[j] = m_calData[i][j];
		}
	}
//	calData = m_calData;
}
