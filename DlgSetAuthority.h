#if !defined(AFX_DLGSETAUTHORITY_H__F255D981_3014_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGSETAUTHORITY_H__F255D981_3014_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetAuthority.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetAuthority dialog

class CDlgSetAuthority : public CDialog
{
// Construction
public:
	CDlgSetAuthority(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetAuthority)
	enum { IDD = IDD_DLG_WORK_AUTHORITY };
	BOOL	m_alignAd;
	BOOL	m_alignEng;
	BOOL	m_alignOp;
	BOOL	m_autoMarkAd;
	BOOL	m_autoMarkEng;
	BOOL	m_autoMarkOp;
	BOOL	m_createAd;
	BOOL	m_createEng;
	BOOL	m_createOp;
	BOOL	m_editObjAd;
	BOOL	m_editObjEng;
	BOOL	m_editObjOp;
	BOOL	m_manualMarkAd;
	BOOL	m_manualMarkEng;
	BOOL	m_manualMarkOp;
	BOOL	m_markOrderAd;
	BOOL	m_markOrderEng;
	BOOL	m_markOrderOp;
	BOOL	m_newDocAd;
	BOOL	m_newDocEng;
	BOOL	m_newDocOp;
	BOOL	m_objMoveAd;
	BOOL	m_objMoveEng;
	BOOL	m_objMoveOp;
	BOOL	m_openDevAd;
	BOOL	m_openDevEng;
	BOOL	m_openDevOp;
	BOOL	m_openMarkAd;
	BOOL	m_openMarkEng;
	BOOL	m_openMarkOp;
	BOOL	m_openObjAd;
	BOOL	m_openObjEng;
	BOOL	m_openObjOp;
	BOOL	m_openScrAd;
	BOOL	m_openScrEng;
	BOOL	m_openScrOp;
	BOOL	m_orgSizeAd;
	BOOL	m_orgSizeEng;
	BOOL	m_orgSizeOp;
	BOOL	m_saveDevAd;
	BOOL	m_saveDevEng;
	BOOL	m_saveDevOp;
	BOOL	m_saveMarkAd;
	BOOL	m_saveMarkEng;
	BOOL	m_saveMarkOp;
	BOOL	m_saveObjAd;
	BOOL	m_saveObjEng;
	BOOL	m_saveObjOp;
	BOOL	m_saveScrAd;
	BOOL	m_saveScrEng;
	BOOL	m_saveScrOp;
	BOOL	m_authorityAd;
	BOOL	m_authorityEng;
	BOOL	m_authorityOp;
	BOOL	m_binAd;
	BOOL	m_binEng;
	BOOL	m_binOp;
	BOOL	m_devAd;
	BOOL	m_devEng;
	BOOL	m_devOp;
	BOOL	m_fieldAd;
	BOOL	m_fieldEng;
	BOOL	m_fieldOp;
	BOOL	m_paraAd;
	BOOL	m_paraEng;
	BOOL	m_paraOp;
	BOOL	m_passAd;
	BOOL	m_passEng;
	BOOL	m_passOp;
	BOOL	m_zoomAd;
	BOOL	m_zoomEng;
	BOOL	m_zoomOp;
	BOOL	m_laserCtlAd;
	BOOL	m_laserCtlEng;
	BOOL	m_laserCtlOp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetAuthority)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetAuthority)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETAUTHORITY_H__F255D981_3014_11D6_97D6_0000B4BB2A6F__INCLUDED_)
