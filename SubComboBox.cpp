// SubComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "SubComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubComboBox

CSubComboBox::CSubComboBox()
{
	 m_strInputTxt = _T("");
}

CSubComboBox::~CSubComboBox()
{
}


BEGIN_MESSAGE_MAP(CSubComboBox, CComboBox)
	//{{AFX_MSG_MAP(CSubComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubComboBox message handlers

BOOL CSubComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	 if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))

    {
		 
		 /*
		 CString str;
		 int idx = GetCurSel();
		 int count = GetCount();
		 if( idx < 0 ) return TRUE;
		 //for(int i = 0; i , GetCount(); i++)
		 //{
		//	 GetLBText(i,str);

			 
			 //if(FindString() == str)
			//	 SetCurSel(i);
			 
		// }
		 GetLBText(GetCurSel(),str);
		 idx = FindString(0, str);
		 ShowDropDown(TRUE);
		 
		 //GetLBText(i,str);
		 */
		 //keybd_event(VK_TAB, 0, 0, 0);
		 //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		  SetCurSel(GetCurSel());
		 ShowDropDown(FALSE);
		 return TRUE;
		 
	 }
	 
	 else
		 
	 {
		 
		 return CWnd::PreTranslateMessage(pMsg);
		 
	 }
	
//	return CComboBox::PreTranslateMessage(pMsg);
}
