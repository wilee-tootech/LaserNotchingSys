// MarkOrder.cpp: implementation of the CMarkOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MK.h"
#include "MarkOrder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "MkDoc.h"

CMarkOrder::CMarkOrder()
{

}

CMarkOrder::~CMarkOrder()
{

}

//////////////////////////////////////////////////////
// 오브젝트를 리스트에 주가 한다
void CMarkOrder::AddObj(defobj *obj)
{
	int number;
	
	m_markOrder.AddTail(obj);
	number = m_markOrder.GetCount();
	number--;
	obj->number = number;
}

///////////////////////////////////////////////////////
// 오브젝트를 리스트에서 삭제 한다
void CMarkOrder::DeleteObj(defobj *obj)
{
	POSITION pos, objpos;
	defobj *tempobj;

	pos = m_markOrder.Find(obj, NULL);
	objpos = pos;


	// 오브젝트의 number를 변경한다
	tempobj = m_markOrder.GetNext(pos);
	while(pos)
	{
		tempobj = m_markOrder.GetNext(pos);
		tempobj->number = tempobj->number - 1 ;
	}
	// 오브젝트를 리스트에서 삭제한다
	m_markOrder.RemoveAt(objpos);
}

/////////////////////////////////////////////////////////
// 오브젝트의 마킹 순서를 한단계 높인다
int CMarkOrder::OrderUp(defobj *obj)
{
	POSITION pos, objpos;
	defobj *curobj, *frontobj;

	pos = m_markOrder.Find(obj, NULL);
	objpos = pos;
	
	
	curobj = m_markOrder.GetPrev(pos);

	if (pos != NULL) 
	{
		curobj->number--;

		frontobj = m_markOrder.GetAt(pos);
		frontobj->number++;
		m_markOrder.RemoveAt(pos);

		m_markOrder.InsertAfter(objpos, frontobj);
	}
	return curobj->number;
}

/////////////////////////////////////////////////////////
// 오브젝트의 마킹 순서를 한단계 낮춘다
int CMarkOrder::OrderDown(defobj *obj)
{
	POSITION pos, objpos;
	defobj *curobj, *backobj;

	pos = m_markOrder.Find(obj);
	objpos = pos;

	curobj = m_markOrder.GetNext(pos);

	if (pos != NULL)
	{
		curobj->number++;

		backobj = m_markOrder.GetAt(pos);
		backobj->number--;

		m_markOrder.RemoveAt(pos);
		m_markOrder.InsertBefore(objpos, backobj);
	}
	return curobj->number;
}

////////////////////////////////////////////////////////
// 오브젝트의 순서를 가장 빠르게 한다
void CMarkOrder::OrderFirst(defobj *obj)
{
	int i=0;
	POSITION pos;
	defobj *curobj;

	// 지우기
	pos = m_markOrder.Find(obj);
	curobj = m_markOrder.GetAt(pos);
	m_markOrder.RemoveAt(pos);

	// 첫번째로 삽입
	m_markOrder.AddHead(curobj);

	// obj->number  재 설정
	pos = m_markOrder.GetHeadPosition();
	while(pos)
	{
		curobj = m_markOrder.GetNext(pos);
		curobj->number = i;
		i++;
	}
}

/////////////////////////////////////////////////////
// 오브젝트의 마킹 순서를 가장 늦게 한다
int CMarkOrder::OrderLast(defobj *obj)
{
	int i=0;
	POSITION pos;
	defobj *curobj;

	// 지우기
	pos = m_markOrder.Find(obj);
	curobj = m_markOrder.GetAt(pos);
	m_markOrder.RemoveAt(pos);

	// 마지막에 삽입
	m_markOrder.AddTail(curobj);

	// obj->number 재 설정
	pos = m_markOrder.GetHeadPosition();
	while(pos)
	{
		curobj = m_markOrder.GetNext(pos);
		curobj->number = i;
		i++;
	}
	return --i;
}
