// DataBuilder.h: interface for the CDataBuilder class.
//
// * Singleton
//   데이터들을 장비에다가 Setting 시키는 역할 (예전의 SendAllDataToDsp 역할) 을 하되 
//   OBJECT의 Data를 보내는 것은 각 OBJECT에 위임
//   역할의 범위를 지정할 필요가 있다. OBJECT의 Data만 할 것인지 bin, para, offset 등도 할 것인지..
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUILDER_H__6B948471_0D93_4E5C_9DA2_F23A261E98D4__INCLUDED_)
#define AFX_DATABUILDER_H__6B948471_0D93_4E5C_9DA2_F23A261E98D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marking.h"

class CDataBuilder  
{
public:
	void SetDelayTime(unsigned int iSecond);
	CDataBuilder();
	virtual ~CDataBuilder();

	virtual UINT BuildTotalData(CMarking *pMarking); 
	virtual void SetOffset(int iX, int iY);
	virtual void SetAngle(double dAngle);

	static CDataBuilder *GetInstance();

private:	
	static CDataBuilder *m_pDataBuilder;
};

#endif // !defined(AFX_DATABUILDER_H__6B948471_0D93_4E5C_9DA2_F23A261E98D4__INCLUDED_)
