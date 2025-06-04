// UnitMIL.h: interface for the CUnitMIL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITMIL_H__8B8DA961_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
#define AFX_UNITMIL_H__8B8DA961_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define MAXMM		180
//#define MAXFIELD	60000

class CUnitMIL  
{
public:
	DOUBLE m_dMaxField;
	DOUBLE m_dMaxMil;
	DOUBLE m_dValue;

public:
	CUnitMIL();
	virtual ~CUnitMIL();

	BOOL   SetMaxValue(double maxfield, double maxmil);
	DOUBLE TransTo(DOUBLE value, int unit);
	DOUBLE TransTo(int unit);
	DOUBLE SetFromField(DOUBLE value);
	
	CUnitMIL operator = (DOUBLE data);
	CUnitMIL operator = (CUnitMIL data);
	CUnitMIL operator + (DOUBLE data);
	CUnitMIL operator + (CUnitMIL data);
	CUnitMIL operator - (DOUBLE data);
	CUnitMIL operator - (CUnitMIL data);

private:
	double round(double source, int degitno);
};

#endif // !defined(AFX_UNITMIL_H__8B8DA961_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
