// Que.h: interface for the CQue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUE_H__007781A6_738D_4D4F_B350_C460C52C2366__INCLUDED_)
#define AFX_QUE_H__007781A6_738D_4D4F_B350_C460C52C2366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQue  
{
public:
	CQue();
	virtual ~CQue();
	char *Pull();
	void Push(char *pData);
	void Clear();
	

private:
	CList<char *,char *> m_List;

};

#endif // !defined(AFX_QUE_H__007781A6_738D_4D4F_B350_C460C52C2366__INCLUDED_)
