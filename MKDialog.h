// MKDialog.h: interface for the CMKDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKDIALOG_H__92A8EC17_06EF_48AB_A163_2DFA83E65881__INCLUDED_)
#define AFX_MKDIALOG_H__92A8EC17_06EF_48AB_A163_2DFA83E65881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
//
class CMKObject;

class CMKDialog : public CDialog  
{
public:
	CMKDialog(UINT ID,CWnd *pWnd);
	virtual ~CMKDialog();
	void SetMKObject(CMKObject *pObject);
	CMKObject *GetMKObject();

private:
	CMKObject *m_pObject;


};

#endif // !defined(AFX_MKDIALOG_H__92A8EC17_06EF_48AB_A163_2DFA83E65881__INCLUDED_)
