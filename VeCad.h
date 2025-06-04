// VeCad.h: interface for the CVeCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECAD_H__8D531A32_6257_11D6_8790_00C026664D59__INCLUDED_)
#define AFX_VECAD_H__8D531A32_6257_11D6_8790_00C026664D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "Mru.h"
#include <afxtempl.h>
#include "DVector.h"
#include "vlEntity.h"

class CTrimmer;
class CDHpgl;
class CNoView;

#define SOLID_LINE	0
#define	DOT_LINE	1


#ifndef M_PI
#define M_PI ( 3.14159265358979323846 )
#endif

#define SNAPMODE_GRID_NODES			 0
#define SNAPMODE_POLAR				 1
#define SNAPMODE_GRIPS				 2
#define SNAPMODE_POINT				 3
#define SNAPMODE_NEAREST			 4
#define SNAPMODE_END				 5
#define SNAPMODE_MIDDLE				 6
#define SNAPMODE_INTER				 7
#define SNAPMODE_CENTER				 8
#define SNAPMODE_PERPENDICULAR		 9
#define SNAPMODE_TANGENT			10
#define SNAPMODE					11

class CVeCad
{
public:
	CVeCad();
	virtual ~CVeCad();

	friend class CvlEntity;
	friend class CTrimmer;

public:
	HWND		m_hVec;
	bool		m_bGuideAdd;//true = add, false = delete	


	//ggasa 2002 50 26
//	CConfig		m_Config;
	
protected:
	bool		m_bGuideLine;
	bool		m_bGuideVert;//true = vert, false = horz

	bool		m_bDisableCloseQuery;
	bool		m_bAddingEnt;

	int			m_iLineType;//DOT, SOLID

	VLPOINT		m_dGuideRectMaxLeftTop;
	VLPOINT		m_dGuideRectMaxRightBtm;

	int			m_VecX;
	int			m_VecY;
	int			m_SBarH;  // height of status bar

	CTrimmer*	m_pTrim;
	
	HWND		m_hMain;
	UINT		m_nMenuID;

	char		m_szFileName[MAX_PATH];
	bool		m_bModified;
	bool		m_bClosed;

	static bool	m_bExplode;
	static CArray<CvlEntity*, CvlEntity*>	m_ExpAddArray;
	static CArray<CvlLine*, CvlLine*>		m_GuideLineArray;
	static CArray<CvlRect*, CvlRect*>		m_GuideRectArray;

	// Grid 설정 변수
	VLPOINT		m_dPtGridStep;
	VLPOINT		m_dPtGridBStep;
	COLORREF	m_GridCol;
	COLORREF	m_GridBCol;
	int			m_iGridTypeMain;
	int			m_iGridTypeBold;
	bool		m_bGridShow;

	// snap 모드 상태 변수
	bool		m_bSnapMode[SNAPMODE];
	double		m_fSnapAngle;

	// Jump Vector 설정 변수
	double		m_dJumpLineWidth;
	double		m_dJumpDotInterval;
	char		m_szJumpLineDesc[32];
	COLORREF	m_ColJumpVector;

	// 내부 동기화 변수
	UINT		m_nMsgWait;
	bool		m_bMsgWait;


	// 벡터 넘버링 구현
	CNoView*	m_pNoView;

protected:
	void	UpdateGuideRect();
	bool	SearchInGuideObj(CvlEntity* pEnt);

	void	GridUpdate(bool bSaveAndValidate);
	
	void	InitSnap();
	
	void	AddVector(VECTORARRAY* pArray, double dx, double dy, int nCmd);
	void	OnEntityAdd(int nIndex);
	bool	OnRButtonDown(int nx, int ny, double dx, double dy);
	bool	OnLButtonDown(int nx, int ny, double dx, double dy);
	bool	OnKeyUp(int nVirtualKey, int /*RepeatCnt*/);
	bool	OnKeyDown(int nVirtualKey, int RepeatCnt);
	bool	OnMenuEdit(int nx, int ny, double dx, double dy);
	bool	OnExecute(int Prm1, int Prm2, double Prm3, double Prm4);
	bool	EntityToHpgl(CvlEntity* pEnt, CDHpgl* pChar);

	static int CALLBACK DwgProc (int iDwg, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5);

	void RegisterMsg(UINT nMsg);
	void WaitForMsg();

public:
	bool ReleaseNoView();
	bool InitNoView();
	void	AddGuideRect(double dCenterX, double dCenterY, double dSizeX, double dSizeY);//, bool bClear);
	void	AddGuideLine(int nx, int ny, double dx, double dy);

