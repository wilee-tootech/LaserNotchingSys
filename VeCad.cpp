// VeCad.cpp: implementation of the CVeCad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Modena02.h"
#include "VeCad.h"

#include "Trimmer.h"
#include "DFont.h"
#include "vlEntity.h"

//#include "DlgOffsetSize.h"
#include "GUtility.h"

//#include "NoView.h"
// 2003.02.12   필드 셋팅
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CMruList	g_MruList;

//-- REX 6.05
bool	CVeCad::m_bExplode	= false;

CArray<CvlEntity*, CvlEntity*>	CVeCad::m_ExpAddArray;
CArray<CvlLine*, CvlLine*>		CVeCad::m_GuideLineArray;
CArray<CvlRect*, CvlRect*>		CVeCad::m_GuideRectArray;

CVeCad::CVeCad()
{	
	m_pTrim				= NULL;
	m_bModified			= false;
	m_bClosed			= true;
	
	m_bGuideVert		= false;
	m_bGuideLine		= false;
	m_bGuideAdd			= true;
	m_bDisableCloseQuery= false;
	m_bGridShow			= true;

	m_bAddingEnt		= false;

	memset(m_szFileName,0, sizeof(char)*MAX_PATH);
	memset(m_bSnapMode,	0, sizeof(bool)*SNAPMODE);

	memset(m_szJumpLineDesc, 0, sizeof(char)*30);
	
	m_ColJumpVector		= RGB(0,128,128);
	m_dJumpLineWidth	= 0.0;
	m_dJumpDotInterval	= 0.0;

	m_fSnapAngle		= 45.0/180*M_PI;

	m_nMsgWait			= 0;
	m_bMsgWait			= false;

	m_nMenuID			= 0;

	m_pNoView			= NULL;
}

CVeCad::~CVeCad()
{
	delete m_pTrim;

}

void CVeCad::CanvasClose()
{
	if (IsClosed()==false)
	{
		GridUpdate(true);

		m_bDisableCloseQuery = true;
		vlExecute( VC_FILE_CLOSE );
		m_bDisableCloseQuery = false;
		
		m_szFileName[0] = NULL;
		m_bClosed = true;
	}

	RemoveAllGuideLine();
	EnableGuideLine(false);

	// Guide rect 제거.
	int Size = m_GuideRectArray.GetSize();
	
	for (int i=0; i<Size; i++)
	{
		CvlRect* pRect = m_GuideRectArray.GetAt(i);
		pRect->Erase();
		delete pRect;
	}

	m_GuideRectArray.RemoveAll();

	ReleaseNoView();

}

// 
void CVeCad::CanvasInit()
{
	// Add Dot Line Style , Jump Vector 스타일 복원
	vlStLineAdd("DOT", m_szJumpLineDesc);//"0.2,-0.2");

	// GUIDE Layer Setting
	int nIndexOld	= vlLayerIndex( NULL, 0 );
	int nIndexNew	= vlLayerAdd( "GUIDE", 0.25, RGB(128,128,255), VL_COL_BLACK );
	
	// 2003.02.18   이민씨와 협의 후
	if (nIndexNew>=0)
		vlPropPutInt( VD_LAYER_LOCK, nIndexNew, 1 );// ReadOnly

	SetLineType(SOLID_LINE);
	
	//////////////////////////////////////////////////////////////////////////
	vlUpdate();	

	vlLayerActive( nIndexOld );
	Zoom(VC_ZOOM_ALL);
	vlRedraw();

	// 이전에 만들어진 Canvas 와 같게 그리드 설정 복원
	GridUpdate(false);
	// 이전에 만들어진 Canvas 와 같게 Snap 설정 복원
	InitSnap();

	m_bModified = false;
}

//-----------------------------------------------
bool CVeCad::CanvasNew()
{
	if (CloseQuery()==false)
		return false;

	CanvasClose();
	
	bool bRet = true;
	
	if ( vlFileNew( m_hVec, _T("") ) >= 0 )
	{
		m_szFileName[0] = NULL;
		m_bClosed = false;

		CanvasInit();

		m_bModified = false;
		bRet = true;
	}
	else
		bRet = false;

	return bRet;
}

//-----------------------------------------------
void CVeCad::CanvasCreate(HWND hWndMain)
{
	// Create VeCAD toolbar
	m_hMain = hWndMain;

	m_VecX = 0;
	m_VecY = 0;
	
	// Create VeCAD	window, size will be set in OnSize()
	m_hVec = vlWndCreate( hWndMain, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, 0,0,400,300);

	//Create StatusBar
	int SBarH = 0;
	vlStatBarCreate( AfxGetMainWnd()->m_hWnd, &SBarH );
	
	vlPropPut( VD_WND_EMPTYTEXT, (int)m_hVec, "HK FontCAD" );

	long Style = ::GetWindowLong(m_hVec, GWL_STYLE);
	Style &= ~WS_BORDER;
	::SetWindowLong(m_hVec, GWL_STYLE, Style);	

	m_szFileName[0] = NULL;
}
//-----------------------------------------------
void CVeCad::Print() 
{
	vlExecute( VC_PRINT );
}
//-----------------------------------------------
void CVeCad::Reset()
{
	vlExecute( VC_RESET );
}
//-----------------------------------------------
void CVeCad::LineWidth()
{
	vlExecute( VC_SHOWLINEW );
}

//***********************************************
void CVeCad::DrawLine() 
{
	vlExecute( VC_DRAW_LINE );	
}
//-----------------------------------------------
void CVeCad::DrawPolyline() 
{
	vlExecute( VC_DRAW_POLYLINE );	
}
//-----------------------------------------------
void CVeCad::DrawSpline() 
{
	vlExecute( VC_DRAW_SPLINE );	
}
//-----------------------------------------------
void CVeCad::DrawPoint() 
{
	vlExecute( VC_DRAW_POINT );
}
//-----------------------------------------------
void CVeCad::DrawCircCR() 
{
	vlExecute( VC_DRAW_CIRC_CR );
}
//-----------------------------------------------
void CVeCad::DrawCircCD() 
{
	vlExecute( VC_DRAW_CIRC_CD );
}
//-----------------------------------------------
void CVeCad::DrawCirc2P() 
{
	vlExecute( VC_DRAW_CIRC_2P );
}
//-----------------------------------------------
void CVeCad::DrawCirc3P() 
{
	vlExecute( VC_DRAW_CIRC_3P );
}
//-----------------------------------------------
void CVeCad::DrawArcCSE()
{
	vlExecute( VC_DRAW_ARC_CSE );
}
//-----------------------------------------------
void CVeCad::DrawArcSEM()
{
	vlExecute( VC_DRAW_ARC_SEM );
}
//-----------------------------------------------
void CVeCad::DrawArcSME()
{
	vlExecute( VC_DRAW_ARC_SME );
}
//-----------------------------------------------
void CVeCad::DrawEllipse() 
{
	vlExecute( VC_DRAW_ELLIPSE );
}
//-----------------------------------------------
void CVeCad::DrawRect() 
{
	vlExecute( VC_DRAW_RECT );
}
//-----------------------------------------------
void CVeCad::DrawHatch() 
{
	vlExecute( VC_DRAW_HATCH );
}
//-----------------------------------------------
void CVeCad::DrawDimHor()
{
	vlExecute( VC_DRAW_DIM_HOR );
}
//-----------------------------------------------
void CVeCad::DrawDimVer()
{
	vlExecute( VC_DRAW_DIM_VER );
}
//-----------------------------------------------
void CVeCad::DrawDimPar()
{
	vlExecute( VC_DRAW_DIM_PAR );
}
//-----------------------------------------------
void CVeCad::DrawDimAng()
{
	vlExecute( VC_DRAW_DIM_ANG );
}
//-----------------------------------------------
void CVeCad::DrawDimRad()
{
	vlExecute( VC_DRAW_DIM_RAD );
}
//-----------------------------------------------
void CVeCad::DrawDimDiam()
{
	vlExecute( VC_DRAW_DIM_DIAM );
}
//-----------------------------------------------
void CVeCad::DrawDimOrd()
{
	vlExecute( VC_DRAW_DIM_ORD );
}
//***********************************************
void CVeCad::Zoom(double dZoomFactor) 
{
	if (dZoomFactor >= VC_ZOOM_ALL &&
		dZoomFactor <= VC_ZOOM_SEL)
		vlExecute((int)dZoomFactor);
	else
		vlZoom( dZoomFactor );
}

//***********************************************
void CVeCad::EditCbCut() 
{
	vlExecute( VC_EDIT_CBCUT );
}
//-----------------------------------------------
void CVeCad::EditCbCopy() 
{
	vlExecute( VC_EDIT_CBCOPY );
}
//-----------------------------------------------
void CVeCad::EditCbPaste() 
{
	vlExecute( VC_EDIT_CBPASTE );
}
//-----------------------------------------------
void CVeCad::EditEntprop() 
{
	vlExecute( VC_EDIT_ENTPROP );
}
//-----------------------------------------------
void CVeCad::EditRedo() 
{
	vlExecute( VC_EDIT_REDO );
}
//-----------------------------------------------
void CVeCad::EditUndo() 
{
	vlExecute( VC_EDIT_UNDO );
}
//-----------------------------------------------
void CVeCad::EditCopy() 
{
	vlExecute( VC_EDIT_COPY );
}
//-----------------------------------------------
void CVeCad::EditTrim() 
{
	vlExecute( VC_EDIT_TRIM );
}
//-----------------------------------------------
void CVeCad::EditScale() 
{
	vlExecute( VC_EDIT_SCALE );
}
//-----------------------------------------------
void CVeCad::EditCreblock() 
{
	vlExecute( VC_EDIT_CREBLOCK );
}
//-----------------------------------------------
void CVeCad::EditErase() 
{
	vlExecute( VC_EDIT_ERASE );
}
//-----------------------------------------------
void CVeCad::EditExplode() 
{
	vlExecute( VC_EDIT_EXPLODE );
}
//-----------------------------------------------
void CVeCad::EditExtend() 
{
	vlExecute( VC_EDIT_EXTEND );
}
//-----------------------------------------------
void CVeCad::EditFillet() 
{
	vlExecute( VC_EDIT_FILLET );
}
//-----------------------------------------------
void CVeCad::EditMirror() 
{
	vlExecute( VC_EDIT_MIRROR );
}
//-----------------------------------------------
void CVeCad::EditMove() 
{
	vlExecute( VC_EDIT_MOVE );
}
//-----------------------------------------------
void CVeCad::EditRotate() 
{
	vlExecute( VC_EDIT_ROTATE );
}

//-----------------------------------------------
void CVeCad::InsText() 
{
	vlExecute( VC_INS_TEXT );	
}
//-----------------------------------------------
void CVeCad::InsSymbol() 
{
	vlExecute( VC_INS_SYMBOL );	
}
//-----------------------------------------------
void CVeCad::InsBlock() 
{
	vlExecute( VC_INS_BLOCK );
}
//-----------------------------------------------
void CVeCad::InsImage() 
{
	vlExecute( VC_INS_IMAGE );
}
//-----------------------------------------------
void CVeCad::InsRMap() 
{
	vlExecute( VC_INS_RMAP );
}
//***********************************************

void CVeCad::FmtLayout(int iCmd)
{
	ASSERT(	iCmd == VC_FMT_LAYOUT	||		iCmd == VC_FMT_PAGE		||		iCmd == VC_FMT_LAYER	||			iCmd == VC_FMT_STLINE	||
			iCmd == VC_FMT_STTEXT	|| 		iCmd == VC_FMT_STDIM	||		iCmd == VC_FMT_STPOINT	|| 			iCmd == VC_FMT_STHATCH	|| 
			iCmd == VC_FMT_BLOCK	|| 		iCmd == VC_FMT_GRID		||		iCmd == VC_FMT_OSNAP	|| 			iCmd == VC_FMT_PSNAP	||	
			iCmd == VC_FMT_UNITS	||		iCmd == VC_FMT_PRIVATE	||		iCmd == VC_FMT_PREFERS	||			iCmd == VC_FMT_MLINE);

	vlExecute(iCmd);
}

//***********************************************
void CVeCad::ToolDist () 
{
	vlExecute( VC_TOOL_DIST );
}
//-----------------------------------------------
void CVeCad::ToolPrnRect () 
{
	vlExecute( VC_TOOL_PRNRECT );
}
//-----------------------------------------------
void CVeCad::ToolStat () 
{
	vlExecute( VC_TOOL_STAT );
}
//-----------------------------------------------
void CVeCad::SelByPoint () 
{
	vlExecute( VC_SEL_BYPOINT );
}
//-----------------------------------------------
void CVeCad::SelByRect () 
{
	vlExecute( VC_SEL_BYRECT );
}
//-----------------------------------------------
void CVeCad::SelByPolygon () 
{
	vlExecute( VC_SEL_BYPOLYGON );
}
//-----------------------------------------------
void CVeCad::InsGlass() 
{
	vlExecute( VC_INS_GLASS );
}

void CVeCad::Resize(int xStart, int yStart, int cx, int cy)
{
	vlWndResize( m_hVec, m_VecX+xStart, m_VecY+yStart, cx-m_VecX, cy-m_VecY-m_SBarH );
	vlStatBarResize();
}

void CVeCad::SetFocus()
{
	vlSetFocus();
}

void CVeCad::InitVeCad()
{
	// Register your copy of Vecad.dll
	vlRegistration( 1843258482 );
	// Set message handler function
	vlSetMsgHandler( DwgProc );
	
	m_pTrim = new CTrimmer;
}

