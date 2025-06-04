// DlgBin.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgBin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBin dialog


CDlgBin::CDlgBin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBin::IDD, pParent)
{

	for (int i=0; i < MAX_BIN_SIZE;i++)	{
		for (int j=0; j < MAX_BIN_SIZE; j++) {
			m_iBinbit[i][j] = 2;
		}
	}
	//{{AFX_DATA_INIT(CDlgBin)
	
	//}}AFX_DATA_INIT
}


void CDlgBin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBin)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
	
	int i, j, index;
	CString strIndex;



	// BinNumber Control 생성
	//index = IDC_INDEX_BIN1;
	//for (i = 0; i < MAX_BIN_SIZE; i++) {
	//	DDX_Text(pDX, index+i, m_strBinData[i]);
		//strIndex.Format("%d",index+i);
	//	DDV_MaxChars(pDX,m_strBinData[i], 3);
	//}

	// BinData Control 생성
	index = IDC_BIN1_BIT1;
	for (i=0; i < MAX_BIN_SIZE;i++)
	{
		for (j=0; j < MAX_BIN_SIZE; j++)
		{
			DDX_Check(pDX, index+i*MAX_BIN_SIZE+j, m_iBinbit[i][j]);
		}
	}
}


BEGIN_MESSAGE_MAP(CDlgBin, CDialog)
	//{{AFX_MSG_MAP(CDlgBin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBin message handlers
#include "LoadString.h"

BOOL CDlgBin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// String 로딩
	CLoadString LoadString;
	LoadString.LoadString(this, -1, -1, -1, TRUE, TRUE);
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
	
	// 예제 Check Box 초기화
	CButton *pButton;
	pButton = (CButton*)GetDlgItem(IDC_HIGH);
	pButton->SetCheck(1);
	pButton = (CButton*)GetDlgItem(IDC_LOW);
	pButton->SetCheck(0);
	pButton = (CButton*)GetDlgItem(IDC_DONT_CARE);
	pButton->SetCheck(3);
	
	// CBin Instance 얻어오기
	m_pBin = m_pBin->GetInstance();

	LoadValue();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBin::OnOK() 
{
	// TODO: Add extra validation here
	SetValue();
	
	CDialog::OnOK();
}

void CDlgBin::LoadValue()
{
	// BinNumber와 BinData 받아오기
//	CString *pBinNumber = new CString;
//	CString *pBinData = new CString;
	CString pBinNumber;
	CString pBinData;

	int i, j;
	for (i = 0; i < MAX_BIN_SIZE; i++) {
//		m_pBin->GetBinData(i, pBinNumber, pBinData);
//		m_strBinData[i] = *pBinData;
		m_pBin->GetBinData(i, &pBinNumber, &pBinData);
		m_strBinData[i] = pBinData;
		for (j = 0; j < MAX_BIN_SIZE; j++)
			m_iBinbit[i][j] = pBinNumber.GetAt(j) - '0'; 
//			m_iBinbit[i][j] = (*pBinNumber).GetAt(j) - '0'; 
	}
//	UpdateData(FALSE);
}

void CDlgBin::SetValue()
{
	UpdateData(TRUE);
	CString strBinNumber("");
	for (int i = 0; i < MAX_BIN_SIZE; i++) {
		strBinNumber = "";
		for (int j = 0; j < MAX_BIN_SIZE; j++) {
			char ch;
			ch = m_iBinbit[i][j] + '0';
			strBinNumber += ch;
		}
		m_pBin->SetBinData(i, strBinNumber, m_strBinData[i]);
	}
}
