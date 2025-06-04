#pragma once

//#include "afxext.h"
#include "GuiDefine.h"

#include <vector>
#include <map>
#include <iterator>

namespace NAME_GUI_MANAGER
{
struct FORM_INFOR
{
	CWnd* pWnd;
	long PaneID;
	long FormID;
	bool bShow;
	void __stdcall Clear( )
	{
		pWnd = NULL;
		FormID = 0;
		PaneID  = 0;
		bShow = false;
	}
	__stdcall FORM_INFOR() {Clear();}
};
	
class CDivideView : public CSplitterWnd
{		
public:
	BOOL __stdcall AddView( UINT FormID, int nRow, int nCol, CSize Size, CRuntimeClass * pViewClass, CCreateContext* pContext );
	void __stdcall DeleteView( void );
	BOOL __stdcall ChangeView( int InforPanelID, int nCmdPanelID = 0);	
	BOOL __stdcall HideView( long lFormId);
private:
	CWnd* __stdcall GetWndbyPane( int x, int y );
			
	long __stdcall  GetFormIDbyPane( int x, int y );
	
	
	BOOL __stdcall IsExistView( long lFormId );

public:
	void SetSplitBarSize(int iBar, int iBorder);
	CWnd* __stdcall GetWndbyFormID ( long lFormId );
	void __stdcall SetFixSplitBar( BOOL bEnable );
	BOOL __stdcall ShowView( long lFormId);

		
public:
	


private:
	std::map< long, FORM_INFOR* > m_MapViews;
	FORM_INFOR m_CurrFormInfor;

	long m_lCurInforPanelFormID	;	// 현재 활성화 된 Information Panel  Form ID
	long m_lCurCmdPanelFormID;		// 현재 활성화 된 Command Panel Form ID
	BOOL m_bFixSplitBar;


public:
	__stdcall CDivideView( void );
	virtual __stdcall ~CDivideView( void );

virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);

DECLARE_MESSAGE_MAP()
afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


class CGuiManager
{

public:
	CDivideView* __stdcall GetItem( FORM_TYPE );
public:
	BOOL __stdcall Initialize( CWnd* pWnd );
	void __stdcall Terminate( void );
	void __stdcall ArragePositon( void );

private:
	std::vector<CDivideView*> m_FormList;		

public:
	CGuiManager(void);
	~CGuiManager(void);

public:
}; 



}
using namespace NAME_GUI_MANAGER;

extern CGuiManager* GuiMgr;



