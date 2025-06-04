// UnitMIL.cpp: implementation of the CUnitMIL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "UnitMIL.h"
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

CUnitMIL::CUnitMIL()
{
	m_dMaxMil = MAXMM / 25.4 * 1000;
	m_dMaxField = MAXFIELD;
}

CUnitMIL::~CUnitMIL()
{

}
DOUBLE CUnitMIL::TransTo(DOUBLE value, int unit)
{
	switch(unit)
	{
	case MM: // Mil => mm
		return value / 1000 * 25.4;
		break;
	case FIELD: // Mil => Field
		return value / m_dMaxMil * m_dMaxField;
		break;
	case _POINT: // Mil => POINT
		return (value/ 1000 * 25.4) / 0.35;
		break;
	case MIL:	// Mil => Mil
		return value;
		break;
	default:
		return value;
		break;
	}
}

DOUBLE CUnitMIL::TransTo(int unit)
{
	switch(unit)
	{
	case MM: // Mil => mm
		return m_dValue / 1000 * 25.4;
		break;
	case FIELD: // Mil => Field
		return m_dValue / m_dMaxMil * m_dMaxField;
		break;
	case _POINT: // Mil => POINT
		return (m_dValue/ 1000 * 25.4) / 0.35;
		break;
	case MIL:	// Mil => Mil
		return m_dValue;
		break;
	default:
		return m_dValue;
		break;
	}
}

BOOL CUnitMIL::SetMaxValue(double maxfield, double maxmil)
{
	m_dMaxMil = maxmil;
	m_dMaxField = maxfield;
	return TRUE;
}

CUnitMIL CUnitMIL::operator = (DOUBLE data)
{
	m_dValue = data;
	return *this;
}

CUnitMIL CUnitMIL::operator = (CUnitMIL data)
{
	m_dValue = data.m_dValue;
	return *this;
}

CUnitMIL CUnitMIL::operator + (DOUBLE data)
{
	m_dValue += data;
	return *this;
}

CUnitMIL CUnitMIL::operator + (CUnitMIL data)
{
	m_dValue += data.m_dValue;
	return *this;
}

DOUBLE CUnitMIL::SetFromField(DOUBLE value)
{
	//return round(value / m_dMaxField * m_dMaxMil, 2); // : 잠시보류 2004.3.15
	return (value * m_dMaxMil) / m_dMaxField;
}

CUnitMIL CUnitMIL::operator - (DOUBLE data)
{
	m_dValue -= data;
	return *this;
}
CUnitMIL CUnitMIL::operator - (CUnitMIL data)
{
	m_dValue -= data.m_dValue;
	return *this;
}

double CUnitMIL::round(double source, int degitno)
{
    double no = pow(10.0, degitno);
    double fr = 0.5;
    double result = floor(source * no + fr) / no;
    return (result);
}