int CALLBACK CVeCad::DwgProc (int /*iDwg*/, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5)
{

	//DEBUG
//	if (Msg==VM_ENTEXPLODE)
//		TRACE("");

	TCHAR		szStr[256] = {0,};
	double		x, 
				y, 
				w, 
				h, 
				scx, 
				scy;
	int			BmpW, 
				BmpH;
	HBITMAP		hImage;

	if (Msg!=VM_MOUSEMOVE && Msg!=VM_STATUSTEXT && Msg!=VM_TOOLDRAG &&
		Msg!=VM_GETSTRING && Msg!=VM_BEGINPAINT && Msg!=VM_ENDPAINT )
	{
		char szMsg[256] = {0,};
		char szCmd[64]	= {0,};

		if (CVeCad::FormatVeCadMsg(Msg, szMsg)==true)
		{
			if (CVeCad::FormatVeCadCmd(Prm1, szCmd)==true)
				sprintf(szMsg, "%s \t%s\t%d", szMsg, szCmd, Prm2);
		}

		strcat(szMsg, "\n");
		TRACE(szMsg);
	}

	if (g_Vl.m_bMsgWait==true && Msg==g_Vl.m_nMsgWait)
		g_Vl.m_bMsgWait = false;

	bool	bNoViewChange = false;

	switch( Msg )
	{
	case VM_CLOSEQUERY:

		if (g_Vl.m_bDisableCloseQuery==false)
			g_Vl.CloseQuery();

		return TRUE;

    case VM_ERROR:
		break;
		
    case VM_GETSTRING:
		break;
		
    case VM_ZOOM:
		bNoViewChange = true;
		break;
		
    case VM_MOUSEMOVE:
		break;
		
    case VM_ENDPAINT:
		// this message are sent just after VeCAD finish redraw entities from VEC file
		// here we can use vlDraw... functions
		
		// load some image
		BmpW = 500;   // I take this value, but you must know real size of your bitmap
		BmpH = 500;
		hImage = (HBITMAP)LoadImage( NULL, "c:\\abc123.bmp", IMAGE_BITMAP, BmpW, BmpH, LR_LOADFROMFILE );
		if (hImage)
		{
			// get left cottom corner of the current drawing (-1)
			x = vlPropGetDbl( VD_DWG_LEFT, -1 );
			y = vlPropGetDbl( VD_DWG_BOTTOM, -1 );
			// get size of drawing
			w = vlPropGetDbl( VD_DWG_WIDTH, -1 );
			h = vlPropGetDbl( VD_DWG_HEIGHT, -1 );
			// calculate scale value, in order bitmap takes 1/4 of drawing size
			// pixels per drawing's unit
			scx = BmpW / w * 4;
			scy = BmpH / h * 4;
			// draw bitmap here
			vlDrawBitmap( hImage, BmpW, BmpH, x,y, scx, scy );
			DeleteObject( hImage ); 
		}
		break;
		
    case VM_OBJACTIVE:
		if (Prm1==VL_OBJ_PAGE)
		{
			TRACE("Update Main Title\n");
			//pMain->UpdateMainTitle();
		}
		break;
		
    case VM_DWGLOADED:
    case VM_DWGSAVED:
//		g_MruList.Add( (LPCTSTR)Prm5 );
		AfxGetApp()->AddToRecentFileList( (LPCTSTR)Prm5 );		
 
	case VM_DWGSELECT:
		TRACE("Update Main Title\n");
//		pMain->UpdateMainTitle();
		break;
		
    case VM_DWGLOADING:
    case VM_DWGSAVING:
		_stprintf( szStr, _T("Loading: %d%%"), Prm1 );
		vlStatBarSetText( VL_SB_COORD, szStr );
		break;

	case VM_ENTADD:
	case VM_ENTCOPY:
		g_Vl.OnEntityAdd(Prm2);		
		break;

	case VM_GRIPMOVE:
		g_Vl.m_bModified = true;
		::SendMessage( AfxGetMainWnd()->GetSafeHwnd() , WM_UPDATE_MAIN_TITLE, 0,0);
		break;

    case VM_EXECUTE:
		g_Vl.OnExecute(Prm1, Prm2, Prm3, Prm4);
		break;
		
	case VM_EXECUTED:
		switch(Prm1)
		{
		case VC_FMT_GRID:		
			g_Vl.GridUpdate(true);
			break;

		case VC_SHOWGRID:
			g_Vl.m_bGridShow = !g_Vl.m_bGridShow;
			break;

		case VC_RESET:
			g_Vl.m_pTrim->Free();
			g_Vl.EnableGuideLine(false);

			if (g_Vl.m_pNoView)
				g_Vl.ReleaseNoView();
			break;
		}

		break;
 
    case VM_TOOLOPEN:
		if (Prm1==VC_CUSTOM+1)
			return 1;
		break;
		
    case VM_TOOLCLICK:
		if (Prm1==VC_CUSTOM+1)
			MessageBox( 0, "aaa", "qqq", MB_OK );
		break;
	
	// Trimming 구현을 위해 추가한 부분.
	//<------------여기서부터.
    case VM_LBDOWN:
		if (g_Vl.OnLButtonDown(Prm1, Prm2, Prm3, Prm4)==true)
			return 1;

		break;

	case VM_RBDOWN:
		if (g_Vl.OnRButtonDown(Prm1, Prm2, Prm3, Prm4)==true )
			return 1;

	case VM_KEYUP:
		bNoViewChange = true;
		g_Vl.OnKeyUp(Prm1, Prm2);
		break;
	case VM_KEYDOWN:
		g_Vl.OnKeyDown(Prm1, Prm2);
		break;

	case VM_MENUEDIT:
		if (g_Vl.m_bAddingEnt == false && g_Vl.m_nMenuID!=0 && g_Vl.OnMenuEdit(Prm1, Prm2, Prm3, Prm4)==true)
			return 1;

		break;

	case VM_RASTER:
		return 1;

	case VM_WINRESIZE:
		bNoViewChange = true;

		break;
	}
	//<---------------여기까지...

//	if (bNoViewChange == true && g_Vl.m_pNoView)
//		g_Vl.m_pNoView->PostMessage( WM_UPDATE_NO );

	return 0;
}


