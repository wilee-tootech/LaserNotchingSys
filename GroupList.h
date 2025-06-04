// GroupList.h: interface for the CGroupList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUPLIST_H__54244F66_4417_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
#define AFX_GROUPLIST_H__54244F66_4417_11D5_9CEB_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGroupList:public CList<int,int> 
{
public:
	float dy;
	float dx;
	int m_Grouped; // 0: 무상태 1: 선택 상태 2: 무상태 
	CRect m_Rect;
	CGroupList();
	virtual ~CGroupList();

};
 
#endif // !defined(AFX_GROUPLIST_H__54244F66_4417_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
