// DlgDeleteRecipeSucc.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgDeleteRecipeSucc.h"
#include "afxdialogex.h"


// CDlgDeleteRecipeSucc 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgDeleteRecipeSucc, CDialogEx)

CDlgDeleteRecipeSucc::CDlgDeleteRecipeSucc(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDeleteRecipeSucc::IDD, pParent)
{

}

CDlgDeleteRecipeSucc::~CDlgDeleteRecipeSucc()
{
}

void CDlgDeleteRecipeSucc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDeleteRecipeSucc, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDeleteRecipeSucc::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgDeleteRecipeSucc 메시지 처리기입니다.


void CDlgDeleteRecipeSucc::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

BOOL CDlgDeleteRecipeSucc::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CenterWindow();

	return TRUE;
}
	