bool CVeCad::FormatVeCadCmd(UINT nCmd, LPTSTR szParam)
{
	switch(nCmd)
	{
	case VL_OBJ_PAGE      :	sprintf ( szParam, "VL_OBJ_PAGE      ");	break;
	case VL_OBJ_LAYER     :	sprintf ( szParam, "VL_OBJ_LAYER     ");	break;
	case VL_OBJ_STLINE    :	sprintf ( szParam, "VL_OBJ_STLINE    ");	break;
	case VL_OBJ_MLINE     :	sprintf ( szParam, "VL_OBJ_MLINE     ");	break;
	case VL_OBJ_STTEXT    :	sprintf ( szParam, "VL_OBJ_STTEXT    ");	break;
	case VL_OBJ_STHATCH   :	sprintf ( szParam, "VL_OBJ_STHATCH   ");	break;
	case VL_OBJ_STDIM     :	sprintf ( szParam, "VL_OBJ_STDIM     ");	break;
	case VL_OBJ_STPOINT   :	sprintf ( szParam, "VL_OBJ_STPOINT   ");	break;
	case VL_OBJ_GRPOINT   :	sprintf ( szParam, "VL_OBJ_GRPOINT   ");	break;
	case VL_OBJ_VIEW      :	sprintf ( szParam, "VL_OBJ_VIEW      ");	break;
	case VL_OBJ_PRNRECT   :	sprintf ( szParam, "VL_OBJ_PRNRECT   ");	break;
	case VL_OBJ_BLOCK     :	sprintf ( szParam, "VL_OBJ_BLOCK     ");	break;

	case VL_ENT_POINT     :	sprintf ( szParam, "VL_ENT_POINT     ");	break;
	case VL_ENT_LINE      :	sprintf ( szParam, "VL_ENT_LINE      ");	break;
	case VL_ENT_POLY      :	sprintf ( szParam, "VL_ENT_POLY      ");	break;
	case VL_ENT_CIRCLE    :	sprintf ( szParam, "VL_ENT_CIRCLE    ");	break;
	case VL_ENT_ARC       :	sprintf ( szParam, "VL_ENT_ARC       ");	break;
	case VL_ENT_ARC2      :	sprintf ( szParam, "VL_ENT_ARC2      ");	break;
	case VL_ENT_ELLIPSE   :	sprintf ( szParam, "VL_ENT_ELLIPSE   ");	break;
	case VL_ENT_TEXT      :	sprintf ( szParam, "VL_ENT_TEXT      ");	break;
	case VL_ENT_BITMAP    :	sprintf ( szParam, "VL_ENT_BITMAP    ");	break;
	case VL_ENT_INSBLOCK  :	sprintf ( szParam, "VL_ENT_INSBLOCK  ");	break;
	case VL_ENT_HATCH     :	sprintf ( szParam, "VL_ENT_HATCH     ");	break;
	case VL_ENT_FLOOD     :	sprintf ( szParam, "VL_ENT_FLOOD     ");	break;
	case VL_ENT_RECT      :	sprintf ( szParam, "VL_ENT_RECT      ");	break;
	case VL_ENT_DIMLIN    :	sprintf ( szParam, "VL_ENT_DIMLIN    ");	break;
	case VL_ENT_DIMANG    :	sprintf ( szParam, "VL_ENT_DIMANG    ");	break;
	case VL_ENT_DIMRAD    :	sprintf ( szParam, "VL_ENT_DIMRAD    ");	break;
	case VL_ENT_DIMDIAM   :	sprintf ( szParam, "VL_ENT_DIMDIAM   ");	break;
	case VL_ENT_DIMORD    :	sprintf ( szParam, "VL_ENT_DIMORD    ");	break;
	case VL_ENT_INSDWG    :	sprintf ( szParam, "VL_ENT_INSDWG    ");	break;
	case VL_ENT_CUSTOM    :	sprintf ( szParam, "VL_ENT_CUSTOM    ");	break;


	case VC_FILE_NEW		:	sprintf ( szParam, "VC_FILE_NEW        ");	break;
	case VC_FILE_OPEN       :	sprintf ( szParam, "VC_FILE_OPEN       ");	break;
	case VC_FILE_SAVE       :	sprintf ( szParam, "VC_FILE_SAVE       ");	break;
	case VC_FILE_SAVEAS     :	sprintf ( szParam, "VC_FILE_SAVEAS     ");	break;
	case VC_FILE_CLOSE      :	sprintf ( szParam, "VC_FILE_CLOSE      ");	break;
	case VC_FILE_CLOSEALL   :	sprintf ( szParam, "VC_FILE_CLOSEALL   ");	break;
	case VC_FILE_LIST       :	sprintf ( szParam, "VC_FILE_LIST       ");	break;
	case VC_IMPORT_DXF      :	sprintf ( szParam, "VC_IMPORT_DXF      ");	break;
	case VC_IMPORT_VDF      :	sprintf ( szParam, "VC_IMPORT_VDF      ");	break;
	case VC_IMPORT_HPGL     :	sprintf ( szParam, "VC_IMPORT_HPGL     ");	break;
	case VC_IMPORT_CNC      :	sprintf ( szParam, "VC_IMPORT_CNC      ");	break;
	case VC_IMPORT_DP1      :	sprintf ( szParam, "VC_IMPORT_DP1      ");	break;
	case VC_IMPORT_AVSHP    :	sprintf ( szParam, "VC_IMPORT_AVSHP    ");	break;
	case VC_EXPORT_DXF      :	sprintf ( szParam, "VC_EXPORT_DXF      ");	break;
	case VC_EXPORT_HPGL     :	sprintf ( szParam, "VC_EXPORT_HPGL     ");	break;
	case VC_EXPORT_CNC      :	sprintf ( szParam, "VC_EXPORT_CNC      ");	break;
	case VC_EXPORT_BMP      :	sprintf ( szParam, "VC_EXPORT_BMP      ");	break;
	case VC_EXPORT_AVSHP    :	sprintf ( szParam, "VC_EXPORT_AVSHP    ");	break;
	case VC_PRINT           :	sprintf ( szParam, "VC_PRINT           ");	break;
		
	case VC_ZOOM_ALL        :	sprintf ( szParam, "VC_ZOOM_ALL        ");	break;
	case VC_ZOOM_WIN        :	sprintf ( szParam, "VC_ZOOM_WIN        ");	break;
	case VC_ZOOM_PAN        :	sprintf ( szParam, "VC_ZOOM_PAN        ");	break;
	case VC_ZOOM_PAGE       :	sprintf ( szParam, "VC_ZOOM_PAGE       ");	break;
	case VC_ZOOM_IN         :	sprintf ( szParam, "VC_ZOOM_IN         ");	break;
	case VC_ZOOM_OUT        :	sprintf ( szParam, "VC_ZOOM_OUT        ");	break;
	case VC_ZOOM_LEFT       :	sprintf ( szParam, "VC_ZOOM_LEFT       ");	break;
	case VC_ZOOM_RIGHT      :	sprintf ( szParam, "VC_ZOOM_RIGHT      ");	break;
	case VC_ZOOM_UP         :	sprintf ( szParam, "VC_ZOOM_UP         ");	break;
	case VC_ZOOM_DOWN       :	sprintf ( szParam, "VC_ZOOM_DOWN       ");	break;
	case VC_ZOOM_PREV       :	sprintf ( szParam, "VC_ZOOM_PREV       ");	break;
	case VC_ZOOM_SEL        :	sprintf ( szParam, "VC_ZOOM_SEL        ");	break;
	case VC_PAGE_NEXT       :	sprintf ( szParam, "VC_PAGE_NEXT       ");	break;
	case VC_PAGE_PREV       :	sprintf ( szParam, "VC_PAGE_PREV       ");	break;
	case VC_PAGE_FIRST      :	sprintf ( szParam, "VC_PAGE_FIRST      ");	break;
	case VC_PAGE_LAST       :	sprintf ( szParam, "VC_PAGE_LAST       ");	break;
	case VC_PAGE_DLG        :	sprintf ( szParam, "VC_PAGE_DLG        ");	break;
	case VC_VIEW_SAVE       :	sprintf ( szParam, "VC_VIEW_SAVE       ");	break;
	case VC_VIEW_LIST       :	sprintf ( szParam, "VC_VIEW_LIST       ");	break;
		
	case VC_DRAW_POINT      :	sprintf ( szParam, "VC_DRAW_POINT      ");	break;
	case VC_DRAW_LINE       :	sprintf ( szParam, "VC_DRAW_LINE       ");	break;
	case VC_DRAW_POLYLINE   :	sprintf ( szParam, "VC_DRAW_POLYLINE   ");	break;
	case VC_DRAW_SPLINE     :	sprintf ( szParam, "VC_DRAW_SPLINE     ");	break;
	case VC_DRAW_CIRC_CR    :	sprintf ( szParam, "VC_DRAW_CIRC_CR    ");	break;
	case VC_DRAW_CIRC_CD    :	sprintf ( szParam, "VC_DRAW_CIRC_CD    ");	break;
	case VC_DRAW_CIRC_2P    :	sprintf ( szParam, "VC_DRAW_CIRC_2P    ");	break;
	case VC_DRAW_CIRC_3P    :	sprintf ( szParam, "VC_DRAW_CIRC_3P    ");	break;
	case VC_DRAW_CIRC_TTT   :	sprintf ( szParam, "VC_DRAW_CIRC_TTT   ");	break;
	case VC_DRAW_ARC_CSE    :	sprintf ( szParam, "VC_DRAW_ARC_CSE    ");	break;
	case VC_DRAW_ARC_CSA    :	sprintf ( szParam, "VC_DRAW_ARC_CSA    ");	break;
	case VC_DRAW_ARC_CSL    :	sprintf ( szParam, "VC_DRAW_ARC_CSL    ");	break;
	case VC_DRAW_ARC_SEM    :	sprintf ( szParam, "VC_DRAW_ARC_SEM    ");	break;
	case VC_DRAW_ARC_SME    :	sprintf ( szParam, "VC_DRAW_ARC_SME    ");	break;
	case VC_DRAW_ARC_SCE    :	sprintf ( szParam, "VC_DRAW_ARC_SCE    ");	break;
	case VC_DRAW_ARC_SCA    :	sprintf ( szParam, "VC_DRAW_ARC_SCA    ");	break;
	case VC_DRAW_ARC_SCL    :	sprintf ( szParam, "VC_DRAW_ARC_SCL    ");	break;
	case VC_DRAW_ARC_SEA    :	sprintf ( szParam, "VC_DRAW_ARC_SEA    ");	break;
	case VC_DRAW_ARC_SED    :	sprintf ( szParam, "VC_DRAW_ARC_SED    ");	break;
	case VC_DRAW_ARC_SER    :	sprintf ( szParam, "VC_DRAW_ARC_SER    ");	break;
	case VC_DRAW_ARC_CONT   :	sprintf ( szParam, "VC_DRAW_ARC_CONT   ");	break;
	case VC_DRAW_SECTOR     :	sprintf ( szParam, "VC_DRAW_SECTOR     ");	break;
	case VC_DRAW_ELLIPSE    :	sprintf ( szParam, "VC_DRAW_ELLIPSE    ");	break;
	case VC_DRAW_RECT       :	sprintf ( szParam, "VC_DRAW_RECT       ");	break;
	case VC_DRAW_DIM_HOR    :	sprintf ( szParam, "VC_DRAW_DIM_HOR    ");	break;
	case VC_DRAW_DIM_VER    :	sprintf ( szParam, "VC_DRAW_DIM_VER    ");	break;
	case VC_DRAW_DIM_PAR    :	sprintf ( szParam, "VC_DRAW_DIM_PAR    ");	break;
	case VC_DRAW_DIM_ANG    :	sprintf ( szParam, "VC_DRAW_DIM_ANG    ");	break;
	case VC_DRAW_DIM_RAD    :	sprintf ( szParam, "VC_DRAW_DIM_RAD    ");	break;
	case VC_DRAW_DIM_DIAM   :	sprintf ( szParam, "VC_DRAW_DIM_DIAM   ");	break;
	case VC_DRAW_DIM_ORD    :	sprintf ( szParam, "VC_DRAW_DIM_ORD    ");	break;
	case VC_DRAW_HATCH      :	sprintf ( szParam, "VC_DRAW_HATCH      ");	break;
	case VC_INS_TEXT        :	sprintf ( szParam, "VC_INS_TEXT        ");	break;
	case VC_INS_SYMBOL      :	sprintf ( szParam, "VC_INS_SYMBOL      ");	break;
	case VC_INS_BLOCK       :	sprintf ( szParam, "VC_INS_BLOCK       ");	break;
	case VC_INS_IMAGE       :	sprintf ( szParam, "VC_INS_IMAGE       ");	break;
	case VC_INS_RMAP        :	sprintf ( szParam, "VC_INS_RMAP        ");	break;
	case VC_INS_GLASS       :	sprintf ( szParam, "VC_INS_GLASS       ");	break;
	case VC_INS_DRAWING     :	sprintf ( szParam, "VC_INS_DRAWING     ");	break;
	case VC_INS_AVSHP       :	sprintf ( szParam, "VC_INS_AVSHP       ");	break;
	case VC_INS_FLOOD       :	sprintf ( szParam, "VC_INS_FLOOD       ");	break;
		
	case VC_EDIT_ENTPROP    :	sprintf ( szParam, "VC_EDIT_ENTPROP    ");	break;
	case VC_EDIT_COPY       :	sprintf ( szParam, "VC_EDIT_COPY       ");	break;
	case VC_EDIT_MOVE       :	sprintf ( szParam, "VC_EDIT_MOVE       ");	break;
	case VC_EDIT_ROTATE     :	sprintf ( szParam, "VC_EDIT_ROTATE     ");	break;
	case VC_EDIT_SCALE      :	sprintf ( szParam, "VC_EDIT_SCALE      ");	break;
	case VC_EDIT_MIRROR     :	sprintf ( szParam, "VC_EDIT_MIRROR     ");	break;
	case VC_EDIT_ERASE      :	sprintf ( szParam, "VC_EDIT_ERASE      ");	break;
	case VC_EDIT_EXPLODE    :	sprintf ( szParam, "VC_EDIT_EXPLODE    ");	break;
	case VC_EDIT_CREBLOCK   :	sprintf ( szParam, "VC_EDIT_CREBLOCK   ");	break;
	case VC_EDIT_EXTEND     :	sprintf ( szParam, "VC_EDIT_EXTEND     ");	break;
	case VC_EDIT_TRIM       :	sprintf ( szParam, "VC_EDIT_TRIM       ");	break;
	case VC_EDIT_FILLET     :	sprintf ( szParam, "VC_EDIT_FILLET     ");	break;
	case VC_EDIT_ARRAY      :	sprintf ( szParam, "VC_EDIT_ARRAY      ");	break;
	case VC_EDIT_JOIN       :	sprintf ( szParam, "VC_EDIT_JOIN       ");	break;
	case VC_EDIT_UNDO       :	sprintf ( szParam, "VC_EDIT_UNDO       ");	break;
	case VC_EDIT_REDO       :	sprintf ( szParam, "VC_EDIT_REDO       ");	break;
	case VC_EDIT_CBCUT      :	sprintf ( szParam, "VC_EDIT_CBCUT      ");	break;
	case VC_EDIT_CBCOPY     :	sprintf ( szParam, "VC_EDIT_CBCOPY     ");	break;
	case VC_EDIT_CBPASTE    :	sprintf ( szParam, "VC_EDIT_CBPASTE    ");	break;
		
	case VC_FMT_LAYOUT      :	sprintf ( szParam, "VC_FMT_LAYOUT      ");	break;
	case VC_FMT_PAGE        :	sprintf ( szParam, "VC_FMT_PAGE        ");	break;
	case VC_FMT_LAYER       :	sprintf ( szParam, "VC_FMT_LAYER       ");	break;
	case VC_FMT_STLINE      :	sprintf ( szParam, "VC_FMT_STLINE      ");	break;
	case VC_FMT_STTEXT      :	sprintf ( szParam, "VC_FMT_STTEXT      ");	break;
	case VC_FMT_STDIM       :	sprintf ( szParam, "VC_FMT_STDIM       ");	break;
	case VC_FMT_STPOINT     :	sprintf ( szParam, "VC_FMT_STPOINT     ");	break;
	case VC_FMT_STHATCH     :	sprintf ( szParam, "VC_FMT_STHATCH     ");	break;
	case VC_FMT_BLOCK       :	sprintf ( szParam, "VC_FMT_BLOCK       ");	break;
	case VC_FMT_GRID        :	sprintf ( szParam, "VC_FMT_GRID        ");	break;
	case VC_FMT_OSNAP       :	sprintf ( szParam, "VC_FMT_OSNAP       ");	break;
	case VC_FMT_PSNAP       :	sprintf ( szParam, "VC_FMT_PSNAP       ");	break;
	case VC_FMT_UNITS       :	sprintf ( szParam, "VC_FMT_UNITS       ");	break;
	case VC_FMT_PRIVATE     :	sprintf ( szParam, "VC_FMT_PRIVATE     ");	break;
	case VC_FMT_PREFERS     :	sprintf ( szParam, "VC_FMT_PREFERS     ");	break;
	case VC_FMT_MLINE       :	sprintf ( szParam, "VC_FMT_MLINE       ");	break;
		
	case VC_SNAP_DLG        :	sprintf ( szParam, "VC_SNAP_DLG        ");	break;
	case VC_SNAP_CLEAR      :	sprintf ( szParam, "VC_SNAP_CLEAR      ");	break;
	case VC_SNAP_GRID       :	sprintf ( szParam, "VC_SNAP_GRID       ");	break;
	case VC_SNAP_POLAR      :	sprintf ( szParam, "VC_SNAP_POLAR      ");	break;
	
	case VC_SNAP_GRIP       :	sprintf ( szParam, "VC_SNAP_GRIP       ");	break;
	case VC_SNAP_POINT      :	sprintf ( szParam, "VC_SNAP_POINT      ");	break;
	case VC_SNAP_NEAR       :	sprintf ( szParam, "VC_SNAP_NEAR       ");	break;
	case VC_SNAP_END        :	sprintf ( szParam, "VC_SNAP_END        ");	break;
	case VC_SNAP_MID        :	sprintf ( szParam, "VC_SNAP_MID        ");	break;
	case VC_SNAP_INTER      :	sprintf ( szParam, "VC_SNAP_INTER      ");	break;
	case VC_SNAP_CEN        :	sprintf ( szParam, "VC_SNAP_CEN        ");	break;
	case VC_SNAP_PERP       :	sprintf ( szParam, "VC_SNAP_PERP       ");	break;
	case VC_SNAP_TANG       :	sprintf ( szParam, "VC_SNAP_TANG       ");	break;
	case VC_SNAP_REALTIME   :	sprintf ( szParam, "VC_SNAP_REALTIME   ");	break;
		
	case VC_TOOL_DIST       :	sprintf ( szParam, "VC_TOOL_DIST       ");	break;
	case VC_TOOL_PRNRECT    :	sprintf ( szParam, "VC_TOOL_PRNRECT    ");	break;
	case VC_TOOL_STAT       :	sprintf ( szParam, "VC_TOOL_STAT       ");	break;
	case VC_TOOL_NAVIGATOR  :	sprintf ( szParam, "VC_TOOL_NAVIGATOR  ");	break;
	case VC_TOOL_LAYERS     :	sprintf ( szParam, "VC_TOOL_LAYERS     ");	break;
	case VC_ENT_SWAP        :	sprintf ( szParam, "VC_ENT_SWAP        ");	break;
	case VC_ENT_TOTOP       :	sprintf ( szParam, "VC_ENT_TOTOP       ");	break;
	case VC_ENT_TOBOTTOM    :	sprintf ( szParam, "VC_ENT_TOBOTTOM    ");	break;
	case VC_SEL_BYPOINT     :	sprintf ( szParam, "VC_SEL_BYPOINT     ");	break;
	case VC_SEL_BYRECT      :	sprintf ( szParam, "VC_SEL_BYRECT      ");	break;
	case VC_SEL_BYPOLYGON   :	sprintf ( szParam, "VC_SEL_BYPOLYGON   ");	break;
	case VC_SEL_BYPOLYLINE  :	sprintf ( szParam, "VC_SEL_BYPOLYLINE  ");	break;
	case VC_SEL_BYDIST      :	sprintf ( szParam, "VC_SEL_BYDIST      ");	break;
	case VC_SEL_BYHANDLE    :	sprintf ( szParam, "VC_SEL_BYHANDLE    ");	break;
	case VC_SEL_BYKEY       :	sprintf ( szParam, "VC_SEL_BYKEY       ");	break;
	case VC_SEL_BYLAYER     :	sprintf ( szParam, "VC_SEL_BYLAYER     ");	break;
		
	case VC_RESET			:	sprintf ( szParam, "VC_RESET			");	break;
	case VC_REDRAW			:	sprintf ( szParam, "VC_REDRAW			");	break;
	case VC_SHOWLINEW		:	sprintf ( szParam, "VC_SHOWLINEW		");	break;
	case VC_SHOWGRID		:	sprintf ( szParam, "VC_SHOWGRID			");	break;
	case VC_SHOWFILL		:	sprintf ( szParam, "VC_SHOWFILL			");	break;
	default					:	sprintf ( szParam, "UNKNOWN CODE %d", nCmd); return false;
	}
	
	return true;
}


bool CVeCad::FormatVeCadEntity(int nType, LPTSTR szParam)
{
	switch(nType)
	{
	case VL_ENT_POINT	:	sprintf( szParam, "POINT   "); break;
	case VL_ENT_LINE    :	sprintf( szParam, "LINE    "); break;
	case VL_ENT_POLY    :	sprintf( szParam, "POLY    "); break;
	case VL_ENT_CIRCLE  :	sprintf( szParam, "CIRCLE  "); break;
	case VL_ENT_ARC     :	sprintf( szParam, "ARC     "); break;
	case VL_ENT_ARC2    :	sprintf( szParam, "ARC2    "); break;
	case VL_ENT_ELLIPSE :	sprintf( szParam, "ELLIPSE "); break;
	case VL_ENT_TEXT    :	sprintf( szParam, "TEXT    "); break;
	case VL_ENT_BITMAP  :	sprintf( szParam, "BITMAP  "); break;
	case VL_ENT_INSBLOCK:	sprintf( szParam, "INSBLOCK"); break;
	case VL_ENT_HATCH   :	sprintf( szParam, "HATCH   "); break;
	case VL_ENT_FLOOD   :	sprintf( szParam, "FLOOD   "); break;
	case VL_ENT_RECT    :	sprintf( szParam, "RECT    "); break;
	case VL_ENT_DIMLIN  :	sprintf( szParam, "DIMLIN  "); break;
	case VL_ENT_DIMANG  :	sprintf( szParam, "DIMANG  "); break;
	case VL_ENT_DIMRAD  :	sprintf( szParam, "DIMRAD  "); break;
	case VL_ENT_DIMDIAM :	sprintf( szParam, "DIMDIAM "); break;
	case VL_ENT_DIMORD  :	sprintf( szParam, "DIMORD  "); break;
	case VL_ENT_INSDWG  :	sprintf( szParam, "INSDWG  "); break;
	case VL_ENT_CUSTOM  :	sprintf( szParam, "CUSTOM  "); break;
	default:
		return false;
	}

	return true;
}

