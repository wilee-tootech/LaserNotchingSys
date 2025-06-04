// Interface

#ifndef _MKObjectApproacher
#define _MKObjectApproacher

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MKObject.h"

//  상속받은 클래스는 배열을 사용하던 리스트를 사용하던 같은 인터페이스로 
//	기능을 제공한다. #include "MKObject.h"

#include <afxcoll.h>

// CMKObjectApproacher 의 인터페이스를 따르기만 하면 얼마든지 다른 접근자로 변경 가능, 런타임시 말고
class CMKObjectApproacher
{
public:
	CMKObjectApproacher();
	virtual ~CMKObjectApproacher();
	virtual UINT Add(CMKObject *pMKObject)=0;		//오브젝트하나를 추가
	virtual UINT Delete(CMKObject *pMKObject)=0;    //오브젝트하나 삭제
	virtual CMKObject *GetFirst(int &iPos)=0;       //처음을 가져옴
	virtual CMKObject *GetNext(int &iPos)=0;        //그다음을 가져온다
	virtual CMKObject *GetAt(int iPosition)=0;      //iPosition에 위치해 있는 오브젝트를 가져온다
	virtual UINT DeleteAt(int iPosition)=0;         //iPosition에 있는 오브젝트를 지운다
	virtual UINT InsertAt(int iPosition, CMKObject *pMKObject)=0; 
	virtual int Size()=0;                           //배열의 크기를 반납 
	virtual LONG FindPos(CMKObject *pObject)=0;     //오브젝트가 몇번째에 위치해 있는지 알아온다
	virtual void RemoveAll()=0;                     //전체 삭제(포인터만, 오브젝트는 남아있음)
	

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

