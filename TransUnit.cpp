// TransUnit.cpp: implementation of the CTransUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TransUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTransUnit::CTransUnit()
{
	m_iUnit = FIELD;
	SetMaxValue(MAXFIELD, MAXMM); 
}

CTransUnit::~CTransUnit()
{
}

CTransUnit::CTransUnit(double maxfield, double maxmm)
{
	m_iUnit = FIELD;
	SetMaxValue(maxfield, maxmm);
}

CTransUnit* CTransUnit::m_pTransUnit = 0;
CTransUnit* CTransUnit::GetInstance(double maxfield, double maxmm) 
{
	if (m_pTransUnit == 0) {
		m_pTransUnit = new CTransUnit(maxfield, maxmm);
	}
	return m_pTransUnit;
}

CTransUnit* CTransUnit::GetInstance() 
{
	if (m_pTransUnit == 0) {
		m_pTransUnit = new CTransUnit();
	}
	return m_pTransUnit;
}

BOOL CTransUnit::SetMaxValue(double maxfield, double maxmm)
{
	m_dMaxField	= maxfield;
	m_dMaxmm	= maxmm;
	m_dMaxPoint	= m_dMaxmm / 0.35;
	m_dMaxMil	= m_dMaxmm / 25.4 * 1000;

	CUnitMIL::SetMaxValue(m_dMaxField, m_dMaxMil); 
	CUnitMM::SetMaxValue(m_dMaxField, m_dMaxmm); 
	CUnitPOINT::SetMaxValue(m_dMaxField, m_dMaxPoint); 

	return true;
}

CTransUnit CTransUnit::operator = (DOUBLE data)
{
	m_dValue = data;
	return *this;
}

CTransUnit CTransUnit::operator = (CTransUnit data)
{
	m_iUnit = data.m_iUnit;
	m_dValue = data.m_dValue;
	return *this;
}

CTransUnit CTransUnit::operator + (DOUBLE data)
{
	m_dValue += data;
	return *this;
}

CTransUnit CTransUnit::operator + (CTransUnit data)
{
	switch(m_iUnit)
	{
	case MM: // data를 MM 단위로 바꾸어 더한다
		m_dValue += data.GetMM();
		break;
	case FIELD:
		m_dValue += data.GetField();
		break;
	case _POINT:
		m_dValue += data.GetPoint();
		break;
	case MIL:
		m_dValue += data.GetMil();
		break;
	default:
		m_dValue += data.m_dValue;
		break;
	}
	return *this;
}

CTransUnit CTransUnit::operator - (DOUBLE data)
{
	m_dValue -= data;
	return *this;
}

CTransUnit CTransUnit::operator - (CTransUnit data)
{
	switch(m_iUnit)
	{
	case MM: // data를 MM 단위로 바꾸어 더한다
		m_dValue -= data.GetMM();
		break;
	case FIELD:
		m_dValue -= data.GetField();
		break;
	case _POINT:
		m_dValue -= data.GetPoint();
		break;
	case MIL:
		m_dValue -= data.GetMil();
		break;
	default:
		m_dValue -= data.m_dValue;
		break;
	}
	return *this;
}

////////////////////////////////////////////////////
// value = 변환될 값, unit = 입력값의 데이터 단위
DOUBLE CTransUnit::GetField(DOUBLE value, UINT unit)
{
	switch(unit)
	{
	case MM: // MM => field
		return CUnitMM::TransTo(value, FIELD);
	case FIELD: // field => field
		return value;
	case _POINT: // point => field
		return CUnitPOINT::TransTo(value, FIELD);
	case MIL: // MIL => field
		return CUnitMIL::TransTo(value, FIELD);
	default:
		return value;
	}
	return 0;
}

DOUBLE CTransUnit::GetField()
{
	switch(m_iUnit)
	{
	case MM: // MM => field
		return CUnitMM::TransTo(m_dValue, FIELD);
	case FIELD: // field => field
		return m_dValue;
	case _POINT: // point => field
		return CUnitPOINT::TransTo(m_dValue, FIELD);
	case MIL: // MIL => field
		return CUnitMIL::TransTo(m_dValue, FIELD);
	default:
		return m_dValue;
	}
	return 0;
}

DOUBLE CTransUnit::GetMil(DOUBLE value, UINT unit)
{
	switch(unit)
	{
	case MM: // MM => mil
		return CUnitMM::TransTo(value, MIL);
	case FIELD: // field => mil
		return CUnitMIL::SetFromField(value);
	case _POINT: // point => mil
		return CUnitPOINT::TransTo(value, MIL);
	case MIL: // MIL => mil
		return value;
	default:
		return value;
	}
	return 0;
}

DOUBLE CTransUnit::GetMil()
{
	switch(m_iUnit)
	{
	case MM: // MM => mil
		return CUnitMM::TransTo(m_dValue, MIL);
	case FIELD: // field => mil
		return CUnitMIL::SetFromField(m_dValue);
	case _POINT: // point => mil
		return CUnitPOINT::TransTo(m_dValue, MIL);
	case MIL: // MIL => mil
		return m_dValue;
	default:
		return m_dValue;
	}
	return 0;
}