bool CVeCad::FormatVeCadMsg(UINT nMsg, LPTSTR szParam)
{
	switch(nMsg)
	{
	/////////////////////////////////////////////////
	// VeCAD messages, passed to drawing procedure
	case VM_GETSTRING      :		sprintf( szParam, "VM_GETSTRING      ");		break;
	case VM_ERROR          :		sprintf( szParam, "VM_ERROR          ");		break;
	case VM_ZOOM           :		sprintf( szParam, "VM_ZOOM           ");		break;
	case VM_ZOOMMIN        :		sprintf( szParam, "VM_ZOOMMIN        ");		break;
	case VM_ZOOMMAX        :		sprintf( szParam, "VM_ZOOMMAX        ");		break;
	case VM_BEGINPAINT     :		sprintf( szParam, "VM_BEGINPAINT     ");		break;
	case VM_ENDPAINT       :		sprintf( szParam, "VM_ENDPAINT       ");		break;
	case VM_LBPAINT        :		sprintf( szParam, "VM_LBPAINT        ");		break;
	case VM_OBJADD         :		sprintf( szParam, "VM_OBJADD         ");		break;
	case VM_OBJDELETE      :		sprintf( szParam, "VM_OBJDELETE      ");		break;
	case VM_OBJACTIVE      :		sprintf( szParam, "VM_OBJACTIVE      ");		break;
	case VM_ENTADD         :		sprintf( szParam, "VM_ENTADD         ");		break;
	case VM_ENTDELETE      :		sprintf( szParam, "VM_ENTDELETE      ");		break;
	case VM_ENTSELECT      :		sprintf( szParam, "VM_ENTSELECT      ");		break;
	case VM_ENTUNSELECT    :		sprintf( szParam, "VM_ENTUNSELECT    ");		break;
	case VM_ENTCOPY        :		sprintf( szParam, "VM_ENTCOPY        ");		break;
	case VM_ENTMOVE        :		sprintf( szParam, "VM_ENTMOVE        ");		break;
	case VM_ENTROTATE      :		sprintf( szParam, "VM_ENTROTATE      ");		break;
	case VM_ENTSCALE       :		sprintf( szParam, "VM_ENTSCALE       ");		break;
	case VM_ENTMIRROR      :		sprintf( szParam, "VM_ENTMIRROR      ");		break;
	case VM_ENTERASE       :		sprintf( szParam, "VM_ENTERASE       ");		break;
	case VM_ENTEXPLODE     :		sprintf( szParam, "VM_ENTEXPLODE     ");		break;
	case VM_ENTPROPDLG     :		sprintf( szParam, "VM_ENTPROPDLG     ");		break;
	case VM_ENTINDEX       :		sprintf( szParam, "VM_ENTINDEX       ");		break;
	case VM_KEYDOWN        :		sprintf( szParam, "VM_KEYDOWN        ");		break;
	case VM_MOUSEMOVE      :		sprintf( szParam, "VM_MOUSEMOVE      ");		break;
	case VM_LBDOWN         :		sprintf( szParam, "VM_LBDOWN         ");		break;
	case VM_LBDBLCLK       :		sprintf( szParam, "VM_LBDBLCLK       ");		break;
	case VM_RBDOWN         :		sprintf( szParam, "VM_RBDOWN         ");		break;
	case VM_KEYUP          :		sprintf( szParam, "VM_KEYUP          ");		break;
	case VM_LBUP           :		sprintf( szParam, "VM_LBUP           ");		break;
	case VM_RBUP           :		sprintf( szParam, "VM_RBUP           ");		break;
	case VM_MBDOWN         :		sprintf( szParam, "VM_MBDOWN         ");		break;
	case VM_MBUP           :		sprintf( szParam, "VM_MBUP           ");		break;
	case VM_TOOLCREATE     :		sprintf( szParam, "VM_TOOLCREATE     ");		break;
	case VM_TOOLOPEN       :		sprintf( szParam, "VM_TOOLOPEN       ");		break;
	case VM_TOOLCLOSE      :		sprintf( szParam, "VM_TOOLCLOSE      ");		break;
	case VM_TOOLCLICK      :		sprintf( szParam, "VM_TOOLCLICK      ");		break;
	case VM_TOOLDRAG       :		sprintf( szParam, "VM_TOOLDRAG       ");		break;
	case VM_TOOLREDRAW     :		sprintf( szParam, "VM_TOOLREDRAW     ");		break;
	case VM_CANCELTOOL     :		sprintf( szParam, "VM_CANCELTOOL     ");		break;
	case VM_REPEATTOOL     :		sprintf( szParam, "VM_REPEATTOOL     ");		break;
	case VM_MENUEDIT       :		sprintf( szParam, "VM_MENUEDIT       ");		break;
	case VM_MENUVER        :		sprintf( szParam, "VM_MENUVER        ");		break;
	case VM_EXECUTE        :		sprintf( szParam, "VM_EXECUTE        ");		break;
	case VM_EXECUTED       :		sprintf( szParam, "VM_EXECUTED       ");		break;
	case VM_DWGCREATE      :		sprintf( szParam, "VM_DWGCREATE      ");		break;
	case VM_DWGDELETE      :		sprintf( szParam, "VM_DWGDELETE      ");		break;
	case VM_DWGCLEAR       :		sprintf( szParam, "VM_DWGCLEAR       ");		break;
	case VM_DWGSELECT      :		sprintf( szParam, "VM_DWGSELECT      ");		break;
	case VM_DWGLOADING     :		sprintf( szParam, "VM_DWGLOADING     ");		break;
	case VM_DWGLOADED      :		sprintf( szParam, "VM_DWGLOADED      ");		break;
	case VM_DWGSAVING      :		sprintf( szParam, "VM_DWGSAVING      ");		break;
	case VM_DWGSAVED       :		sprintf( szParam, "VM_DWGSAVED       ");		break;
	case VM_DWGUPDATE      :		sprintf( szParam, "VM_DWGUPDATE      ");		break;
	case VM_PASSWORD       :		sprintf( szParam, "VM_PASSWORD       ");		break;
	case VM_TIMER          :		sprintf( szParam, "VM_TIMER          ");		break;
	case VM_RASTER         :		sprintf( szParam, "VM_RASTER         ");		break;
	case VM_CLOSEQUERY     :		sprintf( szParam, "VM_CLOSEQUERY     ");		break;
	case VM_WINRESIZE      :		sprintf( szParam, "VM_WINRESIZE      ");		break;
	case VM_WDWG_CLOSED    :		sprintf( szParam, "VM_WDWG_CLOSED    ");		break;
	case VM_WVIEW_CLOSED   :		sprintf( szParam, "VM_WVIEW_CLOSED   ");		break;
	case VM_GRIPSELECT     :		sprintf( szParam, "VM_GRIPSELECT     ");		break;
	case VM_GRIPDRAG       :		sprintf( szParam, "VM_GRIPDRAG       ");		break;
	case VM_GRIPMOVE       :		sprintf( szParam, "VM_GRIPMOVE       ");		break;
	case VM_STATUSTEXT     :		sprintf( szParam, "VM_STATUSTEXT     ");		break;
	case VM_EXP___MIN      :		sprintf( szParam, "VM_EXP___MIN      ");		break;
	case VM_EXP_BEGIN      :		sprintf( szParam, "VM_EXP_BEGIN over ");		break;
	case VM_EXP_END        :		sprintf( szParam, "VM_EXP_END over   ");		break;
	case VM_EXP_ENTITY     :		sprintf( szParam, "VM_EXP_ENTITY over");		break;
	case VM_EXP_MOVETO     :		sprintf( szParam, "VM_EXP_MOVETO     ");		break;
	case VM_EXP_LINETO     :		sprintf( szParam, "VM_EXP_LINETO     ");		break;
	case VM_EXP_ARCTO      :		sprintf( szParam, "VM_EXP_ARCTO      ");		break;
	case VM_EXP_DROP       :		sprintf( szParam, "VM_EXP_DROP       ");		break;
	case VM_EXP_DROPSIZE   :		sprintf( szParam, "VM_EXP_DROPSIZE   ");		break;
	case VM_EXP_COLOR      :		sprintf( szParam, "VM_EXP_COLOR      ");		break;
	case VM_EXP_WIDTH      :		sprintf( szParam, "VM_EXP_WIDTH      ");		break;
	case VM_EXP_LAYER      :		sprintf( szParam, "VM_EXP_LAYER      ");		break;
	case VM_EXP_PUMPOFF    :		sprintf( szParam, "VM_EXP_PUMPOFF    ");		break;
	case VM_EXP_EXPLODE    :		sprintf( szParam, "VM_EXP_EXPLODE    ");		break;
	case VM_EXP_LINES      :		sprintf( szParam, "VM_EXP_LINES      ");		break;
	case VM_EXP_FILLINGS   :		sprintf( szParam, "VM_EXP_FILLINGS   ");		break;
	case VM_EXP___MAX      :		sprintf( szParam, "VM_EXP___MAX      ");		break;
	case VM_PROP_PRE       :		sprintf( szParam, "VM_PROP_PRE       ");		break;
	case VM_PROP_POST      :		sprintf( szParam, "VM_PROP_POST      ");		break;
	case VM_NAV_CLOSE      :		sprintf( szParam, "VM_NAV_CLOSE      ");		break;
	case VM_NAV_DIALOG     :		sprintf( szParam, "VM_NAV_DIALOG     ");		break;
	case VM_MOUSEWHEEL     :		sprintf( szParam, "VM_MOUSEWHEEL     ");		break;
		/********************************************************************
		* VeCAD commands identifiers
		********************************************************************/
		
		// File
	case VC_FILE_NEW        :		sprintf( szParam, "VC_FILE_NEW        ");		break;
	case VC_FILE_OPEN       :		sprintf( szParam, "VC_FILE_OPEN       ");		break;
	case VC_FILE_SAVE       :		sprintf( szParam, "VC_FILE_SAVE       ");		break;
	case VC_FILE_SAVEAS     :		sprintf( szParam, "VC_FILE_SAVEAS     ");		break;
	case VC_FILE_CLOSE      :		sprintf( szParam, "VC_FILE_CLOSE      ");		break;
	case VC_FILE_CLOSEALL   :		sprintf( szParam, "VC_FILE_CLOSEALL   ");		break;
	case VC_FILE_LIST       :		sprintf( szParam, "VC_FILE_LIST       ");		break;
	case VC_IMPORT_DXF      :		sprintf( szParam, "VC_IMPORT_DXF      ");		break;
	case VC_IMPORT_VDF      :		sprintf( szParam, "VC_IMPORT_VDF      ");		break;
	case VC_IMPORT_HPGL     :		sprintf( szParam, "VC_IMPORT_HPGL     ");		break;
	case VC_IMPORT_CNC      :		sprintf( szParam, "VC_IMPORT_CNC      ");		break;
	case VC_IMPORT_DP1      :		sprintf( szParam, "VC_IMPORT_DP1      ");		break;
	case VC_IMPORT_AVSHP    :		sprintf( szParam, "VC_IMPORT_AVSHP    ");		break;
	case VC_EXPORT_DXF      :		sprintf( szParam, "VC_EXPORT_DXF      ");		break;
	case VC_EXPORT_HPGL     :		sprintf( szParam, "VC_EXPORT_HPGL     ");		break;
	case VC_EXPORT_CNC      :		sprintf( szParam, "VC_EXPORT_CNC      ");		break;
	case VC_EXPORT_BMP      :		sprintf( szParam, "VC_EXPORT_BMP      ");		break;
	case VC_EXPORT_AVSHP    :		sprintf( szParam, "VC_EXPORT_AVSHP    ");		break;
	case VC_PRINT           :		sprintf( szParam, "VC_PRINT           ");		break;
	case VC_ZOOM_ALL        :		sprintf( szParam, "VC_ZOOM_ALL        ");		break;
	case VC_ZOOM_WIN        :		sprintf( szParam, "VC_ZOOM_WIN        ");		break;
	case VC_ZOOM_PAN        :		sprintf( szParam, "VC_ZOOM_PAN        ");		break;
	case VC_ZOOM_PAGE       :		sprintf( szParam, "VC_ZOOM_PAGE       ");		break;
	case VC_ZOOM_IN         :		sprintf( szParam, "VC_ZOOM_IN         ");		break;
	case VC_ZOOM_OUT        :		sprintf( szParam, "VC_ZOOM_OUT        ");		break;
	case VC_ZOOM_LEFT       :		sprintf( szParam, "VC_ZOOM_LEFT       ");		break;
	case VC_ZOOM_RIGHT      :		sprintf( szParam, "VC_ZOOM_RIGHT      ");		break;
	case VC_ZOOM_UP         :		sprintf( szParam, "VC_ZOOM_UP         ");		break;
	case VC_ZOOM_DOWN       :		sprintf( szParam, "VC_ZOOM_DOWN       ");		break;
	case VC_ZOOM_PREV       :		sprintf( szParam, "VC_ZOOM_PREV       ");		break;
	case VC_ZOOM_SEL        :		sprintf( szParam, "VC_ZOOM_SEL        ");		break;
	case VC_PAGE_NEXT       :		sprintf( szParam, "VC_PAGE_NEXT       ");		break;
	case VC_PAGE_PREV       :		sprintf( szParam, "VC_PAGE_PREV       ");		break;
	case VC_PAGE_FIRST      :		sprintf( szParam, "VC_PAGE_FIRST      ");		break;
	case VC_PAGE_LAST       :		sprintf( szParam, "VC_PAGE_LAST       ");		break;
	case VC_PAGE_DLG        :		sprintf( szParam, "VC_PAGE_DLG        ");		break;
	case VC_VIEW_SAVE       :		sprintf( szParam, "VC_VIEW_SAVE       ");		break;
	case VC_VIEW_LIST       :		sprintf( szParam, "VC_VIEW_LIST       ");		break;
		// Draw
	case VC_DRAW_POINT      :		sprintf( szParam, "VC_DRAW_POINT      ");		break;
	case VC_DRAW_LINE       :		sprintf( szParam, "VC_DRAW_LINE       ");		break;
	case VC_DRAW_POLYLINE   :		sprintf( szParam, "VC_DRAW_POLYLINE   ");		break;
	case VC_DRAW_SPLINE     :		sprintf( szParam, "VC_DRAW_SPLINE     ");		break;
	case VC_DRAW_CIRC_CR    :		sprintf( szParam, "VC_DRAW_CIRC_CR    ");		break;
	case VC_DRAW_CIRC_CD    :		sprintf( szParam, "VC_DRAW_CIRC_CD    ");		break;
	case VC_DRAW_CIRC_2P    :		sprintf( szParam, "VC_DRAW_CIRC_2P    ");		break;
	case VC_DRAW_CIRC_3P    :		sprintf( szParam, "VC_DRAW_CIRC_3P    ");		break;
	case VC_DRAW_CIRC_TTT   :		sprintf( szParam, "VC_DRAW_CIRC_TTT   ");		break;
	case VC_DRAW_ARC_CSE    :		sprintf( szParam, "VC_DRAW_ARC_CSE    ");		break;
	case VC_DRAW_ARC_CSA    :		sprintf( szParam, "VC_DRAW_ARC_CSA    ");		break;
	case VC_DRAW_ARC_CSL    :		sprintf( szParam, "VC_DRAW_ARC_CSL    ");		break;
	case VC_DRAW_ARC_SEM    :		sprintf( szParam, "VC_DRAW_ARC_SEM    ");		break;
	case VC_DRAW_ARC_SME    :		sprintf( szParam, "VC_DRAW_ARC_SME    ");		break;
	case VC_DRAW_ARC_SCE    :		sprintf( szParam, "VC_DRAW_ARC_SCE    ");		break;
	case VC_DRAW_ARC_SCA    :		sprintf( szParam, "VC_DRAW_ARC_SCA    ");		break;
	case VC_DRAW_ARC_SCL    :		sprintf( szParam, "VC_DRAW_ARC_SCL    ");		break;
	case VC_DRAW_ARC_SEA    :		sprintf( szParam, "VC_DRAW_ARC_SEA    ");		break;
	case VC_DRAW_ARC_SED    :		sprintf( szParam, "VC_DRAW_ARC_SED    ");		break;
	case VC_DRAW_ARC_SER    :		sprintf( szParam, "VC_DRAW_ARC_SER    ");		break;
	case VC_DRAW_ARC_CONT   :		sprintf( szParam, "VC_DRAW_ARC_CONT   ");		break;
	case VC_DRAW_SECTOR     :		sprintf( szParam, "VC_DRAW_SECTOR     ");		break;
	case VC_DRAW_ELLIPSE    :		sprintf( szParam, "VC_DRAW_ELLIPSE    ");		break;
	case VC_DRAW_RECT       :		sprintf( szParam, "VC_DRAW_RECT       ");		break;
	case VC_DRAW_DIM_HOR    :		sprintf( szParam, "VC_DRAW_DIM_HOR    ");		break;
	case VC_DRAW_DIM_VER    :		sprintf( szParam, "VC_DRAW_DIM_VER    ");		break;
	case VC_DRAW_DIM_PAR    :		sprintf( szParam, "VC_DRAW_DIM_PAR    ");		break;
	case VC_DRAW_DIM_ANG    :		sprintf( szParam, "VC_DRAW_DIM_ANG    ");		break;
	case VC_DRAW_DIM_RAD    :		sprintf( szParam, "VC_DRAW_DIM_RAD    ");		break;
	case VC_DRAW_DIM_DIAM   :		sprintf( szParam, "VC_DRAW_DIM_DIAM   ");		break;
	case VC_DRAW_DIM_ORD    :		sprintf( szParam, "VC_DRAW_DIM_ORD    ");		break;
	case VC_DRAW_HATCH      :		sprintf( szParam, "VC_DRAW_HATCH      ");		break;
	case VC_INS_TEXT        :		sprintf( szParam, "VC_INS_TEXT        ");		break;
	case VC_INS_SYMBOL      :		sprintf( szParam, "VC_INS_SYMBOL      ");		break;
	case VC_INS_BLOCK       :		sprintf( szParam, "VC_INS_BLOCK       ");		break;
	case VC_INS_IMAGE       :		sprintf( szParam, "VC_INS_IMAGE       ");		break;
	case VC_INS_RMAP        :		sprintf( szParam, "VC_INS_RMAP        ");		break;
	case VC_INS_GLASS       :		sprintf( szParam, "VC_INS_GLASS       ");		break;
	case VC_INS_DRAWING     :		sprintf( szParam, "VC_INS_DRAWING     ");		break;
	case VC_INS_AVSHP       :		sprintf( szParam, "VC_INS_AVSHP       ");		break;
	case VC_INS_FLOOD       :		sprintf( szParam, "VC_INS_FLOOD       ");		break;
		// Edit
	case VC_EDIT_ENTPROP    :		sprintf( szParam, "VC_EDIT_ENTPROP    ");		break;
	case VC_EDIT_COPY       :		sprintf( szParam, "VC_EDIT_COPY       ");		break;
	case VC_EDIT_MOVE       :		sprintf( szParam, "VC_EDIT_MOVE       ");		break;
	case VC_EDIT_ROTATE     :		sprintf( szParam, "VC_EDIT_ROTATE     ");		break;
	case VC_EDIT_SCALE      :		sprintf( szParam, "VC_EDIT_SCALE      ");		break;
	case VC_EDIT_MIRROR     :		sprintf( szParam, "VC_EDIT_MIRROR     ");		break;
	case VC_EDIT_ERASE      :		sprintf( szParam, "VC_EDIT_ERASE      ");		break;
	case VC_EDIT_EXPLODE    :		sprintf( szParam, "VC_EDIT_EXPLODE    ");		break;
	case VC_EDIT_CREBLOCK   :		sprintf( szParam, "VC_EDIT_CREBLOCK   ");		break;
	case VC_EDIT_EXTEND     :		sprintf( szParam, "VC_EDIT_EXTEND     ");		break;
	case VC_EDIT_TRIM       :		sprintf( szParam, "VC_EDIT_TRIM       ");		break;
	case VC_EDIT_FILLET     :		sprintf( szParam, "VC_EDIT_FILLET     ");		break;
	case VC_EDIT_ARRAY      :		sprintf( szParam, "VC_EDIT_ARRAY      ");		break;
	case VC_EDIT_JOIN       :		sprintf( szParam, "VC_EDIT_JOIN       ");		break;
	case VC_EDIT_UNDO       :		sprintf( szParam, "VC_EDIT_UNDO       ");		break;
	case VC_EDIT_REDO       :		sprintf( szParam, "VC_EDIT_REDO       ");		break;
	case VC_EDIT_CBCUT      :		sprintf( szParam, "VC_EDIT_CBCUT      ");		break;
	case VC_EDIT_CBCOPY     :		sprintf( szParam, "VC_EDIT_CBCOPY     ");		break;
	case VC_EDIT_CBPASTE    :		sprintf( szParam, "VC_EDIT_CBPASTE    ");		break;
	case VC_FMT_LAYOUT      :		sprintf( szParam, "VC_FMT_LAYOUT      ");		break;
	case VC_FMT_PAGE        :		sprintf( szParam, "VC_FMT_PAGE        ");		break;
	case VC_FMT_LAYER       :		sprintf( szParam, "VC_FMT_LAYER       ");		break;
	case VC_FMT_STLINE      :		sprintf( szParam, "VC_FMT_STLINE      ");		break;
	case VC_FMT_STTEXT      :		sprintf( szParam, "VC_FMT_STTEXT      ");		break;
	case VC_FMT_STDIM       :		sprintf( szParam, "VC_FMT_STDIM       ");		break;
	case VC_FMT_STPOINT     :		sprintf( szParam, "VC_FMT_STPOINT     ");		break;
	case VC_FMT_STHATCH     :		sprintf( szParam, "VC_FMT_STHATCH     ");		break;
	case VC_FMT_BLOCK       :		sprintf( szParam, "VC_FMT_BLOCK       ");		break;
	case VC_FMT_GRID        :		sprintf( szParam, "VC_FMT_GRID        ");		break;
	case VC_FMT_OSNAP       :		sprintf( szParam, "VC_FMT_OSNAP       ");		break;
	case VC_FMT_PSNAP       :		sprintf( szParam, "VC_FMT_PSNAP       ");		break;
	case VC_FMT_UNITS       :		sprintf( szParam, "VC_FMT_UNITS       ");		break;
	case VC_FMT_PRIVATE     :		sprintf( szParam, "VC_FMT_PRIVATE     ");		break;
	case VC_FMT_PREFERS     :		sprintf( szParam, "VC_FMT_PREFERS     ");		break;
	case VC_FMT_MLINE       :		sprintf( szParam, "VC_FMT_MLINE       ");		break;
		// Snap
	case VC_SNAP_DLG        :		sprintf( szParam, "VC_SNAP_DLG        ");		break;
	case VC_SNAP_CLEAR      :		sprintf( szParam, "VC_SNAP_CLEAR      ");		break;
	case VC_SNAP_GRID       :		sprintf( szParam, "VC_SNAP_GRID       ");		break;
	case VC_SNAP_POLAR      :		sprintf( szParam, "VC_SNAP_POLAR      ");		break;
	case VC_SNAP_KNOT       :		sprintf( szParam, "VC_SNAP_KNOT over  ");		break;
	case VC_SNAP_POINT      :		sprintf( szParam, "VC_SNAP_POINT      ");		break;
	case VC_SNAP_NEAR       :		sprintf( szParam, "VC_SNAP_NEAR       ");		break;
	case VC_SNAP_END        :		sprintf( szParam, "VC_SNAP_END        ");		break;
	case VC_SNAP_MID        :		sprintf( szParam, "VC_SNAP_MID        ");		break;
	case VC_SNAP_INTER      :		sprintf( szParam, "VC_SNAP_INTER      ");		break;
	case VC_SNAP_CEN        :		sprintf( szParam, "VC_SNAP_CEN        ");		break;
	case VC_SNAP_PERP       :		sprintf( szParam, "VC_SNAP_PERP       ");		break;
	case VC_SNAP_TANG       :		sprintf( szParam, "VC_SNAP_TANG       ");		break;
	case VC_SNAP_REALTIME   :		sprintf( szParam, "VC_SNAP_REALTIME   ");		break;
		// Tools
	case VC_TOOL_DIST       :		sprintf( szParam, "VC_TOOL_DIST       ");		break;
	case VC_TOOL_PRNRECT    :		sprintf( szParam, "VC_TOOL_PRNRECT    ");		break;
	case VC_TOOL_STAT       :		sprintf( szParam, "VC_TOOL_STAT       ");		break;
	case VC_TOOL_NAVIGATOR  :		sprintf( szParam, "VC_TOOL_NAVIGATOR  ");		break;
	case VC_TOOL_LAYERS     :		sprintf( szParam, "VC_TOOL_LAYERS     ");		break;
	case VC_ENT_SWAP        :		sprintf( szParam, "VC_ENT_SWAP        ");		break;
	case VC_ENT_TOTOP       :		sprintf( szParam, "VC_ENT_TOTOP       ");		break;
	case VC_ENT_TOBOTTOM    :		sprintf( szParam, "VC_ENT_TOBOTTOM    ");		break;
	case VC_SEL_BYPOINT     :		sprintf( szParam, "VC_SEL_BYPOINT     ");		break;
	case VC_SEL_BYRECT      :		sprintf( szParam, "VC_SEL_BYRECT      ");		break;
	case VC_SEL_BYPOLYGON   :		sprintf( szParam, "VC_SEL_BYPOLYGON   ");		break;
	case VC_SEL_BYPOLYLINE  :		sprintf( szParam, "VC_SEL_BYPOLYLINE  ");		break;
	case VC_SEL_BYDIST      :		sprintf( szParam, "VC_SEL_BYDIST      ");		break;
	case VC_SEL_BYHANDLE    :		sprintf( szParam, "VC_SEL_BYHANDLE    ");		break;
	case VC_SEL_BYKEY       :		sprintf( szParam, "VC_SEL_BYKEY       ");		break;
	case VC_SEL_BYLAYER     :		sprintf( szParam, "VC_SEL_BYLAYER     ");		break;		
		// Misc
	case VC_RESET         :			sprintf( szParam, "VC_RESET           ");		break;
	case VC_REDRAW        :			sprintf( szParam, "VC_REDRAW          ");		break;
	case VC_SHOWLINEW     :			sprintf( szParam, "VC_SHOWLINEW       ");		break;
	case VC_SHOWGRID      :			sprintf( szParam, "VC_SHOWGRID        ");		break;
	case VC_SHOWFILL      :			sprintf( szParam, "VC_SHOWFILL        ");		break;				
		// Offset for custom commands that use cursor
	case VC_CUSTOM        :			sprintf( szParam, "VC_CUSTOM          ");		break;
	}

	return true;
}

