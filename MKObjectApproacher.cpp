
#include "StdAfx.h"
#include "Return.h"

#include "MKObjectApproacher.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//�׽�Ʈ �Ϸ�.

#define ARRAY_GROWBY  100     // �÷��� �Ǹ� 100�� ������ �ø���.

CMKObjectApproacher::CMKObjectApproacher()
{

}

CMKObjectApproacher::~CMKObjectApproacher()
{

}

CMKStdObjectApproacher::CMKStdObjectApproacher()
{

	m_ObjectArray.SetSize(NULL,ARRAY_GROWBY);
	m_nSize = 0;
		
}

CMKStdObjectApproacher::~CMKStdObjectApproacher()
{
	
}



UINT CMKStdObjectApproacher::Add(CMKObject *pMKObject)
{

	ASSERT ( FALSE == IsBadReadPtr( pMKObject , sizeof(CMKObject) ) );
	if( TRUE == IsBadReadPtr( pMKObject , sizeof(CMKObject) ) )
	{
		OutputDebugString("CMKStdObjectApproacher::Add - pMKObject pointer invalid.");
		return R_INVALID_POINTER;
	}

	int nArraySize = m_ObjectArray.GetSize();
	int nBound = m_ObjectArray.GetUpperBound();
	

	if( m_nSize < nArraySize )
	{
		m_ObjectArray.SetAt(m_nSize, pMKObject);
		
	}
	else
	{
		int nResult = m_ObjectArray.Add(pMKObject);
	}
	m_nSize++;


	return R_DEFAULT;
}
UINT CMKStdObjectApproacher::Delete(CMKObject *pMKObject)
{
	// Return Value: ã���� �ε��� ��
	//               �� ã���� -1
	register int i; 
	int nSize;
	CMKObject const *pSrcObject = pMKObject;
	CMKObject *pObject;

	ASSERT ( FALSE == IsBadReadPtr( pMKObject , sizeof(CMKObject) ) );
	if( TRUE == IsBadReadPtr( pMKObject , sizeof(CMKObject) ) )
	{
		OutputDebugString("CMKStdObjectApproacher::Delete - pMKObject pointer invalid.");
		return R_INVALID_POINTER;
	}


	nSize = m_ObjectArray.GetSize();
	
	for( i= 0 ; i< nSize; i++)
	{
		pObject = (CMKObject *)m_ObjectArray.GetAt(i);
		if( pSrcObject == pObject){   //  ���� �����Ϳ� ��ġ �ϸ�.
			m_ObjectArray.RemoveAt(i);
			m_nSize--;
			return i;
			//break; 
		}
	}
	return -1;
}

CMKObject* CMKStdObjectApproacher::GetFirst(int &iPos)  
{
	// iPos�� ���� ����, �������� �����忡�� GetFirst GetNext������ ��ġ�ٺ��� ���� ������
	// ���� ȣ���ϴ� ���� �ڱⰡ ������ �޾ƿԴ��� ����ϴ°� ���� Ȯ���ϰ� ȿ������ ���
	
	CMKObject *pMKObject;
	pMKObject = NULL;

	iPos =0;
	//m_CurPos = 0;
	if( m_nSize == 0) return NULL; //�ϳ��� ���ԵǾ����� ������ NULL����
	pMKObject = (CMKObject *)m_ObjectArray.GetAt(iPos); //�ϳ��� �����´�.
	
	if( TRUE == IsBadReadPtr ( pMKObject, sizeof(CMKObject ) ) )
	{
		OutputDebugString("CMKStdObjectApproacher::GetFirst() - pMKObject pointer invalid");
		return NULL;
		
	}
	iPos++; // ���������� �о�����

	return pMKObject;

}
void CMKStdObjectApproacher::RemoveAll()
{
	m_ObjectArray.RemoveAll();
	m_nSize=0;
	return;
}


int CMKStdObjectApproacher::Size()
{
//	int size = m_ObjectArray.GetSize(), canObjSize = 0;
//	CMKObject* pObject;
//	for (int i = 0; i < size; i++)
//	{
//		pObject = (CMKObject *)m_ObjectArray.GetAt(i);
//		if (pObject->GetMarkState())
//			canObjSize++;
//	}
	return m_ObjectArray.GetSize();
//	return canObjSize;
}


LONG CMKStdObjectApproacher::FindPos(CMKObject *pObject)
{
	// pObject�� ���°�� ��ġ�� �ִ��� �˾Ƴ���. 
	CMKObject *pObj;

	int iSize, iIndex=0;
	iSize = m_ObjectArray.GetSize();
	
	while ( iIndex < iSize)
	{
		pObj = (CMKObject *)m_ObjectArray.GetAt(iIndex);
		if( pObject == pObj) return iIndex;
		iIndex++;
	}
	return -1;

}


CMKObject *CMKStdObjectApproacher::GetNext(int &iPos)
{
	CMKObject *pMKObject;
	pMKObject = NULL;
	int nSize;


	nSize = m_ObjectArray.GetSize();

	// GetFirst���� 0���� �ʱ�ȭ�� ���� ���� �������� ������.
	
	if( iPos >= nSize || iPos < 0 )
	{
		iPos = NULL;
		return NULL;
	}
	
	pMKObject = (CMKObject *)m_ObjectArray.GetAt(iPos);
	iPos++;
	return pMKObject;
}

CMKObject *CMKStdObjectApproacher::GetAt(int iPosition)
{
	CMKObject *pMKObject;
	pMKObject = NULL;
		
	if( (iPosition >= 0) && (iPosition <m_nSize ))
	{
		pMKObject = (CMKObject *)m_ObjectArray.GetAt(iPosition);
	}

	return pMKObject;
}

UINT CMKStdObjectApproacher::DeleteAt(int iPosition)
{

	int nSize;
	nSize = m_ObjectArray.GetSize();
	ASSERT( (iPosition >= 0) && (iPosition <nSize ) );

	m_ObjectArray.RemoveAt(iPosition);
	m_nSize--;

	return R_DEFAULT;
}


UINT CMKStdObjectApproacher::InsertAt(int iPosition, CMKObject *pMKObject)
{
	ASSERT(FALSE==IsBadReadPtr( pMKObject, sizeof(CMKObject) ) );
	int nSize = m_ObjectArray.GetSize();
	
	m_ObjectArray.InsertAt(iPosition,pMKObject);
	m_nSize++;
	return R_DEFAULT;
}

CMKStdObjectApproacher *CMKStdObjectApproacher::Instance()
{
	static CMKStdObjectApproacher *pInstance;
	if( NULL == pInstance )
	{
		pInstance = new CMKStdObjectApproacher;
		return pInstance;
	}
	else return pInstance;
}

	

