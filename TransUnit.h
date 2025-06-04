// TransUnit.h: interface for the CTransUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSUNIT_H__D6D877E0_F26F_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
#define AFX_TRANSUNIT_H__D6D877E0_F26F_11D5_9CF1_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "UnitMil.h"
#include "UnitMM.h"
#include "UnitPOINT.h"

class CTransUnit: public CUnitMIL, public CUnitMM, public CUnitPOINT
{
public:
	CTransUnit();
	CTransUnit(double maxfield, double maxmm);
	virtual ~CTransUnit();

	void SetState(UINT unit);
	BOOL SetValueWithField(double value);
	BOOL SetValueWithMM(double value);
	BOOL SetValueWithPoint(double value);
	BOOL SetValueWithMil(double value);
	BOOL SetValue(double value);
	BOOL SetValue(double value, UINT unit);
	BOOL SetMaxValue(double maxfield, double maxmm);
	double GetPoint(double value, UINT unit);
	double GetPoint();
	double GetMM(double value, UINT unit);
	double GetMM();
	double GetMil(double value, UINT unit);
	double GetMil();
	double GetField(double value, UINT unit);
	double GetField();
	double GetValue(UINT unit);

	CTransUnit operator = (DOUBLE data);
	CTransUnit operator = (CTransUnit data);
	CTransUnit operator + (DOUBLE data);
	CTransUnit operator - (DOUBLE data);
	CTransUnit operator + (CTransUnit data);
	CTransUnit operator - (CTransUnit data);

	/* �� �� ����� ������ Field, MM �ʱ� ������ ���ؼ� �ٸ� �����ڸ� ȣ���ؾ��ϱ� ���� */
	static CTransUnit *GetInstance();
	static CTransUnit *GetInstance(double maxfield, double maxmm); // ������ �ν��Ͻ� ��ȯ�ϱ�

private:
	static CTransUnit *m_pTransUnit;
	int m_iUnit; // ��ü ������ ������ ��������   // int m_State; ��� ����ϱ�
	             // ��� ���ڰ��� ����� �̰��� �����Ͽ� ���� Get���� 
	int m_iPreviousUnit; // �ʱ�ȭ�� �ʱ� ���̺��� �ϱ� or Mark File���� �о���̱�
	DOUBLE m_dMaxField;
	DOUBLE m_dValue;
};

#endif // !defined(AFX_TRANSUNIT_H__D6D877E0_F26F_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
