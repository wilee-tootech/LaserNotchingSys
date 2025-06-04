// InsertFail.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InsertFail.h"
#include "afxdialogex.h"


// CInsertFail ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInsertFail, CDialogEx)

CInsertFail::CInsertFail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertFail::IDD, pParent)
{

}

CInsertFail::~CInsertFail()
{
}

void CInsertFail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInsertFail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInsertFail::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsertFail �޽��� ó�����Դϴ�.


void CInsertFail::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CInsertFail::SetFailText(const CString& text)
{
    CWnd* pDlgItem = GetDlgItem(IDC_CTTEXT_FAIL); // ��Ʈ�� ��������
    if (pDlgItem != NULL)
    {
        pDlgItem->SetWindowText(text); // �ؽ�Ʈ ����
    }
}