DOUBLE CTransUnit::GetMM(DOUBLE value, UINT unit)
{
	switch(unit)
	{
	case MM: // MM => mm
		return value;
	case FIELD: // field => mm
		return CUnitMM::SetFromField(value);
	case _POINT: // point => mm
		return CUnitPOINT::TransTo(value, MM);
	case MIL: // MIL => mm
		return CUnitMIL::TransTo(value, MM);
	default:
		return value;
	}
	return 0;
}

DOUBLE CTransUnit::GetMM()
{
	switch(m_iUnit)
	{
	case MM: // MM => mm
		return m_dValue;
	case FIELD: // field => mm
		return CUnitMM::SetFromField(m_dValue);
	case _POINT: // point => mm
		return CUnitPOINT::TransTo(m_dValue, MM);
	case MIL: // MIL => mm
		return CUnitMIL::TransTo(m_dValue, MM);
	default:
		return m_dValue;
	}
	return 0;
}

DOUBLE CTransUnit::GetPoint(DOUBLE value, UINT unit)
{
	switch(unit)
	{
	case MM: // MM => point
		return CUnitMM::TransTo(value, _POINT);
	case FIELD: // field => point
		return CUnitPOINT::SetFromField(value);
	case _POINT: // point => point
		return value;
	case MIL: // MIL => point
		return CUnitMIL::TransTo(value, _POINT);
	default:
		return value;
	}
	return 0;
}

DOUBLE CTransUnit::GetPoint()
{
	switch(m_iUnit)
	{
	case MM: // MM => point
		return CUnitMM::TransTo(m_dValue, _POINT);
	case FIELD: // field => point
		return CUnitPOINT::SetFromField(m_dValue);
	case _POINT: // point => point
		return m_dValue;
	case MIL: // MIL => point
		return CUnitMIL::TransTo(m_dValue, _POINT);
	default:
		return m_dValue;
	}
	return 0;
}

void CTransUnit::SetState(UINT unit)
{
	switch(m_iUnit)
	{
	case MM:	// MM => unit
		m_dValue = CUnitMM::TransTo(m_dValue, unit); break;
	case FIELD:
		switch(unit)
		{
		case MM: // FIELD => MM
			m_dValue = CUnitMM::SetFromField(m_dValue); break;
		case FIELD: // FIELD => FIELD
			m_dValue = m_dValue; break;
		case _POINT: // FIELD => POINT
			m_dValue = CUnitPOINT::SetFromField(m_dValue); break;
		case MIL:  // FIELD => MIL
			m_dValue = CUnitMIL::SetFromField(m_dValue); break;
		default:
			break;
		}
		break;
	case _POINT: // POINT => unit
		m_dValue = CUnitPOINT::TransTo(m_dValue, unit); break;
	case MIL:	// MIL => unit
		m_dValue = CUnitMIL::TransTo(m_dValue, unit); break;
	default:
		m_dValue = m_dValue; break;
	}
	m_iUnit = unit;
}

BOOL CTransUnit::SetValue(DOUBLE value)
{
	m_dValue = value;
	switch(m_iUnit)
	{
	case MM:
		CUnitMIL::m_dValue = CUnitMM::TransTo(value, MIL); // mm => mil 변환후 저장 
		CUnitMM::m_dValue = value;
		CUnitPOINT::m_dValue = CUnitMM::TransTo(value,_POINT); // mm => point
		break;
	case FIELD:
		CUnitMIL::m_dValue = CUnitMIL::SetFromField(value);	// field => mil
		CUnitMM::m_dValue = CUnitMM::SetFromField(value);	// field => mm
		CUnitPOINT::m_dValue = CUnitPOINT::SetFromField(value);// field => point
		break;
	case _POINT:
		CUnitMIL::m_dValue = CUnitPOINT::TransTo(value, MIL); // point => mil
		CUnitMM::m_dValue = CUnitPOINT::TransTo(value, MM);	// point => mm
		CUnitPOINT::m_dValue = value;
		break;
	case MIL:
		CUnitMIL::m_dValue = value; // min => mil
		CUnitMM::m_dValue = CUnitMIL::TransTo(value,MM);  // mil => mm
		CUnitPOINT::m_dValue = CUnitMIL::TransTo(value,_POINT); // mil => point 
		break;
	default:
		CUnitMIL::m_dValue = value;
		CUnitMM::m_dValue = value;
		CUnitPOINT::m_dValue = value;
		break;
	}

	return TRUE;
}

BOOL CTransUnit::SetValue(DOUBLE value, UINT unit)
{
	m_iUnit = unit;
	SetValue(value);
	return TRUE;
}

BOOL CTransUnit::SetValueWithField(DOUBLE value)
{
	m_iUnit = FIELD;
	SetValue(value);
	return TRUE;
}

BOOL CTransUnit::SetValueWithMM(DOUBLE value)
{
	m_iUnit = MM;
	SetValue(value);
	return TRUE;
}

BOOL CTransUnit::SetValueWithPoint(DOUBLE value)
{
	m_iUnit = _POINT;
	SetValue(value);
	return TRUE;
}

BOOL CTransUnit::SetValueWithMil(DOUBLE value)
{
	m_iUnit = MIL;
	SetValue(value);
	return TRUE;
}

DOUBLE CTransUnit::GetValue(UINT unit)
{
	switch(unit)
	{
	case MM:
		return GetMM();
	case FIELD:
		return GetField();
	case _POINT:
		return GetPoint();
	case MIL:
		return GetMil();
	default:
		return GetField();
	}
}
