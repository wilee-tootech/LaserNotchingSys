// DataBuilder.h: interface for the CDataBuilder class.
//
// * Singleton
//   �����͵��� ��񿡴ٰ� Setting ��Ű�� ���� (������ SendAllDataToDsp ����) �� �ϵ� 
//   OBJECT�� Data�� ������ ���� �� OBJECT�� ����
//   ������ ������ ������ �ʿ䰡 �ִ�. OBJECT�� Data�� �� ������ bin, para, offset � �� ������..
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
