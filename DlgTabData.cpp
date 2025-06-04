// DlgTabData.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgTabData.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgTabData 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTabData, CDialogEx)

CDlgTabData::CDlgTabData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTabData::IDD, pParent)
	, m_bUseReverse(FALSE)
	, m_dTabPosition(0)
	, m_dOffset(0)
{

}

CDlgTabData::~CDlgTabData()
{
}

void CDlgTabData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_USE_REVERSE, m_bUseReverse);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_dTabPosition);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_dOffset);
}


BEGIN_MESSAGE_MAP(CDlgTabData, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgTabData 메시지 처리기입니다.


void CDlgTabData::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


void CDlgTabData::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	UpdateData(true);
	CDialogEx::OnOK();
}

