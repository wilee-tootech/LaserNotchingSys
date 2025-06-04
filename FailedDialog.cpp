#include "stdafx.h"
#include "FailedDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CFailedDialog, CDialogEx)

CFailedDialog::CFailedDialog(CWnd* pParent /*= nullptr*/)
    : CDialogEx(IDD_DLG_FAIL_LOGIN, pParent)
{
}

CFailedDialog::~CFailedDialog()
{
}

void CFailedDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CONT, m_strMessage); // IDC_EDIT_CONT�� ���� �޽����� ǥ���� Edit Control�� ID�Դϴ�.
}

BEGIN_MESSAGE_MAP(CFailedDialog, CDialogEx)
END_MESSAGE_MAP()
