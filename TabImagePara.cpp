// TabImagePara.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TabImagePara.h"
#include "LoadString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabImagePara dialog


CTabImagePara::CTabImagePara(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabImagePara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabImagePara)
	m_iBmpSize = 0;
	m_iDwellTime = 0;
	m_iLineMoveDelayTime = 0;
	//}}AFX_DATA_INIT
}


void CTabImagePara::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabImagePara)
	DDX_Text(pDX, IDC_BMPSIZE, m_iBmpSize);
	DDX_Text(pDX, IDC_DWELLTIME, m_iDwellTime);
	DDX_Text(pDX, IDC_MOVEDELAYTIME, m_iLineMoveDelayTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabImagePara, CDialog)
	//{{AFX_MSG_MAP(CTabImagePara)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabImagePara message handlers

BOOL CTabImagePara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	LoadString.LoadString(this, IDS_IMAGEPARA_1, IDC_IMAGEPARA_1, IDC_IMAGEPARA_1, FALSE, FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
