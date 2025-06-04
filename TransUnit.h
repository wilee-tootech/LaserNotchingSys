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

	/* 두 개 만드는 이유는 Field, MM 초기 셋팅을 위해서 다른 생성자를 호출해야하기 때문 */
	static CTransUnit *GetInstance();
	static CTransUnit *GetInstance(double maxfield, double maxmm); // 유일한 인스턴스 반환하기

private:
	static CTransUnit *m_pTransUnit;
	int m_iUnit; // 전체 동일한 단위로 가져가기   // int m_State; 대신 사용하기
	             // 모든 숫자관련 놈들은 이곳에 접근하여 물론 Get으로 
	int m_iPreviousUnit; // 초기화는 초기 테이블에서 하기 or Mark File에서 읽어들이기
	DOUBLE m_dMaxField;
	DOUBLE m_dValue;
};

#endif // !defined(AFX_TRANSUNIT_H__D6D877E0_F26F_11D5_9CF1_0000B4BB2A6F__INCLUDED_)