	void	RemoveAllGuideLine();
	void	RemoveGuideLine(int nx, int ny, double dx, double dy);
	
	//----------------
	static bool FormatVeCadCmd(UINT nCmd, LPTSTR szParam);
	static bool FormatVeCadMsg(UINT nMsg, LPTSTR szParam);
	static bool FormatVeCadEntity(int nType, LPTSTR szParam);

	void	GetGuideRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom);
	void	GetOuterRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom);
	bool	CloseQuery();

	bool	EnableGuideLine(bool bEnable);

	void	GridSet(VLPOINT dPtStep, COLORREF Col, int iGridTypeMain, VLPOINT dPtStepBold, COLORREF BCol, int iGridTypeBold);
	void	GridGet(VLPOINT* pdPtStep, COLORREF* pCol, int* piGridTypeMain, VLPOINT* pdPtBStep, COLORREF* pBCol, int* piGridTypeBold);
	bool	GridIsShow();
	void	GridShow(bool bShow);

	void	SnapSet(long nSnapID, bool bStatus);
	bool	SnapGet(long nSnapID);
	double	SnapGetAngle();
	void	SnapSetAngle(double fAngle);

	int		GetLineType();
	void	SetLineType(int iType);
	void	SetJumpVector(double dLineWidth, double dDotInterval, COLORREF Color);
	void	GetJumpVector(double* pdLineWidth, double* pdDotInterval, COLORREF* pColor);
	
	bool	IsClosed();
	bool	IsModified();
	void	SetModified(bool bModified);
	int		GetEntityIndex(int Num, bool bSel);
	int		GetEntityCount();
		
	//----------------
	bool	IsEnableGuideLine();
	bool	IsEnableOffset();
	bool	IsEnableOffsetMulti();
	bool	IsEnableTrim();
	bool	IsEnableExt();

	bool	EnableOffset(bool bEnable, bool bMulti);	
	bool	EnableTrim(bool bEnable);
	bool	EnableExt(bool bEnable);

	void	SetOffsetParameter(double dOffset, int nCount);
	void	GetOffsetParameter(double* pdOffset, int* pnCount);

	//----------------
	LPCTSTR	FileGetName();
	void	FileSetName(LPCTSTR lpszFileName);
	void	FileSaveHpgl(LPCTSTR lpszPathName);
	bool	FileLoadHpgl(LPCTSTR lpszPathName);
	void	FileLoadDxf(LPCTSTR lpszPathName);
	void	FileExportDxf(LPCTSTR lpszPathName);

	void	InitVeCad();
	void	SetFocus();
	void	Resize(int xStart, int yStart, int cx, int cy);
	void	SetContextMenu(UINT nID);

	bool	CanvasToFont(CDHpgl*	pChar);
	void	CanvasCreate(HWND hWndMain);
	bool	CanvasNew();
	void	CanvasClose();	
	void	CanvasClear(bool bDelGuideRect);
	void	CanvasInit();


	void Print();

	void Reset();

	void LineWidth();

	void DrawLine();
	void DrawPolyline();
	void DrawSpline();
	void DrawPoint();
	void DrawCircCR();
	void DrawCircCD();
	void DrawCirc2P();
	void DrawCirc3P();
	void DrawArcCSE();
	void DrawArcSEM();
	void DrawArcSME();
	void DrawEllipse();
	void DrawRect();
	void DrawHatch();
	void DrawDimHor();
	void DrawDimVer();
	void DrawDimPar();
	void DrawDimAng();
	void DrawDimRad();
	void DrawDimDiam();
	void DrawDimOrd();
	
	void Zoom(double dZoomFactor);

	void EditCbCut();
	void EditCbCopy();
	void EditCbPaste();
	void EditEntprop();
	void EditRedo();
	void EditUndo();
	void EditCopy();
	void EditTrim();
	void EditScale();
	void EditCreblock();
	void EditErase();
	void EditExplode();
	void EditExtend();
	void EditFillet();
	void EditMirror();
	void EditMove();
	void EditRotate();
	void EditMoveAll(double dx, double dy);
	void EditExplodeAll();

	void InsText();
	void InsSymbol();
	void InsBlock();
	void InsImage();
	void InsRMap();

	void FmtLayout(int iCmd);

	void ToolDist();
	void ToolPrnRect();
	void ToolStat();

	void SelByPoint();
	void SelByRect();
	void SelByPolygon();

	void InsGlass();

	//ggasa 2002 -5 26
//	void OpenMruFile (int i);
};

#endif // !defined(AFX_VECAD_H__8D531A32_6257_11D6_8790_00C026664D59__INCLUDED_)
