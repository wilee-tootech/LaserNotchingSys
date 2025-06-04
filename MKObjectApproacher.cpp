
#include "StdAfx.h"
#include "Return.h"

#include "MKObjectApproacher.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//테스트 완료.

#define ARRAY_GROWBY  100     // 늘려야 되면 100개 단위로 늘린다.

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
	// Return Value: 찾으면 인덱스 값
	//               못 찾으면 -1
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
		if( pSrcObject == pObject){   //  지울 포인터와 일치 하면.
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
	// iPos를 쓰는 이유, 여러개의 쓰레드에서 GetFirst GetNext과정을 거치다보면 서로 엇갈림
	// 따라서 호출하는 놈이 자기가 어디까지 받아왔는지 기억하는게 가장 확실하고 효율적인 방법
	
	CMKObject *pMKObject;
	pMKObject = NULL;

	iPos =0;
	//m_CurPos = 0;
	if( m_nSize == 0) return NULL; //하나도 삽입되어있지 않으면 NULL리턴
	pMKObject = (CMKObject *)m_ObjectArray.GetAt(iPos); //하나를 가져온다.
	
	if( TRUE == IsBadReadPtr ( pMKObject, sizeof(CMKObject ) ) )
	{
		OutputDebugString("CMKStdObjectApproacher::GetFirst() - pMKObject pointer invalid");
		return NULL;
		
	}
	iPos++; // 성공적으로 읽었으면

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
	// pObject가 몇번째에 위치해 있는지 알아낸다. 
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

	// GetFirst에서 0으로 초기화된 값을 차츰 증가시켜 나간다.
	
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

	

