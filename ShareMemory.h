// ShareMemory.h: interface for the CShareMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREMEMORY_H__8916094D_85D3_4E4B_8456_45114F8DB17B__INCLUDED_)
#define AFX_SHAREMEMORY_H__8916094D_85D3_4E4B_8456_45114F8DB17B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShareMemory  
{
public:
	static CShareMemory *m_pShareMemory;
	CShareMemory();
	virtual ~CShareMemory();

};

#endif // !defined(AFX_SHAREMEMORY_H__8916094D_85D3_4E4B_8456_45114F8DB17B__INCLUDED_)
