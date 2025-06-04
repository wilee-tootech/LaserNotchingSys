// UnitPOINT.h: interface for the CUnitPOINT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITPOINT_H__8B8DA962_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
#define AFX_UNITPOINT_H__8B8DA962_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUnitPOINT  
{
public:
	DOUBLE m_dMaxPoint;
	DOUBLE m_dMaxField;
	DOUBLE m_dValue;
public:
	CUnitPOINT();
	virtual ~CUnitPOINT();

	DOUBLE TransTo(DOUBLE value, int unit);
	DOUBLE TransTo(int unit);
	DOUBLE SetFromField(DOUBLE value);

	BOOL SetMaxValue(double maxfield, double maxpoint);
	CUnitPOINT operator = (DOUBLE data);
	CUnitPOINT operator = (CUnitPOINT data);
	CUnitPOINT operator + (DOUBLE data);
	CUnitPOINT operator + (CUnitPOINT data);
	CUnitPOINT operator - (DOUBLE data);
	CUnitPOINT operator - (CUnitPOINT data);

private:
	double round(double source, int degitno);
};

#endif // !defined(AFX_UNITPOINT_H__8B8DA962_F29A_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
