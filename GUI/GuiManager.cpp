//#include "windef.h"
#include "stdafx.h"
#include "GuiManager.h"

CGuiManager* GuiMgr = NULL;

BEGIN_MESSAGE_MAP(NAME_GUI_MANAGER::CDivideView, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



__stdcall CDivideView::CDivideView( void )
{
	m_CurrFormInfor.Clear();
	m_bFixSplitBar = TRUE; 
}
__stdcall CDivideView::~CDivideView( void )
{
	DeleteView();
}

BOOL __stdcall CDivideView::AddView( UINT FormID, int nRow, int nCol, CSize Size, CRuntimeClass * pViewClass, CCreateContext* pContext )
{
	if( IsExistView( FormID ) == TRUE )
		return FALSE;
	
	if( GetWndbyPane ( nRow, nCol ) != NULL )
	{
		HideView( GetFormIDbyPane( nRow, nCol ) );
	}
	
	if( CreateView( nRow, nCol, pViewClass, Size, pContext ) == TRUE )  // Default
	{
		FORM_INFOR* FormInfor = new FORM_INFOR;
		
		if( FormInfor != NULL )
		{
			if( nCol == 0 )
			{
				m_lCurInforPanelFormID = FormID;
			}
			else
			{
				m_lCurCmdPanelFormID = FormID;
			}
			FormInfor->FormID = FormID;
			FormInfor->PaneID = MAKELONG( nRow, nCol );		
			FormInfor->pWnd = GetPane( nRow, nCol );
			FormInfor->bShow = TRUE;
			
			m_MapViews.insert( std::map< long, FORM_INFOR* >::value_type( FormID, FormInfor ) );	
			ShowView( FormID );
			return true;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

void __stdcall CDivideView::DeleteView( void )
{
	std::map<long, FORM_INFOR*>::iterator itr;
	FORM_INFOR* Item;
	for( itr = m_MapViews.begin(); itr != m_MapViews.end(); ++itr )
	{
		Item = ( *itr ).second;
		delete Item;
	}
	m_MapViews.clear();
}

BOOL __stdcall CDivideView::IsExistView( long lFormId )
{
	std::map< long, FORM_INFOR* >::iterator itr;
	itr = m_MapViews.find( lFormId );
	return itr!=m_MapViews.end() ? TRUE : FALSE;
}

BOOL __stdcall CDivideView::ChangeView( int nInforPanelFormID, int nCmdPanelID)
{
	if( IsExistView ( nInforPanelFormID ) == FALSE )
		return FALSE;

	if( nInforPanelFormID != m_lCurInforPanelFormID )
	{
		HideView( m_lCurInforPanelFormID );
		ShowView( nInforPanelFormID );
		m_lCurInforPanelFormID = nInforPanelFormID;
		RecalcLayout();
	}	
	else 
	{
		//ShowView( nInforPanelFormID );
		m_lCurInforPanelFormID = nInforPanelFormID;
		//RecalcLayout();

	}

	
	if( m_lCurCmdPanelFormID != nCmdPanelID )
	{
		HideView( m_lCurCmdPanelFormID );
		ShowView( nCmdPanelID );
		m_lCurCmdPanelFormID = nCmdPanelID;
		RecalcLayout();
	}	
	
	else
	{
		//ShowView( nCmdPanelID );
		m_lCurCmdPanelFormID = nCmdPanelID;
		//RecalcLayout();
	}
	
	
	return TRUE;
}
BOOL __stdcall CDivideView::ShowView( long lFormId)
{
	std::map<long, FORM_INFOR*>::iterator itr;

	itr = m_MapViews.find( lFormId );

	if( itr != m_MapViews.end() )
	{
		CPoint p( (*itr).second->PaneID );

		if( (*itr).second->bShow == FALSE )
		{
			//CWnd* pWnd = (*itr).second->pWnd;			
			//CWnd* pWnd = GetDlgItem(IdFromRowCol(p.x,p.y));		//--> Assert 발생 원인 불명 ( Inital 할때 는 문제 없다가 다시 할당할때 문제 발생 )  		

			(*itr).second->pWnd->SetDlgCtrlID( IdFromRowCol( p.x, p.y ) );
			(*itr).second->pWnd->ShowWindow( SW_SHOW );
			(*itr).second->bShow = TRUE;
			return TRUE;
		}
		else 
			return FALSE;
	}
	else 
		return FALSE;
}

BOOL __stdcall CDivideView::HideView( long lFormId )
{
	std::map<long, FORM_INFOR*>::iterator itr;
	itr = m_MapViews.find( lFormId );

	if( itr != m_MapViews.end() )
	{		
		if( (*itr).second->bShow == TRUE )
		{
			CPoint p( (*itr).second->PaneID );
			CWnd* pWnd = GetPane( p.x, p.y );
			pWnd->SetDlgCtrlID( 0 );
			pWnd->ShowWindow( SW_HIDE );
			(*itr).second->bShow = FALSE;
			return TRUE;
		}
	}
	else 
		return FALSE;
	return FALSE;
}

CWnd* __stdcall CDivideView::GetWndbyPane( int x, int y )
{
	std::map<long, FORM_INFOR*>::iterator itr;
	for( itr = m_MapViews.begin(); itr != m_MapViews.end(); ++itr )
	{
		CPoint p( (*itr).second->PaneID );
		if( p.x == x && p.y == y && (*itr).second->bShow == TRUE )
			return GetPane(x, y);
	}
	return NULL;	
}

CWnd* __stdcall CDivideView::GetWndbyFormID ( long lFormId )
{
	
	std::map<long, FORM_INFOR*>::iterator itr;
	for( itr = m_MapViews.begin(); itr != m_MapViews.end(); ++itr )
	{
		if( (*itr).second->FormID == lFormId )
			return (CWnd*) (( *itr ).second->pWnd );
	}
	return NULL;
}
long __stdcall CDivideView::GetFormIDbyPane( int x, int y )
{
	std::map<long, FORM_INFOR*>::iterator itr;
	for( itr = m_MapViews.begin(); itr != m_MapViews.end(); ++itr )
	{
		CPoint p( ( *itr ).second->PaneID );
		if( p.x == x && p.y == y && ( *itr ).second->bShow == TRUE )
			return ( *itr ).second->FormID;
	}
	return -1;
}

void CDivideView::SetSplitBarSize( int iBar, int iBorder )
{
	if(iBar != 0)
	{
		iBar = 1;
	}
	m_cxSplitter	= m_cySplitter		= iBar;
	m_cxSplitterGap	= m_cySplitterGap	= iBar;
	m_cxBorder		= m_cyBorder		= iBorder;
	RecalcLayout();
}
void __stdcall CDivideView::SetFixSplitBar( BOOL bEnable )
{
	m_bFixSplitBar = bEnable;
}


/*********************************************************************************/

CGuiManager::CGuiManager(void)
{
}

CGuiManager::~CGuiManager(void)
{
	Terminate();
}

BOOL __stdcall CGuiManager::Initialize( CWnd* pWnd  )
{
	for( int i = 0; i< WND_SPLITTER_MAX; i++ )
	{
		CDivideView* Item = new CDivideView();
		if( Item != NULL )
			m_FormList.push_back( Item );
	}
	
	//NavigationPanel 사용시
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->CreateStatic( pWnd, 3, 1);
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->CreateStatic( GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL ), 1, 2, WS_CHILD | WS_VISIBLE, 
															GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->IdFromRowCol(1, 0) );
															

	//NavigationPanel 미사용시
	/*
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->CreateStatic( pWnd, 2, 1);
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->CreateStatic( GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL ), 1, 2, WS_CHILD | WS_VISIBLE, 
   														GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->IdFromRowCol(1, 0) );
	*/
	return true;
}

void __stdcall CGuiManager::Terminate( void )
{

	std::vector< CDivideView* >::iterator m_FormList_itr;
	for( m_FormList_itr = m_FormList.begin(); m_FormList_itr != m_FormList.end(); ++m_FormList_itr )
	{
		delete ( CDivideView* ) ( *m_FormList_itr );
	}
	m_FormList.clear();
}

CDivideView* __stdcall CGuiManager::GetItem( FORM_TYPE nType )
{
	if( nType >= WND_SPLITTER_MAX )
		return NULL;
	if( m_FormList.empty() )
		return NULL;
	
	std::vector< CDivideView* >::iterator m_FormList_itr;
	m_FormList_itr = m_FormList.begin() + ( unsigned int )nType;	
	
	return (*m_FormList_itr);
}

void __stdcall CGuiManager::ArragePositon( void )
{	
	int nFormWidth = GetSystemMetrics(SM_CXFULLSCREEN);;
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->SetSplitBarSize(1, 2);
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->SetSplitBarSize(1, 2);

	GetItem( WND_SPLITTER_HORIZONTAL)->SetRowInfo(0, GUI_TITLE_HEIGHT, GUI_TITLE_HEIGHT );
	GetItem( WND_SPLITTER_HORIZONTAL)->SetRowInfo(1, ( GUI_WINDOWS_HEIGHT - GUI_TITLE_HEIGHT - GUI_NAVI_HEIGHT ), ( GUI_WINDOWS_HEIGHT - GUI_TITLE_HEIGHT - GUI_NAVI_HEIGHT ) );
	if(nFormWidth <= 1500)
	{
		GetItem( WND_SPLITTER_VERTICAL)->SetColumnInfo( 0, 1300 - GUI_CMD_WIDTH, 1300 - GUI_CMD_WIDTH );
	} else
	{
		GetItem( WND_SPLITTER_VERTICAL)->SetColumnInfo( 0, GUI_WINDOWS_WIDTH - GUI_CMD_WIDTH, GUI_WINDOWS_WIDTH - GUI_CMD_WIDTH );
	}
}

void NAME_GUI_MANAGER::CDivideView::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pDC == NULL)
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}


	COLORREF m_bColor = 0;
	CRect rect = rectArg;
	int CX_BORDER = 1, CY_BORDER = 1;
	if(nType == splitBar) //nType == splitBorder
	{
		//COLORREF clr = RGB_MAIN;
		pDC->Draw3dRect(rect, m_bColor, m_bColor);
		rect.InflateRect(-CX_BORDER, -CY_BORDER);
		//pDC->FillSolidRect(rect, m_bColor);
		return;
	}
	else if(nType == splitBorder)
	{
		pDC->Draw3dRect(rect, m_bColor, m_bColor);
		rect.InflateRect(-CX_BORDER, -CY_BORDER);
		pDC->Draw3dRect(rect, m_bColor, m_bColor);
		//pDC->FillSolidRect(rect, m_bColor);
		return;
	}
	else
	{
		CSplitterWnd::OnDrawSplitter(pDC, nType, rectArg);
	}
	pDC->FillSolidRect(rectArg, m_bColor);
	//}

}


void NAME_GUI_MANAGER::CDivideView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bFixSplitBar)	CWnd::OnMouseMove(nFlags, point);
	else				CSplitterWnd::OnMouseMove(nFlags, point);
}
void NAME_GUI_MANAGER::CDivideView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bFixSplitBar)	CWnd::OnLButtonDown(nFlags, point);
	else				CSplitterWnd::OnLButtonDown(nFlags, point);
}

