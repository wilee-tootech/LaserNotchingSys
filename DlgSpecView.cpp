// DlgSpecView.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgSpecView.h"
#include "FieldParameter.h"
#include "InitialTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSpecView dialog


CDlgSpecView::CDlgSpecView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpecView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSpecView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strPartNo = _T("");
	m_strMsg= _T("");
	m_strFileName = _T("");

}


void CDlgSpecView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSpecView)
	
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSpecView, CDialog)
	//{{AFX_MSG_MAP(CDlgSpecView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSpecView message handlers

void CDlgSpecView::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDlgSpecView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString m_strSpecImgFolder = pInitialTable->GetSpecImgFolder();
	m_strPartNo = pFieldParameter->GetPartNo();

	m_strFileName.Format("%s\\%s.bmp",m_strSpecImgFolder,m_strPartNo);

	CFileFind filefind;
	
	if(FALSE == filefind.FindFile(m_strFileName)){
		m_strMsg.Format("%s   Can not found file!",m_strFileName); 
		AfxMessageBox(m_strMsg);
	}
	else
	{
		//m_Picture.SetBitmap("c:\\image.bmp");	
		m_Picture.SetBitmap(m_strFileName);	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