//ggasa 2002 05 26
/*
void CVeCad::OpenMruFile (int i)
{
	LPCTSTR pszFileName = g_MruList.Get( i );

	if (pszFileName)
	{
		int iDwg = vlDocCreate( m_hVec );  //, DwgProc );

		if (iDwg>=0)
		{
			if (vlFileLoad( VL_FILE_VEC, pszFileName )==FALSE)
			{
				vlDocDelete( iDwg );
			}
			else
			{
				strcpy(m_szFileName, pszFileName);
				vlSetFocus();
			}
		}
	}    
}*/

void CVeCad::AddGuideLine(int /*nx*/, int /*ny*/, double dx, double dy)
{
	VLPOINT dPt1, dPt2;

	// Vert/Horz 에 따라 좌표 재계산.
	if (m_bGuideVert)
	{
		dPt1.x = dx;
		dPt2.x = dx;
		dPt1.y = m_dGuideRectMaxLeftTop.y;
		dPt2.y = m_dGuideRectMaxRightBtm.y;
	}
	else
	{
		dPt1.x = m_dGuideRectMaxLeftTop.x;
		dPt2.x = m_dGuideRectMaxRightBtm.x;
		dPt1.y = dy;
		dPt2.y = dy;
	}

	// Guide Line Entity 추가.
	int			nOldLine	= GetLineType();
	int			nLayerOld	= vlLayerIndex(NULL, 0);
	int			nLayer		= vlLayerIndex("GUIDE", 0);

	vlLayerActive( nLayer );
	SetLineType( SOLID_LINE );

	int			nIndex	= vlAddLine( dPt1.x, dPt1.y, dPt2.x, dPt2.y );
	CvlEntity*	pEnt	= CvlEntity::GetEntity( nIndex );

	pEnt->m_iColor		= VL_COL_MAGENTA;
	pEnt->m_bOwnColor	= TRUE;

	pEnt->UpdateData(false);

	// 원래 설정으로 설정 복구
	SetLineType( nOldLine );
	vlLayerActive( nLayerOld );
	
	// Array 에 저장

	m_GuideLineArray.Add( (CvlLine*)pEnt );
}

