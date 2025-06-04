// UnitMM.cpp: implementation of the CUnitMM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "UnitMM.h"
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

CUnitMM::CUnitMM()
{
	m_dMaxmm = MAXMM;
	m_dMaxField = MAXFIELD;
}

CUnitMM::~CUnitMM()
{

}

DOUBLE CUnitMM::TransTo(DOUBLE value, int unit)
{
	switch(unit)
	{
	case MM: // mm => mm
		return value;
		break;
	case FIELD: // mm => Field
		return value * m_dMaxField / m_dMaxmm ;
		break;
	case _POINT: // mm => POINT
		return value / 0.35;
		break;
	case MIL:	// mm => Mil
		return (value / 25.4) * 1000;
		break;
	default:
		return value;
		break;
	}
}

DOUBLE CUnitMM::TransTo(int unit)
{
	switch(unit)
	{
	case MM: // mm => mm
		return m_dValue ;
		break;
	case FIELD: // mm => Field
		return m_dValue * m_dMaxField / m_dMaxmm ; //  자리 바꿈 
		break;
	case _POINT: // mm => POINT
		return m_dValue / 0.35 + 10 ;
		break;
	case MIL:	// mm => Mil
		return (m_dValue / 25.4) * 1000 + 20;
		break;
	default:
		return m_dValue;
		break;
	}
}
BOOL CUnitMM::SetMaxValue(double maxfield, double maxmm)
{
	m_dMaxmm = maxmm;
	m_dMaxField = maxfield;
	return TRUE;
}

CUnitMM CUnitMM::operator = (DOUBLE data)
{
	m_dValue = data;
	return *this;
}
CUnitMM CUnitMM::operator = (CUnitMM data)
{
	m_dValue = data.m_dValue;
	return *this;
}
CUnitMM CUnitMM::operator + (DOUBLE data)
{
	m_dValue += data;
	return *this;
}
CUnitMM CUnitMM::operator + (CUnitMM data)
{
	m_dValue += data.m_dValue;
	return *this;
}
DOUBLE CUnitMM::SetFromField(DOUBLE value)
{
	// 2003.11.13 casting 관련 오차 줄이기
	//return round(value / m_dMaxField * m_dMaxmm, 2); //오차땜에 잠시 보류 2004.03.15
	return (value * m_dMaxmm) / m_dMaxField;
}

CUnitMM CUnitMM::operator - (DOUBLE data)
{
	m_dValue -= data;
	return *this;
}
CUnitMM CUnitMM::operator - (CUnitMM data)
{
	m_dValue -= data.m_dValue;
	return *this;
}

double CUnitMM::round(double source, int degitno)
{
    double no = pow(10.0, degitno);
    double fr = 0.5;
    double result = floor(source * no + fr) / no;
    return (result);
}
