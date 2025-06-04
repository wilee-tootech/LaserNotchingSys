// MarkOrder.h: interface for the CMarkOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKORDER_H__9E7158C2_CCAB_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
#define AFX_MARKORDER_H__9E7158C2_CCAB_11D5_9CF0_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Afxtempl.h"

struct defobj;
///////////////////////////////////////
// ��������Ʈ�� Ŀ�� ������ ���� �Ѵ�
class CMarkOrder  
{
public:
	void AddObj(defobj *obj);
	CMarkOrder();
	virtual ~CMarkOrder();

public:
	int OrderLast(defobj *obj);
	void OrderFirst(defobj *obj);
	int OrderDown(defobj *obj);
	int OrderUp(defobj *obj);
	void DeleteObj(defobj* obj);
	CList<defobj*, defobj*> m_markOrder;
};

#endif // !defined(AFX_MARKORDER_H__9E7158C2_CCAB_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
