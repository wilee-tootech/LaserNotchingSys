// Que.cpp: implementation of the CQue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mk.h"
#include "Que.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQue::CQue()
{

}

CQue::~CQue()
{

}

char *CQue::Pull()
{
	POSITION pos;

	pos = m_List.GetTailPosition();
	ASSERT(pos !=NULL);
	
	return m_List.GetAt(pos);
}
void CQue::Push(char *pData)
{
	m_List.AddHead(pData);
}

void CQue::Clear()
{
	POSITION pos;
	pos = m_List.GetHeadPosition();

	char *pData;

	while( pos )
	{
		pData = m_List.GetNext(pos);
		if( pData != NULL)
			delete pData;
	}
	m_List.RemoveAll();


}