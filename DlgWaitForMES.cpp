// DlgWaitForMES.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgWaitForMES.h"
#include "afxdialogex.h"


// CDlgWaitForMES ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgWaitForMES, CDialogEx)

CDlgWaitForMES::CDlgWaitForMES(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWaitForMES::IDD, pParent)
{

}

CDlgWaitForMES::~CDlgWaitForMES()
{
}

void CDlgWaitForMES::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgWaitForMES, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDlgWaitForMES::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgWaitForMES::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgWaitForMES �޽��� ó�����Դϴ�.


void CDlgWaitForMES::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void CDlgWaitForMES::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

void CDlgWaitForMES::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) // Ÿ�̸� ID
    {
        OnCancel(); // ��ȭ ���� �ݱ�
        KillTimer(1); // Ÿ�̸� ����
    }

    CDialogEx::OnTimer(nIDEvent);
}

BOOL CDlgWaitForMES::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CenterWindow();

    return TRUE;
}
