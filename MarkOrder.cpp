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
// ������Ʈ�� ����Ʈ�� �ְ� �Ѵ�
void CMarkOrder::AddObj(defobj *obj)
{
	int number;
	
	m_markOrder.AddTail(obj);
	number = m_markOrder.GetCount();
	number--;
	obj->number = number;
}

///////////////////////////////////////////////////////
// ������Ʈ�� ����Ʈ���� ���� �Ѵ�
void CMarkOrder::DeleteObj(defobj *obj)
{
	POSITION pos, objpos;
	defobj *tempobj;

	pos = m_markOrder.Find(obj, NULL);
	objpos = pos;


	// ������Ʈ�� number�� �����Ѵ�
	tempobj = m_markOrder.GetNext(pos);
	while(pos)
	{
		tempobj = m_markOrder.GetNext(pos);
		tempobj->number = tempobj->number - 1 ;
	}
	// ������Ʈ�� ����Ʈ���� �����Ѵ�
	m_markOrder.RemoveAt(objpos);
}

/////////////////////////////////////////////////////////
// ������Ʈ�� ��ŷ ������ �Ѵܰ� ���δ�
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
// ������Ʈ�� ��ŷ ������ �Ѵܰ� �����
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
// ������Ʈ�� ������ ���� ������ �Ѵ�
void CMarkOrder::OrderFirst(defobj *obj)
{
	int i=0;
	POSITION pos;
	defobj *curobj;

	// �����
	pos = m_markOrder.Find(obj);
	curobj = m_markOrder.GetAt(pos);
	m_markOrder.RemoveAt(pos);

	// ù��°�� ����
	m_markOrder.AddHead(curobj);

	// obj->number  �� ����
	pos = m_markOrder.GetHeadPosition();
	while(pos)
	{
		curobj = m_markOrder.GetNext(pos);
		curobj->number = i;
		i++;
	}
}

/////////////////////////////////////////////////////
// ������Ʈ�� ��ŷ ������ ���� �ʰ� �Ѵ�
int CMarkOrder::OrderLast(defobj *obj)
{
	int i=0;
	POSITION pos;
	defobj *curobj;

	// �����
	pos = m_markOrder.Find(obj);
	curobj = m_markOrder.GetAt(pos);
	m_markOrder.RemoveAt(pos);

	// �������� ����
	m_markOrder.AddTail(curobj);

	// obj->number �� ����
	pos = m_markOrder.GetHeadPosition();
	while(pos)
	{
		curobj = m_markOrder.GetNext(pos);
		curobj->number = i;
		i++;
	}
	return --i;
}
