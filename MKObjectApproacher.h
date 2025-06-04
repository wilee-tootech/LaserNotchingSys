// Interface

#ifndef _MKObjectApproacher
#define _MKObjectApproacher

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MKObject.h"

//  ��ӹ��� Ŭ������ �迭�� ����ϴ� ����Ʈ�� ����ϴ� ���� �������̽��� 
//	����� �����Ѵ�. #include "MKObject.h"

#include <afxcoll.h>

// CMKObjectApproacher �� �������̽��� �����⸸ �ϸ� �󸶵��� �ٸ� �����ڷ� ���� ����, ��Ÿ�ӽ� ����
class CMKObjectApproacher
{
public:
	CMKObjectApproacher();
	virtual ~CMKObjectApproacher();
	virtual UINT Add(CMKObject *pMKObject)=0;		//������Ʈ�ϳ��� �߰�
	virtual UINT Delete(CMKObject *pMKObject)=0;    //������Ʈ�ϳ� ����
	virtual CMKObject *GetFirst(int &iPos)=0;       //ó���� ������
	virtual CMKObject *GetNext(int &iPos)=0;        //�״����� �����´�
	virtual CMKObject *GetAt(int iPosition)=0;      //iPosition�� ��ġ�� �ִ� ������Ʈ�� �����´�
	virtual UINT DeleteAt(int iPosition)=0;         //iPosition�� �ִ� ������Ʈ�� �����
	virtual UINT InsertAt(int iPosition, CMKObject *pMKObject)=0; 
	virtual int Size()=0;                           //�迭�� ũ�⸦ �ݳ� 
	virtual LONG FindPos(CMKObject *pObject)=0;     //������Ʈ�� ���°�� ��ġ�� �ִ��� �˾ƿ´�
	virtual void RemoveAll()=0;                     //��ü ����(�����͸�, ������Ʈ�� ��������)
	

private:
	
};

class CMKStdObjectApproacher : public CMKObjectApproacher
{
public:

	
	virtual UINT Add(CMKObject *pMKObject);
	virtual UINT Delete(CMKObject *pMKObject);
	virtual CMKObject *GetFirst(int &iPos);
	virtual CMKObject *GetNext(int &iPos);
	virtual CMKObject *GetAt(int iPosition);
	virtual UINT DeleteAt(int iPosition);
	virtual UINT InsertAt(int iPosition, CMKObject *pMKObject);
	virtual void RemoveAll();
	virtual int Size();
	virtual LONG FindPos(CMKObject *pObject);
	

	virtual CMKStdObjectApproacher *Instance();

	CMKStdObjectApproacher();
	virtual ~CMKStdObjectApproacher();
	






private:

	//static CMKStdObjectApproacher *m_pInstance;
	
	CObArray m_ObjectArray;
	
	int m_nSize;
};
#endif //_MKObjectApproacher