void CVeCad::RemoveGuideLine(int nx, int ny, double /*dx*/, double /*dy*/)
{
	int nLayerOld = vlLayerIndex(NULL,0);
	int nLayerGuide = vlLayerIndex("GUIDE",0);

	vlLayerActive(nLayerGuide);
	vlPropPutInt( VD_LAYER_LOCK, nLayerGuide, 0 );// ReadOnly Release


	// 좌표에서 Entity 인덱스 찾기.
	int nIndex = vlGetEntity(VL_EI_BYPOINT, nx, ny	);
	
	// m_GuideLineArray 에서 해당하는 Entity 가 있는지 체크.
	// 있으면 제거. (VeCad 에서도, m_GuideLineArray 에서도.)	
	int nSize = m_GuideLineArray.GetSize();

	for (int i=0; i<nSize; i++)
	{
		CvlLine* pLine = m_GuideLineArray.GetAt(i);
		
		if (pLine->m_iIndex == nIndex)
		{
			pLine->Erase();
			delete pLine;

			nSize--;

			m_GuideLineArray.RemoveAt(i);
		}
	}	

	vlPropPutInt( VD_LAYER_LOCK, nLayerGuide, 1 );// ReadOnly Enable
	vlLayerActive(nLayerOld);
}

bool CVeCad::OnLButtonDown(int nx, int ny, double dx, double dy)
{
/*	bool bTrim			= IsEnableTrim();
	bool bExt			= IsEnableExt();
	bool bOffset		= IsEnableOffset();
	bool bOffsetMulti	= IsEnableOffsetMulti();

	if (m_bGuideLine)
	{
		if (m_bGuideAdd)
			AddGuideLine(nx, ny, dx, dy);
		else
			RemoveGuideLine(nx, ny, dx, dy);

		vlRedraw();

		return true;
	}
	else if ( bTrim || bExt )
	{
		vlSelect(false, -1);
		
		if (m_pTrim->m_bSetSrc==false)
			m_pTrim->FindSrcLine(dx, dy);
		else
		{
			m_pTrim->Run(nx, ny);
			m_pTrim->Free();
		}
		
		vlRedraw();
		
		return true;
	}
	else if ( bOffset || bOffsetMulti )
	{
		if (m_pTrim->m_bSetSrc==false)
		{
			if (m_pTrim->FindOffsetSrc(dx, dy)==true)
			{
//				CDlgOffsetSize Dlg;
				
				Dlg.m_bMultiOffset = m_pTrim->m_bOffsetMulti;

				if (Dlg.DoModal()==IDOK)
				{
					m_pTrim->SetOffsetParameter( Dlg.m_dOffsetSize, Dlg.m_nOffsetCount );

					if (m_pTrim->MakeOffset()==true)
					{					
						m_pTrim->Free();

						// Trim 기능의 Enable 상태 유지를 위해서.
				//		if (bOffsetMulti)
				//			Enable

					}
				}
				else
					m_pTrim->Free();
			}
		}

		vlRedraw();

		return true;
	}
	
	vlRedraw();
*/
	return false;
}

bool CVeCad::OnKeyUp(int nVirtualKey, int /*RepeatCnt*/)
{
	switch(nVirtualKey)
	{
	case VK_CONTROL:
		if (m_bGuideAdd==false && IsEnableGuideLine()==true)
			m_bGuideAdd = true;

		break;
	}

	return true;
}

bool CVeCad::OnKeyDown(int nVirtualKey, int /*RepeatCnt*/)
{
	switch(nVirtualKey)
	{
	case VK_CONTROL:
		if (m_bGuideAdd==true && IsEnableGuideLine()==true)
			m_bGuideAdd = false;

//		TRACE("Control Key Pressed\n");
		break;
	}

	return true;
}

bool CVeCad::OnMenuEdit(int /*nx*/, int /*ny*/, double/* dx*/, double /*dy*/)
{	
	// 선택된 엔티티가 있는지 확인.
	if (GetEntityIndex(0, true)==-1)
		return false;

	POINT point;
	GetCursorPos(&point);

	if (point.x == -1 && point.y == -1)
	{
		//keystroke invocation
		CRect rect;
		GetClientRect(m_hMain, rect);

		POINT PtRect;

		/////////////////////////////////////
		PtRect.x	= rect.left;
		PtRect.y	= rect.top;
		ClientToScreen(m_hMain, &PtRect);
		rect.left	= PtRect.x;
		rect.top	= PtRect.y;
		/////////////////////////////////////
		point = rect.TopLeft();

		point.x += 5;
		point.y += 5;
	}

	if (m_nMenuID>0)
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(m_nMenuID));

		CMenu* pPopup = menu.GetSubMenu(0);
//		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = AfxGetMainWnd();

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);

		vlSetFocus();

		return true;
	}
	
	return false;
}

bool CVeCad::OnExecute(int Prm1, int /*Prm2*/, double/* dx*/, double /*dy*/)
{
	switch(Prm1)
	{
	case VC_EDIT_ENTPROP:
	case VC_EDIT_COPY	:
	case VC_EDIT_MOVE	:
	case VC_EDIT_ROTATE	:
	case VC_EDIT_SCALE	:
	case VC_EDIT_MIRROR	:
	case VC_EDIT_ERASE	:
	case VC_EDIT_EXPLODE:
	case VC_EDIT_CREBLOCK:
	case VC_EDIT_UNDO	:
	case VC_EDIT_REDO	:
	case VC_EDIT_CBCUT	:
	case VC_EDIT_CBCOPY	:
	case VC_EDIT_CBPASTE:
		m_bModified = true;
		::SendMessage( AfxGetMainWnd()->GetSafeHwnd() , WM_UPDATE_MAIN_TITLE, 0,0);
		break;
		
	case VC_FILE_CLOSEALL:
	case VC_FILE_CLOSE:
	case VC_FILE_NEW:	
	case VC_FILE_OPEN:
	case VC_FILE_SAVE:
	case VC_FILE_SAVEAS:
		break;
				
	case VC_DRAW_POINT   :
	case VC_DRAW_LINE    :
	case VC_DRAW_POLYLINE:
	case VC_DRAW_SPLINE  :
	case VC_DRAW_CIRC_CR :
	case VC_DRAW_CIRC_CD :
	case VC_DRAW_CIRC_2P :
	case VC_DRAW_CIRC_3P :
	case VC_DRAW_CIRC_TTT:
	case VC_DRAW_ARC_CSE :
	case VC_DRAW_ARC_CSA :
	case VC_DRAW_ARC_CSL :
	case VC_DRAW_ARC_SEM :
	case VC_DRAW_ARC_SME :
	case VC_DRAW_ARC_SCE :
	case VC_DRAW_ARC_SCA :
	case VC_DRAW_ARC_SCL :
	case VC_DRAW_ARC_SEA :
	case VC_DRAW_ARC_SED :
	case VC_DRAW_ARC_SER :
	case VC_DRAW_ARC_CONT:
	case VC_DRAW_SECTOR  :
	case VC_DRAW_ELLIPSE :
	case VC_DRAW_RECT    :
	case VC_DRAW_DIM_HOR :
	case VC_DRAW_DIM_VER :
	case VC_DRAW_DIM_PAR :
	case VC_DRAW_DIM_ANG :
	case VC_DRAW_DIM_RAD :
	case VC_DRAW_DIM_DIAM:
	case VC_DRAW_DIM_ORD :
	case VC_DRAW_HATCH   :

		m_bAddingEnt = true;
		EnableGuideLine(false);
		vlSetFocus();
		break;
	}


	return true;
}


bool CVeCad::OnRButtonDown(int /*nx*/, int /*ny*/, double/* dx*/, double /*dy*/)
{
	if (m_bGuideLine)
	{
		m_bGuideVert = !m_bGuideVert;
		return true;
	}
	else if ( g_Vl.IsEnableTrim() || g_Vl.IsEnableExt() )
	{
		m_pTrim->SetSrcLine();
		return true;
	}
	
	vlRedraw();

	return false;
}

void CVeCad::OnEntityAdd(int nIndex)
{	
	m_bAddingEnt = false;

	if (CVeCad::m_bExplode)
	{
		CvlEntity* pEnt = CvlEntity::GetEntity(nIndex);

		m_ExpAddArray.Add( pEnt );
	}
	else
	{
		CvlEntity* pEnt = CvlEntity::GetEntity(nIndex);

		if ( m_iLineType==DOT_LINE )
		{
			pEnt->m_bOwnColor	= TRUE;
			pEnt->m_iColor		= m_ColJumpVector;

			pEnt->UpdateData( false );
		}

		if (pEnt->m_iType>=VL_ENT_DIMLIN && pEnt->m_iType<=VL_ENT_DIMORD)
		{
			pEnt->m_bOwnColor	= TRUE;
			pEnt->m_iColor		= RGB(128, 128, 64);
			
			pEnt->UpdateData( false );
		}

		delete pEnt;
	}
	
	if ( !IsEnableGuideLine() )
		m_bModified = true;

	::SendMessage( AfxGetMainWnd()->GetSafeHwnd() , WM_UPDATE_MAIN_TITLE, 0,0);
}

bool CVeCad::IsEnableTrim()
{
	return m_pTrim->m_bEnableTrim;
}

bool CVeCad::EnableTrim(bool bEnable)
{
	m_pTrim->Free();

	bool bRet = m_pTrim->m_bEnableTrim;
	m_pTrim->m_bEnableTrim = bEnable;
	
	return bRet;
}

bool CVeCad::EnableExt(bool bEnable)
{
	m_pTrim->Free();
	
	bool bRet = m_pTrim->m_bEnableExt;
	m_pTrim->m_bEnableExt = bEnable;

	return bRet;
}

bool CVeCad::EnableGuideLine(bool bEnable)
{
	m_bGuideLine = bEnable;

	vlSetFocus();
	m_bGuideAdd = true;

	return m_bGuideLine;
}

bool CVeCad::IsEnableGuideLine()
{
	return m_bGuideLine;
}

bool CVeCad::IsEnableExt()
{
	return m_pTrim->m_bEnableExt;
}

bool CVeCad::IsEnableOffset()
{
	return (m_pTrim->m_bEnableOffset && m_pTrim->m_bOffsetMulti==false);	
}

bool CVeCad::IsEnableOffsetMulti()
{
	return (m_pTrim->m_bEnableOffset && m_pTrim->m_bOffsetMulti==true);	
}

bool CVeCad::EnableOffset(bool bEnable, bool bMulti)
{
	m_pTrim->Free();

	bool bRet = m_pTrim->m_bEnableOffset;

	m_pTrim->m_bEnableOffset= bEnable;
	m_pTrim->m_bOffsetMulti	= bMulti;

	vlSelect(false, -1);

	return bRet;
}

void CVeCad::SetOffsetParameter(double dOffset, int nCount)
{
	m_pTrim->SetOffsetParameter(dOffset, nCount);
}

void CVeCad::GetOffsetParameter(double* pdOffset, int* pnCount)
{
	m_pTrim->GetOffsetParameter(pdOffset, pnCount);
}

void CVeCad::FileSaveHpgl(LPCTSTR lpszPathName)
{
//	ASSERT(lpszPathName!=NULL);

	strcpy(m_szFileName, lpszPathName);


	// CAD 정보를 실제 폰트에 넣는것이 아니라 임시 오브젝트인 Hpgl 에 넣는다.
	CDHpgl Hpgl;
	CanvasToFont( &Hpgl ); 

	Hpgl.SaveAsPLT( lpszPathName );

	m_bModified = false;
}

void CVeCad::FileExportDxf(LPCTSTR /*lpszPathName*/)
{
	vlExecute(VC_EXPORT_DXF);
	//vlFileSave(VL_FILE_DXF, lpszPathName);
}

void CVeCad::FileLoadDxf(LPCTSTR lpszPathName)
{
	// vlFileLoad 함수 호출시 Canvas 가 재생성되므로 가이드 레이어와 
	// 점프벡터 설정은 함수 호출 후에 한다.

	// 2003.02.15   필드 셋팅 추가 start
/*	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	// 2003.02.15   필드 셋팅 추가 end

	if (IsClosed()==true)
		CanvasNew();
	else
	{
		vlClear(true);
		vlRedraw();
	}
		
	if (vlExecute(VC_IMPORT_DXF)==TRUE)
	{	
		strcpy(m_szFileName, lpszPathName);	

		CanvasInit();

		m_bModified = false;

		CDHpgl HpglData;

		CanvasToFont(&HpglData);
	
		CRect Rect = HpglData.FindMyRect();
		CGUtility Util;

		// 2003.02.15   필드 셋팅 추가 start
		double dRight	= Util.LSBtoMM( Rect.right, pFrame->Field_Size_Mm );
		double dBottom	= Util.LSBtoMM( Rect.bottom, pFrame->Field_Size_Mm );
		double dLeft	= Util.LSBtoMM( Rect.left, pFrame->Field_Size_Mm );
		double dTop		= Util.LSBtoMM( Rect.top, pFrame->Field_Size_Mm );
		// 2003.02.15   필드 셋팅 추가 end
//		double dRight	= Util.LSBtoMM( Rect.right );
//		double dBottom	= Util.LSBtoMM( Rect.bottom );
//		double dLeft	= Util.LSBtoMM( Rect.left );
//		double dTop		= Util.LSBtoMM( Rect.top );

		AddGuideRect( (dRight+dLeft)/2, (dBottom+dTop)/2, dRight-dLeft, dBottom-dTop);//, true );
	}
	else
		CanvasClose();
		*/
}

