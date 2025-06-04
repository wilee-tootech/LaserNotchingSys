 // UnitMM.h: interface for the CUnitMM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITMM_H__8B8DA960_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
#define AFX_UNITMM_H__8B8DA960_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define MAXMM		180
//#define MAXFIELD	60000

class CUnitMM  
{
public:
	DOUBLE m_dMaxField;
	DOUBLE m_dMaxmm;
	DOUBLE m_dValue;

public:
	double round(double source, int degitno);
	CUnitMM();
	virtual ~CUnitMM();

	DOUBLE TransTo(DOUBLE value, int unit);
	DOUBLE TransTo(int unit);
	DOUBLE SetFromField(DOUBLE value);

	BOOL SetMaxValue(double maxfield, double maxmm);
	CUnitMM operator = (DOUBLE data);
	CUnitMM operator = (CUnitMM data);
	CUnitMM operator + (DOUBLE data);
	CUnitMM operator + (CUnitMM data);
	CUnitMM operator - (DOUBLE data);
	CUnitMM operator - (CUnitMM data);
};

#endif // !defined(AFX_UNITMM_H__8B8DA960_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
