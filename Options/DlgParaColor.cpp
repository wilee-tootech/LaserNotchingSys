// DlgParaColor.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DlgParaColor.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParaColor dialog


CDlgParaColor::CDlgParaColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParaColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParaColor)
	//}}AFX_DATA_INIT
}


void CDlgParaColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParaColor)
	DDX_Control(pDX, IDC_PARA_9, m_ctlPara[8]);
	DDX_Control(pDX, IDC_PARA_8, m_ctlPara[7]);
	DDX_Control(pDX, IDC_PARA_7, m_ctlPara[6]);
	DDX_Control(pDX, IDC_PARA_6, m_ctlPara[5]);
	DDX_Control(pDX, IDC_PARA_5, m_ctlPara[4]);
	DDX_Control(pDX, IDC_PARA_4, m_ctlPara[3]);
	DDX_Control(pDX, IDC_PARA_3, m_ctlPara[2]);
	DDX_Control(pDX, IDC_PARA_20, m_ctlPara[19]);
	DDX_Control(pDX, IDC_PARA_2, m_ctlPara[1]);
	DDX_Control(pDX, IDC_PARA_19, m_ctlPara[18]);
	DDX_Control(pDX, IDC_PARA_18, m_ctlPara[17]);
	DDX_Control(pDX, IDC_PARA_17, m_ctlPara[16]);
	DDX_Control(pDX, IDC_PARA_16, m_ctlPara[15]);
	DDX_Control(pDX, IDC_PARA_15, m_ctlPara[14]);
	DDX_Control(pDX, IDC_PARA_14, m_ctlPara[13]);
	DDX_Control(pDX, IDC_PARA_13, m_ctlPara[12]);
	DDX_Control(pDX, IDC_PARA_12, m_ctlPara[11]);
	DDX_Control(pDX, IDC_PARA_11, m_ctlPara[10]);
	DDX_Control(pDX, IDC_PARA_10, m_ctlPara[9]);
	DDX_Control(pDX, IDC_PARA_1, m_ctlPara[0]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParaColor, CDialog)
	//{{AFX_MSG_MAP(CDlgParaColor)
	ON_BN_CLICKED(IDC_PARA_1, OnPara1)
	ON_BN_CLICKED(IDC_PARA_2, OnPara2)
	ON_BN_CLICKED(IDC_PARA_3, OnPara3)
	ON_BN_CLICKED(IDC_PARA_4, OnPara4)
	ON_BN_CLICKED(IDC_PARA_5, OnPara5)
	ON_BN_CLICKED(IDC_PARA_6, OnPara6)
	ON_BN_CLICKED(IDC_PARA_7, OnPara7)
	ON_BN_CLICKED(IDC_PARA_8, OnPara8)
	ON_BN_CLICKED(IDC_PARA_9, OnPara9)
	ON_BN_CLICKED(IDC_PARA_10, OnPara10)
	ON_BN_CLICKED(IDC_PARA_11, OnPara11)
	ON_BN_CLICKED(IDC_PARA_12, OnPara12)
	ON_BN_CLICKED(IDC_PARA_13, OnPara13)
	ON_BN_CLICKED(IDC_PARA_14, OnPara14)
	ON_BN_CLICKED(IDC_PARA_15, OnPara15)
	ON_BN_CLICKED(IDC_PARA_16, OnPara16)
	ON_BN_CLICKED(IDC_PARA_17, OnPara17)
	ON_BN_CLICKED(IDC_PARA_18, OnPara18)
	ON_BN_CLICKED(IDC_PARA_19, OnPara19)
	ON_BN_CLICKED(IDC_PARA_20, OnPara20)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParaColor message handlers

void CDlgParaColor::OnPara1() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(0);
}

void CDlgParaColor::OnPara2() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(1);
}

void CDlgParaColor::cDoModal(int iIndex)
{
	CColorDialog dlg;
	CString strColor;

	if (dlg.DoModal() == IDOK) {
		m_colPara[iIndex] = dlg.GetColor();
		m_ctlPara[iIndex].m_col = m_colPara[iIndex];
		m_ctlPara[iIndex].Invalidate(FALSE);
	}
}

void CDlgParaColor::OnPara3() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(2);	
}

void CDlgParaColor::OnPara4() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(3);	
}

void CDlgParaColor::OnPara5() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(4);	
}

void CDlgParaColor::OnPara6() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(5);
}

void CDlgParaColor::OnPara7() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(6);	
}

void CDlgParaColor::OnPara8() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(7);	
}

void CDlgParaColor::OnPara9() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(8);
}

void CDlgParaColor::OnPara10() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(9);
}

void CDlgParaColor::OnPara11() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(10);
}

void CDlgParaColor::OnPara12() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(11);
}

void CDlgParaColor::OnPara13() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(12);
}

void CDlgParaColor::OnPara14() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(13);
}

void CDlgParaColor::OnPara15() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(14);
}

void CDlgParaColor::OnPara16() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(15);
}

void CDlgParaColor::OnPara17() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(16);
}

void CDlgParaColor::OnPara18() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(17);
}

void CDlgParaColor::OnPara19() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(18);
}

void CDlgParaColor::OnPara20() 
{
	// TODO: Add your control notification handler code here
	this->cDoModal(19);
}



BOOL CDlgParaColor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for (int iIndex = 0; iIndex < PARA_NUM; iIndex++) {
		m_ctlPara[iIndex].m_col = m_colPara[iIndex];
		m_ctlPara[iIndex].Invalidate();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