bool CVeCad::FileLoadHpgl(LPCTSTR lpszPathName)
{
/*	// 2003.02.15   필드 셋팅 추가 start
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	// 2003.02.15   필드 셋팅 추가 end

	CDHpgl HpglData;

	if (HpglData.LoadFile(lpszPathName)==TRUE && CanvasNew()==true)
	{
		CRect Rect = HpglData.FindMyRect();
		CGUtility Util;
		// 2003.02.15   필드 셋팅 추가 start
		double dRight	= Util.LSBtoMM( Rect.right, pFrame->Field_Size_Mm );
		double dBottom	= Util.LSBtoMM( Rect.bottom, pFrame->Field_Size_Mm );
		double dLeft	= Util.LSBtoMM( Rect.left, pFrame->Field_Size_Mm );
		double dTop		= Util.LSBtoMM( Rect.top, pFrame->Field_Size_Mm );
		// 2003.02.15   필드 셋팅 추가 end
//		double dRight	= Util.LSBtoMM( Rect.right );
//		double dBottom	= Util.LSBtoMM( Rect.bottom );
//		double dLeft	= Util.LSBtoMM( Rect.left );
//		double dTop		= Util.LSBtoMM( Rect.top );

		AddGuideRect( (dRight+dLeft)/2, (dBottom+dTop)/2, dRight-dLeft, dBottom-dTop);//, true );

		HpglData.DrawCanvas();
		strcpy(m_szFileName, lpszPathName);	
		m_bModified = false;

		return true;
	}
*/
	return false;
}

int CVeCad::GetEntityCount()
{	
	// GUIDE 레이어가 아닌 작업 레이어의 엔티티 개수를 리턴.
	int nLayerIndex = vlLayerIndex(NULL, 0);

	if (nLayerIndex<0)
		return 0;

//	int temp = vlPropGetInt(VD_DWG_N_ENT, nLayerIndex);
	int Cnt		= 0;//
	int nIndex	= vlGetEntity( VL_EI_FIRST,  VL_DRAWING, 0 );

	do
	{
		if ( vlPropGetInt( VD_ENT_LAYER, nIndex)!=nLayerIndex )//only Active Layer 
			continue; 

		Cnt++;
	}while ( (nIndex = vlGetEntity( VL_EI_NEXT, 0, 0) ) >=0 );

	return Cnt;
}

int CVeCad::GetEntityIndex(int Num, bool bSel)
{
//	ASSERT(Num>=0);
	
	int iIndex	= vlGetEntity( VL_EI_FIRST, (bSel==true) ? VL_SELECTION : VL_DRAWING, 0 );
	int nLayerActive = vlLayerIndex(NULL, 0);

	///////////////////////////

	do
	{
		if ( vlPropGetInt( VD_ENT_LAYER, iIndex)!=nLayerActive )//only Active Layer 
			continue; 

		if (--Num < 0)
			break;

	}while ( (iIndex = vlGetEntity( VL_EI_NEXT, 0, 0) ) >=0 );

	///////////////////////////

/*	while (1)
	{
		int iIndex = vlPropGetInt( VD_ENT_LAYER, iIndex);

		if ( ==nLayerActive )
		{
			if (--Num < 0)
				break;
		}

		iIndex	= vlGetEntity(VL_EI_NEXT, 0, 0);
	}
*/
	return iIndex;
}

bool CVeCad::CanvasToFont(CDHpgl*	pChar)
{
	if (	vlPageCount()==0 && 
			AfxMessageBox("logo data is empty. Do you want to save ?", MB_YESNO)!=IDYES )
		return false;

	pChar->Clear();	
	
	//////////////////////////////////
	EditExplodeAll();

	int nCntLayer	= vlLayerCount();
	int nGuideLayer	= vlLayerIndex("GUIDE", 0);
	int nOldLayer	= vlLayerIndex(NULL, 0);

	for (int l=0; l<nCntLayer; l++)
	{
		int nActiveLayer = vlLayerActive(l);

		// 활성화 실패 혹은 가이드 레이어일 경우 PASS
		if (nActiveLayer<0 || nActiveLayer==nGuideLayer)
			continue;

		// 레이어 안에서의 엔티티 처리.	
		int Cnt		= GetEntityCount();//vlPropGetInt(VD_LAYER_N_REF, nActiveLayer);//

		for (int i=0; i<Cnt; i++)
		{
			int	iIndex	= GetEntityIndex(i, false);

			CvlEntity* pEnt = CvlEntity::GetEntity(iIndex);
			if (pEnt == NULL)
				continue;

			// Dim 은 Hpgl 로 보내지 않는다. 
			if (!(pEnt->m_iType>=VL_ENT_DIMLIN && pEnt->m_iType<=VL_ENT_DIMORD))
			{			
				EntityToHpgl(pEnt, pChar);
			}

			delete pEnt;
		}
	}

	// 이전 활성 레이어 복구
	vlLayerActive(nOldLayer);

	pChar->FindMyRect();

	return true;
}

void	CVeCad::AddVector(VECTORARRAY* pArray, double dx, double dy, int nCmd)
{
/*//	ASSERT( pArray != NULL );
	// 2003.02.12   필드 셋팅
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	CGUtility	Util;
	CDVector	Vector;

	// 2003.02.12   필드 셋팅
	Vector.m_Point.x= Util.MMtoLSB( dx, pFrame->Field_Size_Mm);
	Vector.m_Point.y= Util.MMtoLSB( dy, pFrame->Field_Size_Mm);
//	Vector.m_Point.x= Util.MMtoLSB( dx, FIELD_SIZE_MM);
//	Vector.m_Point.y= Util.MMtoLSB( dy, FIELD_SIZE_MM);
	Vector.m_nCmd	= nCmd;

	pArray->Add(Vector);
	*/
}

void CVeCad::FileSetName(LPCTSTR lpszFileName)
{
	strcpy(m_szFileName, lpszFileName );
}

LPCTSTR CVeCad::FileGetName()
{
	return m_szFileName;
}

bool CVeCad::IsClosed()
{
	return m_bClosed;
}

void CVeCad::SetModified(bool bModified)
{
	m_bModified = bModified;
}

bool CVeCad::IsModified()
{
	return m_bModified;
}

bool CVeCad::SnapGet(long nSnapID)
{
//	ASSERT(nSnapID>=0 && nSnapID<SNAPMODE);

	return m_bSnapMode[nSnapID];
}

void CVeCad::SnapSet(long nSnapID, bool bStatus)
{
//	ASSERT( nSnapID>=0 && nSnapID<SNAPMODE );

	if (m_bSnapMode[nSnapID]!= bStatus)
	{
		m_bSnapMode[nSnapID] = !m_bSnapMode[nSnapID];

		switch(nSnapID)
		{
		case SNAPMODE_GRID_NODES	:
			vlExecute(VC_SNAP_GRID);	break;
			break;
		case SNAPMODE_POLAR			:
			vlExecute(VC_SNAP_POLAR);	break;
			break;
		case SNAPMODE_GRIPS			:
			vlExecute(VC_SNAP_GRIPS);	break;
			break;
		case SNAPMODE_POINT			:
			vlExecute(VC_SNAP_POINT);	break;
			break;
		case SNAPMODE_NEAREST		:
			vlExecute(VC_SNAP_NEAR);	break;
			break;
		case SNAPMODE_END			:
			vlExecute(VC_SNAP_END);		break;
			break;
		case SNAPMODE_MIDDLE		:
			vlExecute(VC_SNAP_MID);		break;
			break;
		case SNAPMODE_INTER			:
			vlExecute(VC_SNAP_INTER);	break;
			break;
		case SNAPMODE_CENTER		:
			vlExecute(VC_SNAP_CEN);		break;
			break;
		case SNAPMODE_PERPENDICULAR	:
			vlExecute(VC_SNAP_PERP);	break;
			break;
		case SNAPMODE_TANGENT		:
			vlExecute(VC_SNAP_TANG);	break;
			break;
		}
	}

}



void CVeCad::InitSnap()// 무조건 설정 변수를 VeCad 로(가져오는게 안되더라.)
{
	vlPropPutDbl(VD_DWG_PSNAPANGLE, -1, m_fSnapAngle);
	vlPropPutDbl(VD_DWG_PSNAPDIST, -1, 0.0001);  //  

	// Clear 상태에서 Snap 을 m_bSnapMode 에 맞게 설정해주므로
	// CanvasNew 호출 중에만 한번 부른다.
	for (int i=0; i<SNAPMODE; i++)
	{
		if (m_bSnapMode[i]==true)
		{
			switch(i)
			{
			case SNAPMODE_GRID_NODES	:
				vlExecute(VC_SNAP_GRID);	break;
				break;
			case SNAPMODE_POLAR			:
				vlExecute(VC_SNAP_POLAR);	break;
				break;
			case SNAPMODE_GRIPS			:
				vlExecute(VC_SNAP_GRIPS);	break;
				break;
			case SNAPMODE_POINT			:
				vlExecute(VC_SNAP_POINT);	break;
				break;
			case SNAPMODE_NEAREST		:
				vlExecute(VC_SNAP_NEAR);	break;
				break;
			case SNAPMODE_END			:
				vlExecute(VC_SNAP_END);		break;
				break;
			case SNAPMODE_MIDDLE		:
				vlExecute(VC_SNAP_MID);		break;
				break;
			case SNAPMODE_INTER			:
				vlExecute(VC_SNAP_INTER);	break;
				break;
			case SNAPMODE_CENTER		:
				vlExecute(VC_SNAP_CEN);		break;
				break;
			case SNAPMODE_PERPENDICULAR	:
				vlExecute(VC_SNAP_PERP);	break;
				break;
			case SNAPMODE_TANGENT		:
				vlExecute(VC_SNAP_TANG);	break;
				break;
			}
		}
	}
}


void CVeCad::GridSet(VLPOINT dPtStep, COLORREF Col, int iGridTypeMain, VLPOINT dPtStepBold, COLORREF BCol, int iGridTypeBold)
{
	m_dPtGridStep	= dPtStep;
	m_dPtGridBStep	= dPtStepBold;
	m_GridCol		= Col;
	m_GridBCol		= BCol;
	m_iGridTypeMain	= iGridTypeMain;
	m_iGridTypeBold = iGridTypeBold;

	GridUpdate(false);
}

void CVeCad::GridGet(VLPOINT* pdPtStep, COLORREF* pCol, int* piGridTypeMain, VLPOINT* pdPtBStep, COLORREF* pBCol, int* piGridTypeBold)
{
	*pdPtStep		= m_dPtGridStep;
	*pdPtBStep		= m_dPtGridBStep;
	*pCol			= m_GridCol;
	*pBCol			= m_GridBCol;
	*piGridTypeMain	= m_iGridTypeMain;
	*piGridTypeBold	= m_iGridTypeBold;
}

void CVeCad::GridUpdate(bool bSaveAndValidate)
{
	int nIndex = vlPageIndex(NULL, 0);

	if (bSaveAndValidate==true)
	{
		m_dPtGridStep.x	= vlPropGetDbl(VD_GRID_DX,		nIndex);
		m_dPtGridStep.y	= vlPropGetDbl(VD_GRID_DY,		nIndex);
		m_GridCol		= vlPropGetInt(VD_GRID_COLOR,	nIndex);
		m_iGridTypeMain	= vlPropGetInt(VD_GRID_TYPE,	nIndex);

		m_dPtGridBStep.x= vlPropGetInt(VD_GRID_BSTEPX,	nIndex);
		m_dPtGridBStep.y= vlPropGetInt(VD_GRID_BSTEPY,	nIndex);
		m_GridBCol		= vlPropGetInt(VD_GRID_BCOLOR,	nIndex);
		m_iGridTypeBold	= vlPropGetInt(VD_GRID_BTYPE,	nIndex);
	}
	else
	{
		vlPropPutDbl(VD_GRID_X0,	nIndex, 0);
		vlPropPutDbl(VD_GRID_Y0,	nIndex, 0);

		vlPropPutDbl(VD_GRID_DX,	nIndex,	m_dPtGridStep.x);
		vlPropPutDbl(VD_GRID_DY,	nIndex,	m_dPtGridStep.y);
		vlPropPutInt(VD_GRID_COLOR,	nIndex,	m_GridCol);

		vlPropPutInt(VD_GRID_BSTEPX,nIndex,	(int)m_dPtGridBStep.x);
		vlPropPutInt(VD_GRID_BSTEPY,nIndex,	(int)m_dPtGridBStep.y);
		vlPropPutInt(VD_GRID_BCOLOR,nIndex,	m_GridBCol);

		vlPropPutInt(VD_GRID_TYPE, nIndex, m_iGridTypeMain);
		vlPropPutInt(VD_GRID_BTYPE, nIndex, m_iGridTypeBold);


		vlUpdate();
		vlRedraw();
	}
}

int CVeCad::GetLineType()
{
	return m_iLineType;
}

void CVeCad::SetLineType(int iType)
{
	int nIndex = -1;
	
	m_iLineType = iType;

	if (iType==SOLID_LINE)
		nIndex = vlStLineIndex("Solid", 0);

	else if (iType==DOT_LINE)
		nIndex = vlStLineIndex("DOT", 0);
	
	//ASSERT(nIndex!=-1);
	if(nIndex >=0 )
		vlStLineActive(nIndex);
}

void CVeCad::SetJumpVector(double dLineWidth, double dDotInterval, COLORREF Color)
{
	m_dJumpLineWidth	= dLineWidth;
	m_dJumpDotInterval	= dDotInterval;
	m_ColJumpVector		= Color;

	if (dLineWidth==0.0 && dDotInterval==0.0)
		strcpy(m_szJumpLineDesc, "");
	else
		sprintf(m_szJumpLineDesc, "%.2lf,-%.2lf", dLineWidth, dDotInterval);
	
	int nStLineIndex = vlStLineIndex("DOT", 0);

	vlPropPut(VD_STLINE_DESC, nStLineIndex, (void*)m_szJumpLineDesc );

	int Size = GetEntityCount();

	for (int i=0; i<Size; i++)
	{
		int			nIndex	= g_Vl.GetEntityIndex(i, false);
		CvlEntity*	pEnt	= CvlEntity::GetEntity( nIndex );
		
		if (pEnt->m_iStLine==nStLineIndex)
		{
			pEnt->m_iColor = Color;
			pEnt->UpdateData(false);
		}

		delete pEnt;
	}
//	vlPropPutInt(VD_LAYER_COLOR, 0/*vlLayerIndex( "GUIDE", 0 )*/, Color);
}

