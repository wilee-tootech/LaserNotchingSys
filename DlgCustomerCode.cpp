// DlgCustomerCode.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgCustomerCode.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomerCode dialog


CDlgCustomerCode::CDlgCustomerCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCustomerCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCustomerCode)
	m_EditIndex = 0;
	m_EditCode = _T("");
	m_ComboCode = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCustomerCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCustomerCode)
	DDX_Control(pDX, IDC_LIST_CUSTOMER, m_ListControl);
	DDX_Text(pDX, IDC_EDIT_CODE, m_EditCode);
	DDV_MaxChars(pDX, m_EditCode, 2);
	DDX_CBString(pDX, IDC_COMBO_SEL, m_ComboCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCustomerCode, CDialog)
	//{{AFX_MSG_MAP(CDlgCustomerCode)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CUSTOMER, OnClickListCustomer)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomerCode message handlers


void CDlgCustomerCode::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgCustomerCode::OnButtonInsert() 
{
	// TODO: Add your control notification handler code here
	int count = m_ListControl.GetItemCount();

	LV_ITEM lvitem;
	int index, select;
	CString str;

	UpdateData(true);

	for (int i = 0; i < count; i++)
	{
		if (m_ListControl.GetItemText(i, 0) == m_EditCode)
		{
			//AfxMessageBox("등록된 코드입니다. 다른 코드를 입력하세요.");
			return;
		}
	}

	GetDlgItemText(IDC_EDIT_CODE, str);
	if (str == "")
	{
		AfxMessageBox("Code 값을 입력하세요.");
//		AfxMessageBox("Input the Code, please.");	//in English
		return;
	}

	if (str.GetLength() != 2)
	{
		AfxMessageBox("Code 값은 두자리를 입력해야 합니다.");
//		AfxMessageBox("Input 2-digit code.");	//in English
		return;
	}

	select = ((CComboBox*)GetDlgItem(IDC_COMBO_SEL))->GetCurSel();
	if (select < 0)
	{
		AfxMessageBox("Customer를 선택하세요.");
//		AfxMessageBox("Select Customer.");	//in English
		return;
	}

    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = count;

    lvitem.iSubItem = 0;
    lvitem.pszText = (LPSTR)(LPCTSTR)m_EditCode;
    index = m_ListControl.InsertItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 1;
    lvitem.pszText = (LPSTR)(LPCTSTR)m_ComboCode;
	m_ListControl.SetItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 2;
	str.Format("%d", select);
    lvitem.pszText = (LPSTR)(LPCTSTR)str;
	m_ListControl.SetItem(&lvitem);	

	((CComboBox*)GetDlgItem(IDC_COMBO_SEL))->SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_CODE, "");
}

void CDlgCustomerCode::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//int index = m_ListControl.GetSelectedCount();

	if (m_index < 0)
	{
		AfxMessageBox("삭제 할 항목을 선택하세요.");
//		AfxMessageBox("Select the item to delete.");	//in English
		return;
	}

	m_ListControl.DeleteItem(m_index);
}

void CDlgCustomerCode::DataLoad()
{
	/*
	FILE *fp_ ;
	int count, index, result;
	char code[] = "XX\0";
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

	fp_  = fopen("CustomerData.txt", "rt");
	if (fp_  == NULL)
	{
		AfxMessageBox("설정 내용을 불러올 수 없습니다.");
		return;
	}

	m_ListControl.DeleteAllItems();

	pDoc->ResetCusData();
	count = 0;
	while(true)
	{
		result = fscanf(fp_ , "%d,%c%c\n", &index, &code[0], &code[1]);

		if (result < 0)	break;

		SetDlgItemText(IDC_EDIT_CODE, (CString)code);
		((CComboBox*)GetDlgItem(IDC_COMBO_SEL))->SetCurSel(index);
		OnButtonInsert();

		pDoc->structCusData[count].index = index;
		pDoc->structCusData[count].code[0] = (TCHAR)code[0];
		pDoc->structCusData[count].code[1] = (TCHAR)code[1];
		count++;
	}

	fclose(fp_ );
	*/

	int count = 0;
	CString str = "XXX";
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

	m_ListControl.DeleteAllItems();

	while(true)
	{
		if (pDoc->structCusData[count].index < 0)	break;

		str.SetAt(0, pDoc->structCusData[count].code[0]);
		str.SetAt(1, pDoc->structCusData[count].code[1]);
		str.SetAt(2, '\0');

		SetDlgItemText(IDC_EDIT_CODE, str);
		((CComboBox*)GetDlgItem(IDC_COMBO_SEL))->SetCurSel(pDoc->structCusData[count].index);
		OnButtonInsert();

		count++;
	}
}

void CDlgCustomerCode::DataSave()
{
	FILE *fp_ ;
	CString str;
	int index;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
//	fp_  = fopen("CustomerData.txt", "wt");	
	fp_  = fopen(pApp->m_strCwd + "\\CustomerData.txt","wt");	
	if (fp_  == NULL)
	{
		AfxMessageBox("설정 내용을 저장할 수 없습니다.");
//		AfxMessageBox("Cannot save the data.");	//in English
		return;
	}

	int count = m_ListControl.GetItemCount();
	pDoc->ResetCusData();

	for (int i = 0; i < count; i++)
	{
		str.Format("%s", m_ListControl.GetItemText(i, 0));
		index = atoi(m_ListControl.GetItemText(i, 2));
		fprintf(fp_ , "%d,%c%c\n", index, str.GetAt(0), str.GetAt(1));

		pDoc->structCusData[i].index = index;
		pDoc->structCusData[i].code[0] = str.GetAt(0);
		pDoc->structCusData[i].code[1] = str.GetAt(1);
	}

	fclose(fp_ );
}

BOOL CDlgCustomerCode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
    m_ListControl.InsertColumn(0, "Code", LVCFMT_LEFT, 50);
    m_ListControl.InsertColumn(1, "Customer", LVCFMT_LEFT, 120);
	m_ListControl.InsertColumn(2, "Index", LVCFMT_LEFT, 80);
	
	DataLoad();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCustomerCode::OnOK() 
{
	// TODO: Add extra validation here
	DataSave();

	CDialog::OnOK();
}

void CDlgCustomerCode::OnClickListCustomer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_index = -1;

    m_index = m_ListControl.GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);

    if(m_index == -1) 
        return;

	*pResult = 0;
}

BOOL CDlgCustomerCode::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}

int CDlgCustomerCode::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
