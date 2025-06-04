// Calibration.h: interface for the CCalibration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALIBRATION_H__09C1FC09_DDD2_4138_B5B2_04440531DC96__INCLUDED_)
#define AFX_CALIBRATION_H__09C1FC09_DDD2_4138_B5B2_04440531DC96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalibration  
{
public:
	CCalibration();
	virtual ~CCalibration();
	LRESULT OpenCalFile(CString calFile);
	void GetCalData(CPoint (*calData)[MAX_CAL_DATA]);

private:
	CPoint m_calData[MAX_CAL_DATA][MAX_CAL_DATA];
};

#endif // !defined(AFX_CALIBRATION_H__09C1FC09_DDD2_4138_B5B2_04440531DC96__INCLUDED_)