void CVeCad::GetJumpVector(double* pdLineWidth, double* pdDotInterval, COLORREF* pColor)
{
	*pdLineWidth	= m_dJumpLineWidth;
	*pdDotInterval	= m_dJumpDotInterval;
	*pColor			= m_ColJumpVector;
}

void CVeCad::AddGuideRect(double dCenterX, double dCenterY, double dSizeX, double dSizeY)
{
	// Add Page Guide Rect
	int nOld	= vlLayerIndex( NULL, 0 );
	int nIndex	= vlLayerIndex( "GUIDE", 0 );
	
	vlLayerActive( nIndex );

	int nOldLineType = GetLineType();
	
	SetLineType( SOLID_LINE );

	CvlRect* pRect		= new CvlRect;

	pRect->m_dCoord.x	= dCenterX;
	pRect->m_dCoord.y	= dCenterY;
	pRect->m_dWidth		= dSizeX;
	pRect->m_dHeight	= dSizeY;

	pRect->AddToCanvas();

//	int nGuideIndex = vlAddRect( dCenterX, dCenterY, dSizeX, dSizeY, 0.0, 0.0 );	
	m_GuideRectArray.Add( pRect );//(CvlRect*)CvlEntity::GetEntity(nGuideIndex) );

	m_dGuideRectMaxLeftTop.x	= dCenterX;
	m_dGuideRectMaxLeftTop.y	= dCenterY;
	m_dGuideRectMaxRightBtm.x	= dCenterX;
	m_dGuideRectMaxRightBtm.y	= dCenterY;

	UpdateGuideRect();

	SetLineType(nOldLineType);

	if (nOld==nIndex)
		nOld--;

	vlLayerActive( nOld );

	m_bModified = false;

	vlRedraw();
}

bool CVeCad::CloseQuery()
{
/*	char szText[128]={0,};
	char szFileName[MAX_PATH]={0,};
	
	strcpy(szFileName, FileGetName() );

	if (strlen(szFileName)==0)
		strcpy(szFileName, "Noname");
	sprintf(szText, "Save Changes in Logo file \"%s\"?",  szFileName);
	
	int Ret = -1;

	if ( ( m_bModified == true) && 
		 (Ret = AfxMessageBox( szText, MB_YESNOCANCEL )) == IDYES )
		::SendMessage( AfxGetMainWnd()->GetSafeHwnd() , WM_COMMAND,  ID_FILE_SAVE_HPGL, 0 );

	else if (Ret==IDCANCEL)
		return false;
*/
	return true;
}

void CVeCad::RemoveAllGuideLine()
{
	int Size = m_GuideLineArray.GetSize();

	for (int i=0; i<Size; i++)
	{
		CvlLine* pLine = m_GuideLineArray.GetAt(i);
		pLine->Erase();

		delete pLine;
	}

	m_GuideLineArray.RemoveAll();

	m_bModified = false;
}

void CVeCad::CanvasClear(bool bDelGuideRect)
{
	vlClear(TRUE);
	CanvasInit();

	// vlClear() 는 추가한 Line 속성까지 제거하지만, Grid , Snap 은 변화시키지 않는다.
	// 하지만 CanvasInit() 는 라인스타일을 복원시키면서 Grid , Snap 을 뒤집어 놓는다.
	// 그래서 다시 한번 뒤집어 정상으로 바꾼다.

	GridUpdate(false);	
	InitSnap();

	if (bDelGuideRect==false)
	{
		AddGuideRect(	(m_dGuideRectMaxRightBtm.x + m_dGuideRectMaxLeftTop.x)/2, 
						(m_dGuideRectMaxRightBtm.y + m_dGuideRectMaxLeftTop.y)/2 , 
						m_dGuideRectMaxRightBtm.x - m_dGuideRectMaxLeftTop.x, 
						m_dGuideRectMaxLeftTop.y - m_dGuideRectMaxRightBtm.y);//, true);
	}
}

void CVeCad::SnapSetAngle(double fAngle)
{
	m_fSnapAngle = fAngle*M_PI/180;
	
	vlPropPutDbl(VD_DWG_PSNAPANGLE, -1, m_fSnapAngle);
}

double CVeCad::SnapGetAngle()
{
	return m_fSnapAngle*180/M_PI;
}

void CVeCad::GridShow(bool bShow)
{
	if (m_bGridShow!=bShow)
	{
		m_bGridShow=bShow;
		
		vlPropPutInt(VD_DWG_SHOWGRID, -1, m_bGridShow);
	}
}

bool CVeCad::GridIsShow()
{
	return m_bGridShow;
}

void CVeCad::WaitForMsg()
{
	while (m_bMsgWait)
	{
		Sleep(5);
	}
}

void CVeCad::RegisterMsg(UINT nMsg)
{
	m_nMsgWait = nMsg;
	m_bMsgWait = true;
}

void CVeCad::SetContextMenu(UINT nID)
{
	m_nMenuID = nID;
}

void CVeCad::GetOuterRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom)
{
//	ASSERT(pdLeft!=NULL && pdTop!=NULL && pdRight!=NULL && pdBottom!=NULL);

	double	dLeftMin	= (double)0x7fffffffffffffff, 
			dTopMax		= (double)-0x7fffffffffffffff, 
			dRightMax	= (double)-0x7fffffffffffffff, 
			dBottomMin	= (double)0x7fffffffffffffff;

	int nSize = GetEntityCount();

	for (int i=0; i<nSize; i++)
	{
		int			nIndex	= GetEntityIndex(i, false);
		CvlEntity*	pEnt	= CvlEntity::GetEntity(nIndex);

		double dLeft, dTop, dRight, dBottom;

		pEnt->GetOuterRect(&dLeft, &dTop, &dRight, &dBottom);

		delete pEnt;

		if (dLeft < dLeftMin)			dLeftMin	= dLeft;
		if (dRight >= dRightMax)		dRightMax	= dRight;
		if (dTop >= dTopMax)			dTopMax		= dTop;
		if (dBottom < dBottomMin)		dBottomMin	= dBottom;
	}

	*pdLeft		= dLeftMin;
	*pdRight	= dRightMax;
	*pdTop		= dTopMax;
	*pdBottom	= dBottomMin;
}

void CVeCad::EditMoveAll(double dx, double dy)
{
	int nSize = GetEntityCount();

	VLPOINT PtOffset = {dx, dy};

	for (int i=0; i<nSize; i++)
	{
		CvlEntity* pEnt = CvlEntity::GetEntity(GetEntityIndex(i, false));
		pEnt->Move(PtOffset);

		delete pEnt;

		//vlMove( , dx, dy);
	}

	vlUpdate();

	vlRedraw();
}

void CVeCad::GetGuideRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom)
{
	*pdLeft		= m_dGuideRectMaxLeftTop.x ;
	*pdTop		= m_dGuideRectMaxLeftTop.y ;
	*pdRight	= m_dGuideRectMaxRightBtm.x;
	*pdBottom	= m_dGuideRectMaxRightBtm.y;
}

void CVeCad::EditExplodeAll()
{
	// Polygon 으로 변신 ////////////////////////////////
	int	Cnt	= GetEntityCount();

	CArray<CvlEntity*, CvlEntity*> aEntity;

	// 엔티티 개체 포인터 배열 준비. 
	// HATCH 나 BLOCK 이면 배열의 맨 앞으로 넣어서 먼저 Explode 되게 한다.
	for (int i=0; i<Cnt; i++)
	{
		CvlEntity* pEnt = CvlEntity::GetEntity( GetEntityIndex(i, false) );
		
		if (pEnt!=NULL)
		{
			// 해치, 블록일 경우 먼저 익스플로드.
			if (pEnt->m_iType==VL_ENT_HATCH || pEnt->m_iType==VL_ENT_INSBLOCK)
			{
				aEntity.InsertAt(0, pEnt);	
			}
			else if (pEnt->m_iType>=VL_ENT_DIMLIN && pEnt->m_iType<=VL_ENT_DIMORD)
			{// Explode 하면서, Dimension 은 무시.
				delete pEnt;
				continue;
			}
			else
			{
				aEntity.Add( pEnt );
			}
		}
		else//DEBUG
		{
			TRACE("pEnt 는 NULL 이 되면 안된다. \n");
//			ASSERT(pEnt!=NULL);			
		}
	}

	// 각 엔티티를 익스플로드.
	Cnt = aEntity.GetSize();

	// 2003.02.05   판단으로 보아 시간 많이 걸림
	// So 임시 주석
	for(i=0; i<Cnt; i++)
	{
		CvlEntity* pEnt = aEntity.GetAt(i);
		pEnt->Explode(VL_ENT_POLY);
		delete pEnt;
	}

	aEntity.RemoveAll();

	////////////////////////////////

	int Size = CVeCad::m_ExpAddArray.GetSize();

	for (i = 0; i<Size; i++)
		delete CVeCad::m_ExpAddArray.GetAt(i);

	CVeCad::m_ExpAddArray.RemoveAll();

	vlUpdate();
}

bool CVeCad::EntityToHpgl(CvlEntity *pEnt, CDHpgl *pChar)
{
	// 0 : Solid Line, 1 : DOT Line
	int nEndCmd = 0;
	
	// 2003.03.20   수정 dxf 다중 레이어 관련
	// 원본 	if (pEnt->m_iStLine!=0)
	if (pEnt->m_iStLine==1)
		nEndCmd = CDVector::PEN_UP;
	else
		nEndCmd = CDVector::PEN_DOWN;
	
	bool	bFirstEnt	= true;
	VLPOINT PtPrev		= { 0.0 , 0.0 };
	
	switch(pEnt->m_iType)
	{
	case VL_ENT_POINT:{
		CvlPoint* pPt = (CvlPoint*)pEnt;
		
		AddVector(&pChar->m_aVectorData, pPt->m_dCoord.x, pPt->m_dCoord.y, nEndCmd);
		
		PtPrev.x = pPt->m_dCoord.x;
		PtPrev.y = pPt->m_dCoord.y;
		
		break;}

	case VL_ENT_LINE:{
		CvlLine* pLine = (CvlLine*)pEnt;
		
		if ( (PtPrev.x != pLine->m_dLine1.x) || (PtPrev.y != pLine->m_dLine1.y) || (bFirstEnt==true) )
		{
			AddVector(	&pChar->m_aVectorData, pLine->m_dLine1.x, pLine->m_dLine1.y, CDVector::PEN_UP);
			bFirstEnt = false;
		}
		
		AddVector(	&pChar->m_aVectorData, pLine->m_dLine2.x,pLine->m_dLine2.y,	nEndCmd);
		
		PtPrev.x = pLine->m_dLine2.x;
		PtPrev.y = pLine->m_dLine2.y;
		
		break;}

	case VL_ENT_POLY:{
		CvlPoly* pPoly = (CvlPoly*)pEnt;
		
		if ( (PtPrev.x != pPoly->m_pdVert[0].x) || (PtPrev.y != pPoly->m_pdVert[0].y) || (bFirstEnt == true) )
			
		{
			AddVector(	&pChar->m_aVectorData, pPoly->m_pdVert[0].x, pPoly->m_pdVert[0].y, CDVector::PEN_UP);
			
			bFirstEnt = false;
		}
		
		for (int i=1; i<pPoly->m_iNoVer; i++)
			AddVector(	&pChar->m_aVectorData, pPoly->m_pdVert[i].x, pPoly->m_pdVert[i].y, nEndCmd);
		
		PtPrev.x = pPoly->m_pdVert[pPoly->m_iNoVer-1].x;
		PtPrev.y = pPoly->m_pdVert[pPoly->m_iNoVer-1].y;
		
		break;}
	}

	return true;
}

bool CVeCad::SearchInGuideObj(CvlEntity* /*pEnt*/)
{
//	m_GuideLineArray

	return true;
}

void CVeCad::UpdateGuideRect()
{
	int Size = m_GuideRectArray.GetSize();

	for (int i=0; i<Size; i++)
	{
		CvlRect* pRect = m_GuideRectArray.GetAt(i);

		if (pRect->m_iType==VL_ENT_RECT)
		{
			// 최외각 Gudie Rect 를 찾는다. 
			VLPOINT dPtTemp1 = {pRect->m_dCoord.x - pRect->m_dWidth/2, pRect->m_dCoord.y + pRect->m_dHeight/2};//Left Top
			VLPOINT dPtTemp2 = {pRect->m_dCoord.x + pRect->m_dWidth/2, pRect->m_dCoord.y - pRect->m_dHeight/2};//Right Bottom
	
			if (m_dGuideRectMaxLeftTop.x >= dPtTemp1.x)
				m_dGuideRectMaxLeftTop.x = dPtTemp1.x;

			if (m_dGuideRectMaxLeftTop.y <= dPtTemp1.y)
				m_dGuideRectMaxLeftTop.y = dPtTemp1.y;

			if (m_dGuideRectMaxRightBtm.x <= dPtTemp2.x)
				m_dGuideRectMaxRightBtm.x = dPtTemp2.x;

			if (m_dGuideRectMaxRightBtm.y >= dPtTemp2.y)
				m_dGuideRectMaxRightBtm.y = dPtTemp2.y;
		}
	}
}


bool CVeCad::InitNoView()
{
/*	if (ReleaseNoView()==true)
	{

		CWnd* pWndVecTemp = CWnd::FromHandle(m_hVec);
		m_pNoView = new CNoView;

		if (m_pNoView->Create(WS_CHILD | WS_VISIBLE, pWndVecTemp))
		{
			m_pNoView->SendMessage(WM_UPDATE_NO);
			return true;
		}
		else
		{
			delete m_pNoView;
			m_pNoView = NULL;
		}
	}
	*/

	return false;
}

bool CVeCad::ReleaseNoView()
{
/*	if (m_pNoView)
	{
		m_pNoView->DestroyWindow();
		delete m_pNoView;
		m_pNoView = NULL;
	}	
	*/

	return true;
}
