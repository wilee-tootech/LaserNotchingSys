// DlgView.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgView dialog


CDlgView::CDlgView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgView)
	m_iSelBoxSize = 0;
	m_iRulerSize = 0;
	m_iRulerFontSize = 0;
	m_iRulerScaleSize = 0;
	//}}AFX_DATA_INIT
}


void CDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgView)
	DDX_Control(pDX, IDC_PIC_SELBOX, m_ctlSelBox);
	DDX_Control(pDX, IDC_PIC_RULER, m_ctlRuler);
	DDX_Control(pDX, IDC_PIC_GRIDSCALE, m_ctlGridScale);
	DDX_Control(pDX, IDC_PIC_GRIDLINE, m_ctlGridLine);
	DDX_Control(pDX, IDC_PIC_DEVOUTER, m_ctlDevOuter);
	DDX_Control(pDX, IDC_PIC_DEVLINE, m_ctlDevLine);
	DDX_Control(pDX, IDC_PIC_DEVINNER, m_ctlDevInner);
	DDX_Text(pDX, IDC_SIZE_SELBOX, m_iSelBoxSize);
	DDX_Text(pDX, IDC_SIZE_RULER, m_iRulerSize);
	DDX_Text(pDX, IDC_SIZE_RULERFONT, m_iRulerFontSize);
	DDX_Text(pDX, IDC_SIZE_RULERSCALE, m_iRulerScaleSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgView, CDialog)
	//{{AFX_MSG_MAP(CDlgView)
	ON_BN_CLICKED(IDC_COL_DEVINNER, OnColDevInner)
	ON_BN_CLICKED(IDC_COL_DEVOUTER, OnColDevOuter)
	ON_BN_CLICKED(IDC_COL_DEVLINE, OnColDevline)
	ON_BN_CLICKED(IDC_COL_GRIDLINE, OnColGridline)
	ON_BN_CLICKED(IDC_COL_GRIDSCALE, OnColGridscale)
	ON_BN_CLICKED(IDC_COL_RULER, OnColRuler)
	ON_BN_CLICKED(IDC_COL_SELBOX, OnColSelbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgView message handlers

void CDlgView::OnColDevInner() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colDevInner);
	if (dlg.DoModal() == IDOK) {
		m_colDevInner = dlg.GetColor();
		m_ctlDevInner.m_col = m_colDevInner;
		m_ctlDevInner.Invalidate(FALSE);
//		SetColor(IDC_PIC_DEVINNER, m_colDevInner);
	}
}

void CDlgView::OnColDevOuter() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colDevOuter);
	if (dlg.DoModal() == IDOK) {
		m_colDevOuter = dlg.GetColor();
		m_ctlDevOuter.m_col = m_colDevOuter;
		m_ctlDevOuter.Invalidate(FALSE);
//		SetColor(IDC_PIC_DEVOUTER, m_colDevOuter);
	}	
}

BOOL CDlgView::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_ctlSelBox.m_col = m_colSelBox;
	m_ctlSelBox.Invalidate();
	m_ctlRuler.m_col = m_colRuler;
	m_ctlRuler.Invalidate();
	m_ctlGridScale.m_col = m_colGridScale;
	m_ctlGridScale.Invalidate();
	m_ctlGridLine.m_col = m_colGridLine;
	m_ctlGridLine.Invalidate();
	m_ctlDevOuter.m_col = m_colDevOuter;
	m_ctlDevOuter.Invalidate();
	m_ctlDevLine.m_col = m_colDevLine;
	m_ctlDevLine.Invalidate();
	m_ctlDevInner.m_col = m_colDevInner;
	m_ctlDevInner.Invalidate();

/*	SetColor(IDC_PIC_DEVINNER, m_colDevInner);
	SetColor(IDC_PIC_DEVOUTER, m_colDevOuter);
	SetColor(IDC_PIC_DEVLINE,  m_colDevLine);
	SetColor(IDC_PIC_GRIDLINE, m_colGridLine);
	SetColor(IDC_PIC_GRIDSCALE, m_colGridScale);
	SetColor(IDC_PIC_SELBOX, m_colSelBox);
	SetColor(IDC_PIC_RULER, m_colRuler);*/

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgView::OnColDevline() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colDevLine);
	if (dlg.DoModal() == IDOK) {
		m_colDevLine = dlg.GetColor();
		m_ctlDevLine.m_col = m_colDevLine;
		m_ctlDevLine.Invalidate(FALSE);
//		SetColor(IDC_PIC_DEVLINE, m_colDevLine);
	}	
}

void CDlgView::OnColGridline() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colGridLine);
	if (dlg.DoModal() == IDOK) {
		m_colGridLine = dlg.GetColor();
		m_ctlGridLine.m_col = m_colGridLine;
		m_ctlGridLine.Invalidate(FALSE);
//		SetColor(IDC_PIC_GRIDLINE, m_colGridLine);
	}		
}

void CDlgView::OnColGridscale() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colGridScale);
	if (dlg.DoModal() == IDOK) {
		m_colGridScale = dlg.GetColor();
		m_ctlGridScale.m_col = m_colGridScale;
		m_ctlGridScale.Invalidate(FALSE);
//		SetColor(IDC_PIC_GRIDSCALE, m_colGridScale);
	}		
}

void CDlgView::OnColRuler() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colRuler);
	if (dlg.DoModal() == IDOK) {
		m_colRuler = dlg.GetColor();
		m_ctlRuler.m_col = m_colRuler;
		m_ctlRuler.Invalidate(FALSE);
//		SetColor(IDC_PIC_RULER, m_colRuler);
	}		
}

void CDlgView::OnColSelbox() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	CString strColor;

//	dlg.SetCurrentColor(m_colSelBox);
	if (dlg.DoModal() == IDOK) {
		m_colSelBox = dlg.GetColor();
		m_ctlSelBox.m_col = m_colSelBox;
		m_ctlSelBox.Invalidate(FALSE);
//		SetColor(IDC_PIC_SELBOX, m_colSelBox);
	}		
}

void CDlgView::SetColor(int iID, int iColor)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(iID);
	RECT rtClientRect;
	CBrush brBrush;
	brBrush.CreateSolidBrush(iColor);
	pWnd->GetClientRect(&rtClientRect);
	pWnd->GetDC()->FillRect(&rtClientRect, &brBrush);
}
