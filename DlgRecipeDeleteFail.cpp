// DlgRecipeDeleteFail.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgRecipeDeleteFail.h"
#include "afxdialogex.h"


// CDlgRecipeDeleteFail 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRecipeDeleteFail, CDialogEx)

CDlgRecipeDeleteFail::CDlgRecipeDeleteFail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecipeDeleteFail::IDD, pParent)
{

}

CDlgRecipeDeleteFail::~CDlgRecipeDeleteFail()
{
}

void CDlgRecipeDeleteFail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRecipeDeleteFail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRecipeDeleteFail::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRecipeDeleteFail 메시지 처리기입니다.


void CDlgRecipeDeleteFail::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
