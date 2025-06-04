// UnitPOINT.cpp: implementation of the CUnitPOINT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "UnitPOINT.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "define.h"

CUnitPOINT::CUnitPOINT()
{
	m_dMaxPoint = MAXMM / 0.35;
	m_dMaxField = MAXFIELD;
}

CUnitPOINT::~CUnitPOINT()
{

}
DOUBLE CUnitPOINT::TransTo(DOUBLE value, int unit)
{
	switch(unit)
	{
	case MM: // point => mm
		return value * 0.35;
		break;
	case FIELD: // point => Field
		return value / m_dMaxPoint * m_dMaxField;
		break;
	case _POINT: // point => POINT
		return value;
		break;
	case MIL:	// point => Mil
		return value * 0.35  / 25.4 * 1000;
		break;
	default:
		return value;
		break;
	}
}
DOUBLE CUnitPOINT::TransTo(int unit)
{
	switch(unit)
	{
	case MM: // point => mm
		return m_dValue * 0.35;
		break;
	case FIELD: // point => Field
		return m_dValue / m_dMaxPoint * m_dMaxField;
		break;
	case _POINT: // point => POINT
		return m_dValue;
		break;
	case MIL:	// point => Mil
		return m_dValue * 0.35  / 25.4 * 1000;
		break;
	default:
		return m_dValue;
		break;
	}
}
BOOL CUnitPOINT::SetMaxValue(double maxfield, double maxpoint)
{
	m_dMaxPoint = maxpoint;
	m_dMaxField = maxfield;
	return TRUE;
}
CUnitPOINT CUnitPOINT::operator = (DOUBLE data)
{
	m_dValue = data;
	return *this;
}
CUnitPOINT CUnitPOINT::operator = (CUnitPOINT data)
{
	m_dValue = data.m_dValue;
	return *this;
}
CUnitPOINT CUnitPOINT::operator + (DOUBLE data)
{
	m_dValue += data;
	return *this;
}
CUnitPOINT CUnitPOINT::operator + (CUnitPOINT data)
{
	m_dValue += data.m_dValue;
	return *this;
}
DOUBLE CUnitPOINT::SetFromField(DOUBLE value)
{
	//return round(value / m_dMaxField * m_dMaxPoint, 2);
	return (value * m_dMaxPoint) / m_dMaxField;
}

CUnitPOINT CUnitPOINT::operator - (DOUBLE data)
{
	m_dValue -= data;
	return *this;
}
CUnitPOINT CUnitPOINT::operator - (CUnitPOINT data)
{
	m_dValue -= data.m_dValue;
	return *this;
}

double CUnitPOINT::round(double source, int degitno)
{
    double no = pow(10.0, degitno);
    double fr = 0.5;
    double result = floor(source * no + fr) / no;
    return (result);
}
