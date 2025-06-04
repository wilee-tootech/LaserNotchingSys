// DlgSetAuthority.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgSetAuthority.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetAuthority dialog


CDlgSetAuthority::CDlgSetAuthority(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetAuthority::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetAuthority)
	m_alignAd = FALSE;
	m_alignEng = FALSE;
	m_alignOp = FALSE;
	m_autoMarkAd = FALSE;
	m_autoMarkEng = FALSE;
	m_autoMarkOp = FALSE;
	m_createAd = FALSE;
	m_createEng = FALSE;
	m_createOp = FALSE;
	m_editObjAd = FALSE;
	m_editObjEng = FALSE;
	m_editObjOp = FALSE;
	m_manualMarkAd = FALSE;
	m_manualMarkEng = FALSE;
	m_manualMarkOp = FALSE;
	m_markOrderAd = FALSE;
	m_markOrderEng = FALSE;
	m_markOrderOp = FALSE;
	m_newDocAd = FALSE;
	m_newDocEng = FALSE;
	m_newDocOp = FALSE;
	m_objMoveAd = FALSE;
	m_objMoveEng = FALSE;
	m_objMoveOp = FALSE;
	m_openDevAd = FALSE;
	m_openDevEng = FALSE;
	m_openDevOp = FALSE;
	m_openMarkAd = FALSE;
	m_openMarkEng = FALSE;
	m_openMarkOp = FALSE;
	m_openObjAd = FALSE;
	m_openObjEng = FALSE;
	m_openObjOp = FALSE;
	m_openScrAd = FALSE;
	m_openScrEng = FALSE;
	m_openScrOp = FALSE;
	m_orgSizeAd = FALSE;
	m_orgSizeEng = FALSE;
	m_orgSizeOp = FALSE;
	m_saveDevAd = FALSE;
	m_saveDevEng = FALSE;
	m_saveDevOp = FALSE;
	m_saveMarkAd = FALSE;
	m_saveMarkEng = FALSE;
	m_saveMarkOp = FALSE;
	m_saveObjAd = FALSE;
	m_saveObjEng = FALSE;
	m_saveObjOp = FALSE;
	m_saveScrAd = FALSE;
	m_saveScrEng = FALSE;
	m_saveScrOp = FALSE;
	m_authorityAd = FALSE;
	m_authorityEng = FALSE;
	m_authorityOp = FALSE;
	m_binAd = FALSE;
	m_binEng = FALSE;
	m_binOp = FALSE;
	m_devAd = FALSE;
	m_devEng = FALSE;
	m_devOp = FALSE;
	m_fieldAd = FALSE;
	m_fieldEng = FALSE;
	m_fieldOp = FALSE;
	m_paraAd = FALSE;
	m_paraEng = FALSE;
	m_paraOp = FALSE;
	m_passAd = FALSE;
	m_passEng = FALSE;
	m_passOp = FALSE;
	m_zoomAd = FALSE;
	m_zoomEng = FALSE;
	m_zoomOp = FALSE;
	m_laserCtlAd = FALSE;
	m_laserCtlEng = FALSE;
	m_laserCtlOp = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSetAuthority::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetAuthority)
	DDX_Check(pDX, IDC_ALIGNOBJ_AD, m_alignAd);
	DDX_Check(pDX, IDC_ALIGNOBJ_ENG, m_alignEng);
	DDX_Check(pDX, IDC_ALIGNOBJ_OP, m_alignOp);
	DDX_Check(pDX, IDC_AUTOMARK_AD, m_autoMarkAd);
	DDX_Check(pDX, IDC_AUTOMARK_ENG, m_autoMarkEng);
	DDX_Check(pDX, IDC_AUTOMARK_OP, m_autoMarkOp);
	DDX_Check(pDX, IDC_CREATEOBJ_AD, m_createAd);
	DDX_Check(pDX, IDC_CREATEOBJ_ENG, m_createEng);
	DDX_Check(pDX, IDC_CREATEOBJ_OP, m_createOp);
	DDX_Check(pDX, IDC_EDITOBJ_AD, m_editObjAd);
	DDX_Check(pDX, IDC_EDITOBJ_ENG, m_editObjEng);
	DDX_Check(pDX, IDC_EDITOBJ_OP, m_editObjOp);
	DDX_Check(pDX, IDC_MANUALMARK_AD, m_manualMarkAd);
	DDX_Check(pDX, IDC_MANUALMARK_ENG, m_manualMarkEng);
	DDX_Check(pDX, IDC_MANUALMARK_OP, m_manualMarkOp);
	DDX_Check(pDX, IDC_MARKORDER_AD, m_markOrderAd);
	DDX_Check(pDX, IDC_MARKORDER_ENG, m_markOrderEng);
	DDX_Check(pDX, IDC_MARKORDER_OP, m_markOrderOp);
	DDX_Check(pDX, IDC_NEWDOC_AD, m_newDocAd);
	DDX_Check(pDX, IDC_NEWDOC_ENG, m_newDocEng);
	DDX_Check(pDX, IDC_NEWDOC_OP, m_newDocOp);
	DDX_Check(pDX, IDC_OBJMOVE_AD, m_objMoveAd);
	DDX_Check(pDX, IDC_OBJMOVE_ENG, m_objMoveEng);
	DDX_Check(pDX, IDC_OBJMOVE_OP, m_objMoveOp);
	DDX_Check(pDX, IDC_OPENDEV_AD, m_openDevAd);
	DDX_Check(pDX, IDC_OPENDEV_ENG, m_openDevEng);
	DDX_Check(pDX, IDC_OPENDEV_OP, m_openDevOp);
	DDX_Check(pDX, IDC_OPENMARK_AD, m_openMarkAd);
	DDX_Check(pDX, IDC_OPENMARK_ENG, m_openMarkEng);
	DDX_Check(pDX, IDC_OPENMARK_OP, m_openMarkOp);
	DDX_Check(pDX, IDC_OPENOBJ_AD, m_openObjAd);
	DDX_Check(pDX, IDC_OPENOBJ_ENG, m_openObjEng);
	DDX_Check(pDX, IDC_OPENOBJ_OP, m_openObjOp);
	DDX_Check(pDX, IDC_OPENSCR_AD, m_openScrAd);
	DDX_Check(pDX, IDC_OPENSCR_ENG, m_openScrEng);
	DDX_Check(pDX, IDC_OPENSCR_OP, m_openScrOp);
	DDX_Check(pDX, IDC_ORGSIZE_AD, m_orgSizeAd);
	DDX_Check(pDX, IDC_ORGSIZE_ENG, m_orgSizeEng);
	DDX_Check(pDX, IDC_ORGSIZE_OP, m_orgSizeOp);
	DDX_Check(pDX, IDC_SAVEDEV_AD, m_saveDevAd);
	DDX_Check(pDX, IDC_SAVEDEV_ENG, m_saveDevEng);
	DDX_Check(pDX, IDC_SAVEDEV_OP, m_saveDevOp);
	DDX_Check(pDX, IDC_SAVEMARK_AD, m_saveMarkAd);
	DDX_Check(pDX, IDC_SAVEMARK_ENG, m_saveMarkEng);
	DDX_Check(pDX, IDC_SAVEMARK_OP, m_saveMarkOp);
	DDX_Check(pDX, IDC_SAVEOBJ_AD, m_saveObjAd);
	DDX_Check(pDX, IDC_SAVEOBJ_ENG, m_saveObjEng);
	DDX_Check(pDX, IDC_SAVEOBJ_OP, m_saveObjOp);
	DDX_Check(pDX, IDC_SAVESCR_AD, m_saveScrAd);
	DDX_Check(pDX, IDC_SAVESCR_ENG, m_saveScrEng);
	DDX_Check(pDX, IDC_SAVESCR_OP, m_saveScrOp);
	DDX_Check(pDX, IDC_SETAUTHORITY_AD, m_authorityAd);
	DDX_Check(pDX, IDC_SETAUTHORITY_ENG, m_authorityEng);
	DDX_Check(pDX, IDC_SETAUTHORITY_OP, m_authorityOp);
	DDX_Check(pDX, IDC_SETBIN_AD, m_binAd);
	DDX_Check(pDX, IDC_SETBIN_ENG, m_binEng);
	DDX_Check(pDX, IDC_SETBIN_OP, m_binOp);
	DDX_Check(pDX, IDC_SETDEV_AD, m_devAd);
	DDX_Check(pDX, IDC_SETDEV_ENG, m_devEng);
	DDX_Check(pDX, IDC_SETDEV_OP, m_devOp);
	DDX_Check(pDX, IDC_SETFIELD_AD, m_fieldAd);
	DDX_Check(pDX, IDC_SETFIELD_ENG, m_fieldEng);
	DDX_Check(pDX, IDC_SETFIELD_OP, m_fieldOp);
	DDX_Check(pDX, IDC_SETPARA_AD, m_paraAd);
	DDX_Check(pDX, IDC_SETPARA_ENG, m_paraEng);
	DDX_Check(pDX, IDC_SETPARA_OP, m_paraOp);
	DDX_Check(pDX, IDC_SETPASS_AD, m_passAd);
	DDX_Check(pDX, IDC_SETPASS_ENG, m_passEng);
	DDX_Check(pDX, IDC_SETPASS_OP, m_passOp);
	DDX_Check(pDX, IDC_ZOOM_AD, m_zoomAd);
	DDX_Check(pDX, IDC_ZOOM_ENG, m_zoomEng);
	DDX_Check(pDX, IDC_ZOOM_OP, m_zoomOp);
	DDX_Check(pDX, IDC_LASERCTL_AD, m_laserCtlAd);
	DDX_Check(pDX, IDC_LASERCTL_ENG, m_laserCtlEng);
	DDX_Check(pDX, IDC_LASERCTL_OP, m_laserCtlOp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetAuthority, CDialog)
	//{{AFX_MSG_MAP(CDlgSetAuthority)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetAuthority message handlers

BOOL CDlgSetAuthority::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
