// InsertFail.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InsertFail.h"
#include "afxdialogex.h"


// CInsertFail 대화 상자입니다.

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


// CInsertFail 메시지 처리기입니다.


void CInsertFail::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CInsertFail::SetFailText(const CString& text)
{
    CWnd* pDlgItem = GetDlgItem(IDC_CTTEXT_FAIL); // 컨트롤 가져오기
    if (pDlgItem != NULL)
    {
        pDlgItem->SetWindowText(text); // 텍스트 설정
    }
}
